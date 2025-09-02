# Gardener Alex

## 题目描述

园丁 Alex 喜欢种树。我们提醒一下，树是一个包含 $n$ 个顶点的连通无环图。

今天他决定种一棵有根二叉树。二叉树是指任意一个顶点的儿子不超过两个的树。幸运的是，Alex 拥有一个从 $1$ 到 $n$ 的排列，这是他上次生日时收到的礼物，所以他决定按照这个排列来种树。具体过程如下：他找到排列中的最小元素，并将其作为树的根节点。然后将排列分为两部分：最小元素左边的所有元素和右边的所有元素。左边部分的最小元素作为根的左儿子，右边部分的最小元素作为根的右儿子。之后，对这两部分递归重复上述过程。

现在 Alex 想要种一片森林：对于排列的每一个循环左移，都种一棵树。他想知道，哪一种循环左移能使树的深度最小。不幸的是，种一片森林既困难又耗时，但 Alex 现在就想知道答案。你能帮帮他吗？

我们提醒一下，对于排列 $a_1, a_2, \ldots, a_k, \ldots, a_n$，循环左移 $k$ 位后的排列为 $a_{k+1}, a_{k+2}, \ldots, a_n, a_1, a_2, \ldots, a_k$。

## 说明/提示

下图展示了样例测试中所有可能的树以及它们对应的循环左移次数。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1220F/842ebd6718bd1cfe86bfa2961c3f54499387dbf1.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 2 3 4
```

### 输出

```
3 2
```

# 题解

## 作者：houzhiyuan (赞：12)

为啥前一篇题解的做法这么阴间啊。

其实不是很难，考虑最后树一定是 $1$ 为根，那么相当于在 $1$ 左边有一棵树，右边有一棵树。

问题转化为已知一个序列，求每个前缀的笛卡尔树深度。

这个直接在单调栈建树的时候直接统计就好了，具体而言，记录 $dep_i$ 表示 $i$ 下面有多少个点，加入一个点的时候删掉的点里找最大值即可。

然后前缀做一遍，后缀做一遍，直接合并即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int st[N],top,dep[N];
void work(vector<int> &vec,int *f){
    if(vec.size()){
        f[1]=1;
        st[top=1]=vec[0],dep[1]=0;
        for(int i=1;i<vec.size();i++){
            f[i+1]=f[i];
            if(vec[i]>st[top])st[++top]=vec[i],f[i+1]=max(f[i+1],top),dep[top]=0;
            else {
                int s=0;
                while(st[top]>vec[i]&&top)s=max(s,top+1+dep[top]),top--;
                f[i+1]=max(f[i+1],s);
                st[++top]=vec[i],dep[top]=s-top;
            }
        }
    }
    for(int i=0;i<=vec.size();i++)f[i]++;
}
int n,a[N],f[N],g[N],ans1=1e9;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=n+1;i<=2*n;i++)a[i]=a[i-n];
    int k=0;
    for(int i=1;i<=n;i++)if(a[i]==1){
        vector<int> vec;
        for(int j=i+1;j<i+n;j++)vec.push_back(a[j]);
        work(vec,f);
        reverse(vec.begin(),vec.end());
        work(vec,g);
        k=i-1;
    }
    for(int i=0;i<n;i++)ans1=min(ans1,max(g[i],f[n-1-i]));
    printf("%d ",ans1);
    for(int i=0;i<n;i++)if(max(g[i],f[n-1-i])==ans1)return printf("%d\n",(k-i+n)%n),0;
}
```

---

## 作者：Daniel_yuan (赞：5)

~~打克隆赛的时候打乱了题目顺序，在写完 ABC 之后开始找 D 题，觉得这题似乎可做就开肝了，哪知道做了个 F。~~

先考虑生成原序列的笛卡尔树，然后把最后一个数删掉，加到最前面去。

假设一开始是 $5~2~1~3~6~4$ 。

![](https://cdn.luogu.com.cn/upload/image_hosting/44t8ar32.png)


把 $4$ 丢到前面变成了 $4~5~2~1~3~6$

![](https://cdn.luogu.com.cn/upload/image_hosting/qtn9fi46.png)

可以发现，设删除的是最后一个数为 $x$，它是没有右儿子的，而且其左子树的范围就是上一个小于它的数到它的这个区间（如上述初始序列的位置 $(4,6)$）。删掉它后，它的左儿子会代替它的位置，所以它的左子树的总体深度会减一。

同样的，考虑分析把数 $x$ 插到最前面去，它是没有左儿子的，而且其右子树的范围就是它到下一个小于它的数的这个区间（如上述修改后的序列位置 $(1,3)$）。加入它后，它所占的地方的子树会变成它的右子树，所以这一段的总体深度会加一。

有了这个性质之后就可以动态维护这棵笛卡尔树的深度。只需要写个支持区间加，区间求 $\min$ 的线段树即可。至于找区间内下一个/上一个小于某个数的值的位置，可以用二分加 ST 表。

代码如下：（考时代码求轻喷）

```cpp
#include <bits/stdc++.h>
#define RI register int
typedef long long LL;

#define FILEIO(name) freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);

using namespace std;

char buf[1000000], *p1 = buf, *p2 = buf;
inline char gc() {
  if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin);
  return p1 == p2 ? EOF : *(p1++);
}
template <class T> inline void read(T &n) {
  n = 0; RI ch = gc(), f;
  while ((ch < '0' || ch > '9') && ch != '-') ch = gc();
  f = (ch == '-' ? ch = gc(), -1 : 1);
  while (ch >= '0' && ch <= '9') n = n * 10 + (ch ^ 48), ch = gc();
  n *= f;
}

int const MAXN = 4e5 + 5;
int a[MAXN], b[MAXN];
int Mn[MAXN][21];
int child[MAXN][2], stk[MAXN], val[MAXN];
int D[MAXN];
int LOG[MAXN];
int Mx[MAXN * 4], tag[MAXN * 4];

void Dfs(int now, int dep) {
  D[now] = dep;
  if (child[now][0]) Dfs(child[now][0], dep + 1);
  if (child[now][1]) Dfs(child[now][1], dep + 1);
}
inline int GetMin(int l, int r) {
  int k = LOG[r - l + 1];
  return min(Mn[l][k], Mn[r - (1 << k) + 1][k]);
}

#define lc (x << 1)
#define rc (x << 1 | 1)
inline void Update(int x) { Mx[x] = max(Mx[lc], Mx[rc]); }
inline void Add(int x, int num) { Mx[x] += num, tag[x] += num; }
inline void Pushdown(int x) { if (tag[x]) Add(lc, tag[x]), Add(rc, tag[x]), tag[x] = 0; }
void Modify(int x, int l, int r, int i, int j, int num) {
  if (i <= l && r <= j) return Add(x, num);
  Pushdown(x);
  int mid = (l + r) >> 1;
  if (i <= mid) Modify(lc, l, mid, i, j, num);
  if (j > mid) Modify(rc, mid + 1, r, i, j, num);
  Update(x);
}
int Query(int x, int l, int r, int i, int j) {
  if (i <= l && r <= j) return Mx[x];
  Pushdown(x);
  int mid = (l + r) >> 1, re = -1;
  if (i <= mid) re = max(re, Query(lc, l, mid, i, j));
  if (j > mid) re = max(re, Query(rc, mid + 1, r, i, j));
  return re;
}
#undef lc
#undef rc

int main() {
  
#ifdef LOCAL
  FILEIO("a");
#endif

  int n; read(n);
  LOG[1] = 0;
  for (RI i = 2; i <= n + n; ++i)
    LOG[i] = LOG[i >> 1] + 1;
  for (RI i = 1; i <= n; ++i) read(b[i]);
  for (RI i = 1; i <= n; ++i)
    if (b[i] == 1) {
      for (RI j = 1; j <= n; ++j, i = i % n + 1)
        a[j] = b[i];
      break;
    }
  for (RI i = n + 1; i <= n + n; ++i) a[i] = a[i - n];
  for (RI i = 1; i <= n + n; ++i)
    Mn[i][0] = a[i];
  for (RI k = 1; k <= 19; ++k)
    for (RI i = 1; i + (1 << k) - 1 <= n + n; ++i)
      Mn[i][k] = min(Mn[i][k - 1], Mn[i + (1 << (k - 1))][k - 1]);

/* 构造初始笛卡尔树 */

  int L = n + 1, R = n + n, top = 0;
  for (RI i = L; i <= R; ++i) {
    int x = a[i];
    while (top && val[top] > x) --top;
    if (top) child[stk[top]][1] = i;
    child[i][0] = stk[top + 1];
    stk[++top] = i;
    val[top] = x;
    stk[top + 1] = 0;
  }
 
  Dfs(n + 1, 1);
  for (RI i = L; i <= R; ++i)
    Modify(1, 1, n + n, i, i, D[i]);
  int tmp = Query(1, 1, n + n, L, R);
  int ans = 0x7f7f7f7f, anspos = 0;
  if (tmp < ans) ans = tmp, anspos = L;
  
  for (RI i = n; i > 1; --i) {
  
  /* 删掉最后一个 */
    int del = i + n;
    int l = L, r = R - 1, mid, pos;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (GetMin(mid, R) < a[del]) pos = mid, l = mid + 1;
      else r = mid - 1;
    }
    Modify(1, 1, n + n, pos + 1, del, -1);
    
/* 把刚刚删掉的插到第一个 */

    int ins = i;
    l = L, r = R - 1;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (GetMin(L, mid) < a[ins]) pos = mid, r = mid - 1;
      else l = mid + 1;
    }
    int Deep = Query(1, 1, n + n, pos, pos);
    Modify(1, 1, n + n, ins, ins, Deep);
    Modify(1, 1, n + n, ins, pos - 1, 1);

    --L, --R;
    int tmp = Query(1, 1, n + n, L, R);
    if (tmp < ans)
      ans = tmp, anspos = L;
  }
  int k = a[anspos];
  for (RI i = 1; i <= n; ++i)
    if (k == b[i])
      printf("%d %d\n", ans, i - 1);

  return 0;
}

// created by Daniel yuan

```


---

## 作者：Kingna (赞：4)

## [CF1220F Gardener Alex](https://www.luogu.com.cn/problem/CF1220F)

### 题目翻译

有一个 $1\sim n$ 的排列，按照这个序列建二叉树：
* 找最小的元素作为根。
* 排列被分为这个元素的左边和右边两个部分。
* 左边最小元素成为左子节点，右边最小元素成为右子节点。

现在可将序列往左移动一些单位，输出移动后树的最小深度，及需要向左移动多少的元素才能到达这个深度。


### 思路

首先移动排列，使 $1$ 成为最左边的元素。现在这个问题可以这样理解：一定以 $1$ 为根，且 $1$ 左边一棵树，右边一棵树。不妨设数组从 $0$ 开始，那么此时 $1$ 就是 $0$ 号元素。

现在，我们要将新数组拆分为两个部分（其中一个可能是空的），以便最小化两个部分的树的最大深度。其中一个部分从下标 $1$ 开始以 $i$ 结尾的前缀，设其深度为 $s_i$。另一个部分是下标 $i$ 开始下标 $n-1$ 结束的后缀，设其深度为 $t_i$。

我们知道 $s_1\leq s_2\leq\dots \leq  s_{n-1}$ 且 $t_1\geq t_2\geq \dots \geq t_{n-1}$。那么只需要每添加一个节点，就动态更新笛卡尔树的深度，**这是可做的，但是对于此题比较复杂**。因为我们只需要二分出一个右端点 $L$ 满足 $s_L\leq t_{L+1}$。使用二分算法，再对于内层使用 $O(n)$ 求出 $[1,mid]$ 的深度和 $[mid+1,n-1]$ 的深度，复杂度即为 $O(n\log n)$。

具体怎么求 $[l,r]$ 构建笛卡尔树的深度？考虑笛卡尔树的本质，寻找区间最小的点再分成左右子树，于是只需要预处理 ST 表求出 $[l,r]$ 最小值位置即可了。

找到右端点 $L$ 后，$[1,L],[L+1,n-1]$ 和 $[1,L+1],[L+2,n-1]$ 两个解都可能是答案，比较一下大小即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long

const int N = 4e5 + 5, mod = 998244353;

int n, a[N], cycle;
PII st[21][N];

int query_min(int l, int r) { // 查找区间最小值位置
	int lg = log2(r - l + 1);
	return min(st[lg][l], st[lg][r - (1 << lg) + 1]).second; 
}

int get(int l, int r) { // 求解 [l,r] 构建笛卡尔树的深度
	if (l > r) return 0;
	if (l == r) return 1;
	int mid = query_min(l, r);
	return max(get(l, mid - 1), get(mid + 1, r)) + 1;
}

signed main() {
	cin >> n;
	_for(i, 0, n - 1) cin >> a[i];
	_for(i, 0, n - 1) if (a[i] == 1) cycle = i;
	_for(i, 0, n - 1) a[i + n] = a[i];
	_for(i, 0, n - 1) a[i] = a[n + (i + cycle) % n];
	_for(i, 0, n - 1) st[0][i] = {a[i], i};
	_for(j, 1, 19) {
		_for(i, 0, n - (1 << j)) st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
	}
	int L = 0, R = n - 1;
	while (L < R) {
		int mid = (L + R + 1) >> 1;
		if (get(1, mid) <= get(mid + 1, n - 1)) L = mid;
		else R = mid - 1;
	}
	int res1 = max(get(1, L), get(L + 1, n - 1)) + 1;
	int res2 = max(get(1, L + 1), get(L + 2, n - 1)) + 1;
	if (res1 <= res2) {
		cycle += L + 1;
		cout << res1 << ' ' << cycle % n << endl;
	}
	else {
		cycle += L + 2;
		cout << res2 << ' ' << cycle % n << endl;
	}
}
```

---

## 作者：Walrus (赞：2)

提供一个很奇怪的解法，有概率会被 hack。

观察这个序列建树后会有什么性质。

首先可以发现不管序列怎么移动建出来的树的根一定是固定的。

考虑先对初始序列建笛卡尔树，然后观察移动一位这棵树的结构会发生什么变化，按照题意很显然就是将最右边的节点接到最左边去，这时会有三种情况：

- 树的最大深度不变。
- 树的最大深度变大。
- 树的最大深度变小。

并且位移操作是「连续的」。

这里先给出一个结论（本人并不保证其一定正确）？

>假设 $A$ 是原序列位移 $x$ 位后的序列，则函数 $f(x)=\max \limits_{1\leq i \leq n} dep_i$ 是下凸的。

大概证明一下，如果树的最大深度会变小则移动的这个数的深度一定是**唯一最大的**。若下一次位移会将最大深度变大，则下下次位移一定不会将最大深度再次减小，即函数不会上凸。

**注：有更详细的证明或 hack 欢迎交流。**

于是考虑先三分再暴力，三分逐渐逼近区间，在最后的小区间上暴力算，有点分块的思想。

code

```cpp
#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define pre(i, j, k) for(int i = j; i >= k; --i)
#define pb push_back
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define PII pair<int, int>
#define PDD pair<double, double>
#define fi first
#define se second
#define double long double
#define int long long
#define inf 0x3fffffff
#define pi acos(-1)
using namespace std;
const double eps = 1e-9;
const int N = 1e6 + 5;
const int mod = 1e9 + 7;
int ch[N][2], dp[N], siz[N], st[N], top, a[N], b[N], dep[N], n, m, rt, tot, ret1 = inf, ret2;
int s[N], inv[N];


int dfs(int x) {
	if(!x) return 0;
	int ls = ch[x][0], rs = ch[x][1];
	return max(dfs(ls), dfs(rs)) + 1;
}

void init(int *a) {
//	a[0] = inf;
//	rep(i, 1, n) if(a[i] > a[rt]) rt = i;
	rep(i, 1, n) {
		while(top && a[st[top]] > a[i]) ch[i][0] = st[top--];
		if(top) ch[st[top]][1] = i;
		st[++top] = i;
	}
	rt = st[1];
}

int f(int x) {
	top = 0;
	rep(i, 1, n) a[i] = b[(i + x) % n + 1], ch[i][0] = ch[i][1] = 0;
	init(a);
	return dfs(rt);
}

signed main() {
	FASTIO
	cin >> n;
	rep(i, 1, n) cin >> b[i];
	
	int l = 1, r = n / 2;
	const int eps = 66;
	while(l + eps < r) {
		int p = (r - l) / 3.0,
			midl = l + p, midr = r - p;
		if(f(l + p) < f(r - p)) r = midr;
		else l = midl;
	} 
	rep(i, l, r) if(f(i) < ret1) ret1 = f(i), ret2 = (i + 1) % n;
	
	l = n / 2 + 1, r = n;
	while(l + eps < r) {
		int p = (r - l) / 3.0,
			midl = l + p, midr = r - p;
		if(f(l + p) < f(r - p)) r = midr;
		else l = midl;
	}
	rep(i, l, r) if(f(i) < ret1) ret1 = f(i), ret2 = (i + 1) % n;
	cout << ret1 << ' ' << ret2;
	return 0;
}
```

---

## 作者：Felix72 (赞：1)

考虑到加点删点时是对连续区间操作的，考虑数据结构无脑做。

因为需要改深度，所以要区间加法；因为需要考虑单点的移动，所以要染色操作；因为要知道单点的深度，所以要动态维护右链。

那么用线段树、单调栈和双端队列按照题意模拟就能通过了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
int n, a[N * 2], l[N * 2], r[N * 2], sta[N * 2], top, rt, idx;
int q[N * 2], head = 1, tail = 0;
int ans1, ans2;
struct SGT
{
	int ls, rs, data, tag;
	#define ls(x) tree[x].ls
	#define rs(x) tree[x].rs
	#define data(x) tree[x].data
	#define tag(x) tree[x].tag
}tree[N * 4];
inline void pushup(int now)
{data(now) = max(data(ls(now)), data(rs(now)));}
inline void pushdown(int now)
{
	if(tag(now))
	{
		if(ls(now)) data(ls(now)) += tag(now), tag(ls(now)) += tag(now);
		if(rs(now)) data(rs(now)) += tag(now), tag(rs(now)) += tag(now);
		tag(now) = 0;
	}
}
inline void build(int &now, int l, int r)
{
	if(!now) now = ++idx;
	if(l == r) return ;
	int mid = l + r >> 1;
	if(l <= mid) build(ls(now), l, mid);
	if(mid < r) build(rs(now), mid + 1, r);
}
inline void color(int now, int l, int r, int pos, int num)
{
	if(l == r) {data(now) = num; return ;}
	pushdown(now);
	int mid = l + r >> 1;
	if(pos <= mid) color(ls(now), l, mid, pos, num);
	if(mid < pos) color(rs(now), mid + 1, r, pos, num);
	pushup(now);
}
inline void insert(int now, int l, int r, int L, int R, int num)
{
	if(L > R) return ;
	if(L <= l && r <= R)
	{
		data(now) += num, tag(now) += num;
		return ;
	}
	pushdown(now);
	int mid = l + r >> 1;
	if(L <= mid) insert(ls(now), l, mid, L, R, num);
	if(mid < R) insert(rs(now), mid + 1, r, L, R, num);
	pushup(now);
}
inline int ask(int now, int l, int r, int L, int R)
{
	if(L > R) return 1e7;
	if(L <= l && r <= R) return data(now);
	pushdown(now);
	int mid = l + r >> 1, ans = 1e7;
	if(L <= mid) ans = min(ans, ask(ls(now), l, mid, L, R));
	if(mid < R) ans = min(ans, ask(rs(now), mid + 1, r, L, R));
	return ans;
}
inline void dfs(int now, int l, int r)
{
	if(l == r) {cout << data(now) << " "; return ;}
	pushdown(now);
	int mid = l + r >> 1;
	if(l <= mid) dfs(ls(now), l, mid);
	if(mid < r) dfs(rs(now), mid + 1, r);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i], a[i + n] = a[i];
	for(int i = 1; i <= 2 * n; ++i) l[i] = 0, r[i] = 2 * n + 1;
	for(int i = 1; i <= 2 * n; ++i)
	{
		while(top && a[sta[top]] > a[i]) r[sta[top]] = i, --top;
		sta[++top] = i;
	}
	top = 0;
	for(int i = 2 * n; i >= 1; --i)
	{
		while(top && a[sta[top]] > a[i]) l[sta[top]] = i, --top;
		sta[++top] = i;
	}
	build(rt, 1, n);
	for(int i = 1; i <= n; ++i)
	{
		int from = l[i] + 1, to = r[i] - 1;
		from = max(from, 1), to = min(to, n);
		insert(rt, 1, n, from, to, 1);
	}
	
	for(int i = 1; i <= n; ++i)
	{
		while(head <= tail && a[q[tail]] > a[i]) --tail;
		q[++tail] = i;
	}
	
	ans1 = data(rt), ans2 = 0;
	for(int i = 1; i < n; ++i)
	{
		int depth;
		if(head <= tail && a[q[head]] == a[i]) ++head;
		while(head <= tail && a[q[tail]] > a[i]) --tail;
		q[++tail] = i; depth = tail - head + 1;
		
		int from = l[i] + 1, to = r[i] - 1;
		from = max(from, i), to = min(to, n + i - 1);
		insert(rt, 1, n, from, min(to, n), -1);
		insert(rt, 1, n, 1, to - n, -1);
		
		from = l[i + n] + 1, to = r[i + n] - 1;
		from = max(from, i + 1), to = min(to, i + n);
		
		insert(rt, 1, n, from, n, 1);
		insert(rt, 1, n, max(1, from - n), to - n, 1);
		color(rt, 1, n, i, depth);
		
		if(data(rt) < ans1) ans1 = data(rt), ans2 = i;
		
	}
	cout << ans1 << " " << ans2 << '\n';
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

把 $1$ 找到。之后问题转化为：求一个序列的前缀和后缀的笛卡尔树高度。

显然，笛卡尔树的线性建树恰好能解决这个问题。

使用线段树维护节点深度变化，即可做到 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=200000+10;
int n,rev[MAXN],a[MAXN],mx[MAXN<<2],tag[MAXN<<2],len[2][MAXN];
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void push_down(int k,int l,int r) {
	mx[lson]+=tag[k],mx[rson]+=tag[k],tag[lson]+=tag[k],tag[rson]+=tag[k];
	return tag[k]=0,void();	
}
void update(int k,int l,int r,int x,int y,int v) {
	if(x<=l&&r<=y) return tag[k]+=v,mx[k]+=v,void();
	push_down(k,l,r);
	if(x<=mid) update(lson,l,mid,x,y,v);
	if(y>mid) update(rson,mid+1,r,x,y,v);
	return mx[k]=max(mx[lson],mx[rson]),void();
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i],rev[a[i]]=i;
	stack<pair<int,int>> st;
	st.push({1,n});
	int pos=rev[1];
	len[0][1]=1;
	update(1,1,n,n,n,1);
	ffor(i,1,n-1) {
		pos--;
		if(pos==0) pos=n;
		while(a[pos]<st.top().first) st.pop();
		update(1,1,n,n-i,n-i,st.size());
		update(1,1,n,n-i,st.top().second-1,1);
		st.push({a[pos],n-i});
		len[0][i+1]=mx[1];
	}
	memset(mx,0,sizeof(mx)),memset(tag,0,sizeof(tag));
	pos=rev[1],len[1][1]=1;
	while(!st.empty()) st.pop();
	st.push({1,1});
	update(1,1,n,1,1,1);
	ffor(i,1,n-1) {
		pos++;
		if(pos==n+1) pos=1;
		while(a[pos]<st.top().first) st.pop();
		update(1,1,n,i+1,i+1,st.size());
		update(1,1,n,st.top().second+1,i+1,1);
		st.push({a[pos],i+1});
		len[1][i+1]=mx[1];
	}
	int ans=0x3f3f3f3f;
	ffor(i,1,n) ans=min(ans,max(len[0][i],len[1][n-i+1]));
	cout<<ans<<' ';
	ffor(i,1,n) if(max(len[0][i],len[1][n-i+1])==ans) {
		int dis=rev[1]-i;
		if(dis<0) dis+=n;
		cout<<dis;
		return 0;	
	}
	return 0;
}
```

---

