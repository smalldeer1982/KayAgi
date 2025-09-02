# 「VUSC」Card Tricks

## 题目背景

**upd 2023.1.17 数据已加强。** 

**upd 2023.10.18 空间限制调整为 100 MiB。**

Bessie 正在玩一场卡牌游戏！

这个游戏有一些~~神秘的~~规则。Bessie 需要用一些编程技巧，加快计算。

## 题目描述

牌堆可以看成一个长度为 $N$ 的数列，下标为 $i$ 的位置值为 $a_i$。$(1\le i\le N)$

有 $Q$ 次操作，每次操作给定 $l_i,r_i,v_i$，$\forall l_i\le j \le r_i,a_j\gets a_j \lor v_i$。

其中 $\lor$ 表示按位或操作，即 C++ 中的 `|`。

对于 $i=1,2,\dots,N$，求出在哪一次操作后，$a_i$ **首次严格大于** $P$，其中 $P$ 为一给定常数。

数据保证在初始情况下，$P\ge\max\{a_i\}$。

## 说明/提示

#### 样例 #1 解释

第一次操作后的数列为 $1,2,3,4,5$。

第二次操作后的数列为 $11,2,3,4,5$。

第三次操作后的数列为 $11,6,7,4,5$。

……

最终的数列为 $11,14,15,4,23$。

---

#### 数据范围
全部数据满足：$1\le N,Q \le 10^6$，$1\le l_i\le r_i \le N$，$1\le a_i,v_i,P\le 10^9$。

测试点 $1\sim2$ 另满足 $1\le N,Q\le 10^3$。

测试点 $3$ 另满足 $l_i=r_i$。

测试点 $4$ 另满足 $l_i=1,r_i=N$。

测试点 $5\sim10$ 无额外限制。

**本题数据规模较大，请注意常数优化。**

## 样例 #1

### 输入

```
5 7 10
1 2 3 4 5
1 1 1
1 1 10
2 5 4
2 3 8
5 5 2
5 5 1
5 5 16```

### 输出

```
2 4 4 -1 7```

## 样例 #2

### 输入

```
10 10 86
26 27 33 1 21 31 9 22 17 14
6 10 76
5 8 85
4 5 89
3 9 87
2 9 100
7 10 83
1 6 75
1 4 66
3 10 68
3 4 72```

### 输出

```
7 5 4 3 3 1 2 1 1 6```

# 题解

## 作者：Little09 (赞：9)

考虑到每个数一定不会变小，即随时间单调不降。我们考虑对每个数算答案：找出所有该数涉及的操作，放到时间轴上，在时间轴上二分一下第一个超过 $P$ 的时间。

具体地，我们可以用线段树实现这个事情。线段树第 $i$ 个位置放的是第 $i$ 次操作 or 上的值，如果第 $i$ 次操作与该数无关，就放上 $0$。对于每个数在线段树上二分一下即可。由于第 $i$ 的操作区间是 $[l_i,r_i]$，我们只要在 $l_i$ 个数的时候加入这个操作，再第 $r_i+1$ 个数的时候删除。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define pii pair<int,int>
#define fi first
#define se second
const int N=1e6+5;
int n,q,p;
int a[N],b[N],s[N*4];
int t[N*2],h[N],val[N*2],nxt[N],cnt;
inline void add(int x,int y,int z)
{
	t[++cnt]=y,val[cnt]=z;
	nxt[cnt]=h[x],h[x]=cnt;
}

void update(int u,int l,int r,int x,int y)
{
	if (l==r)
	{
		s[u]=y;
		return;
	}
	int mid=(l+r)>>1;
	if (x<=mid) update(u*2,l,mid,x,y);
	else update(u*2+1,mid+1,r,x,y);
	s[u]=s[u*2]|s[u*2+1];
}
int ask(int u,int l,int r,int x)
{
	if (l==r)
	{
		if ((x|s[u])<=p) return -1;
		return l; 
	}
	int mid=(l+r)>>1;
	if ((x|s[u*2])>p) return ask(u*2,l,mid,x);
	return ask(u*2+1,mid+1,r,x|s[u*2]);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> q >> p;
	for (int i=1;i<=n;i++) cin >> a[i];
	for (int i=1;i<=q;i++) 
	{
		int l,r,x;
		cin >> l >> r >> x;
		b[i]=x;
		add(l,i,b[i]),add(r+1,i,0);
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=h[i];j;j=nxt[j]) update(1,1,q,t[j],val[j]);
		cout << ask(1,1,q,a[i]) << " ";
	}
	return 0;
}

```

使用 zkw 线段树可以获得更小的常数，代码可以私信 5ab。


---

## 作者：5ab_juruo (赞：4)

一个显然的事实是，每个数的每一位只会被修改至多一次。所以如果能快速找到第一个需要修改的位，则可以直接暴力修改，修改的时候维护 $a_i$ 和 $P$ 的关系即可。

快速查找的过程可以并查集维护，每次将一个位置设为 $1$ 后将左右连续 $1$ 段合并，这样直接做的空间复杂度是 $\mathcal{O}(n\log a_i)$ 的，无法通过。

考虑离线所有询问从高位向低位处理，对于第 $i$ 位，求出每个数把第 $i$ 位操作至 $1$ 的第一次操作的编号。对于 $P$ 的当前位，分类讨论：

- 若 $P$ 的第 $i$ 位为 $1$：

对于所有第 $i$ 位无法操作至 $1$ 的数，打上不能继续计算答案的标记。否则，维护 $q_j$ 为第 $j$ 个数至少需要多少次操作才能使第 $i$ 位及以后的所有位 $\ge P$，对这个数取 $\max$。

- 若 $P$ 的第 $i$ 位为 $0$：

若第 $j$ 个数在操作 $p_j$ 可以让第 $i$ 位赋成 $1$，则用 $\max(p_j,q_j)$ 更新 $j$ 处最终的答案。

由于题目要求 $a_i$ 要严格大于 $P$，所以最终无须计算 $a_i=P$ 的情况。

时间复杂度 $\mathcal{O}(n\alpha(n)\log a_i)$，实现中并查集是 $O(\log n)$ 的，但常数更优秀一点。

```cpp
const int max_n = 1000000, max_q = 1000000, max_lga = 30;

struct qry
{
	int l, r, v;
}
qr[max_q];

struct dsu
{
	int dsu[max_n + 1];
	void init(int n)
	{
		iota(dsu, dsu + n + 1, 0);
	}
	int fnd(int x) { return x == dsu[x] ? x : (dsu[x] = fnd(dsu[x])); }
	inline int del(int x)
	{
		return dsu[x] = fnd(x + 1);
	}
}
d;
int a[max_n], ans[max_n], pmx[max_n], curv[max_n];
bool ok[max_n];

inline void chmax(int& _a, int _b) { if (_a < _b) _a = _b; }
inline void chmin(int& _a, int _b) { if (_a > _b) _a = _b; }

signed main()
{
	int n, q, p;
    
	read(n), read(q), read(p);
	for (int i = 0; i < n; i++)
		read(a[i]);
	for (int i = 0; i < q; i++)
	{
		auto &[l, r, v] = qr[i];
		read(l), read(r), read(v);
		l--, r--;
	}
	
	fill(ans, ans + n, q + 1);
	fill(ok, ok + n, true);
	
	for (int i = max_lga - 1; i >= 0; i--)
	{
		d.init(n);
		fill(curv, curv + n, -1);
		
		for (int j = 0; j < n; j++)
			if ((a[j] >> i) & 1)
				curv[j] = 0;
		
		for (int j = 0; j < q; j++)
		{
			auto [l, r, v] = qr[j];
			if ((v >> i) & 1)
			{
				for (int x = d.fnd(l); x <= r; x = d.del(x))
				{
					if (curv[x] == -1)
						curv[x] = j + 1;
				}
			}
		}
		
		if ((p >> i) & 1)
		{
			for (int j = 0; j < n; j++)
			{
				if (curv[j] == -1)
					ok[j] = false;
				else if (ok[j])
					chmax(pmx[j], curv[j]);
			}
		}
		else
		{
			for (int j = 0; j < n; j++)
			{
				if (curv[j] != -1 && ok[j])
					chmin(ans[j], max(curv[j], pmx[j]));
			}
		}
	}
	
	for (int i = 0; i < n; i++)
		printf("%d%c", (ans[i] == q + 1 ? -1 : ans[i]), " \n"[i == n - 1]);
	
	return 0;
}
```

---

## 作者：zesqwq (赞：3)

# 【模板】不撤销整体二分 / P8955 「VUSC」Card Tricks 题解

~~ds 真好玩~~

你考虑整体二分，区间或上一个值是很好维护的操作，但是我们发现整体二分中有一个操作叫做撤销最后的操作，我认为撤销操作并不方便维护，于是我们引入一个新的技巧，叫做 不撤销的整体二分。

整体二分实际上是一个线段树的结构，一般的整体二分都是从根节点向下递归判定每个询问的答案在左区间还是右区间，然后递归解决，类似 $\text{dfs}$，但是我们可以用一个不太一样的做法：从上至下对每一层进行判定答案在左区间还是右区间。

具体的，假设我们二分答案 $\in [1, 8]$，则过程如下：

- 先扫描根节点 $[1, 8]$ 把存的询问判定是否符合要求并将符合的下放到 $[1, 4]$，不符合的放到 $[5, 8]$；
- 再扫描第二层节点 $[1, 4]$，$[5, 8]$，并判定将其存储的询问需要放入左孩子还是右孩子；
- 再扫描第三层节点 $[1, 2]$，$[3, 4]$，$[5, 6]$，$[7, 8]$ ......；
- 再扫描第四层节点，得出每个询问的答案。

也就是我们对线段树的每一层节点进行遍历，然后把当前节点的询问放入左儿子或右儿子，遍历完一层之后重置回初始状态。

你发现因为你是从左到右遍历的，因此你可以规避掉撤销这个操作。

或许可以叫它整体二分二次离线？

在实际的实现中，你甚至不需要把这个线段树建立出来，只需要进行 $\lceil \log n \rceil$ 次二分，每次记录每个询问的答案范围，然后将询问按照左或右端点排序，扫描询问，挨个判定使答案范围缩小一半即可。

然后这道题直接使用这个技巧就可以解决了。卡常就自己试试吧，很快乐的。

时间复杂度 $O(n \log n \log V)$，空间复杂度 $O(n)$。

代码十分简短：

```cpp
int n, m, p;
int a[N], lzy[N << 1], w[N << 1];
struct OP {
	int l, r, v;
} q[N];
struct Answer {
	int l, r, id;
	inline bool operator<(const Answer &b) const { return r < b.r; }
} ans[N];
int h[30], cnt = 0;
inline void maketag(int u, int v) { w[u] |= v, lzy[u] |= v; }
inline void pushdown(int u, int M) {
	if (lzy[u]) maketag(M << 1, lzy[u]), maketag(M << 1 | 1, lzy[u]), lzy[u] = 0;
}
void update(int u, int L, int R, int l, int r, int v) {
	if (L > r || R < l || ((w[u] | v) == w[u])) return;
	if (L >= l && R <= r) return maketag(u, v);
	int M = L + R >> 1;
	pushdown(u, M);
	update(M << 1, L, M, l, r, v), update(M << 1 | 1, M + 1, R, l, r, v);
	w[u] = w[M << 1] & w[M << 1 | 1];
}
int query(int u, int L, int R, int x) {
	if (L == R) return w[u];
	int M = L + R >> 1;
	pushdown(u, M);
	if (x <= M) return query(M << 1, L, M, x);
	return query(M << 1 | 1, M + 1, R, x);
}
void build(int u, int L, int R) {
	lzy[u] = 0;
	if (L == R) return void(w[u] = a[L]);
	int M = L + R >> 1;
	build(M << 1, L, M), build(M << 1 | 1, M + 1, R), w[u] = w[M << 1] & w[M << 1 | 1];
}
int as[N];
int main() {
	read(n), read(m), read(p);
	for (int i = 1; i <= n; i++) read(a[i]), ans[i].l = 1, ans[i].r = m + 1, ans[i].id = i;
	for (int i = 1; i <= m; i++) read(q[i].l), read(q[i].r), read(q[i].v);
	for (int k = 1; k <= __lg(n) + 1; k++) {
		sort(ans + 1, ans + n + 1), build(1, 1, n);
		int nr = 1;
		for (int i = 1; i <= n; i++) {
			if (ans[i].l == ans[i].r) continue;
			while (nr <= (ans[i].l + ans[i].r >> 1)) update(1, 1, n, q[nr].l, q[nr].r, q[nr].v), ++nr;
			if (query(1, 1, n, ans[i].id) <= p) ans[i].l = (ans[i].l + ans[i].r >> 1) + 1;
			else ans[i].r = (ans[i].l + ans[i].r) >> 1;
		}
	}
	for (int i = 1; i <= n; i++) as[ans[i].id] = ans[i].l;
	for (int i = 1; i <= n; i++) write(as[i] <= m ? as[i] : -1), IO::putc(' ');
	do_flush();
	return 0;
}
```

---

## 作者：Moeebius (赞：3)

## Preface

出题的时候给的空间限制 256MB。

然后验题人 @[Enucai](https://www.luogu.com.cn/user/169574) 用主席树把 std 吊打了。

经过出题组讨论决定，把主席树卡掉。

于是就有了 128MB 的 ML。

然后 std 被管理员吊打了。


然后 std 又被 5ab 吊打了。

~~多灾多难的 std~~

## Analysis

首先讲一下部分分吧。

第一档是给暴力的。

第二、三档都是给二分的。我们把每次修改标记到各个编号上，然后由于按位或单调不降，可以在每个编号上二分从第几次操作开始大于 $P$。

实现的时候预处理前缀或即可，时间复杂度 $O(N+Q+N\log Q)$。

---

接下来讲正解。

同样从单调性出发，我们考虑整体二分。

考虑当前要处理 $[l,r]$ 的点，答案可能为 $[L,R]$。

我们令 $mid\gets \dfrac{(L+R)}{2}$。

递归时，我们**用线段树**先做掉 $[L,mid]$ 的询问，然后找出已经超过 $P$ 的位置，扔到「第一堆点」去；没有超过的扔到「第二堆点」。

然后把刚刚进行的，$[L,mid]$ 的操作「回滚」掉。

接着，递归 $[L,mid]$ 和 $[mid+1,r]$，分别求解「第一堆点」和「第二堆点」的答案。

递归出口就是 $L=R$。

此时，我们把这个询问做掉，然后将 $[l,r]$ 的点的答案设为 $L$，**并且需要保存一下**。

这样的话，递归完前一半，**等同于把前一半询问做完并且保存了下来，做后一半的时候就无需重新做这些询问了。**

如果被卡常了，可以用 zkw 线段树 + 标记永久化，常数非常小。

实现回滚的话就是存两个 tag 啦！

时间复杂度 $O((N+Q)\log N \log Q)$，空间复杂度 $O(N)$，可以通过本题。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define il inline
#define mkp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define lll __int128
#define ll long long
#define For(i,j,k) for(int i=(j); i<=(k); ++i)
#define ForDown(i,j,k) for(int i=(j); i>=(k); --i)
#define pb push_back
#define FileIO(filename) freopen(filename ".in" ,"r",stdin);freopen(filename ".out" ,"w",stdout)
template<typename T> 
il void read(T &x){ x=0;int f=1;char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}while(isdigit(c)){x=x*10+c-'0';c=getchar();}x*=f;}
template<typename T, typename ... Args>
il void read(T &x, Args &... y){ read(x);read(y...); }
// File head end

const int MAXN=1e6+5;
int n,N=1,q,p,a[MAXN],ans[MAXN],id[MAXN],tmp[MAXN];
struct Query
{
    int l,r,v;
}qry[MAXN]; // 离线询问
struct Node
{
    int pre,cur;
    // 标记永久化，一切皆 tag
    // cur 是当前 tag
    // pre 是最后一次保存的 tag
    Node() : pre(0),cur(0) {}
}T[MAXN<<2];
#define lc(p) (p<<1)
#define rc(p) (p<<1|1)
il void build()
{
    while(N<=n+1) N<<=1;
    For(i,N+1,N+n) T[i].cur=T[i].pre=a[i-N];
}
il void modify(int id) // 区间按位或
{
    for(int s=qry[id].l+N-1, t=qry[id].r+N+1, v=qry[id].v; s^t^1; s>>=1, t>>=1)
    {
        if(~s&1) T[s^1].cur|=v;
        if(t&1) T[t^1].cur|=v;
    }
}
il int calc(int pos) // 单点查询
{
    int __ans=0;
    for(int p=pos+N; p; p>>=1)
    {
        __ans|=T[p].cur;
    }
    return __ans;
}
void roll_back(int id) // 回滚到上一次保存
{
    for(int s=qry[id].l+N-1, t=qry[id].r+N+1; s^t^1; s>>=1, t>>=1)
    {
        if(~s&1) T[s^1].cur=T[s^1].pre;
        if(t&1) T[t^1].cur=T[t^1].pre;
    }
}
void save(int id) // 回滚到上一次保存
{
    for(int s=qry[id].l+N-1, t=qry[id].r+N+1; s^t^1; s>>=1, t>>=1)
    {
        if(~s&1) T[s^1].pre=T[s^1].cur;
        if(t&1) T[t^1].pre=T[t^1].cur;
    }
}
il void solve(int l, int r, int L, int R) // id 中 [l,r] 的点，答案为 [L,R]
{
    if(L==R)
    {
        modify(L);
        For(i,l,r) ans[id[i]]=L;
        save(L); // 保存
        return;
    }
    int mid=(L+R)>>1,pl=l,pr=r;
    For(i,L,mid)
    {
        modify(i);
    }
    For(i,l,r)
    {
        if(calc(id[i])>p) tmp[pl++]=id[i];   
        else tmp[pr--]=id[i];
    }
    copy(tmp+l,tmp+r+1,id+l);
    For(i,L,mid) roll_back(i); // 回滚
    if(pl==1) {For(i,L,mid) modify(i),save(i);} // 易错点，即使左半边没有点也要把这些询问做掉并且存下来，否则后面会出问题
    else solve(l,pl-1,L,mid);
    if(pr==n) {For(i,mid+1,R) modify(i),save(i);}
    else solve(pr+1,r,mid+1,R);
}

signed main()
{
    read(n,q,p);
    For(i,1,n) read(a[i]);
    For(i,1,q) read(qry[i].l,qry[i].r,qry[i].v);
    qry[++q] = (Query){1, n, INT_MAX}; // 强制有解，输出的时候特判一下即可
    build();
    For(i,1,n) id[i]=i;
    solve(1,n,1,q);
    For(i,1,n) printf("%d ",ans[i]==q?-1:ans[i]);
    puts("");
	return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

很显然每个数的每一位最多只会修改一遍。于是拆位，每一位开个并查集，存下一个不拥有这一位的数，就可以暴力修改了。

但是空间是 $O(n \log V)$ 的，炸了。于是可以考虑手写 `i24` 类，同时并查集寻找祖先不要用递归版的路径压缩，然后就过了。

```cpp
// Problem: P8955 「VUSC」Card Tricks
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8955
// Memory Limit: 100 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 20], *p1 = buf, *p2 = buf;
inline int read() {
    char c = getchar();
    int x = 0;
    for (; !isdigit(c); c = getchar()) ;
    for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    return x;
}

const int maxn = 1000100;

int n, m, K, a[maxn], ans[maxn];

struct i24 {
	unsigned char a, b, c;
	
	inline void set(int x) {
		a = x & 255;
		b = (x >> 8) & 255;
		c = (x >> 16) & 255;
	}
	
	inline int val() {
		return a + ((int)b << 8) + ((int)c << 16);
	}
} fa[30][maxn];

inline int find(int k, int x) {
	while (fa[k][x].val() != x) {
		int t = fa[k][fa[k][x].val()].val();
		fa[k][x].set(t);
		x = t;
	}
	return x;
}

void solve() {
	n = read();
	m = read();
	K = read();
	for (int i = 1; i <= n; ++i) {
		a[i] = read();
		ans[i] = -1;
	}
	for (int j = 0; j < 30; ++j) {
		for (int i = 1; i <= n + 1; ++i) {
			fa[j][i].set((a[i] & (1 << j)) ? i + 1 : i);
		}
	}
	for (int t = 1, l, r, x; t <= m; ++t) {
		l = read();
		r = read();
		x = read();
		for (int j = 0; j < 30; ++j) {
			if ((~x) & (1 << j)) {
				continue;
			}
			for (int i = find(j, l); i <= r; i = find(j, i)) {
				a[i] |= (1 << j);
				if (a[i] > K && ans[i] == -1) {
					ans[i] = t;
				}
				fa[j][i].set(i + 1);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		printf("%d ", ans[i]);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```


---

## 作者：Hisy (赞：1)

## 前言
跟同学们打赌，随机跳题，结果跳到了这一道题目……
## 分析
由于或上一个数，该数一定不会变小，具有单调性，所以考虑如下思路：
- 对于每一个元素，可以二分到哪一个操作大于 $p$。区间或操作可以使用线段树维护。

但是，这样的时间复杂度是 $n\times m\log n$ 的。

记得之前校园 OI 提到过一次算法：整体二分。就是指对于需要 $n$ 次二分的算法时间复杂度，并且二分的上界下界可以相同，那么可以放到一起二分。时间复杂度可以优化至理论 $n\log n\log m$ 的复杂度。（复杂度不会证明）
## 整体二分
整体二分是一种离线算法，思路大概是对询问进行划分。
- 假如，当前二分的值域为 $[l,r]$，设 $mid=\frac{l+r}{2}$，并进行划分询问。
- 将 $check(mid)$ 结果为否的询问划入左区间，即 $[l,mid]$ 的区间。将 $check(mid)$ 结果为真的询问划入右区间，即 $[mid+1,r]$。（突然感觉像分治思路）
- 对于左右两个区间，分别再次进行二分。
- 直到如果二分值域长度为一，即为答案。

本蒟蒻初次听老师说的时候，一头雾水，云里雾里的。

很明显，上述操作可以使用类似于递归的方式实现，伪代码如下：
```cpp
void solve(int l,int r,int L,int R){
	if(L==R){//二分到答案了 
		for(int i=l;i<=r;++i){
			ans[que[i].id]=L;
		}
		return; 
	}
	int mid=(L+R)>>1,ltop=0,rtop=0;//划分 mid 
	for(int i=l;i<=r;++i){
		if(check(b[i],mid)){
			rson[++rtop]=b[i];//进入右区间 
		}else{
			lson[++ltop]=b[i];//进入左区间 
		}
	}
	for(int i=1;i<=ltop;++i){
		b[i+l-1]=lson[i];
	}//属于左区间放左边 
	for(int i=1;i<=rtop;++i){
		b[i+l+ltop-1]=rson[i];
	}//属于右区间放右边 
	solve(l,l+ltop-1,L,mid);//二分左区间 
	solve(l+ltop,r,mid+1,R);//二分右区间 
}
```
## 回归正题
就是利用单调性和题目允许离线进行整体二分。但是，思路要进行如下转化：
- 每一次询问 $val$ 在第 $i$ 个数什么时候会变得大于 $p$。

ok，这样思路是不是清晰了很多。接下来，考虑询问结构体怎么弄：
- 首先，$val$ 表示原来的数。
- 肯定还要有 $id$ 表示第几个数，没有这个怎么输出？

单靠这两个是不够的，还需要有一个 $opt$ 表示后来得数，这个是我调了 $2$ 天之后看题解翻到了[这位大佬得题解](https://www.luogu.com.cn/article/mnxau7kp)的出来得结论。

再把 $check$ 往里面一代，你就会得出一份有正确性得代码！（来之不易呀）
## 代码
```cpp
#include<stdio.h>
#include<ctype.h>
#define MAXN 1000010
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#define putchar putchar_unlocked
#define opt optimize
#define tar target
#pragma GCC opt(3)
#pragma GCC tar("avx")
#pragma GCC opt("Ofast")
#pragma GCC opt("inline")
#pragma GCC opt("-fgcse")
#pragma GCC opt("-fgcse-lm")
#pragma GCC opt("-fipa-sra")
#pragma GCC opt("-ftree-pre")
#pragma GCC opt("-ftree-vrp")
#pragma GCC opt("-fpeephole2")
#pragma GCC opt("-ffast-math")
#pragma GCC opt("-fsched-spec")
#pragma GCC opt("unroll-loops")
#pragma GCC opt("-falign-jumps")
#pragma GCC opt("-falign-loops")
#pragma GCC opt("-falign-labels")
#pragma GCC opt("-fdevirtualize")
#pragma GCC opt("-fcaller-saves")
#pragma GCC opt("-fcrossjumping")
#pragma GCC opt("-fthread-jumps")
#pragma GCC opt("-funroll-loops")
#pragma GCC opt("-fwhole-program")
#pragma GCC opt("-freorder-blocks")
#pragma GCC opt("-fschedule-insns")
#pragma GCC opt("inline-functions")
#pragma GCC opt("-ftree-tail-merge")
#pragma GCC opt("-fschedule-insns2")
#pragma GCC opt("-fstrict-aliasing")
#pragma GCC opt("-fstrict-overflow")
#pragma GCC opt("-falign-functions")
#pragma GCC opt("-fcse-skip-blocks")
#pragma GCC opt("-fcse-follow-jumps")
#pragma GCC opt("-fsched-interblock")
#pragma GCC opt("-fpartial-inlining")
#pragma GCC opt("no-stack-protector")
#pragma GCC opt("-freorder-functions")
#pragma GCC opt("-findirect-inlining")
#pragma GCC opt("-fhoist-adjacent-loads")
#pragma GCC opt("-frerun-cse-after-loop")
#pragma GCC opt("inline-small-functions")
#pragma GCC opt("-finline-small-functions")
#pragma GCC opt("-ftree-switch-conversion")
#pragma GCC opt("-foptimize-sibling-calls")
#pragma GCC opt("-fexpensive-optimizations")
#pragma GCC opt("-funsafe-loop-optimizations")
#pragma GCC opt("inline-functions-called-once")
#pragma GCC opt("-fdelete-null-pointer-checks")
#pragma GCC opt(2)
using namespace std;
struct node{
	int l,r,w;
}que[MAXN];
struct Node{
	int val,lazy;
}tree[MAXN<<2];
struct NODE{
	int val,id,opt;
}a[MAXN]; 
int n,q,p,ans[MAXN],lson[MAXN],rson[MAXN];
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
inline int read(){
	register int res=0;
	register char c=getchar();
	while(!isdigit(c)){
		c=getchar();
	}
	while(isdigit(c)){
		res=(res<<1)+(res<<3)+(c^48);
		c=getchar();
	}
	return res;
}
inline void write(const int ans){
	if(ans>9){
		write(ans/10);
	}
	putchar(ans%10+'0');
}
inline void push_down(const int root){
	const int lazy=tree[root].lazy;
	tree[root<<1].lazy|=lazy;
	tree[root<<1].val|=lazy;
	tree[root<<1|1].lazy|=lazy;
	tree[root<<1|1].val|=lazy;
	tree[root].lazy=0;
}
inline void change(const int root,const int l,const int r,const int L,const int R,const int val){
	if(L<=l&&r<=R){
		tree[root].lazy|=val;
		tree[root].val|=val;
		return;
	}
	const int mid=(l+r)>>1;
	push_down(root);
	if(L<=mid){
		change(root<<1,l,mid,L,R,val);
	}
	if(mid<R){
		change(root<<1|1,mid+1,r,L,R,val);
	}
}
inline int query(const int root,const int l,const int r,const int Q){
	if(l==r){
		return tree[root].val;
	}
	const int mid=(l+r)>>1;
	push_down(root);
	if(Q<=mid){
		return query(root<<1,l,mid,Q);
	}
	return query(root<<1|1,mid+1,r,Q); 
}
inline void modify(const int root,const int l,const int r,const int Q,const int val){
	if(l==r){
		tree[root].val=val;
		return;
	}
	const int mid=(l+r)>>1;
	push_down(root);
	if(Q<=mid){
		modify(root<<1,l,mid,Q,val);
	}else{
		modify(root<<1|1,mid+1,r,Q,val);
	}
}
inline void solve(const int l,const int r,const int L,const int R){
    if(l>r){
    	return;
	}
    if(L==R){
        for(register int i=l;i<=r;++i){
        	ans[a[i].id]=L;
		}
        return;
    }
    const int mid=(L+R)>>1;
	register int ltop=0,rtop=0;
    for(register int i=L;i<=mid;++i){
    	change(1,1,n,que[i].l,que[i].r,que[i].w);
	}
    for(register int i=l;i<=r;++i){
        const int sum=query(1,1,n,a[i].id);
        if((sum|a[a[i].id].val)<=p){
        	a[a[i].id].opt|=sum;
			rson[++rtop]=a[i].id;
		}else{
			lson[++ltop]=a[i].id;
		}
		modify(1,1,n,a[i].id,a[a[i].id].opt);
    }
    for(register int i=1;i<=ltop;++i){
    	a[i+l-1].id=lson[i];
	}
    for(register int i=1;i<=rtop;++i){
    	a[i+l+ltop-1].id=rson[i];
	}
    solve(l,l+ltop-1,L,mid);
    solve(l+ltop,r,mid+1,R);
}
int main(){
	n=read();
	q=read();
	p=read(); 
	que[q+1]=((node){1,n,p});
	for(register int i=1;i<=n;++i){
		a[i].val=read();
		a[i].id=i;
	}
	for(register int i=1;i<=q;++i){
		que[i].l=read();
		que[i].r=read();
		que[i].w=read();
	}
	solve(1,n,1,q+1);
	for(register int i=1;i<=n;++i){
		if(ans[i]==q+1){
			putchar('-');
			putchar('1');
		}else{
			write(ans[i]);
		}
		putchar(' ');
	}
	return 0;
}
```
## 闲话
当然，来之不易其实并没有太多的体现在对于算法的考验，因为 $1$ 天编码，$3$ 天调试加卡常。

说实话，挺毒瘤的，第九个点本来一直卡在 $3004$ 毫秒卡不过去，结果想到了校园一位巨佬得出得结论：C++20 比 C++14 跑得快，然后卡过去的。

本代码还可以有很多优化的地方，比如常数更小的什么线段树呀，什么第三篇题解上的不撤销整体二分呀，甚至还有想不出来的并查集。

总之，为了纪念 $4$ 天的恶战，就写一篇题解纪念一下吧。

---

## 作者：Laisira (赞：1)

## 整体二分板题啊

### ~~废话~~
做完后看了看题解区的大佬竟然用了传说中的**不撤销整体二分**，感觉不需要啊，整体二分板子改改就能过。

### 题面
给出 $n$ 个数和 $q$ 次操作，第 $i$ 次操作要求把 $[l,r]$ 的区间按位与上 $w$。问第 $i$ 个数在至少第几次操作后严格大于 $P$。

### 思路
显然，在每次操作后，序列上的数不降。考虑整体二分，线段树支持修改和查询，修改可以记忆一个 $op_i$ 表示新与的数，对他重复利用，多 $\ * \ $ 几次就过了。

### 代码
```cpp
int a[Maxn],fg[Maxn],opt[Maxn];
struct Query {
    int l,r,w;
} Q[Maxn];
int n,q,p;
int answer[Maxn];
// ~~ 线段树 ~~ 
int value[(Maxn<<2)],lazy[(Maxn<<2)];
void merge(int x,int l,int r,int L,int R,int val)
{
    if(L<=l&&r<=R) {lazy[x]|=val,value[x]|=val;return ;}
    int mid=(l+r)>>1;
    value[x<<1]|=lazy[x];
    value[x<<1|1]|=lazy[x];
    lazy[x<<1]|=lazy[x];
    lazy[x<<1|1]|=lazy[x];
    lazy[x]=0;
    if(L<=mid)merge(x<<1,l,mid,L,R,val);
    if(mid<R)merge(x<<1|1,mid+1,r,L,R,val);
}
int query(int x,int l,int r,int u)
{
    if(l == r)return value[x];
    int mid=(l+r)>>1;
    value[x<<1]|=lazy[x];
    value[x<<1|1]|=lazy[x];
    lazy[x<<1]|=lazy[x];
    lazy[x<<1|1]|=lazy[x];
    lazy[x]=0;
    if(u<=mid)return query(x<<1,l,mid,u);
    else return query(x<<1|1,mid+1,r,u);
}
void merge0(int x,int l,int r,int u,int val)
{
    if(l == r)return value[x]=val,void();
    int mid=(l+r)>>1;
    value[x<<1]|=lazy[x];
    value[x<<1|1]|=lazy[x];
    lazy[x<<1]|=lazy[x];
    lazy[x<<1|1]|=lazy[x];
    lazy[x]=0;
    if(u<=mid)merge0(x<<1,l,mid,u,val);
    else merge0(x<<1|1,mid+1,r,u,val);
}
// ~~ 整体二分 ~~
int q1[Maxn],q2[Maxn];
void solve(int head,int tail,int l,int r)
{
    int mid=(l+r)>>1,s1=0,s2=0;
    if(head>tail)return ;
    if(l == r) {
        for(int i=head;i<=tail;i++)
            answer[fg[i]]=l;
        return ;
    }
    for(int i=l;i<=mid;i++)
        merge(1,1,n,Q[i].l,Q[i].r,Q[i].w);
    for(int i=head;i<=tail;i++)
    {
        int sum=query(1,1,n,fg[i]);
        if((sum|a[fg[i]])<=p)opt[fg[i]]|=sum,q2[++s2]=fg[i],merge0(1,1,n,fg[i],opt[fg[i]]);
        else q1[++s1]=fg[i],merge0(1,1,n,fg[i],opt[fg[i]]);
    }
    for(int i=1;i<=s1;i++)
        fg[i+head-1]=q1[i];
    for(int i=1;i<=s2;i++)
        fg[i+head+s1-1]=q2[i];
    solve(head,head+s1-1,l,mid);
    solve(head+s1,tail,mid+1,r);
}
int main()
{
    io>>n>>q>>p;
    Q[q+1]=(Query){1,n,0};
    for(int i=1;i<=n;i++)
        io>>a[i],fg[i]=i;
    for(int i=1;i<=q;i++)
    {
        int l,r,w;
        io>>l>>r>>w;
        Q[i]={l,r,w};
    }
    solve(1,n,1,q+1);
    for(int i=1;i<=n;i++)
        if(answer[i]!=q+1)
            io<<answer[i],io.pc(32);
        else io.pc('-'),io<<1,io.pc(32);
    return 0;
}
```

---

## 作者：StayAlone (赞：0)

首先很容易想到整体二分，线段树维护区间或，需要带撤销，时间复杂度 $\mathcal O(n\log^2 n)$。然而撤销太麻烦，存在一种不撤销的整体二分。

思想其实很简单。在整体二分的分治树上，每次操作就是将一个区间的询问往左右两个区间下放。对于每一层，线段树依次从左往右处理即可，时间复杂度不受影响。

然而这个题有更好的做法。考虑换维，扫序列维，线段树维护前 $i$ 次操作该位置的或。那么只需要在 $l$ 处加入 $v$，$r+1$ 处删除 $v$，配合线段树上二分，即可做到 $\mathcal O(n\log n)$。

[AC record](https://www.luogu.com.cn/record/214754920)

```cpp
int n, q, P, a[MAXN];
vector <pii> opt[MAXN];

struct setr {
    int val[MAXN << 2];

    il void pushup(int x) {
        val[x] = val[ls(x)] | val[rs(x)];
    }

    il void upd(int x, int l, int r, int k, int p) {
        if (l == r) return val[x] = p, void();
        int mid = l + r >> 1;
        k <= mid ? upd(ls(x), l, mid, k, p) : upd(rs(x), mid + 1, r, k, p);
        pushup(x);
    }

    il int query(int x, int l, int r, int k) {
        if (l == r) return (k | val[x]) > P ? l : -1;
        int w = val[ls(x)], mid = l + r >> 1;
        if ((w | k) > P) return query(ls(x), l, mid, k);
        return query(rs(x), mid + 1, r, w | k);
    }
} T;

int main() {
    read(n, q, P); rer(i, 1, n, a);
    int l, r, v;
    rep1(i, 1, q) read(l, r, v), opt[l].eb(v, i), opt[r + 1].eb(-v, i);
    rep1(i, 1, n) {
        for (auto [v, t] : opt[i]) T.upd(1, 1, q, t, v > 0 ? v : 0);
        printf("%d ",  T.query(1, 1, q, a[i]));
    }
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

从左往右扫描，假设扫描到第 $p$ 个点。如果第 $j$ 次操作是或 $v_j$ 并且当前点在范围内（$p\in[l_j,r_j]$）则第 $j$ 个位置是 $v_j$。把 $0$ 位置设成 $a_i$ 之后就是线段树二分出第一次 $\ge P+1$ 的位置，$\mathcal{O}(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ls (p << 1)
#define rs (p << 1 | 1)
#define pii pair<int, int>
#define fi first
#define se second
#define mid (l + r >> 1)
using namespace std;
const int N = 1e6 + 5;
int n, q, k, a[N], tr[N << 2], l, r, v;
vector<pii> vc[N];
inline void upd(int p, int l, int r, int x, int v){
    if(l == r){
        tr[p] = v;
        return ;
    }
    if(mid >= x) upd(ls, l, mid, x, v);
    else upd(rs, mid + 1, r, x, v);
    tr[p] = tr[ls] | tr[rs];
}
inline int find(int p, int l, int r, int v){
    if((v | tr[p]) < k) return -1;
    if(l == r) return l;
    if((v | tr[ls]) >= k) return find(ls, l, mid, v);
    return find(rs, mid + 1, r, v | tr[ls]);
}
int main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
    scanf("%d%d%d", &n, &q, &k), k++;
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= q; i++){
        scanf("%d%d%d", &l, &r, &v);
        vc[l].push_back({i, v}), vc[r + 1].push_back({i, 0});
    }
    for(int i = 1; i <= n; i++){
        upd(1, 0, q, 0, a[i]);
        for(pii e : vc[i]){
            upd(1, 0, q, e.fi, e.se);
        }
        printf("%d ", find(1, 0, q, 0));
    }
    puts("");
    return 0;
}
```

---

## 作者：strcmp (赞：0)

根据位或的性质，任意时刻之后每个数都是单调不减的。

直接考虑修改并不好做，这类似一个折半警报器状物，并且我们很难对一个区间做整体位或修改和 $\max$ 的查询（$\max$ 是查询是否有东西超过了 $P$）。

一个修改影响的是一个区间，考虑扫描线位置，在 $l$ 加入这个修改，在 $r + 1$ 删除这个修改。

考虑当前扫描到 $a_i$，那么就是跟我们保留的修改集合进行位或。每次相当于加入或删除若干个集合的数。

$(\mathbb N^+,\,\text{or})$ 是交换幺半群，但不是群，不存在逆元。

因此考虑时间线段树，把修改放到 $[1,\,Q]$ 的时间轴上，一个位置是 $0$ 代表这个修改对当前位置没有作用，否则有作用。查询是前缀的线段树上二分。修改就是单点修改。

使用 zkw 树维护即可，时间复杂度 $\Theta((n + Q) \log Q)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define mid (l + r >> 1)
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pq = priority_queue<int>;
using vec = vector<int>;
constexpr int maxn = 1e6 + 10, mod = 998244353, B = 600; constexpr ll inf = 1e16;
int n, Q, P, a[maxn], t[maxn * 3], M = 1; vector<pii> q[maxn];
inline void mdf(int x, int d) { t[x += M] = d; while (x >>= 1) t[x] = t[x << 1] | t[x << 1 | 1]; }
inline int low(int p) {
    int x = 1, w = 0;
    while (x <= M) {
        if ((t[x << 1] | w | a[p]) > P) x <<= 1;
        else w |= t[x << 1], x = (x << 1) | 1;
    }
    if ((w | a[p] | t[x]) <= P) return -1;
    return x - M;
}
int main() {
    scanf("%d%d%d", &n, &Q, &P); while (M < Q) M <<= 1;
    rep(i, 1, n) scanf("%d", &a[i]);
    for (int i = 1, l, r, v; i <= Q; i++) scanf("%d%d%d", &l, &r, &v), q[l].pb({ v, i }), q[r + 1].pb({ 0, i });
    rep(i, 1, n) {
        for (auto x : q[i]) mdf(x.Y, x.X);
        printf("%d ", low(i));
    }
    return 0;
}
```

---

## 作者：imzfx_Square (赞：0)

### 前言

在练习整体二分的时候找到了这道，~~大力卡常后~~过了，顺便写篇题解。

### 思路

由于一个数或上另一个数，其结果必然不小于原数，所以满足单调性。

先想对于单个 $a_x$ 如何二分求解。

设当前二分的区间为 $[L,R]$（下文令 $mid=\displaystyle{\lfloor \frac{L+R}{2} \rfloor}$）：

- 对于操作区间 $[L,mid]$，计算 $k=\bigvee_{i=L}^{mid}[l_i \le x][x \le r_i]v_i$（即对于每个 $l_i \le x \le r_i$ 的区间，将它们的 $v_i$ 或起来）。

- 若 $a_x \vee k > p$，在左半区间继续查找，否则令 $a_x \larr a_x \vee k$，在右半区间继续查找。

对于多个 $a_i$，我们需要进行多次二分，显然这是不可取的。

考虑整体二分，则我们需要快速对一个区间进行或运算，查询单点权值，可以使用线段树。

值得一提的是，这道题只需要单点查询，因此可以使用一个类似于标记永久化的方法，如果在区间取或的递归过程中，当前区间被需要操作的区间完全覆盖，则在该区间打上或标记，查询时一路向下求标记或起来的和即可。

~~还有这道题需要卡常，笔者卡了很久才从 90pts 到 100pts~~。

### 代码：

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int N=1e6+5;
namespace SGT{
	#define L (x<<1)
	#define R (x<<1|1)
	int l[N<<2],r[N<<2];
	int tag[N<<2];
	inline void build(int x,int lq,int rq){
		l[x]=lq;
		r[x]=rq;
		tag[x]=0;
		if(lq==rq)return;
		const int mid=lq+rq>>1;
		build(L,lq,mid);
		build(R,mid+1,rq);
	}
	inline void modify(int x,int lq,int rq,int k){
		if(lq<=l[x]&&r[x]<=rq){
			if(k)tag[x]|=k;
			else tag[x]=0;//便于快速清空线段树
			return;
		}
		const int mid=l[x]+r[x]>>1;
		if(lq<=mid)modify(L,lq,rq,k);
		if(rq>mid)modify(R,lq,rq,k);
	}
	inline int query(int x,int i){
		if(l[x]==r[x])return tag[x];
		const int mid=l[x]+r[x]>>1;
		int res=tag[x];
		if(i<=mid)res|=query(L,i);
		else res|=query(R,i);
		return res;
	}
	#undef L
	#undef R
}
using SGT::build;
using SGT::modify;
using SGT::query;

int q[N],ql[N],qr[N];
int n,Q,p,a[N];
int l[N],r[N],k[N];
int ans[N];

//整体二分板子
inline void solve(int vaL,int vaR,int lq,int rq){
	if(lq>rq)return;
	if(vaL==vaR){
		for(int i=lq;i<=rq;++i)
			ans[q[i]]=vaL;
		return;
	}
	const int mid=vaL+vaR>>1;
	int cntl=0,cntr=0;
	for(int i=vaL;i<=mid;++i)
		modify(1,l[i],r[i],k[i]);
	for(int i=lq;i<=rq;++i){
		const int k=query(1,q[i]);
		if((k|a[q[i]])>p){
			ql[++cntl]=q[i];
		}else{
			a[q[i]]|=k;
			qr[++cntr]=q[i];
		}
	}
	for(int i=vaL;i<=mid;++i)
		modify(1,l[i],r[i],0);//清空线段树
	for(int i=1;i<=cntl;++i)
		q[lq+i-1]=ql[i];
	for(int i=1;i<=cntr;++i)
		q[lq+cntl+i-1]=qr[i];
	solve(vaL,mid,lq,lq+cntl-1);
	solve(mid+1,vaR,lq+cntl,rq);
}

template<typename T>
inline void read(T &x){
    char c;
    x=0;
    int fu=1;
    c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-')fu=-1;
        c=getchar();
    }
    while(c<='9'&&c>='0'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    x*=fu;
}
template<typename T>
inline void print(T x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)print(x/10);
    putchar(x%10+'0');
}

int main(){
	read(n);read(Q);read(p);
	for(register int i=1;i<=n;++i){
		read(a[i]);
		q[i]=i;
	}
	for(register int i=1;i<=Q;++i){
		read(l[i]);read(r[i]);read(k[i]);
	}
	build(1,1,n);
	solve(1,Q+1,1,n);
	for(register int i=1;i<=n;++i){
		if(ans[i]>Q)print(-1);
		else print(ans[i]);
		printf(" ");
	}
	return 0;
}
```

---

## 作者：Disjoint_cat (赞：0)

# [ P8955 Card Tricks](https://www.luogu.com.cn/problem/P8955)

## 题意

给你一个长度为 $n$ 的数组 $a$ 和一个整数 $P$。有 $q$ 次操作，每次操作用一个三元组 $(l,r,v)$ 表示，表示对于所有的 $i\in[l,r]$，令 $a_i\gets a_i\operatorname{or}v$，其中 $\operatorname{or}$ 为按位或。

现在你需要对每个 $1\le i\le n$，回答以下问题：

> 求出最小的整数 $x\le n$，使得在依次执行操作 $1\sim x$ 后，有 $a_i>P$，或报告不存在。

数据范围：$n,q\le10^6$。

## 题解

考虑一个经典的 trick：扫描线。

维护一个数据结构，用来维护每个前缀的所有操作的 $v$ 的按位或值。那么当扫描线扫到第 $i$ 个位置时，我们需要撤销所有满足 $r=i-1$ 的操作，并加入 $l=i$ 的操作。此时，其中第 $t$ 个位置的值就表示第 $t$ 次操作对 $a_i$ 的影响（或上的值）。

可以用线段树维护。因为按位或满足结合律，所以我们需要在线段树上找到一个最短的前缀 $a_i$ 按位或上该前缀的总影响所得到的值 $>P$。

在线段树上做二分即可解决该问题。时间复杂度 $\Theta((n+q)\log q)$，空间复杂度 $\Theta(n+q)$。

## 代码片段

最大数据跑了大概一秒，完全没问题。~~不知道出题人的两只 $\log$ 做法是哪来的。~~

```cpp
const int N=1000005,SZ=1<<21;
int n,m,p,a[N];
vector<PII>add[N],del[N];

struct segt
{
	int tr[SZ];
	segt(){memset(tr,0,sizeof(tr));}
#define mid (l+r>>1)
#define rmd (mid+1)
#define lid (id<<1)
#define rid (lid|1)
	void modify(int pos,int val,int l=1,int r=m+1,int id=1)
	{
		if(l==r)return void(tr[id]=val);
		if(pos<=mid)modify(pos,val,l,mid,lid);
		else modify(pos,val,rmd,r,rid);
		tr[id]=tr[lid]|tr[rid];
	}
	int query(int stt,int goal,int l=1,int r=m+1,int id=1)
	{
		if(l==r)return l;
		if((stt|tr[lid])>goal)return query(stt,goal,l,mid,lid);
		return query(stt|tr[lid],goal,rmd,r,rid);
	}
}t;

void Solve(int CASE)
{
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1,l,r,v;i<=m;i++)
	{
		cin>>l>>r>>v;
		add[l].PB(i,v),del[r+1].PB(i,v);
	}
	for(int i=1;i<=n;i++)
	{
		for(auto j:add[i])t.modify(j.fi,j.se);
		for(auto j:del[i])t.modify(j.fi,0);
		int res=t.query(a[i],p);
		if(res<=m)cout<<res;
		else cout<<"-1";
		cout<<" ";
	}
}
```

---

