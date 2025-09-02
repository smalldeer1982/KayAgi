# [Celeste-B] No More Running

## 题目背景

> 逃离自己内心的人，

> 永远也到达不了顶峰。

> 想要到达山顶，你能做的只有

> 不再逃避

## 题目描述

通往山顶的路上水晶遍布。

在晶簇中，Madeline 发现了一个不同寻常的水晶洞穴，洞穴中镶嵌着五彩斑斓的宝石。

经过 Madeline 的观察，她发现这些宝石形成了一个奇妙的机关，只要让宝石收集到足够的魔力，就能打开机关，拿到水晶之心。

具体来说，在这个巨大的洞穴里有着 $n$ 颗宝石，每颗宝石都被镶嵌在**形态结构完全相同**但**相互独立**的树形结构里。更具体地，在这个洞穴里有 $n$ 个相同的树形结构 $T$，树形结构 $T$ 有 $n$ 个节点，而第 $i$ 颗宝石被镶嵌到了第 $i$ 个树形结构 $T$ 的第 $i$ 号节点上。

Madeline 能够推动宝石从而让宝石在树形结构上滑动。当宝石滑过树形结构的一条边**过后**，这条边就会被关闭，并且边上储存的魔力就会被积蓄到宝石中。(再次提醒，这 $n$ 颗宝石所在的树形结构是相互独立的，这意味着在一个树形结构中一条边的封闭并不会导致在其他树形结构中这条边也被封闭)

宝石能储存的魔力是有上限的，更具体而言，每颗宝石都只能储存 $mod$ 的魔力，一旦超过这个魔力上界，宝石的魔力就会溢出，你可以认为宝石此时储存的魔力会对 $mod$ 取模。

Madeline 想要知道，镶嵌在每个顶点上的宝石最终最多能储存多少魔力，你能帮帮她吗？

## 说明/提示

![图挂了](https://i.loli.net/2019/08/30/sPwyQKUDANRCT2f.png)

"特殊约定" 中，"一条链"意味着树形结构的第 $i$ 条边连接第 $i$ 个和第 $i+1$ 个节点。

对于所有数据有 $0\leq w<mod$ 

保证输入的所有边构成一棵树

对于 $1$~$6$ 号测试点，时限为 $1s$

对于 $7$~$12$ 号测试点，时限为 $2s$

对于 $13$~$20$ 号测试点，时限为 $3s$

## 样例 #1

### 输入

```
5 16
1 2 13
2 3 15
3 4 7
3 5 3
```

### 输出

```
15
15
15
10
15```

# 题解

## 作者：EndSaH (赞：6)

# Description

给定一棵 $n$ 个点的树，边有边权，以及模数 $mod$。对树上每个点都要求出以该点为端点，且权值和模 $mod$ 的余数最大的路径。

$$
1 \le n \le 10 ^5, mod \in \{2, 32, 65536\}
$$

# Solution

点分治。对当前以 $rt$ 为根的树中所有节点先得出他们到根的距离 $dis _i$（当然是在模意义下的），然后扫一棵子树内的点看如何求答案。发现把两条路径组合起来最多只会超出模数一次，所以对超出模数和不超出模数分别讨论，用 `std::multiset` 维护即可。（求答案前，先将子树内从 `std::multiset` 里面全部删除）

不要漏了根的答案，即此时 `std::multiset` 里的最大值。

$O(n \log ^2 n)$。

# Code

竟然只有 116 行...

```cpp
#include <iostream>
#include <vector>
#include <bitset>
#include <set>

#define fir first
#define sec second

using namespace std;
using pii = pair<int, int>;

const int maxN = 1e5 + 5;

int n, mod, rt, minp, all;
int size[maxN], dis[maxN], ans[maxN];
vector<pii> G[maxN];
bitset<maxN> vis;
multiset<int> S;

inline bool Chkmin(auto& x, const auto& y)
{ return x > y ? x = y, true : false; }

inline bool Chkmax(auto& x, const auto& y)
{ return x < y ? x = y, true : false; }

inline void Mod(int& x)
{ x >= mod ? x -= mod : 0; }

void Getroot(int u, int fa)
{
    int maxp = 0;
    size[u] = 1;
    for (auto& v : G[u]) if (v.fir != fa and !vis[v.fir])
    {
        Getroot(v.fir, u);
        size[u] += size[v.fir];
        Chkmax(maxp, size[v.fir]);
    }
    Chkmax(maxp, all - size[u]);
    if (Chkmin(minp, maxp))
        rt = u;
}

void DFS(int u, int fa)
{
    S.insert(dis[u]);
    for (auto& v : G[u]) if (v.fir != fa and !vis[v.fir])
    {
        Mod(dis[v.fir] = dis[u] + v.sec);
        DFS(v.fir, u);
    }
}

int flag;
// Insert and Erase
void InEr(int u, int fa)
{
    if (flag)
        S.insert(dis[u]);
    else
        S.erase(S.find(dis[u]));
    for (auto& v : G[u]) if (v.fir != fa and !vis[v.fir])
        InEr(v.fir, u);
}

void Getans(int u, int fa)
{
    Chkmax(ans[u], dis[u] + *--S.upper_bound(mod - dis[u] - 1));
    Chkmax(ans[u], (dis[u] + *S.rbegin()) % mod);
    for (auto& v : G[u]) if (v.fir != fa and !vis[v.fir])
        Getans(v.fir, u);
}

void Div(int u)
{
    minp = 1e9, Getroot(u, 0);
    Getroot(rt, 0);
    dis[rt] = 0, DFS(rt, 0);
    for (auto& v : G[rt]) if (!vis[v.fir])
    {
        flag = 0, InEr(v.fir, rt);
        Getans(v.fir, rt);
        flag = 1, InEr(v.fir, rt);
    }
    Chkmax(ans[rt], *S.rbegin());
    flag = 0, InEr(rt, 0);
    vis.set(rt);
    // printf("Now Divide %d:\n", rt);
    // for (int i = 1; i <= n; ++i)
    //     printf("ans[%d] is: %d\n", i, ans[i]);
    // for (int i = 1; i <= n; ++i)
    //     printf("dis[%d] is: %d\n", i, dis[i]);
    for (auto& v : G[rt]) if (!vis[v.fir])
        all = size[v.fir], Div(v.fir);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("wib.in", "r", stdin);
    freopen("wib.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> mod;
    for (int i = n - 1; i; --i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w), G[v].emplace_back(u, w);
    }
    all = n, Div(1);
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << endl;
    return 0;
}
```

---

## 作者：yiming564 (赞：4)

# [P5563 [Celeste-B] No More Running](https://www.luogu.com.cn/problem/P5563)

本做法截止至 2024/11/15 [最优解榜一](https://www.luogu.com.cn/record/188865256)。

## $\text{Description}$

给定一棵 $n$ 个节点的带边权树，求对于每个节点 $u$，以 $u$ 为端点的路径长度 **在模 $k$ 意义下** 最长为多少。

数据范围：$1 \leq n \leq 10 ^ 5$, $k \in \{2, 32, 65536\}$。

## $\text{Solution}$

### 前置知识

- [**点分治**](https://www.luogu.com.cn/problem/P3806)

### 符号约定

- $|u|$：$u$ 所在的集合大小，在本题的语境中特指 $u$ 连通块点集的大小。
- $\operatorname{dis}(u, v)$：$u \rightarrow v$ 路径的长度，在本题中是在模 $k$ 意义下的。

### 分析

树上路径问题一般考虑点分治，点分治的套路不再赘述，我们考虑如何统计答案。

对于一个节点 $u$，以 $u$ 为端点的路径以下两部分：

- 以 $u$ 为点分治中心时，由 $u$ 延展到 $u$ 所在连通块的所有路径。
- 其他点分治中心在 $\text{DFS}$ 扫到 $u$ 时所走的路径。

对于第一类路径的统计是非常容易的，如何统计第二类路径？

一种做法是，在点分治路径统计完成后，对于 $u$ 连通块中的每个节点 $v$，计算 $v$ 到 $u$ 子树中 $v_0$ 的距离并使用它更新 $v$，需要注意 $v$ 和 $v_0$ 不可以在 $u$ 的同一棵子树内。

纯暴力计算一次的时间复杂度就是 $O(|u| ^ 2)$ 的。

可以考虑使用一个数据结构维护分治中心 $u$ 的连通块，该数据结构包含 $u$ 到连通块的所有路径的长度。

在计算 $u$ 的每棵子树中的点前，先把该子树中的所有路径从该数据结构中删除，然后统计模 $k$ 意义下的 $\max{\operatorname{dis}(u, v) + \operatorname{dis}(u, v_0)}$，容易发现这个式子 $< 2k$，即最多只会溢出一次。

- 如果溢出了 $0$ 次，那么 $\operatorname{dis}(u, v_0) < k - \operatorname{dis}(u, v)$ 最大时原式最大。
- 如果溢出了 $1$ 次，那么 $\operatorname{dis}(u, v_0) < k < 2k - \operatorname{dis}(u, v)$ 最大时原式最大，即此时对 $\operatorname{dis}(u, v_0)$ 无限制。

因此我们维护一个有序的，可删除的数据结构统计 $\operatorname{dis}(u, v_0)$，每次二分查找最大的满足要求的值即可。

这样计算一次的时间复杂度就是 $O(|u|p)$ 的，其中 $O(p)$ 是数据结构进行一次操作的时间复杂度。

倘若使用平衡树来实现，则总的时间复杂度是 $O(n \log ^ 2 n)$ 的。[代码](https://www.luogu.com.cn/paste/qitwfqwv)

### 优化

在其他题解中大多使用 `std::multiset` 来维护 $u$ 所在的连通块，也有人用 `__gnu_pbds::tree` 来优化，但不要忘记一个传奇数据结构：

$$\texttt{std::bitset 永远的神！}$$

注意到本题的 $k$ 较小，因此可以使用 `std::bitset` 开一个桶来维护，**注意这个桶下标 $i$ 的位置储存的是 $k - 1 - i$**，即这是一个反向的桶，因为 `std::bitset` 只有 `_Find_first()` 和 `_Find_next()` 操作，无法查询最大值。

计算一个节点 $u$ 的时间复杂度为 $O(\frac{k}{w} \times |u|)$，因此总时间复杂度为 $O(\frac{k}{w} \times n \log n)$，且由于 `std::bitset` 使用了硬件指令优化，常数极小，实测比平衡树快了五倍。

### $\text{tricks}$

- 由于 $k$ 是 $2$ 的整数幂，因此可以用按位与来替代取模。
- 可以在每一层点分治时记录子树的 $\text{DFN}$ 序，后续的遍历枚举 $\text{DFN}$ 序列即可，从而减小常数。
- [数据生成器](https://www.luogu.com.cn/paste/ad3gic2s)。

## $\text{Code}$

非关键代码进行了轻度压行，但总体上可读性应该尚可，如有需要，可以自己格式化一下。

```cpp
#include <bits/extc++.h>

#define inline __always_inline
template <typename T> inline void chkmax(T &x, const T &y) { if (x < y) x = y; }
template <typename T> inline void read(T &x)
{
	char ch;
	for (ch = getchar(); !isdigit(ch); ch = getchar());
	for (x = 0; isdigit(ch); ch = getchar()) x = x * 10 + (ch - '0');
}
const int MaxN = 1e5 + 5, MaxA = 65536;

struct edge_t { int v, w; }; std::vector<edge_t> graph[MaxN];
inline void add_edge(int u, int v, int w) { graph[u].push_back({v, w}), graph[v].push_back({u, w}); }
int n, mod, rt; char vis[MaxN];
int Size(int u, int fa)
{
	int s = 1;
	for (auto &&[v, w] : graph[u]) if (!vis[v] && v != fa) s += Size(v, u);
	return s;
}
int Root(int u, int fa, int sum)
{
	int su = 1, sv, max = 0;
	for (auto &&[v, w] : graph[u]) if (!vis[v] && v != fa) su += sv = Root(v, u, sum), chkmax(max, sv);
	chkmax(max, sum - su); if (max <= sum >> 1) rt = u; return su;
}
inline int Root(int u) { Root(u, 0, Size(u, 0)); return rt; }
int seq[MaxN], dis[MaxN], max[MaxN], t[MaxN], cnt[MaxA], top;
std::bitset<MaxA> rev;
inline void add(int d) { if (!cnt[d]++) rev[mod - d] = 1; }
inline void del(int d) { if (!--cnt[d]) rev[mod - d] = 0; }
void Dis(int u, int fa, int d)
{
	seq[top] = u, add(dis[top++] = d), chkmax(max[u], d);
	for (auto &&[v, w] : graph[u]) if (!vis[v] && v != fa) Dis(v, u, (d + w) & mod);
}
inline void calc(int u)
{
	vis[u] = 1, top = 0;
	for (auto &&[v, w] : graph[u]) if (!vis[v]) Dis(v, u, w), t[v] = top;
	for (int i = 0; i < top; i++) chkmax(max[u], dis[i]);
	chkmax(max[u], mod - (int)rev._Find_first()); 
	top = 0;
	for (auto &&[v, w] : graph[u])
		if (!vis[v])
		{
			for (int i = top; i < t[v]; i++) del(dis[i]);
			for (int i = top; i < t[v]; i++)
			{
				const int &u = seq[i], &exp = dis[i], &a = rev._Find_first(), &b = rev._Find_next(exp - 1);
				if (a != MaxA) chkmax(max[u], exp + mod - a & mod);
				if (b != MaxA) chkmax(max[u], exp + mod - b);
			}
			for (int i = top; i < t[v]; i++) add(dis[i]);
			top	= t[v];
		}
	while (top != 0) del(dis[--top]);
}
void dfs(int u)
{
	calc(u);
	for (auto &&[v, w] : graph[u]) if (!vis[v]) dfs(Root(v));
}
int main()
{
	read(n), read(mod), mod--;
	for (int i = 1, u, v, w; i < n; i++) read(u), read(v), read(w), add_edge(u, v, w & mod);
	dfs(Root(1));
	for (int i = 1; i <= n; i++) printf("%d\n", max[i]);
	return 0;
}
```

---

## 作者：AlicX (赞：2)

### 题意

给定一棵树，求出从每一个点出发的所有路径中路径权值和模 $Mod$ 的最长路径。

## Solution 

考虑点分治，设当前根节点为 $u$，一条经过 $u$ 的路径 $s\to t$ 显然可以被分成 $s \to u$ 和 $u \to t$ 两段，然后我们求出以 $u$ 为根时的所有点到 $u$ 的权值和（取模意义下），不难发现两条路径权值和加起来不会超过 $2 \times Mod$。

此时可以分成三种情况讨论：

1. 路径起点就是 $u$，直接取所有路径权值最大值即可。

2. 两条路径长度加起来不超过 $Mod$。设当前节点是 $v$，最优策略是在其他路径中找到路径权值小于等于 $Mod-dis_v-1$ 的最大权值，用 `set` 维护每个点的路径权值，然后二分查询即可。

3. 两条路径长度加起来超过 $Mod$。设当前节点是 $v$，最优策略则是其他路径中权值最大的，直接取 `set` 的结尾元素即可。

一个子树内的节点不可以分成两条路径，注意去重。

为了防止 RE，可以先在 `set` 中插入一个哨兵。时间复杂度 $O(n \log^2n)$。

```cpp
#include<bits/stdc++.h> 
#define ll long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=1e5+10; 
const int INF=1e9+7; 
int n,Mod; 
int dis[N]; 
bool st[N]; 
int h[N],idx=0; 
int Max[N],rt=0; 
int siz[N],sum=0; 
struct Edge{ 
	int w; 
	int to,ne; 
}e[N<<1]; 
il void add(int u,int v,int w){ 
	e[idx].w=w,e[idx].to=v,e[idx].ne=h[u],h[u]=idx++; 
} 
il void dfs1(int u,int fa){ 
	siz[u]=1,Max[u]=0; 
	for(int i=h[u];i!=-1;i=e[i].ne){
		int to=e[i].to; 
		if(to==fa||st[to]) continue; 
		dfs1(to,u); siz[u]+=siz[to]; 
		Max[u]=max(Max[u],siz[to]); 
	} Max[u]=max(Max[u],sum-siz[u]); 
	if(Max[rt]>Max[u]) rt=u; 
} 
int t[N],id=0; 
il void dfs2(int u,int fa){ 
	t[++id]=u; 
	for(int i=h[u];i!=-1;i=e[i].ne){ 
		int to=e[i].to; 
		if(to==fa||st[to]) continue; 
		dis[to]=(dis[u]+e[i].w)%Mod; dfs2(to,u); 
	} 
} 
int ans[N]; 
il void calc(int u){ 
	set<pii> s; s.insert({0,0}); 
	for(int i=h[u];i!=-1;i=e[i].ne){ 
		int to=e[i].to; 
		if(st[to]) continue; 
		id=0,dis[to]=e[i].w%Mod,dfs2(to,u); 
		for(int j=1;j<=id;j++) s.insert({dis[t[j]],t[j]}); 
	} for(int i=h[u];i!=-1;i=e[i].ne){ 
		int to=e[i].to; 
		if(st[to]) continue; 
		id=0,dis[to]=e[i].w%Mod,dfs2(to,u); 
		for(int j=1;j<=id;j++) s.erase(s.find({dis[t[j]],t[j]})); 
		for(int j=1;j<=id;j++){ 
			int dist=dis[t[j]]; 
			ans[u]=max(ans[u],dist); 
			ans[t[j]]=max(ans[t[j]],dist); 
			pii p={Mod-dist,0}; 
			auto it=s.lower_bound(p); it--;  
			ans[t[j]]=max(ans[t[j]],dist+(*it).x); 
			auto It=s.rbegin(); 
			ans[t[j]]=max(ans[t[j]],(dist+(*It).x)%Mod); 
		} for(int j=1;j<=id;j++) s.insert({dis[t[j]],t[j]}); 
	} 
} 
il void solve(int u){ 
	st[u]=true,calc(u); 
	for(int i=h[u];i!=-1;i=e[i].ne){
		int to=e[i].to; 
		if(st[to]) continue; 
		sum=Max[rt=0]=siz[to]; 
		dfs1(to,0); solve(rt); 
	} 
} 
signed main(){ 
	memset(h,-1,sizeof h); 
	n=read(),Mod=read(); 
	for(int i=1,u,v,w;i<n;i++) u=read(),v=read(),w=read(),add(u,v,w),add(v,u,w); 
	sum=Max[rt=0]=n,dfs1(1,0); solve(rt); 
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]); 
	return 0; 
} 
```

---

## 作者：云浅知处 (赞：1)

Celeste 的题/se

----------------

考虑点分治。

设 $\text{Dist}(u)$ 表示 $u$ 到根的路径长 $\bmod\ m$ 的值，那么只需要计算「对于所有在不同子树内的 $u,v$， $\text{Dist}(u)+\text{Dist}(v)$ 模 $m$ 的最大值」。

先将所有 $\text{Dist}$ 值对 $m$ 取模。不难发现此时两个数加起来要么小于 $m$，要么在 $[m,2m)$ 之间。

枚举 $u$，对于第一种情况，只需要计算出 $<m-\text{Dist}(u)$ 的最大的 $\text{Dist}$ 值，二分即可；对于第二种情况显然直接取最大值即可。

这道题还需要对每个点都求出来以它为端点的最优路径，实际上只需要在枚举端点时顺便统计一下就行了。

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

int n,mod;

struct Edge{
	int to,cost;
	Edge(int T,int C):to(T),cost(C){}
	Edge(){}
};

const int MN=1e5+5;
vector<Edge>G[MN];
int sz[MN],mx[MN],rt,num;
bool vis[MN];

void calcsiz(int u,int fa){
	sz[u]=1,mx[u]=0;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to;
		if(v==fa||vis[v])continue;
		calcsiz(v,u);
		sz[u]+=sz[v],mx[u]=max(mx[u],sz[v]);
	}
	mx[u]=max(mx[u],num-sz[u]);
	if(mx[u]<mx[rt]||rt==0)rt=u;
}

int dis[MN],cnt;

struct Node{
	int id,val;
	Node(int I,int V):id(I),val(V){}
	Node(){}
	inline bool operator<(const Node &rhs)const{
		return val<rhs.val;
	}
};

multiset<Node>S;
Node d[MN];

#define Sit multiset<Node>::iterator

void calcdis(int u,int fa){
	d[++cnt]=Node(u,dis[u]%mod);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to,w=G[u][i].cost;
		if(v==fa||vis[v])continue;
		dis[v]=(dis[u]+w)%mod,calcdis(v,u);
	}
}

int ans[MN];

void dfz(int u,int fa){
	S.insert(Node(u,0)),vis[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to,w=G[u][i].cost;
		if(v==fa||vis[v])continue;
		dis[v]=w%mod,calcdis(v,u);
		for(int j=1;j<=cnt;j++)S.insert(d[j]);cnt=0;
	}
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to,w=G[u][i].cost;
		if(v==fa||vis[v])continue;
		dis[v]=w%mod,calcdis(v,u);
		for(int j=1;j<=cnt;j++)S.erase(S.find(d[j]));
		for(int j=1;j<=cnt;j++){
			Sit it=S.lower_bound(Node(d[j].id,mod-d[j].val%mod));
			assert(it!=S.begin());it--;assert(it->val+d[j].val<mod);
			ans[d[j].id]=max(ans[d[j].id],d[j].val+it->val);
			it=S.end();it--;
			ans[d[j].id]=max(ans[d[j].id],(d[j].val+it->val)%mod);
		}
		for(int j=1;j<=cnt;j++)S.insert(d[j]);cnt=0;
	}
	Sit it=S.end();it--;
	ans[u]=max(ans[u],it->val);S.clear();
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to;
		if(v==fa||vis[v])continue;
		num=sz[v],rt=0;
		calcsiz(v,u),calcsiz(rt,0);
		dfz(rt,u);
	}
}

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif
	
	n=read();mod=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		G[u].push_back(Edge(v,w)),G[v].push_back(Edge(u,w));
	}
	
	num=n;calcsiz(1,0),calcsiz(rt,0);
	dfz(rt,0);
	
	for(int i=1;i<=n;i++)cout<<ans[i]<<endl;

    return 0;
}
```

---

## 作者：XiaoZi_qwq (赞：0)

# P5563 [Celeste-B] No More Running
## 题意概述
给定一棵树，对于每一个点，求在所有以该点为端点的路径中，权值在模 $p$ 意义下的最大值。
## 分析
看到题目要求的东西是与**树上路径权值相关**的，所以考虑点分治。  
若无特殊说明，以下叙述中的 $dis(u,v)$，皆为 在模 $p$ 意义下 $u$ 到 $v$ 路径的长度。  
和其他点分治题目一样，以一个点 $u$ 为端点的路径可以被分为两类：当 $u$ 作为重心时统计到的路径和当 $u$ 不作为重心时统计到的路径。  
对于第一种路径，直接取最大的 $dis(u,v)$ 就可以了。（因为权值肯定不超过 $p$）  
对于第二种路径，我们就需要考虑如何刻画“在模 $p$ 意义下”这个限制了。    
对于一条路径 $(u,v)$，它可以被分为 $(u,rt)$ 和 $(rt,v)$ 两个部分（$rt$ 指重心）。我们可以对 $dis(u,rt)+dis(rt,v)$ 和 $p$ 的大小关系就行分类讨论：  
对于 $dis(u,rt)+dis(rt,v) \lt p$ 的 $v$，那么它对 $u$ 点答案的贡献为：
$$
dis(u,rt)+dis(rt,v)
$$  
对于 $dis(u,rt)+dis(rt,v) \ge p$ 的 $v$，那么它对 $u$ 点答案的贡献为：  
$$
dis(u,rt)+dis(rt,v)-p
$$
现在现在只剩下一个问题：“怎么快速找出符合条件的 $v$”。这可以考虑排序后用二分查找处理（代码所使用的方法）或STL大法。  
_**Talk is cheap,show me your code**_

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline int read(){
  register int x=0,f=1;
  char c=getchar();
  while(c<'0' || '9'<c) f=(c=='-')?-1:1,c=getchar();
  while('0'<=c && c<='9') x=(x<<1)+(x<<3)+c-'0',c=getchar();
  return x*f;
}
void write(int x){
  if(x>=10) write(x/10);
  putchar(x%10+'0');
}
typedef long long ll;
const int N=1e5+10;
int n,mod,ans[N];
struct Edge{int from,to,dis;}e[N<<1];
int num,h[N];
void add(int f,int t,int d){e[++num].from=h[f],e[num].to=t,e[num].dis=d,h[f]=num;}
int rt,sz[N],mxsz[N],sum=n;
bool vis[N];
void getsz(int u,int fa){
  sz[u]=1,mxsz[u]=0;
  for(int i=h[u];i;i=e[i].from){
    int v=e[i].to;
    if(v==fa || vis[v]) continue;
    getsz(v,u);
    mxsz[u]=max(mxsz[u],sz[v]);
    sz[u]+=sz[v];
  }
  mxsz[u]=max(sum-sz[u],mxsz[u]);
  if(mxsz[u]<mxsz[rt])
    rt=u;
}

struct Node{
  int val,id;
  Node(int _val=0,int _id=0){val=_val,id=_id;}
}d[N];
bool cmp(Node a,Node b){return a.val<b.val;}
int dis[N],ed[N],rk[N],f[N],cnt,tot,lst;//d:所有的距离
inline int find(int x){return f[x]=(f[x]==x)?x:find(f[x]);}
void dfs(int u,int fa){
  d[++tot]=Node(dis[u],u);
  for(int i=h[u];i;i=e[i].from){
    int v=e[i].to;
    if(v==fa || vis[v]) continue;
    dis[v]=(dis[u]+e[i].dis)%mod;
    dfs(v,u);
  }
}
int found(int x){//功能：找到第一个小于等于x的数
  int L=1,R=tot,mid,ans=-1;
  while(L<=R){
    mid=L+R>>1;
    if(d[find(mid)].val<=x){
      if(find(mid))
        ans=find(mid);
      L=mid+1;
    }
    else
      R=mid-1;
  }
  return ans==-1?0:d[ans].val;
}
void dfs1(int u,int fa,int p){//从d数组中删除/加回去
  f[rk[u]]=(p==1)?rk[u]:(rk[u]-1);
  for(int i=h[u];i;i=e[i].from){
    int v=e[i].to;
    if(v==fa || vis[v]) continue;
    dfs1(v,u,p);
  }
}
void dfs2(int u,int fa){//统计答案
  ans[u]=max(ans[u],max((found(mod-dis[u]-1)+dis[u])%mod,(dis[u]+d[find(tot)].val)%mod));
  for(int i=h[u];i;i=e[i].from){
    int v=e[i].to;
    if(v==fa || vis[v]) continue;
    dfs2(v,u);
  }
}
void calc(int u){
  cnt=tot=0;
  for(int i=h[u];i;i=e[i].from){
    int v=e[i].to;
    if(vis[v]) continue;
    dis[v]=e[i].dis;
    dfs(v,u),ed[++cnt]=tot;
  }
  sort(d+1,d+tot+1,cmp);
  for(int i=1;i<=tot;i++) rk[d[i].id]=i;
  if(tot)
    ans[u]=max(ans[u],d[tot].val);
  for(int i=h[u];i;i=e[i].from){
    int v=e[i].to;
    if(vis[v]) continue;
    dfs1(v,u,0);
    dfs2(v,u);
    dfs1(v,u,1);
  }
}
void slove(int u){
  vis[u]=true,calc(u);
  for(int i=h[u];i;i=e[i].from){
    int v=e[i].to;
    if(vis[v]) continue;
    sum=sz[v],rt=0;
    getsz(v,0);
    slove(rt);
  }
}
void init(){
  mxsz[0]=inf,d[0].val=0;
  for(int i=0;i<=n;i++) f[i]=i;
  sum=n;
}
int main()
{
  n=read(),mod=read();
  for(int i=1,u,v,w;i<n;i++) u=read(),v=read(),w=read(),add(u,v,w),add(v,u,w);
  getsz(1,0);
  slove(rt);
  for(int i=1;i<=n;i++)
    write(ans[i]),putchar('\n');
  return 0;
}

```

---

