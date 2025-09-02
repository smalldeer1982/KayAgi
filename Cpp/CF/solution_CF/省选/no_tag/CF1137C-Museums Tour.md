# Museums Tour

## 题目描述

一个国家有 $n$ 个城市，通过 $m$ 条单向道路相连。有趣的是，在这个国家，每周有 $d$ 天，并且每个城市恰好有一个博物馆。

已知每个博物馆一周的营业情况（开门或关门）和 $m$ 条单向道路，由于道路的设计，每条道路都需要**恰好一个晚上**的时间通过。你需要设计一条旅游路线，使得从首都：$1$ 号城市开始，并且当天是本周的第一天。每天白天，如果当前城市的博物馆**开着门**，旅行者可以进入博物馆参观展览，否则什么也做不了，这一天的晚上，旅行者要么结束行程，要么通过一条道路前往下一个城市。当然，旅行者**可以多次经过一个城市**。

要求让旅行者能够参观的**不同**博物馆数量尽量多（同一个城市的博物馆参观多次仅算一次），请你求出这个最大值。

## 样例 #1

### 输入

```
4 5 3
3 1
1 2
2 4
4 1
2 3
011
110
111
001
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 3 7
1 2
1 3
2 3
1111111
0000000
0111111
```

### 输出

```
2
```

# 题解

## 作者：zhoukangyang (赞：14)

## 蒟蒻语
本来不到 $1$ 小时就写出来了, 数组却清空错了 QAQ

$\Huge \text{sto sjy orz}$

## 蒟蒻解

考虑到每一天博物馆开放情况是不相同的, 可以把每一个博物馆一周的每一天的情况存下来, 第 $u$ 个博物馆 $k$ 天的编号是 $u + (k-1)n$。每一条边　$(u, v)$, 对于 $\forall x \in [1, d]$, 连一条 $(u + (x - 1) n, v + (x \mod d) n + v)$ 的边。

现在每一个点都对应着一个博物馆和一周中的某一天。

最后要求的是从 $1$ 号点出发, 能到达几个开着博物馆。

首先先缩点。

**两个对应相同博物馆的要么缩完之后在统一个点, 要么不联通**

如何证明呢？sjy 说很简单。 

假设第 $u$ 天对应的点能到第 $v$ 天对应的点 (不妨 $v > u$), 所以这个博物馆经过 $v - u$ 天可以返回到自己。因此 $lcm(n, v - u) - (v - u)$ 天后还是可以返回到这个博物馆。 $lcm(u, v - u) - v - u \equiv (v - u)\pmod{n}$。

所以第 $v$ 天对应的点可以到达 $v-u$ 天前对应的点。所以第 $v$ 天对应的点可以到达第 $u$ 天到达的点。

---
所以现在只要先缩点, 然后统计一下缩了之后的点里面有多少种不同的 博物馆开门的状态， 最后跑一遍最长路就好了。

## 蒟蒻码

```
#include<bits/stdc++.h>
#define N 100010
#define M 5000010
#define L(i, j, k) for(int i = j; i <= k; i++)
#define R(i, j, k) for(int i = j; i >= k; i--)
using namespace std;
bitset<M> vis, used;
bitset<N> day[55];
// bool [M];

int n, m, d, low[M], dfn[M], tot, bh[M], cnt, stot, st[M], dp[M], val[M];
int head[M], edge_id;
struct node {
    int to, next;
} e[M];

void add_edge(int u, int v) { // 加边
    ++edge_id, e[edge_id].next = head[u], e[edge_id].to = v, head[u] = edge_id;
}

int gw(int x) { return (x - 1) % n + 1; } // 找这是哪一个点
int gd(int x) { return (x - 1) / n + 1; } // 找这是哪一天

inline void dfs(int x) { // tarjan 缩点, 已经手写栈了 QAQ
    low[x] = dfn[x] = ++tot, st[++stot] = x, vis[x] = 1;
    for(int i = head[x]; i; i = e[i].next) {
        int v = e[i].to;
        if(!dfn[v]) dfs(v), low[x] = min(low[x], low[v]);
        else if(vis[v]) low[x] = min(low[x], dfn[v]);
    }
    if(low[x] == dfn[x]) {
        int now = stot, pp;
        ++cnt;
        while(st[now] != x) {
            pp = st[now], bh[pp] = cnt, vis[pp] = 0, --now;
            if(!used[gw(pp)] && day[gd(pp)][gw(pp)]) 
                used[gw(pp)] = 1, val[cnt]++;
        }
        bh[x] = cnt, vis[x] = 0, --now;
        if(!used[gw(x)] && day[gd(x)][gw(x)]) used[gw(x)] = 1, val[cnt]++;
        L(i, now, stot) used[gw(st[i])] = 0;
        stot = now;
    }
}

int hd[M], eid;
struct ndeo {
    int to, next;
} g[M];

void ad_edge(int u, int v) { // 加边
    ++eid, g[eid].next = hd[u], g[eid].to = v, hd[u] = eid;
}

inline int DFS(int x) { // DFS 找最长路
    if(vis[x]) return dp[x];
    for(int i = hd[x]; i; i = g[i].next) dp[x] = max(DFS(g[i].to), dp[x]);
    vis[x] = 1, dp[x] += val[x];
    return dp[x];
}

void rebuild() { // 缩点后建图
    L(i, 1, n * d) for(int j = head[i]; j; j = e[j].next) {
        int v = e[j].to;
        if(bh[i] != bh[v]) ad_edge(bh[i], bh[v]);
    }
}

char s[55];
int main() {
    scanf("%d%d%d", &n, &m, &d);
    L(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        L(j, 1, d) add_edge(n * (j - 1) + u, n * (j % d) + v); // 连边
    }
    L(i, 1, n) {
        scanf("%s", s + 1);
        L(j, 1, d) day[j][i] = (s[j] == '1');
    }
    L(i, 1, n * d) if(!dfn[i]) dfs(i);
    rebuild();
    vis.reset();
    printf("%d\n", DFS(bh[1])); 
    return 0;
}
```

---

## 作者：Rainbow_qwq (赞：12)

[CF1137C Museums Tour
](https://www.luogu.com.cn/problem/CF1137C)

---

# 思路

分层图 & 强连通缩点。

注意一些要点：

1. 只要能走，旅行者可以走无数天。
2. 一周 $d$ 天的开放是循环的。

于是我们可以想到拆点，把一个点 $u$ 拆成 $[u,0],[u,1],\dots,[u,d-1]$，这样每个点的博物馆对应一个确定的状态 开/关。

对于原图上的边 $u\to v$ ，拆成 $d$ 条边 $[u,i]\to [v,(i+1)\bmod d] (0\le i\le d-1)$ ，相当于今天的 $u$ 向明天的 $v$ 连边。

然后从 $[1,0]$ 开始跑一次最长路就可以了？不行，图上还有环。

于是想到 Tarjan 缩点，每个强连通分量的点权为 **这个强连通分量中开启的不同博物馆个数**。

缩点后形成一个 DAG 就可以直接 dfs 求最长路了。

Q: 会不会重复统计相同博物馆？

不会的，假设 $[u,i]$ 与 $[u,j]$ 在不同强连通分量且 $[u,i]$ 可到 $[u,j]$ ，那么从 $[u,j]$ 也能走到 $[u,i]$ 。

upd:上面那句话的证明如下：

如果存在 $[i,a]\to [i,a+x]$ ，那么
$[i,a+x]\to[i,a+x+x]$ ， 以此类推 $[i,a+x]\to [i,(a+x*d)\ \bmod \ d]$

而 $[i,(a+x*d)\ \bmod \ d]$ 就是 $[i,a]$

也就是说 如果 $[i,a]\to [i,a+x]$ ，那么
$[i,a+x]\to[i,a]$

时间/空间复杂度 $O(nd)$ 。

这题思路还是挺顺的（

# 代码

有点难写，还要注意不被卡空间（

注意：计算点权的时候，vis 数组不能 memset 。

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
#define maxn 100005
#define N 100005*50
int n,m,k;
long long sta[maxn];

struct edge{
	int to,nxt;
}e[N],e2[N];
int tot,tot2,head[N],head2[N];
inline void adde(int u,int v){
	e[++tot]=(edge){v,head[u]};
	head[u]=tot;
}
inline void adde2(int u,int v){
	e2[++tot2]=(edge){v,head2[u]};
	head2[u]=tot2;
}

int idx,scc,bel[N],dfn[N],low[N];
int f[N],val[N];
bool ins[N],vis[N];
stack<int>s,q;
inline void tarjan(int u){
	dfn[u]=low[u]=++idx;
	ins[u]=1;s.push(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(ins[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]!=dfn[u])return;
	++scc;int v; 
	do{
		v=s.top();s.pop();
		ins[v]=0,bel[v]=scc;
		int x=(v-1)%n+1,day=(v-1)/n;
      // x:哪个城市
      // day:哪天
		if(!vis[x] && (sta[x]>>day&1)){
			val[scc]++,vis[x]=1;
			q.push(x);
		}
	}while(u!=v);
	while(!q.empty())vis[q.top()]=0,q.pop();
}

inline int P(int i,int j){
	return j*n+i;
}
//dfs 最长路
int dfs(int u)
{
	if(vis[u])return f[u];
	vis[u]=1;
	for(int i=head2[u];i;i=e2[i].nxt){
		int v=e2[i].to;
		f[u]=max(f[u],dfs(v));
	}
	return f[u]+=val[u];
}

int main()
{
	n=read(),m=read(),k=read();
	For(i,1,m){
		int u=read(),v=read();
		For(j,0,k-1)adde(P(u,j),P(v,(j+1)%k));
	}
	char ch;
	For(i,1,n)
		For(j,0,k-1){
			while(!isdigit(ch=getchar()));
			sta[i]|=1ll*(ch-'0')<<j;
		}

	tarjan(1);
	
	For(i,1,n*k)
	{
		if(!dfn[i])continue;
		int u=bel[i];
		for(int j=head[i];j;j=e[j].nxt){
			int v=e[j].to;
			if(!dfn[v])continue;
			v=bel[v];
			if(u!=v)adde2(u,v);
		}
	}
	cout<<dfs(bel[1]);
    return 0;
}
```

---

## 作者：小粉兔 (赞：6)

本题解节选自我的博客园文章[CodeForces Contest #1137: Round #545 (Div. 1)](https://www.cnblogs.com/PinkRabbit/p/CF1137.html)。

### 题意简述：

一个 $n$ 个点 $m$ 条边的简单有向图，一周有 $d$ 天。

每个点都有一个博物馆，给出博物馆 $i$ 在一周的第 $j$ 天的开门情况（$1\le i\le n$，$1\le j\le d$）。

这周的第 $1$ 天，你从 $1$ 号点开始，每次走一条边需要花费 $1$ 天，如果当前点的博物馆开着，你就可以进去游览。

问在足够长的时间后，你最多可以游览多少个不同的博物馆（一个点的博物馆游览多次只算一次）。

### 题解：

有两种做法，一种比较简单，一种比较复杂，我写的是复杂的。

考虑 $\mathrm{f}[i][j]$ 表示一周的第 $j$ 天在 $i$ 号点，最终能游览多少个博物馆。

但是图上有环，转移比较困难。于是考虑强连通分量缩点。这样形成一个 DAG。

观察可以得到，一个缩点后的强连通分量，是拥有自己的“周期”的，即若第 $j$ 天在这个强连通分量中，第 $j+x$ 天也能在同一个点上，最小的正整数 $x$ 便是周期。

这个周期一定是 $d$ 的因数，因为 $d$ 是所有强连通分量的总周期，周期可以这样计算：

- 周期 $\mathrm{period}$ 初始化为 $d$。

- 考虑这个强连通分量的 DFS 树，记录每个点的深度 $\mathrm{dep}$。

- 对于每一条边 $u\to v$，令 $\mathrm{period}=\gcd(\mathrm{period},\mathrm{dep}[u]-\mathrm{dep}[v]+1)$。

关于证明，只能感性理解。

这之后就可以 DP 了，DP 的状态变为 $\mathrm{f}[i][j]$ 表示 $i$ 号强连通分量中的时间戳为 $j$ 的答案。

因为涉及到强连通分量内所有点的时间戳，需要对每个强连通分量设置一个基准时间戳以便互相转化，所幸我们可以用 $\mathrm{dep}\bmod \mathrm{period}$ 来当作节点的相对时间戳，基准时间戳为 $0$。

DP 时需要处理一个 $\mathrm{cnt}[j]$ 数组表示当强连通分量时间戳为 $j$ 时这个强连通分量内开启的不同博物馆个数。DP 时要格外注意不同强连通分量中时间戳的转换。

时间复杂度 $\mathcal{O}((n+m)d)$。

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>

const int MN = 100005, MD = 55;

int N, M, D;
std::vector<int> G[MN], T[MN];
char s[MD]; int w[MN][MD];

int dfn[MN], low[MN], stk[MN], instk[MN], tp, dfc;
int dep[MN], bel[MN], per[MN], tic[MN], itic[MN], bcnt;
void Tarjan(int u) {
	low[u] = dfn[u] = ++dfc;
	stk[++tp] = u, instk[u] = 1;
	for (auto v : G[u]) {
		if (!dfn[v]) {
			dep[v] = dep[u] + 1, Tarjan(v);
			low[u] = std::min(low[u], low[v]);
		}
		else if (instk[v]) low[u] = std::min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		++bcnt;
		for (int x = 0; x != u; --tp) {
			x = stk[tp];
			bel[x] = bcnt;
			T[bcnt].push_back(x);
			instk[x] = 0;
		}
	}
}

int f[MN][MD];

int main() {
	scanf("%d%d%d", &N, &M, &D);
	for (int i = 1; i <= M; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
	}
	for (int i = 1; i <= N; ++i)
		if (!dfn[i]) dep[i] = 1, Tarjan(i);
	for (int i = 1; i <= bcnt; ++i) per[i] = D;
	for (int u = 1; u <= N; ++u)
		for (auto v : G[u]) if (bel[u] == bel[v])
			per[bel[u]] = std::__gcd(per[bel[u]], std::abs(dep[u] - dep[v] + 1));
	for (int i = 1; i <= N; ++i)
		tic[i] = dep[i] % per[bel[i]], itic[i] = tic[i] ? per[bel[i]] - tic[i] : 0;
	for (int i = 1; i <= N; ++i) {
		scanf("%s", s);
		for (int j = 0; j < D; ++j) w[i][j] = s[j] - '0';
	}
	for (int id = 1; id <= bcnt; ++id) {
		int pr = per[id];
		static int cnt[MD];
		for (int j = 0; j < pr; ++j) cnt[j] = 0;
		for (int j = 0; j < pr; ++j) {
			for (auto u : T[id]) for (int k = 0; k < D; k += pr)
				if (w[u][(k + tic[u] + j) % D]) { ++cnt[j]; break; }
		}
		for (int j = 0; j < pr; ++j) {
			f[id][j] = cnt[j];
			for (auto u : T[id]) {
				int ticv = (j + tic[u] + 1) % pr;
				for (auto v : G[u]) if (bel[v] != id) {
					for (int k = 0; k < D; k += pr)
						f[id][j] = std::max(f[id][j], cnt[j] + f[bel[v]][(itic[v] + k + ticv) % per[bel[v]]]);
				}
			}
		}
	}
	printf("%d\n", f[bel[1]][itic[1]]);
	return 0;
}

// 19-03-10 00:18 ~ 19-03-10 00:54
```

而相对简单的做法是，将每个点在一周的每天拆成不同的点。这样有 $n\times d$ 个点，每个点记作 $\langle u,j\rangle$ 即 $u$ 号点在第 $j$ 天拆出的点（$1\le u\le n$，$0\le j<d$）。每个点的权值为 $0$ 或 $1$，取决于当天此点的博物馆是否开启。

对于一条边 $u\to v$，将其拆成 $d$ 条边，连接 $\langle u,j\rangle$ 和 $\langle v,(j+1)\bmod d\rangle$。

这样再强连通分量缩点后，形成一个 DAG。每个缩点后的强连通分量权值为这个强连通分量中开启的不同博物馆个数，直接求最长路即可。

为什么不会重复统计？考虑重复统计的情况，即存在一条路径使得 $\langle u,j_1\rangle$ 可以到达 $\langle u,j_2\rangle$ 但不在同一个强连通分量中，这是不可能的，因为单独看这条路径经过的顶点编号序列，沿着这个序列再重复走 $d-1$ 遍一定能回到 $\langle u,j_1\rangle$。这意味着如果同一顶点拆出的两点弱连通，它们必然也强连通，所以不需要担心重复统计的情况。

代码就不给了，比较简单。不过这个做法似乎空间翻好几番，要小心处理。

---

## 作者：wjyyy (赞：3)

好题。

我们考虑把每一天拆成 $d$ 个点，令第 $i$ 号点在第 $j$ 天的点为 $[i,j]$。存在 $\left<i,v\right>$，则让 $[i,j]$ 向 $[v,j\bmod d+1]$ 连边。

**注意：博物馆不开放仅代表不做出贡献，不代表那天不能去那个城市。因此连边不能省。**

然后我们可以在这个有向无环图上跑 tarjan 缩点。

可以证明，在新的 DAG 上的任意一条链中，**原图**的每个点只会出现在一个强连通分量里。

- 在连边后的图上，如果原图中的点 $[i,j]$ 向 $[i,k]$ 有连边，那么 $[i,k]$ 一定向 $[i,j]$ 有连边。因此在路径上可能出现的原图同一个点的新点都会被缩到同一个强连通分量里。

因此我们可以计算每个 SCC 的贡献。当给出的矩阵中 $[i,j]$ 为 $1$ 时则做出 $1$ 的贡献，$i$ 相同的不重复统计。

然后计算从 $[1,1]$ 开始的权值最长路。拓扑排序可以完成。

但是由于一共有 $5\times 10^6$ 个点，递归~~可能~~会爆栈，因此我写的非递归（码量有点大但是不是很难写）。

## Code：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>

struct edge
{
    int from,n,nxt;
    edge(int from,int n,int nxt)
    {
        this->from=from;
        this->n=n;
        this->nxt=nxt;
    }
    edge(){}
    friend bool operator ==(edge a,edge b)
    {
        return a.from==b.from&&a.n==b.n;
    }
    friend bool operator <(edge a,edge b)
    {
        if(a.from!=b.from)
            return a.from<b.from;
        return a.n<b.n;
    }
}e[5000000];
int head[5000100],ecnt=-1;
void add(int from,int to)
{
    e[++ecnt]=edge(from,to,head[from]);
    head[from]=ecnt;
}
int dfn[5000100],low[5000100],cnt=0,del[5000100],dcnt=0;
int f[5000100],sz[5000100],cur[5000100];
int stk[5000100],tp=0,d,stk_[5000100],tp_=0;
bool in[5000100],used[5000100];
bool ava[5000100];
void tarjan(int x)
{
    stk[++tp]=x;
    cur[x]=-1;
    while(tp)
    {
        x=stk[tp];
        if(x==7)
        {
            int o;
            o=1;
        }
        if(cur[x]==-1)
        {
            cur[x]=head[x];
            dfn[x]=++cnt;
            low[x]=dfn[x];
            in[x]=1;
            stk_[++tp_]=x;
        }
        else
        {
            low[x]=low[x]<low[e[cur[x]].n]?low[x]:low[e[cur[x]].n];
            cur[x]=e[cur[x]].nxt;
        }

        if(cur[x]!=-1)
        for(int i=cur[x];~i;cur[x]=i=e[i].nxt)
            if(!dfn[e[i].n])
            {
                stk[++tp]=e[i].n;
                cur[e[i].n]=-1;
                break;
            }
            else if(in[e[i].n])
                low[x]=low[x]<dfn[e[i].n]?low[x]:dfn[e[i].n];

        if(cur[x]==-1)
        {
            if(low[x]==dfn[x])
            {
                ++dcnt;
                int b=tp_;
                do
                {
                    if(ava[stk_[tp_]]&&!used[(stk_[tp_]-1)/d+1])
                    {
                        ++sz[dcnt];
                        used[(stk_[tp_]-1)/d+1]=1;
                    }
                    del[stk_[tp_]]=dcnt;
                    in[stk_[tp_--]]=0;
                }while(stk_[tp_+1]!=x);
                for(int i=tp_+1;i<=b;++i)
                    used[(stk_[i]-1)/d+1]=0;
            }
            --tp;
        }
    }
}
int D[5000100],q[5000100],l=0,r=0;

char s[100];
int main()
{
    memset(head,-1,sizeof(head));
    int n,m,u,v;
    scanf("%d%d%d",&n,&m,&d);

    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&u,&v);
        for(int j=1;j<=d;++j)
            add((u-1)*d+j,(v-1)*d+j%d+1);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%s",s+1);
        for(int j=1;j<=d;++j)
            if(s[j]=='1')
                ava[(i-1)*d+j]=1;
    }
    for(int i=1;i<=n*d;++i)
        if(!dfn[i])
            tarjan(i);
    for(int i=0;i<=ecnt;++i)
    {
        e[i].from=del[e[i].from];
        e[i].n=del[e[i].n];
    }
    std::sort(e,e+ecnt+1);
    std::unique(e,e+1+ecnt);
    int t=ecnt;
    for(int i=0;i<ecnt;++i)
        if(e[i]<e[i+1]==false)
        {
            t=i;
            break;
        }
    ecnt=-1;
    memset(head,-1,sizeof(head));
    for(int i=0;i<=t;++i)
        if(e[i].n!=e[i].from)
        {
            ++D[e[i].from];
            add(e[i].n,e[i].from);
        }

    for(int i=1;i<=dcnt;++i)
        if(!D[i])
            q[++r]=i;
    while(l<r)
    {
        int x=q[++l];
        f[x]+=sz[x];
        for(int i=head[x];~i;i=e[i].nxt)
        {
            --D[e[i].n];
            f[e[i].n]=f[e[i].n]>f[x]?f[e[i].n]:f[x];
            if(!D[e[i].n])
                q[++r]=e[i].n;
        }
    }
    printf("%d\n",f[del[1]]);
    return 0;
}
```

---

## 作者：Rainybunny (赞：2)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.org/problem/CF1137C).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先膜一下各位有金勾勾的巨佬们的题解救回了我放弃掉的思路$w$.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;为了方便描述, 我们假设一周$d$天从第$0$天开始, 第$d-1$天结束.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;拿到题目, 第一反应是建分层图, 第$i$层的$n$个点表示星期$i$的博物馆状态 ( $0/1$ ). 那么在连接一条实际的边$<s,t>$时, 就是对于所有星期$i$, 第$i$层的$s$向"明天"的$t$连边. 我们对这个大小为$n\times d$的图缩点后, 将每个点的权值令为该点内开放博物馆的数量, 貌似求一条最长链就行了.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;那么问题来了, 是否会出现对于同一博物馆的重复计算呢?  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;具体来说, 是否存在一个博物馆$u$和一星期中不同的两天$i,j$, 星期$i$的博物馆$u$和星期$j$的博物馆$u$同时对答案产生贡献? 这种情况有是否能避免? 我们设$u_i$表示星期$i$的博物馆$u$, 对$u_i,u_j$分类讨论:
### 1) $u_i,u_j$属于同一$SCC$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这种情况可能出现, 却容易避免. 我们在求一个$SCC$的点权时, 标记已经产生贡献的结点, 就不会重复统计了.
### 2) otherwise
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~鉴于难以判断掉重复, 这种情况就一定不存在.~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;的确, 在$u_i,u_j$不属于同一$SCC$时, 它们不可能同时贡献答案. 反之, 假设$u_i$先产生贡献, 那么必然存在一条路径$P<u_i,...,u_j>$. 回归到原图, 就意味着存在一个包含$u$的环, 设其包含$t$个结点, 则应有:
$$
j\equiv i+kt\pmod{d}
$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其中$k\in\mathbb{N}\cap\lbrack 0,d)$. 上式变换可得:
$$
i\equiv j+(d-k)t\pmod{d}
$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这意味着, 同样存在$k'\in\mathbb{N}\cap\lbrack0,d)$, 使得从$u_j$开始, 沿着环转$k'$圈后回到$u_i$, 那么$<u_i,u_j>$与$<u_j,u_i>$同时存在, 这与$u_i,u_j$不属于同一$SCC$相矛盾.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;那么问题便迎刃而解, 缩点之后再$DAG$上跑一边最长链的$DP$即可.  
## 代码
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$tips$: 注意控制空间, "#define int long long"啥的就没有必要了. 用来标记产生贡献的数组利用惰性清除法, 保证均摊$O(nd)$.
```cpp
#include <queue>
#include <stack>
#include <cstdio>
#include <cstring>

#define Int register int

using namespace std;

typedef long long int LL;

const int MAXN = 1e5, MAXM = 1e5, MAXD = 50, MAXND = MAXN * MAXD;
int n, m, d, Cnte, CprC, Indx, Cnts, Head[MAXND + 5] = {}, CprH[MAXND + 5] = {};
int DFN[MAXND + 5] = {}, Low[MAXND + 5] = {}, SCC[MAXND + 5] = {}, Val[MAXND + 5] = {}, F[MAXND + 5] = {};
LL Status[MAXN + 5] = {};
bool Instk[MAXND + 5] = {}, Appear[MAXN + 5] = {};
stack<int> S;
queue<int> Appr;

struct Edge { int To, _nxt; } Graph[MAXND + 5] = {}, CprG[MAXND + 5] = {};

inline int Min ( const int a, const int b ) { return a < b ? a : b; }

inline int Max ( const int a, const int b ) { return a > b ? a : b; }

inline void Link ( const int From, const int To ) {
	Graph[++ Cnte] = { To, Head[From] };
	Head[From] = Cnte;
}

inline void CprLink ( const int From, const int To ) {
	CprG[++ CprC] = { To, CprH[From] };
	CprH[From] = CprC;
}

inline void Tarjan ( const int u ) {
	int v;
	DFN[u] = Low[u] = ++ Indx, Instk[u] = true, S.push ( u );
	for ( Int i = Head[u]; i; i = Graph[i]._nxt ) {
		if ( ! DFN[v = Graph[i].To] ) {
			Tarjan ( v ), Low[u] = Min ( Low[u], Low[v] );
		} else if ( Instk[v] ) {
			Low[u] = Min ( Low[u], DFN[v] );
		}
	}
	if ( DFN[u] == Low[u] ) {
		++ Cnts;
		do {
			v = S.top (); S.pop (), Instk[v] = false;
			SCC[v] = Cnts;
			if ( ! Appear[( v - 1 ) % n + 1] && ( Status[( v - 1 ) % n + 1] >> ( v - 1 ) / n ) & 1 ) {
				++ Val[Cnts], Appear[( v - 1 ) % n + 1] = true, Appr.push ( ( v - 1 ) % n + 1 );
			}
		} while ( v ^ u );
		for ( ; ! Appr.empty (); Appear[Appr.front ()] = false, Appr.pop () );
	}
}

inline void MakeGraph () {
	for ( Int i = 1; i <= d * n; ++ i ) {
		if ( ! DFN[i] ) continue;
		int u = SCC[i], v;
		for ( Int j = Head[i]; j; j = Graph[j]._nxt ) {
			if ( ! DFN[Graph[j].To] ) continue;
			if ( u ^ ( v = SCC[Graph[j].To] ) ) CprLink ( u, v );
		}
	}
}

inline void DFS ( const int u ) {
	if ( F[u] ) return ;
	for ( Int i = CprH[u], v; i; i = CprG[i]._nxt ) {
		DFS ( v = CprG[i].To ), F[u] = Max ( F[u], F[v] );
	}
	F[u] += Val[u];
}

inline void Work () {
	scanf ( "%d %d %d", &n, &m, &d );
	for ( Int i = 1, s, t; i <= m; ++ i ) {
		scanf ( "%d %d", &s, &t );
		for ( Int j = 0; j ^ d; ++ j ) Link ( j * n + s, ( j + 1 ) % d * n + t );
	}
	for ( Int i = 1; i <= n; ++ i ) {
		char str[MAXD + 5] = {}; scanf ( "%s", str );
		for ( Int j = 0; j ^ d; ++ j ) Status[i] |= 1LL * ( str[j] ^ '0' ) << j;
	}
	Tarjan ( 1 );
	MakeGraph ();
	DFS ( SCC[1] );
	printf ( "%d\n", F[SCC[1]] );
}

int main () {
	Work ();
	return 0;
}
```

---

## 作者：libra9z (赞：2)

### [原题描述](https://www.luogu.org/problemnew/show/CF1137C)

~~这是一个贼难的Div1的C题。。。~~

考虑把每一个城市拆成$D$个节点，分别为每一个城市一周每一天。这样一共会有$N*D$个节点。

接着在原来每一个道路连接的两个城市拆成的$D$个城市分别建有向边，
即：如果原来$A$到$B$有一条边，就对$(A_1, B_2), (A_2, B_3), ..., (A_d-1, B_d), (A_d, B_1)$这些节点对分别建有向边。

接着在建好的图上强连通缩点。
每一个缩点之后的$DAG$的点权即是有多少个节点是$Open$的。

在缩完点之后的$DAG$中跑一次最长路就能 **$\color{green} \text{Accepted}$** 了。

呃呃呃$……$ 不是 **$\color{green} \text{Accepted}$** ，而是  **$\color{red} \text{Memory Limit Exceed}$** 。

原因是这题太卡空间了$……$
所以，要想办法优化空间。

首先，不能用$STL$的$vector$存边，会 **$\color{red} \text{Memory Limit Exceed on test 10}$** 。

所以药用**链式向星式**存边。

接着，珂以把输入的$string$转化成$bool$数组。

再把$bool$数组转化成$bitset$就珂以优化很多空间。

于是，这样就珂以 **$\color{green} \text{Accepted}$** 了。

最后献一下蒟蒻的 **$\color{green} \text{Accepted}$** 代码：
```cpp
// Code By H~S~C

//#define __FILE_JUDGE

#ifdef ONLINE_JUDGE
#define __ONLINE_OPTIMIZE
#else
#define __DEBUG
#endif

#define __SINGLE_TEST
//#define __MUlTIPUL_TEST

#ifdef __ONLINE_OPTIMIZE
#pragma comment(linker, "/STACK:1024000000,1024000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#if __cplusplus >= 201103L
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#else
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <tr1/tuple>
#endif
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cstdarg>
#include <vector>
#include <memory>
#include <bitset>
#include <cstdio>
#include <stack>
#include <queue>
#include <deque>
#include <cmath>
#include <ctime>
#include <list>
#include <set>
#include <map>
using namespace std;
#if __cplusplus < 201103L
using namespace tr1;
#endif

#define rep(i, n) for (int i = 0; i < (n); ++ i)
#define rep1(i, n) for (int i = 1; i <= (n); ++ i)
#define Rep(i, a, b) for (int i = (a); i <= (b); ++ i)
#define repit(it, a) for (__typeof(a.begin()) it = a.begin(); it != a.end(); it ++)
#define MP make_pair
#define All(a) a.begin(), a.end()
#define SZ(a) ((int)a.size())
#define sqr(s) ((s) * (s))
#define fillset(a, val) memset(a, val, sizeof(a))
#define fi first
#define se second
#define endl '\n'
#define FILEOPEN(f) freopen(f".in", "r", stdin); \
                    freopen(f".out", "w", stdout)

typedef long long ll;
typedef unsigned long long ull;
typedef long long llong;
typedef unsigned long long ullong;
typedef long double ld;
typedef pair <int, int> pii;
#ifndef __linux__
typedef unsigned long long hash_type;
#else
typedef unsigned __int128 ulllong;
typedef __int128 lllong;
typedef ulllong hash_type;
#endif

#ifndef __DEBUG
#define Debug(...)
#else
#if __cplusplus >= 201103L
template <typename T> inline void _debug(const char* names, T && t) {
  (cerr << names << " = " << t << endl).flush();
}
template <typename T1, typename ...T>
inline void _debug(const char* names, T1 && t1, T && ... t) {
  const char* comma = strchr(names, ',');
  (cerr.write(names, comma - names) << " = " << t1 << ", ").flush();
  _debug(comma + 1, t ...);
}
#define Debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define Debug(x) cerr << #x << " = " << x << '\n'
#define Debug(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << '\n'
#define Debug(x, y, z) cerr << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << '\n'
#endif
#endif

template <typename T>
inline void chmax(T &x, T y) { x = max(x, y); }
template <typename T>
inline void chmin(T &x, T y) { x = min(x, y); }

const int inf = 0x3f3f3f3f;
const ll lnf = 0x3f3f3f3f3f3f3f3f;
const double EPS = 1e-9, PI = acos(-1.0);
const int mod1 = 1000000007, mod2 = 998244353;

bool solve(const int &CASENUM);
signed main(int argc, const char *argv[]) {
#ifdef ONLINE_JUDGE
  cerr << "Program by H~S~C: \n";
#endif
#ifdef __FILE_JUDGE
  FILEOPEN(__FILE__);
#endif
  ios_base :: sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
#ifdef __SINGLE_TEST
  solve(1);
#elif defined(__MUlTIPUL_TEST)
  int Tests = 1; while (!solve(Tests ++));
#else
  int Tests, Test; cin >> Tests; for (Test = 1; Test <= Tests; ++ Test) solve(Test);
#endif
  return 0;
}
// TODO XXX starts HERE!!

const int Maxn = 100005;
const int Maxd = 5e6 + 5;

int n, m, d, nn, ans;
bitset <55> grid[Maxn];
int dfn[Maxd], low[Maxd], instk[Maxd], scc[Maxd];
int index_ = 0, cnt = 0, st[Maxd], top;
struct Edge {
  int to, next;
}ng[Maxd], g[Maxd];
int nghead[Maxd], ghead[Maxd];
int ngcnt, gcnt;
inline void add_edge_g(int u, int v) {
  g[++ gcnt] = (Edge) {v, ghead[u]};
  ghead[u] = gcnt;
}
inline void add_edge_ng(int u, int v) {
  ng[++ ngcnt] = (Edge) {v, nghead[u]};
  nghead[u] = ngcnt;
}
vector <int> has[Maxd];
int dp[Maxd], val[Maxd];

inline void tarjan(int u);
bool solve(const int &CASENUM){
  memset(scc, -1, sizeof scc);
  cin >> n >> m >> d;
  rep(i, m) {
    int u, v;
    cin >> u >> v; -- u, -- v;
    rep(i, d) add_edge_g(u * d + i, v * d + (i + 1) % d);
  } nn = n * d;
  rep(i, n) {
    string s;
    cin >> s;
    rep(j, SZ(s))
      grid[i][j] = s[j] - '0';
  }
  rep(i, nn) if (!dfn[i]) tarjan(i);
  rep(i, cnt) {
    sort(All(has[i]));
    int last = -1;
    rep(j, SZ(has[i])) {
      int v = has[i][j];
      if (v / d != last)
        if (grid[v / d][v % d])
          ++ val[i], 
          last = v / d;
    }
  }
  rep(u, nn) {
    for (int j = ghead[u]; j; j = g[j].next) {
      int v = g[j].to;
      if (scc[u] == scc[v]) continue;
      add_edge_ng(scc[u], scc[v]);
    }
  }
  rep(u, cnt) {
    dp[u] = val[u];
    for (int i = nghead[u]; i; i = ng[i].next)
      dp[u] = max(dp[u], val[u] + dp[ng[i].to]);
  }
  printf("%d\n", dp[scc[0]]);
  return false;
}

void tarjan(int x) {
  low[x] = dfn[x] = ++ index_;
  st[++ top] = x; instk[x] = 1;
  for (int i = ghead[x]; i; i = g[i].next)
    if (!dfn[g[i].to])
      tarjan(g[i].to), 
      low[x] = min(low[x], low[g[i].to]);
    else if (instk[g[i].to])
      low[x] = min(low[x], dfn[g[i].to]);
  if (dfn[x] == low[x]) {
    while (st[top] ^ x)
      has[scc[st[top]] = cnt].push_back(st[top]), 
      instk[st[top --]] = 0;
    has[scc[st[top]] = cnt].push_back(st[top]);
    instk[st[top --]] = 0, cnt ++;
  }
}
```


---

## 作者：Mirasycle (赞：1)

把一个拆成 $d$ 个点，分别代表在一周之内的某一天到达某个博物馆。对于原图的一条边 $(u,v)$，连边 $(u,x)\to (v,(x+1)\bmod d)$

先 tarjan 一下，求出每个 scc 之内有几个博物馆，然后直接跑最长路 dp 就行了。

看似可能会在两个 scc 中统计到相同的博物馆。但是其实一个博物馆的两个状态不可能只有单向可达性，假如 $(x,0)\to (x,a)$，那么 $(x,a)\to (x,a+a)$，以此类推可以得到 $(x,a)\to (x,a\times d)$，在模 $d$ 的意义下就是 $(x,0)$，所以二者在同一 scc 中只会被统计一次。

时间复杂度 $O((n+m)d)$

---

## 作者：DerrickLo (赞：1)

容易想到，可以把一个博物馆拆成 $d$ 个点，每个点表示第 $i$ 天这个博物馆，那么对于每条边 $(u,v)$，可以对于每天由今天的 $u$ 连向明天的 $v$。

然后进行缩点，每个强连通分量缩成点后的点值可以就是这个这个强连通分量不同博物馆的数量，然后跑个最长路就行了。

注意不能使用 `vector` 存图。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,d,u[100005],v[100005],low[5000005],dfn[5000005],st[5000005],top,cnt,cntt,fr[5000005],vl[5000005],ins[5000005],vis[5000005],aa[5000005],dis[5000005],head1[5000005],head2[5000005],cnt1,cnt2;
long long vv[100005];
struct ee{
	int nxt,to;
}edge1[5000005],edge2[5000005];
void add1(int u,int v){
	edge1[++cnt1]={head1[u],v};
	head1[u]=cnt1;
}
void add2(int u,int v){
	edge2[++cnt2]={head2[u],v};
	head2[u]=cnt2;
}
string s;
inline int get(int a,int b){
	return a*n+b;
}
inline void tarjan(int u){
	dfn[u]=low[u]=++cnt,st[++top]=u,ins[u]=1;
	for(int i=head1[u];i;i=edge1[i].nxt){
		int v=edge1[i].to;
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(ins[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		cntt++;
		int nowcnt=0;
		do{
			fr[st[top]]=cntt;
			ins[st[top]]=0;
			long long xx=(st[top]-1)%n+1,yy=(st[top]-1)/n;
			if(!vis[xx]&&(vv[xx]&(1ll<<yy)))vis[xx]=1,vl[cntt]++,aa[++nowcnt]=xx;
		}while(st[top--]!=u);
		for(int i=1;i<=nowcnt;i++)vis[aa[i]]=0;
	}
}
inline void dfs(int u){
	if(vis[u])return;
	vis[u]=1;
	for(int i=head2[u];i;i=edge2[i].nxt){
		int v=edge2[i].to;
		dfs(v);
		dis[u]=max(dis[u],dis[v]); 
	}
	dis[u]+=vl[u];
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>d;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
		for(int j=0;j<d;j++)add1(get(j,u[i]),get((j+1)%d,v[i]));
	}
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=0;j<s.size();j++)vv[i]+=(1ll<<j)*(s[j]-'0');
	} 
	for(int i=1;i<=n*d;i++)if(!dfn[i])tarjan(i);
	for(int i=1;i<=m;i++)for(int j=0;j<d;j++){
		int uu=fr[get(j,u[i])],vv=fr[get((j+1)%d,v[i])];
		if(uu==vv)continue;
		add2(uu,vv);
	}
	dfs(fr[1]);
	cout<<dis[fr[1]];
	return 0;
}
```

---

## 作者：lfxxx (赞：1)

考虑把每个点进行拆成 $d$ 个点表示星期几走到这个点，那么原图上的边 $(u,v)$ 就被拆成$(pos_{u,i},pos_{v,i+1})$ 表示星期的变化。

然后考虑进行缩点，在一个强连通分量内的同一个博物馆只能被计算一次？

那要是一个博物馆出现在两个强连通分量内呢？

可以证明这种情况不会出现，因为边 $(pos_{u,i},pos_{v,j})$ 和边 $(pos_{v,j},pos_{u,k})$ 代表原图中存在边 $(u,v)$ 与 $(v,u)$ 且类似的可以证明一个博物馆拆成的点一定在一个强连通分量中，那么接下来计算强连通分量内的贡献，拓扑排序后跑一遍最长路即可。

```cpp
// LUOGU_RID: 122368344
#include<bits/stdc++.h>
#define pos(i,j)((i-1)*d+j-1)
using namespace std;
int n,d,m;
const int maxn = 1e5*51+1;
struct Node{
	int v,to;
}e1[maxn<<1],e2[maxn<<1];
int tot1,tot2;
int head[maxn][2];
void add1(int u,int v){
	e1[++tot1].v=v;
	e1[tot1].to=head[u][0];
	head[u][0]=tot1;
}
void add2(int u,int v){
	e2[++tot2].v=v;
	e2[tot2].to=head[u][1];
	head[u][1]=tot2;
}
int dfncnt,vis[maxn],dfn[maxn],low[maxn],color,col[maxn];
bitset<maxn> point;
stack<int> st;
void tanjan(int u){
	st.push(u);
	vis[u]=1;
	low[u]=dfn[u]=++dfncnt;
	for(int i=head[u][0];i;i=e1[i].to){
		int v=e1[i].v;
		if(dfn[v]==0){
			tanjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v]==1){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]){
		++color;
		while(st.top()!=u){
			col[st.top()]=color;	
			vis[st.top()]=0;
			st.pop();
		}
		col[u]=color;
		vis[u]=0;
		st.pop();
	}
}
void bfs(){//处理从 1 号节点出发可以抵达的点 
	for(int i=1;i<=color;i++) low[i]=0; 
	queue<int> q;
	q.push(col[pos(1,1)]);
	while(q.size()>0){
		int u=q.front();
		q.pop();
		for(int i=head[u][1];i;i=e2[i].to){
			int v=e2[i].v;
			low[v]++;
			if(low[v]==1) q.push(v);
		}
	}
}
unordered_map<int,int> use[100001];
void build(){//处理缩点后的连边 
	for(int u=pos(1,1);u<=pos(n,d);u++){
		for(int i=head[u][0];i;i=e1[i].to){
			int v=e1[i].v;
			int U=col[u],V=col[v];
			if(U==V) continue;
			add2(U,V);
		}
	}
	for(int i=1;i<=color;i++) vis[i]=0;
	for(int u=pos(1,1);u<=pos(n,d);u++){
		if(point[u]==1&&use[u/d][col[u]]==0){
			vis[col[u]]++;
			use[u/d][col[u]]=1;
		}
	}
}
int answer;
void topo(){
	queue<int> q;
	for(int i=1;i<=color;i++) dfn[i]=-1000000;
	dfn[col[pos(1,1)]]=vis[col[pos(1,1)]];
	q.push(col[pos(1,1)]);
	while(q.size()>0){
		int u=q.front();
		q.pop();
		for(int i=head[u][1];i;i=e2[i].to){
			int v=e2[i].v;
			dfn[v]=max(dfn[v],dfn[u]+vis[v]);
			low[v]--;
			if(low[v]==0) q.push(v);
		}
	}
	for(int i=1;i<=color;i++) answer=max(answer,dfn[i]);
}  
int main(){
	cin>>n>>m>>d;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		for(int j=1;j<=d;j++) add1(pos(u,j),pos(v,j%d+1));
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=d;j++){
			char c;
			cin>>c;
			point[pos(i,j)]=c-'0';
		}
	}
	for(int i=pos(1,1);i<=pos(n,d);i++) if(dfn[i]==0) tanjan(i);
	build();
	bfs();
	topo();
	cout<<answer<<'\n';
}
```


---

## 作者：MortisM (赞：1)

> [CF1137C Museums Tour](https://codeforces.com/problemset/problem/1137/C)

这道题就是卡空间限制比较紧的题，卡了好久才卡进去。

这个题看上去像一个最长路的问题，但是不同于最长路的有 2 点：
+ 每个点不是所有时间访问都可以的
+ 图有可能有环

对于第一个问题，需要用到一个小技巧：把一个点分成 $d$ 个点，这样每个新建出来的点就可以代表节点编号和访问时间了。连边方案就是原图上有一条边 $(u,v)$，则新图就将 $(u,0)\rightarrow (v,1),(u,1)\rightarrow (v,2),...,(u,d-2)\rightarrow (v,d-1),(u,d-1)\rightarrow (v,0)$ 连起来，这样第一个问题就解决了。

对于第二个问题，经典的套路就是 Tarjan 缩点，缩点完的点权就是在这个点里的原图的点的个数。需要注意的是，同一个点不同时间访问只算一次，而且这个时间访问必须合法。

后面跑一个最长路就可以了，时间复杂度 $O(nd)$，题目时间宽松，可以较容易地通过。

**关于卡空间：**

这道题的空间只有 `512MB`，然后你需要记录：
+ 原图信息
+ Tarjan 中的信息（时间戳、维护栈等）
+ 缩点后的图的信息
+ 最长路的 DP 数组

然后你发现这个是开不下的，所以要进行一些空间的优化。我的优化有：
+ 用链式前向星存图
+ 栈使用 STL 的（我也不知道为什么，但是加上就对了）
+ 求最长路不用拓扑排序，而使用 DFS（就可以不用维护队列了）

这样就可以 AC 了。

[代码](https://codeforces.com/contest/1137/submission/170153725)

```cpp
#include<bits/stdc++.h>
//#define JERRY_JIANG
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
inline int read() {
	int x = 0;
	bool f = 0;
	char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return f ? -x : x;
}
inline void print(int x) {
	if(x < 0) return putchar('-'), print(-x);
	if(x >= 10) print(x / 10);
	putchar(x % 10 + '0');
}
bool Memst;
constexpr int N = 1e5 + 10, D = 55;
int n, m, d, val[N * D], col[N * D], dp[N * D];
ll sta[N];
int dfn[N * D], low[N * D], tim = 0, tp = 0, tp2 = 0, scc = 0;
bool instk[N * D], vis[N];
int head1[N * D], t1[N * D], nxt1[N * D], head2[N * D], t2[N * D], nxt2[N * D], tot1 = 0, tot2 = 0;
stack<int> stk, stk2;
void addEdge1(int u, int v) {
	nxt1[++tot1] = head1[u]; head1[u] = tot1; t1[tot1] = v;
}
void addEdge2(int u, int v) {
	nxt2[++tot2] = head2[u]; head2[u] = tot2; t2[tot2] = v; 
}
void tarjan(int x) {
	dfn[x] = low[x] = ++tim;
	stk.push(x); instk[x] = 1;
	for(int i = head1[x]; i; i = nxt1[i]) {
		int to = t1[i];
		if(!dfn[to]) {
			tarjan(to); low[x] = min(low[x], low[to]);
		}
		else if(instk[to]) low[x] = min(low[x], dfn[to]);
	}
	if(dfn[x] == low[x]) {
		int cur; scc++;
		do {
			cur = stk.top(); stk.pop(); instk[cur] = 0; col[cur] = scc;
			int x = cur / d, day = cur % d;
			if(!vis[x] && ((sta[x] >> day) & 1)) {
				vis[x] = 1; val[scc]++; stk2.push(x);
			}
		} while(cur != x);
		while(!stk2.empty()) {vis[stk2.top()] = 0; stk2.pop();}
	}
}
int dfs(int x) {
	if(vis[x]) return dp[x];
	vis[x] = 1;
	for(int i = head2[x]; i; i = nxt2[i]) {
		int to = t2[i];	dp[x] = max(dp[x], dfs(to));
	}
	return dp[x] += val[x];
}
bool Memed;
int main(){
	fprintf(stderr, "%.3lf MB\n", (&Memst - &Memed) / 1048576.0);
	#ifdef JERRY_JIANG
		FILE *IN = freopen("wd.in", "r", stdin);
		FILE *OUT = freopen("wd.out", "w", stdout);
	#endif
	cin >> n >> m >> d;
	int u, v;
	for(int i = 1; i <= m; i++) {
		cin >> u >> v;
		--u, --v;
		for(int j = 0; j < d; j++) {
			addEdge1(u * d + j , v * d + (j + 1) % d);
		}
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < d; j++) {
			char ch = getchar();
			while(!isdigit(ch)) ch = getchar();
			if(ch == '1') sta[i] |= (1LL << j);
		}
	}
	tarjan(0);
	for(int i = 0; i < n * d; i++) if(dfn[i]) {
		for(int j = head1[i]; j; j = nxt1[j]) {
			int to = t1[j]; if(!dfn[to]) continue;
			if(col[i] != col[to]) addEdge2(col[i], col[to]);
		}
	}
	cout << dfs(col[0]) << '\n';
	#ifdef JERYY_JIANG
		fprintf(stderr, "%.3lf ms\n", TIME);
	#endif
	return 0;
}
/*
author: Jerry_Jiang
start coding at 30/08/22 17:00
finish debugging at 30/08/22 20:09
*/
```

---

## 作者：daniEl_lElE (赞：0)

将每个点拆为 $d$ 个点，分别表示 $t\bmod d=j$（$t$ 为时间）到达 $i$ 点的情况。将其表示为 $(i,j)$。

建图，缩点。缩点后显然会形成一个 DAG。

观察到任意两个 $(i,j)$ 和 $(i,k)$ 要么在同一个强连通分量里面，要么互相不可抵达。感性理解的话，如果 $(i,j)$ 可达 $(i,k)$ 且不在同一个强联通分量，设 $(k-j)\bmod d=x$，则 $(i,j)$ 可达 $(i,(j+x)\bmod d),(i,(j+2x)\bmod d),\dots,(i,j+(j+dx)\bmod d)$。注意到 $(i,(j+dx)\bmod d)$ 就是 $(i,j)$，于是 $j$ 与 $k$ 就在同一个强连通分量里了。

于是对于缩点后的每个点计算有多少个城市的博物馆能在相应时间内开门，DAG 上跑最长链即可。

总复杂度 $O(nd)$。注意空间。[注意 dfs 要加 inline](https://www.luogu.com.cn/discuss/785043)。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;
int h[6000005],to[6000005],lst[6000005],totp;
void add(int u,int v){
	totp++;
	lst[totp]=h[u];
	to[totp]=v;
	h[u]=totp;
}
bool open[200005][55];
// vector<int> vc[5000005];
int dfn[5000005],low[5000005],cnt,stk[5000005];
bool ins[5000005];
int top,bel[5000005],tot,val[5000005],deg[5000005];
bool vis[5000005];
int maxlen[5000005];
int rem[5000005],ne;
inline void dfs(int now){
	dfn[now]=low[now]=++cnt;
	stk[++top]=now; ins[now]=1;
	for(int i=h[now];i;i=lst[i]){
		int v=to[i];
		if(!dfn[v]) dfs(v);
		if(ins[v]) low[now]=min(low[now],low[v]);
	}
	if(low[now]==dfn[now]){
		tot++;
		while(stk[top]!=now){
			ins[stk[top]]=0;
			bel[stk[top]]=tot;
			top--;
		}
		ins[stk[top]]=0;
		bel[stk[top]]=tot;
		top--;
	}
}
signed main(){
	int n,m,d,tag=0; cin>>n>>m>>d;
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		if(i==1&&u==20590&&v==17720){
			tag=1;
		}
		for(int j=0;j<d;j++){
			add((u-1)*d+j,(v-1)*d+((j+1)%d));
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<d;j++){
			char c; cin>>c;
			open[i][j]=(c-'0');
		}
	}
	for(int i=0;i<n*d;i++) if(!dfn[i]) dfs(i);
	for(int i=1;i<=n;i++){
		for(int j=0;j<d;j++){
			if(open[i][j]){
				if(!rem[bel[(i-1)*d+j]]) rem[bel[(i-1)*d+j]]=1,val[bel[(i-1)*d+j]]++;
			}
		}
		for(int j=0;j<d;j++) rem[bel[(i-1)*d+j]]=0;
	}
	for(int i=0;i<n*d;i++){
		for(int j=h[i];j;j=lst[j]){
			int v=to[j];
			if(bel[i]!=bel[v]) dfn[++ne]=bel[i],low[ne]=bel[v];
		}
	}
	for(int i=0;i<n*d;i++) h[i]=to[i]=lst[i]=0; totp=0;
	for(int i=1;i<=ne;i++){
		add(dfn[i],low[i]);
	}
	queue<int> q; q.push(bel[0]); vis[bel[0]]=1;
	while(!q.empty()){
		int f=q.front(); q.pop();
		for(int i=h[f];i;i=lst[i]){
			int v=to[i];
			deg[v]++;
			if(vis[v]) continue;
			vis[v]=1;
			q.push(v);
		}
	}
	for(int i=0;i<n*d;i++) if(!deg[i]) deg[i]=1e9;
	q.push(bel[0]); maxlen[bel[0]]=0;
	int maxv=0;
	while(!q.empty()){
		int f=q.front(); q.pop();
		maxlen[f]+=val[f];
		maxv=max(maxv,maxlen[f]);
		for(int i=h[f];i;i=lst[i]){
			int v=to[i];
			deg[v]--;
			maxlen[v]=max(maxlen[v],maxlen[f]);
			if(!deg[v]) q.push(v);
		}
	}
	cout<<maxv;
	return 0;
}
```

---

