# Binary Tree on Plane

## 题目描述

A root tree is a directed acyclic graph that contains one node (root), from which there is exactly one path to any other node.

A root tree is binary if each node has at most two outgoing arcs.

When a binary tree is painted on the plane, all arcs should be directed from top to bottom. That is, each arc going from $ u $ to $ v $ must meet the condition $ y_{u}&gt;y_{v} $ .

You've been given the coordinates of all tree nodes. Your task is to connect these nodes by arcs so as to get the binary root tree and make the total length of the arcs minimum. All arcs of the built tree must be directed from top to bottom.

## 样例 #1

### 输入

```
3
0 0
1 0
2 1
```

### 输出

```
3.650281539872885
```

## 样例 #2

### 输入

```
4
0 0
1 0
2 1
2 0
```

### 输出

```
-1
```

# 题解

## 作者：Gypsophila (赞：8)

### Description
给你平面上 $n$ 个点 $(2 \leq n \leq 400)$，要求用这些点组成一个二叉树(每个节点的儿子节点不超过两个)，定义每条边的权值为两个点之间的欧几里得距离。求一个权值和最小的二叉树，并输出这个权值。

其中，点 $i$ 可以成为点 $j$ 的的父亲的条件是：点 $i$ 的 $y$ 坐标比 $j$ 的 $y$ 坐标大。

如果不存在满足条件的二叉树，输出 $-1$ 。

### Solution

边 $(a,b)$ 表示一条容量为 $a$ ，费用为 $b$ 的边

把每个点 $u$ 拆成两个点入点 $u_1$ 和出点 $u_2$ 

从源点向 $u_1$ 连一条 $(2,0)$，意义为限制了  $u$ 只能有两个儿子

从 $u_2$  向汇点连一条 $(1,0)$ ，意义是限制了 $u$ 最多只有一个父亲

若 $u_y > v_y$ 则在 $u_1$ 和 $v_2$ 之间连一条 $(1,Len)$，其中 Len 是两点之间的距离 $\sqrt {(u_x - v_x)^2 + (u_y-v_y)^2}$

然后跑最小费用最大流完事。

### Code
[看代码戳这里](https://www.cnblogs.com/acfunction/p/10105432.html)

---

## 作者：KAMIYA_KINA (赞：4)

## 提要

本题需要一定的网络流基础，是一道非常好的 **最小费用最大流** 题目。

## 正文

本题中给出了一个二叉树的约束关系，当贪心思想十分难以处理约束关系的时候，我们更多时候需要用网络流的思想去解决题目的约束。

我们思考这样一个问题，一个点最多的儿子节点是 $2$  个，父亲节点是一个，而且必须保证只有一个节点没有父亲节点。那么我们的约束肯定就是从父亲节点和儿子节点中的关系来考虑。

考虑一个儿子节点会对应一个父亲节点，那么我们就可以分别考虑一个点成为父亲节点和儿子的情况，两个点的情况我们将一个点 $u$ 分别拆成 $u_1,u_2$（注意这里的 $u$ 只代表一种变量情况，下文中出现的一些新的命名与这里的拆点表示的是同样的意义），设 $u_1$ 代表着成为父亲节点时儿子节点的约束情况， $u_2$ 代表着成为儿子节点时的被约束情况，$u_1$ 向超级源点连流量为 $2$ 的边，$u_2$ 向超级汇点连流量为 $1$ 的边，用流量限制约束关系。

考虑当一个点成为另一个点的儿子节点时会产生的贡献如何设置：

由于我们已经将流量设为了约束关系，而且网络流中是很难用小数当做流量的，所以我们很自然的想到了 **费用** 。

当 $u$ 点可以成为 $v$ 点的父亲节点时，就将 $u_1$ 点连向 $v_2$ 点，流量随便（中间的边权并不影响点之间的约束关系，点的约束只与源点和汇点有关），边权为两点之间的距离。

## 代码

~~~cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
const int N = 1e6 + 1;
const int INF = 1e9 + 1;
struct node {
    int x,y;
    bool operator<(const node &tem)const{return y > tem.y;}
};
int hd[N],nxt[N],to[N],cap[N],tot = 1,cur[N],flow[N],pre[N],lst[N];
double val[N],ans = 0,dis[N];
bool vis[N];
int s,t,n;
node p[N];
inline void add(const int u,const int v,const int z,const double k) {nxt[++tot] = hd[u],to[tot] = v,cap[tot] = z,val[tot] = k,hd[u] = tot;}
inline void adds(const int u,const int v,const int z,const double k) {add(u,v,z,k),add(v,u,0,-k);}
inline double calc(const int u,const int v) {return sqrt((double)(p[u].x - p[v].x) * (p[u].x - p[v].x) + (p[u].y - p[v].y) * (p[u].y - p[v].y));}
inline bool SPFA(){
    queue<int>Q;
    for(int i = 1; i <= t; i++) flow[i] = INF,dis[i] = INF,vis[i] = false;
    Q.push(s); vis[s] = 1; dis[s] = 0; pre[t] = -1;
    while (!Q.empty()) {
        int now = Q.front(); Q.pop(),vis[now]=0;
        for (int eg = hd[now]; eg ; eg = nxt[eg]) {
            int v = to[eg];
            if (cap[eg] && dis[v] > dis[now] + val[eg]){
                dis[v] = dis[now] + val[eg],pre[v] = now,lst[v] = eg;
                flow[v] = min(flow[now],cap[eg]);
                if (!vis[v]) vis[v] = true,Q.push(v);
            }
        }
    }
    return pre[t]!=-1;
}

int mcmf(){
    int sum = 0;
    while (SPFA()) {
        int now = t;
        sum += flow[t],ans += flow[t] * dis[t];
        while (now != s){
            now[lst][cap] -= flow[t];
            (now[lst] ^ 1)[cap] += flow[t];
            now = pre[now];
        }
    }
    return sum;
}
int main() {
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) scanf("%d%d",&p[i].x,&p[i].y);
    sort(p + 1,p + 1 + n);
    s = n << 1 + 1,t = n << 1 + 2;
    for(int i = 1; i <= n; i++) adds(s,i,2,0),adds(i + n,t,1,0);
    for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) if(p[i].y > p[j].y) adds(i,j + n,1,calc(i,j));//两点之间的连边。
    if(mcmf() != n - 1) puts("-1");//如果说有父亲节点的节点个数不足 n - 1 个的话，那么就代表没有解
    else printf("%.6lf\n",ans);
    return 0;
}
~~~

## 题外话

这道题我用 $\text{dinic}$ 死都卡不过去，然后换了 $\text{EK}$ 之后就过了，所以说这种单条路拓展的图还是用 $\text{EK}$ 循环还是快一些， $\text{dinic}$ 递归的常数实在是太大了。

---

## 作者：chenxia25 (赞：4)

注意到对于一个边集是一棵树当且仅当，只有一个点没有入边，其他点都恰好有一个入边，所有点的出边数量 $\leq 2$。于是我们可以针对这个度数建网络流。

我们考虑一条流表示新增上去一条边。那么 $s$ 到每个点连 $2$，每个点向 $t$ 连 $1$，两个点间该连连，费用照搞。然后跑最大流看是否等于 $n-1$，等于的话输出最小费用。

但这样有个 bug，那就是一条流可能不经过任何中间边，只经过一个点。那怎么办呢。**遇到这种逻辑混乱的，无法建图的，拆点！拆点！拆点！**考虑把每个点拆成两个点表示入出，入连向出并且自己不连向自己，正确性显然。

---

## 作者：FutaRimeWoawaSete (赞：3)

麻了，不知道为什么 dinic 一次跑不完所有增广路。             

其实在思路上感觉还是挺 trick 的吧，主要还是卡常，确信。                   

观察二叉树的性质，即每个点的入度为 $1$，考虑一条边就是让一个点的入度加 $1$，即每个点只会被匹配一次。            

套路的将一个点拆成两个点一个表示出点一个表示入点，做成一个二分图匹配状左边是出点右边是入点，从源点向所有入点连容量为 $2$ 的边，特判根节点后，使非根节点的所有出点都向 $t$ 连一条容量为 $1$ 的边，即可保证在有解的情况下最大流流量大小为 $n - 1$。

当然以上边的单价全为 $0$，毕竟没有实际意义。

为了避免讨论，我们在判无解时也直接用最大流流量是不是 $n - 1$ 特判就好了。          

$O(n ^ 2)$ 连边，对于每条有向边 $(u,v,w)$，让 $u$ 的出点向 $v$ 的入点连一条容量为 $1$ 单价为距离的边。

然后就是卡常了，卡了半个晚上的常还是找不出来为什么费用流的 dinic 一次跑不出来，最后就直接每次 SPFA 后多跑几次 dinic 就过了……如果有人愿意也可以来看下 dinic 里面哪里写爆了。            

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 5e2 + 5;
const double Inf = 2e6 + 1;
int n,m,head[Len * 2],cnt = 1,s,t,flag[Len * 2],Bs[Len * 2],len,SS,tt,maxflow,cur[Len * 2];
double dis[Len * 3],mincost;
struct node
{
	int next,to,w;double ww;
}edge[Len * Len * 2];
void add(int from,int to,int w,double ww)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	edge[cnt].w = w , edge[cnt].ww = ww;
	head[from] = cnt;
}
bool SPFA()
{
	queue<int> q;
	for(int i = 1 ; i <= (n * 2) + 2 ; i ++) dis[i] = Inf , flag[i] = 0;
	cur[s] = head[s] , dis[s] = 0 , flag[s] = 1 , q.push(s);
	while(!q.empty())
	{
		int p = q.front();q.pop();
		flag[p] = 0;
		for(int e = head[p] ; e ; e = edge[e].next)
		{
			int to = edge[e].to;
			if(dis[to] > dis[p] + edge[e].ww && edge[e].w)
			{
				dis[to] = dis[p] + edge[e].ww;
				cur[to] = head[to];
				if(!flag[to]) q.push(to) , flag[to] |= 1;
			}
		}
	}
	if(dis[t] == Inf) return 0;
	return 1;
}
int dfs(int u,int In)
{
	if(u == t) return In;
	flag[u] = 1;
	int Out = 0;
	for(int e = cur[u] ; e && In > 0 ; e = edge[e].next)
	{
		int to = edge[e].to;
		cur[u] = e;
		if(!flag[to] && edge[e].w && dis[to] == dis[u] + edge[e].ww)
		{
			int res = dfs(to , min(In , edge[e].w));
			mincost += res * edge[e].ww;
			In -= res;
			Out += res;
			edge[e].w -= res;
			edge[e ^ 1].w += res;		
		}
	} 
	flag[u] = 0;
	if(!Out) dis[u] = -1;
	return Out;
}
struct Node
{
	int x,y;
}P[Len];
struct Edge
{
	int u,v;double w;
	Edge(){u = v = w = 0;}
	Edge(int U,int V,double W){u = U , v = V , w = W;}
}E[Len * Len];
double dist(int x,int y,int X,int Y)
{
	return sqrt((X - x) * (X - x) + (Y - y) * (Y - y));
}
void Work(int a,int b)
{
	if(P[a].y > P[b].y) 
	{
		E[++ len] = Edge(a , b , dist(P[a].x , P[a].y , P[b].x , P[b].y));
		Bs[b] ++;
	}
}
int main()
{
	scanf("%d",&n);
	s = (n * 2) + 1 , t = s + 1;
	for(int i = 1 ; i <= n ; i ++) scanf("%d %d",&P[i].x,&P[i].y);
	for(int i = 1 ; i <= n ; i ++)
		for(int j = i + 1 ; j <= n ; j ++)
		{
			if(P[i].y > P[j].y) Work(i , j);
			else Work(j , i);
		}
	for(int i = 1 ; i <= n ; i ++)
	{
		add(s , i , 2 , 0) , add(i , s , 0 , 0);
		if(!Bs[i]) continue;
		add(i + n , t , 1 , 0) , add(t , i + n , 0 , 0);	
	} 
	for(int i = 1 ; i <= len ; i ++) add(E[i].u , E[i].v + n , 1 , E[i].w) , add(E[i].v + n , E[i].u , 0 , -E[i].w);
	while(SPFA()) 
	{
		while(1)
		{
			int res = dfs(s , 2000000);
			if(!res) break;
			maxflow += res;
		}
	}
	if(maxflow != n - 1) return puts("-1") & 0;
	printf("%.7lf\n",mincost);
 	return 0;
}
```

---

## 作者：rui_er (赞：1)

费用流。

可以将原问题转化为类似于匹配的问题，只不过这种匹配并不是一对一的。具体地，将每个点 $u$ 拆成两个点 $u_\text{fa},u_\text{son}$，设源点为 $s$、汇点为 $t$，则一条流 $s\to u_\text{fa}\to v_\text{son}\to t$ 就代表 $u$ 是 $v$ 的父亲。

一个节点最多作为两个节点的父亲，因此 $s\to u_\text{fa}$ 的容量为 $2$、代价为 $0$。一个节点最多作为一个节点的儿子，因此 $u_\text{son}\to t$ 的容量为 $1$、代价为 $0$。对于每一对节点 $(u,v)$，若 $u$ 可以作为 $v$ 的父亲，则连接一条边 $u_\text{fa}\to v_\text{son}$，容量为 $1$、代价为 $\sqrt{(\Delta x)^2+(\Delta y)^2}$。

求出最大流 $\text{MF}$ 和此时的最小费用 $\text{MC}$。根据上面的分析，可以构成一棵二叉树当且仅当 $\text{MF}=n-1$，此时的 $\text{MC}$ 就是最小权值和。

```cpp
// Problem: CF277E Binary Tree on Plane
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF277E
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;
const ll N = 1e3+5, M = 3e6+5, inf = 0x3f3f3f3f3f3f3f3fll;

ll n, s, t, x[N], y[N], vis[N], flow[N], pre[N];
double dis[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
struct Edge {
	ll v, w, nxt;
	double c;
	Edge(ll a=0, ll b=0, double c=0.0, ll d=0) : v(a), w(b), c(c), nxt(d) {}
}e[M];
ll h[N], ne = 1;
void add(ll u, ll v, ll w, double c) {
	e[++ne] = Edge(v, w, c, h[u]); h[u] = ne;
	e[++ne] = Edge(u, 0,-c, h[v]); h[v] = ne;
}
bool BellmanFord() {
	fill(dis, dis+1+t, 1e100);
	memset(vis, 0, sizeof(vis));
	memset(flow, 0x3f, sizeof(flow));
	queue<ll> q;
	dis[s] = 0.0;
	vis[s] = 1;
	pre[t] = -1;
	q.push(s);
	while(!q.empty()) {
		ll u = q.front(); q.pop();
		vis[u] = 0;
		for(ll i=h[u];i;i=e[i].nxt) {
			ll v = e[i].v, w = e[i].w;
			double c = e[i].c;
			if(w && dis[v] > dis[u] + c) {
				dis[v] = dis[u] + c;
				pre[v] = i;
				flow[v] = min(flow[u], w);
				if(!vis[v]) {
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return ~pre[t];
}
tuple<ll, double> MCMF() {
	ll maxflow = 0; double mincost = 0.0;
	while(BellmanFord()) {
		ll now = inf;
		for(ll u = t; u != s; u = e[pre[u]^1].v) chkmin(now, flow[u]);
		for(ll u = t; u != s; u = e[pre[u]^1].v) {
			e[pre[u]].w -= now;
			e[pre[u]^1].w += now;
			mincost += now * e[pre[u]].c;
		}
		maxflow += now;
	}
	return make_tuple(maxflow, mincost);
}
double dist(int i, int j) {
	double dx = x[i] - x[j], dy = y[i] - y[j];
	return sqrt(dx * dx + dy * dy);
}

int main() {
	scanf("%lld", &n);
	s = 2 * n + 1; t = 2 * n + 2;
	rep(i, 1, n) {
		scanf("%lld%lld", &x[i], &y[i]);
		add(s, i, 2, 0.0);
		add(i+n, t, 1, 0.0);
	}
	rep(i, 1, n) rep(j, 1, n) if(y[i] > y[j]) add(i, j+n, 1, dist(i, j));
	int maxflow; double mincost;
	tie(maxflow, mincost) = MCMF();
	if(maxflow < n - 1) puts("-1");
	else printf("%.15f\n", mincost);
	return 0;
}
```

---

## 作者：tzc_wk (赞：1)

安利个人 blog：https://www.cnblogs.com/ET2006/

注意到一张图是一棵树当且仅当只有一个点（根节点）没有父亲，其它点都有恰好一个父亲。并且每个点连向其儿子的边不超过 $2$，故可以以此为突破口建图。

做网络流题目首先要搞清楚三点：点表示什么，边表示什么，一条 $S$ 到 $T$ 的路径表示什么。这题我们可以用点表示原图中的点，一条 $S\to T$ 的三个点的路径 $S\to u\to v\to T$ 表示 $(u,v)$ 之间多了条边，其中 $u$ 是父亲，$v$ 是儿子。这样一来思路就出来了，对于每个点 $u$，连一条从 $S$ 到 $u$，容量为 $2$ 的边，表示 $u$ 最多是 $2$ 个节点的父亲；再连一条 $u$ 到 $T$，容量为 $1$ 的边，表示 $u$ 最多是一个节点的父亲。然后对于所有二元组 $(u,v)$ 满足 $u$ 能成为 $v$ 的父亲，连一条从 $u$ 到 $v$，容量为 $1$，费用为这两点之间的距离。然后跑最小费用最大流就行了，最大流限制边数必须为 $n-1$，最小费用保证权值和最小。如果最大流不是 $n-1$ 那么就不存在满足要求的二叉树，否则输出最小费用即可。

但这样做是有问题的，因为会出现 $S\to u\to T$ 的路径，也就是说自己可能会成为自己的儿子。碰到这种情况怎么办呢？拆点啊。考虑将每个点拆成 $u_1,u_2$ 两个点，$u_2$ 用于”接受父亲“，$u_1$ 用于“作为儿子”，也就是说，将原先 $S\to u$ 的边改为 $S\to u_1$，$S\to u$ 的边改为 $S\to u_2$，$u\to v$ 的边改为 $u_2\to v_1$。这样就不会出现"自己可能会成为自己的儿子"的情况了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=400;
const int MAXV=802;
const int MAXE=3e5;
const int INF=0x3f3f3f3f;
int n,x[MAXN+5],y[MAXN+5],S=801,T=802;
int hd[MAXV+5],to[MAXE+5],nxt[MAXE+5],cap[MAXE+5],ec=1;
double cst[MAXE+5];
double dis(int x1,int y1,int x2,int y2){
	return sqrt(1ll*(x2-x1)*(x2-x1)+1ll*(y2-y1)*(y2-y1));
}
void adde(int u,int v,int f,double c){
	to[++ec]=v;cap[ec]=f;cst[ec]=c;nxt[ec]=hd[u];hd[u]=ec;
	to[++ec]=u;cap[ec]=0;cst[ec]=-c;nxt[ec]=hd[v];hd[v]=ec;
}
double dist[MAXV+5];int flw[MAXV+5],pre[MAXV+5],lste[MAXV+5];
bool inq[MAXV+5];
bool getdis(){
	fill(dist,dist+MAXV+1,INF);memset(flw,0,sizeof(flw));
	dist[S]=0;flw[S]=INF;queue<int> q;q.push(S);inq[S]=1;
	while(!q.empty()){
		int x=q.front();q.pop();inq[x]=0;
		for(int e=hd[x];e;e=nxt[e]){
			int y=to[e],z=cap[e];double w=cst[e];
			if(dist[y]>dist[x]+w&&z){
				dist[y]=dist[x]+w;flw[y]=min(flw[x],z);
				pre[y]=x;lste[y]=e;
				if(!inq[y]){inq[y]=1;q.push(y);}
			}
		}
	} return dist[T]<INF;
}
pair<int,double> mcmf(){
	int mxfl=0;double mncst=0;
	while(getdis()){
		mxfl+=flw[T];mncst+=flw[T]*dist[T];
		for(int i=T;i!=S;i=pre[i]){
			cap[lste[i]]-=flw[T];cap[lste[i]^1]+=flw[T];
		}
	} return mp(mxfl,mncst);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(y[i]<y[j]){
		adde(j+n,i,1,dis(x[i],y[i],x[j],y[j]));
	}
	for(int i=1;i<=n;i++) adde(S,i+n,2,0);
	for(int i=1;i<=n;i++) adde(i,T,1,0);
	pair<int,double> ans=mcmf();
	if(ans.fi!=n-1) puts("-1");
	else printf("%.10lf\n",ans.se);
	return 0;
}
```

---

## 作者：infinities (赞：1)

费用流。
 
因为有两种参数，一种是儿子/父亲个数(整数)，一种是距离(实数)，两种信息不能扯到一起跑，所以要跑费用流。

自己刚开始想用一种非常奇葩的方法构造，yy了半天发现有个无法解决的问题，于是又回到正常思路。

用一般的套路，超级源点和汇点和其他点的连边要么是表示两种相对应的不同信息，要么是为了使每个起始点都有无穷大的流量，每个结束点的流量都能流到一个点里统计。

这里显然是前者。

把每个点拆成 $u_i,v_i$ 两个点，$v_i$ 用来表示和儿子有关的信息，$u_i$ 用来表示和父亲有关的信息。

然后从每个 $v_i$ 连一条流量为2，费用为0的边到源点，因为二叉树每个点最多只能有2个儿子，还没有儿子的时候没有距离，从每个 $u_i$ 连一条流量为1，费用为0的边到汇点，原因同上。

接着对于每组 $y_i > y_j$ 的点 $i,j$，从 $v_i$ 到 $u_j$ 连一条流量为1，费用为距离的边，因为这时 $i$ 可以当 $j$ 的父亲。

然后跑一遍最小费用最大流板子即可。

注意输出时的精度，这里我保留了8位小数。

最后特判无解，其实不难。考虑到树上除了根节点一共有 $n - 1$ 个节点有父亲，我们只需在建边的时候记录一下每个 $u_i$ 到汇点的边的编号，最后枚举一下，看这些边有没有被流掉 $n-1$ 条即可。

code:
```cpp
#include<bits/stdc++.h>
#define op long long
#define rint register int
const int maxn = 3e5 + 100;
const int INF = 2e9;
int read(){
    int x = 0,f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

using std::ios;
using std::cin;
using std::cout;
using std::max;
using std::min;
using std::sort;
using std::unique;
using std::lower_bound;
using std::swap;
using std::abs;
using std::acos;
using std::queue;
using std::map;
using std::string;
double mon[maxn], cost[maxn], mincost;
queue<int>q;
int check[maxn];
int n, m, s, t, to[maxn], nxt[maxn], fr[maxn], l[maxn], cnt = 1, flow[maxn], maxflow, vis[maxn], pre[maxn], liu[maxn];
void add(int u, int v, int ll, double monn){
	++cnt, to[cnt] = v, l[cnt] = ll, mon[cnt] = monn, nxt[cnt] = fr[u], fr[u] = cnt;
	++cnt, to[cnt] = u, l[cnt] = 0, mon[cnt] = -monn, nxt[cnt] = fr[v], fr[v] = cnt;
}
bool SPFA(){
	for(int i = 1; i < maxn - 10; i++)cost[i] = 123456789.99;
	memset(flow, 0x3f, sizeof(flow));
	memset(vis, 0, sizeof(vis));
	vis[s] = 1, pre[t] = -13, cost[s] = 0; q.push(s);
	while(!q.empty()){
		int now = q.front(); q.pop(); 
		for(int i = fr[now]; i; i = nxt[i]){
			if(l[i] && cost[to[i]] > cost[now] + mon[i]){
				cost[to[i]] = cost[now] + mon[i];
				liu[to[i]] = i;
				flow[to[i]] = min(l[i], flow[now]);
				pre[to[i]] = now;
				if(!vis[to[i]]){
					q.push(to[i]);
					vis[to[i]] = 1;
				}
			}
		}
		vis[now] = 0;
	}
	return !(pre[t] == -13);
}
void MCMA(){
	while(SPFA()){
		int now = t;
		maxflow += flow[t], mincost += (double)flow[t] * cost[t];
		while(now != s){
			l[liu[now]] -= flow[t];
			l[liu[now] ^ 1] += flow[t];
			now = pre[now];
		}
	}
}
double loca(int x1, int x2, int y1, int y2){
	return sqrt((double)(x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
struct node{
	double x, y;
}p[maxn];
bool cmp(node a, node b){
	return a.y > b.y;
}
int cntp, u[maxn], v[maxn], vout[maxn], ans;
signed main(){
	n = read();
	for(int i = 1; i <= n; i++){
		p[i].x = read();
		p[i].y = read(); 
	}
	sort(p + 1, p + 1 + n, cmp);
	s = ++cntp, t = ++cntp;
	for(int i = 1; i <= n; i++){
		u[i] = ++cntp, v[i] = ++cntp;
		add(s, v[i], 2, 0);
		add(u[i], t, 1, 0);
		check[i] = cnt - 1;
    }
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			if(p[i].y != p[j].y){
			    add(v[i], u[j], 1, loca(p[i].x, p[j].x, p[i].y, p[j].y));
			}
		}
	}
	MCMA();
	for(int i = 1; i <= cnt; i++){
		if(l[check[i]] > 0){
			ans++;
		}
	}
	if(ans > 1)cout << "-1";else
	printf("%.8lf", mincost);
}
```

---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF277E)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/08/30/CF277E%20Binary%20Tree%20on%20Plane/)

## 前言

尝试对 `double` 数组数组进行 `memset` 并 debug 一小时。

### 前置芝士

网络流


## 分析

首先，为什么这一题可以用网络流来做呢？

网络流的题目一般都有一个明显的特点：有很多其他方法解决不了的限制。然后我们来看这道题，题目中要求构建一颗二叉树，也就相当于一个节点最多只有两个儿子和一个父亲，然后还有对于 $y$ 坐标的限制，考虑到这些限制不好用其它方法搞，于是考虑网络流建模。

我们考虑任意一个二叉树的节点 $u$，它有着双重身份——父亲和儿子，于是我们把一个点 $u$ 拆成 $u_1$ 和 $u_2$ 两个点，$u_1$ 代表父亲，$u_2$ 代表儿子，然后我们套路地将源点 $s$ 向 $u_1$ 连一条容量为 $2$，费用为 $0$ 的边，代表一个点最多只能有两个儿子，$u_2$ 向汇点 $t$ 连一条容量为 $1$，费用为 $0$ 的边，代表一个点有一个父亲。

然后我们考虑两个点 $u$ 和 $v$，如果 $u$ 可以当 $v$ 的父亲，我们就从 $u_1$ 向 $v_2$ 连一条容量为 $1$，费用为两点距离的边，代表连边的费用为两点间距离，然后我们跑最小费用最大流即可 AC 本题。

## 代码

```c++
#include <bits/stdc++.h>
#define pii pair<int, int>

using namespace std;
const int N = 1e6 + 10, INF = 1 << 30;
int h[N], e[N], ne[N], f[N], idx;
int s, t;
double w[N];
pii pos[N];
double d[N];
int minf[N], pre[N];
bool vis[N];
int flow;
double res;

inline int read()
{
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline void add(int a, int b, int c, double d)
{
    e[idx] = b;
    f[idx] = c;
    w[idx] = d;
    ne[idx] = h[a];
    h[a] = idx++;
}

inline double dist(int x1, int y1, int x2, int y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

inline bool spfa()
{
    for (int i = s; i <= t; i++) d[i] = INF;
    memset(vis, 0, sizeof vis);
    queue<int> q;
    q.push(s);
    d[s] = 0;
    minf[s] = INF;
    while (q.size())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = h[u]; ~i; i = ne[i])
        {
            int v = e[i];
            if (d[v] > d[u] + w[i] && f[i])
            {
                d[v] = d[u] + w[i];
                minf[v] = min(minf[u], f[i]);
                pre[v] = i;
                if (!vis[v])
                    q.push(v), vis[v] = true;
            }
        }
    }
    return d[t] < INF;
}

inline void EK()
{
    while (spfa())
    {
        flow += minf[t], res += d[t] * minf[t];
        for (int i = t; i != s; i = e[pre[i] ^ 1])
            f[pre[i]] -= minf[t], f[pre[i] ^ 1] += minf[t];
    }
}

int main()
{
    memset(h, -1, sizeof h);
    int n = read();
    for (int i = 1; i <= n; i++) pos[i].first = read(), pos[i].second = read();
    s = 0, t = 2 * n + 1;
    for (int i = 1; i <= n; i++)
        add(s, i, 2, 0), add(i, s, 0, 0);
    for (int i = 1; i <= n; i++)
        add(i + n, t, 1, 0), add(t, i + n, 0, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (i == j || pos[i].second <= pos[j].second) continue;
            double d = dist(pos[i].first, pos[i].second, pos[j].first, pos[j].second);
            add(i, j + n, 1, d);
            add(j + n, i, 0, -d);
        }
    EK();
    if (flow < n - 1) puts("-1");
    else printf("%.10lf\n", res);
    return 0;
}
```



---

## 作者：intel_core (赞：0)

考虑怎么解决二叉树的限制。

它等价于每个顶点只能连向两个 $y$ 坐标小的节点。

转化为二分图模型，一种 $n-1$ 条边的匹配方案中每一条边 $(x,y)$ ，$x$ 为 $y$ 在树上的儿子。

给左侧每个点限制流量为 $1$ ，右侧每个点限制流量为 $2$，总流量不超过 $n-1$。

对于两个节点 $x,y$，直接连一条费用是距离的边就行。

最后一次费用流解决问题，最劣复杂度 $O(n^3 \sqrt{n})$，应该足够了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e3+10;
const int MR=1e6+10;
#define db double
const db eps=1e-9;
int n,maxy,pos,x[NR],y[NR];
struct edge{
	int to,next,flow;db v;
}g[MR];
int tot=1,fte[NR];
void add(int x,int y,int z,db v){
//	printf("%d %d %d %.6lf\n",x,y,z,v);
	g[++tot]=(edge){y,fte[x],z,v};fte[x]=tot;
	g[++tot]=(edge){x,fte[y],0,-v};fte[y]=tot;
}

int s,t,p1,p2,vis[NR];
queue<int>q;
db dis[NR],ans;
bool SPFA(){
	for(int i=1;i<=t;i++)dis[i]=1e9;
	q.push(s);dis[s]=0;vis[s]=1;
	while(!q.empty()){
		int x=q.front();
		q.pop();vis[x]=0;
//		cout<<x<<" "<<dis[x]<<endl;
		for(int i=fte[x];i;i=g[i].next)
			if(g[i].flow&&dis[g[i].to]>dis[x]+g[i].v+eps){
				dis[g[i].to]=dis[x]+g[i].v;
//				printf("x:%d y:%d v:%.6lf\n",x,g[i].to,g[i].v);
				if(!vis[g[i].to])q.push(g[i].to),vis[g[i].to]=1;
			}
	}
	return dis[t]<1e9;
}
int dfs(int id,int Lim){
	if(id==t)return Lim;
	vis[id]=1;
	int flow=0,f;
	for(int i=fte[id];i;i=g[i].next)
		if(!vis[g[i].to]&&g[i].flow&&abs(dis[g[i].to]-dis[id]-g[i].v)<eps){
			f=dfs(g[i].to,min(g[i].flow,Lim-flow));
			if(!f){
				dis[g[i].to]=1e9;
				continue;
			}
			flow+=f;g[i].flow-=f;g[i^1].flow+=f;
			ans+=f*g[i].v;
			if(flow==Lim)break;
		}
	vis[id]=0;
	return flow;
}
db Dinic(){
	int Flow,MaxFlow=0;
	while(SPFA())
		while(Flow=dfs(s,1e9))MaxFlow+=Flow;
	if(MaxFlow<n-1)puts("-1"),exit(0);
	return ans;
}

int sq(int x){return x*x;}
int main(){
	cin>>n;s=n*2+3;t=s+1;
	p1=n*2+1;p2=p1+1;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i],maxy=max(maxy,y[i]);
	for(int i=1;i<=n;i++)
		if(maxy==y[i]){
			if(pos)puts("-1"),exit(0);
			else pos=i;
		}
	add(s,p1,n-1,0);add(p2,t,n-1,0);
	for(int i=1;i<=n;i++)add(i+n,p2,2,0);
	for(int i=1;i<=n;i++)add(p1,i,1,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(y[j]>y[i])add(i,j+n,1,sqrt(sq(x[i]-x[j])+sq(y[i]-y[j])));
	printf("%.6lf\n",Dinic());
	return 0;
}
```

---

