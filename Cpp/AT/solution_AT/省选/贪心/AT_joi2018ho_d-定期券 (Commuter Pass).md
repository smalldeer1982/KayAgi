# 定期券 (Commuter Pass)

## 题目描述

JOI 君居住的城市中有 $N$ 个车站，编号为 $1$ 到 $N$。同时，还有 $M$ 条铁路线，编号为 $1$ 到 $M$。每条铁路线 $i$ ($1 \leq i \leq M$) 连接车站 $A_i$ 和车站 $B_i$，票价为 $C_i$ 日元。

JOI 君住在车站 $S$ 附近，学校在车站 $T$ 附近，因此他计划购买一张从车站 $S$ 到车站 $T$ 的定期票。购买该定期票时，需要选择一条从 $S$ 到 $T$ 的最低票价路径。购票之后，他可以在这条指定路径上的所有铁路线自由通行。

此外，JOI 君还频繁访问车站 $U$ 和车站 $V$ 附近的书店。他希望选择的定期票能帮助他降低从车站 $U$ 到车站 $V$ 的出行费用。

从车站 $U$ 到车站 $V$ 时，若经过的铁路线 $i$ 包含在定期票所指定的路径中，则票价为 $0$ 日元；否则，票价为 $C_i$ 日元。我们的目标是找到一种选择定期票路径的方法，使得从车站 $U$ 到车站 $V$ 的总票价最小。

## 说明/提示

### 限制

所有数据满足：

- $2 \leq N \leq 100,000$
- $1 \leq M \leq 200,000$
- $1 \leq S, T, U, V \leq N$
- $S \neq T$
- $U \neq V$
- $S \neq U$ 或 $T \neq V$
- 任意两个车站间至少有一条可行的铁路线
- 对于 $1 \leq i \neq j \leq M$，$A_i \neq A_j$ 或 $B_i \neq B_j$
- $1 \leq C_i \leq 1,000,000,000$

### 子任务

#### 子任务 1 [16 分]

- 满足 $S = U$。

#### 子任务 2 [15 分]

- 从车站 $S$ 到车站 $T$ 的最优路径唯一。

#### 子任务 3 [24 分]

- $N \leq 300$。

#### 子任务 4 [45 分]

- 无额外限制。

### 示例解释

在示例中，从车站 $1$ 到车站 $4$ 的最小票价路径是 $1 \to 2 \to 3 \to 5 \to 4$。在该路径上，除了 $5$ 号铁路线需支付 $2$ 日元外，其他路线均免费，总费用为 $2$ 日元。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6 6
1 6
1 4
1 2 1
2 3 1
3 5 1
2 4 3
4 5 2
5 6 1```

### 输出

```
2```

## 样例 #2

### 输入

```
6 5
1 2
3 6
1 2 1000000000
2 3 1000000000
3 4 1000000000
4 5 1000000000
5 6 1000000000```

### 输出

```
3000000000```

## 样例 #3

### 输入

```
8 8
5 7
6 8
1 2 2
2 3 3
3 4 4
1 4 1
1 5 5
2 6 6
3 7 7
4 8 8```

### 输出

```
15```

## 样例 #4

### 输入

```
5 5
1 5
2 3
1 2 1
2 3 10
2 4 10
3 5 10
4 5 10```

### 输出

```
0```

## 样例 #5

### 输入

```
10 15
6 8
7 9
2 7 12
8 10 17
1 3 1
3 8 14
5 7 15
2 3 7
1 10 14
3 6 12
1 5 10
8 9 1
2 9 7
1 4 1
1 8 1
2 4 7
5 6 16```

### 输出

```
19```

# 题解

## 作者：dyc2022 (赞：2)

JOI 的一道好题。
***
### 题意简述

给定一个无向带权图，和节点 $S,T,U,V$。你可以将 $S \rightarrow T$ 的一条最短路上的所有边权修改为 $0$，然后最小化 $U \rightarrow V$ 的最短路长度。

### Solution

首先，我们可以处理出所有可能出现在 $S$ 到 $T$ 的最短路的边（以下简称 **可能边**）。一条边 $(U_i,V_i,W_i)$ 可能出现在最短路中，当且仅当 $\text{dis}_{S,U_i} + W_i + \text{dis}_{V_i,T} = \text{dis}_{S,T}$，这一点显然。

我们可以把每一条可能边按照最短路经过它的方向定向。有一个显然的结论，那就是由可能边组成的图是一张 DAG。因为在一个正边权图中，一条最短路是不可能出现环的。

那么我们可以把这个问题转化为一个 DAG 上 dp 问题。我们可以预处理出 $U$ 和 $V$ 到每一个节点的最短路。然后我们在 DAG 上通过 dp 求出每一个节点 $i$ 所能到达的节点 $k_i$，使 $\text{dis}_{k_i,V}$ 最小。那么最后的答案就是 $\min \text{dis}_{U,i}+ \text{dis}_{k_i,V}$。

### AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define N 100006
using namespace std;
vector<pair<int,int> > G[N];
int n,m,s1,t1,s2,t2;
int u[N<<2],v[N<<2],w[N<<2],dis[4][N],vis[N],ans[N],in[N];
struct Node{int u,d;};
bool operator >(Node x,Node y){return x.d>y.d;}
priority_queue<Node,vector<Node>,greater<Node> > q;
void dij(int s,int *D)
{
    for(int i=1;i<=n;i++)vis[i]=0,D[i]=1e15;
    D[s]=0;
    q.push({s,0});
    while(!q.empty())
    {
        Node now=q.top();q.pop();
        int u=now.u;
        if(vis[u])continue;
        vis[u]=1;
        for(auto v:G[u])
        {
            if(vis[v.first])continue;
            if(D[u]+v.second<D[v.first])
            {
                D[v.first]=D[u]+v.second;
                q.push({v.first,D[v.first]});
            }
        }
    }
    //for(int i=1;i<=n;i++)cout<<D[i]<<' ';puts("");
}
void topo(int s)
{
    queue<int> q2;
    q2.push(s);
    //cout<<s<<':'<<ans[s]<<endl;
    while(!q2.empty())
    {
        int now=q2.front();q2.pop();
        for(auto v:G[now])
        {
            //cout<<"topu: "<<now<<' '<<v.first<<endl;
            in[v.first]--;
            ans[v.first]=min(ans[v.first],ans[now]);
            if(!in[v.first])q2.push(v.first);
        }
    }
}
int solve()
{
    for(int i=1;i<=(m<<1);i++)ans[i]=1e15;
    for(int i=1;i<=n;i++)G[i].clear(),in[i]=0;
    for(int i=1;i<=(m<<1);i++)G[u[i]].push_back({v[i],w[i]});
    dij(s1,dis[0]),dij(t1,dis[1]),dij(s2,dis[2]),dij(t2,dis[3]);
    for(int i=1;i<=n;i++)G[i].clear();
    set<int> points;
    for(int i=1;i<=(m<<1);i++)
    {
        if(dis[0][u[i]]+w[i]+dis[1][v[i]]==dis[0][t1])
        {
            G[v[i]].push_back({u[i],w[i]});
            in[u[i]]++;
            points.insert(u[i]),points.insert(v[i]);
        }
    }
    for(auto it=points.begin();it!=points.end();it++)
        ans[*it]=dis[3][*it];
    for(auto it=points.begin();it!=points.end();it++)
        if(!in[*it])topo(*it);
    //for(int i=1;i<=n;i++)cout<<ans[i]<<' ';cout<<endl;
    int minn=1e15;
    for(auto it=points.begin();it!=points.end();it++)minn=min(minn,dis[2][*it]+ans[*it]);
    //cout<<"["<<minn<<"]\n";
    return min(minn,dis[2][t2]);
}
main()
{
    scanf("%lld%lld%lld%lld%lld%lld",&n,&m,&s1,&t1,&s2,&t2);
    for(int i=1;i<=m;i++)
    {
        scanf("%lld%lld%lld",&u[i],&v[i],&w[i]);
        u[i+m]=v[i],v[i+m]=u[i],w[i+m]=w[i];
    }
    int ans=solve();
    swap(s1,t1);
    ans=min(ans,solve());
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

题意：给定一张无向图 $G$，现在给定四个点 $S$，$T$，$u$，$v$，你需要任意选取 $S\to T$ 的一条最短路，并使得将其上所有边边权均赋为 $0$ 后 $u\to v$ 最短路长度最短。

题解：

首先考虑下面的引理：

$\textbf{Lemma}$ 图中 $S\to T$，$u\to v$ 可以构造两条最短路满足下列两种情况中至少一组：

+ 两条图上的路径没有重边。
+ 两条图上的路径有且只有一段相同的边。

$\textbf{Proof}$ 若上述两条图上的路径有两段或以上的重合部分，则任意两段相邻的重合部分，必然有一段路径不重合。考虑找出这一段路径在另一条最短路上所对应的路径，则此时若这条新的路径边权之和大于或等于原来最短路，则换为原来的最短路一定不会更劣；若小于原来的最短路，则原来的最短路就可以被替换为现在的路径，不符合最短路的定义。因此得证。

以及下面的另一个引理：

$\textbf{Lemma}$ 令 $\text{DS}$ 数组表示 $S$ 点为原点的最短路长度，$\text{DT}$ 数组表示 $T$ 点为原点的最短路长度，则对于每一条 $u\leftrightarrow v$，长度为 $w$ 的一条无向边，若满足 $\text{DS}_u+\text{DT}_v+w=\text{DS}_{T}$，或者 $\text{DT}_u+\text{DS}_v+w=\text{DS}_{v}$，则该边可能成为 $S\to T$ 的最短路，否则一定不可能。

$\textbf{Proof}$ 若 $\text{DS}_u+\text{DT}_v+w=\text{DS}_{T}$，则等式的前半部分可以分离为：

+ 从 $S$ 沿最短路走到 $u$。
+ 从 $u$ 走到 $v$，边权为 $w$。
+ 从 $v$ 沿最短路走到 $T$。

而后半部分的 $\text{DS}_T$ 则表示 $S$ 直接走到 $T$ 的最短路。若这两个相等，则表示 $S\to u\to v\to T$ 这一条路径也为最短路，因此 $u\to v$ 这条边在最短路上。反过来同理。

若 $\text{DS}_u+\text{DT}_v+w>\text{DS}_T$，则根据类似于上面的分析可以发现，$u\to v$ 这条边在当前的选取路径下不在最短路上。而因为另外两个部分已经为最短的长度，没有其他的路径继续压缩上述的长度，因此她一定不在最短路上。因此证毕。

又有第三个引理：

$\textbf{Lemma}$ 若将所有可能在最短路上的边按照 $S\to T$ 最短路上的顺序建边，则新图为一张 $\text{DAG}$。

$\textbf{Proof}$ 若图不为 $\text{DAG}$ 则必然存在环。原图中不存在负权边，也就更不可能存在负环。没有负环就不会在新图中存在环，而有向无环图即为 $\text{DAG}$，因此得证。

因此建出新图 $G_1$ 和新图的反图 $G_2$，在 $G_1$ 中跑 $S$ 点的最短路，$G_2$ 中跑 $T$ 点的最短路。然后考虑枚举两条最短路重合的一段路径 $x\to y$，满足 $G_1$ 中 $x$ 可以到达 $y$，并且使得 $\text{DU}_x+\text{DV}_y$ 的值最小。此时考虑在 $\text{DAG}$ 上 $\text{dp}$，对于每一个点 $x$ 找出在 $G_1$ 中其能走到的 $y$ 中 $\text{DV}_y$ 的最小值。这个问题就是平凡的了。

于是这个题我们就做完啦！！！！！不愧是一道好题！！！

---

## 作者：_RainCappuccino_ (赞：0)

>$\mathtt{TAG}$：最短路，DP，拓扑排序
## 题意
给定一个 $n$ 个点 $m$ 条边的无向图，边有边权。

给定两对点 $s_1,t_1$ 和 $s_2,t_2$。

你可以选定 $s_1$ 到 $t_1$ 的**一条**最短路径，使得这些边的边权变为 $0$，要求操作之后 $s_2$ 到 $t_2$ 的最短路长度最小。

## First. $s_2$ 到 $t_2$ 的最短路性质

我们发现，这条最短路会经过一段连续的选定边。

如何证明？

反证法。

假设选定路径为 $e_1,e_2,\dots,e_k$，如果 $s_2$ 到 $t_2$ 的最短路为 $E_1,E_2,\dots, e_x,e_{x + 1}, E_{l},\dots,E_{r},e_{x+3},\dots,E_{len}$。显然 $e_{x+2} < \sum_{i=l}^{r} E_i$，且选用 $e_{x + 2}$ 能保证路径连续，是合法路径，显然比 $s_2$ 到 $t_2$ 的最短路更短，与最短路定义矛盾，所以这条最短路会经过一段连续的选定边。

## Second. 求 $s_2$ 到 $t_2$ 的最短路

根据上文中的性质，设该连续路径的两个端点为 $p, q$，可以将该最短路分成 $3$ 段：$dis_{s_2, p} + 0 + dis_{q, t_2}$。

不妨枚举 $p$，找到使得 $dis_{q, t_2}$ 最小的**在最短路中且可达**的 $q$。

首先先将最短路 DAG 建出来。

这里直接判断一条边 $(u, v, w)$ 是否满足 $dis_{s_1, u} + w + dis_{v, t_1} = dis_{s_1, t_1}$，满足就加入图中。

由于是 DAG，所以 $q$ 可以 DP 求解：

$$dp_u =  \mathop {\max}_{v\in g_u} dp_v$$

注意这里可以是 $p \to q$ 也可以是 $q \to p$，所以同时再反过来维护一下使得 $dis_{q, s_2}$ 最小的**在最短路中且可达**的 $q$。


## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int N = 2e5 + 10;
typedef pair<int, int> pi;
vector<pi> g[N];
vector<int> g2[N];
ll dis[4][N];
bool vis[N];
int n, m, s, t, s2, t2;
void dij (int s, ll dis[]) {
	for (int i = 1; i <= n; i ++) dis[i] = 1e20;
	memset(vis, 0, sizeof vis);
	dis[s] = 0;
	priority_queue<pi, vector<pi>, greater<pi> > q;
	q.push({0, s});
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for (auto e : g[u]) {
			int v = e.first, w = e.second;
			if(dis[u] + w < dis[v]) {
				q.push({dis[v] = dis[u] + w, v});
			}
		}
	}
} 
ll dp[N], f[N], ans = 1e20;
int in[N];
 
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> s >> t >> s2 >> t2;
	for (int i = 1; i <= m; i ++) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].push_back({v, w}), g[v].push_back({u, w});
	}
	dij(s, dis[0]), dij(t, dis[1]);
	dij(s2, dis[2]), dij(t2, dis[3]);
	for (int i = 1; i <= n; i ++) {
		for (auto e : g[i]) {
			int u = e.first, w = e.second;
			if(dis[0][i] + dis[1][u] + w == dis[0][t]) {
				g2[i].push_back(u);
				// cout << i << ' ' << u << endl;
				in[u] ++;
			}
		}
	}
	for (int i = 1; i <= n; i ++) {
		dp[i] = dis[2][i];
		f[i] = dis[3][i];
	}
	queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto v : g2[u]) {
			dp[v] = min(dp[v], dp[u]);
			f[v] = min(f[v], f[u]);
			if(!(-- in[v])) q.push(v);
		}
	}
	for (int i = 1; i <= n ;i ++) ans = min(ans, dp[i] + dis[3][i]), ans = min(ans, f[i] + dis[2][i]);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：菲斯斯夫斯基 (赞：0)

### 前言

模拟赛 T3，赛时只做了前 3 个子任务，输了。

### 思路

注：便于描述，以下「最优的路径」指题目中「从站 $U$ 到站 $V$ 的最小成本的路径」,「最短路」指题目中「从站 $S$ 到站 $T$ 的花费最小的路径」。

直接讲正解吧。先把所有在最短路上的边拎出来，最优的路径一定是走了最短路中一些连续的边，反证即可证明。

然后就可以跑一个拓扑，记 $dp_{i}$ 为走到 $i$ 这个点之前（含 $i$）所有走过的点距离 $U$ 的最小值。因为在 $i$ 之前走的所有点到 $i$ 的花费都为 $0$，所以最后的答案是 $\min\{dp_i+dis_{i,V}\}$，$dis_{i,V}$ 是 $i$ 到 $V$ 的最小花费。

不过还要注意像样例 $3$ 的那种情况，有可能最优的路径与最短路反方向行走。所以还要跑一次 $dp_i$ 为 $i$ 之前的点到 $V$ 的最小值，答案为 $\min\{dp_i+dis_{i,U}\}$。

这题就做完了。至于怎么把所有在最短路上的边拎出来，判断两个端点 $i$、$j$ 分别到 $U$、$V$ 的最小花费之和加上这条边的权值是否为 $U$ 到 $V$ 的最小花费就行。

没看懂思路的具体看代码吧。

### 代码

要跑四遍 Dijkstra。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=1e5+10;
int n,m,s,t,u,p,cnt,tot,ans=1e18,len,sum;
int vis[N],f[5][N],head[N],in[N],chk[N<<2],dp[3][N];
queue<int>q;
struct edge
{
	int x,to,c,nxt;
}v[N<<2];
struct ccf
{
	int x,c;
	bool operator <(const ccf &a)const
	{
		return c>a.c;
	}
};
void add(int x,int y,int z)
{
	v[++cnt]={x,y,z,head[x]};
	head[x]=cnt;
}
int dijkstra(int s,int t,int now)
{
	memset(vis,0,sizeof(vis));
	f[now][s]=0;
	priority_queue<ccf>q;
	q.push({s,0});
	while(!q.empty())
	{
		auto x=q.top();
		q.pop();
		if(vis[x.x])continue;
		vis[x.x]=1;
		for(int id=head[x.x];id;id=v[id].nxt)
		{
			pii i={v[id].to,v[id].c};
			if(f[now][i.fi]<=f[now][x.x]+i.se)continue;
			f[now][i.fi]=f[now][x.x]+i.se;
			q.push({i.fi,f[now][i.fi]});
		}
	}
	return f[now][t];
}
void topo(int x)
{
	in[x]=0,q.push(x);
	while(!q.empty())
	{
		x=q.front();
		q.pop();
		for(int id=head[x];id;id=v[id].nxt)
		{
			int i=v[id].to;
			if(!chk[id])continue;
			dp[1][i]=min(dp[1][i],dp[1][x]),dp[2][i]=min(dp[2][i],dp[2][x]);//求最小值
			in[i]--;
			if(!in[i])q.push(i);
		}
	}
}
signed main()
{
	cin>>n>>m;
	cin>>s>>t;
	cin>>u>>p;
	memset(f,127,sizeof(f));
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		add(x,y,z),add(y,x,z);
	}
	sum=dijkstra(s,t,++tot),dijkstra(t,s,++tot);
	ans=dijkstra(u,p,++tot),dijkstra(p,u,++tot);//先跑4遍Dijkstra
	for(int i=1;i<=cnt;i++)
	{
		chk[i]=(f[1][v[i].x]+f[2][v[i].to]+v[i].c==sum);//在最短路上的边
		if(chk[i])in[v[i].to]++;
	}
	memset(dp,127,sizeof(dp));
	for(int i=1;i<=n;i++)
		if(in[i]||i==s)dp[1][i]=f[3][i],dp[2][i]=f[4][i];//起点到U和V的距离
	topo(s);
	for(int i=1;i<=n;i++)
		ans=min(ans,min(dp[1][i]+f[4][i],dp[2][i]+f[3][i]));//最后求最小值
	cout<<ans<<endl;
	return 0;
}
```

---

