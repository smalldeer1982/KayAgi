# [ABC174F] Range Set Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc174/tasks/abc174_f

$ N $ 個の色の付いた玉が左右一列に並んでおり、左から $ i $ 番目の玉の色は $ c_i $ です。

クエリが $ Q $ 個与えられます。$ i $ 番目のクエリでは、左から $ l_i $ 番目から $ r_i $ 番目までにある玉の色の種類数を答えてください。

## 说明/提示

### 制約

- $ 1\leq\ N,Q\ \leq\ 5\ \times\ 10^5 $
- $ 1\leq\ c_i\ \leq\ N $
- $ 1\leq\ l_i\ \leq\ r_i\ \leq\ N $
- 入力はすべて整数である。

### Sample Explanation 1

\- $ 1,2,3 $ 番目の玉の色は $ 1,2,1 $ で、色 $ 1,2 $ の $ 2 $ 種類があります。 - $ 2,3,4 $ 番目の玉の色は $ 2,1,3 $ で、色 $ 1,2,3 $ の $ 3 $ 種類があります。 - $ 3 $ 番目の玉の色は $ 1 $ で、色 $ 1 $ の $ 1 $ 種類があります。

## 样例 #1

### 输入

```
4 3
1 2 1 3
1 3
2 4
3 3```

### 输出

```
2
3
1```

## 样例 #2

### 输入

```
10 10
2 5 6 5 2 1 7 9 7 2
5 5
2 4
6 7
2 2
7 8
7 9
1 8
6 9
8 10
6 8```

### 输出

```
1
2
2
1
2
2
6
3
3
3```

# 题解

## 作者：August_Light (赞：7)

# [ABC174F] Range Set Query 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc174_f)

upd 2024/1/13: 重写了整篇题解。

因为本题要求与 P1972 几乎一模一样，所以直接按 P1972 来讲。代码也是放 P1972 的。注意两题输入格式与数据范围有所不同。

## 题意简述

省流：**静态区间数颜色**。

有 $n$ 个数 $a_1, a_2 \dots a_n$。有 $m$ 个询问 $l,r$，求从 $l$ 到 $r$ 有多少个不同的元素。

$1 \le n,m,a_i \le 10^6$。

### 三倍经验

[P1972 [SDOI2009] HH的项链](https://www.luogu.com.cn/problem/P1972)

[DQUERY - D-query](https://www.luogu.com.cn/problem/SP3267)

## 前置知识

- 树状数组（离线）
- 可持久化线段树（在线）

## 解法

对于每个位置 $i$，预处理出 $pre_i$ 表示 $i$ 左边离 $i$ 最近的满足 $a_i=a_j$ 的下标 $j$。

```cpp
    for (int i = 1; i <= n; i++) {
        pre[i] = lst[a[i]];
        lst[a[i]] = i;
    }
```

然后查询区间中的不同数，我们可以只把每个数在区间中最后一次出现时统计进去。

扫一遍数组，扫到每个右端点的时候，维护每个左端点对应的答案。

具体做法：

数组 $tr_x$ 表示 **在** $[1, x]$ **中每个位置出现的数是否是最后一次出现**，$tr_x$ 每个位置的取值为 $0$ 或 $1$。

举例：

| $a$    | $\{1,1,4,5,1,4\}$ |
|   :-   |        :-         |
| $tr_1$ | $\{1\}$           |
| $tr_2$ | $\{0,1\}$         |
| $tr_3$ | $\{0,1,1\}$       |
| $tr_4$ | $\{0,1,1,1\}$     |
| $tr_5$ | $\{0,0,1,1,1\}$   |
| $tr_6$ | $\{0,0,0,1,1,1\}$ |

那么询问就变为 $tr_r$ 的区间 $[l, r]$ 的和。

### 做法 1：离线树状数组

但是其实不需要维护那么多 $tr$。

把询问**离线**，按 $r$ 排序。用某种数据结构维护一个 $tr$，扫描序列 $a$，每当扫到一个 $r$ 就直接用当时的 $tr$ 统计答案。

单点修改、区间（前缀）查询，由此想到树状数组。

```cpp
    // tr 为一个树状数组
    int ptr = 1;
    for (int i = 1; i <= m; i++) {
        while (ptr <= q[i].r) { // q 为离线下来的询问，用结构体存储
            if (pre[ptr])
                tr.add(pre[ptr], -1); // 清除上一次出现的位置
            tr.add(ptr, 1);           // 只保留最后出现的位置
            ptr++;
        }
        ans[q[i].id] = tr.query(q[i].r) - tr.query(q[i].l - 1); // 前缀和求区间和
    }
```

时间复杂度 $O(m \log m + m \log n)$。空间复杂度 $\Theta(n + m + W)$。$W$ 为值域。

### 做法 2：在线可持久化线段树

我就是要维护那么多 $tr$！

使用可持久化线段树即可。具体做法同做法 1。

时间复杂度 $O(n \log n) - O(\log n)$。空间复杂度 $O(n + m \log n + W)$。$W$ 为值域。

**优化常数的做法**：

原本做法：
- 修改：在 $pre_i$ 处 -1，在 $i$ 处 +1。
- 查询：在 $r$ 对应的线段树上查询 $[l,r]$。

小常数做法：
- 修改：在 $pre_i$ 处 +1。
- 查询：在第 $r$ 棵树查询 $[0,l-1]$，在第 $l-1$ 棵树查询 $[0,l-1]$。

这样可以减半可持久化线段树的空间，只需要开到 $21n$。

亲测这样使时间从 17.48s 降到 9.62s。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 省略快读快写的实现

const int MAXN = 5e5 + 100;
const int MAXM = 5e5 + 100;
const int MAXW = 5e5 + 100; // 值域

int n, m;
int a[MAXN];

int lowbit(int x) {
    return x & -x;
}
struct Fenwick {
    ll c[MAXN];
    ll query(int x) {
        ll ret = 0;
        for (int i = x; i; i -= lowbit(i))
            ret += c[i];
        return ret;
    }
    void add(int x, ll k) {
        for (int i = x; i <= n; i += lowbit(i))
            c[i] += k;
    }
};

struct Q {
    int l, r;
    int id;
} q[MAXM];
int ans[MAXM];

int lst[MAXW]; // lst[a[i]] = a[i] 上次出现的位置，默认为 0
int pre[MAXN]; // pre[i] = i 左边离 i 最近的满足 a[i] == a[j] 的 j
Fenwick tr;    // 目前为止每个位置出现的数是否是最后一次出现

int main() {
    n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    m = read();
    for (int i = 1; i <= m; i++) {
        q[i].l = read(); q[i].r = read();
        q[i].id = i;
    }
    sort(q + 1, q + m + 1, [](Q x, Q y) {
        return x.r < y.r;
    });

    for (int i = 1; i <= n; i++) {
        pre[i] = lst[a[i]];
        lst[a[i]] = i;
    }

    int ptr = 1;
    for (int i = 1; i <= m; i++) {
        while (ptr <= q[i].r) {
            if (pre[ptr])
                tr.add(pre[ptr], -1); // 清除上一次出现的位置
            tr.add(ptr, 1);           // 只保留最后出现的位置
            ptr++;
        }
        ans[q[i].id] = tr.query(q[i].r) - tr.query(q[i].l - 1); // 前缀和求区间和
    }

    for (int i = 1; i <= m; i++)
        write(ans[i], '\n');
    return 0;
}
```

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 省略快读快写的实现

const int MAXN = 1e6 + 5;
const int MAXW = 1e6 + 5;

int n, m;
int a[MAXN];

struct HJT {
    #define M ((L + R) >> 1)
    #define lson(u) (t[u].lson)
    #define rson(u) (t[u].rson)
    struct Node {
        int lson, rson;
        int val;
    } t[MAXN * 21];
    int tot = 0;
    int rt[MAXN];
    void pushup(int u) {
        t[u].val = t[lson(u)].val + t[rson(u)].val;
    }
    void insert(int &u, int pre, int L, int R, int x, ll v) {
        u = ++tot;
        lson(u) = lson(pre);
        rson(u) = rson(pre);
        t[u].val = t[pre].val;
        if (L == R) {
            t[u].val += v;
            return;
        }
        if (x <= M)
            insert(lson(u), lson(pre), L, M, x, v);
        else
            insert(rson(u), rson(pre), M+1, R, x, v);
        pushup(u);
    }
    int query(int u, int L, int R, int l, int r) {
        if (!u) return 0;
        if (R < l || r < L) return 0;
        if (l <= L && R <= r)
            return t[u].val;
        if (r <= M) return query(lson(u), L, M, l, r);
        if (l > M) return query(rson(u), M+1, R, l, r);
        return query(lson(u), L, M, l, r) + query(rson(u), M+1, R, l, r);
    }
};

HJT tr;

int lst[MAXW];
int pre[MAXN];

int main() { ios::sync_with_stdio(0); cin.tie(0);
    n = read();
    tr.rt[0] = ++tr.tot;
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        pre[i] = lst[a[i]]; lst[a[i]] = i;
    }
    for (int i = 1; i <= n; i++)
        tr.insert(tr.rt[i], tr.rt[i-1], 0, n, pre[i], 1);

    m = read(); while (m--) {
        int l = read(), r = read();
        write(tr.query(tr.rt[r], 0, n, 0, l-1) - tr.query(tr.rt[l-1], 0, n, 0, l-1), '\n');
    }
    return 0;
}
```

---

## 作者：Usada_Pekora (赞：4)

题意：静态，问区间不同值个数。

我们可以直接暴力去做，从 $l\sim r$ 判断这个数是不是第一次出现，于是每个区间内只有第一个数会产生贡献。所以维护一个 $pre_i$ 表示上一个与 $a_i$ 相同的数的下标，没有就是 $0$，于是我们发现只需要统计所有 $pre_i\lt l$ 的个数就好了，结合上面的过程是容易理解的。

树状数组：拆分成 $[1,r]$ 和 $[1,l)$ 两个询问然后作差，发现后面这个东西的答案是 $l-1$，没必要额外算，然后对所有的询问按 $r$ 离线，从小到大加入每个 $pre_i$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int c[N], pre[N], lst[N], ans[N], n, m, idx;
struct Q {
	int r, x, id;
} q[N];
inline int read() {
	int x = 0;
	char ch = getchar();
	while (!isdigit(ch))
		ch = getchar();
	while (isdigit(ch))
		x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	return x;
}
inline void modify(int x) {
	while (x <= n) {
		c[x]++;
		x += (x & -x);
	}
}
inline int query(int x) {
	int res = 0;
	while (x) {
		res += c[x];
		x -= (x & -x);
	}
	return res;
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) {
		int x = read();
		pre[i] = lst[x] + 1;
		lst[x] = i;
	}
	for (int i = 1; i <= m; i++) {
		int l = read(), r = read();
		q[i] = {r, l, i};
	}
	int j = 1;
	sort(q + 1, q + m + 1, [&](const Q &lhs, const Q &rhs) -> bool { return lhs.r < rhs.r; });
	for (int i = 1; i <= m; i++) {
		while (j <= q[i].r)
			modify(pre[j++]);
		ans[q[i].id] += query(q[i].x) - (q[i].x - 1);
	}
	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}
```

主席树：直接插入 $pre_i$，然后对 $r,l-1$ 这两棵树作差即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int rt[N], ls[N * 30], rs[N * 30], sum[N * 30], pre[N], n, m, idx;
inline int modify(int pre, int l, int r, int x) {
	int p = ++idx;
	ls[p] = ls[pre], rs[p] = rs[pre], sum[p] = sum[pre] + 1;
	if (l == r)
		return p;
	int mid = (l + r) >> 1;
	if (x <= mid)
		ls[p] = modify(ls[pre], l, mid, x);
	else
		rs[p] = modify(rs[pre], mid + 1, r, x);
	return p;
}
inline int query(int u, int v, int l, int r, int x) {
	if (r <= x)
		return sum[v] - sum[u];
	int mid = (l + r) >> 1, res = 0;
	res = query(ls[u], ls[v], l, mid, x);
	if (x > mid)
		res += query(rs[u], rs[v], mid + 1, r, x);
	return res;
}
inline int read() {
	int x = 0;
	char ch = getchar();
	while (!isdigit(ch))
		ch = getchar();
	while (isdigit(ch))
		x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	return x;
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) {
		int x = read();
		rt[i] = modify(rt[i - 1], 0, n - 1, pre[x]);
		pre[x] = i;
	}
	for (int i = 1; i <= m; i++) {
		int l = read(), r = read();
		printf("%d\n", query(rt[l - 1], rt[r], 0, n - 1, l - 1));
	}
	return 0;
}
```

最后就是我们一开始说的暴力，可以利用莫队直接优化。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
inline int read() {
	int x = 0;
	char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return x;
}
int n, m, a[N], bel[N], cnt[N], res, ans[N];
struct queries {
	int l, r, id;
	queries() {}
	bool operator < (const queries & x) const {
		if (bel[l] ^ bel[x.l]) return bel[l] < bel[x.l];
		else if (bel[l] & 1) return r < x.r;
		return r > x.r;
	}
} q[N];
inline void add(int x) {
	if (cnt[a[x]] == 0) res++;
	cnt[a[x]]++;
}
inline void del(int x) {
	cnt[a[x]]--;
	if (cnt[a[x]] == 0) res--;
}
int main() {
	n = read(), m = read();
	const int sq = sqrt(n);
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) bel[i] = (i - 1) / sq + 1;
	for (int i = 1; i <= m; i++) {
		q[i].l = read(), q[i].r = read();
		q[i].id = i;
	}
	sort(q + 1, q + m + 1);
	int l = 1, r = 0;
	for (int i = 1; i <= m; i++) {
		while (l < q[i].l) del(l++);
		while (l > q[i].l) add(--l);
		while (r < q[i].r) add(++r);
		while (r > q[i].r) del(r--);
		ans[q[i].id] = res;
	}
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

[HH的项链](https://www.luogu.com.cn/problem/P1972)弱化版。

我们可以使用普通莫队来做这道题。我们定义 $\mathit{cnt}_{i}$ 表示在当前区间内数字 $i$ 出现的个数。在进行更新范围的时候，我们只需要判断一下操作之后（前） $\mathit{cnt}_{i}$ 是否等于 $0$，如果等于 $0$，表明这个数字在操作之后（前）没有出现过，则更新答案即可。

注：对于这道题，没有修改与什么别的东西，所以我们把块长定义为 $\sqrt{n}$ 即可，复杂度 $O(q\sqrt{n})$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e6+10;
int ans;
int n,m;
int c[N],cnt[N];
struct node{
	int l,r,id;
}a[N];
int b[N];
bool cmp(node a,node b){
	int len=sqrt(n);
	if(a.l/len!=b.l/len){
		return a.l<b.l;
	}
	else{
		return a.r<b.r;
	}
}
void mody(){
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(l>a[i].l){
			ans+=!(cnt[c[--l]]++);//优化，不需要再写个add/del函数（再套函数会TLE） 
		}
		while(r<a[i].r){
			ans+=!(cnt[c[++r]]++);
		}
		while(l<a[i].l){
			ans-=!(--cnt[c[l++]]);
		}
		while(r>a[i].r){
			ans-=!(--cnt[c[r--]]);
		}
		b[a[i].id]=ans;//更新答案 
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>c[i];
	}
	for(int i=1;i<=m;i++){
		cin>>a[i].l>>a[i].r;
		a[i].id=i;
	}
	sort(a+1,a+m+1,cmp);
	mody();
	for(int i=1;i<=m;i++){
		cout<<b[i]<<"\n";
	}
	return 0;
}
```


---

## 作者：AlicX (赞：0)

~~别说我水题解。~~

### Solution 

题意非常明了了，在此不在赘述。

较流行的有两种做法：

1. 找出每一个数前面的第一个与其相同的数的位置，再用树状数组统计。

2. 使用莫队，那么这道题瞬间被秒成了板子。

莫队的思想就是知道了 $(l,r)$ 区间的答案，就能在 $O(1)$ 的时间更新出 $(l+1,r)$，$(l,r+1)$，$(l-1,r)$，$(l,r-1)$ 的答案，只需要利用分块的思想排序后，时间复杂度就成为了 $O(n \sqrt{n})$ 级别的了。  

那么这道题进行更新是只需要判断此数是否是第一次出现或者被删除就可以了。

~~我是不是废话太多了。~~

### AC Code

```cpp
// Celestial Cyan
// Luogu uid : 706523
// Luogu : https://www.luogu.com.cn/problem/AT_abc174_f
// CF : 
// AT : https://atcoder.jp/contests/abc174/tasks/abc174_f
// FTOJ :
// Contest : AtCoder Beginner Contest 174 
// Cnblogs : 
// Memory Limit: 1 GB
// Time Limit: 2000 ms
// 2023/ /

#include<bits/stdc++.h>
//#define int long long
#define x first
#define y second
#define il inline
#define db double
#define low(x) x&-x
#define ls(x) x<<1
#define rs(x) x<<1|1
#define pb(x) push_back(x)
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
#define debug puts("-------")
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII;
const int N=5e5+10,INF=1e9+7;
int n,m;
int ans[N]; 
int sum=0,len; 
int a[N],cnt[N]; 
struct Mind{ 
	int l,r,id; 
	il bool operator<(Mind &Cyan)const{ 
		if(l/len!=Cyan.l/len) return l<Cyan.l;
		return (l/len)&1?r<Cyan.r:r>Cyan.r; 
	} 
}q[N]; 
il int read(){
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
il void add(int x){
	cnt[x]++;
	sum+=(cnt[x]==1); 
} 
il void del(int x){
	cnt[x]--;
	sum-=(!cnt[x]); 
}
signed main(){ 
	n=read(),m=read(); len=sqrt(n); 
	for(int i=1;i<=n;i++) a[i]=read(); 
	for(int i=1;i<=m;i++) q[i].l=read(),q[i].r=read(),q[i].id=i;
	sort(q+1,q+m+1); int l=1,r=0; 
	for(int i=1;i<=m;i++){ 
		while(l>q[i].l) add(a[--l]); 
		while(r<q[i].r) add(a[++r]); 
		while(l<q[i].l) del(a[l++]); 
		while(r>q[i].r) del(a[r--]); 
		ans[q[i].id]=sum; 
	} for(int i=1;i<=m;i++) printf("%d\n",ans[i]);  
	return 0;
} /* */ 
```


---

## 作者：syxmz (赞：0)

### 1 题目链接
[传送门](https://atcoder.jp/contests/abc174/tasks/abc174_f?lang=en)
### 2 题目大意
问一个序列中 $[l,r]$ 中有多少个不同的数。
### 3 解法分析
如果没记错的话是在 2023GDKOI 讲解过的。

提供一个相对典型的思路。

将询问离线下来。

从左到右遍历数组，用树状数组存每种颜色出现的最右下标。

对于询问 $(l,r)$，在遍历到 $r$ 位置时，该询问的答案就是树状数组中 $[l,r]$ 的和，直接查询即可。
### 4 AC Code
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); ++(i))
#define fep(i, a, b) for (int (i) = (a); (i) < (b); ++(i))
#define int long long
#define N 500007
using namespace std;

int n, q;
int c[N], l[N], r[N];
int a[N], b[N], ans[N];
vector <pair <int, int> > x[N];

void add(int x,int v) {
	for (int i = x; i <= n; i += i & -i)
		b[i] += v;
}

int sum(int x) {
	int v = 0;
	for (int i = x; i > 0; i -= i & -i)
		v += b[i];
	return v;
}

signed main() {
	scanf("%lld%lld", &n, &q);
	rep(i, 1, n)
		scanf("%lld", &c[i]);
	rep(i, 1, q) {
		scanf("%lld%lld", &l[i], &r[i]);
		x[r[i]].push_back({l[i], i});
	}
	rep(i, 1, n) {
		if (a[c[i]])
			add(a[c[i]], -1);
		a[c[i]] = i;
		add(i, 1);
		for (pair <int, int> it : x[i])
			ans[it.second] = sum(i) - sum(it.first - 1);
	}
	rep(i, 1, q)
		printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

三倍经验：[SP3267](https://www.luogu.com.cn/problem/SP3267)，[P1972](https://www.luogu.com.cn/problem/P1972)。

本题有多种解法：莫队，主席树，线段树，树状数组，可以去翻上面那两题的题解，不再详述。这里只介绍一种做法。

首先可以先把所有询问离线下来。

发现对于所有询问区间 $ [l,r] $，实际上只需要保留最右边的数字即可，不影响答案。因此把所有询问按 $ r $ 升序排序，然后遍历 $ i $，当前面的位置没有 $ i $ 时将前面的区间和 $ +1 $，否则区间和 $ +1 $ 后删掉前面一个，维护一个链表即可。

于是一个询问的答案即为 $ sum_r-sum_{l-1} $，只需要实现一个单点加区间查询的数据结构，树状数组即可，这里用 LCT 实现，时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。虽然常数巨大但貌似还是比莫队快一点。这份代码可以通过这题和第一个三倍经验，第二个要写正常的树状数组。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int c[maxn],tag[maxn],n;
struct Splay
{
    int ch[maxn][2],fa[maxn],siz[maxn],val[maxn],sum[maxn],add[maxn],mul[maxn],rev[maxn];
    void clear(int x)
    {
        ch[x][0]=ch[x][1]=fa[x]=siz[x]=val[x]=sum[x]=add[x]=rev[x]=0;
        mul[x]=1;
    }
    int getch(int x)
    {
        return (ch[fa[x]][1]==x);
    }
    int isroot(int x)
    {
        clear(0);
        return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    void maintain(int x)
    {
        clear(0);
        siz[x]=(siz[ch[x][0]]+1+siz[ch[x][1]]);
        sum[x]=(sum[ch[x][0]]+val[x]+sum[ch[x][1]]);
    }
    void pushdown(int x)
    {
        clear(0);
        if(mul[x]!=1)
        {
            if(ch[x][0])
            mul[ch[x][0]]=(mul[x]*mul[ch[x][0]]),val[ch[x][0]]=(val[ch[x][0]]*mul[x]),sum[ch[x][0]]=(sum[ch[x][0]]*mul[x]),add[ch[x][0]]=(add[ch[x][0]]*mul[x]);
            if(ch[x][1])
            mul[ch[x][1]]=(mul[x]*mul[ch[x][1]]),val[ch[x][1]]=(val[ch[x][1]]*mul[x]),sum[ch[x][1]]=(sum[ch[x][1]]*mul[x]),add[ch[x][1]]=(add[ch[x][1]]*mul[x]);
            mul[x]=1;
        }
        if(add[x])
        {
            if(ch[x][0])
            add[ch[x][0]]=(add[ch[x][0]]+add[x]),val[ch[x][0]]=(val[ch[x][0]]+add[x]),sum[ch[x][0]]=(sum[ch[x][0]]+add[x]*siz[ch[x][0]]);
            if(ch[x][1])
            add[ch[x][1]]=(add[ch[x][1]]+add[x]),val[ch[x][1]]=(val[ch[x][1]]+add[x]),sum[ch[x][1]]=(sum[ch[x][1]]+add[x]*siz[ch[x][1]]);
            add[x]=0;
        }
        if(rev[x])
        {
            if(ch[x][0])
            rev[ch[x][0]]^=1,swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
            if(ch[x][1])
            rev[ch[x][1]]^=1,swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
            rev[x]=0;
        }
    }
    void update(int x)
    {
        if(!isroot(x))
        update(fa[x]);
        pushdown(x);
    }
    void rotate(int x)
    {
        int y=fa[x],z=fa[y],chx=getch(x),chy=getch(y);
        fa[x]=z;
        if(!isroot(y))
        ch[z][chy]=x;
        ch[y][chx]=ch[x][chx^1];
        fa[ch[x][chx^1]]=y;
        ch[x][chx^1]=y;
        fa[y]=x;
        maintain(y);
        maintain(x);
        maintain(z);
    }
    void splay(int x)
    {
        update(x);
        for(int f=fa[x];f=fa[x],!isroot(x);rotate(x))
        if(!isroot(f))
        rotate(getch(x)==getch(f)?f:x);
    }
    void access(int x)
    {
        for(int f=0;x;f=x,x=fa[x])
        splay(x),ch[x][1]=f,maintain(x);
    }
    void makeroot(int x)
    {
        access(x);
        splay(x);
        swap(ch[x][0],ch[x][1]);
        rev[x]^=1;
    }
    int find(int x)
    {
        access(x);
        splay(x);
        while(ch[x][0])
        x=ch[x][0];
        splay(x);
        return x;
    }//前面都是LCT板子部分
    void added(int u,int c)
    {
        int v=u;
        makeroot(u), access(v), splay(v);
      val[u] = (val[v] + c) ;
      sum[v] = (sum[v] + siz[v] * c ) ;
      add[v] = (add[v] + c) ;
        return;
    }//单点加（相当于对区间[u,u]加）
    int query(int u)
    {
        if(u==0)
            return 0;
        int v=1;
        makeroot(u), access(v), splay(v);
        return sum[v];
    }//区间查询（注意特判u=0的情况，在转化前缀和时1-1=0会出问题）
    void link(int u,int v)
    {
    if (find(u) != find(v)) 
    makeroot(u), fa[u] = v;
    }
}st;
struct seele
{
	int L,R,ad; 
}a[maxn];
int sum[maxn],ans[maxn],nxt[maxn],head[maxn],m,mx,num[maxn];
inline bool cmp(seele x1,seele x2) 
{ 
	return x1.L==x2.L ? x1.R<x2.R : x1.L<x2.L;
}
signed main() 
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) 
		num[i]=read();
	for(int i=n;i>=1;i--) 
	{
		nxt[i]=head[num[i]];
		head[num[i]]=i;
		mx=max(mx,num[i]);
	}
	mx=max(mx,maxn/2);
        for(int i=1;i<=mx+1;i++)
            st.clear(i),st.val[i]=0,st.maintain(i),st.splay(i);
        for(int i=0;i<=mx+1;++i)
            st.sum[i]=0;
        for(int i=1;i<mx+1;i++)
            st.link(i,i+1);
	for(int i=1;i<=m;i++) 
	{
		a[i].L=read();
		a[i].R=read();
		a[i].ad=i; 
	}
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=mx;i++) 
		if(head[i]) 
		st.added(head[i],1); 
	int now=1;
	for(int i=1;i<=m;i++) 
	{
		while(now<a[i].L) 
		{
			if(nxt[now])
			st.added(nxt[now],1);
			now++;
		}
		ans[a[i].ad]=st.query(a[i].R)-st.query(a[i].L-1); 
	}
	for(int i=1;i<=m;i++)
	printf("%d\n",ans[i]);
}
```


---

