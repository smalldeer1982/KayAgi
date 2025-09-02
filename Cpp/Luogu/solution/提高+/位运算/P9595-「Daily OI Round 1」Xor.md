# 「Daily OI Round 1」Xor

## 题目描述

给定一个长度为 $n$ 的序列，一共有 $q$ 次询问，每次询问给定正整数 $x$，然后依次执行以下操作：

- 把序列中所有数异或上 $x$。
- 求长度最大的区间 $[l,r]$（$l,r$ 是非负整数）满足区间中的每个整数在序列中出现，区间的长度定义为 $r-l+1$。

**注意，在每个询问过后序列是发生变化的。**

**几个需要说明的地方：**

1. “区间”指的是数的区间，比如区间 $[1,3]$ 中的整数有 $1,2,3$，与序列无关。
2. “序列”指的是修改后的序列，同时不包括之前的序列。

## 说明/提示

### **样例解释**

对于第一组样例，序列初始是 $\{1,2,3,4,5\}$，第一次询问给定 $x=1$，则异或后的序列为 $\{0,3,2,5,4\}$。区间 $[2,5]$ 中的每个整数 $2,3,4,5$ 都在这个序列中，这是满足条件的最大区间，所以答案为 $5-2+1=4$。

### **数据范围**

**本题开启捆绑测试。**

| $\text{Subtask}$ | 分值 | $n,q\leq$ | $a_i\leq$ | $x\leq$ |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $10$ | $10^3$ | $10^3$ | $10^3$ |
| $1$ | $20$ | $5\times10^5$ | $10^3$ | $10^3$ |
| $2$ | $10$ | $5\times10^5$ | $10^3$ | $5\times10^5$ |
| $3$ | $60$ | $5\times10^5$ | $5\times10^5$ | $5\times10^5$ |

对于全部数据，保证：$1\leq n,q,a_i,x\leq 5\times10^5$。

## 样例 #1

### 输入

```
5 2
1 2 3 4 5
1
1
```

### 输出

```
4
5```

## 样例 #2

### 输入

```
10 10
5 9 8 3 5 7 10 19 5 24
10
56
19
14
18
53
52
57
96
1000```

### 输出

```
2
2
2
4
2
3
3
2
2
2```

# 题解

## 作者：recollect_i (赞：14)

这篇题解中，我将从线段树的角度重新讲解，同时提出一个扩展。

我们可以用权值线段树维护最长连续段：线段树每个节点维护 $L,R,M,S$ 分别表示这个区间的左边连续段长度、右边连续段长度、最大连续段长度、区间长度，这样就可以实现区间合并。

这样建的线段树如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6bnuksd6.png)

其中橙色线段代表左儿子，蓝色线段代表右儿子，下同。

为了方便后文叙述，“层”从下往上、从 $0$ 开始编号，层的最大编号为 $k$，每一层的节点从 $0$ 开始编号。

考虑一个异或 $x$ 的操作，比如 $x=5$，如果固定底层的节点不变，则线段树会长这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/ggyhxoas.png)

可以发现，实际上是把第 $1$ 层和第 $3$ 层的节点交换左右儿子。

实际上，对于异或 $x$ 的操作，若 $x$ 二进制第 $i$ 位（从低到高，从 $0$ 开始编号）为 $1$，则将线段树第 $i+1$ 层的左右儿子交换。

对于所有的异或 $x$ 的操作，线段树的节点会有很多重合部分，把所有的操作的线段树建出来并合并，则会是这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/0maog4tu.png)

有几个性质：

- 对于第 $i(i>0)$ 层第 $j$ 个节点，它的左儿子是第 $i-1$ 层第 $j$ 个节点，右儿子是第 $i-1$ 层第 $j\bigoplus 2^i$ 个节点，其中 $a\bigoplus b$ 表示 $a$ 和 $b$ 的按位异或。
- 对于第 $k$ 层第 $j$ 个节点，以这个点为根的线段树是异或 $j$ 操作后的线段树。

对于本题，第 $k$ 层节点的 $M$ 值便是答案。

实际上，由于是线段树，它可以维护区间合并。也就是说，下标异或的背景下，可以 $O(\log n)$ 求一般的可以区间合并的区间查询，但不支持快速修改（如图，一个底层节点涉及的节点是 $O(n)$ 的）。

比如有以下问题：

- 这题的基础上可以加一个值域区间的限制。
- 给定长度为 $2^m$ 的序列 $a$，$q$ 次询问给定 $l,r,x$ 求 $\max_{i=l}^r a_{i\bigoplus x}$，$1\leq m \leq 20$，$1\leq q \leq 2^{20}$，$0\leq a_i\leq 10^9$。
- 给定大小为 $n$ 的集合 $a$，$q$ 次询问给定 $x,k$，求 $a$ 里的数异或上 $x$ 后，集合的第 $k$ 小值，$1\leq n,q \leq 2^{20}$，$0\leq a_i\leq 2^{20}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int M = 21, N = 1 << 19 | 5;

int m = 19, n = 1 << m, q, t, x, y;
struct node{
	int l, r, m, p;
}s[2][N];

void pushup(node &u, node &l, node &r)
{
	u.l = l.p ? l.l + r.l : l.l;
	u.r = r.p ? r.r + l.r : r.r;
	u.m = max(l.r + r.l, max(l.m, r.m));
	u.p = l.p & r.p;
}

int main()
{
	scanf("%d%d", &q, &t);
	while(q -- ) scanf("%d", &x), s[0][x] = {1, 1, 1, 1};
	for(int i = 1, x = 1, y = 0; i <= m; i ++ , x ^= 1, y ^= 1)
		for(int j = 0; j < n; j ++ )
			pushup(s[x][j], s[y][j], s[y][j ^ (1 << i - 1)]);
	while(t -- ) scanf("%d", &x), y ^= x, printf("%d\n", s[1][y].m);
	return 0;
}
```

---

## 作者：recollect_i (赞：10)

## subtask0

模拟。先将原序列去重，每个询问进行异或然后重新排序，从前往后遍历数组找合法的区间，更新答案。时间复杂度 $O(n^2\log n)$。

## subtask1

对于每组询问，可以看作是独立地异或前面的 $x$ 的异或和后查询。可以预处理对于所有可能的异或的值的答案。

## subtask2

可以看到对于 $x$，二进制超过 $10$ 位的部分不会影响序列的相对位置，所以只需考虑 $10$ 位。

## subtask3

在 subtask1 的基础上，考虑更快预处理对于所有异或值的答案。

设 $p_i$ 表示原序列是否有 $i$。

把异或值按二进制最后一位分类，对于最后一位是 $1$ 的值，把 $p_{2i}$ 和 $p_{2i+1}$ 交换。

可以发现，这一步之后，$2i,2i+1$ 的相对位置不会改变，所以可以把这两个位置的信息合并。

类似线段树维护最长连续段，设 $l,r,m$ 分别表示左边、右边的连续段长度和最大连续段长度，可以把 $l,r$ 的信息合并到 $u$ 中。

考虑分治，对于第 $i$ 层，分别处理第 $i$ 位是 $0$ 还是 $1$，如果是 $1$，则交换 $2i,2i+1$ 的信息，接着合并 $2i,2i+1$ 的信息，分治到下一层。

如果一共有 $k$ 位，对于第 $i$ 层，会处理 $2^i$ 次，每次的时间复杂度为 $O(2^{k-i})$，则每层的时间复杂度为 $O(2^k)$，一共会分治 $k$ 层，所以总的时间复杂度为 $O(2^kk)$。第 $i$ 层空间复杂度为 $O(2^{k-i})$，所以总空间复杂度可以做到 $O(2^k)$。本题中 $2^{19}>5\times 10^5$，则 $k=19$。

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const int K = 20, N = 1 << 19 | 5;

int n, q, m = 19, x, y;
struct node{
	int l, r, m;
}s[K][N];
int res[N];

void pushup(node &u, node &l, node &r, int k)
{
	u.l = l.l == k ? k + r.l : l.l;
	u.r = r.r == k ? k + l.r : r.r;
	u.m = max(max(l.m, r.m), l.r + r.l);
}
void solve(int k, int p)
{
	if(k == m)
	{
		res[p] = s[k][0].m;
		return ;
	}
	for(int i = 0; i < 1 << m - k - 1; i ++ )
	{
		pushup(s[k + 1][i], s[k][i << 1], s[k][i << 1 | 1], 1 << k);
	}
	solve(k + 1, p);
	for(int i = 0; i < 1 << m - k - 1; i ++ )
	{
		pushup(s[k + 1][i], s[k][i << 1 | 1], s[k][i << 1], 1 << k);
	}
	solve(k + 1, p | 1 << k);
}

int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i ++ )
	{
		scanf("%d", &x);
		s[0][x] = {1, 1, 1};
	}
	solve(0, 0);
	x = 0;
	while(q -- )
	{
		scanf("%d", &y);
		x ^= y;
		printf("%d\n", res[x]);
	}
	return 0;
} 
```

---

## 作者：Usada_Pekora (赞：4)

官方题解还是过于抽象了，来写一个从 01trie 的角度考虑的。

首先考虑如果操作是区间平移应该怎么做，我们是在维护一个 $O(V)$ 的 01 序列，查询连续 1 个数，那就是 scoi 序列操作这个题。

那我们放到 trie 上是差不多的，每次询问合并两个儿子即可，需要记录一个区间长度。

然后你一个修改就往下递归，某一位有 1 就是这一位每个点都交换左右子树，写成暴力大概是这样。

```cpp
inline node merge(node lhs, node rhs, int len) {
	node res;
	res.lmax = (lhs.maxs == len ? len + rhs.lmax : lhs.lmax);
	res.rmax = (rhs.maxs == len ? len + lhs.rmax : rhs.rmax);
	res.maxs = max({lhs.maxs, rhs.maxs, lhs.rmax + rhs.lmax});
	return res;
}
inline void insert(int &p, int x, int dep) {
	if (!p)
		p = ++idx;
	if (dep == 0) {
		t[p].lmax = t[p].rmax = t[p].maxs = 1;
		return;
	}
	if (x >> (dep - 1) & 1)
		insert(ch[p][1], x, dep - 1);
	else
		insert(ch[p][0], x, dep - 1);
	t[p] = merge(t[ch[p][0]], t[ch[p][1]], 1 << (dep - 1));
}
inline void pushdown(int &p, int dep, int x) {
	if (!p)
		return;
	if (dep == 0) {
		t[p].lmax = t[p].rmax = t[p].maxs = 1;
		return;
	}
	if (x >> (dep - 1) & 1)
		swap(ch[p][0], ch[p][1]);
	pushdown(ch[p][0], dep - 1, x), pushdown(ch[p][1], dep - 1, x);
	t[p] = merge(t[ch[p][0]], t[ch[p][1]], 1 << (dep - 1));
}
```

于是考虑优化修改。

发现一次交换要么交换整层的 trie 节点，那我们从下往上合并即可，枚举每一位有没有被 $\operatorname{xor} 1$。

显然从下往上的第 $i$ 层要被合并 $O(2^i)$ 次，合并的复杂度是这一层点数，那么总复杂度就是 $O(V\log V)$。

写起来大概是这样：

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define mkp make_pair
#define lwb lower_bound
#define upb upper_bound
using namespace std;
typedef long long ll;
typedef long double lf;
const int N = 5e5 + 5, mod = 1e9 + 7;
template<typename T> inline bool chkmax(T &x, const T &y) {
	return (x < y) && (x = y, true);
}
template<typename T> inline bool chkmin(T &x, const T &y) {
	return (y < x) && (x = y, true);
}
int idx = 0, rt;
int ch[N * 20][2], fa[N * 20], ans[N << 1];
inline int lowbit(int x) {
	return x & -x;
}
vector<int> tr[23];
struct node {
	int lmax, rmax, maxs;
	node() {
		lmax = rmax = maxs = 0;
	}
} t[N * 20];
inline node merge(node lhs, node rhs, int len) {
	node res;
	res.lmax = (lhs.maxs == len ? len + rhs.lmax : lhs.lmax);
	res.rmax = (rhs.maxs == len ? len + lhs.rmax : rhs.rmax);
	res.maxs = max({lhs.maxs, rhs.maxs, lhs.rmax + rhs.lmax});
	return res;
}
inline void insert(int &p, int x, int dep) {
	if (!p)
		p = ++idx;
	if (dep == 0) {
		t[p].lmax = t[p].rmax = t[p].maxs = 1;
		return;
	}
	if (x >> (dep - 1) & 1)
		insert(ch[p][1], x, dep - 1);
	else
		insert(ch[p][0], x, dep - 1);
	t[p] = merge(t[ch[p][0]], t[ch[p][1]], 1 << (dep - 1));
}
inline void build(int &p, int dep) {
	if (!p)
		p = ++idx;
	tr[dep].pb(p);
	if (dep == 0) 
		return;
	build(ch[p][0], dep - 1), build(ch[p][1], dep - 1);
	fa[ch[p][0]] = fa[ch[p][1]] = p;
} 
inline void solve(int xorval, int dep) {
	if (dep == 19) {
		ans[xorval] = t[rt].maxs;
		return;
	}
//	assert(tr[dep].size() == lowbit(tr[dep].size()));
//	cerr << dep << ' ' << tr[dep].size() << '\n';
	for (int i = 0; i + 1 < tr[dep].size(); i += 2) {
		int u = tr[dep][i], v = tr[dep][i + 1];
		t[fa[u]] = merge(t[u], t[v], 1 << dep);
	}
	solve(xorval, dep + 1);
	for (int i = 0; i + 1 < tr[dep].size(); i += 2) {
		int u = tr[dep][i], v = tr[dep][i + 1];
		t[fa[u]] = merge(t[v], t[u], 1 << dep);
	}
	solve(xorval | (1 << dep), dep + 1);
}
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int n, q, x;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> x;
		insert(rt, x, 19);
	}
	build(rt, 19);
//	return 0;
//	for (int i = 0; i <= 20; i++)
//		cerr << tr[i].size() << '\n';
//	return 0;
	solve(0, 0);
	int xorval = 0;
	while (q--) {
		cin >> x;
		xorval ^= x;
		cout << ans[xorval] << '\n';
	}
	return 0;
}
```

---

## 作者：一只绝帆 (赞：3)

看到异或先想是线性基还是 $\text{Trie}$。

很明显排除线性基，用 $\text{Trie}$。

先考虑单组询问，我们发现值连续的节点在 $\text{Trie}$ 上的位置也是连续的，形如一个线段树求最大子段和。

那么带异或询问怎么办呢，异或的本质是 $\text{Trie}$ 上交换子树，要么本层子树全部交换要么不交换，而我们一共就只有 $2^{19}$ 种交换可能，考虑全部处理出来。

发现一棵子树只需要 $2^{19-dep_x}$ 的空间（根节点 $dep=0$），开一个动态数组，总空间复杂度每层 $2^{19}$，是 $O(2^{B}B)$。

处理的过程非常简单，自下而上，枚举二进制时只需要关心最高位是否需要交换分类讨论即可。

Code：
```cpp
#include<bits/stdc++.h>
#define gc getchar
#define F(i,a,b) for(int i(a),i##end(b);i<=i##end;i++)
#define ne nxt[x][v>>(B-i-1)&1]
#define n0 nxt[x][0]
#define n1 nxt[x][1]
using namespace std;
int read() {
	int s=0;char c=gc(),w=0;
	while(c<'0'||c>'9') w|=c=='-',c=gc();
	while(c>='0'&&c<='9') s=s*10+(c^48),c=gc();
	return w?-s:s;
} const int B=19,N=(1<<B)*5+5,C=(1<<B)*80;
int *pre[N],*suf[N],*mx[N],buf[C],*BUF=buf+(C-1),lst;
int *alloc(int sz) {return BUF-=sz;}
int n,q,nxt[N][2],snt,dep[N];
void ins(int v) {
	int x=0;F(i,0,B-1) {
		if(!ne) dep[ne=++snt]=dep[x]+1;
		x=ne;
	}
}
void sol(int x) {
	if(dep[x]==B) return pre[x][0]=suf[x][0]=mx[x][0]=1,void();
	n0&&(sol(n0),0);n1&&(sol(n1),0);
	for(int i=0;i<(1<<B-dep[x]);i++) {
		if((i>>B-dep[x]-1)&1) {
			#define j i^(1<<B-dep[x]-1)
			mx[x][i]=max(max(mx[n0][j],mx[n1][j]),suf[n1][j]+pre[n0][j]);
			pre[x][i]=pre[n1][j]+pre[n0][j]*(pre[n1][j]==(1<<B-dep[x]-1));
			suf[x][i]=suf[n0][j]+suf[n1][j]*(suf[n0][j]==(1<<B-dep[x]-1)); 
			#undef j
		} else {
			mx[x][i]=max(max(mx[n0][i],mx[n1][i]),suf[n0][i]+pre[n1][i]);
			pre[x][i]=pre[n0][i]+pre[n1][i]*(pre[n0][i]==(1<<B-dep[x]-1));
			suf[x][i]=suf[n1][i]+suf[n0][i]*(suf[n1][i]==(1<<B-dep[x]-1));
		}
	}
}
int main() {
	n=read();q=read();
	F(i,1,n) ins(read());
	F(i,0,snt) pre[i]=alloc(1<<B-dep[i]),suf[i]=alloc(1<<B-dep[i]),mx[i]=alloc(1<<B-dep[i]);
	sol(0);
	F(i,1,q) printf("%d\n",mx[0][lst^=read()]);
	return 0;
}

```

---

## 作者：MaxBlazeResFire (赞：2)

一场只有神题的比赛，无限膜拜出题组。

~~但官方题解写得还是太抽象了，于是我决定自己来写一篇重述一下官方的做法。~~

记 $p_i$ 表示 $i$ 是否存在。将序列转化为一个值域上的 $01$ 桶。那么一次操作 $x$ 等价于 $\forall i,p_i\leftarrow p_{i\oplus x}$。

有一个性质：操作 $x\oplus y$ 等价于先操作 $x$ 再操作 $y$，反之亦然。

对于前者，$p_i$ 最终变为 $p_{i\oplus (x\oplus y)}$；对于后者，$p_{i\oplus y}$ 被 $p_{(i\oplus y)\oplus x}$ 转移之后又转移给 $p_i$，故性质正确。

首先将询问看成每次独立异或上之前所有操作的异或和，从而预处理每一种询问的答案。

考察一次操作 $X$，由上述性质，我们将它拆解成二进制下每位相加的形式，将问题转化为每次单独异或一个形如 $2^k$ 的数，而这个操作就变得比较朴素了。

取本题的最大值域为 $K=19,N=2^K$。建立一棵分治值域线段树，共 $20$ 层，从下往上分别为第 $0,1,2,\cdots K$ 层。第 $i$ 层有 $2^{K-i}$ 个长度为 $2^i$ 的区间，从左往右编号 $0,1,2,\cdots,2^{K-i}-1$，编号为 $j$ 的区间掌管值域区间 $[j\times 2^i,(j+1)\times 2^i-1]$。一开始时，我们把 $p$ 桶的信息扔到第 $0$ 层的 $N$ 个节点上，然后 **对于每一层的每个区间，维护不包含 $0$ 的最大子段和。**

考虑异或 $2^0$ 带来的变化。相当于最 $0$ 层 **所有** 编号为偶数与编号为奇数的相邻两个节点的信息对换。如果异或 $2^1$ 呢？我们发现（模 $4$ 意义下）$0,1$ 的信息原封不动地搬到了 $2,3$ 的位置，$2,3$ 的信息原封不动地搬到了 $0,1$ 的位置。换句话说，我们可以先进行一次节点合并上推，再对换第 $1$ 层 **所有** 编号为偶数与编号为奇数的相邻两个节点的信息。

如果异或 $2^0+2^1$ 呢？可以先在第 $0$ 层进行一次大对换，上传，再对第 $1$ 层进行一次大对换。

于是我们得到了求异或任意值 $X$ 时答案的方法：将 $X$ 二进制位分解，从低向高位考虑，如果为 $0$ 就直接上传，为 $1$ 就整层互换后再上传。

我们发现，在第 $k$ 层不对换可以处理所有在第 $k$ 位为 $0$ 的 $X$ 的答案，反之可以处理所有在第 $k$ 位为 $1$ 的 $X$ 的答案。那么可以从底向上跑一个带回溯的 $\rm dfs$，先不对换，直接上传所有节点，求得所有第 $i$ 位为 $0$ 的答案；向下回溯到第 $i$ 层后对一整层做 $2^{K-i-1}$ 次相邻节点的对换，求得所有第 $i$ 位为 $1$ 的答案。复杂度分析：第 $i$ 层会被 $\rm dfs$ 到 $2^i$ 次，每被 $\rm dfs$ 到一次进行 $2$ 轮（对换与不对换）$2^{K-i-1}$ 次的上传，每层的复杂度为 $O(2^K)=O(N)$，总复杂度就是 $O(KN)=O(N\log N)$。

推到最上层的时候记录当前的最大子段和即可。注意，由于我们要维护值域上的非 $0$ 最大连续段，这里的最大子段和要把 $0$ 当作 $-\infty$ 看。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 550005
#define INF 1e12

const int MAXK = 19;
int n,q,buc[MAXN],Ans[MAXN];

struct node{ int L,R,sum,msum; }T[MAXK + 1][MAXN];

inline node push_up( node l , node r ){
	node res;
	res.sum = l.sum + r.sum;
	res.L = max( l.L , l.sum + r.L );
	res.R = max( r.R , r.sum + l.R );
	res.msum = max( max( l.msum , r.msum ) , l.R + r.L );
	return res;
}

void merge( int floor , int V ){
	if( floor == MAXK ){ Ans[V] = T[MAXK][0].msum; return; }
	for( int i = 0 ; i < 1 << ( MAXK - floor - 1 ) ; i ++ )
		T[floor + 1][i] = push_up( T[floor][i << 1] , T[floor][i << 1 | 1] );
	merge( floor + 1 , V );
	for( int i = 0 ; i < 1 << ( MAXK - floor - 1 ) ; i ++ )
		T[floor + 1][i] = push_up( T[floor][i << 1 | 1] , T[floor][i << 1] );
	merge( floor + 1 , V + ( 1 << floor ) );
}

signed main(){
	scanf("%lld%lld",&n,&q);
	for( int i = 1 ; i <= n ; i ++ ){ int x; scanf("%lld",&x),buc[x] ++; }
	for( int i = 0 ; i < ( 1 << MAXK ) ; i ++ ){
		int t = buc[i] ? 1 : -INF;
		T[0][i] = node{ t , t , t , t };
	}
	merge( 0 , 0 );
	int X = 0;
	for( int i = 1 ; i <= q ; i ++ ){
		int x; scanf("%lld",&x); X ^= x;
		printf("%lld\n",Ans[X]);
	}
	return 0;
}
```

---

