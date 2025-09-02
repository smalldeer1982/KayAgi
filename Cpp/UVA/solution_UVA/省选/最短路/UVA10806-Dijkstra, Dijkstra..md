# Dijkstra, Dijkstra.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1747

[PDF](https://uva.onlinejudge.org/external/108/p10806.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10806/e738bac0dde02ff0489078ea146317a0237c7c29.png)

## 样例 #1

### 输入

```
2
1
1 2 999
3
3
1 3 10
2 1 20
3 2 50
9
12
1 2 10
1 3 10
1 4 10
2 5 10
3 5 10
4 5 10
5 7 10
6 7 10
7 8 10
6 9 10
7 9 10
8 9 10
0```

### 输出

```
Back to jail
80
Back to jail```

# 题解

## 作者：VenusM1nT (赞：7)

楼上写$Spfa$的巨佬也太神了吧……%%%

我这种小蒟蒻就只会写费用流……

~~这不是费用流裸题吗怎么做到写Spfa的~~

~~这个题目名字就已经明示这题不用Dijkstra/Spfa了居然还能用Spfa写出来也太神了吧！~~

咳咳，来讲讲费用流怎么做

首先发现限制边流量，即只能经过一次，想到网络流，然后要求最短路径，网络流 $\Rightarrow$ 费用流

于是我们在建边时，对每条边建**两条边**，分别为从$u$到$v$，从$v$到$u$，流量为$1$，费用为长度，最后建超级源$S$到$1$号点一条边，流量为$2$，代表要走两次（即往返路径，可以将它拆成两条路径，因为是无向图），跑一遍最小费用最大流就可求出答案

输出答案时记得判断是否满流，不满流要输出无解$Back$ $to$ $jail$，否则输出最小费用

见代码

```cpp
#include<bits/stdc++.h>
#define inf 1010580540
using namespace std;
deque <int> q;
int cnt,fst[1005],nxt[200005],to[200005],w[200005],cot[200005],cur[1005];
int n,m,S,T,dis[1005],maxflow,mincost;
bool inq[1005],vis[1005];
void AddEdge(int u,int v,int c,int fl)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
	w[cnt]=c;
	cot[cnt]=fl;
}
bool Spfa()
{
	memset(dis,60,sizeof(dis));
	memset(inq,0,sizeof(inq));
	q.push_front(T);
	dis[T]=0;
	inq[T]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop_front();
		inq[u]=0;
		for(int i=fst[u];i;i=nxt[i])
		{
			int v=to[i];
			if(dis[v]>dis[u]-cot[i] && w[i^1])
			{
				dis[v]=dis[u]-cot[i];
				if(!inq[v])
				{
					if(!q.empty() && dis[v]<dis[q.front()]) q.push_front(v);
					else q.push_back(v);
					inq[v]=1;
				}
			}
		}
	}
	return dis[S]!=inf;
}
int Dfs(int u,int flow)
{
	vis[u]=1;
	if(u==T || !flow) return flow;
	int used=0;
	for(int i=cur[u];i;i=nxt[i])
	{
		cur[u]=i;
		int v=to[i];
		if(dis[v]==dis[u]-cot[i] && w[i] && !vis[v])
		{
			int fl=Dfs(v,min(flow,w[i]));
			if(fl)
			{
				used+=fl;
				flow-=fl;
				w[i]-=fl;
				w[i^1]+=fl;
				if(!flow) break;
			}
		}
	}
	return used;
}
void zkwMCMF()
{
	while(Spfa())
	{
		vis[T]=1;
		while(vis[T])
		{
			memcpy(cur,fst,sizeof(fst));
			memset(vis,0,sizeof(vis));
			int fl=Dfs(S,inf);
			maxflow+=fl;
			mincost+=dis[S]*fl;
		}
	}
}
int main()
{
	while(cin>>n)
	{
		if(!n) break;
		scanf("%d",&m);
		cnt=1;
		maxflow=mincost=0;
		memset(fst,0,sizeof(fst));
		S=0;
		T=n;
		for(int i=1;i<=m;i++)
		{
			int x,y,z;
			scanf("%d %d %d",&x,&y,&z);
			AddEdge(x,y,1,z);
			AddEdge(y,x,0,-z);
			AddEdge(y,x,1,z);
			AddEdge(x,y,0,-z);
		}
		AddEdge(S,1,2,0);
		AddEdge(1,S,0,0);
		zkwMCMF();
		if(maxflow!=2) printf("Back to jail\n");
		else printf("%d\n",mincost);
	}
	return 0;
}
```

---

## 作者：liangbowen (赞：2)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/UVA10806)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17083572.html)

费用流简单题。

## 思路

数据范围这么小，也肯定不是让你跑 Dijkstra 之类的。

考虑费用流。建立一个超级源点 $S$，连边 $S \xrightarrow{cap = 1 \ cost = 0} 1$，表示要来回两次。

然后直接建图，对于图中的两个点 $(u, v)$，建**双向**边 $u \xrightarrow{cap = 1 \ cost = w} v$，原因显然。

然后跑板子即可。如果最后的流量不是 $2$，说明不能跑满来回这两次。输出无解。

否则输出代价即可。注意多测清空。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 105, inf = 0x3f3f3f3f;
struct Edge {int now, nxt, w, cost;} e[114514];
int head[N], cur = 1;
void ad(int u, int v, int  w, int cost)
{
    e[++cur].now = v, e[cur].nxt = head[u], e[cur].w = w, e[cur].cost = cost;
    head[u] = cur;
}
void add(int u, int v, int w, int cost) {ad(u, v, w, cost), ad(v, u, 0, -cost);}
int dis[N], icost[N], pre[N]; bool inque[N];
int s, t;
bool spfa()
{
    queue <int> q;
    memset(dis, 0x3f, sizeof dis), memset(icost, 0, sizeof icost);
    q.push(s), dis[s] = 0, icost[s] = inf, inque[s] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), inque[u] = false;
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].now;
            if (!e[i].w) continue;
            if (dis[u] + e[i].cost < dis[v])
            {
                dis[v] = dis[u] + e[i].cost, pre[v] = i;
                icost[v] = min(icost[u], e[i].w);
                if (!inque[v]) q.push(v), inque[v] = true;
            }
        }
    }
    return icost[t] > 0;
}
void EK(int &flow, int &cost)
{
    while (spfa())
    {
        int w = icost[t];
        flow += w, cost += w * dis[t];
        for (int i = t; i != s; i = e[pre[i] ^ 1].now)
            e[pre[i]].w -= w, e[pre[i] ^ 1].w += w;
    }
}
void solve()
{
	memset(head, 0, sizeof head), cur = 1;
    int n, m;
	scanf("%d%d", &n, &m);
    if (n == 0) exit(0);
    
	s = 0, t = n; add(s, 1, 2, 0);
	while (m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, 1, w), add(v, u, 1, w);
	}
	int flow = 0, cost = 0; EK(flow, cost);
	if (flow != 2) puts("Back to jail"); else cout << cost << '\n';
}
int main()
{
	while (true) solve();
	return 0;
}
```

---

## 作者：strcmp (赞：2)

这是一道比较裸的网络流，实质就是**查询两点之间的“最短往返路”**，对于这道题的连边，上面几篇题解已经给出很清晰的方法，这篇题解**主要是讲为什么要这样连边。**

首先，我们看连边方式：
```
对于输入的边，我们对边上的两个节点方互相连费用为权值，容量为 1 的边。

最后，增加超级源 s，从 s 到 1 连一条容量为 2 ，费用为 0 的边。

跑最小费用最大流，即是答案。

无解的情况，跑出来的最大流不足 2 时判无解。
```

$\cdot$ 为什么要双向连边？

因为是无向图。

$\cdot$ **为什么要限制流量为 $1$？**

因为不能走相同的路，如果这条路走过了，那么它就相当于被堵死了，也就不能从这里走过。

$\cdot$ **为什么要增加超级源 $s$？**

因为要限制流量（即限制走的次数）。

$\cdot$ **为什么要从 $s$ 连向 $1$ 点容量为 2 的边。**

因为要走两次，所以容量为 $2$，比如如果要走三次，容量就为 $3$，以此类推......

$\cdot$ 为什么在流量不足 $2$ 的时候判无解？

因为如果流量不足 $2$，即代表从 $1$ 到 $n$ 无论如何也无法走两条不相交的路径。

这道题的疑惑基本上解决了，接下来请看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define inf 1000000000000000
#define V 100100
#define E 500100
typedef long long int ll;
struct edge {
	int to, next;
	ll capa, cost;
};
int cnt = 0, head[V], n, m; edge node[E];
inline void add(int fir, int nxt, ll w, ll c) {
	node[cnt].to = nxt,
	node[cnt].capa = w,
	node[cnt].cost = c,
	node[cnt].next = head[fir],
	head[fir] = cnt++;
}
int s, t, cur[V]; deque<int>que; ll dep[V], sum = 0, cost = 0;
bool vis[V];
inline bool spfa(){
	for(register int i = 0;i <= n;++i)dep[i]=inf;
	dep[s] = 0; que.push_back(s); int u, v;
	while(!que.empty()){
		v = que.front(); que.pop_front();
		for(register int i = head[v]; i != -1; i = node[i].next){
			u = node[i].to;
			if(dep[v] + node[i].cost < dep[u] && node[i].capa){
				dep[u] = dep[v] + node[i].cost;
				if(!que.empty() && dep[u]<dep[que.front()])que.push_front(u);
				else que.push_back(u);
			}
		}
	}
	return (dep[t] != inf);
}
ll dfs(register int v,register ll flow){
	if(v == t || flow == 0)return flow; ll used = 0, wei = 0;
	vis[v]=true;
	for(register int i = cur[v]; i != -1; i = node[i].next){
		cur[v] = i;
		if(!vis[node[i].to] && dep[node[i].to] == dep[v] + node[i].cost && node[i].capa){
			wei = dfs(node[i].to, min(flow - used, node[i].capa));
			if(wei){
				node[i].capa -= wei,
				node[i ^ 1].capa += wei,
				used += wei,
				cost += node[i].cost * wei;
			}
		}
		if(used == flow)break;
	}
	vis[v]=false;
	return used;
}
inline void Dinic(){
	while(spfa()){
		memcpy(cur,head,(n + 1)*sizeof(int));
		sum += dfs(s,inf);
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(); cout.tie();
	memset(head, -1, V * sizeof(int));
	int f, l; ll w, c;
	while(1){
		cin >> n;
		if(n == 0)exit(0);
		cin >> m;
		s = 0, t = n;
		for (register int i = 0; i < m; ++i) {
			cin >> f >> l >> c;
			add(f, l, 1, c), add(l, f, 0, -c);
			add(l, f, 1, c), add(f, l, 0, -c);
		}
		add(s, 1, 2, 0); add(1, s, 0, 0);
		Dinic();
		if(sum != 2)cout<<"Back to jail\n";
		else cout << cost << endl;
		for(register int i = 0; i <= n; i++)head[i] = -1;
		for(register int i = 0; i <= cnt; i++)node[i].to = node[i].capa = node[i].cost = 0;
		sum = cost = cnt = 0;
	}
	return 0;
}
```


---

## 作者：JK_LOVER (赞：1)

## 题意
给你一张无向图，求出在一条边只走一次的前提下，求出从起点到终点再回到起点的最短路径。[qwq](https://www.luogu.com.cn/blog/xzc/solution-uva10806) 。
## 分析
因为要走过去，再回来的过程中每条边只走一次。所以朴素的最短路是行不通的。

- 走一个来回，在无向图中其实是等价于从起点连续走两次的。

- 考虑如何做到每条边只走一次。一次这个条件其实是对这条边的容量限制。那么我们就可以用 $MinCostMaxFlow$ 来求解。

一条无向边，可以拆成两条有向边。那么这两条有向边总共只走一次是怎么做到的。我们可以发现，在建反向边时候我们是建了条花费为 $-w$ 的边。如果从另一个方向走过了，在找最短路时我们一定会走反向边。所以这种情况其实都不用考虑的。

- 那么我们把 $S$ 连向 $1$ 点， $n$ 点连向 $T$ 点，容量为 $2$ 。这样就可以完美解决这道题了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int inf = 0x3f3f3f3f;
const int N = 2010;
int n,m,head[N],cnt,S,T;
struct edge{int cap,flow,nxt,to,w;}e[N];
void add(int x,int y,int c,int f,int w)
{
	e[++cnt].flow = f;e[cnt].cap = c;
	e[cnt].to = y;e[cnt].nxt = head[x];e[cnt].w = w;
	head[x] = cnt;
}
int cost,maxflow;
int lastedge[N],lastnode[N],a[N],dis[N],vis[N];
bool bfs(int s,int t)
{
	memset(dis,inf,sizeof(dis));
	memset(a,0,sizeof(a));
	memset(vis,0,sizeof(vis));
	deque<int> que;
	a[s] = inf;dis[s] = 0;lastnode[s] = -1;vis[s] = 1;
	que.push_back(s);
	while(que.size())
	{
		int x = que.front();
		que.pop_front();
		vis[x] = 0;
		for(int i = head[x];~i;i = e[i].nxt)
		{
			if(e[i].cap > e[i].flow)
			{
				int y = e[i].to;
				if(dis[y] > dis[x] + e[i].w)
				{
					lastnode[y] = x;
					lastedge[y] = i;
					dis[y] = dis[x] + e[i].w;
					a[y] = min(e[i].cap - e[i].flow,a[x]);
					if(vis[y]) continue;
					vis[y] = 1;
					if(que.size())
					{
						if(dis[y] < dis[que.front()])
						que.push_front(y);
						else que.push_back(y);
					}
					else que.push_back(y);
				}
			}
		}
	}
	return a[t] > 0;
}
void addedge()
{
	m = read();
	for(int i = 1;i <= m;i++)
	{
		int x = read(),y = read(),w = read();
		add(x,y,1,0,w);
		add(y,x,0,0,-w);
		add(y,x,1,0,w);
		add(x,y,0,0,-w);
	}
	add(S,1,2,0,0);
	add(1,S,0,0,0);
	add(n,T,2,0,0);
	add(T,n,0,0,0);
}
int EK(int s,int t)
{
	memset(head,-1,sizeof(head));
	cnt = -1;cost = 0;maxflow = 0;
	addedge();
	while(bfs(s,t))
	{
		cost += dis[t]*a[t];
		maxflow += a[t];
		int u = t;
		while(u != s)
		{
			e[lastedge[u]].flow += a[t];
			e[lastedge[u]^1].flow -= a[t];
			u = lastnode[u];	
		}
	}
	return cost;
}
int main()
{
	while(1){
		n = read();
		if(!n) break;
		S = n+10;
		T = n+20;
		int ans = EK(S,T);
		if(maxflow == 2)
		cout<<ans<<endl;
		else cout<<"Back to jail"<<endl;
	}	
	return 0;
} 
```


---

## 作者：EmptyAlien (赞：0)

[Dijkstra, Dijkstra. - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/UVA10806)

## 题意简述

- 给你一个有 $n$ 个点，$m$ 条边的**加权无向图**

- 求 $1$ 到 $n$ 再到 $1$ 的**最短路径**

- 且**一条边不能经过两次**

## 题目分析

这是一道比较经典的**最小费用最大流**的问题。

问题在于建图（实际上很多网络流题目重点都在建图上）。

从 $1$ 到 $n$ 再返回 $1$，实际上可以看成是从 $1$ 开始往 $n$ 走两次（原题义也确实如此）。

那我们可以让每条边最多只能流过去 $1$ 次，而费用即为通过边所需的时间，这样就满足了一条边只能走一次的要求。

而为了让它走两遍，我们**建一个超级起点** $0$，与**超级终点** $n+1$，让 $0$ 往 $1$ 连一条费用为 $0$，流量上限为 $2$ 的边，同理，让 $n$ 往 $n + 1$ 连一条费用为 $0$，流量上限为 $2$ 的边。

如此一来，若最大流为 $2$，则该题有解，输出最小费用。

否则，该题无解，输出 `Back to jail`。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int M = 5005;
const int INF = 0x3f3f3f3f;

// ================================================================================
// 链式前向星
struct Node{
	int to;
	int next;
	int cap;
	int flow;
	int cost;
}e[4 * M]; // 无向图最大流需要乘4倍
int head[N];
int tot;
void Init() {
	tot = 0;
	memset(head, 0xff, sizeof head);
}
void Add(int u, int v, int cap, int cost) {
	e[tot].to = v;
	e[tot].cap = cap;
	e[tot].flow = 0;
	e[tot].cost = cost;
	e[tot].next = head[u];
	head[u] = tot;
	tot++;
}
void Edge(int u, int v, int cap, int cost) {
	Add(u, v, cap, cost);
	Add(v, u, 0, -cost);
}

// ===============================================================================
// 最小费用最大流
int minCost;
int maxFlow;
int dis[N];
bool vis[N];
int pre[N];
bool SPFA(int s, int t) {
	queue<int> q;
	memset(dis, 0x3f, sizeof dis);
	memset(vis, 0, sizeof vis);
	memset(pre, 0xff, sizeof pre);
	q.push(s);
	vis[s] = true;
	dis[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (int i = head[u]; i != -1; i = e[i].next) {
			int v = e[i].to;
			if (e[i].cap > e[i].flow and dis[v] > dis[u] + e[i].cost) {
				dis[v] = dis[u] + e[i].cost;
				pre[v] = i;
				if (!vis[v]) {
					q.push(v);
					vis[v] = true;
				}
			}
		}
	}
	return pre[t] != -1;
}
void MCMF(int s, int t) {
	int d;
	minCost = 0;
	maxFlow = 0;
	while (SPFA(s, t)) {
		d = INF;
		for (int i = pre[t]; i != -1; i = pre[e[i^1].to]) {
			d = min(d, e[i].cap - e[i].flow);
		}
		maxFlow += d;
		for (int i = pre[t]; i != -1; i = pre[e[i^1].to]) {
			e[i].flow += d;
			e[i ^ 1].flow -= d;
		}
		minCost += dis[t] * d;
	}
}

// ==============================================================================

int n, m;
void Solve() {
	Init();
	cin >> m;
	Edge(0, 1, 2, 0);
	Edge(n, n + 1, 2, 0);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
        // 记住，这是一个无向图
		Edge(u, v, 1, w);
		Edge(v, u, 1, w);
	}
	MCMF(0, n + 1);
	if (maxFlow == 2) {
		cout << minCost << endl;
	} else {
		cout << "Back to jail" << endl;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	while (n != 0) {
		Solve();
		cin >> n;
	}
	return 0;
}
```


---

