# [USACO05MAR] Ombrophobic Bovines 发抖的牛

## 题目描述

FJ 的牛们非常害怕淋雨，那会使他们瑟瑟发抖。他们打算安装一个下雨报警器，并且安排了一个撤退计划。他们需要计算最少的让所有牛进入雨棚的时间。  
牛们在农场的 $F$ 个田地上吃草。有 $P$ 条双向路连接着这些田地。路很宽，无限量的牛可以通过。田地上有雨棚，雨棚有一定的容量，牛们可以瞬间从这块田地进入这块田地上的雨棚。  
请计算最少的时间，让每只牛都进入雨棚。

## 说明/提示

对于 $100\%$ 的数据：$1\le F\le 200$，$1\le P\le 1500$。

## 样例 #1

### 输入

```
3 4
7 2
0 4
2 6
1 2 40
3 2 70
2 3 90
1 3 120
```

### 输出

```
110```

# 题解

## 作者：郑朝曦zzx (赞：8)

# 一 解题算法
本题所用的算法是最短路、二分答案、网络最大流。此处最短路使用 Floyd 算法，最大流使用 Dinic 算法。
# 二 解题方法
### 建图：
网络流问题中**建图**（未知问题已知化）很重要，那么这题应该怎么建图呢？

先分析题目，题目要求最小时间，所以肯定符合二分答案的性质。先拆点，把牛棚和雨棚拆开，对于每次二分到的时间，如果某两点之间可以在这个时间内到达，则建起一条无限流量的边。然后建一个超级源点，到每个牛棚建一条边权为牛的数量的边，最后建一个超级汇点，每个雨棚连一条边权为雨棚容量的边到汇点。
### “检测”函数：
众所周知，二分答案中有一个检测函数，那么这个函数怎么写呢？

每次跑一下最大流算法，如果流量大于总牛量则返回真，否则返回假。
# 三 参考代码
我做这到题的时候最大流写的不太熟练，是照着题解写的（并非抄，哪里借鉴代码中我会尽量注明），所以我的代码和一些题解会比较相似。这是完整代码：
```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#define ll long long
#define maxn 4100
#define maxm 16000
#define inf 100000000000000000
using namespace std;
int n, m, cnt = 1, S, T;
ll ans = inf, sum;
int cow[maxn], house[maxn], head[maxn], nlast[maxn];
ll dis[maxn][maxn];
ll Min(ll x, ll y) { return x <= y ? x : y; }
struct edge
{
	int to, next;
	ll f;
}e[maxm << 3];
void add_edge(int f, int t, ll fl)
{
	e[++cnt] = (edge){t, head[f], fl};
	head[f] = cnt;
	e[++cnt] = (edge){f, head[t], 0};
	head[t] = cnt;
}
void input()
{
	scanf("%d %d", &n, &m);
	S = 2 * n + 1;
	T = 2 * n + 2;
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d %d", &cow[i], &house[i]);
		sum += (ll)cow[i];
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			dis[i][j] = inf;
	for (int i = 1; i <= n; ++i)
		dis[i][i] = 0;
	for (int i = 1; i <= m; ++i)
	{
		int from, to, Dis;
		scanf("%d %d %d", &from, &to, &Dis);
		dis[from][to] = Min(dis[from][to], Dis);
		dis[to][from] = Min(dis[to][from], Dis);
        //这里借鉴了题解
	}
}
void init()
{
	memset(head, 0, sizeof(head));
	memset(nlast, 0, sizeof(nlast));
	cnt = 1;
}
void Floyd()
{
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				dis[i][j] = Min(dis[i][j], dis[i][k] + dis[k][j]);
//	for (int i = 1; i <= n; ++i)
//	{
//		for (int j = 1; j <= n; ++j)
//			printf("%lld ", dis[i][j]);
//		puts(" ");
//	}
}
int dist[maxn];
bool vis[maxn];
bool bfs()
{
	//bfs判断连通性，以及每一个点到终点的距离
	memset(dist, 0, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	queue <int> q;
	vis[T] = true;
	dist[T] = 1;
	q.push(T);
	while (!q.empty())
	{
		const int now = q.front();
		//printf("%d ", now);
		q.pop();
		for (int i = head[now]; i; i = e[i].next)
		{
			const int to = e[i].to;
			if (vis[to] == false && e[i ^ 1].f)
			{//如果这条边的反向边还有残量，而且这个节点没被访问过
				vis[to] = true;
				dist[to] = dist[now] + 1;
				q.push(to);
			}
		}
	}
	return vis[S];
}
ll Dinic(int x, ll f)
{
	if (x == T) return f;
	//如果这个点就是终点
	ll now = f;
	//now表示剩余流量
	for (int i = nlast[x]; i; i = e[i].next)
	{
		const int to = e[i].to;
		if (dist[to] == dist[x] - 1 && e[i].f)
		{//Dinic的增广原则为先增广较短的增广路
			const ll a = Dinic(to, Min(now, e[i].f));
			//a记录增广路上所有边的最小值
			e[i].f -= a;
			//e[i ^ 1] 为反悔边，即可以退回流量
			e[i ^ 1].f += a;
			now -= a;
			//增广出去剩余流量减少
			if (now == 0) return f;
		}
	}
	return f - now;
	//返回这条路径能增广的量
}
ll maxflow()
{
	ll now = 0;
	while (bfs())
	{
		for (int i = 1; i <= n * 2 + 2; ++i)
			nlast[i] = head[i];
		now += Dinic(S, inf);
	}
	return now;
}
bool check(ll mid)
{
	init();
	for (int i = 1; i <= n; ++i)
	{
		add_edge(S, i, cow[i]);
		add_edge(i + n, T, house[i]);
		for (int j = 1; j <= n; ++j)
		{
			if (i == j || dis[i][j] <= mid)
				add_edge(i, j + n, inf);
                //这里借鉴了题解。
		}
	}
	ll F = maxflow();
//	printf("%lld\n", F);
	return (F >= sum);
}
void search()
{
	ll l = 0, r = inf;
	while (l <= r)
	{
		ll mid = (l + r) >> 1;
		//printf("%lld %d\n", mid, check(mid));
		if (check(mid) == true)
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
}
void output()
{
	if (ans == inf || ans == 0) printf("-1\n");
	else printf("%lld", ans);
}
int main()
{
	input();
	Floyd();
	search();
	output();
	return 0;
}
```


管理员，求通过。



---

## 作者：青鸟_Blue_Bird (赞：4)

在看这篇题解之前，您首先需要学会： 二分求解，Floyd全源最短路，Dicnic网络最大流（当然啦,神仙们写Dicnic二进制优化、HLPP预流推进更好）

回到题目，第一眼看上去，我的第一反应是最短路和贪心。但是，很快就发现这些想法根本行不通。为什么呢？简单解释一下：

最短路算法要求的是有**起点**，有**终点**，但是这道题很明显是无序的。一个牛可以前往任意的雨棚，最短路不好统计。

那么，贪心呢？如果我们贪心地将一头牛往最近的雨棚塞，很有可能导致别处的牛无法挤进来，从而**大幅延长**别的牛的运动时间，如下图所示。方案被否决。

（圆圈中数字代表雨棚容量，d代表距离）
![image.png](https://i.loli.net/2020/08/17/7xI6BC5F9m1qtQs.png)

既然这些算法都不好搞，不妨换个思路。

首先，无论我们的牛前往哪个雨棚，走得肯定是**最短路**，于是我们可以求一个全源最短路。

其次，可以想到，我们最终的答案**仅**取决于走得**最久**的那头牛，不同的走法会导致不同的结果。于是，问题又变成了“是否存在一种方案，使得最大值最小”这种东东。于是，我们选择二分时间最小值，判断所有牛是否可以在该时间内到达雨棚。

那么，如何判断答案是否合法呢？所有牛的终点不确定，因此考虑网络流建模。不妨将牛和雨棚的容量分开看，一块农田拆成两个点。从超级源点 $S$ 连向第一波点，最大流量为该点牛的数量 $x$，保证这个点有 $x$ 头牛需要安置。对于第二波点，全部连向超级汇点 $T$, 流量为雨棚的容量，即保证从这个点的雨棚“出来”的牛不超过容量。

而对于牛和雨棚，我们将合法的连上一条为 $inf$的边，保证他们无限通过。何为合法的？当然就是在同一块农田的牛和雨棚， 和最短路距离不超过当前枚举答案的点啦！（确保最长时间不能超过当前答案）。

最后，我们跑一波最大流，如果最大流等于牛的数量，证明当前的方案合法，反之，如果最大流小于牛的数量，则证明在该时间内无法保证所有的牛可以找到雨棚。

参考代码（当前弧优化的普通 $Dicnic$ 版本）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define M 100010
#define N 1010
#define ll long long
const ll inf = (ll)1e18;  // 一定要够大 

template <class T>
inline void read(T& a){
	T x = 0, s = 1;
	char c = getchar();
	while(!isdigit(c)){
		if(c == '-') s = -1;
		c = getchar();
	}
	while(isdigit(c)){
		x = x * 10 + (c ^ '0');
		c = getchar();
	}
	a = x * s;
	return ;
}

struct node{
	int v, next;
	ll w;
	
	public:
		node(int v = 0, ll w = 0, int next = -1){  // 方便初始化为 -1 
			this -> v = v;
			this -> w = w;
			this -> next = next;
			return ;
		}
		
	inline void clean(){
		this -> v = 0;
		this -> w = 0;
		this -> next = -1;
		return ;
	}
		
}t[M << 1];
int f[N];
ll dis[N][N];
int n, m;
int suma = 0, sumb = 0;  // 奶牛总数和雨棚总容量 
int a[N], b[N];
int s, ht; // 起点和终点 

int bian = -1;
inline void add(int u, int v, ll w){
	t[++bian] = node(v, w, f[u]), f[u] = bian;
	t[++bian] = node(u, 0, f[v]), f[v] = bian;  // 反向虚边 
	return ;
}

struct Max_Flow{    // 最大流 
	int deth[N];
	int cur[N];    

	bool bfs(){
		queue <int> q;	
		memset(deth, 0, sizeof(deth));
		deth[s] = 1; 
		q.push(s);
		while(!q.empty()){
			int now = q.front(); q.pop();
			for(int i = f[now]; ~i; i = t[i].next){
				int v = t[i].v;
				if(!deth[v] && t[i].w){
					deth[v] = deth[now] + 1;
					q.push(v);
				}
			}
		}
		return deth[ht] != 0;
	}
	
	ll dfs(ll now,ll dist){
		if(now == ht || !dist)return dist;
		for(int& i = cur[now]; ~i; i = t[i].next){
			ll v = t[i].v;
			if(deth[v] == deth[now] + 1 && t[i].w != 0){
				ll di = dfs(v, min(dist, t[i].w));
				if(di > 0){
					t[i].w -= di;
					t[i^1].w += di;
					return di;
				}
			}
		}	
		return 0; 
	}
	
	ll Dicnic(){
		ll sum = 0;
		while(bfs()){
			memcpy(cur, f, sizeof(cur));
			while(ll temp = dfs(s, inf))
				sum += temp;		
		}
		return sum; 
	}
	
} T;

inline void clean(){
	memset(f, -1, sizeof(f));
	for(int i = 1; i <= bian; i++)
		t[i].clean();
	bian = -1;
	return ;
}

bool judge(ll mid, int sum){
	clean();                        // 记得清空 
	for(int i = 1; i <= n; i++){
		add(s, i, a[i]);
		add(i + n, ht, b[i]);
		for(int j = 1; j <= n; j++){
			if(i == j || dis[i][j] <= mid)   // 本身就在这块农田或者距离在当前限制之内 
				add(i, j + n, inf);
		}
	}
	return T.Dicnic() == sum;
}

int main(){
//	freopen("hh.txt", "r", stdin);
	read(n), read(m);
	for(int i = 1; i <= n; i++){
		read(a[i]), read(b[i]);
		suma += a[i], sumb += b[i];  // 牛的总数， 容量的总数 
	}
	if(suma > sumb){  // 特判，如果根本放不下就直接去世 
		printf("-1");
		return 0;  
	}
	
	s = n * 2 + 1, ht = n * 2 + 2;
	memset(dis, 0x3f, sizeof(dis));    
	for(int i = 1; i <= m; i++){
		ll x, y, w;
		read(x), read(y), read(w);
		dis[x][y] = dis[y][x] = min(dis[x][y], w);
	}
	for(int k = 1; k <= n; k++)    // Floyd 最短路 
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
				
	ll l = 0, r = 0;
	ll ans = -1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(i != j)  r = max(r, dis[i][j]);
			
	while(l <= r){      // 二分答案 
		ll mid = l + r >> 1;
		if(judge(mid, suma)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%lld\n", ans < inf ? ans : -1);
	return 0;
}```


（话说这真的只是一道绿题吗……）


---

## 作者：sane1981 (赞：1)

# 题目
**[P6768 [USACO05MAR]Ombrophobic Bovines](https://www.luogu.com.cn/problem/P6768)**
# 题目解读
本题大意为：每个点上有一些人和一些容纳人的房子，花最短时间使所有人走到房间，若无法满足，则输出 $-1$。

这道题目第一眼看过去不就是贪心加最短路吗，可是如果让一堆奶牛全部进入同一个房子，剩下的奶牛也许要绕很长的路走到另个房子，答案显然不是最优。

那这么办？RP++。

由于起点终点不确定，那么就先求**全源最短路**，毕竞所有道路都可以容纳任意多的奶牛，显然都走最短路好。观察数据  $F≤200,P≤1500$  用 Floyd   求是个不搓的选择。
#### 代码片花——Floyd
```cpp
void Floyd(){
	for(int k=1;k<=F;k++)
		for(int i=1;i<=F;i++)
			for(int j=1;j<=F;j++)
				G[i][j]=min(G[i][j],G[i][k]+G[k][j]);	
}
```


之后呢？？想一想求最小时间最常用的方法是什么？

当然是**二分答案法**

二分答案法要满足单调性，本题是满足的，因为求的时间相当于走到房子花费最大的人，因此二分出色的接近**常数的速度**完全可以胜任。
#### 代码片花——二分
```cpp
bool Check(long long tim){
	memset(head,0,sizeof(head));
	tot=1;
	for(int i=1;i<=F;i++) add(0,i,cow[i]);
	for(int i=1;i<=F;i++) add(i+F,2*F+1,house[i]);
	for(int i=1;i<=F;i++)
		for(int j=1;j<=F;j++)
			if(G[i][j]<=tim) add(i,j+F,INF); //建图
	return Dinic()>=sum1; //跑Dinic
}
-------------------------------------------
long long L=0,R=MAXINF,mid,ans;
while(L<=R){
	mid=L+R>>1;
//	cout<<mid<<endl;
	if(Check(mid)) ans=mid,R=mid-1;
	else L=mid+1;
}  //二分模板
```
照以上思路，我们在 $mid$ 的时间下只要判断是否可以都走到房间就行了，这时候构建一个新图，把最短路小于等于 $mid$ 的路径的两端点连起来，组成传说中的**二分图**，同时建立一个超级源点和超级汇点。跑一下最大流(初二蒟蒻不会 ISPA ,只会背 Dinic 模板)。
#### 代码片花——Dinic
```cpp
bool BFS(){
	for(int i=0;i<=2*F+1;i++) deep[i]=INF;
	queue <int> Q;
	Q.push(0);deep[0]=0;now[0]=head[0];
	while(!Q.empty()){
		int u=Q.front();Q.pop();
		for(int i=head[u];i;i=g[i].next){
			int v=g[i].to;
			if(g[i].capacity>0&&deep[v]==INF){
				deep[v]=deep[u]+1;
				now[v]=head[v];
				if(v==2*F+1) return true;
				Q.push(v);
			}
		}
	}
	return false;
}
int DFS(int u,int flow){
	if(u==2*F+1) return flow;
	int incf,res=0;
	for(int i=now[u];i&&flow;i=g[i].next){
		int v=g[i].to;
		now[u]=i;
		if(g[i].capacity>0&&deep[v]==deep[u]+1){
			incf=DFS(v,min(flow,g[i].capacity));
			if(incf==0) deep[v]=INF;
			g[i].capacity-=incf;
			g[i^1].capacity+=incf;
			flow-=incf;
			res+=incf;
		} 
	}
	return res;
}
int Dinic(){
	int maxflow=0;
	while(BFS()) maxflow+=DFS(0,INF);
	return maxflow; 
}
```
模板代码，没什么好说的。
# AC Code
```cpp
#include<bits/stdc++.h>
#include<queue>
using namespace std;
const int INF=1<<29;
const long long MAXINF=1e15;
int F,P,sum1,sum2;
int cow[205],house[205];
int a,b;
long long c;
long long G[205][205];
int head[405],tot=1;
struct edge{
	int next,to,capacity;
}g[2*405*405];
void add(int u,int v,int f){
	g[++tot]=(edge){head[u],v,f};
	head[u]=tot;
	g[++tot]=(edge){head[v],u,0};
	head[v]=tot;
}
void Floyd(){
	for(int k=1;k<=F;k++)
		for(int i=1;i<=F;i++)
			for(int j=1;j<=F;j++)
				G[i][j]=min(G[i][j],G[i][k]+G[k][j]);	
}
int now[405],deep[405];
bool BFS(){
	for(int i=0;i<=2*F+1;i++) deep[i]=INF;
	queue <int> Q;
	Q.push(0);deep[0]=0;now[0]=head[0];
	while(!Q.empty()){
		int u=Q.front();Q.pop();
		for(int i=head[u];i;i=g[i].next){
			int v=g[i].to;
			if(g[i].capacity>0&&deep[v]==INF){
				deep[v]=deep[u]+1;
				now[v]=head[v];
				if(v==2*F+1) return true;
				Q.push(v);
			}
		}
	}
	return false;
}
int DFS(int u,int flow){
	if(u==2*F+1) return flow;
	int incf,res=0;
	for(int i=now[u];i&&flow;i=g[i].next){
		int v=g[i].to;
		now[u]=i;
		if(g[i].capacity>0&&deep[v]==deep[u]+1){
			incf=DFS(v,min(flow,g[i].capacity));
			if(incf==0) deep[v]=INF;
			g[i].capacity-=incf;
			g[i^1].capacity+=incf;
			flow-=incf;
			res+=incf;
		} 
	}
	return res;
}
int Dinic(){
	int maxflow=0;
	while(BFS()) maxflow+=DFS(0,INF);
	return maxflow; 
}
bool Check(long long tim){
	memset(head,0,sizeof(head));
	tot=1;
	for(int i=1;i<=F;i++) add(0,i,cow[i]);
	for(int i=1;i<=F;i++) add(i+F,2*F+1,house[i]);
	for(int i=1;i<=F;i++)
		for(int j=1;j<=F;j++)
			if(G[i][j]<=tim) add(i,j+F,INF);
	return Dinic()>=sum1;
}
int main(){
	scanf("%d%d",&F,&P);
	for(int i=1;i<=F;i++)
		scanf("%d%d",&cow[i],&house[i]),sum1+=cow[i],sum2+=house[i];
	for(int i=1;i<=F;i++)
		for(int j=1;j<=F;j++)
			if(i==j) G[i][j]=0;
			else G[i][j]=MAXINF;
	for(int i=1;i<=P;i++){
		scanf("%d%d%lld",&a,&b,&c);
		G[a][b]=G[b][a]=min(G[a][b],c);
	}
	Floyd();
	long long L=0,R=MAXINF,mid,ans;
	while(L<=R){
		mid=L+R>>1;
//		cout<<mid<<endl;
		if(Check(mid)) ans=mid,R=mid-1;
		else L=mid+1;
	}
	if(ans!=0&&ans!=MAXINF) printf("%lld\n",ans);
	else printf("-1\n");
	return 0;
}
```
此题综合性比较强，有些难度，实在是一道好题（也许我太弱）。

---

## 作者：happybob (赞：1)

可以发现，牛如果想要去其他地点的雨棚，那么一定走最短路。

所以可以先 $O(n^3)$ 处理最短路，然后二分答案，将所有最短路 $\leq$ 当前二分的时间的边加入。

然后网络流判断可行性，即超级源点向每一块田地连一条容量为牛的个数的边，然后把田地和雨棚拆点，雨棚向超级汇点连容量为雨棚最多能放牛的个数的边。最后两点判断一次最短路，看是否可以加边。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstring>
#include <climits>
#include <queue>
using namespace std;

#define int long long

const int N = 5e6, INF = INT_MAX;

int dis[205][205], cow[N], rain[N], sum;

int n, p, T, S;
int e[N], h[N], c[N], ne[N], idx;

int cur[N], d[N];

void add(int x, int y, int z)
{
	e[idx] = y, ne[idx] = h[x], c[idx] = z, h[x] = idx++;
	e[idx] = x, ne[idx] = h[y], c[idx] = 0, h[y] = idx++;
}

void solve(int maxn)
{
	for (int i = 0; i <= T; i++) h[i] = -1;
	for (int i = 0; i <= idx; i++)
	{
		c[i] = ne[i] = e[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		add(S, i, cow[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		add(i + n, T, rain[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (dis[i][j] <= maxn)
			{
				add(i, j + n, INF);
				//add(j, i, INF);
				//printf("%lld %lld\n", i, j);
			}
		}
	}
}

bool bfs()
{
	for (int i = 0; i <= T; i++) d[i] = -1;
	queue<int> q;
	q.push(S);
	d[S] = 0;
	cur[S] = h[S];
	while (q.size())
	{
		int u = q.front();
		q.pop();
		for (int i = h[u]; ~i; i = ne[i])
		{
			int j = e[i];
			if (d[j] == -1 && c[i] > 0)
			{
				d[j] = d[u] + 1;
				cur[j] = h[j];
				if (j == T) return 1;
				q.push(j);
			}
		}
	}
	return 0;
}

int dfs(int u, int flow)
{
	if (u == T) return flow;
	int sum = 0;
	for (int i = cur[u]; ~i && sum < flow; i = ne[i])
	{
		int j = e[i];
		cur[u] = i;
		if (d[j] == d[u] + 1 && c[i] > 0)
		{
			int f = dfs(j, min(c[i], flow - sum));
			if (!f) d[j] = -1;
			else
			{
				sum += f;
				c[i] -= f;
				c[i ^ 1] += f;
			}
		}
	}
	return sum;
}

int dinic()
{
	int sum = 0, f;
	while (bfs())
	{
		while (f = dfs(S, INF))
		{
			sum += f;
		}
	}
	return sum;
}

bool check(int x)
{
	solve(x);
	return dinic() >= sum;
}

signed main()
{
	memset(dis, 0x3f, sizeof dis);
	scanf("%lld%lld", &n, &p);
	T = 2 * n + 1;
	for (int i = 1; i <= n; i++) scanf("%lld%lld", &cow[i], &rain[i]), dis[i][i] = 0, sum += cow[i];
	for (int i = 1; i <= p; i++)
	{
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		dis[u][v] = min(dis[u][v], w);
		dis[v][u] = min(dis[v][u], w);
	}
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	bool f = 0;
	int l = 0, r = INF * 100;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (check(mid)) r = mid - 1, f = 1;
		else l = mid + 1;
	}
	printf("%lld\n", f ? r + 1 : -1);
	return 0;
}
```


---

## 作者：MSqwq (赞：1)

前置芝士：最短路 $+$ 最大流 $+$ 二分答案    
题意：每个草地有雨棚也有若干头牛，我们已知所有的边和会通过这些边所需的时间，问什么时候所有牛都可以到雨棚里面  
看到这种题就直接看数据范围 $n \le 200$，这种东西就很自然的想到网络流啦，再读读题就可以发现是求最大流。  
发现所有牛去往其他草地的路线一定是最短路，所以先考虑最短路。这数据范围求最短路当然是用 $Floyd$ 了，~~但是 n 为 100 会炸~~ ，200当然是不会炸的啦。  
跑完最短路我们就要建立最大流的模型了，网络流的题难就难在建图，当然所有图论问题都是建图 $+$ 跑板子，所以应该在思维上锻炼自己抽象能力。  
好回到正题，怎么建图，如果你做过 [ [CQOI2015]网络吞吐量](https://www.luogu.com.cn/problem/P3171) 就知道本题要通过拆点的方式来构图，因为如果是两个点可以互相到达，而不能通过单纯的状态来表示传递流量，所以就要采用拆点的方式。  
（下文我把这个点本省称为本身点，拆的点称为拆点）  
现在就应该~~理所应当~~完成了以下几步：  
1. 起点和每一个点的本身点都应该有一条边，容量为牛的数量  
2. 每一个本身点都应该和自己相应的拆点有一条边，容量为正无穷  
3. 每一个拆点和终点都应该有一条边，容量为雨棚的数量  

好这样你就完成一半了  
接下来考虑每个点之间该如何连边，因为牛要按照最短的路径走向其他的草地，而此题问的是最少的时间，这个时候你就可以发现如果我们把所有边都连起来就不能限制最小的时间，所以考虑二分答案，二分最少的时间，然后再考虑连边，这样就可以想到是吧小于等于二分的时间的那些边连起来，然后再跑最大流就可以啦qwq  
回顾一下本题的解题思路啊：  
看到最小，所以想到最短路，因为边很少想到 $Floyd$，因为牛要去往其他的某个点类似于那个流水问题，所以想到最大流，然后再想到边如果全部取不能得到最小，所以采用二分答案  
好啦这就是本题的解决方案，有啥问题或者不懂的欢迎来问我呀qwq  
接下来是代码：  
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#define ll long long
using namespace std;
const int N=4010,M=2000010,K=300;
struct MSQWQ{
	int to,next;
	ll z;
}e[M];
int elast[N],cur[N],k=1;
void print(int x,int y,int z){cout<<x<<"->"<<y<<"="<<z<<endl;}
void add(int x,int y,ll z)
{
	//print(x,y,z);
	e[++k].to=y,e[k].z=z,e[k].next=elast[x],elast[x]=k;
	e[++k].to=x,e[k].z=0,e[k].next=elast[y],elast[y]=k;
}

int n,m;
ll w[N],v[N];
ll ddis[K][K];
ll ans;
int st,en;
queue<int>q;
ll dis[N],cnt[N];


void bfs(int en)
{
	q.push(en);
	for(int i=0;i<=N-10;i++)cur[i]=elast[i],dis[i]=-1,cnt[i]=0;
	dis[en]=0;
	cnt[0]=1;
	while(!q.empty())
	{
		int now=q.front();q.pop();
		for(int i=elast[now];i;i=e[i].next)
		{
			int to=e[i].to;
			if(dis[to]==-1)
			{
				dis[to]=dis[now]+1;
				//cout<<to<<" "<<dis[to]<<endl;
				cnt[dis[to]]++;
				q.push(to);
			}
		}
	}
}
ll dfs(int x,ll flow)
{
	if(x==en)return flow;
	ll d=0;
	for(int i=cur[x];i;i=e[i].next)
	{
		cur[x]=i;
		int to=e[i].to;
		if(e[i].z>0&&dis[x]==dis[to]+1)
		{
			int tmp=dfs(to,min(e[i].z,flow-d));
			e[i].z-=tmp;
			e[i^1].z+=tmp;
			d+=tmp;
			if(d==flow||dis[st]>=n*2+1)return d;
		}
	}
	if(dis[st]>=n*2+1)return d;
	cnt[dis[x]]--;
	if(cnt[dis[x]]==0)dis[st]=n*2+1;
	dis[x]++;
	cur[x]=elast[x];
	cnt[dis[x]]++;
	return d;
}

ll L,R,mid,qans;
ll sum;
bool check(ll mid)
{
	k=1;
	memset(elast,0,sizeof(elast));
	
	for(int i=1;i<=n;i++)add(st,i,w[i]);
	for(int i=1;i<=n;i++)add(i,i+n,1e18);

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(ddis[i][j]<=mid)add(i,j+n,1e18);
	
	for(int i=1;i<=n;i++)
		add(i+n,en,v[i]);
	
	ans=0;
	bfs(en);
	while(dis[st]<n*2+1)ans+=dfs(st,1e18);
	
	if(ans==sum)return true;
	return false;
}

int main()
{
	scanf("%d%d",&n,&m);
	st=0,en=n*2+1;
	for(int i=1;i<=n;i++)scanf("%lld%lld",&w[i],&v[i]),sum+=w[i];
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)ddis[i][j]=1e18;
	
	for(int i=1;i<=m;i++)
	{
		int x,y;
		ll z;
		scanf("%d%d%lld",&x,&y,&z);
		ddis[x][y]=min(ddis[x][y],z);
		ddis[y][x]=min(ddis[y][x],z);
	}
	
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				ddis[i][j]=min(ddis[i][j],ddis[i][k]+ddis[k][j]);
				
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=n;j++)cout<<ddis[i][j]<<" ";
//		cout<<endl;
//	}
	
	L=0,R=1e18+1;
	while(L<=R)
	{
		mid=(L+R)/2;
		if(check(mid))qans=mid,R=mid-1;
		else L=mid+1;
	}
	if(qans==0||qans==1e18+1)printf("-1");
	else printf("%lld",qans);
}
```


---

## 作者：JK_LOVER (赞：1)

## 题意
给你 $n$ 个点， $m$ 条边。使所有的牛都可以到达牛棚，求问最小时间。[$QWQ$](https://www.luogu.com.cn/blog/xzc/solution-p6768)
## 分析
先考虑每一头牛都可以独立行动。那么其实是求最后一头牛进入牛棚的时间。那么每一个点的牛棚个数有限，这个就限制了容量。就是一个网络流模型了。每个点要拆成入点和出点，那么现在就是求最大时间最小。这个可以二分来做。二分最大时间，对于每个时间暴力重构图。如果两个点是距离小于或等于最大时间，就可以连一条容量为 $\inf$ 的边。跑一次网络流，查询是否满流就行了。

- 细节：这道题有重边，取最小计算就行。
##

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N = 603100;

int S,T,n,m;
struct Edge{int cap,flow,to,nxt;}e[N];
int in[N],cur[N],out[N],Maxflow = 0,dis[N],head[N],cnt = 1,dist[2100][2100];
void add(int x,int y,int cap)
{
	e[++cnt].cap = cap;e[cnt].flow = 0;e[cnt].nxt = head[x];e[cnt].to = y;head[x] = cnt;
	e[++cnt].cap = 0  ;e[cnt].flow = 0;e[cnt].nxt = head[y];e[cnt].to = x;head[y] = cnt;
}
queue<int> Q;
bool Bfs(int s,int t)
{
	while(Q.size()) Q.pop();
	memset(dis,0,sizeof(dis));
	dis[s] = 1;Q.push(s);
	while(Q.size()){
		int x = Q.front();Q.pop();
		for(int i = head[x];i;i=e[i].nxt){
			if(e[i].cap>e[i].flow && !dis[e[i].to]){
				dis[e[i].to] = dis[x]+1;Q.push(e[i].to);
				if(e[i].to==t) return true;
			}
		}
	}
	return false;
}
int Dfs(int x,int a,int t){
	if(x==t||a==0) return a;
	int f,flow = 0;
	for(int i = cur[x];i;i=e[i].nxt){
		int y = e[i].to;
		if(dis[y] == dis[x]+1 && (f=Dfs(y,min(a,e[i].cap-e[i].flow),t))>0)
		{
			flow+=f;a-=f;e[i].flow+=f;e[i^1].flow-=f;cur[x]=i;
			if(!a) break;
		}
	}
	return flow;
}
void rebuild(int limit){
	memset(head,0,sizeof(head));cnt = 1;
	for(int i = 1;i <= n;i++) add(S,i,in[i]),add(i+n,T,out[i]),add(i,i+n,0x3f3f3f3f);
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n;j++){
			if(dist[i][j] <= limit) add(i,j+n,0x3f3f3f3f);
		}
	}
}
signed main()
{
	cin >> n >> m;
	memset(dist,0x3f,sizeof(dist));
	for(int i = 1;i <= n;i++) cin >> in[i] >> out[i],Maxflow += in[i];
	for(int i = 1;i <= m;i++) {
		int a,b,c;cin >> a >> b >> c;
		dist[a][b] = dist[b][a] = min(dist[a][b],c);
	}
	int Max = 0;
	for(int k = 1;k <= n;k++){
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= n;j++){
				dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
			}
		}
	}
	S = 0;T = 2*n + 1;
	int ans = 0x3f3f3f3f3f3f3f3f,L = 0,R = 0x3f3f3f3f3f3f3f3f;
	while(L <= R){
		int Mid = L + R >> 1;
		rebuild(Mid);
		int maxflow = 0;
		while(Bfs(S,T)){
			for(int i = 0;i <= T;i++) cur[i] = head[i];
			maxflow += Dfs(S,0x3f3f3f3f,T);
		}
		if(maxflow >= Maxflow) R = Mid - 1,ans = min(ans,Mid);
		else L = Mid + 1;
	}
	if(ans == 0x3f3f3f3f3f3f3f3f) cout<<"-1"<<endl;
	else cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：splendore (赞：0)

看到题目中的 $n\le 200$，就知道可以考虑某些图论算法。

但不是费用流，别像我一样想歪了。

又看到题目隐含着需要一个最短路，那直接写一手 Floyd，然后看到题目要求最小值，想到二分答案应该比较好解决，然后发现 $check()$ 函数不太好写，题目里要维护的东西比较杂，但再回望一下 $n\le 200$，于是掏出 Dinic 写最大流。

具体上，每次 $check()$ 需要重新建图。

设当前二分到的时间为 $mid$，就将每对距离小于 $mid$ 的田地与雨棚连边，容量为 $inf$。从源点向每个田地建一条容量为牛的数量的边。然后从每个雨棚向汇点连一条容量为雨棚容量的边即可。

建完图跑一边最大流，如果最大流大于等于总流量返回真，否则返回假。

代码略长。
```
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
typedef long long LL;
const int N=405,M=N*N*4+N*4+5;
const LL inf=0x3f3f3f3f3f3f3f3f;
struct edge{int y;LL f;int pre;}e[M];int elen=1,last[N];
void ins(int x,int y,LL f){
	e[++elen]={y,f,last[x]};last[x]=elen;
	e[++elen]={x,0,last[y]};last[y]=elen;
}
int n,m;
LL sum=0;
int h[N],cur[N],st,ed;
bool v[N];
bool bh(){
	memset(h,0,sizeof(h));h[st]=1;
	memset(v,0,sizeof(v));v[st]=1;
	queue<int>q;q.push(st);
	while(!q.empty()){
		int x=q.front();q.pop();
		v[x]=0;
		for(int k=last[x];k;k=e[k].pre){
			int y=e[k].y;
			if(e[k].f&&!h[y]){
				h[y]=h[x]+1;
				if(!v[y]){
					v[y]=1;
					q.push(y);
				}
			}
		}
	}
	return h[ed];
}
LL dfs(int x,LL f){
	if(x==ed)return f;
	LL sx=0;
	for(int k=cur[x];k;k=e[k].pre){
		cur[x]=k;
		int y=e[k].y;
		if(e[k].f&&h[y]==h[x]+1&&sx<f){
			LL sy=dfs(y,min(e[k].f,f-sx));
			e[k].f-=sy;e[k^1].f+=sy;sx+=sy;
			if(sx==f)return f;
		}
	}
	return sx;
}
LL g[N][N];
int a[N],b[N];
bool check(LL mid){
	elen=1;
	memset(last,0,sizeof(last));
	for(int i=1;i<=n;++i){
		ins(st,i,a[i]);
		ins(i+n,ed,b[i]);
		for(int j=1;j<=n;++j)
			if(i==j||g[i][j]<=mid)
				ins(i,j+n,inf);
	}
	LL mxf=0;
	while(bh()){
		memcpy(cur,last,sizeof(cur));
		mxf+=dfs(st,inf);
	}
	return mxf>=sum;
}
int main(){
	scanf("%d%d",&n,&m);
	st=0;ed=n*2+1;
	for(int i=1;i<=n;++i){
		scanf("%d%d",&a[i],&b[i]);
		sum+=a[i];
	}
	memset(g,0x3f,sizeof(g));
	for(int i=1,x,y;i<=m;++i){
		LL c;
		scanf("%d%d%lld",&x,&y,&c);
		g[x][y]=g[y][x]=min(g[x][y],c);
	}
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
	LL l=0,r=inf-1,ans=0;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%lld\n",ans?ans:-1);
	return 0;
}
```

---

## 作者：zzzyyyyhhhhh (赞：0)

首先，问题可以转换为最短路径问题和最大流问题的结合。每个田地的牛数和雨棚的容量决定了牛的转移难度，而田地之间的路径和通过时间决定了牛可以在多短的时间内到达其他田地。在给定的时间限制下，我们要判断是否能够将所有牛分配到合适的雨棚中。

第一步是利用 Floyd 求解每两个田地之间的最短路径，接下来，我们要使用二分法来猜测最小的时间。在每次二分过程中，我们猜测一个时间值，判断在该时间范围内是否可以完成所有牛的转移。

为了实现这一点，我们需要将问题转化为最大流模型来进行判断。最大流模型的构建过程如下：每块田地上的牛可以看作源点，雨棚可以看作汇点，连接源点和汇点的边表示田地上的牛和雨棚的容量限制。在二分的时间范围内，若两块田地之间的最短路径小于或等于当前猜测的时间，我们就在图中为它们建立一条容量为无穷的边，表示牛可以在这个时间内从一块田地移动到另一块田地的雨棚。

当所有田地和雨棚都连接好后，我们使用最大流来检查当前流量是否等于田地上牛的总数。如果流量达到牛的总数，说明在当前时间内可以完成牛的转移，否则需要继续调整时间范围进行二分。

如果没有找到合适的时间范围，说明无法将牛们在规定的时间内转移到雨棚中，输出`-1`。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5418;
int n,m;

namespace flow
{
	int s,t;
	vector<int> a[4*N];
	struct node
	{
		int t, w, extra;
	} edge[N*100];
	int cnt=1;
	int dis[4*N];
	int ans;
	int ansedge;
	int toed[N*100];
	int to[N*100];
	bool bfs()
	{
		queue<int> q;
		bitset<N> v;
		int tmp;
		v.reset();
		q.push(s);
		v[s] = 1;
		dis[s] = 1 << 30;
		while(!q.empty())
		{
			tmp = q.front();
			// cout << tmp << '\n';
			q.pop();
			for (int i = 0; i < a[tmp].size();i++)
			{
				if (v[edge[a[tmp][i]].t] || edge[a[tmp][i]].extra == 0)
					continue;
				// cout << tmp << ' ' << edge[a[tmp][i]].t << ' ' << edge[a[tmp][i]].extra << '\n';
				v[edge[a[tmp][i]].t] = 1;
				dis[edge[a[tmp][i]].t] = min(dis[tmp], edge[a[tmp][i]].extra);
				toed[edge[a[tmp][i]].t] = tmp;
				to[edge[a[tmp][i]].t] = a[tmp][i];
				if (edge[a[tmp][i]].t == t)
					return 1;
				q.push(edge[a[tmp][i]].t);
			}
		}
		return 0;
	}
	void work()
	{
		int tmp, ex, ed;
		while (bfs())
		{
			tmp = t, ex = dis[t];
			// cout << ans << ' ' << ex << '\n';
			while (1)
			{
				ed = to[tmp];
				tmp = toed[tmp];
				edge[ed].extra -= ex;
				edge[ed ^ 1].extra += ex;
				if(tmp==s)
					break;
			}
			ans += ex;
		}
	}
	void clear()
	{
		for(int i=1;i<=n*3+1;i++)
		{
			a[i].clear();
			dis[i]=0;
		}
		ansedge=0;
		cnt=1;
		ans=0;
	}
	void add(int x,int y,int z)
	{
		// cout<<x<<' '<<y<<' '<<z<<'\n';
		edge[++cnt] = {y, z, z};
		a[x].push_back(cnt);
		edge[++cnt] = {x, z, 0};
		a[y].push_back(cnt);
		// cout<<"ok";
	}
}
namespace mindist
{
	struct edge
	{
		int t,w;
	};
	vector<edge> a[N];
	struct node
	{
		int x,dis;
	};
	int dist[N];
	bool operator<(node x,node y)
	{
		return x.dis>y.dis;
	}
	priority_queue<node> q;
	void add(int x)
	{
		for(auto i:a[x])
		{
			if(dist[i.t]>dist[x]+i.w)
			{
				dist[i.t]=dist[x]+i.w;
				q.push({i.t,dist[i.t]});
			}
		}
	}
	void add(int x,int y,int w)
	{
		a[x].push_back({y,w});
	}
	void work(vector<int> ss,vector<int> ww)
	{
		memset(dist,0x3f,sizeof dist);
		for(int i=0;i<(int)ss.size();i++)
		{
			dist[ss[i]]=ww[i];
			q.push({ss[i],dist[ss[i]]});
		}
		int x,y;
		while(!q.empty())
		{
			x=q.top().x,y=q.top().dis;
			q.pop();
			if(dist[x]==y)add(x);
		}
	}
}int mew[N],lim[N];
int d[N][N];
int sum;
bool check(int x)
{
	flow::clear();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(d[i][j]<=x)
			{
				flow::add(i+n,j+1+2*n,10000);
			}
		}
	}
	flow::s=1,flow::t=5*n;
	for(int i=1;i<=n;i++)
	{
		flow::add(flow::s,i+n,mew[i]);
		flow::add(i+1+2*n,flow::t,lim[i]);
	}
	flow::work();
	// cout<<x<<' '<<flow::ans<<' '<<sum<<'\n';
	return flow::ans==sum;
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>mew[i]>>lim[i];
		sum+=mew[i];
	}
	int x,y,z;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			d[i][j]=1e18+1;
		}
	}
	for(int i=1;i<=n;i++)d[i][i]=0;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y>>z;
		d[x][y]=d[y][x]=min(d[x][y],z);
	}
	for(int mid=1;mid<=n;mid++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int i=1;i<=n;i++)
			{
				d[i][j]=min(d[i][j],d[i][mid]+d[mid][j]);
			}
		}
	}
	for(int j=1;j<=n;j++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int mid=1;mid<=n;mid++)
			{
				d[i][j]=min(d[i][j],d[i][mid]+d[mid][j]);
			}
		}
	}
	// for(int i=1;i<=n;i++)
	// {
	// 	for(int j=1;j<=n;j++)
	// 	{
	// 		cout<<i<<' '<<j<<' '<<d[i][j]<<'\n';
	// 	}
	// }
	// cout<<d[1][n]<<'\n';
	int l=0,r=1e17,mid,ans=998244353;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	if(ans!=998244353)cout<<ans;
	else cout<<-1;
}
```

---

## 作者：Lvlinxi2010 (赞：0)

### 题目思路
题意可转化为求最慢进入雨棚的的牛进入雨棚的最短时间，发现答案具有单调性，考虑二分。

设当前检验的时间为 $x$，我们将源点和田地（编号 $1 \dots n$）连边，容量为田地上牛的数量，汇点和雨棚（编号 $n+1 \dots 2n$）连边，容量为雨棚的容量。

我们可以用 Floyd 预处理出两点之间的最短路，若 $(i,j)$ 的最短路长度小于 $x$，在图上建一条 $i$ 到 $j+n$ 的边，容量为正无穷。

在图上跑一遍最大流，若最大流等于牛的数量的总和，则 $x$ 是一个可行的时间。

tips：一定不要像我一样边的数组只开 4000，不然你会喜提 TLE on test #4。

附上代码：

```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(ll i=(a);i<=(b);i++)
#define FR(i,a,b) for(ll i=(a);i>=(b);i--)
#define ll long long
using namespace std;
const ll MAXN = 2e2 + 10;
const ll MR = 5e4 + 10;
const ll inf = 2e9;
ll n,m,s,t,sum=0;
ll a[MAXN],b[MAXN],d[MAXN][MAXN];
ll head[MAXN<<1],now[MAXN<<1],tot=1;
ll dis[MAXN<<1];
inline int read(){
	int x=0,y=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') y=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x*y;
}
struct edge{
	ll v,w,nxt;
}e[MR<<1];
void add_edge(ll u,ll v,ll w){
	e[++tot].v=v;
	e[tot].w=w;
	e[tot].nxt=head[u];
	head[u]=tot;
}

bool bfs(){
	FL(i,0,t) dis[i]=inf;
	queue<ll> q;
	q.push(s);
	dis[s]=0;
	now[s]=head[s];
	while(!q.empty()){
		ll x=q.front();
		q.pop();
		for(ll i=head[x];i!=-1;i=e[i].nxt){
			ll v=e[i].v;
			if(e[i].w>0&&dis[v]==inf){
				q.push(v);
				now[v]=head[v];
				dis[v]=dis[x]+1;
				if(v==t) return 1;
			}
		}
	}
	return 0;
}

ll dfs(ll x,ll sum){
	if(x==t) return sum;
	ll k,res=0;
	for(ll i=now[x];i!=-1&&sum;i=e[i].nxt){
		now[x]=i;
		ll v=e[i].v;
		if(e[i].w>0&&(dis[v]==dis[x]+1)){
			k=dfs(v,min(sum,e[i].w));
			if(k==0) dis[v]=inf;
			e[i].w-=k;
			e[i^1].w+=k;
			res+=k;
			sum-=k;
		}
	}
	return res;
}
bool check(ll x){
	//printf("check %lld\n",x);
	for(register int i=0;i<=t;i++) head[i]=-1;
	tot=1;
	for(register int i=1;i<=n;i++){
		add_edge(s,i,a[i]);
		add_edge(i,s,0);
		add_edge(i+n,t,b[i]);
		add_edge(t,i+n,0);
		for(register int j=1;j<=n;j++){
			//printf("dis[%lld][%lld]=%lld\n",i,j,d[i][j]);
			if(d[i][j]<=x){
				add_edge(i,j+n,inf);
				add_edge(j+n,i,0);
			}
		}
	}
	ll res=0;
	while(bfs()){
		//puts("work");
		res+=dfs(s,inf);
	}
	return (res>=sum);
} 
signed main(){
	n=read();
	m=read();
	s=0,t=2*n+1;
	memset(d,0x3f,sizeof(d));
	for(register int i=1;i<=n;i++) a[i]=read(),b[i]=read(),d[i][i]=0,sum+=a[i];
	for(register int i=1;i<=m;i++){
		ll u,v,w;
		u=read(),v=read(),w=read();
		d[u][v]=min(d[u][v],w);
		d[v][u]=min(d[v][u],w);
	}
	for(register int k=1;k<=n;k++){
		for(register int i=1;i<=n;i++){
			for(register int j=1;j<=n;j++) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
		}
	}
	ll l=0,r=2e11,ans=-1;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",ans);
}
```

---

## 作者：LJ07 (赞：0)

## 题目描述
[题目传送门](https://www.luogu.com.cn/problem/P6768)

## 思路简述
题目求的是每头牛进入雨棚**最大时间的最小值**，容易想到是二分答案。

先使用 Floyd 预处理每两个田地之间的距离（铺垫）。

每次二分时间的最大值，并使用网络流 check。

容易想到将每个田地拆成两个点：牛和雨棚。

建一个超级源点和一个超级汇点。从超级源点起，向每个“牛”节点连一条容量为牛的数量的边，向每个“雨棚”节点连一条容量为雨棚所能容纳的最多牛数的边。

如果两个田地能够在限制时间内互达（照应），那么就分别从这两个田地的“牛”节点向彼此“雨棚”节点连一条容量为无穷大的边。

最后跑一遍网络流，check 最大流是否等于牛的总数。

**温馨提示：本题的二分边界和最短路的边界要开大。**

## 丑陋の代码
[click here](https://www.luogu.com.cn/paste/x8ub5eww)

---

## 作者：天南地北 (赞：0)

大意：让每只奶牛都能进入雨棚的最小时间

最容易想到的就是跑$Floyd$+贪心，$Floyd$用来计算两点之间的最短时间，但是这里有一个问题，如何分配奶牛进入雨棚？

这就是本题最难的地方——跑网络流$Dinic$

既然要分配奶牛进入雨棚，我们可以考虑用构图跑网络流来分配。

那么我们如何构图呢，这里面哪个是超级源点$S$，超级源点$T$？

首先每头奶牛都会从自己当前的牛棚出发，所以我们可以先将超级源点$S$连向每一个牛棚。对应的，这里的每一条边是当前牛棚的奶牛数量。

接着每头奶牛都可能到达别的雨棚，又或者不动，留在当前它的雨棚，所以呢我们就可以将雨棚拆成两个点，我们在这里称之为，雨棚起点，雨棚终点。

当然，不是每个雨棚都能到达每一个雨棚，所以呢，当两个点之间通过的时间小于一个特定值（后面会提），我们才连边，当然这条边的容量是无限的（每条路通过容量的限制是无限的），就设置为$inf$

最后将每一个雨棚终点连向超级源点$T$，每条边的容量设置为每个田地的雨棚总数。

画图理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/t3ite5iq.png)

上面的$cow[i]$是第$i$个田地上的奶牛总数，$len[i]$是第$i$个田地上的雨棚总数。

当然了，我们刚才提到的特定值又是什么呢？

这个特定值需要——二分答案，通过二分答案时间，再通过每一次$mid$值作为特定值，接着构图（就是刚才上述的构图）跑$Dinic$，然后判断最大流是否超过或等于所有奶牛的总数。

成立就说明，在少于$mid$的时间内，可以分配所有的奶牛到达雨棚，最后左右指针左右移动，缩小区间就出答案即可。

所以本题的思路（知识点）为：最短路$Floyd$+二分答案+网络流

参考程序
```cpp
#include<bits/stdc++.h>
#define int long long 
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=603100;
int S,T,n,m;
struct Edge
{
	int cap,flow,to,nxt;
}e[N];
int in[N],nhead[N],out[N];
int Maxflow=0;
int dis[N],head[N],cur=1;
int dp[2100][2100];
void Add_edge(int x,int y,int cap)
{
	e[++cur].cap=cap;
	e[cur].flow=0;
	e[cur].nxt=head[x];
	e[cur].to=y;
	head[x]=cur;
	
	e[++cur].cap=0;
	e[cur].flow=0;
	e[cur].nxt=head[y];
	e[cur].to=x;
	head[y]=cur;
}
queue<int>Q;
bool Bfs(int s,int t)
{
	while(Q.size()) Q.pop();
	memset(dis,0,sizeof(dis));
	dis[s]=1;Q.push(s);
	while(Q.size())
	{
		int x=Q.front();Q.pop();
		for(int i=head[x];i;i=e[i].nxt)
			if(e[i].cap>e[i].flow && !dis[e[i].to])
			{
				dis[e[i].to] = dis[x]+1;Q.push(e[i].to);
				if(e[i].to==t) return true;
			}
	}
	return false;
}
int Dfs(int x,int a,int t)
{
	if(x==t||a==0) return a;
	int f,flow=0;
	for(int i=nhead[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(dis[y]==dis[x]+1&&(f=Dfs(y,min(a,e[i].cap-e[i].flow),t))>0)
		{
			flow+=f;a-=f;e[i].flow+=f;e[i^1].flow-=f;nhead[x]=i;
			if(!a)break;
		}
	}
	return flow;
}
void rebuild(int limit)
{
	memset(head,0,sizeof(head));cur=1;
	rep(i,1,n)
		Add_edge(S,i,in[i]),Add_edge(i+n,T,out[i]),Add_edge(i,i+n,0x3f3f3f3f);
	rep(i,1,n)
		rep(j,1,n)
			if(dp[i][j]<=limit)Add_edge(i,j+n,0x3f3f3f3f);
}
signed main()
{
	cin>>n>>m;
	memset(dp,0x3f,sizeof(dp));
	rep(i,1,n)
		cin>>in[i]>>out[i],Maxflow+=in[i];
	rep(i,1,m)
	{
		int x,y,z;
		cin>>x>>y>>z;
		dp[x][y]=dp[y][x]=min(dp[x][y],z);
	}
	int Max=0;
	rep(k,1,n)
		rep(i,1,n)
			rep(j,1,n)
				dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
	S=0;T=2*n+1;
	int ans=0x3f3f3f3f3f3f3f3f,low=0,high=0x3f3f3f3f3f3f3f3f;
	while(low<=high)
	{
		int Mid=(low+high)>>1;
		rebuild(Mid);
		int maxflow=0;
		while(Bfs(S,T))
		{
			for(int i=0;i<=T;i++)nhead[i]=head[i];
			maxflow+=Dfs(S,0x3f3f3f3f,T);
		}
		if(maxflow>=Maxflow)high=Mid-1,ans=min(ans,Mid);
		else low=Mid+1;
	}
	if(ans==0x3f3f3f3f3f3f3f3f)cout<<"-1"<<endl;
	else cout<<ans<<endl;
	return 0;
} 
```
本题建议加上标签：最短路$Floyd$，二分答案，网络流


---

## 作者：Erica_N_Contina (赞：0)

### 大意

一副无向图中有 $n$ 个点，晴天时第 $i$ 个点上有 $p_i$ 个人，在下雨天时第 $i$ 个点上可以容纳 $w_i$ 个人，求开始下雨时如何调配使得所有人走到路的用时和最小。路 $i$ 的用时记为 $t_i$。

### 思路

先分析题目，题目要求最小时间，所以肯定符合二分答案（**二分用时**）的性质。先拆点，把每个点 $i$ 拆成 $u_i,v_i$，代表 $p_i$ 和 $w_i$，对于每次二分到的时间，如果某两点之间可以在这个时间内到达（**最短路**求出），则建起一条无限流量的边。然后建一个超级源点，到每个 $u_i$ 建一条边权为 $p_i$ 的数量的边，最后建一个超级汇点，每个 $v_i$ 连一条边权为 $w_i$ 的边到汇点。

**二分设计**

被二分的值：用时和。

边界：$l$ 为 $0$，$r$ 为所有 $t_i$ 之和（当然取 $INF$ 问题也不大）。

`judge()` 函数：每次跑一下最大流，判定流量是否大于总牛量。

**最短路**

多源最短路（Floyd 全源最短路即可，神仙们写 Johnson 应该也行）。区别于网络流，我们需要建另外一幅图，用来跑最短路。

**最大流**

dinic 算法。重点在建图上：

1. 把每个点 $i$ 拆成 $u_i,v_i$（这样就会有 $2\times n$ 个点了），代表 $p_i$ 和 $w_i$，对于每次二分到的时间，如果某两点之间可以在这个时间内到达（**最短路**求出），则建起一条无限流量的边。

2. 建一个超级源点 $S$，到每个 $u_i$ 连一条边权为 $p_i$ 的边。

3. 建一个超级汇点 $T$，每个 $v_i$ 连一条边权为 $w_i$ 的边到汇点。

为了方便，我们把 $S,T$ 分别设置在点 $2\times n,2\times n+1$ 上。



### 代码详解

**输入**

```C++

signed main(){
	scanf("%d%d",&n,&m);
	S=2*n+1,T=2*n+2;
	for(int i=1;i<=n;++i){
		scanf("%d%d",&cow[i],&house[i]);
		sum+=(ll)cow[i];//记录牛的总数
	}
	
	//弗洛伊德初始化
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			dis[i][j]=INF;
	for(int i=1;i<=n;++i)
		dis[i][i]=0;
		
	//加边
	for(int i=1;i<=m;++i){
		int u,to,w;
		scanf("%d%d%d",&u,&to,&w);
		dis[u][to]=min(dis[u][to],w);//注意两个点之间可能有多条路
		dis[to][u]=min(dis[to][u],w);
	}
}
```


**最短路**

最短路我们只需要求一次即可，就像预处理一样。所以我们先写最短路。

```C++
void flyd(){
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}
```


**二分**

```C++
	ll l=0,r=INF;
	while(l<=r)	{
		ll mid=(l+r)>>1;
		if(judge(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
```


**判定函数**

```C++

void init(){
	memset(h,0,sizeof h);
  	memset(cur,0,sizeof cur);
	for(int i=1;i<=N-2;i++){
		memset(&e[i],0,sizeof(struct edge));
	}
	idx=1;
}

bool judge(int mid){
	init();//注意这里要多次建网络流跑dinic,所以需要init(清空旧的网络流图)
	for (int i = 1; i <= n; ++i){
		add(S, i, cow[i]);//建网络流图
		add(i, S, 0);//建反向图
		add(i + n, T, house[i]);
		add(T,i + n, 0);
		for (int j = 1; j <= n; ++j){
			if (i == j || dis[i][j] <= mid){//如果某两点之间可以在这个时间内到达（最短路求出），则建起一条无限流量的边
				add(i, j + n, INF);
                add(j + n, i, 0);
            }
		}
	}
	ll ans = dinic();
//	printf("%lld\n", F);
	return (ans >= sum);
} 
```


**dinic**

最大流板子，巴巴多斯（不必多说）。

```C++
struct edge{
	int to,nxt,c;
}e[N];
void add(int x,int y,int b){
	e[++idx]={y,h[x],b};
	h[x]=idx;
}

//...

bool bfs(){//对每个点进行分层 ,为dfs找增广路做准备 
	memset(d,0,sizeof d);
	queue<int>q;
	q.push(s);d[s]=1;//源点是第一层 
	while(q.size()){
		int u=q.front();q.pop();
		for(int i=h[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!d[v]&&e[i].c){//如果没有访问过v并且这条边有剩余容量 
				d[v]=d[u]+1;//v点位于u的下一层 
				q.push(v) ;
				if(v==t)return 1;
			}
		}
	}
	return 0;
} 
int dfs(int u,int mf){//当前点u,(这条路径上)走到u时的剩余流量 
 
	 if(u==t)return mf;//如果已经到达汇点,直接返回
	 int sum=0;//计算u点可以流出的流量之和 (e.g.当u=2时,最后sum=3+3+4+2+3)
	 
	 for(int i=cur[u];i;i=e[i].nxt){
	 	cur[u]=i;//记录从哪一条边走出去了 ,后面有用 
	 	int v=e[i].to;
	 	
	 	if(d[v]==d[u]+1&&e[i].c){//如果v在u的下一层 并且有剩余容量 
	 		int f=dfs(v,min(mf,e[i].c));//正如EK中的'mf[v]=min(mf[u],e[i].c);' 
		 	//回
			e[i].c-=f;
			e[i^1].c+=f;//更新残留网,对照EK 
			sum+=f;
			mf-=f;//类似八皇后,请思考! 
			if(!mf)break;//优化.当在u的前几条分支已经流光了u的可用流量时,就不用考虑剩下的分支了 
		 }
	 } 
	 if(!sum)d[u]=0;//残枝优化.目前这条路没有可行流了 
	 return sum;
}
int dinic(){//累加答案 
	int ans=0;
	while(bfs()){//可以找到增光路 
		memcpy(cur,h,sizeof h);//请思考! 
		ans+=dfs(s,1e9);//还是那句话'//源点的流量上限为无穷大,即源点能为后面提供无限大的流量' 
	}
	return ans;
} 
```


**总代码**

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define ll long long
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=4e3+5;
const int M=4e6+5;
const int MOD=903250223;
const int INF=1e18;
//变量
int n,a,b,c,x[N],y[N],ans,res,tmp,cnt,dis[N][N];
int idx,h[N],d[N],cur[N],cow[N],S,T,house[N],sum,m;

struct edge{
	int to,nxt,c;
}e[M];

void add(int x,int y,int b){
	e[++idx]={y,h[x],b};
	h[x]=idx;
}

bool bfs(){//对每个点进行分层 ,为dfs找增广路做准备 
	memset(d,0,sizeof d);
	queue<int>q;
	q.push(S);d[S]=1;//源点是第一层 
	while(q.size()){
		int u=q.front();q.pop();
		for(int i=h[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!d[v]&&e[i].c){//如果没有访问过v并且这条边有剩余容量 
				d[v]=d[u]+1;//v点位于u的下一层 
				q.push(v) ;
				if(v==T)return 1;
			}
		}
	}
	return 0;
} 

int dfs(int u,int mf){//当前点u,(这条路径上)走到u时的剩余流量 
//	memset(d,0,sizeof d);//..
	
	 if(u==T)return mf;//如果已经到达汇点,直接返回
	 int sum=0;//计算u点可以流出的流量之和 (e.g.当u=2时,最后sum=3+3+4+2+3)
	 
	 for(int i=cur[u];i;i=e[i].nxt){
	 	cur[u]=i;//记录从哪一条边走出去了 ,后面有用 
	 	int v=e[i].to;
	 	
	 	if(d[v]==d[u]+1&&e[i].c){//如果v在u的下一层 并且有剩余容量 
	 		int f=dfs(v,min(mf,e[i].c));//正如EK中的'mf[v]=min(mf[u],e[i].c);' 
		 	//回
			e[i].c-=f;
			e[i^1].c+=f;//更新残留网,对照EK 
			sum+=f;
			mf-=f;//类似八皇后,请思考! 
			if(!mf)break;//优化.当在u的前几条分支已经流光了u的可用流量时,就不用考虑剩下的分支了 
		 }
	 } 
	 if(!sum)d[u]=0;//残枝优化.目前这条路没有可行流了 
	 return sum;
}

int dinic(){//累加答案 
	int ans=0;
	while(bfs()){//可以找到增光路 
		memcpy(cur,h,sizeof h);//请思考! 
		ans+=dfs(S,INF);//还是那句话'//源点的流量上限为无穷大,即源点能为后面提供无限大的流量' 
	}
	return ans;
}

void init(){
	memset(h,0,sizeof h);
//	for(int i=1;i<=idx;i++){
//		e[i].to=e[i].nxt=e[i].c=0;
//	}
	memset(cur,0,sizeof cur);
	idx=1;
}

bool judge(int mid){
	init();//注意这里要多次建网络流跑dinic,所以需要init(清空旧的网络流图)
	for (int i = 1; i <= n; ++i){
		add(S, i, cow[i]);//建网络流图
		add(i, S, 0);//建反向图
		add(i + n, T, house[i]);
		add(T,i + n, 0);
		for (int j = 1; j <= n; ++j){
			if (i == j || dis[i][j] <= mid){//如果某两点之间可以在这个时间内到达（最短路求出），则建起一条无限流量的边
				add(i, j + n, INF);
				add(j + n, i, 0);
			}
		}
	}
	ll res = dinic();
//	printf("%lld\n", F);
	return (res >= sum);
} 

void flyd(){
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}

signed main(){
	scanf("%lld%lld",&n,&m);
	S=2*n+1,T=2*n+2;
	for(int i=1;i<=n;++i){
		scanf("%lld%lld",&cow[i],&house[i]);
		sum+=cow[i];//记录牛的总数
	}
	
	//弗洛伊德初始化
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			dis[i][j]=INF;
	for(int i=1;i<=n;++i)
		dis[i][i]=0;
		
	//加边
	for(int i=1;i<=m;++i){
		int u,to,w;
		scanf("%lld%lld%lld",&u,&to,&w);
		dis[u][to]=min(dis[u][to],w);//注意两个点之间可能有多条路
		dis[to][u]=min(dis[to][u],w);
	}
	flyd();
	ans=INF;
	ll l=0,r=INF;
	while(l<=r)	{
		ll mid=(l+r)>>1;
		if(judge(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	if (ans == INF || ans == 0) printf("-1\n");
	else printf("%lld", ans);
}
```




---

