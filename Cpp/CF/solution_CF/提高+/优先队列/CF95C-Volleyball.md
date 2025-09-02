# Volleyball

## 题目描述

Petya loves volleyball very much. One day he was running late for a volleyball match. Petya hasn't bought his own car yet, that's why he had to take a taxi. The city has $ n $ junctions, some of which are connected by two-way roads. The length of each road is defined by some positive integer number of meters; the roads can have different lengths.

Initially each junction has exactly one taxi standing there. The taxi driver from the $ i $ -th junction agrees to drive Petya (perhaps through several intermediate junctions) to some other junction if the travel distance is not more than $ t_{i} $ meters. Also, the cost of the ride doesn't depend on the distance and is equal to $ c_{i} $ bourles. Taxis can't stop in the middle of a road. Each taxi can be used no more than once. Petya can catch taxi only in the junction, where it stands initially.

At the moment Petya is located on the junction $ x $ and the volleyball stadium is on the junction $ y $ . Determine the minimum amount of money Petya will need to drive to the stadium.

## 说明/提示

An optimal way — ride from the junction 1 to 2 (via junction 4), then from 2 to 3. It costs 7+2=9 bourles.

## 样例 #1

### 输入

```
4 4
1 3
1 2 3
1 4 1
2 4 1
2 3 5
2 7
7 2
1 2
7 7
```

### 输出

```
9
```

# 题解

## 作者：EuphoricStar (赞：8)

## 思路

先求出所有点对之间的最短路。

然后有一种很显然的构图方法：如果 $dis_{i,j} \le t_i$，则向 $i$ 到 $j$ 连一条权值为 $c_i$ 的边。

最后重新跑最短路即可。

## 代码

```cpp
/*

p_b_p_b txdy
AThousandMoon txdy
AThousandSuns txdy
hxy txdy

*/

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 1010;
const ll inf = 0x3f3f3f3f3f3f3f3fLL;

ll n, m, S, T, dis[maxn][maxn], f[maxn];
bool vis[maxn];
vector<pii> G[maxn];
struct node {
	ll dis, pos;
	node() {}
	node(ll a, ll b) : dis(a), pos(b) {}
	bool operator < (const node &u) const {
		return dis > u.dis;
	}
};
priority_queue<node> pq;

void dij(int S, ll *dis) {
	for (int i = 1; i <= n; ++i) {
		dis[i] = inf;
	}
	memset(vis, 0, sizeof(vis));
	dis[S] = 0;
	pq.push(node(0, S));
	while (pq.size()) {
		int u = pq.top().pos;
		pq.pop();
		if (vis[u]) {
			continue;
		}
		vis[u] = 1;
		for (pii p : G[u]) {
			ll v = p.fst, d = p.scd;
			if (dis[v] > dis[u] + d) {
				dis[v] = dis[u] + d;
				if (!vis[v]) {
					pq.push(node(dis[v], v));
				}
			}
		}
	}
}

void solve() {
	scanf("%lld%lld%lld%lld", &n, &m, &S, &T);
	while (m--) {
		ll u, v, d;
		scanf("%lld%lld%lld", &u, &v, &d);
		G[u].pb(make_pair(v, d));
		G[v].pb(make_pair(u, d));
	}
	for (int s = 1; s <= n; ++s) {
		dij(s, dis[s]);
	}
	for (int i = 1; i <= n; ++i) {
		G[i].clear();
	}
	for (int i = 1; i <= n; ++i) {
		ll t, c;
		scanf("%lld%lld", &t, &c);
		for (int j = 1; j <= n; ++j) {
			if (dis[i][j] <= t && i != j) {
				G[i].pb(make_pair(j, c));
			}
		}
	}
	dij(S, f);
	printf("%lld", f[T] < inf ? f[T] : -1LL);
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

## 作者：Komorebi_03 (赞：4)

### 思路：
跑两边 Dijkstra。

第一次跑 $n$ 次 Dijkstra，求出所有点间的最短路。

然后建新图再跑一次 Dijkstra，求出 $S$ 点到 $T$ 点的最短路。

注意开 long long，并且 INF 要设大一点（~~因为这个被卡了好几发~~。
```cpp
// Problem: CF95C Volleyball
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF95C
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By:Komorebi_03
#include<bits/stdc++.h>
using namespace std;
#define clear(a) memset(a,0,sizeof a)
#define int long long
const int INF = 0x7fffffffffffffff;
const int N = 1e6+5;
int n,m,s,t,dis[N],dist[N],cost[N];
bool vis[N];
vector<pair<int,int>> g[N],G[N];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void DJ1(int s)
{
	clear(vis);
	for (int i=0;i<=n;i++)
		dis[i]=INF;
	dis[s]=0;
	priority_queue<pair<int,int>> q;
	q.push(make_pair(0,s));
	while (!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])
			continue;
		vis[u]=true;
		for (int i=0;i<g[u].size();i++)
		{
			int v=g[u][i].first;
			if(!vis[v] && dis[v]>g[u][i].second+dis[u])
			{
				dis[v]=g[u][i].second+dis[u];
				q.push(make_pair(-dis[v],v));
			}
		}
	}
	for (int i=1;i<=n;i++)
		if(i!=s && dis[i]<=dist[s])
			G[s].push_back(make_pair(i,cost[s]));
}

void DJ2(int s)
{
	clear(vis);
	for (int i=0;i<=n;i++)
		dis[i]=INF;
	dis[s]=0;
	priority_queue<pair<int,int>> q;
	q.push(make_pair(0,s));
	while (!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])
			continue;
		vis[u]=true;
		for (int i=0;i<G[u].size();i++)
		{
			int v=G[u][i].first;
			if(!vis[v] && dis[v]>G[u][i].second+dis[u])
			{
				dis[v]=G[u][i].second+dis[u];
				q.push(make_pair(-dis[v],v));
			}
		}
	}
}

signed main()
{
	n=read();
	m=read();
	s=read();
	t=read();
	for (int i=1;i<=m;i++)
	{
		int u=read();
		int v=read();
		int w=read();
		g[u].push_back(make_pair(v,w));
		g[v].push_back(make_pair(u,w));
	}
	for (int i=1;i<=n;i++)
	{
		dist[i]=read();
		cost[i]=read();
	}
	for (int i=1;i<=n;i++)
		DJ1(i);
	DJ2(s);
	if(dis[t]==INF)
		cout<<-1;
	else
		cout<<dis[t];
	return 0;
	//Amireux_35
}
```


---

## 作者：ifyml (赞：2)

这题就是用了两遍dijkstra（队列优化）  
第一次是用来建一个新图  
第二次就找最短路


```cpp
#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#define N 1001
using namespace std;
int n,m,s,f,a,b;
struct ss{
	int to;
	long long c;
	bool operator < (const ss &r)const
	{return r.c<c;}//重载小于符号：让它明白你的优先队列的优先级
};
vector<ss> q[N*2],q2[N*2];//两个图:原图和新图
int d[N],co[N],used[N];
long long dis[N],di;
void dij1(int ok)
{
	for(int i=0;i<=n;i++)dis[i]=9999999999999,used[i]=0;
    //这个地方要注意：它的数据的距离很大，所以初始化要更大...
	dis[ok]=0;
	priority_queue<ss> que;
	que.push((ss){ok,0});
	while(!que.empty())
	{
		ss te=que.top();que.pop();
		int to=te.to;
		if(used[to])continue;//如果已经得到最优值，就无需再继续
		used[to]=1;
		for(int i=0;i<q[to].size();i++)
		{
			int v=q[to][i].to;
			long long dist=q[to][i].c+dis[to];
			if(!used[v]&&dist<dis[v])
			{
				dis[v]=dist;
				que.push((ss){v,dis[v]});//加入队列
			}
		}
	}
	for(int i=1;i<=n;i++)
	 if(i!=ok&&d[ok]>=dis[i])
		q2[ok].push_back((ss){i,co[ok]});
        //开始建图：这个点和能到达的点建边，以cost为边权，
        //第二遍只需找最短路，就可以找到起点到终点的最小代价
}
void dij2(int ok)
{
	for(int i=0;i<=n;i++)dis[i]=9999999999999,used[i]=0;
	dis[ok]=0;
	priority_queue<ss> que;
	que.push((ss){ok,0});
	while(!que.empty())
	{
		ss te=que.top();que.pop();
		int to=te.to;
		if(used[to])continue;
		used[to]=1;
		for(int i=0;i<q2[to].size();i++)
		{
			int v=q2[to][i].to;
			long long dist=q2[to][i].c+dis[to];
			if(!used[v]&&dist<dis[v])
			{
				dis[v]=dist;
				que.push((ss){v,dis[v]});
			}
		}
	}
	if(dis[f] == 9999999999999)printf("-1\n");//不能到达
	else printf("%lld\n",dis[f]);//输出最小代价
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&f);
    for(int i=1;i<=m;i++)
	 {
		 scanf("%d%d%lld",&a,&b,&di);
		 q[a].push_back((ss){b,di});//建边
		 q[b].push_back((ss){a,di});
	 }
    for(int i=1;i<=n;i++)
	 scanf("%d%d",&d[i],&co[i]);//每辆车的行驶距离和相应费用
	for(int i=1;i<=n;i++)
	 dij1(i);
	dij2(s);
	return 0;//完美结束
}

```

---

## 作者：Ak_hjc_using (赞：0)

### 思路
其实就是 Dijkstra 算法的模板题。

考虑使用 Dijkstra 最短路算法。\
学习链接（[Dijkstra](https://www.luogu.com.cn/article/13x1az3d)）

题目给出了一张 $n$ 个点，$m$ 条边的无向图，并不是让我们直接跑最短路，而是每个点有一个 $t$ 和 $c$，表示这个点最多跑 $t$ 的距离，需要 $c$ 的花费。

那么思路就非常明显了：

- 先直接建图跑最短路，算出以所有点为起点的最短路 $dis_{i, j}$。
- 双重循环判断两点 $i$，$j$，是否 $dis_{i, j} \le t_{i}$，如果是就可以直接建一条边权为 $c_{i}$ 边。\
（注意：**不要建重边**）
- 然后再跑一边最短路，算出起点到终点的最短路径即可。

### 代码：
```cpp
#include <bits/stdc++.h>
typedef long long LL;
using namespace std;
#define int long long
const int INF = 1e18;
const int N = 2e3 + 5;

struct Edge {
	int v, w;
};
struct Node {
	int id, w;
	bool operator < (const Node & a) const {
		return w > a.w;
	}
};
vector<Edge> G[N] ;
int n, m, dis[N][N], vis[N], s, t, T[N], c[N];
void Dijkstra(int *dis, int ss) {
	for (int i = 1; i <= n; i++) {
		dis[i] = INF;
		vis[i]  = 0;
	}
	priority_queue<Node> Q;
	dis[ss] = 0;
	Q.push({ss, 0});
	while (!Q.empty()) {
		int u = Q.top().id;
		Q.pop();
		if (vis[u] == true) continue ;
		vis[u] = true;
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i].v, w = G[u][i].w;
			if (vis[v] == false && dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				Q.push({v, dis[v]});
			}
		}
	}
	return ;
}
void add_edge(int u, int v, int w) {
	G[u].push_back({v, w});
	G[v].push_back({u, w});
	return ;
}
void work() {
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		add_edge(u, v, w);
	}
	for (int i = 1; i <= n; i++) Dijkstra(dis[i], i);
	for (int i = 1; i <= n; i++) G[i].clear();
	for (int i = 1; i <= n; i++) cin >> T[i] >> c[i];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) continue ;
			if (dis[i][j] <= T[i]) {
				G[i].push_back({j, c[i]});
			}
		}
	}
	Dijkstra(dis[s], s);
	if (dis[s][t] != INF) cout << dis[s][t] << '\n';
	else cout << -1 << '\n'; 
	return ;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	work();
	return 0;
}
```

---

## 作者：OIer_ACMer (赞：0)

# 题目解析：

本题由于十分复杂，又是限制车费又是限制每辆车行驶距离的。所以，我们要“逆其道而行之”。

我们可以首先用迪杰斯特拉算法从 $1$ 到 $n$ 枚举每一个点，找出每个点到其它所有点的最短路，并用 $dis$ 数组储存。

之后，到了第二步，求最短花费。我们再把花费看作距离，再跑一个最短路，不过，这个时候的**最短路由于每辆车有其固定的行驶距离**，所以只有在满足车的最大行驶距离时，才可以更新。再说简单点，这部分就相当于重新建一次图，只不过区别是再每次添加权值时直接进行求解计算代价，不用建完图之后再一一求解，且不用存图，减少了空间复杂度炸的风险。

最后，由于数据最终答案太大，所以在这里建议开长长整型数组，且数组范围一定要开够。

还有，本题我们最好用[数组对](https://blog.csdn.net/sevenjoin/article/details/81937695)来存放每个点下标以及其答案，因为优先队列时间复杂度不是很稳定，但主要原因是，容易写错~~本人亲测~~！！！

# 代码如下：

```

#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f3f3f3f3f
#define int long long
struct node
{
    int to, val, next;
} edge[1000009];
int head[1000009], cnt;
void add(int u, int v, int w)
{
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    edge[cnt].val = w;
    head[u] = cnt;
}
int n, m;
int st, ed;
// int t[1000009], c[1000009];

int vis[1009];
int dis[1009][1009];
int cover[1009], w[1009];
int cost[1009];
void dij(int s)
{
    memset(vis, 0, sizeof(vis));
    fill(dis[s] + 1, dis[s] + 1 + n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push(make_pair(0, s));
    dis[s][s] = 0;
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
        {
            continue;
        }
        vis[u] = 1;
        for (int i = head[u]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            int w = edge[i].val;
            if (dis[s][v] > dis[s][u] + w)
            {
                dis[s][v] = dis[s][u] + w;
                q.push(make_pair(dis[s][v], v));
            }
        }
    }
}
signed main()
{
    cin >> n >> m;
    cin >> st >> ed;
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> cover[i] >> w[i];
        dij(i);
    }
    fill(cost + 1, cost + 1 + n, INF);
    memset(vis, 0, sizeof(vis));
    cost[st] = 0;
    while (1)
    {
        int v = -1;
        for (int u = 1; u <= n; ++u)
        {
            // cout << vis[u] << endl;
            if (vis[u] == 0 && (v == -1 || cost[u] < cost[v]))
            {
                v = u;
            }
        }
        if (v == -1)
        {
            break;
        }
        vis[v] = 1;
        for (int u = 1; u <= n; ++u)
        {
            if (dis[v][u] <= cover[v])
            {
                cost[u] = min(cost[u], cost[v] + w[v]);
            }
        }
    }
    if (cost[ed] == INF)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << cost[ed] << endl;
    }
    return 0;
}

```

---

## 作者：aaa_lvzekai (赞：0)

## 注意事项

- 如果你 WA on test 3，请检查是否在无解时输出 $-1$。（翻译没说）
- 如果你 RE on test 22 or 32，请检查是否将数组开大。（比如 $1000000$）

## 题意

给定一个无向正权图，每次在 $i$ 点给定 $t$，$c$。表示可以在 $i$ 点走到距离 $\le t$ 的一个点，花费为 $c$。告诉你起点、终点，求最少花费。

## 思路

很明显，我们可以每次在第 $i$ 个结点跑 Dijkstra。然后把距离 $\le t$ 的加入 wait_add 数组，并按照 wait_add 来建边权为 $c$ 的有向图跑 Dijkstra 即可。

## AC代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1000010,INF=0x3f3f3f3f3f3f3f3f;
ll n,m,s,t,cnt,dist[N];
pair<pair<ll,ll>,ll> wait_add[N];
ll h[N],e[N],w[N],ne[N],idx;
bool vis[N];
void add(ll x,ll y,ll z)
{
	e[idx]=y,w[idx]=z,ne[idx]=h[x],h[x]=idx++;
}
void dijkstra(ll start)
{
	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> heap;
	pair<ll,ll> u;
	heap.push({0,start});
	memset(dist,0x3f,sizeof(dist));
	dist[start]=0;
	memset(vis,false,sizeof(vis));
	while(heap.size())
	{
		u=heap.top();
		heap.pop();
		if(vis[u.second])
		{
			continue;
		}
		vis[u.second]=true;
		for(int i=h[u.second],j;~i;i=ne[i])
		{
			j=e[i];
			if(dist[j]>dist[u.second]+w[i])
			{
				dist[j]=dist[u.second]+w[i];
				heap.push({dist[j],j});
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	cin>>s>>t;
	memset(h,-1,sizeof(h));
	while(m--)
	{
		ll x,y,z;
		cin>>x>>y>>z;
		add(x,y,z),add(y,x,z);
	}
	for(int i=1;i<=n;i++)
	{
		ll x,y;
		cin>>x>>y;
		dijkstra(i);
		for(int j=1;j<=n;j++)
		{
			if(i!=j&&dist[j]<=x)
			{
				cnt++;
				wait_add[cnt].first.first=i,wait_add[cnt].first.second=j,wait_add[cnt].second=y;
			}
		}
	}
	memset(h,-1,sizeof(h)),idx=0;
	for(int i=1;i<=cnt;i++)
	{
		add(wait_add[i].first.first,wait_add[i].first.second,wait_add[i].second);
	}
	dijkstra(s);
	if(dist[t]>=INF/2)
	{
		cout<<-1<<"\n";
	}
	else
	{
		cout<<dist[t]<<"\n";
	}
	return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

很水的最短路题。

很显然地先对原有的图跑一遍最短路，假如 $dis_{i,j} \leq t_i$，就可以从 $i \to j$，花费为 $c_i$，所以再建出一个图，用 $c_i$ 做为边权，求出 $S$ 到 $T$ 的最短路即可。总的时间复杂度为 $O(n^2 \log n)$。

注意开 `long long`。

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second 
#define il inline 
#define db double
#define il inline 
#define low(x) x&-x 
#define pb(x) push_back(x) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=1010,INF=1e18+7;  
int n,m; 
int S,T; 
pii a[N]; 
bool st[N]; 
int dise[N]; 
int dis[N][N]; 
int h[N],idx=0;  
int he[N],idxe=0; 
struct Node{ 
	int w; 
	int to,ne; 
}tr[N<<1],tre[N*N];  
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
il void adde(int u,int v,int w){
	tre[idxe].w=w,tre[idxe].to=v,tre[idxe].ne=he[u],he[u]=idxe++; 
} 
il void dij(int s){ 
	priority_queue<pii> q; 
	memset(st,false,sizeof st); 
	dis[s][s]=0; q.push({0,s}); 
	while(!q.empty()){ 
		int u=q.top().y; q.pop(); 
		if(st[u]) continue; st[u]=true; 
		for(int i=h[u];i!=-1;i=tr[i].ne){
			int to=tr[i].to; 
			if(dis[s][to]>dis[s][u]+tr[i].w){
				dis[s][to]=dis[s][u]+tr[i].w; 
				q.push({-dis[s][to],to}); 
			} 
		} 
	} 
} 
il void dije(int s){ 
	priority_queue<pii> q; 
	memset(st,false,sizeof st); 
	dise[s]=0; q.push({0,s}); 
	while(!q.empty()){ 
		int u=q.top().y; q.pop(); 
		if(st[u]) continue; st[u]=true; 
		for(int i=he[u];i!=-1;i=tre[i].ne){
			int to=tre[i].to; 
			if(dise[to]>dise[u]+tre[i].w){
				dise[to]=dise[u]+tre[i].w; 
				q.push({-dise[to],to}); 
			} 
		} 
	} 
} 
signed main(){ 
	memset(h,-1,sizeof h); 
	memset(he,-1,sizeof he); 
	n=read(),m=read(),S=read(),T=read(); 
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dis[i][j]=INF,dise[i]=INF; 
	while(m--){ 
		int u=read(),v=read(),w=read(); 
		add(u,v,w),add(v,u,w); 
	} for(int i=1;i<=n;i++) a[i].x=read(),a[i].y=read(); 
	for(int i=1;i<=n;i++){
		dij(i); 
		for(int j=1;j<=n;j++){
			if(dis[i][j]<=a[i].x){ 
				adde(i,j,a[i].y);
			} 
		} 
	} dije(S); printf("%lld\n",(dise[T]==INF)?-1:dise[T]); 
	return 0; 
} /* */ 
```


---

## 作者：yi_fan0305 (赞：0)

一看题，好像是最短路，数据范围 $n \le 1000$，可以跑 dijkstra，但是他要求每个点最远走 $t_i$ 的距离，所以我们要预处理出点两两之间的距离，跑 $n$ 遍 dijkstra 即可。

处理完之后，就可以根据 $t_i$ 和 $c_i$ 建新图了，在新图上跑一边最短路求出答案即可。最后的最后，一定要注意，如果不能到达，要输出 $-1$。~~这个翻译没说。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;

const int N = 1010;

int n, m, S, T;
ll t[N], c[N];
ll dis[N][N], Dis[N];
bool vis[N];
vector<pli> son[N], nson[N];

void dij(int s) {
	priority_queue<pli, vector<pli>, greater<pli> > q;
	for (int i = 1; i <= n; ++ i) {
		dis[s][i] = 1e18;
		vis[i] = 0;
	}
	dis[s][s] = 0;
	q.push({0, s});
	while (! q.empty()) {
		int u = q.top().second;
		q.pop();
		if (vis[u])	continue;
		vis[u] = 1;
		for (auto [w, v] : son[u]) {
			if (dis[s][v] > dis[s][u] + w) {
				dis[s][v] = dis[s][u] + w;
				q.push({dis[s][v], v});
			}
		}
	}
}

void Dij(int s) {
	priority_queue<pli, vector<pli>, greater<pli> > q;
	for (int i = 1; i <= n; ++ i) {
		Dis[i] = 1e18;
		vis[i] = 0;
	}
	Dis[s] = 0;
	q.push({0, s});
	while (! q.empty()) {
		int u = q.top().second;
		q.pop();
		if (vis[u])	continue;
		vis[u] = 1;
		for (auto [w, v] : nson[u]) {
			if (Dis[v] > Dis[u] + w) {
				Dis[v] = Dis[u] + w;
				q.push({Dis[v], v});
			}
		}
	}
}

int main() {
	scanf("%d%d%d%d", &n, &m, &S, &T);
	for (int i = 1, x, y; i <= m; ++ i) {
		ll w;
		scanf("%d%d%lld", &x, &y, &w);
		son[x].push_back({w, y});
		son[y].push_back({w, x});
	}
	for (int i = 1; i <= n; ++ i) {
		scanf("%lld%lld", &t[i], &c[i]);
		dij(i);
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= n; ++ j) {
			if (dis[i][j] <= t[i]) {
				nson[i].push_back({c[i], j});
			}
		}
	}
	Dij(S);
	if (Dis[T] == 1e18) {
		puts("-1");
		return 0;
	}
	printf("%lld\n", Dis[T]);
	return 0;
}
```

---

## 作者：Bulyly (赞：0)

### 题意
给出 $n$ 个节点，每个点都有一辆车。每辆车都有一个最远行驶距离和代价，**且只能到最大路程的节点。** 每辆车只能用一次，求从起点 $x$ 到终点 $y$ 的最小花费，若不能到达输出 $-1$。

### 思路
先做一遍全源最短路，求出每个点对之间的最短距离。然后再以 $x$ 为起点，做一遍单源最短路，与朴素最短路相比，此题距离更新时需要满足车的距离**不小于**点对之间的距离。

下附代码：
```cpp
#include <cstdio> 
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define x first
#define y second

using namespace std;

typedef long long LL;
typedef pair<LL,LL> PLL;
const int N=2010;
const LL INF=0x3f3f3f3f3f3f3f3f;
vector<PLL> edge[N];
int n,m,x,y;
LL dist[N][N];
bool st[N];
LL cost[N],path[N],w[N];

void dijkstra1(int s)
{
	memset(st,false,sizeof st);
	fill(dist[s]+1,dist[s]+n+1,INF);
    priority_queue<PLL,vector<PLL>,greater<PLL>> q;
    dist[s][s]=0;
	q.push({0,s});
    while(q.size())
    {
    	int t=q.top().y;q.pop();
    	if(st[t])  continue;
    	st[t]=true;
    	for(auto v:edge[t])
    	{
    		LL j=v.x,w=v.y;
    		if(dist[s][j]>dist[s][t]+w)
    		{
    			dist[s][j]=dist[s][t]+w;
    			q.push({dist[s][j],j});
			}
		}
    }
}

void dijkstra2()
{
	fill(cost+1,cost+n+1,INF);
	memset(st,false,sizeof st);
	cost[x]=0;
	for(int i=1;i<=n;i++)
	{
		int t=-1;
		for(int j=1;j<=n;j++)
		    if(!st[j] && (t==-1||cost[t]>cost[j]))
		       t=j;
		st[t]=1;
		for(int j=1;j<=n;j++)
			if(dist[t][j]<=path[t])
			   cost[j]=min(cost[j],cost[t]+w[t]);
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%d%d",&x,&y);
	
	for(int i=1;i<=m;i++)
	{
		int a,b;LL c;
		scanf("%d%d%lld",&a,&b,&c);
		edge[a].push_back({b,c});
		edge[b].push_back({a,c});
	}
	
	for(int i=1;i<=n;i++)  dijkstra1(i); 
	for(int i=1;i<=n;i++)  scanf("%lld%lld",&path[i],&w[i]);
	dijkstra2();
	if(cost[y]==INF)  puts("-1");
	else printf("%lld\n",cost[y]);
	
	return 0;
}
```
完结撒花~

---

## 作者：wzy2021 (赞：0)

跑两遍最短路。

设 $dis_{i,j}$ 表示从 $i$ 走到 $j$ 的最短路径，注意这里不是乘车。

对于每一个在 $i$ 位置的司机，

如果 $dis_{i,j} \leq t_i$，则 $i$ 司机就可以从 $i$ 开到 $j$，花费为 $c_i$,

我们就再建一个图，若能乘车从 $i$ 到 $j$ 并要花费 $c$，那么我们就连一条从 $i$ 到 $j$，长度为 $c$ 的边。

最后我们在上图的基础上，求一遍最短路，求出 $x$ 到 $y$ 的最小花费。

备注：发现 $n, m \leq 1000$，$dis_{i, j}$ 就 $n$ 遍 Dijskra 算出即可。

~~~cpp
#include <queue>
#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

const int N = 1010;
const ll inf = (1ll << 60);

int n, m;
int vis[N];
ll dis[N][N];
int t[N], c[N];
vector <pair <int, ll> > e[N]; // 用 vector 存图

int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	if (f == 1) return x;
	else if (f == -1) return -x;
}

void dij (int s) { // 以 s 为起点求到其他点的最短路
	priority_queue <pair<ll, int> > pq;
	for (int i = 1; i <= n; ++i) {
		dis[s][i] = inf; vis[i] = false; // 每次都要把 vis[i] 清空
	}
	pq.push (make_pair (0, s)); dis[s][s] = 0;
	while (!pq.empty()) {
		int u = pq.top().second; ll d = -pq.top().first; pq.pop();
		if (vis[u]) continue;
		vis[u] = true;
		for (int i = 0; i < e[u].size(); ++i) {
			pair <int, ll> v = e[u][i];
			if (dis[s][v.first] > d + v.second) {
				dis[s][v.first] = d + v.second; pq.push (make_pair (-dis[s][v.first], v.first)); // 由于是大根堆，所以进入 pq 的权值变号，保证是小的先。
			}
		}
	}
}

int main() {
	int x, y;
	n = read(); m = read(); x = read(); y = read();
	for (int i = 1; i <= m; ++i) {
		int u, v, w; u = read(); v = read(); w = read();
		e[u].push_back (make_pair (v, w)); e[v].push_back (make_pair (u, w));
	}
	for (int i = 1; i <= n; ++i) {
		t[i] = read(); c[i] = read(); 
	}
	for (int i = 1; i <= n; ++i) {
		dij (i); // 对于每个 i 都求一次最短路
	}
	for (int i = 1; i <= n; ++i) {
		e[i].clear(); // 要新建图，别忘清空！！！
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (dis[i][j] <= t[i] && i != j) { // 注意：i != j
				e[i].push_back (make_pair (j, c[i]));
			}
		}
	}
	dij (x); // 起点是 x，不是 1。
	if (dis[x][y] == inf) printf ("-1\n");
	else printf ("%lld\n", dis[x][y]);
	return 0;
}
~~~

---

## 作者：Vitamin_B (赞：0)

# 思路
先跑一遍全源最短路（要用 $n$ 次 dijkstra，floyd 可能会超时）算出距离，然后给 $dis_{i\to j}\le t$ 的点对连上一条边跑最短路算距离。

[Code](https://codeforces.com/problemset/submission/95/266255338)。

---

