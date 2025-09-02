# [PA 2019 Final] Floyd-Warshall

## 题目背景

译自 PA 2019 Final。


本题数据为自造。

std: zimpha，validator: Starrykiller，generator：KanameMadoka&Starrykiller。Special Thanks to @N_z_。

## 题目描述



有一个 $n$ 个节点的简单有向带权图。Radewoosh 想要求出这张图的全源最短路。他决定写个 Floyd-Warshall：

$$
\def\arraystretch{1.2}
    \begin{array}{ll}
    \hline
    \textbf{算法 1} & \text{\textbf{正确的} Floyd-Warshall 算法} \\
    \hline
    1&\textbf{Require: } n\times n \text{ 的矩阵 }M，满足：\\
    & M_{i,j}=\begin{cases}
                  0, & \text{当 } i=j \\
                  w_{i,j}, & \text{当存在一条 } u\to v \text{ 的有向边，边权为 } w_{i,j} \\
                  \infty, & \text{其他情况}
               \end{cases}
    \\
    2&\ \textbf{for } x=1,2,3,\ldots,n \textbf{ do} \\
    3&\ \qquad\textbf{for } y=1,2,3,\ldots,n \textbf{ do} \\
    4&\ \qquad\qquad\textbf{for } z=1,2,3,\ldots,n \textbf{ do} \\
    5&\ \qquad\qquad\qquad M_{y,z}\gets \min(M_{y,z},M_{y,x}+M_{x,z}) \\
    \hline
    \end{array} 
$$

然而他搞错了循环顺序，于是代码变成了这样：

$$
\def\arraystretch{1.2}
    \begin{array}{ll}
    \hline
    \textbf{算法 2} & \text{\textbf{不正确的} Floyd-Warshall 算法} \\
    \hline
    1&\textbf{Require: } n\times n \text{ 的矩阵 }M，满足：\\
    & M_{i,j}=\begin{cases}
                  0, & \text{当 } i=j \\
                  w_{i,j}, & \text{当存在一条 } u\to v \text{ 的有向边，边权为 } w_{i,j} \\
                  \infty, & \text{其他情况}
               \end{cases}
    \\
    2&\ \textbf{for } y=1,2,3,\ldots,n \textbf{ do} \\
    3&\ \qquad\textbf{for } z=1,2,3,\ldots,n \textbf{ do} \\
    4&\ \qquad\qquad\textbf{for } x=1,2,3,\ldots,n \textbf{ do} \\
    5&\ \qquad\qquad\qquad M_{y,z}\gets \min(M_{y,z},M_{y,x}+M_{x,z}) \\
    \hline
    \end{array} 
$$

令这张图中，$x\to y$ 正确的距离为 $\operatorname{dist}(x,y)$，Radewoosh 求出的为 $\operatorname{dist}'(x,y)$。

求出满足 $\operatorname{dist}(x,y)\neq \operatorname{dist}'(x,y)$ 的 $(x,y)$ 对数。




## 说明/提示

- $2\le n\le 2\times 10^3$；
- $1\le m\le 3\times 10^3$；
- $1\le u,v\le n$，$u\neq v$；
- $1\le w\le 10^5$；
- 给定的图是简单图（无重边自环）。

样例解释：

以下左边的矩阵是正确的 $\operatorname{dist}$ 矩阵，右边是错误的 $\operatorname{dist'}$ 矩阵。

$$\begin{bmatrix}0&6&1&4\\\infin&0&4&7\\\infin&5&0&3\\\infin&2&6&0\end{bmatrix}\qquad\begin{bmatrix}0&9&1&4\\\infin&0&4&7\\\infin&5&0&3\\\infin&2&6&0\end{bmatrix}$$

## 样例 #1

### 输入

```
4 5
2 3 4
3 4 3
4 2 2
1 3 1
1 2 9```

### 输出

```
1```

# 题解

## 作者：hxhhxh (赞：8)

尝试刻画这个错误的 floyd 能得到哪些路径，发现其实没有那么复杂，还是刻画得出来的。

下面约定 $i\sim j$ 表示 $i$ 到 $j$ 的一条有向路径，$i\to j$ 表示 $i$ 到 $j$ 的一条有向边。

假设现在最外层枚举到 $(s,t)$（这里假设 $s<t$，不满足可以建反图再跑一遍），那么下面这些 $s\sim t$
的路径会被考虑：

1. $s\to t$；
2. $s\to p\to t$；
3. $s\sim p\to t$，其中 $s<p<t$，且 $s\sim p$ 的路径会被考虑；
4. $s\sim p\sim t$，其中 $p<s$，且 $s\sim p$ 和 $p\sim t$ 的路径会被考虑。

注意这是一个递归的结论。可以归纳出，所有 $s\sim t$（假设 $s<t$）的被考虑的路径为以下形式：

$$s\to p_1\to p_2\to\dots\to p_k\to\dots\to p_l$$

其中，$k$ 可以等于 $l$，且有以下性质：
1. $p_l=t$，$p_k>s$；
2. $\forall i\in[k,l),p_i<p_{i+1}$；
3. $\nexists i\in[2,k),\min(p_i,p_{i-1})>s$。

也就是说，所有被考虑的从 $s$ 到 $t$ 的路径都是从 $s$ 开始在原图上走，但是不能连续两步都在 $\geq s$ 的点上；然后在第一次违反这个限制后只能向编号更大的点走，最终走到 $t$。

这是一个非常好的结论，以至于我们可以直接利用它来求出错误的最短路。

首先枚举 $s$，忽略两端都大于 $s$ 的边后跑一遍最短路，可以考虑到 $s\sim p_{k-1}$ 的所有路径；然后保留原图上的所有边，可以考虑到 $p_{k-1}\to p_k$；最后只保留从编号小的点到编号大的点的边，可以考虑到 $p_k\sim p_l$。将这三部分拼起来就可以求出错误的最短路了。

时间复杂度为 $O(n(n+m)\log n)$，空间复杂度为 $O(n^2+m)$，可以求出题面代码给出的最短路矩阵。在本题中空间也可以做到 $O(n+m)$，可以把空间限制开到 1M。

下面是代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2222;
int n,m,D[N],t[N],o[N],p;
vector<pair<int,int> >e[N],g[N];
void dij(vector<pair<int,int> >*E,int S,int L,int*s){
	for(int i=1;i<=n;i++) o[i]=s[i]=1e9;
	priority_queue<pair<int,int> >q;
	for(q.push({s[S]=0,S});q.size();){
		int x=q.top().second;
		q.pop();
		if(o[x]<1e9) continue;
		o[x]=s[x];
		for(auto[i,v]:E[x]) if(i<=L||x<=L) if(s[i]>v+s[x]) q.push({-(s[i]=v+s[x]),i});
	}
	for(int i=1;i<=n;i++) for(auto[j,v]:E[i]) s[j]=min(s[j],o[i]+v);
	for(int i=L+1;i<=n;i++) for(auto[j,v]:E[i]) if(j>i) s[j]=min(s[j],s[i]+v);
}
int main(){
	cin>>n>>m;
	for(int i=1,j,k,l;i<=m;i++){
		scanf("%d %d %d",&j,&k,&l);
		e[j].push_back({k,l});
		g[k].push_back({j,l});
	}
	for(int i=1;i<=n;i++){
		dij(e,i,n,D);
		dij(e,i,i,t);
		for(int j=i+1;j<=n;j++) p+=t[j]!=D[j];
	}
	for(int i=1;i<=n;i++){
		dij(g,i,n,D);
		dij(g,i,i,t);
		for(int j=i+1;j<=n;j++) p+=t[j]!=D[j];
	}
	cout<<p;
}
```

---

## 作者：Purslane (赞：2)

# Solution

不要分析问题性质！不要分析问题性质！不要分析问题性质！

本题最难的地方是想到第二个 Floyd 是没啥非常好用的特殊结构的，要硬做。

设 $ok_{i,j}$ 为，第二种 Floyd 目前是否把 $(i,j)$ 算对了。

则转移是：

$$
ok_{i,j} = \bigcup_{k} ok_{i,k} ok_{k,j} \text{check}(i,k,j)
$$

其中 $\text{check}(i,j,k)$ 的含义是：是否有 $dis_{i,j} + dis_{j,k} = dis_{i,k}$。

考虑给定 $i$ 的时候，满足 $\text{check(i,k,j)}=1$ 的 $(k,j)$。可以用最短路图维护（做 $O(nm)$ 次大小为 $O(n)$ 的 `bitset` 运算，绰绰有余）

动态维护 $S_i = \{k \mid ok_{i,k} = 1\}$ 和 $T_i = \{k \mid ok_{k,i}=1 \}$ 即可。

无压力通过。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e3+10,INF=0x3f3f3f3f;
int n,m,ok[MAXN][MAXN],dis[MAXN][MAXN];
bitset<MAXN> chk[MAXN],s[MAXN],t[MAXN];
vector<pair<int,int>> G[MAXN],g[MAXN];
struct Node {int u,dis;};
bool operator <(Node A,Node B) {return A.dis>B.dis;}
int vis[MAXN],tdis[MAXN];
void solve(int u) {
	memset(vis,0,sizeof(vis)),memset(tdis,0x3f,sizeof(tdis));
	vis[u]=0,tdis[u]=0;
	priority_queue<Node> q;
	q.push({u,0});
	while(!q.empty()) {
		int u=q.top().u;
		q.pop();
		if(vis[u]) continue ;
		vis[u]=1;
		for(auto pr:G[u]) {
			int to=pr.first,w=pr.second;
			if(tdis[u]+w<tdis[to]) tdis[to]=tdis[u]+w,q.push({to,tdis[to]});
		}
	}
	ffor(i,1,n) dis[u][i]=tdis[i];
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,m) {
		int u,v,w;
		cin>>u>>v>>w,G[u].push_back({v,w}),g[v].push_back({u,w}); 
	}
	ffor(i,1,n) solve(i);
	ffor(u,1,n) ok[u][u]=s[u][u]=t[u][u]=1;
	ffor(u,1,n) for(auto pr:G[u]) if(dis[u][pr.first]==pr.second) ok[u][pr.first]=1,s[u][pr.first]=t[pr.first][u]=1;
	ffor(u,1,n) {
		ffor(i,1,n) chk[i].reset(),chk[i][i]=1;
		vector<pair<int,int>> st;
		ffor(v,1,n) st.push_back({dis[u][v],v});
		sort(st.begin(),st.end());
		ffor(id,1,n) {
			int v=st[id-1].second;
			for(auto pr:g[v]) if(dis[u][v]==dis[u][pr.first]+pr.second) chk[v]|=chk[pr.first];
		}
		ffor(v,1,n) if((s[u]&t[v]&chk[v]).count()) ok[u][v]=s[u][v]=t[v][u]=1;
	}
	int ans=0;
	ffor(i,1,n) ffor(j,1,n) if(dis[i][j]<INF&&!ok[i][j]) ans++;
	cout<<ans;
	return 0;
}
```

---

## 作者：wwt100127 (赞：0)

首先两点之间的距离用 $n$ 次 Dijkstra 就可以了。

然后考虑什么样的边会被正确求出：

假设正在求 $(x,y)$：

- 若 $x$，$y$ 间有边，则边权等于正常求法下的 $dist_{x,y}$。

- 存在一个点 $p$ 使得 $dist_{x,p}$ 和 $dist_{p,y}$ 能正确求出，且在正常求法下 $dist_{x,p} + dist_{p,y} = dist_{x,y}$。

用 bitset 维护即可（代码中的 $c_{i,j}$ 指的是从当前节点出发，$i$ 为终点，$j$ 是否可做“转移点”）。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mp(x,y) make_pair(x,y)
#define se second
#define fi first
using namespace std;
using PII=pair<int,int>;
const int maxn=2e3+5;
const int maxm=2*maxn;
const int INF=0x3f3f3f3f3f3f3f3fll;
int n,m;

namespace Graph
{
	int head[maxn],tot_edge;
	struct edge
	{
		int v,w,next;
	}e[maxm];
	void G_init()
	{
		memset(head,-1,sizeof(head));
		tot_edge=-1;
	}
	void add(int u,int v,int w)
	{
		e[++tot_edge]=(edge){v,w,head[u]};
		head[u]=tot_edge;
	}
} using namespace Graph;

bitset<maxn> s[maxn],t[maxn],c[maxn];
int D[maxn][maxn];
int dist[maxn];
bool vis[maxn];
priority_queue<PII,vector<PII>,greater<PII> >q;
void Dijkstra(int s)
{
	int i;
	memset(dist,0x3f,sizeof(dist));
	memset(vis,0,sizeof(vis)); 
	dist[s]=0; q.push(mp(0,s));
	while(q.size())
	{
		int x=q.top().se;
		q.pop();
		if(vis[x])
		continue;
		vis[x]=1;
		for(i=head[x];~i;i=e[i].next)
		{
			int y=e[i].v;
			if(dist[y]>dist[x]+e[i].w)
			{
				dist[y]=dist[x]+e[i].w;
				q.push(mp(dist[y],y));
			}
		}
	}
	for(i=1;i<=n;i++) D[s][i]=dist[i];
}
void GetC(int s)
{
	int i;
	for(i=1;i<=n;i++) c[i].reset();
	memset(dist,0x3f,sizeof(dist));
	memset(vis,0,sizeof(vis)); 
	dist[s]=0; q.push(mp(0,s));
	while(q.size())
	{
		int x=q.top().se;
		q.pop();
		if(vis[x])
		continue;
		vis[x]=1;
		for(i=head[x];~i;i=e[i].next)
		{
			int y=e[i].v;
			if(dist[y]>dist[x]+e[i].w)
			{
				dist[y]=dist[x]+e[i].w;
				c[y]=c[x]; c[y][x]=1;
				q.push(mp(dist[y],y));
			}
			else
			if(dist[y]==dist[x]+e[i].w)
			{
				c[y]|=c[x];
				c[y][x]=1;
			}
		}
	}
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int i,j,u,v,w,x,y;
	cin>>n>>m;
	G_init();
	for(i=1;i<=m;i++)
	{
		cin>>u>>v>>w;
		add(u,v,w);
	}
	for(i=1;i<=n;i++)
	Dijkstra(i);
	for(i=1;i<=n;i++)
	s[i][i]=t[i][i]=1;
	for(x=1;x<=n;x++)
	{
		for(i=head[x];~i;i=e[i].next)
		{
			int y=e[i].v;
			if(D[x][y]==e[i].w)
			s[x][y]=t[y][x]=1;
		}
	}
	for(x=1;x<=n;x++)
	{
		GetC(x);
		for(y=1;y<=n;y++)
		{
			if((s[x]&t[y]&c[y]).any())
			s[x][y]=t[y][x]=1;
		}
	}
	int ans=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		ans+=(D[i][j]<=INF/2 && !s[i][j]);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：_lmh_ (赞：0)

先用 $n$ 次 Dijkstra 求出所有点对之间的距离，如果存在一条最短路只有一条边那么显然这个点对可以被正确求出。

否则，考虑 $y=u,z=v$ 时枚举中转点 $x$ 的过程，必须存在一个可能的中转点 $w$ 满足 $d_{u,w}+d_{w,v}=d_{u,v}$ 且 $(u,w),(w,v)$ 均能被正确算出。

用 `bitset` 维护对一个 $u$ 能被正确算出的所有 $(u,v)$ 和所有 $(v,u)$；同时在转移的时候再做一遍 `Dijkstra` 找出对一个 $(u,v)$ 所有可能的中转点（这个如果在第一次做 Dijkstra 时存下来空间会爆），只需对三个 bitset 取交集就可以得出结果。

时间复杂度 $O(\frac{n^3}{w}+nm\log m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2007,M=3007;
struct edge{ll to,w,nxt;}e[M];
ll n,m,hd[N],nE,dis[N],ans,vis[N],d[N][N],W[N][N];
priority_queue<pair<ll,ll> > pq;
bitset<N> F[N],G[N],X[N];
void add(int u,int v,int w){e[++nE]=(edge){v,w,hd[u]};hd[u]=nE;}
void Dijkstra(int s){
	memset(vis,0,sizeof(vis));memset(dis,0x3f,sizeof(dis));
	for (int i=1;i<=n;++i) X[i].reset();
	dis[s]=0;pq.push(make_pair(-dis[s],s));
	while(!pq.empty()){
		ll u=pq.top().second;pq.pop();
		if (vis[u]) continue;
		vis[u]=1;
		for (ll v,w,i=hd[u];i;i=e[i].nxt) if (!vis[v=e[i].to]){
			if (dis[v]>dis[u]+(w=e[i].w)){dis[v]=dis[u]+w;pq.push(make_pair(-dis[v],v));X[v]=X[u];X[v].set(u);}
			else if (dis[v]==dis[u]+w){
				X[v]|=X[u];X[v].set(u);
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);memset(W,0x3f,sizeof(W));
	cin>>n>>m;
	for (ll u,v,w,i=1;i<=m;++i){
		cin>>u>>v>>w;add(u,v,w);W[u][v]=min(W[u][v],w);
	}
	for (int i=1;i<=n;++i){
		Dijkstra(i);
		for (int j=1;j<=n;++j) d[i][j]=dis[j];
	}
	for (int u=1;u<=n;++u){
		for (int v=1;v<=n;++v){
			if (u==v||d[u][v]==W[u][v]){F[u][v]=G[v][u]=1;}
		}
	}
	for (int u=1;u<=n;++u){
		Dijkstra(u);
		for (int v=1;v<=n;++v) if (!F[u][v]){
			if (!(F[u]&G[v]&X[v]).none()) F[u][v]=G[v][u]=1;
			else ++ans;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

