# [ARC090E] Avoiding Collision

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc090/tasks/arc090_c

$ N $ 頂点 $ M $ 辺からなるグラフがあり、このグラフの上に高橋くんと青木くんがいます。

グラフの $ i $ 番目の辺は頂点 $ U_i $ と頂点 $ V_i $ を結んでいます。 この辺を通るのにかかる時間は、通る人 (高橋くんまたは青木くん) によらず、また通る方向によらず、$ D_i $ 分です。

高橋くんは頂点 $ S $ を、青木くんは頂点 $ T $ を同時に出発し、それぞれ頂点 $ T $ および頂点 $ S $ へ最短の時間で移動します。 二人の最短路の選び方の組であって、移動の途中で二人が (辺または頂点上で) 出会うことのないようなものの個数を $ 10^9\ +\ 7 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100,000 $
- $ 1\ \leq\ M\ \leq\ 200,000 $
- $ 1\ \leq\ S,\ T\ \leq\ N $
- $ S\ \neq\ T $
- $ 1\ \leq\ U_i,\ V_i\ \leq\ N $ ($ 1\ \leq\ i\ \leq\ M $)
- $ 1\ \leq\ D_i\ \leq\ 10^9 $ ($ 1\ \leq\ i\ \leq\ M $)
- $ i\ \neq\ j $ のとき、$ (U_i,\ V_i)\ \neq\ (U_j,\ V_j) $ かつ $ (U_i,\ V_i)\ \neq\ (V_j,\ U_j) $
- $ U_i\ \neq\ V_i $ ($ 1\ \leq\ i\ \leq\ M $)
- $ D_i $ は整数である
- 与えられるグラフは連結である

### Sample Explanation 1

条件を満たす最短路の選び方は以下の 2 通りあります。 - 高橋くんが頂点 $ 1\ \rightarrow\ 2\ \rightarrow\ 3 $ という経路で、青木くんが頂点 $ 3\ \rightarrow\ 4\ \rightarrow\ 1 $ という経路で移動する。 - 高橋くんが頂点 $ 1\ \rightarrow\ 4\ \rightarrow\ 3 $ という経路で、青木くんが頂点 $ 3\ \rightarrow\ 2\ \rightarrow\ 1 $ という経路で移動する。

## 样例 #1

### 输入

```
4 4
1 3
1 2 1
2 3 1
3 4 1
4 1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3
1 3
1 2 1
2 3 1
3 1 2```

### 输出

```
2```

## 样例 #3

### 输入

```
3 3
1 3
1 2 1
2 3 1
3 1 2```

### 输出

```
2```

## 样例 #4

### 输入

```
8 13
4 2
7 3 9
6 2 3
1 6 4
7 6 9
3 8 9
1 2 2
2 8 12
8 6 9
2 5 5
4 2 18
5 3 7
5 1 515371567
4 8 6```

### 输出

```
6```

# 题解

## 作者：小粉兔 (赞：14)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/10022225.html](https://www.cnblogs.com/PinkRabbit/p/10022225.html)。

### 题意简述：

给定一张有 $N$ 个点 $M$ 条边的无向图。每条边有相应的边权，边权是正整数。

小 A 要从结点 $S$ 走到结点 $T$，而小 B 则相反，他要从结点 $T$ 走到结点 $S$。

小 A 和小 B 走一条边需要的时间都是这条边的边权，不论方向。

问有多少种走法，使得他们俩都走了最短路，但是他们不会相遇，这里相遇指的是在点上或者在边上相遇。

答案对 $10^9+7$ 取模。

### 题解：

用 Dijkstra 算法求出以结点 $S$ 和结点 $T$ 出发到每个点的最短路和最短路条数。

把从结点 $S$ 到结点 $i$ 的最短路记作 $d1_i$，最短路条数对 $10^9+7$ 取模的结果记作 $g1_i$。

把从结点 $T$ 到结点 $i$ 的最短路记作 $d2_i$，最短路条数对 $10^9+7$ 取模的结果记作 $g2_i$。

把从结点 $S$ 到结点 $T$ 的最短路记作 $Dist$。

考虑用容斥的方法计算答案。答案等于总方案数减去相遇的方案数。总方案数为 $g1_T^2$。

因为走的都是最短路，而且边权是正的，不难证明两人只会相遇一次。

所以只要统计在每个点或者每条边经过的方案数即可。

考虑经过结点 $i$ 的方案数：  
前提是 $d1_i+d2_i=Dist$ 且 $d1_i=d2_i$，方案数为 $g1_i^2g2_i^2$。

考虑经过边 $i\overset{d}{\Longleftrightarrow}j$（其中小 A 从结点 $i$ 走向结点 $j$）的方案数：  
前提是 $d1_i+d+d2_j=Dist$ 且 $d1_i+d>d2_j$ 且 $d1_i<d+d2_j$，方案数为 $g1_i^2g2_j^2$。

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define eF(i,u) for(int i=h[u];i;i=nxt[i])
#define Mod 1000000007
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;

int n,m,S,T;
ll Ans;
int U[200001],V[200001],D[200001];
int h[100001],nxt[400001],to[400001],w[400001],tot;
void ins(int x,int y,int z){nxt[++tot]=h[x];to[tot]=y;w[tot]=z;h[x]=tot;}

ll d1[100001],d2[100001],g1[100001],g2[100001];bool v1[100001],v2[100001];
priority_queue<pli,vector<pli>,greater<pli> > pq;

void Dij(ll*d,ll*g,bool*v,int s){
	d[s]=0ll;
	pq.push(pli(0ll,s));
	g[s]=1;
	while(!pq.empty()){
		pli P=pq.top(); pq.pop();
		int u=P.second; ll du=P.first;
		if(v[u]||d[u]<du) continue;
		v[u]=1;
		eF(i,u){
			if(d[to[i]]==du+w[i])
				g[to[i]]=(g[to[i]]+g[u])%Mod;
			if(d[to[i]]>du+w[i])
				g[to[i]]=g[u],
				d[to[i]]=du+w[i], pq.push(pli(d[to[i]],to[i]));
		}
	}
}

int main(){
	int x,y,z;
	scanf("%d%d",&n,&m);
	scanf("%d%d",&S,&T);
	F(i,1,m) scanf("%d%d%d",&x,&y,&z), ins(x,y,z), ins(y,x,z), U[i]=x, V[i]=y, D[i]=z;
	memset(d1,0x3f,sizeof d1);
	Dij(d1,g1,v1,S);
	memset(d2,0x3f,sizeof d2);
	Dij(d2,g2,v2,T);
	ll Dist=d1[T];
	Ans=g1[T]*g1[T]%Mod;
	F(i,1,n){
		if(d1[i]+d2[i]==Dist&&d1[i]==d2[i])
			Ans=(Ans-g1[i]*g1[i]%Mod*g2[i]%Mod*g2[i]%Mod)%Mod;
	}
	int u,v,d;
	F(i,1,m){
		u=U[i], v=V[i], d=D[i];
		if(d1[u]+d+d2[v]==Dist && d1[u]+d>d2[v] && d2[v]+d>d1[u]){
			Ans=(Ans-g1[u]*g2[v]%Mod*g1[u]%Mod*g2[v]%Mod)%Mod;
		}
		u=V[i], v=U[i], d=D[i];
		if(d1[u]+d+d2[v]==Dist && d1[u]+d>d2[v] && d2[v]+d>d1[u]){
			Ans=(Ans-g1[u]*g2[v]%Mod*g1[u]%Mod*g2[v]%Mod)%Mod;
		}
	}
	printf("%lld",(Ans%Mod+Mod)%Mod);
	return 0;
}
```

---

## 作者：NaVi_Awson (赞：5)

## Description

[题库链接](https://arc090.contest.atcoder.jp/tasks/arc090_c)

给出一张 $N$ 个节点， $M$ 条边的无向图，给出起点 $S$ 和终点 $T$ 。询问两个人分别从 $S$ 和 $T$ 出发，走最短路不相遇的方案数。

$1 \leq N \leq 100,000,1 \leq M \leq 200,000$

## Solution

记最短路长度为 $D$ ，从 $S$ 出发走过的路程为 $d_1$ ，从 $T$ 出发的走过的路程为 $d_2$ 。值得注意的是走最短路相遇只会出现两种情况：

1. 在某个节点相遇，此时 $d_1=d_2=\frac{D}{2}$ ；
2. 在某条边上相遇，记这条边为 $e$ ，边权为 $c$ ，连接 $u,v$ 两个节点。此时 ${d_1}_u+{d_2}_v+c=D$ ，且 ${d_1}_u < \left\lfloor\frac{D}{2}\right\rfloor,{d_2}_v < \left\lfloor\frac{D}{2}\right\rfloor$ 

那么我们跑一遍最短路计数，用总方案数减去上述不合法的情况即可。

## Code

```cpp
//It is made by Awson on 2018.2.2
#include <bits/stdc++.h>
#define LL long long
#define dob complex<double>
#define Abs(a) ((a) < 0 ? (-(a)) : (a))
#define Max(a, b) ((a) > (b) ? (a) : (b))
#define Min(a, b) ((a) < (b) ? (a) : (b))
#define Swap(a, b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))
#define writeln(x) (write(x), putchar('\n'))
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int N = 100000;
const int yzd = 1e9+7;
void read(int &x) {
    char ch; bool flag = 0;
    for (ch = getchar(); !isdigit(ch) && ((flag |= (ch == '-')) || 1); ch = getchar());
    for (x = 0; isdigit(ch); x = (x<<1)+(x<<3)+ch-48, ch = getchar());
    x *= 1-2*flag;
}
void print(int x) {if (x > 9) print(x/10); putchar(x%10+48); }
void write(int x) {if (x < 0) putchar('-'); print(Abs(x)); }

int n, m, s, t, u, v, c;
struct tt {int to, next, cost; }edge[(N<<2)+5];
int path[N+5], top;
int ans1[N+5], ans2[N+5], vis[N+5], in[N+5];
LL dist1[N+5], dist2[N+5];
queue<int>Q;
vector<int>to[N+5];

void add(int u, int v, int c) {
    edge[++top].to = v, edge[top].cost = c, edge[top].next = path[u], path[u] = top;
}
void SPFA(int s, LL *dist) {
    dist[s] = 0; Q.push(s); vis[s] = 1;
    while (!Q.empty()) {
	int u = Q.front(); Q.pop(); vis[u] = 0;
	for (int i = path[u]; i; i = edge[i].next)
	    if (dist[edge[i].to] > dist[u]+edge[i].cost) {
		dist[edge[i].to] = dist[u]+edge[i].cost;
		if (!vis[edge[i].to]) {
		    vis[edge[i].to] = 1; Q.push(edge[i].to);
		}
	    }
    }
}
void topsort(int s, LL *dist, int *ans) {
    for (int u = 1; u <= n; u++) {
	to[u].clear();
	for (int i = path[u]; i; i = edge[i].next)
	    if (dist[edge[i].to] == dist[u]+edge[i].cost) to[u].push_back(edge[i].to), ++in[edge[i].to];
    }
    ans[s] = 1; Q.push(s);
    while (!Q.empty()) {
	int u = Q.front(), size = to[u].size(); Q.pop();
	for (int i = 0; i < size; i++) {
	    if (--in[to[u][i]] == 0) Q.push(to[u][i]); (ans[to[u][i]] += ans[u]) %= yzd;
	}
    }
}
void work() {
    read(n), read(m), read(s), read(t);
    for (int i = 1; i <= m; i++) {
	read(u), read(v), read(c); add(u, v, c); add(v, u, c);
    }
    memset(dist1, 127/3, sizeof(dist1));
    SPFA(s, dist1); topsort(s, dist1, ans1);
    memset(dist2, 127/3, sizeof(dist2));
    SPFA(t, dist2); topsort(t, dist2, ans2);
    int ans = 1ll*ans1[t]*ans1[t]%yzd;
    for (int u = 1; u <= n; u++) {
	if (dist1[u] == dist2[u] && dist2[u]*2 == dist1[t]) (ans -= 1ll*ans1[u]*ans1[u]%yzd*ans2[u]%yzd*ans2[u]%yzd) %= yzd;
	for (int i = path[u]; i; i = edge[i].next)
	    if (dist1[u]+edge[i].cost+dist2[edge[i].to] == dist1[t] && dist1[u]*2 < dist1[t] && dist2[edge[i].to]*2 < dist1[t])
		(ans -= 1ll*ans1[u]*ans1[u]%yzd*ans2[edge[i].to]%yzd*ans2[edge[i].to]%yzd) %= yzd;
    }
    writeln((ans+yzd)%yzd);
}
int main() {
    work();
    return 0;
}
```

---

## 作者：DengDuck (赞：3)

我们先对与 $S,T$ 两个点各跑一次最短路，求出 $dis_{0,x}$，$g_0,x$ 表示 $S\to x$ 的最短路径长度与方案数，$dis_{1,x}$ 和 $g_{1,x}$ 同理。

发现不相遇的方案比较难求，所以考虑容斥，求相遇的方案数，再用总方案数 $g_{0,T}^2$ 减一下。

考虑相遇位置。

- 如果在点 $x$，那么显然条件为 $dis_{0,x}+dis_{1,x}=dis_{0,T},dis_{0,x}=dis_{1,x}$，方案数为 $(g_{0,x}g_{1,x})^2$。
- 如果在边 $(x,y)$，边权为 $w$，那么显然条件为 $dis_{0,x}+dis_{1,y}+w=dis_{0,T},dis_{0,x}+w>dis_{1,y},dis_{1,y}+w>dis_{0,x}$，方案数为 $(g_{0,x}g_{1,y})^2$。

然后这题就做完了，时间复杂度为 $\mathcal O((n+m)\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pLL pair<LL,LL>
#define num first
#define pt second
using namespace std;
const LL N=1e5+5;
const LL mod=1e9+7;
struct node
{
	LL to,w;
};
LL n,m,s,t,x,y,z,dis[2][N],g[2][N],vis[N],ans;
vector<node>v[N];
priority_queue<pLL,vector<pLL>,greater<pLL> >p;
void work(LL s,LL *dis,LL *g)
{
	memset(vis,0,sizeof(vis));
	dis[s]=0;
	g[s]=1;
	p.push({0,s});
	while(!p.empty())
	{
		LL t=p.top().pt;
		p.pop();  
		if(vis[t])continue;
		vis[t]=1;
		for(auto i:v[t])
		{
			if(dis[t]+i.w<dis[i.to])
			{
				dis[i.to]=dis[t]+i.w;
				p.push({dis[i.to],i.to});
				g[i.to]=0;
			}
			if(dis[t]+i.w==dis[i.to])g[i.to]=(g[i.to]+g[t])%mod;
		}
	}
}
int main()
{
	memset(dis,27,sizeof(dis));
	scanf("%lld%lld%lld%lld",&n,&m,&s,&t);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld",&x,&y,&z);
		v[x].push_back({y,z});
		v[y].push_back({x,z});
	}
	work(s,dis[0],g[0]),work(t,dis[1],g[1]);
	ans=g[0][t]*g[0][t]%mod;
	for(int i=1;i<=n;i++)
	{
		if(dis[0][i]+dis[1][i]==dis[0][t]&&dis[0][i]==dis[1][i])ans=(ans-g[0][i]*g[0][i]%mod*g[1][i]%mod*g[1][i]%mod+mod)%mod;
	}
	for(int i=1;i<=n;i++)
	{
		for(auto j:v[i])
		{ 
			if(dis[0][i]+dis[1][j.to]+j.w==dis[0][t]&&dis[0][i]+j.w>dis[1][j.to]&&dis[1][j.to]+j.w>dis[0][i])ans=(ans-g[0][i]*g[0][i]%mod*g[1][j.to]%mod*g[1][j.to]%mod+mod)%mod;
		}
	}
	printf("%lld",ans);
}
```

---

## 作者：Larryyu (赞：2)

## _Description_

给定一个 $n$ 个点，$m$ 条边的无向图，两个人分别从 $S$ 走到 $T$、$T$ 走到 $S$。

每条边需要花费一定的时间通过。

两个人走的路径耗时都是最短的，且两人不会相遇（即在同一时刻两人不在同一点或同一边）。

问有多少种方案满足上述要求。

两种方案不同当且仅当有至少一人走的路径不同。

## _Solution_

首先考虑正向得出答案。

我们发现一条边 $(u,v)$ 若能是 $S$ 到 $T$ 的最短路的一部分，那么 $dis(S,u)$ 和 $dis(v,T)$ 一定确定，即使是在两条不一样的最短路上。

那么为了不相遇，两人走的路径包含的边集一定不交。

然后就会顺畅的想到每条边松弛后只更新一条边，保证最后得出的每一条最短路的边集的交集为空。

然而稍微细想就会发现这是无法保证的，同时也不是正确答案。

因为：

1. 无法保证松弛后更新的唯一边在最短路中。
2. 可能 $a,b$ 两条最短路径有交但 $(a,c),(c,a),(b,c),(c,b)$ 是合法方案。
3. 两条最短路径可能只在一个点相交，而不是边。

说了那么多，就是为了~~让你死了正向推这条心（也有可能作者太菜想不出来）~~ 发现容斥是可行的。
### _Realsol_
发现两个人最多只会相遇一次（注意两条最短路径可能有多个部分重叠）。

分类讨论相遇是在点或边。

设 $Mdis$ 为最短路，$diss_{0,x},cntt_{0,x},diss_{1,x},cntt_{1,x}$ 分别为 $S$ 到 $x$ 的最短耗时、最短路个数，$T$ 到 $x$ 的最短耗时、最短路个数，$dis(x,y)$ 代表无向边 $(x,y)$ 的耗时。

若相遇在点 $x$，则满足 $diss_{0,x}=diss_{1,x}$，同时满足 $diss_{0,x}+diss_{1,x}=Mdis$ 的最短耗时要求，此方案个数为 $(cntt_{0,x}\times cntt_{1,x})^2$。

若相遇在边 $(x,y)$，则满足 $diss_{0,x}+dis(x,y)>diss_{1,y},diss_{1,y}+dis(x,y)>diss_{0,x}$，同时满足 $diss_{0,x}+dis(x,y)+diss_{1,y}=Mdis$ 的最短耗时要求，此方案个数为 $(cntt_{0,x}\times cntt_{1,y})^2$。

注意此为 $S\rightarrow x\rightarrow y\rightarrow T$ 的情况，由于 $(x,y)$  是无向边，所以还要考虑 $S\rightarrow y\rightarrow x\rightarrow T$ 的情况。

最后用总方案数 $cntt_{0,T}\times cntt_{1,S}$ 减去上面不满足要求的方案即可得出正确答案。

## _Code_

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mo=1000000007;
priority_queue<pair<ll,int> >q; 
int n,m,s,t;
int tot,head[100010];
int u[200020],v[200020];
ll diss[2][100010],dis[100010],d[200020];
ll cntt[2][100010],cnt[100010];
bool vis[100010];
struct edge{
	int to,next;
	ll w;
}e[400040];
void add(int x,int y,ll z){
	e[++tot]=edge{y,head[x],z};
	head[x]=tot;
}
void dijsktra(ll *dis,ll *cnt,int st){
	for(int i=1;i<=n;i++){
		dis[i]=1e15;
		vis[i]=0;
	}
	dis[st]=0,cnt[st]=1;
	q.push({0,st});
	while(q.size()){
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].to;
			ll w=e[i].w;
			if(dis[y]<dis[x]+w) continue;
			else if(dis[y]==dis[x]+w){
				cnt[y]+=cnt[x];
				cnt[y]%=mo;
				continue;
			}
			cnt[y]=cnt[x];
			dis[y]=dis[x]+w;
			if(vis[y]) continue;
			q.push({-dis[y],y});
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++){
		int x,y;
		ll z;
		cin>>x>>y>>z;
		add(x,y,z),add(y,x,z);
		u[i]=x,v[i]=y,d[i]=z;
	}
	dijsktra(diss[0],cntt[0],s);
	dijsktra(diss[1],cntt[1],t);
	ll ans=cntt[0][t]*cntt[0][t]%mo;
	for(int i=1;i<=n;i++){
		if(diss[0][i]==diss[1][i]&&diss[0][i]+diss[1][i]==diss[0][t]){
			ans=(ans+mo-cntt[0][i]*cntt[1][i]%mo*cntt[0][i]%mo*cntt[1][i]%mo)%mo;
		}
	}
	for(int i=1;i<=m;i++){
		if(diss[0][u[i]]+d[i]>diss[1][v[i]]&&diss[1][v[i]]+d[i]>diss[0][u[i]]&&diss[0][u[i]]+d[i]+diss[1][v[i]]==diss[0][t]){
			ans=(ans+mo-cntt[0][u[i]]*cntt[1][v[i]]%mo*cntt[0][u[i]]%mo*cntt[1][v[i]]%mo)%mo;
		}
		swap(u[i],v[i]);
		if(diss[0][u[i]]+d[i]>diss[1][v[i]]&&diss[1][v[i]]+d[i]>diss[0][u[i]]&&diss[0][u[i]]+d[i]+diss[1][v[i]]==diss[0][t]){
			ans=(ans+mo-cntt[0][u[i]]*cntt[1][v[i]]%mo*cntt[0][u[i]]%mo*cntt[1][v[i]]%mo)%mo;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：iamajcer (赞：2)

# 思路

直接求不相遇比较难，用减法原理。

很容易想到，首先要搞一个最短路计数。

$dis_{i}$ 表示 $s$ 到 $i$ 的最短路，$cnt_{i}$ 表示 $s$ 到 $i$ 的最短路路径数。

$dis2_{i}$ 表示 $t$ 到 $i$ 的最短路，$cnt2_{i}$ 表示 $t$ 到 $i$ 的最短路路径数。

$sum$ 表示整个图的最短路。

用全部方案 - 相遇方案，就是答案。

全部方案就是最短路径条数平方，也就是 $cnt_{t} \times cnt_{t}$，当然 $cnt2[s] \times cnt2[s]$ 也行。

相遇是在节点上相遇或者边上相遇，分类讨论。

- 在 $u$ 节点相遇：

条件：$dis_{u} = dis2_{u}$，且 $dis_{u} + dis2_{u} = sum$。

贡献：$(cnt_{u} \times cnt2_{u})^2$。

- 在 $u$ 到 $v$ 这条边上相遇：

条件：

$dis_{u}+w+dis2_{v} = sum$。

$dis_{u}+w>dis2_{v}$。

$dis_{v}+w>dis2_{u}$。

贡献：$(cnt_{u} \times cnt2_{v})^2$。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=200005, Mod=1e9+7;
 
struct node
{
    int v, w;
    bool operator <(const node &A) const
    {
        return w>A.w;
    };
};
struct node2
{
    int u, v, w;
}ask[N];
int n, m, s, t, u1, v1, w1;
int dis[N], vis[N], cnt[N], dis2[N], vis2[N], cnt2[N], ans=0, sum=0;
vector<node> a[N];
priority_queue<node> q, q2;
void dij()
{
    memset(dis, 63, sizeof dis);
    memset(vis, 0, sizeof vis);
    dis[s]=0, cnt[s]=1;
    q.push({s, 0});
     
    while (!q.empty())
    {
        int u=q.top().v;
        q.pop();
          
        if (vis[u]) continue;
        vis[u]=1;
         
        for (int i=0; i<a[u].size(); i++)
        {
            int v=a[u][i].v, w=a[u][i].w;
            if (dis[v]>dis[u]+w)
            {
                dis[v]=dis[u]+w;
                q.push({v, dis[v]});
                 
                cnt[v]=cnt[u]%Mod;
            }
            else if (dis[v]==dis[u]+w) cnt[v]=(cnt[v]+cnt[u])%Mod;
        }
    }
}
void dij2()
{
    memset(dis2, 63, sizeof dis2);
    memset(vis2, 0, sizeof vis2);
    dis2[t]=0, cnt2[t]=1;
    q2.push({t, 0});
      
    while (!q2.empty())
    {
        int u=q2.top().v;
        q2.pop();
          
        if (vis2[u]) continue;
        vis2[u]=1;
         
        for (int i=0; i<a[u].size(); i++)
        {
            int v=a[u][i].v, w=a[u][i].w;
            if (dis2[v]>dis2[u]+w)
            {
                dis2[v]=dis2[u]+w;
                q2.push({v, dis2[v]});
                cnt2[v]=cnt2[u]%Mod;
            }
            else if (dis2[v]==dis2[u]+w) cnt2[v]=(cnt2[v]+cnt2[u])%Mod;
        }
    }
}
signed main()
{
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i=1; i<=m; i++)
    {
        scanf("%d%d%lld", &u1, &v1, &w1);
        a[u1].push_back({v1, w1});
        a[v1].push_back({u1, w1});
        ask[i]={u1, v1, w1};
    }
    dij();
    dij2();
     
    sum=dis[t];
    ans=cnt[t]*cnt[t];
     
    for (int i=1; i<=n; i++)
        if (dis[i]==dis2[i] && dis[i]+dis2[i]==sum) ans=((ans-(cnt[i]*cnt[i]%Mod*cnt2[i]%Mod*cnt2[i]%Mod))+Mod)%Mod;
    //printf("%lld\n", ans%Mod);
     
    for (int i=1; i<=m; i++)
    {
        int u=ask[i].u, v=ask[i].v, w=ask[i].w;
        if (dis[u]+w+dis2[v]==sum && dis[u]+w>dis2[v] && dis2[v]+w>dis[u]) ans=((ans-cnt[u]*cnt[u]%Mod*cnt2[v]%Mod*cnt2[v]%Mod)+Mod)%Mod;
        swap(u, v);
        if (dis[u]+w+dis2[v]==sum && dis[u]+w>dis2[v] && dis2[v]+w>dis[u]) ans=((ans-cnt[u]*cnt[u]%Mod*cnt2[v]%Mod*cnt2[v]%Mod)+Mod)%Mod;
    }
     
    printf("%lld", ans%Mod);
    return 0;
}
```

---

## 作者：Antiluna (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc090_c)

### 题意

比较好懂，注意经过的路径必须是最短的。所谓“边相遇”指的就是同一时刻以相对的方向到达两个相邻的点。

### 思路

如果不考虑相遇，就是一个最短路计数问题，答案就是 $cnt_{S,T}\times cnt_{T,S}$（虽然这两者相等）。

最短路计数的转移如下：

必须松弛时，$cnt_v=cnt_u$。

可以松弛但不必须时，$cnt_v=cnt_v+cnt_u$。

现在考虑相遇，根据容斥原理，答案即为所有方案减去点相遇方案和边相遇方案。于是我们分类讨论：

点相遇：显然如果到该点最短距离相等，就一定会在该点相遇。此时方案数为 $cnt_{S,u}^2\times cnt_{T,u}^2$。

边相遇：由于我们不知道边的两个点分别对应 $S$ 还是 $T$，所以两种情况都要考虑，对于其中一种，需要满足两个条件才能边相遇：

$dis_{S,u}+f_{u,v}>dis_{T,v}$

$dis_{T,v}+f_{u,v}>dis_{S,u}$

什么意思呢？意思就是一个人走过这条边之前，另一个人必须至少走上这条边。

无论是点相遇还是边相遇，都必须是在最短路上，所以还要判断最短路：

点：$dis_{S,u}+dis_{u,T}=dis{S,T}$

边：$dis_{S,u}+f_{u,v}+dis_{v,T}=dis_{S,T}$

注意减法取模要加上模数避免溢出，虽然本题貌似不存在这种情况。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,S,T,x[2*200010],y[2*200010],z[2*200010],first[2*100010],mod=1e9+7,ct;
bool bj1[2*100010],bj2[2*100010];
long long dis1[2*100010],g1[2*100010],dis2[2*100010],g2[2*100010],ans;
typedef pair<long long,int> pii;
struct node
{
	int to,next,w;
}tr[2*200010];
priority_queue<pii,vector<pii>,greater<pii> > q1;
priority_queue<pii,vector<pii>,greater<pii> > q2;
void add(int x,int y,int z)
{
	tr[++ct].to=y;
	tr[ct].w=z;
	tr[ct].next=first[x];
	first[x]=ct;
}
void dij1()
{
	memset(dis1,0x7f7f7f7f,sizeof(dis1));
	dis1[S]=0,g1[S]=1;
	q1.push({0ll,S});
	while(q1.size())
	{
		pii now=q1.top();
		q1.pop();
		int u=now.second;
		long long val=now.first;
		if(bj1[u]||dis1[u]<val)continue;
		bj1[u]=1;
		for(int i=first[u];i;i=tr[i].next)
		{
			int v=tr[i].to;
			if(dis1[v]>val+tr[i].w)dis1[v]=val+tr[i].w,g1[v]=g1[u],q1.push({dis1[v],v});
			else if(dis1[v]==val+tr[i].w)g1[v]=(g1[v]+g1[u])%mod;
		}
	}
}
void dij2()
{
	memset(dis2,0x7f7f7f7f,sizeof(dis2));
	dis2[T]=0,g2[T]=1;
	q2.push({0ll,T});
	while(q2.size())
	{
		pii now=q2.top();
		q2.pop();
		int u=now.second;
		long long val=now.first;
		if(bj2[u]||dis2[u]<val)continue;
		bj2[u]=1;
		for(int i=first[u];i;i=tr[i].next)
		{
			int v=tr[i].to;
			if(dis2[v]>val+tr[i].w)dis2[v]=val+tr[i].w,g2[v]=g2[u],q2.push({dis2[v],v});
			else if(dis2[v]==val+tr[i].w)g2[v]=(g2[v]+g2[u])%mod;
		}
	}
}
signed main()
{
	scanf("%d %d",bitand n,bitand m);
	scanf("%d %d",bitand S,bitand T);
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d %d",bitand x[i],bitand y[i],bitand z[i]);
		add(x[i],y[i],z[i]),add(y[i],x[i],z[i]);
	}
	dij1(),dij2();
//	for(int i=1;i<=n;i++)cout<<dis1[i]<<" "<<dis2[i]<<endl;
	ans=g1[T]*g1[T]%mod;
	for(int i=1;i<=n;i++)if(dis1[i]+dis2[i]==dis2[S]&&dis1[i]==dis2[i])ans=(ans-(g1[i]*g1[i]%mod*g2[i]%mod*g2[i]%mod)+mod)%mod;
	for(int i=1;i<=m;i++)
	{
		int u=x[i],v=y[i],w=z[i];
		if(dis1[u]+w+dis2[v]==dis2[S]&&dis1[u]+w>dis2[v]&&dis2[v]+w>dis1[u])ans=(ans-(g1[u]*g1[u]%mod*g2[v]%mod*g2[v]%mod)+mod)%mod;
		if(dis1[v]+w+dis2[u]==dis1[T]&&dis1[v]+w>dis2[u]&&dis2[u]+w>dis1[v])ans=(ans-(g1[v]*g1[v]%mod*g2[u]%mod*g2[u]%mod)+mod)%mod;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：shinkuu (赞：2)

果然自己想出来和看题解做出来是完全不同的感觉……

首先考虑没有不相遇的限制条件怎么做。发现这个问题就是 P1144 再加上乘法原理。

然后思考如何处理相遇的情况。容易想到枚举相遇的点和边。首先从 $s$ 和 $t$ 开始各跑一遍最短路，$dis_{u,0/1},cnt_{u,0/1}$ 分别为点 $u$ 到点 $s/t$ 的距离和此时的最短路数。

然后考虑如何计算经过点 $x$ 的最短路数量。这条最短路一定可以分成以下两段：$s\rightarrow x,x\rightarrow t$。按照乘法原理，数量即为 $cnt_{x,0}\times cnt_{x,1}$。两人同时走过 $x$ 点的情况数即为这个数的平方。

在边上相遇的情况类似，因为要求一定要经过这条边，读者可自行思考或参考代码。

最后考虑什么时候会相遇。容易想到，对于点，当 $dis_{u,0}\times 2=dis_{t,0}$ 时会在该点相遇；对于边，当 $dis_{u,0}\times 2<dis_{t,0}\land dis_{v,1}\times 2<dis_{t,0}$（说明最短路长的一半在这条边上）且 $dis_{u,0}+D_i+dis_{v,1}=dis_{t,0}$（说明该路径为最短路）时会相遇。

将所有情况数减去不合法，即会相遇的方案数即可。

code：

```cpp
int n,m,s,t,cnt[N][2];
ll dis[N][2];
bool vis[N];
int tot,head[N];
struct node{
	int to,nxt,cw;
}e[N<<2];
priority_queue<pair<ll,int>> q;
inline void add(int u,int v,int w){
	e[++tot]={v,head[u],w};
	head[u]=tot;
}
void dij(int S,int op){
	mems(vis,false);
	dis[S][op]=0;
	cnt[S][op]=1;
	q.push(Mp(0,S));
	while(q.size()){
		int u=q.top().se;
		q.pop();
		if(vis[u])
			continue;
		vis[u]=true;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(vis[v]||dis[v][op]<dis[u][op]+e[i].cw)
				continue;
			if(dis[v][op]>dis[u][op]+e[i].cw){
				cnt[v][op]=cnt[u][op];
				dis[v][op]=dis[u][op]+e[i].cw;
				q.push(Mp(-dis[v][op],v));
			}else if(dis[v][op]==dis[u][op]+e[i].cw)
				cnt[v][op]=(cnt[v][op]+cnt[u][op])%mod;
		}
	}
}
void solve(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1,u,v,w;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	mems(dis,0x3f);
	dij(s,0);
	dij(t,1);
	ll d=dis[t][0];
	int ans=1ll*cnt[t][0]*cnt[t][0]%mod;
	for(int u=1;u<=n;u++){
		if(dis[u][0]*2==d)
			ans=(ans-1ll*cnt[u][0]*cnt[u][0]%mod*cnt[u][1]%mod*cnt[u][1]%mod+mod)%mod;
		else{
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(dis[u][0]+e[i].cw+dis[v][1]==d&&dis[u][0]*2<d&&dis[v][1]*2<d)
					ans=(ans-1ll*cnt[u][0]*cnt[u][0]%mod*cnt[v][1]%mod*cnt[v][1]%mod+mod)%mod;
			}
		}
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：GFyyx (赞：1)

## 解题思路
最短路，容斥原理。

正难则反，直接求解比较麻烦，考虑用所有方案数减去非法的方案数求解。

首先求解出 $S,T$ 出发到任意点 $x$ 的最短时间 $FS_x,FT_x$ 和路径数量 $GS_x,GT_x$。

不难证明，如果不考虑相遇的情况，方案数为 $GS_T \times GT_S$。

#### 相遇情况
在某个点 $u$ 上相遇，枚举相遇的点，需要满足以下条件。

$FS_u=FT_u,FS_u+FT_u=FS_T=FT_S$。

方案数为 $(GS_u \times GT_u)^2$。

在边 $(u,v)$ 上相遇，枚举相遇的边，设这条边的边权为 $w$，需要满足以下条件。

$FS_u+FT_v+w=FS_T=FT_S,FS_u+w>FT_v,FT_v+w>FS_u$。

方案数为 $(GS_u \times GT_v)^2$。

综上，答案为 $GS_T \times GT_S- \sum\limits_{x=1}^{n}(GS_x \times GT_x)^2 - \sum\limits_{i=1}^{m}(GS_{i_u} \times GT_{i_v})^2$。

总时间复杂度为跑 Dijkstra 的 $\Theta(n \log n)$。

---

## 作者：Leap_Frog (赞：1)

### P.S.
鸣谢 @[zhouchenyuan005](https://www.luogu.com.cn/user/87416)，笔者如果没有和他讨论过没法做出此题。  
### Discription.
给定一个**带权无向图**，以及起点和终点。  
有两个人在起点和终点出发，相向而行（  
求他们不相遇的方案数。  

### Solution.
首先，我们有一个结论：
> 如果有一条边 $\{u,v\}$ 在最短路上，那 $dis_{s,u}+w_{u,v}=dis_{s,v}$。

然后我们就把题目中的最短路这个限制去掉了。  
于是我们把题目转化成要求一张图的不自交经过两个点的环数。  
然后据 @[zhouchenyuan005](https://www.luogu.com.cn/user/87416)巨佬 说这是个 NP 问题，假了（这是笔者原来的思路。  

那么很显然，这题得用最短路的性质。  
因为边权为正，所以假设我们把所有在最短路上的边连成一张图，这张图显然是 `Dag`。  
那么在这个图上跑两遍 dp 就好了，可以求出到达每个点的路径数量。  
最后再得到从原点到汇点的路径数，它的平方就是答案。。。可惜显然太 naive 了。  

因为原图要求路径不自交，那么我们斥掉自交的部分就好了。  
因为两个人都得走最短路，所以他们只会相遇一次。  
那么我们枚举他们相遇在点或者边上，减去从s到它以及它到汇点平方的积就好了。  

然后此题就做完了。。。

从 s 到一个点只经过最短路的路径方案数还可以直接用 dijkstra 算，下面代码就是用这种方法算的。  
### Coding.
```cpp
//愿你和你重要的人能够再次重逢！
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
typedef long long ll;const int P=1e9+7;
struct edge{int to,w,nxt;}e[400005];
int n,m,s,t,et,head[200005],dp1[200005],dp2[200005];ll ds1[200005],ds2[200005];
inline void adde(int x,int y,int w) {e[++et]=(edge){y,w,head[x]},head[x]=et;}
inline void dijk(int s,int *dp,ll *ds)
{
	priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > >p;
	ds[s]=0,p.push(make_pair(0,s)),dp[s]=1;for(int i=1;i<=n;i++) if(i^s) ds[i]=1e18;
	while(!p.empty())
	{
		int x=p.top().second;ll w=p.top().first;p.pop();if(w^ds[x]) continue;
		for(int i=head[x];i;i=e[i].nxt)
			if(ds[e[i].to]>ds[x]+e[i].w) dp[e[i].to]=dp[x],ds[e[i].to]=ds[x]+e[i].w,p.push(make_pair(ds[e[i].to],e[i].to));
			else if(ds[e[i].to]==ds[x]+e[i].w) (dp[e[i].to]+=dp[x])%=P;
	}
}
signed main()
{
	read(n),read(m),read(s),read(t);
	for(int i=1,x,y,w;i<=m;i++) read(x),read(y),read(w),adde(x,y,w),adde(y,x,w);
	dijk(t,dp2,ds2),dijk(s,dp1,ds1);long long res=dp1[t];res=res*res%P;
	for(int i=1;i<=n;i++) if((ds1[i]<<1)==ds1[t]) res=(res-1ll*dp1[i]*dp2[i]%P*dp1[i]%P*dp2[i]%P+P)%P;
	for(int x=1;x<=n;x++) for(int i=head[x];i;i=e[i].nxt)
		if(ds1[x]+ds2[e[i].to]+e[i].w==ds1[t]&&ds1[x]+e[i].w>ds2[e[i].to]&&ds2[e[i].to]+e[i].w>ds1[x])
			res=(res-1ll*dp1[x]*dp2[e[i].to]%P*dp1[x]%P*dp2[e[i].to]+P)%P;
	return printf("%lld\n",(res%P+P)%P),0;
}
```

---

## 作者：AlicX (赞：0)

## Solution

一道不错的计数题。因为直接求不相遇的方案十分复杂，所以考虑正难则反，用总的方案数减去相遇的方案数。求方案数很套路：在求最短路的时候开一个数组 $del$ 记录到达点 $i$ 的最短路条数，更新最短路时顺便更新即可。

跑完最短路后，设 $dis1$ 为 $s$ 到 $t$ 的最短路数组，$del1$ 为 $s$ 到 $t$ 的最短路的条数的数组，$dis2$ 和 $del2$ 同理，易得总的方案数为 ${del_t}^2$，接下来考虑求相遇的方案数，共分为两种情况：  
1. 在点上相遇。设 $i$ 为相遇点，那么有 $dis1_i=dis2_i$，且 $dis1_i+dis2_i=dis1_t$，方案数为 ${del1_i}^2 \times {del2_i}^2$。

2. 在边上相遇，设在 $i$ 边上相遇，且连接 $u$，$v$，边权为 $w$，那么有 $dis1_u+dis2_v+w=dis1_t$，且 $dis1_u+w>dis2_v$，以及 $dis2_v+w>dis1_u$，方案数为 ${del1_i}^2 \times {del2_i}^2$。

最后输出答案。注意取模。

```cpp
// Celestial Cyan 
// Luogu uid : 706523 
// Luogu : https://www.luogu.com.cn/problem/AT_arc090_c
// CF : 
// AT : https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/arc090_c
// FTOJ : 
// Contest : AtCoder Regular Contest 090
// Cnblogs : 
// Memory Limit: 256 MB
// Time Limit: 2000 ms 
// 2023/8/1    

#include<bits/stdc++.h>
#define int long long
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
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=1e5+10,M=2e5+10,Mod=1e9+7,INF=1e9+7; 
int n,m; 
int s,t; 
int h[N],idx=0; 
bool st1[N],st2[N];
int u[N],v[N],w[N];
int dis1[N],dis2[N]; 
int del1[N],del2[N]; 
struct Node{ 
	int w; 
	int to,ne; 
}tr[M<<1]; 
struct Mind{ 
	il bool operator<(Mind &Cyan)const{ } 
}; 
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
il void add(int u,int v,int w){ 
	tr[idx].w=w,tr[idx].to=v,tr[idx].ne=h[u],h[u]=idx++; 
} 
il void dij1(){
	priority_queue<pii> q; q.push({0,s});
	memset(st1,false,sizeof st1);  
	for(int i=1;i<=n;i++) dis1[i]=INF; dis1[s]=0; del1[s]=1; 
	while(!q.empty()){ 
		int u=q.top().y; q.pop();
		if(st1[u]) continue; st1[u]=true; 
		for(int i=h[u];i!=-1;i=tr[i].ne){
			int to=tr[i].to; 
			if(dis1[to]>dis1[u]+tr[i].w){
				dis1[to]=dis1[u]+tr[i].w; 
				del1[to]=del1[u]; q.push({-dis1[to],to}); 
			} else if(dis1[to]==dis1[u]+tr[i].w) del1[to]=(del1[to]+del1[u])%Mod; 
		} 
	}
} 
il void dij2(){
	priority_queue<pii> q; q.push({0,t}); 
	memset(st2,false,sizeof st2); 
	for(int i=1;i<=n;i++) dis2[i]=INF; dis2[t]=0; del2[t]=1;  
	while(!q.empty()){ 
		int u=q.top().y; q.pop();
		if(st2[u]) continue; st2[u]=true; 
		for(int i=h[u];i!=-1;i=tr[i].ne){ 
			int to=tr[i].to; 
			if(dis2[to]>dis2[u]+tr[i].w){
				dis2[to]=dis2[u]+tr[i].w; 
				del2[to]=del2[u]; q.push({-dis2[to],to}); 
			} else if(dis2[to]==dis2[u]+tr[i].w) del2[to]=(del2[to]+del2[u])%Mod; 
		} 
	}
} 
signed main(){ 
	memset(h,-1,sizeof h); 
	n=read(),m=read(); s=read(),t=read(); 
	for(int i=1;i<=m;i++){ 
		u[i]=read(),v[i]=read(),w[i]=read(); 
		add(u[i],v[i],w[i]),add(v[i],u[i],w[i]);  
	} dij1(); dij2(); int ans=del1[t]*del1[t]%Mod; // cout<<ans<<endl; 
	for(int i=1;i<=n;i++){ 
		if(dis1[i]+dis2[i]==dis1[t]&&dis1[i]==dis2[i]){
			ans=(ans-del1[i]*del1[i]%Mod*del2[i]%Mod*del2[i]%Mod)%Mod;  
		} 
	} for(int i=1;i<=m;i++){ 
		if(dis1[u[i]]+dis2[v[i]]+w[i]==dis1[t]&&dis1[u[i]]+w[i]>dis2[v[i]]&&dis2[v[i]]+w[i]>dis1[u[i]]){
			ans=(ans-del1[u[i]]*del1[u[i]]%Mod*del2[v[i]]%Mod*del2[v[i]]%Mod)%Mod; 
		} swap(u[i],v[i]); 
		if(dis1[u[i]]+dis2[v[i]]+w[i]==dis1[t]&&dis1[u[i]]+w[i]>dis2[v[i]]&&dis2[v[i]]+w[i]>dis1[u[i]]){
			ans=(ans-del1[u[i]]*del1[u[i]]%Mod*del2[v[i]]%Mod*del2[v[i]]%Mod)%Mod; 
		} 
	} printf("%lld\n",(ans%Mod+Mod)%Mod);  
	return 0;
} /* */ 
```


---

## 作者：1saunoya (赞：0)

## 题意

S 和 T 两个人，S 要走到 T，T 要走到 S，不遇见的方案数。

遇见的定义:走相同的路程，在边上或者在点上相遇。

## 题解

正难则反，没任何限制的条件下，答案显然是 $way_{s,t} \times way_{s,t}$。

我们发现两个人 **至多** 碰到一次，减掉在边上遇到的方案数和在点上遇见的方案数，然后就没了。


在边上遇到: $ds_x + w > dt_y$ 并且 $dt_y + w > ds_x$。

注意到是双向边，要算 $(x,y)$ 和 $(y,x)$ 但是两个最多被统计一次（

在点上遇见显然。

```cpp
#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = x; i < y; i++)
#define all(v) begin(v), end(v)
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T>
istream &operator>> (istream &in, vector<T> &v) {
 for (auto &x : v) {
  in >> x;
 }
 return in;
}
using ll=long long;
const int P = 1e9 + 7;
int main() {
 cin.tie(nullptr)->sync_with_stdio(false);
 int n,m,s,t;
 cin>>n>>m>>s>>t;--s;--t;
 vector<vector<pair<int,int>>>g(n);
 vector<tuple<int,int,int>>e(m);
 vector<int>ways(n),wayt(n);
 rep(i,0,m){
  int x,y,w;cin>>x>>y>>w;--x,--y;e[i]=tie(x,y,w);
  g[x].emplace_back(y,w),g[y].emplace_back(x,w);
 }
 vector<bool>vis(n,false);
 vector<ll>ds(n,1e18);
 priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>q;
 q.emplace(ds[s]=0,s),ways[s]=1;
 while(!q.empty()){
  auto tmp=q.top();q.pop();ll d;int u;tie(d,u)=tmp;
  if(vis[u])continue;vis[u]=1;
  for(auto &t:g[u]){
   int v,w;tie(v,w)=t;if(ds[v]>d+w)q.emplace(ds[v]=d+w,v),ways[v]=0;
   if(ds[v]==d+w)ways[v]+=ways[u],ways[v]%=P;
  }
 }
 vis.assign(n,false);vector<ll>dt(n,1e18);
 q.emplace(dt[t]=0,t),wayt[t]=1;
 while(!q.empty()){
  auto tmp=q.top();q.pop();ll d;int u;tie(d,u)=tmp;
  if(vis[u])continue;vis[u]=1;
  for(auto&t:g[u]){
   int v,w;tie(v,w)=t;if(dt[v]>d+w)q.emplace(dt[v]=d+w,v),wayt[v]=0;
   if(dt[v]==d+w)wayt[v]+=wayt[u],wayt[v]%=P;
  }
 }
 int ans=(long long)ways[t]*wayt[s]%P;ll dst=ds[t];
 rep(i,0,n)if(ds[i]==dt[i]&&ds[i]+dt[i]==dst)ans-=(long long)ways[i]*ways[i]%P*wayt[i]%P*wayt[i]%P,ans+=ans>>31&P;
 for(auto &t:e){
  int x,y,w;tie(x,y,w)=t;
  if(ds[x]+dt[y]+w==dst&&ds[x]+w>dt[y]&&dt[y]+w>ds[x]){ans-=(long long)ways[x]*wayt[y]%P*ways[x]%P*wayt[y]%P,ans+=ans>>31&P;}
  swap(x,y);
  if(ds[x]+dt[y]+w==dst&&ds[x]+w>dt[y]&&dt[y]+w>ds[x]){ans-=(long long)ways[x]*wayt[y]%P*ways[x]%P*wayt[y]%P,ans+=ans>>31&P;}
 }
 cout<<ans<<"\n";
}
```

---

