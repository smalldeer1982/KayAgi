# Max Mex

## 题目描述

Grisha 发现了一棵以节点 $1$ 为根的树（即一个无环连通图）。

但这棵树并不是普通的树。每个节点上都写有一个从 $0$ 到 $n-1$ 的排列 $p$，即在节点 $i$ 上写有数字 $p_i$。

Grisha 喜欢为自己发明一些奇怪又有趣的问题，但他并不总能解决这些问题，所以你需要帮助他处理关于这棵树的两种操作。

我们定义函数 $MEX(S)$，其中 $S$ 是一个非负整数集合，$MEX(S)$ 表示不在 $S$ 中的最小非负整数。

设 $l$ 是树上的一条简单路径。记路径上节点的编号为 $u_1, u_2, \ldots, u_k$。

定义 $V(l)$ 为集合 $\{p_{u_1}, p_{u_2}, \ldots, p_{u_k}\}$。

操作有两种：

1. 对于两个节点 $i$ 和 $j$，交换 $p_i$ 和 $p_j$ 的值。
2. 在所有可能的路径 $l$ 中，求 $MEX(V(l))$ 的最大值。

## 说明/提示

括号中的数字表示节点上的排列值。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1083C/ee001f2941a74485fa338c5683d0a7b9e6c8a87f.png)  
在第一个样例中，对于第一个操作，最优路径是从节点 $1$ 到节点 $5$。此时集合为 $\{0, 1, 2\}$，$MEX$ 为 $3$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1083C/a97ad343dd7d844125d1fc7cb7e5c59a598975f8.png)  
对于第三个操作，最优路径是从节点 $5$ 到节点 $6$。此时集合为 $\{0, 1, 4\}$，$MEX$ 为 $2$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1083C/14b2534701770528716075e286813cf69ea8fa73.png)  
在第二个样例中，对于第一个操作，最优路径是从节点 $2$ 到节点 $6$。此时集合为 $\{0, 1, 2, 5\}$，$MEX$ 为 $3$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1083C/7d192d4175cd95e93fe02508dce0199090e46016.png)  
对于第三个操作，最优路径是从节点 $5$ 到节点 $6$。此时集合为 $\{0, 1, 3\}$，$MEX$ 为 $2$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1083C/50ab27acea9feed5a4efb779b2f53af3eecd0804.png)  
对于第五个操作，最优路径是从节点 $5$ 到节点 $2$。此时集合为 $\{0, 1, 2, 3\}$，$MEX$ 为 $4$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1083C/a6c30611a7b3214e1977864c9cb1f77350bde41b.png)  
对于第七个操作，最优路径是从节点 $5$ 到节点 $4$。此时集合为 $\{0, 1, 2, 3\}$，$MEX$ 为 $4$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1083C/deda5efb4637745ff35eb20d670feb37c9954d9c.png)  
对于第九个操作，最优路径是从节点 $6$ 到节点 $5$。此时集合为 $\{0, 1, 3\}$，$MEX$ 为 $2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
2 5 0 3 1 4
1 1 3 3 3
3
2
1 6 3
2
```

### 输出

```
3
2
```

## 样例 #2

### 输入

```
6
5 2 1 4 3 0
1 1 1 3 3
9
2
1 5 3
2
1 6 1
2
1 4 2
2
1 1 6
2
```

### 输出

```
3
2
4
4
2
```

# 题解

## 作者：一扶苏一 (赞：17)

## Description

给定一棵有 $n$ 个点的树，每个节点有点权。所有的点权构成了一个 $0~\sim~n - 1$ 的排列。有 $q$ 次操作，每次操作 $1$ 为交换两个点的点权，操作 $2$ 为查询 $Mex(l)$ 值最大的 $Mex(l)$ 值，其中 $l$ 是树上的一条路径。定义一条路径 $l$ 的 $Mex$ 值 $Mex(l)$ 为这条路径上最小的没有出现过的自然数

## Input

第一行是一个整数 $n$ 代表点数

下面一行是 $n$ 个数字，代表每个点的点权，保证是一个 $0~\sim n - 1$ 的排列

下面一行有 $n - 1$ 个数字，第 $i$ 个数字代表钦定 $1$ 为根时第 $i + 1$ 个点的父节点

下面一行是一个整数 $q$，代表操作个数

下面 $q$ 行，每行一组操作。

如果该行第一个数字为 $1$，则后面有两个数字 $x,y$，代表交换 $x,y$ 的点权

否则该行有且仅有一个数字 $2$，代表一次查询

## Output

对每次查询输出一行一个整数作为答案

## Hint

$2~\leq~n~\leq~2~\times~10^5~,~1~\leq~q~\leq~2~\times~10^5$

## Solution

一道线段树维护图上信息的好题。

记得以前在某学堂学习时，PKU的HJC老师说线段树出现在高端算法竞赛中，除了扔上来一个序列维护一堆东西以外，如果可以用线段树解决，那么原因一定是这道题目的信息具有 **可合并性**。现在想想这大概就是一个比较恰当的例题了。

我们考虑这道题目，每次询问可以转化成查询一个最小的 $k$ 使得 $[0,k)$ 都出现在同一条链上。这个 $k$ 显然是满足二分性质的，于是我们只需要一个能够维护这树节点权值前缀的连通性的数据结构了。考虑如果相邻的两段权值区间的点可以被合并为一条链，那么这段权值区间并显然是合法的。我们考虑对每段区间维护过区间内所有值的链的两个端点。注意这条链必须包含区间中的所有权值但是不一定仅包含这些权值。例如对于区间 $[1,2]$，这条链包含 $\{1,2,4\}$ 也是合法的。

考虑合并时大区间合法当且仅当从两个链的四个端点中选两个做新的端点，剩下两个点都在链上即可。参考 [这道题](https://www.luogu.org/problemnew/show/P3398) 我们可以得到判断一个点是否在一条链上的方法，即：

记两端点为 $u,v$，需要判定的点为 $x$，$LCA(u,v)~=~y$，则有：

$x$ 在链 $(u,v)$ 上 $\Leftrightarrow$ $$((LCA(u,x) == x~\lor~LCA(v,x) == x)~\land LCA(x,y) == y)$$

于是枚举一下两个端点，判定一下即可。

发现在合并时我们会大量用到求LCA的操作，倍增显然不够优秀，于是我们使用ST预处理从而做到 $O(1)$ 查询。这样pushup的复杂度就被我们降到了 $O(w)$，其中 $w$ 为枚举端点的情况数，即 $C_4^2~=~6$。所以修改的复杂度为 $O(w \log n)$

考虑查询时，直接在线段树上二分，维护前缀链的连通性即可做到 $O(w \log n)$。

于是总复杂度 $O((n + q)~w \log n)$，其中 $w~=~6$，可以通过本题

## Code

```cpp
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define putchar(o)\
puts("I am a cheater!")
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = char(x % 10 + '0');} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 2000010;
const int maxm = 4000010;

int n, q, vistime, t;
int MU[maxn], fa[maxn], sz[maxn], dfn[maxm], pre[maxn], ST[30][maxn], deepth[maxn], rmp[maxn], dre[maxn];
std::vector<int> son[maxn];

struct Tree;

void dfs(ci);
void Make_ST();
int ask(Tree*);
void buildpool();
int cmp(ci&, ci&);
int Get_Lca(ci, ci);
void update(Tree*, ci);
bool Is_Lca(ci, ci, ci);
void build(Tree*, ci, ci);
void check(Tree*, Tree*, Tree*);

struct Tree {
	Tree *ls, *rs;
	int l, r;
	int v[2];
	
	inline void pushup() {
		if (!this->rs) {this->v[0] = this->ls->v[0]; this->v[1] = this->ls->v[1];}
		else if (!this->ls) {this->v[0] = this->rs->v[0]; this->v[1] = this->rs->v[1];}
		else if (!(~this->ls->v[0])) {
			this->v[0] = this->v[1] = -1;
		} else if (!(this->rs->v[0])) {
			this->v[0] = this->v[1] = -1;
		} else {
			check(this->ls, this->rs, this);
		}
	}
};
Tree *pool[maxm], qwq[maxm], *rot, pree;
int top;

int main() {
	freopen("1.in", "r", stdin);
	qr(n);
	for (rg int i = 1; i <= n; ++i) {qr(MU[i]); ++MU[i];}
	for (int i = 2; i <= n; ++i) {
		qr(fa[i]); son[fa[i]].push_back(i); ++sz[fa[i]]; ++dre[fa[i]]; ++dre[i];
	}
	bool _flag = true;
	for (rg int i = 1; i <= n; ++i) _flag &= dre[i] <= 2;
	if (_flag) {
		qr(q);
		int a;
		while (q--) {
			a = 0; qr(a);
			if (a == 2) {
				qw(n, '\n', true);
			} else {
				qr(a); qr(a);
			}
		}
		return 0;
	}
	dfs(1);
	Make_ST();
	for (rg int i = 1; i <= n; ++i) rmp[MU[i]] = i;
	buildpool();
	build(rot, 1, n);
	qr(q); int a, b, c;
	while (q--) {
		a = 0; qr(a);
		if (a == 2) {
			pree.v[1] = pree.v[0] = 0; qw(ask(rot) - 1, '\n', true);
		}
		else {
			b = c = 0; qr(b); qr(c);
			std::swap(rmp[MU[b]], rmp[MU[c]]); std::swap(MU[b], MU[c]);
			update(rot, MU[b]); update(rot, MU[c]);
		}
	}
	return 0;
}

void dfs(ci u) {
	dfn [pre[u] = ++vistime] = u;
	for (int i = 0; i < sz[u]; ++i) {
		deepth[son[u][i]] = deepth[u] + 1;
		dfs(son[u][i]); dfn[++vistime] = u;
	}
}

void Make_ST() {
	int dn = n << 1;
	t = log2(dn) + 1;
	for (rg int i = 1; i < dn; ++i) ST[0][i] = dfn[i];
	for (rg int i = 1; i <= t; ++i) {
		rg int di = i - 1;
		for (rg int l = 1; l < dn; ++l) {
			int r= l + (1 << i) - 1;
			if (r >= dn) break;
			ST[i][l] = cmp(ST[di][l], ST[di][l + (1 << di)]);
		}
	}
}

int cmp(ci &_a, ci &_b) {
	if (deepth[_a] < deepth[_b]) return _a;
	return _b;
}

void buildpool() {
	for (rg int i = 0; i < maxm; ++i) pool[i] = qwq + i;
	rot = pool[maxm - 1]; top = maxm - 2;
}

void build(Tree *u, ci l, ci r) {
	if ((u->l = l) == (u->r = r)) {u->v[1] = u->v[0] = rmp[l]; return;}
	int mid = (l + r) >> 1;
	if (l <= mid) build(u->ls = pool[top--], l, mid);
	if (mid < r) build(u->rs = pool[top--], mid + 1, r);
	u->pushup();
}

int Get_Lca(ci u, ci v) {
	int l = pre[u], r = pre[v];
	if (l > r) std::swap(l, r);
	int len = r - l + 1, T = log2(len);
	return cmp(ST[T][l], ST[T][r - (1 << T) + 1]);
}

bool Is_Lca(ci u, ci v, ci x) {
	int _tmp = Get_Lca(u, v);
	return (((Get_Lca(u, x) == x) || (Get_Lca(v, x) == x)) && (Get_Lca(_tmp, x) == _tmp));
}

#define doit \
	if (Is_Lca(v1, u1, x) && (Is_Lca(v1, u1, y))) {\
			u->v[0] = u1; u->v[1] = v1;\
			return;\
	}
void check(Tree *ls, Tree *rs, Tree *u) {
	if (ls->v[0] == 0) { *u = *rs; return;}
	int u1, v1, x, y;
	{
		u1 = ls->v[0]; v1 = ls->v[1]; x = rs->v[0]; y = rs->v[1];
		doit;
	}
	{
		u1 = rs->v[0]; v1 = ls->v[0]; x = rs->v[1]; y = ls->v[1];
		doit;
	}
	{
		u1 = rs->v[1]; v1 = ls->v[1]; x = rs->v[0]; y = ls->v[0];
		doit;
	}
	{
		u1 = rs->v[1]; v1 = ls->v[0]; x = rs->v[0]; y = ls->v[1];
		doit;
	}
	{
		u1 = rs->v[0]; v1 = ls->v[1]; x = rs->v[1]; y = ls->v[0];
		doit;
	}
	{
		u1 = rs->v[0]; v1 = rs->v[1]; x = ls->v[0]; y = ls->v[1];
		doit;
	}
	u->v[0] = u->v[1] = -1;
}
#undef doit

void update(Tree *u, ci pos) {
	if ((u->l > pos) || (u->r < pos)) return;
	if (u->l == u->r) {u->v[0] = u->v[1] = rmp[pos]; return;}
	if (u->ls) update(u->ls, pos);
	if (u->rs) update(u->rs, pos);
	u->pushup();
}

int ask(Tree *u) {
	Tree _tmp;
	if ((u->ls)) {
		check(&pree, u->ls, &_tmp);
		if (~_tmp.v[0]) {
			pree = _tmp; return u->rs ? ask(u->rs) : u->r;
		} else {
			return ask(u->ls);
		}
	} else if (u->rs) return ask(u->rs);
	else return u->r;
}
```

## Summary

判断一个点在一条链上的方法为：它和链的其中一个端点的LCA是他自己且它和这条链顶端的节点的LCA是顶端节点。

当LCA查询极多且难以离线处理时，考虑使用ST预处理欧拉遍历序做到 $O(1)$ 查询

注意ST存储欧拉遍历序需要开 $2n$ 的空间

---

## 作者：zhangboju (赞：14)

### 题目大意

给定一棵有根树，点带权，要求支持两种操作：

1. 交换某两个点的点权。

2. 对于树上的一条路径，其权值定义为该路径上所有点点权的 $\mathrm{mex}$，求所有路径的权值最大值。

保证点权是 $0\sim n-1$ 的排列。

$n,q\le 2\times 10^5 $，时限 $\texttt{3s}$。

### Solution

我们发现，$\mathrm{mex}$ 是一个不好直接维护的东西，考虑怎样将其转化为容易维护的东西。

这类问题可以先考虑不带修改怎么处理。

我们考虑维护 $[l,r]$ 这段数是否出现在链上（注意到根据 $\mathrm{mex}$ 的定义，这条链上可以有其他数），这样我们只需要找到最大的 $x$ 满足 $[0,x]$ 出现在链上即可。

到这里我们可能会认为做不下去了，似乎这个东西比原题更强，我们没有什么头绪。

但仔细思考，其实这种信息是 **可合并的**。

我们对于每个 $[l,r]$ 记一下它在树上对应的链上的两个端点，那么如果我们要合并 $[l_1,r_1],[l_2,r_2]$ 的信息，发现端点只可能取到 $l_1,r_1,l_2,r_2$ 中的两个，然后判断另外两个点是否在这条路径上，我们 $\binom{4}{2}=6$ 的枚举，就可以合并信息。

当然要解决一个问题，就是判断一个点是否在一条路径上，我们可以发现，其充要条件为这个点到这个路径两端的端点的距离和等于这段路径长度，我们可以用 LCA 来处理，转为深度差，这是经典技巧。

而可合并的信息用什么维护呢？线段树！

其实初学线段树的时候，我们可能错误的理解为线段树是用来维护一类序列信息的。实际上这 **不完全** 正确。线段树其实是用来维护一类 **可合并的** 信息，而我们并不关心其具体种类。举个例子，我们为什么可以用线段树来维护最大子段和？本质上就是因为最大子段和可以用几个简单的可合并信息表示，从而也是可合并的。

具体到这道题上，我们线段树上一个区间 $[l,r]$ 维护这个区间在树中出现的链上的两个端点，如果没有就是 $(-1,-1)$，合并就采用上述方法合并。

此时要用线段树维护，我们大可以把点权转为 $1\sim n$，反正现在维护的不是 $\mathrm{mex}$。

说的轻巧，可别忘了我们还有一个问题没解决，就是如何查询？

有同学会说了，那不就是二分吗？但你看，二分是 $O(n\log^2n)$ 的，不一定过得去。

其实大家应该都看出来了，这就是线段树二分。我在开始在这里没想太清楚，容我多啰嗦几句。具体的我们考虑向下查询，查询到叶子节点是直接返回（右）端点。然后对于一个普通节点，我们看它的左儿子对应信息和之前传下来的一个信息能不能合并，若能，则更新这个信息，返回递归右儿子的答案；若不能，则返回递归左儿子的答案。细节可以看代码。

其实这个信息就是左边的所有信息并。因为右边一个区间要合法，不仅要它自身合法，而且要求它和左边的区间能并起来合法。

发现上述这个过程会返回第一个不合法的位置，因此要将答案减一后输出。

同时带来的问题是我们对于一条链，只会跳到 $n$，因此需要特判一条链的情况，直接每个询问都输出 $n$ 即可。

有同学又要说了，这个求 LCA 的过程不是要带 $\log$，变成 $\log^2$ 吗，那我这样麻烦还为了什么呢？

大家又可能看出来了，我们可以使用简洁的 $O(n\log n)-O(1)$ LCA 求解。具体一点，我们按照欧拉序存储每个点（就是 dfs 时到这个点加入一次，从儿子递归出来后加入一次），两个点的 LCA 就是他们的 dfs 序对应在欧拉序上对应区间中的深度最低点，可以使用 ST 表预处理，便可实现预处理为 $O(n\log n)$，单次查询为 $O(1)$ 的 LCA。

### 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T> inline void read(T &x)
{
	x=0;short f=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x*=f;return;
}
const int N=5e5+5;
using PII=pair<int,int>;
#define x first
#define y second
vector<int>g[N];
int dep[N],mp[N],col[N],dfn[N];
int st[N][25],idx;
void dfs(int u)
{
	dfn[u]=++idx,st[idx][0]=u;
	for(int v:g[u]) dep[v]=dep[u]+1,dfs(v),st[++idx][0]=u;
}
int lg[N];
int chk(int x,int y){return dep[x]<dep[y]?x:y;}
int lca(int x,int y)
{
	if(x>y) swap(x,y);	
	int k=lg[y-x+1];
	return chk(st[x][k],st[y-(1<<k)+1][k]);
}
int dis(int x,int y)
{
	int l=lca(dfn[x],dfn[y]);
	return dep[x]+dep[y]-2*dep[l];
}
struct node{
	int l,r; 
	PII p;
}tr[N*4];
bool chk_in(PII a,int x){return dis(a.x,a.y)==dis(a.x,x)+dis(a.y,x);}
PII merge(PII a,PII b)
{
	if(a.x<0||b.x<0) return {-1,-1}; 
	if(chk_in(a,b.x)&&chk_in(a,b.y)) return a;
	if(chk_in(b,a.x)&&chk_in(b,a.y)) return b;
	if(chk_in({a.x,b.x},a.y)&&chk_in({a.x,b.x},b.y)) return {a.x,b.x};
	if(chk_in({a.x,b.y},a.y)&&chk_in({a.x,b.y},b.x)) return {a.x,b.y};
	if(chk_in({a.y,b.x},a.x)&&chk_in({a.y,b.x},b.y)) return {a.y,b.x};
	if(chk_in({a.y,b.y},a.x)&&chk_in({a.y,b.y},b.x)) return {a.y,b.y};
	return {-1,-1}; 
}
void pushup(int u){tr[u].p=merge(tr[u<<1].p,tr[u<<1|1].p);}
void build(int u,int l,int r)
{
	tr[u].l=l,tr[u].r=r;
	if(l==r) return tr[u].p={mp[l],mp[l]},void();
	int mid=l+r>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	pushup(u); 
}
void modify(int u,int pos,int x)
{
	if(tr[u].l==tr[u].r) return tr[u].p={x,x},void();
	int mid=tr[u].l+tr[u].r>>1;
	if(pos<=mid) modify(u<<1,pos,x);
	else modify(u<<1|1,pos,x);
	pushup(u);
}
int query(int u,PII tmp)
{
	if(tr[u].l==tr[u].r) return tr[u].r;
	PII t=(tmp.x==0&&tmp.y==0)?tr[u<<1].p:merge(tmp,tr[u<<1].p);
	if(t.x>=0) return query(u<<1|1,t);
	else return query(u<<1,tmp);
}
int n;
int deg[N];
int main()
{
	read(n);
	for(int i=1;i<=n;++i) read(col[i]),mp[++col[i]]=i;
	for(int i=2,fa;i<=n;++i) read(fa),g[fa].push_back(i),++deg[i],++deg[fa];
	bool flag=true;
	for(int i=1;i<=n;++i) if(deg[i]>2) flag=false;
	dfs(1);
	lg[0]=-1;
	for(int i=1;i<N;++i) lg[i]=lg[i>>1]+1; 
	for(int j=1;j<=21;++j)
	{
		for(int i=1;i<=idx;++i)
		{
			st[i][j]=st[i][j-1];
			if(i+(1<<j-1)<=idx) st[i][j]=chk(st[i][j],st[i+(1<<j-1)][j-1]);
		}
	}
	build(1,1,n);
	int q;read(q);
	while(q--)
	{
		int op,x,y;
		read(op);
		if(op==1)
		{
			read(x),read(y);
			if(flag) continue;
			modify(1,col[x],y),modify(1,col[y],x);
			swap(col[x],col[y]);
		}
		else if(flag) printf("%d\n",n);
		else printf("%d\n",query(1,{0,0})-1);
	}	
	return 0;
}

```

### Conclusion

个人认为这道题是一道好题，综合考察了多个知识点而没有多合一的意味。

既有对 $\mathrm{mex}$ 的精妙转化，又有线段树维护树形态的深刻理解，还有 $O(n\log n)-O(1)$ LCA 的实用技巧，不得不说还是值得一做。

---

## 作者：米奇 (赞：7)




## 题意:

给定一棵有n个点的树，每个节点有点权。所有的点权构成了一个$0 \sim n-1$的排列。有q次操作，每次操作1为交换两个点的点权，操作2为查询$Mex(l)$值最大的$Mex(l)$值,其中$l$是树上的一条路径。定义一条路径$l$的$Mex$值为这条路径上最小的没有出现过的自然数。



## 题解：

这是CF Div1 的C题，难度可想而知。



这题用的是我从来没用过（见过）的做法。



因为如果$Mex(l)=x$ 那么就表明$1-(x-1)$中的所有值都在一条路径上。



我们按值建线段树（不是权值线段树），$l-r$的这个点表示值从$l-r$的路径的两个端点，若不存在就为$(-1,-1)$



两个节点合并，需要用到LCA。



因为树有个性质，三个点$a,b,c$，记$dis(a,b)=A,dis(a,c)=B,dis(b,c)=C$



那么如果$A+B=C ||A+C=B||B+C=A$，那么这三个点在同一条路径上。



求dis时需要用到LCA。



查询答案用的也是我从来没用过的，原来的话我可能会用二分+线段树的做法。



但这是两只log的，其实这题是可以用线段树上二分的方法变成一只log。



怎么线段树上二分呢？我们先看$l-r$这个区间是否符合要求，符合直接return。



不符合，我们先查询左区间，判断是否满足，再查询右区间。



```cpp
int query(node &xjh,int nod,int l,int r)
{
	if(tree[nod].x>=0)
	{
		if(xjh.x<0)
		{
			xjh=tree[nod];
			return r+1;
		}
		node jia=merge(xjh,tree[nod]);
		if(jia.x>=0)
		{
			xjh=jia;
			return r+1;
		}
	}
	if(l==r)return l;
	int res=query(xjh,nod*2,l,mid);
	if(res<=mid)return res;
	else return query(xjh,nod*2+1,mid+1,r);
}
```



## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mid (l+r)/2
const int N=2e5+5;
int n,m,top,t,a[N],xu[N],head[N],ru[N],chu[N],dis[N],f[N][25];
struct node{
	int x,y;
}tree[N*4];
struct node2{
	int too,next;
}edge[N];
/*char buf[1<<21],*p1=buf,*p2=buf;
inline int gc()
{
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}*/
#define gc getchar
inline int read()
{
	int ret=0,f=0;
	char c=gc();
	while(!isdigit(c))
	{
		if(c=='-')f=1;
		c=gc();
	}
	while(isdigit(c))
	{
		ret=ret*10+c-48;
		c=gc();
	}
	if(f)return -ret;
	return ret;
}
void add(int a,int b)
{
	edge[++top].too=b;edge[top].next=head[a];head[a]=top;
}
void dfs(int u,int fa)
{
	ru[u]=++t;
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].too;
		f[v][0]=u;dis[v]=dis[u]+1;
		dfs(v,u);
	}
	chu[u]=++t;
}
bool pd(int x,int y)
{
	if(ru[x]<=ru[y]&&chu[x]>=chu[y])return true;
	return false;
}
int LCA(int x,int y)
{
	if(pd(x,y))return x;
	if(pd(y,x))return y;
	int k=x;
	for(int i=20;i>=0;i--)
		if(!pd(f[k][i],y))k=f[k][i];
	return f[k][0];
}
int dist(int a,int b)
{
	int lca=LCA(a,b);
	return dis[a]+dis[b]-2*dis[lca];
}
node hb(node a,int b)
{
	if(a.x<0||b<0)return (node){-1,-1};
	int aa=a.x,bb=a.y;
	int d1=dist(aa,b);
	int d2=dist(bb,b);
	int d3=dist(aa,bb);
	if(d1+d2==d3)return (node){aa,bb};
	if(d1+d3==d2)return (node){b,bb};
	if(d2+d3==d1)return (node){aa,b};
	return (node){-1,-1};
}
node merge(node a,node b)
{
	if(a.x<0||b.x<0)return (node){-1,-1};
	node jia=hb(a,b.x);
	if(jia.x<0)return (node){-1,-1};
	else return hb(jia,b.y);
}
void pushup(int nod)
{
	tree[nod]=merge(tree[nod*2],tree[nod*2+1]);
}
void build(int nod,int l,int r)
{
	if(l==r)
	{
		tree[nod]=(node){xu[l],xu[l]};
		return;
	}
	build(nod*2,l,mid);
	build(nod*2+1,mid+1,r);
	pushup(nod);
}
void change(int nod,int l,int r,int x)
{
	if(l==r)
	{
		tree[nod]=(node){xu[l],xu[l]};
		return;
	}
	if(x<=mid)change(nod*2,l,mid,x);
	else change(nod*2+1,mid+1,r,x);
	pushup(nod);
}
int query(node &xjh,int nod,int l,int r)
{
	if(tree[nod].x>=0)
	{
		if(xjh.x<0)
		{
			xjh=tree[nod];
			return r+1;
		}
		node jia=merge(xjh,tree[nod]);
		if(jia.x>=0)
		{
			xjh=jia;
			return r+1;
		}
	}
	if(l==r)return l;
	int res=query(xjh,nod*2,l,mid);
	if(res<=mid)return res;
	else return query(xjh,nod*2+1,mid+1,r);
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read()+1;
		xu[a[i]]=i;
	}
	for(int i=2;i<=n;i++)add(read(),i);
	f[1][0]=1;
	dfs(1,0);
	for(int i=1;i<=20;i++)
		for(int j=1;j<=n;j++)
			f[j][i]=f[f[j][i-1]][i-1];
	build(1,1,n);
	m=read();
	while(m--)
	{
		int opt=read();
		if(opt==1)
		{
			int l=read(),r=read();
			swap(xu[a[l]],xu[a[r]]);
			swap(a[l],a[r]);
			change(1,1,n,a[l]);
			change(1,1,n,a[r]);
		}
		else{
			node xjh=(node){-1,-1};
			int ans=query(xjh,1,1,n);
			printf("%d\n",ans-1);
		}
	}
	return 0;
}
```



---

## 作者：do_while_true (赞：3)

写倍增 LCA 被卡常了/fn

首先考虑令 $a_i$ 为权值是 $i$ 的点的编号。询问实际上是想要求出一个最大的前缀使得这个前缀里面的点在树上构成了一条链。

不难看出这个信息是可以合并的，也就是可以用线段树记录区间 $[l,r]$ 内的点是否能够被一条链所覆盖，并且这条链最短时两个端点是什么。只要能够合并两条链，那么单点修改也是容易做到的。

如何合并两条链？不需要分类讨论的做法是，把四个点按照 dfs 序排序之后相邻两两距离之和 $\div 2$（包括头尾）求出四个点形成的虚树大小，然后再枚举点对，看是否有一个点对之间的距离等于这个虚树大小，如果有的话端点就是这两个点，否则形成不了链。

常数有点大，需要用树剖求 LCA，在外层二分时间复杂度是 $\mathcal{O}(n\log^3 n)$，线段树上二分时间复杂度为 $\mathcal{O}(n\log^2 n)$．

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<set>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
const int N=200010;
int n;
int p[N],vis[N];
int dep[N];
int dfn[N],dft;
int top[N],fa[N],siz[N],son[N];
vi eg[N];
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			x=fa[top[x]];
		}
		else y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}
int dis(int x,int y){
	return dep[x]+dep[y]-2*dep[LCA(x,y)];
}
void dfs1(int x,int f){
	dfn[x]=++dft;
	fa[x]=f;siz[x]=1;dep[x]=dep[f]+1;
	for(auto v:eg[x])if(v!=f)dfs1(v,x),siz[x]+=siz[v],son[x]=siz[v]>siz[son[x]]?v:son[x];
}
void dfs2(int x,int t){
	top[x]=t;
	if(son[x])dfs2(son[x],t);
	for(auto v:eg[x])
		if(v!=fa[x]&&v!=son[x])
			dfs2(v,v);
}
#define ls (x<<1)
#define rs ((x<<1)|1)
pii tree[N<<2];
pii merge(pii x,pii y){
	int a=x.fi,b=x.se,c=y.fi,d=y.se;
	vi vec;vec.pb(a);vec.pb(b);vec.pb(c);vec.pb(d);
	sort(vec.begin(),vec.end(),[&](const int &x,const int &y){return dfn[x]<dfn[y];});
	int sum=(dis(vec[0],vec[1])+dis(vec[1],vec[2])+dis(vec[2],vec[3])+dis(vec[3],vec[0]))/2;
	for(int i=0;i<=3;i++)
		for(int j=i+1;j<=3;j++)
			if(dis(vec[i],vec[j])==sum)return mp(vec[i],vec[j]);
	return mp(0,0);
}
int ok(int x){
	return tree[x].fi>0;
}
inline void pushup(int x){
	if(ok(ls)&&ok(rs))
		tree[x]=merge(tree[ls],tree[rs]);
	else tree[x]=mp(0,0);
}
void build(int x,int l,int r){
	if(l==r){
		tree[x]=mp(vis[l],vis[l]);
		return ;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);build(rs,mid+1,r);
	pushup(x);
}
void modify(int x,int tl,int tr,int p){
	if(tl==tr){
		tree[x]=mp(vis[p],vis[p]);
		return ;
	}
	int mid=(tl+tr)>>1;
	if(p<=mid)modify(ls,tl,mid,p);
	else modify(rs,mid+1,tr,p);
	pushup(x);
}
pii query(int x,int tl,int tr,int l,int r){
	if(tl>=l&&tr<=r)return tree[x];
	int mid=(tl+tr)>>1;
	pii s;
	if(mid>=l&&mid<r){
		pii s=query(ls,tl,mid,l,r);
		pii t=query(rs,mid+1,tr,l,r);
		if(!s.fi || !t.fi)return mp(0,0);
		return merge(s,t);
	}
	else{
		if(mid>=l)return query(ls,tl,mid,l,r);
		return query(rs,mid+1,tr,l,r);
	}
}
#undef ls
#undef rs
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n);
	for(int i=1;i<=n;i++)vis[read(p[i])]=i;
	for(int i=2;i<=n;i++){
		int x;read(x);
		eg[x].pb(i);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,0,n-1);
	int q;read(q);
	while(q--){
		int op;read(op);
		if(op==2){
//			cerr << "ans = ";
			int l=1,r=n-1,mid,ans=1;
			while(l<=r){
				mid=(l+r)>>1;
				pii t=query(1,0,n-1,0,mid);
				if(t.fi){
					ans=mid;
					l=mid+1;
				}
				else{
					r=mid-1;
				}
			}
			cout << ans+1 << '\n';
		}
		else{
			int x,y;read(x,y);
			swap(p[x],p[y]);
			vis[p[x]]=x;vis[p[y]]=y;
			modify(1,0,n-1,p[x]);
			modify(1,0,n-1,p[y]);
		}
	}
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：云浅知处 (赞：3)

妙题。

求一条 $\text{mex}$ 值最大的路径，就相当于求一个最大的前缀 $0,1,2,\cdots,k$ 使得点权为 $0,1,\cdots,k$ 的点都可以被包含在同一条链中。

我们考虑对每个 $i$ 维护点权 $=i$ 的点在树上的编号。考虑用线段树来维护一段区间 $[l,r]$ 是否都在同一条链上。

考虑如何合并区间的信息。对于区间 $[l,m]$ 与区间 $[m+1,r]$：

- 若任意一个区间内的点不构成链，那合起来肯定也不构成链。
- 若两边都构成链，那么我们设两条链的端点分别为 $a,b,c,d$；如果能构成新的链那么端点肯定是这四个中的两个，因此枚举 $C_4^2=6$ 种可能，判断一下剩下两个点是否在这条链上即可。

现在只需要判断一个点是否在一条链上。

这个其实很 simple：注意到 $x$ 在链 $u\to v$ 上的充要条件是 $\text{dist}(x,u)+\text{dist}(x,v)=\text{dist}(u,v)$，因此只需要快速求树上两点间距离即可。使用 $\text{ST}$ 表预处理一下 $\text{LCA}$ 即可。

时间复杂度 $O((n+q)\log n)$。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int MN=4e5+5;
const int MC=20;
vector<int>G[MN];
int dis[MN],dfn[MN],n,q;
pair<int,int>ST[MN][MC];
int Lg[MN];

#define mk make_pair
#define fi first
#define se second

int tot=0;
void dfs(int u,int fa,int de){
	dfn[u]=++tot,ST[tot][0]=mk(de,u);
	for(int v:G[u]){
		if(v==fa)continue;
		dis[v]=dis[u]+1,dfs(v,u,de+1);
		dfn[u]=++tot;ST[tot][0]=mk(de,u);
	}
}

void ST_build(){
	assert(tot==2*n-1);
	for(int i=2;i<=tot;i++)Lg[i]=Lg[i>>1]+1;
	for(int x=1;x<=19;x++){
		for(int i=1;i+(1<<x)-1<=tot;i++)ST[i][x]=min(ST[i][x-1],ST[i+(1<<(x-1))][x-1]);
	}
}

int dist(int u,int v){
	int l=dfn[u],r=dfn[v];
	if(l>r)swap(l,r);int k=Lg[r-l+1];
	int z=min(ST[l][k],ST[r-(1<<k)+1][k]).se;
	return dis[u]+dis[v]-2*dis[z];
}

bool chk(int x,int u,int v){return dist(x,u)+dist(x,v)==dist(u,v);}

int c[MN];

struct Node{
	int x,y,f;
	Node(int X,int Y,int F):x(X),y(Y),f(F){}
	Node(){}
};

#define lson(o) (o<<1)
#define rson(o) (o<<1|1)

struct SegTree{
	Node d[MN<<2];

	inline Node merge(Node ls,Node rs){
		if(ls.f==2)return rs;
		if(rs.f==2)return ls;
		if((!ls.f)||(!rs.f))return Node(0,0,0);
		int p=ls.x,q=ls.y,s=rs.x,t=rs.y;
		if(chk(p,s,t)&&chk(q,s,t))return Node(s,t,1);
		if(chk(p,q,t)&&chk(s,q,t))return Node(q,t,1);
		if(chk(q,p,t)&&chk(s,p,t))return Node(p,t,1);
		if(chk(p,q,s)&&chk(t,q,s))return Node(q,s,1);
		if(chk(q,p,s)&&chk(t,p,s))return Node(p,s,1);
		if(chk(s,p,q)&&chk(t,p,q))return Node(p,q,1);
		return Node(0,0,0);
	}

	inline void pushup(int o){
		d[o]=merge(d[lson(o)],d[rson(o)]);
	}

	inline void build(int l,int r,int o){
		if(l==r){d[o]=Node(c[l],c[l],1);return ;}
		int mid=(l+r)>>1;
		build(l,mid,lson(o)),build(mid+1,r,rson(o));
		pushup(o);
	}

	inline void modify(int pos,Node x,int ql,int qr,int o){
		if(ql==qr){d[o]=x;return ;}
		int mid=(ql+qr)>>1;
		if(pos<=mid)modify(pos,x,ql,mid,lson(o));
		else modify(pos,x,mid+1,qr,rson(o));
		pushup(o);
	}
	
	inline int query(Node x,int ql,int qr,int o){
		if(merge(x,d[o]).f==1)return qr;
		if(ql==qr)return ql-1;
		int mid=(ql+qr)>>1;
		if(!merge(x,d[lson(o)]).f)return query(x,ql,mid,lson(o));
		else return query(merge(x,d[lson(o)]),mid+1,qr,rson(o));
	}
}tree;

int p[MN];

#define OK puts("OK")

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif

	n=read();
	for(int i=1;i<=n;i++)p[i]=read(),c[p[i]+1]=i;
	for(int i=2;i<=n;i++){int f=read();G[i].push_back(f),G[f].push_back(i);}
	dfs(1,0,1);ST_build();tree.build(1,n,1);
	q=read();
	while(q--){
		int op=read();
		if(op==1){
			int x=read(),y=read();
			tree.modify(p[x]+1,Node(y,y,1),1,n,1);
			tree.modify(p[y]+1,Node(x,x,1),1,n,1);
			swap(p[x],p[y]);
		}
		else cout<<tree.query(Node(0,0,2),1,n,1)<<endl;
	}

	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

注意到点权是一个排列，查询 $\operatorname{mex}$ 最大的链即可转化为最大的 $i$ 使得权值为 $0\sim i-1$ 的点在一条链上。

考虑上线段树，维护权值为 $[l,r]$ 的点是否在一条链上/如果在，在的最短的一条链是哪条。

考虑合并，显然如果有一边不在一条链上整个区间就不在一条链上。否则容易发现新的最短的一条链一定是目前两边的链的 $4$ 个端点中的 $2$ 个。只需要判断所有端点是否都在这一条链上即可。可以 LCA+dfs 序解决。

每次查询的时候，在线段树上二分答案即可。

总复杂度 $O(n\log n)$。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline")
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define lowbit(i) (i&(-i))
using namespace std;
vector<int> vc[200005];
int f[200005][18],dep[200005],ind[200005],outd[200005],cnt;
int et[400005],tot,lg[400005],inde[200005],outde[200005];
pair<int,int> rmq[400005][19];
void dfs(int now,int fa){
	dep[now]=dep[fa]+1;
	ind[now]=++cnt;
	et[++tot]=now;
	inde[now]=tot;
	f[now][0]=fa;
	for(int i=1;i<=17;i++) f[now][i]=f[f[now][i-1]][i-1];
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs(v,now);
		et[++tot]=now;
	}
	outd[now]=cnt;
	outde[now]=tot;
}
pair<int,int> comb(pair<int,int> x,pair<int,int> y){
	if(x.first<y.first) return x;
	return y;
}
void precal(){
	for(int i=2;i<=tot;i++) lg[i]=lg[i/2]+1;
	for(int i=1;i<=tot;i++) rmq[i][0]=make_pair(dep[et[i]],et[i]);
	for(int j=1;j<=18;j++) for(int i=1;i+(1<<j)-1<=tot;i++) rmq[i][j]=comb(rmq[i][j-1],rmq[i+(1<<(j-1))][j-1]);
}
int qry(int l,int r){
	int k=lg[r-l+1];
	auto v=comb(rmq[l][k],rmq[r-(1<<k)+1][k]);
	return v.second;
}
int lca(int u,int v,int tag=0){
	if(inde[u]>inde[v]) swap(u,v);
//	cout<<u<<" "<<v<<" "<<qry(inde[u],inde[v])<<"\n";
	return qry(inde[u],inde[v]);
	if(dep[u]>dep[v]) swap(u,v);
	for(int i=17;i>=0;i--) if(dep[f[v][i]]>=dep[u]) v=f[v][i];
//	if(tag==1) cout<<u<<" "<<v<<"\n";
	if(u==v) return u;
	for(int i=17;i>=0;i--) if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	return f[u][0];
}
bool check(int i,int j,int k){
	return ind[i]<=ind[j]&&ind[j]<=ind[k]&&outd[k]<=outd[j]&&outd[j]<=outd[i];
}
pair<int,int> merge(pair<int,int> x,pair<int,int> y){
	if(x.first==-1||y.first==-1) return make_pair(-1,-1);
	if(x.first==0) return y;
	if(y.first==0) return x;
	{
		int l=lca(x.first,x.second);
		if((check(l,y.first,x.first)|check(l,y.first,x.second))&(check(l,y.second,x.first)|check(l,y.second,x.second))) return x;
	}
	{
		int l=lca(y.first,y.second);
		if((check(l,x.first,y.first)|check(l,x.first,y.second))&(check(l,x.second,y.first)|check(l,x.second,y.second))) return y;
	}
	{
		int l=lca(x.first,y.first);
//	if(x.first==3&&x.second==3&&y.first==5&&y.second==5) cout<<"OK"<<l<<" "<<check(l,x.second,x.first)<<" ";
		if((check(l,x.second,x.first)|check(l,x.second,y.first))&(check(l,y.second,x.first)|check(l,y.second,y.first))) return make_pair(x.first,y.first);
	}
	{
		int l=lca(x.first,y.second);
		if((check(l,x.second,x.first)|check(l,x.second,y.second))&(check(l,y.first,x.first)|check(l,y.first,y.second))) return make_pair(x.first,y.second);
	}
	{
		int l=lca(x.second,y.first);
		if((check(l,x.first,x.second)|check(l,x.first,y.first))&(check(l,y.second,x.second)|check(l,y.second,y.first))) return make_pair(x.second,y.first);
	}
	{
		int l=lca(x.second,y.second);
		if((check(l,x.first,x.second)|check(l,x.first,y.second))&(check(l,y.first,x.second)|check(l,y.first,y.second))) return make_pair(x.second,y.second);
	}
	return make_pair(-1,-1);
}
int p[200005];
struct sgt{
	pair<int,int> f[1000005];
	void build(int i,int l,int r){
		if(l==r){
			f[i]=make_pair(p[l],p[l]);
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=merge(f[i*2],f[i*2+1]);
//		cout<<i<<" "<<l<<" "<<r<<" "<<f[i].first<<" "<<f[i].second<<" "<<f[i*2].first<<" "<<f[i*2].second<<" "<<f[i*2+1].first<<" "<<f[i*2+1].second<<"\n";
	}
	void change(int i,int l,int r,int pos){
		if(l==r){
			f[i]=make_pair(p[l],p[l]);
			return ;
		}
		if(pos<=mid) change(i*2,l,mid,pos);
		else change(i*2+1,mid+1,r,pos);
		f[i]=merge(f[i*2],f[i*2+1]);
//		cout<<i<<" "<<l<<" "<<r<<" "<<f[i].first<<" "<<f[i].second<<" "<<f[i*2].first<<" "<<f[i*2].second<<" "<<f[i*2+1].first<<" "<<f[i*2+1].second<<"\n";
	}
	int qry(int i,int l,int r,pair<int,int> ori){
		if(l==r){
			if(merge(ori,f[i]).first!=-1) return l;
			else return l-1;
		}
		auto q=merge(ori,f[i*2]);
		if(q.first!=-1) return qry(i*2+1,mid+1,r,q);
		else return qry(i*2,l,mid,ori);
	}
}tree;
int a[200005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],p[a[i]]=i;
	for(int i=2;i<=n;i++){
		int f; cin>>f;
		vc[f].push_back(i);
	}
	dfs(1,0);
	precal();
	tree.build(1,0,n-1);
	int q; cin>>q;
	while(q--){
		int t; cin>>t;
		if(t==1){
			int i,j; cin>>i>>j;
			swap(a[i],a[j]); p[a[i]]=i,p[a[j]]=j;
			tree.change(1,0,n-1,a[i]);
			tree.change(1,0,n-1,a[j]);
		}
		else{
			cout<<tree.qry(1,0,n-1,make_pair(0,0))+1<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：Lates (赞：0)

由于权值是一个排列，所以对于一个集合 $S$，想要凑出集合 $S$ 中数字的极小的链，是唯一确定的。注意这是指 $S$ 是链所包含权值集合的子集。

那么求解 mex 的最大值，可以二分答案 $mid$，判断区间 $[l,mid]$ 是否可以找的这样一个链。

不妨使用线段树，$[l,r]$ 节点维护两个端点 $a,b$，表示当 $S = [l,r]$ 时，链两端点是啥。

发现由于极小的链唯一确定，两个区间是容易合并的。即判断左右儿子是否可以合并成一条新链。

那么有 4 个节点，新链必须包含至少两个其中的节点。（保持极小的性质）

那么枚举 6 种情况判断剩下两个是否在其形成的链上。

这样可以 $O(k \log n )$ 得到一个区间是否可以全部填充。$k$ 是合并复杂度，大搞是 $6\log n$ 的级别。（或者 RMQ $O(1)$ LCA 能做到更优复杂度，但是可能跑不过树剖 LCA？）

这下上述二分过程就可以执行了。 这里使用线段树上二分就可以再去掉一个 log。

交换点权是 simple 的，线段树做两次单点修改。

时间复杂度 $\mathcal{O}((n+q)k\log n)$。

---

## 作者：I_am_Accepted (赞：0)

我们从值的方面考虑，即类似于二分答案 $\text{mex}(V(l))$。

即：我们要维护对于每一个值 $x\in[0,n)$，$[0,x]$ 这些**点权**对应的点是否可能构成一条链。

由于单点修改，我们考虑**线段树**。

线段树每个节点 $[l,r]$ 维护 $(u,v)$，表示：

{ 包含所有 { **点权在** $[l,r]$ 区间内的点 } 的最短链 } 的两端节点编号。

（拗口，强行断句）

当然若不可能构成链，则 $u=v=-1$（标记为无解）。

由于我们可以 $O(1)$ **“合并”两条链**（见后文解释），所以建树 $O(n)$，单次修改的复杂度为 $O(\log n)$。

查询时在线段树上二分，复杂度也是 $O(\log n)$。

总时间 $O(n+q\log n)$。

* * *

**如何 $O(1)$ 查询两点的 LCA：**

求出树的欧拉序，建 ST 表，两点的 LCA 为两点在欧拉序中之间深度最小的点。

成功转化成 RMQ 问题，$O(1)$。

**如何 $O(1)$ 判断一点 $z$ 是否在 $(x,y)$ 路径上：**

$\text{lca}(z,\text{lca}(x,y))=\text{lca}(x,y)\ \land\ (\text{lca}(z,x)=z\ \lor\ \text{lca}(z,y)=z)$

（可能不需要解释）

**“合并”两条链如何做到 $O(1)$：**

拿来两条链的 $4$ 个端点，$\binom{4}{2}$ 枚举哪两个为合并后的端点，判断剩余两个点是否在两端点间的路径上即可。

* * *

由于合并链的常数较大，请注意常数优化。

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define N 200010
#define C 18
#define pi pair<int,int>
char buf[1<<21],*p1,*p2;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read() {
	int x=0,f=1;
	char c=gc();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=gc();}
	return x*f;
}
int n,q,a[N],b[N],dep[N],L[N],R[N],tim=0,f[C+1][2*N],w[4],lg[2*N];
vector<int> e[N];
pi t[N<<2],v;
void dfs(int rt,int fa){
	dep[rt]=dep[fa]+1;
	L[rt]=++tim;
	f[0][tim]=rt;
	for(int i:e[rt]) dfs(i,rt),f[0][++tim]=rt;
	R[rt]=tim;
}
inline int cmp(int x,int y){ return dep[x]<dep[y]?x:y; }
inline int LCA(int x,int y){
	x=L[x],y=L[y];
	if(x>y) swap(x,y);
	int z=lg[y-x];
	return cmp(f[z][x],f[z][y-(1<<z)+1]);
}
inline bool onl(int x,int y,int z){
	int lca=LCA(x,y);
	return LCA(z,lca)==lca && (LCA(z,x)==z || LCA(z,y)==z);
}
inline pi operator+(pi x,pi y){
	if(x.fir==-1 || y.fir==-1) return mkp(-1,-1);
	w[0]=x.fir,w[1]=x.sec,w[2]=y.fir,w[3]=y.sec;
	For(i,0,3)
		if(onl(w[i],w[(i+1)%4],w[(i+2)%4]) && onl(w[i],w[(i+1)%4],w[(i+3)%4]))
			return mkp(w[i],w[(i+1)%4]);
	For(i,0,1)
		if(onl(w[i],w[(i+2)%4],w[(i+1)%4]) && onl(w[i],w[(i+2)%4],w[(i+3)%4]))
			return mkp(w[i],w[(i+2)%4]);
	return mkp(-1,-1);
}
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid ((l+r)>>1)
void build(int rt,int l,int r){
	if(l==r){
		t[rt]=mkp(b[l],b[l]);
		return ;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	t[rt]=t[ls]+t[rs];
}
void modify(int rt,int l,int r,int id){
	if(l==r){
		t[rt]=mkp(b[l],b[l]);
		return ;
	}
	if(id<=mid) modify(ls,l,mid,id);
	else modify(rs,mid+1,r,id);
	t[rt]=t[ls]+t[rs];
}
int que(int rt,int l,int r){
	pi vv=v+t[rt];
	if(vv.fir!=-1){
		v=vv;
		return r+1;
	}
	if(l==r) return l;
	int res=que(ls,l,mid);
	if(res<=mid) return res;
	else return que(rs,mid+1,r);
}
signed main(){
	n=read();
	For(i,1,n) b[a[i]=read()]=i;
	For(i,2,n) e[read()].pb(i);
	dfs(1,0);
	lg[1]=0; For(i,2,tim) lg[i]=lg[i>>1]+1;
	For(j,0,C-1) For(i,1,tim-(1<<(j+1))+1) f[j+1][i]=cmp(f[j][i],f[j][i+(1<<j)]);
	build(1,0,n-1);
	q=read();
	int x,y;
	while(q--){
		if(read()==1){
			x=read(),y=read();
			swap(a[x],a[y]);
			swap(b[a[x]],b[a[y]]);
			modify(1,0,n-1,a[x]);
			modify(1,0,n-1,a[y]);
		}else{
			v=mkp(b[0],b[0]);
			printf("%d\n",que(1,0,n-1));
		}
	}
return 0;}
```

---

## 作者：DerrickLo (赞：0)

注意到 $\operatorname{mex}\ge x$ 当且仅当点权为 $0\sim x-1$ 的点可以构成一条路径。

所以考虑使用线段树维护。不妨将所有点权都 $+1$，每个区间 $[l,r]$ 维护三元组 $(u,v,x)$，若 $x=0$ 表示点权在 $[l,r]$ 的点不能构成一条路径，若 $x=1$ 则表示点权在 $[l,r]$ 的点可以构成一条路径，而且路径的两个端点为 $u$ 和 $v$。

考虑如何合并两个区间。如果任意一个区间构成不了一条路径，那么合并完的区间显然也构成不了一条路径。如果两个区间都可以构成一条路径，那么我们暴力枚举这两个区间的任意两个端点，然后再判断另外两个点在不在这条路径上即可。

至于如何判断一个点 $x$ 是否在 $u$ 到 $v$ 的路径上是简单的，只需要判断是否 $u$ 和 $v$ 恰好有一个点在 $x$ 的子树里，或者 $x=\operatorname{lca}(u,v)$ 。

这样每次合并就是 $\mathcal O(\log n)$ 的，而对于每次询问可以使用线段树二分。

时间复杂度 $\mathcal O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,p[200005],pos[200005],id[200005],sz[200005],fa[200005],dep[200005],top[200005],son[200005],u,v,cnt,op; 
vector<int>ve[200005];
void dfs1(int u){
	id[u]=++cnt,sz[u]=1,dep[u]=dep[fa[u]]+1;
	for(int v:ve[u]){
		dfs1(v),sz[u]+=sz[v];
		if(sz[v]>sz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp){
	top[u]=tp;
	if(!son[u])return;
	dfs2(son[u],tp);
	for(int v:ve[u]){
		if(v==son[u])continue;
		dfs2(v,v);
	}
}
int lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	return v;
}
bool ck(int u,int v,int x){
	int aa=(id[u]>=id[x]&&id[u]<id[x]+sz[x]),bb=(id[v]>=id[x]&&id[v]<id[x]+sz[x]);
	if(aa^bb)return 1; 
	if(aa==1&&bb==1)if(lca(u,v)==x)return 1;
	return 0;
}
struct tree{
	int l,r,u,v,op;
	friend tree operator+(const tree&a,const tree&b){
		if(a.l==-1)return b;
		tree c;c.l=a.l,c.r=b.r;
		if(a.op==0||b.op==0){c.u=c.v=-1;c.op=0;return c;}
		if(ck(a.u,a.v,b.u)&&ck(a.u,a.v,b.v)){
			c.u=a.u,c.v=a.v,c.op=1;
			return c;
		}
		if(ck(a.u,b.u,a.v)&&ck(a.u,b.u,b.v)){
			c.u=a.u,c.v=b.u,c.op=1;
			return c;
		}
		if(ck(a.u,b.v,a.v)&&ck(a.u,b.v,b.u)){
			c.u=a.u,c.v=b.v,c.op=1;
			return c;
		}
		if(ck(a.v,b.u,a.u)&&ck(a.v,b.u,b.v)){
			c.u=a.v,c.v=b.u,c.op=1;
			return c;
		}
		if(ck(a.v,b.v,a.u)&&ck(a.v,b.v,b.u)){
			c.u=a.v,c.v=b.v,c.op=1;
			return c;
		}
		if(ck(b.u,b.v,a.u)&&ck(b.u,b.v,a.v)){
			c.u=b.u,c.v=b.v,c.op=1;
			return c;
		}
		c.u=c.v=-1,c.op=0;
		return c;
	}
}tr[800005];
void build(int u,int l,int r){
	tr[u].l=l,tr[u].r=r;
	if(l==r){
		tr[u].u=tr[u].v=pos[l],tr[u].op=1;
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	tr[u]=tr[u<<1]+tr[u<<1|1];
	//cout<<"!!! "<<tr[u].l<<" "<<tr[u].r<<" "<<tr[u].u<<" "<<tr[u].v<<" "<<tr[u].op<<"\n";
}
void change(int u,int x){
	if(tr[u].l==tr[u].r){
		tr[u].u=tr[u].v=pos[tr[u].l],tr[u].op=1;
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(x<=mid)change(u<<1,x);
	else change(u<<1|1,x);
	tr[u]=tr[u<<1]+tr[u<<1|1];
}
void query(int u,tree now,int &ans){
	if(tr[u].l==tr[u].r){
		if((now+tr[u]).op==1)ans=max(ans,tr[u].l);
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if((now+tr[u<<1]).op==1){
		ans=max(ans,mid);
		query(u<<1|1,now+tr[u<<1],ans);
	}
	else query(u<<1,now,ans);
} 
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i],p[i]++,pos[p[i]]=i;
	for(int i=2;i<=n;i++)cin>>fa[i],ve[fa[i]].emplace_back(i);
	dfs1(1),dfs2(1,1); 
	build(1,1,n);
	cin>>q;
	while(q--){
		cin>>op;
		if(op==1){
			cin>>u>>v;
			swap(p[u],p[v]),swap(pos[p[u]],pos[p[v]]);
			change(1,p[u]),change(1,p[v]);
		}
		else{
			int ans=0;
			tree now={-1,-1,-1,-1,0};
			query(1,now,ans);
			cout<<ans<<"\n";
		}
	}
}
```

---

## 作者：happybob (赞：0)

很简单的题。

考虑若答案大于等于 $x$，那么点权为 $[0,x)$ 的数必然在树上构成一条路径。

直观想法是考虑二分答案，然后判断 $[0,x)$ 点是否构成一条路径。这个东西可以线段树维护，具体地对 $p$ 的逆排列维护一棵线段树，每个节点维护子树区间是否在一条路径上，以及若在一条路径上那么路径两端点是什么。合并只需要考虑新的两个端点在之前四个端点之中即可。既然上了线段树那自然就不用在外层二分了。直接在线段树上面二分即可。直接用倍增或树剖复杂度为 $O(n \log^2 n)$，使用 ST 表维护欧拉序 RMQ 则可以做到 $O(n \log n)$。

代码：


```cpp
#pragma GCC optimize("-Ofast,fast-math,-inline")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include <array>
#include <print>
#include <format>
using namespace std;

const int N = 2e5 + 5, M = N << 1;

int n, q;
array<int, N> p, rp;
vector<int> G[N];

namespace RMQ
{
	array<int, M> euler, dep;
	array<array<int, 20>, M> f;
	array<int, M> LG2, de;
	int idx;
	array<int, N> pos;
	void dfs(int u, int fa, int d)
	{
		idx++;
		pos[u] = idx;
		de[u] = d;
		dep[idx] = d;
		euler[idx] = u;
		for (auto& j : G[u])
		{
			if (j ^ fa)
			{
				dfs(j, u, d + 1);
				idx++;
				dep[idx] = d, euler[idx] = u;
			}
		}
	}
	void Init()
	{
		for (int i = 2; i < M; i++) LG2[i] = LG2[i >> 1] + 1;
		dfs(1, 0, 1);
		for (int i = 1; i <= idx; i++) f[i][0] = i;
		for (int j = 1; j < 20; j++)
		{
			for (int i = 1; i + (1 << j) - 1 <= idx; i++)
			{
				int x = f[i][j - 1], y = f[i + (1 << (j - 1))][j - 1];
				if (dep[x] < dep[y]) f[i][j] = x;
				else f[i][j] = y;
			}
		}
	}
	int query(int l, int r)
	{
		int p = LG2[r - l + 1];
		int x = f[l][p], y = f[r - (1 << p) + 1][p];
		return (dep[x] < dep[y] ? x : y);
	}
	int LCA(const int& u, const int& v)
	{
		int l = pos[u], r = pos[v];
		if (l > r) swap(l, r);
		return euler[query(l, r)];
	}
	inline int dis(const int& u, const int& v)
	{
		return de[u] + de[v] - 2 * de[LCA(u, v)];
	}
	inline bool check(const int& x, const int& u, const int& v)
	{
		if (x == u || x == v) return 1;
		return dis(x, u) + dis(x, v) == dis(u, v);
	}
};

class SegmentTree
{
public:
	struct Node
	{
		int l, r;
		bool res;
		int nu, nv;
		friend Node operator+(const Node& x, const Node& y) noexcept
		{
			if (x.l == -1) return y;
			if (y.l == -1) return x;
			Node z;
			z.l = x.l, z.r = y.r;
			z.res = z.nu = z.nv = 0;
			z.res = x.res && y.res;
			if (z.res)
			{
				vector<int> ve;
				ve.emplace_back(x.nu);
				ve.emplace_back(x.nv);
				ve.emplace_back(y.nu);
				ve.emplace_back(y.nv);
				int ru = -1, rv = -1;
				for (int i = 0; i < ve.size(); i++)
				{
					for (int j = i; j < ve.size(); j++)
					{
						int x = ve[i], y = ve[j];
						bool tag = 1;
						for (auto& k : ve)
						{
							tag &= RMQ::check(k, x, y);
							if (!tag) break;
						}
						if (tag)
						{
							ru = x, rv = y;
							break;
						}
					}
				}
				if (~ru) z.nu = ru, z.nv = rv;
				else z.res = 0;
			}
			return z;
		}
	};
	array<Node, N << 2> tr;
	void pushup(int u)
	{
		tr[u] = tr[u << 1] + tr[u << 1 | 1];
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, 1, rp[r - 1], rp[r - 1] };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
	void update(int u, int x, int v)
	{
		if (tr[u].l == tr[u].r)
		{
			tr[u].nu = tr[u].nv = v;
			return;
		}
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) update(u << 1, x, v);
		else update(u << 1 | 1, x, v);
		pushup(u);
	}
	int query(int u, Node z)
	{
		if (tr[u].res && (tr[u] + z).res) return -1;
		if (tr[u].l == tr[u].r) return tr[u].l;
		int x = query(u << 1, z);
		if (~x) return x;
		return query(u << 1 | 1, z + tr[u << 1]);
	}
}sgt;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	SegmentTree::Node re;
	re.l = -1;
	for (int i = 1; i <= n; i++) cin >> p[i], rp[p[i]] = i;
	for (int i = 2; i <= n; i++)
	{
		int fa;
		cin >> fa;
		G[fa].emplace_back(i), G[i].emplace_back(fa);
	}
	RMQ::Init();
	sgt.build(1, 1, n);
	cin >> q;
	int lstres = -1;
	while (q--)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			int x, y;
			cin >> x >> y;
			if (!(x ^ y)) continue;
			lstres = -1;
			sgt.update(1, p[x] + 1, y);
			sgt.update(1, p[y] + 1, x);
			swap(p[x], p[y]);
		}
		else
		{
			if (~lstres)
			{
				println("{}", lstres);
				continue;
			}
			int val = sgt.query(1, re);
			if (~val) println("{}", (lstres = val - 1));
			else println("{}", (lstres = n));
		}
	}
	return 0;
}
```

---

