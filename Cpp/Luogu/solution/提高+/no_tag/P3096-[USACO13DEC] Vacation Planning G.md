# [USACO13DEC] Vacation Planning G

## 题目描述

Air Bovinia operates flights connecting the N farms that the cows live on (1 <= N <= 20,000). As with any airline, K of these farms have been designated as hubs (1 <= K <= 200, K <= N).

Currently, Air Bovinia offers M one-way flights (1 <= M <= 20,000), where flight i travels from farm u\_i to farm v\_i and costs d\_i (1 <= d\_i <= 10,000) dollars.  As with any other sensible airline, for each of these flights, at least one of u\_i and v\_i is a hub.  There is at most one direct flight between two farms in any given direction, and no flight starts and ends at the same farm.

Bessie is in charge of running the ticketing services for Air Bovinia. Unfortunately, while she was away chewing on delicious hay for a few hours, Q one-way travel requests for the cows' holiday vacations were received (1 <= Q <= 50,000), where the ith request is from farm a\_i to farm b\_i.

As Bessie is overwhelmed with the task of processing these tickets, please help her compute whether each ticket request can be fullfilled, and its minimum cost if it can be done.

To reduce the output size, you should only output the total number of ticket requests that are possible, and the minimum total cost for them. Note that this number might not fit into a 32-bit integer.

是n个点m条有向边，求两两之间的最短路，要求路径上必须经过编号1~k的至少一个点


## 说明/提示

For the first flight, the only feasible route is 1->2->3, costing 20. There are no flights leaving farm 3, so the poor cows are stranded there.


## 样例 #1

### 输入

```
3 3 1 2 
1 2 10 
2 3 10 
2 1 5 
2 
1 3 
3 1 
```

### 输出

```
1 
20 
```

# 题解

## 作者：Ak_hjc_using (赞：1)

本题：[P3096 \[USACO13DEC\] Vacation Planning G](https://www.luogu.com.cn/problem/P3096)\
弱化版：[P3094 \[USACO13DEC\] Vacation Planning S](https://www.luogu.com.cn/problem/P3094)

### 思路

其实就是 Dijkstra 的模板题。

题目意思简化为：

给定一张 $n$ 个点，$m$ 条边的无向图，$k$ 个关键点，给定 $Q$ 次询问，每次询问从 $s$ 到 $t$ **必须经过至少一个关键点**的最短路径。

思路：

弱化版：由于数据量非常小，$n \le 200$，故直接 floyd 算出所有点的最短路径，枚举所有中转点（也就是关键点），算出答案即可。

本题：由于数据量比较大，使 floyd 无法通过本题，所有我们可以使用 Dijkstra 算法，时间复杂度稳定 $O((n+m) \log m)$，可以过本题。

如果是使用 Dijkstra 算法，那么中转点怎么记录呢？，设有一条路径，`1 -> 2 -> 3`，其中 $2$ 是关键点，那么这条路径就可以化为 `1 -> 2` 的路径，加上 `2 -> 3` 的路径，那么就巧妙地转化了中转点的问题，对每一个关键点进行 Dijkstra，记录两个数组，分别用来记录 $1$ 到关键点的距离和关键点到 $n$ 的距离，统计答案时相加即可。

#### 重点（需要优化的地方）

我们不是记录了两个二维数组吗？但是这样的话，由于 $n \le 2 \times 10^4$，所以导致空间复杂度太高了，超过了内存限制，但是发现这里的 $k$ 非常小，所有我们可以把所有的关键点转换为它们各自的编号，用一个数组记录即可。

### 代码：

```cpp
#include <iostream>
#include <vector>
#include <queue>
#define int long long
using namespace std;
const int N = 2e4 + 5, M = 800;
int n, m, k, q, dis_1[M][N], vis[N];
int dis_2[M][N], u[N], v[N], w[N], flag[N], val[N];
const int INF = 1e18;
struct Edge {
    int v;
    int w;
};
struct Node {
    int id, w;
    bool operator < (const Node &a) const {
        return w > a.w;
    }
};
vector<Edge> G[N];
void add_edge(int u, int v, int w) {
    G[u].push_back({v, w});
    return ;
}
void Dijkstra(int *dis, int s) {   
    for (int i = 1; i <= n; i++) {
        dis[i] = INF;
        vis[i] = 0;
    }
    priority_queue<Node> Q;
    Q.push({s, 0});
    dis[s] = 0;
    while (!Q.empty()) {
        Node u = Q.top();
        Q.pop();
        if (vis[u.id] == true) continue ;
        vis[u.id] = true;
        for (int i = 0; i < G[u.id].size(); i++) {
            int v = G[u.id][i].v, w = G[u.id][i].w;
            if (vis[v] == false && dis[v] > dis[u.id] + w) {
                dis[v] = dis[u.id] + w;
                Q.push({v, dis[v]});
            }
        }
    }
    return ;
}
signed main()  {
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> n >> m >> k >> q;
    for (int i = 1; i <= m; i++) cin >> u[i] >> v[i] >> w[i];
    for (int i = 1; i <= k; i++) {
        cin >> val[i];
        flag[val[i]] = i;
    }
    for (int i = 1; i <= m; i++) add_edge(u[i], v[i], w[i]);
    for (int i = 1; i <= k; i++) Dijkstra(dis_1[i], val[i]);
    for (int i = 1; i <= n; i++) G[i].clear();
    for (int i = 1; i <= m; i++) add_edge(v[i], u[i], w[i]);
    for (int i = 1; i <= k; i++) Dijkstra(dis_2[i], val[i]);
    for (int i = 1; i <= n; i++) G[i].clear();
    int cnt = 0, sum = 0;
    while (q --) {
    	int s, t;
    	cin >> s >> t;
    	int ans = 1e18;
    	if (flag[s]) ans = dis_1[flag[s]][t];
    	if (flag[t]) ans = min(ans, dis_2[flag[t]][s]);
    	if (ans == 1e18) {
    		for (int i = 1; i <= k; i++) ans = min(ans, dis_1[i][t] + dis_2[i][s]);
		}
		if (ans != 1e18) {
			cnt ++;
			sum += ans;
		}
 	}
 	cout << cnt << '\n' << sum << endl;
    return 0;
}
```

---

## 作者：KEBrantily (赞：1)

## Description

给定一张图，$n$ 个点，$m$ 条单向边。

每条单向边至少有一个端点是枢纽，总共有 $k$ 个枢纽。

给出若干对形如 ```x y``` 的询问，表示询问能否从 $x$ 点走到到 $y$ 点。

求出能成立的询问的个数，以及所有询问的最短路程和。

## Solution

### 具体思路

发现如果每个点都跑一遍最短路，问题就可以直接解决。

但是 $n\le 20000$，数组显然开不下。

另外有路径必须经过至少一个枢纽的限制，所以只对起点跑最短路也是行不通的。

已知每条边的至少一个端点为枢纽，且最多 $k$ 个，$k\le 200$。

所以我们对每个枢纽跑一遍最短路，就可以掌握全图的情况。

对于每组询问：

- 如果起点是枢纽，已经跑过最短路了，可以直接判断。

- 如果起点不是枢纽，那么其能遍历到的点一定是枢纽，而对于枢纽已经处理完毕，所以可以取起点到枢纽的边权与枢纽到终点的最短路之和的最小值。

另外注意，虽然 $k\le 200$，但是给出的枢纽编号范围是 $[1,20000]$，如果直接将其编号作为数组的一维会开不下。

根据以上信息，本题可以完成。

## Code

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define maxn 40010
#define INF 0x3f3f3f3f
#define int long long

using namespace std;

bool vis[maxn];
int n,m,k,q,tot,ans,cnt,pre[maxn];
int Dis[maxn],head[maxn],path[210][maxn];
struct edge{int fr,to,dis,nxt;}e[maxn];

inline int read(){
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
    return s*w;
}

void add(int fr,int to,int dis){
    e[++tot]=(edge){fr,to,dis,head[fr]};head[fr]=tot;
}

void Dijk(int s){
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
    memset(Dis,INF,sizeof Dis);memset(vis,0,sizeof vis);q.push(make_pair(0,s));Dis[s]=0;
    while(!q.empty()){
        int u=q.top().second;q.pop();
        if(vis[u]) continue;vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to;
            if(Dis[to]>Dis[u]+e[i].dis)
                Dis[to]=Dis[u]+e[i].dis,
                q.push(make_pair(Dis[to],to));
        }
    }
    for(int i=1;i<=n;i++) path[pre[s]][i]=Dis[i];
}

signed main(){
    memset(path,INF,sizeof path);
    n=read();m=read();k=read();q=read();     
    for(int i=1,fr,to,dis;i<=m;i++){
        fr=read();to=read();dis=read();
        add(fr,to,dis);
    }
    for(int i=1,pos;i<=k;i++)
        pos=read(),pre[pos]=i,Dijk(pos);
    for(int i=1,fr,to;i<=q;i++){
        fr=read();to=read();
        if(pre[fr]&&path[pre[fr]][to]<path[0][0]) cnt++,ans+=path[pre[fr]][to];
        else{
            int now=INF;
            for(int j=head[fr];j;j=e[j].nxt){
                int v=e[j].to;
                now=min(e[j].dis+path[pre[v]][to],now);
            }
            if(now!=INF&&now<path[0][0]) ans+=now,cnt++;
        }
    }
    printf("%lld\n%lld",cnt,ans);
    return 0;
} 
```


---

## 作者：SuperGoodGame (赞：1)

感觉题目读了很长时间 ， QAQ可能是我太弱了

题目读懂后难度可能就在代码上了 ， 

因为每条边肯定与至少一个收费站相连 ，而且收费站个数很少 ， 所以我们不需要想floyd那样枚举出所有起点 ， 只用枚举那k个收费站即可

正图反图都建一下 ， 每个收费站作为起点跑一下**最短路**

统计答案时 ， 如果起点终点是收费站 ，** ans= 到另一个端点的最短路** ， 

如果不是 ， **ans= 收费站->起点（反图）  + 收费站->终点 ** 

最短路dis的代码细节还是要注意下 ， 如果不想写多个板子， 那就要加几个维度

细节见代码：
``` C++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

#define re register
#define ll long long
#define Rep(i,l,r) for(re int i=l;i<=r;++i)
#define Max(a,b) ((a)>(b)?(a):(b))
#define N 20005
#define inf 2e8

int n,m,k,q;
int head[2][N] , tot[2] , ch[N];
int p[205] , cnt;
int dis[2][205][N] , vis[N];
ll s=0 , s2=0;
struct node{
	int v,nxt,w;
}e[2][N*2];
inline void add(int u,int v,int val,int num){
	e[num][++tot[num]]=(node){v,head[num][u],val};
	head[num][u]=tot[num];
}

void spfa(int num1 , int U , int num){
	dis[num][num1][U]=0;
	queue <int> q;
	memset(vis,0,sizeof(vis));
	q.push(U) , vis[U]=1;
	while(!q.empty()){
		int u=q.front() ;
		q.pop() , vis[u]=0;
		for(re int i=head[num][u];i;i=e[num][i].nxt){
			int v=e[num][i].v;
			if(dis[num][num1][v]>dis[num][num1][u]+e[num][i].w){
				dis[num][num1][v]=dis[num][num1][u]+e[num][i].w;
				if(!vis[v])
					vis[v]=1 , q.push(v); 
			}
		}
	}
}
void init(int num,int u){
	spfa(num,u,1);
	spfa(num,u,0);
}
int main() {
	scanf("%d%d%d%d",&n,&m,&k,&q);
	Rep(i,1,m){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w,1) , add(v,u,w,0);
	}
	memset(dis,35,sizeof(dis));
	Rep(i,1,k) scanf("%d",&p[++cnt]) , ch[p[cnt]]=cnt , init(cnt,p[cnt]);
	Rep(i,1,q){
		int u,v , ans=inf;
		scanf("%d%d",&u,&v);
		if(ch[u]) ans=dis[1][ch[u]][v];
		if(ch[v]) ans=min(ans,dis[0][ch[v]][u]);
		if(ans==inf)
			Rep(j,1,k) ans=min(ans , dis[0][j][u]+dis[1][j][v]);
		s+= (ans<inf?ans:0); s2+=(ans<inf?1:0);
	}
	cout<<s2<<endl<<s;
	return 0;
}
``` 

---

## 作者：feizhu_QWQ (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P3096)

## 前置芝士

#### [弱化版](https://www.luogu.com.cn/problem/P3094)

OK 啊这道题简单 Floyd 预处理就能 AC。

## 正题开始

好的啊，这道题一眼就能看出是最短路好吧~~废话~~。\
OK 啊，这道题和弱化版的唯一区别有两个：

1. 之前的中枢点是 $1 \sim k$，现在却是指定点。
2. 数据量暴增

所以说啊，这道题怎么写？\
关键点在于 $k$。\
$k$ 的范围十分的小，只有 $200$。\
所以说，我们可以把答案分为两个部分。\
一个是起点到中枢点的距离，二是中枢点到终点的距离。\
这样，思路就出来了，我们预处理出每个中枢点到其他点的距离，因为这里是到起点，所以要额外建一个反图。\
接着处理出中枢点到其他的距离，直接跑。\
还有，如何储存这个答案？\
如果开一个 $n^2$ 的数组，直接炸，所以我们只能存中枢点在所有中枢点的编号，而不是这个中枢点本身的编号！\
至于最短路算法，我选择 Dijkstra。\
所以答案就很明显的出来了！\
最后枚举每个中枢点，然后加上答案就行了。

注：这道题的翻译貌似不是很给力，他让你输出第一行是可行的航线数量，第二行是所有可行航线的最短路权值和哦！\
代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,T;
int dis[205][20005],fdis[205][20005];
int dot[205];
bool vis[20005];
struct edge
{
	int v,w;
};
vector<edge> op[20005],fop[20005];
struct node
{
	int x,id;
	bool operator<(const node &f) const
	{
		return x>f.x;
	}  
};
priority_queue<node> q;
void dijkstra(int id,int s)//模板Dijkstra
{
	for(int i=1;i<=n;i++) dis[id][i]=1e18,vis[i]=false;
	q.push({0,s});
	dis[id][s]=0;
	while(q.size())
	{
		int x=q.top().id;
		q.pop();
		if(vis[x]==true) continue;
		vis[x]=true;
		for(int i=0;i<op[x].size();i++)
		{
			if(vis[op[x][i].v]==true) continue;
			if(dis[id][x]+op[x][i].w<dis[id][op[x][i].v])
			{
				dis[id][op[x][i].v]=dis[id][x]+op[x][i].w;
				q.push({dis[id][op[x][i].v],op[x][i].v});
			}
		}
	}
	return;
}
void fdijkstra(int id,int s)//反图的Dijkstra
{
	for(int i=1;i<=n;i++) fdis[id][i]=1e18,vis[i]=false;
	q.push({0,s});
	fdis[id][s]=0;
	while(q.size())
	{
		int x=q.top().id;
		q.pop();
		if(vis[x]==true) continue;
		vis[x]=true;
		for(int i=0;i<fop[x].size();i++)
		{
			if(fdis[id][x]+fop[x][i].w<fdis[id][fop[x][i].v])
			{
				fdis[id][fop[x][i].v]=fdis[id][x]+fop[x][i].w;
				vis[fop[x][i].v]=true;
				q.push({fdis[id][fop[x][i].v],fop[x][i].v});
			}
		}
	}
	return;
}
signed main()
{
	ios::sync_with_stdio(false);//关流好习惯
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k>>T;
	for(int i=1;i<=m;i++)
	{
		int x,y,w;
		cin>>x>>y>>w;
		op[x].push_back({y,w});
		fop[y].push_back({x,w});//建反图
	}
	for(int i=1;i<=k;i++) cin>>dot[i];
	for(int i=1;i<=k;i++) dijkstra(i,dot[i]);//预处理答案
	for(int i=1;i<=k;i++) fdijkstra(i,dot[i]);
	int sum=0,cnt=0;
	while(T--)
	{
		int s,t;
		cin>>s>>t;
		int minn=1e18;
		for(int i=1;i<=k;i++) minn=min(minn,fdis[i][s]+dis[i][t]);//答案
		if(minn<1e17) cnt++,sum+=minn;
	}
	cout<<cnt<<endl<<sum;
	return 0;
}
```

有关 Dijkstra 的知识，可以参考飞竹小课堂：[**Dijkstra**](https://www.luogu.com.cn/article/o0emaema)\
ヾ (￣▽￣) Bye Bye

---

## 作者：jinfanhao (赞：1)

这道题是道很好的图论题。\
因为要找中转点，所以把图分为正图和反图，对于每个中转点正图反图都要跑。最后在枚举中转点，看中转点中有没有能联通的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e4+1,M=201;
int n,m,k,t,dist[2][M][N],cnt=0,sum=0,op[M];
bool ok[N];
struct edge{
	int v,w;
};
struct node{
	int key,value;
	bool operator<(const node &x) const{
		return value>x.value;
	}
};
vector<edge> g[2][N];
void dijkstra(int pos,int col){
	int st=op[pos];
	for(int i=1; i<=n; ++i){
		dist[col][pos][i]=1e15;
		ok[i]=false;
	}
	dist[col][pos][st]=0;
	priority_queue<node> pq;
	pq.push(node{st,0});
	while(pq.size()){
		node now=pq.top();
		pq.pop();
		int u=now.key;
		if(ok[u])continue;
		ok[u]=true;
		for(int i=0; i<g[col][u].size(); ++i){
			int v=g[col][u][i].v,w=g[col][u][i].w;
			if(!ok[v] && dist[col][pos][v]>dist[col][pos][u]+w){
				dist[col][pos][v]=dist[col][pos][u]+w;
				pq.push({v,dist[col][pos][v]});
			}
		}
	}
}
signed main(){
	scanf("%lld%lld%lld%lld",&n,&m,&k,&t);
	for(int i=1; i<=m; ++i){
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		g[0][u].push_back({v,w});
		g[1][v].push_back({u,w});
	}
	for(int i=1; i<=k; ++i)scanf("%d",&op[i]);
	sort(op+1,op+k+1);
	for(int i=1; i<=k; ++i){
		dijkstra(i,0);
		dijkstra(i,1);
	}
	while(t--){
		int u,v;
		scanf("%lld%lld",&u,&v);
		int minx=1e15;
		for(int i=1; i<=k; ++i)minx=min(minx,dist[1][i][u]+dist[0][i][v]);
		if(minx!=1e15){
			++cnt;
			sum+=minx;
		}
	}
	printf("%lld\n%lld",cnt,sum);
	return 0;
} 
```

---

## 作者：zwye (赞：0)

### 题目大意
他发现整个地图中有 $N$ 个地点。对于所有的路线，指定了其中 $K$ 个地点作为收费站。他设计了 $M$ 种单向的路线，第 $i$ 条路线从地点 $U_{i}$ 至 $V_{i}$ 收费为 $D_{i}$。路线保证 $U_{i}$ 或 $V_{i}$ 至少有一个是收费站，且 $U_{i} \ne V_{i}$，任意两个地点至多有一条路线。现在 Awson 准备进行规划。共提出 $Q$ 个询问，其中第 $i$ 个询问是从地点 $A_{i}$ 至地点 $B_{i}$。请帮助他计算，每个请求是否满足（是否从地点 $A_{i}$ 至地点 $B_{i}$ 有可行路线），并计算：能满足的度假询问的最小费用总和。
### 方法
spfa 求出每个关键点到每一个点的距离，然后查找时有两种情况。

1. from 为关键点，直接输出 from 到 to 的距离。

2. from 不为关键点，那么根据题意与 from 相连的所有点都是关键点，所以枚举每一个关键点求一个最小值再加上 from 到这个关键点的距离就可以了。
### 代码
```c
#include<bits/stdc++.h> 
using namespace std;
int n,m,k,q,cnt,ans,tot;
int head[20005],kk[20005],size=1;
struct node
{
    int next,to,dis;
}edge[20005];
void putin(int from,int to,int dis)
{
    size++;
    edge[size].to=to;
    edge[size].dis=dis;
    edge[size].next=head[from];
    head[from]=size;
}
int dist[201][20005];
bool vis[20005];
void spfa(int r)
{
    int i;
    queue<int>mem;
    memset(vis,0,sizeof(vis));
    mem.push(r);
    vis[r]=1;
    dist[kk[r]][r]=0;
    while(!mem.empty())
    {
        int x=mem.front();mem.pop();
        vis[x]=0;
        for(i=head[x];i!=-1;i=edge[i].next)
        {
            int y=edge[i].to;
            if(dist[kk[r]][y]>dist[kk[r]][x]+edge[i].dis)
            {
                dist[kk[r]][y]=dist[kk[r]][x]+edge[i].dis;
                if(!vis[y])
                {
                    mem.push(y);
                    vis[y]=1;
                }
            }
        }
    }
}
int main()
{
    int i,j;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d%d",&n,&m,&k,&q);
    for(i=1;i<=m;i++)
    {
        int from,to,dis;
        scanf("%d%d%d",&from,&to,&dis);
        putin(from,to,dis);
    }
    memset(dist,127/3,sizeof(dist));
    int kkk;
    for(i=1;i<=k;i++)
        scanf("%d",&kkk),kk[kkk]=++tot,spfa(kkk);
    for(i=1;i<=q;i++)
    {
        int from,to;
        scanf("%d%d",&from,&to);
        if(kk[from]&&dist[kk[from]][to]!=dist[0][0])cnt++,ans+=dist[kk[from]][to];
        else
        {
            int mmin=dist[0][0];
            for(j=head[from];j!=-1;j=edge[j].next)
            {
                int y=edge[j].to;
                mmin=min(mmin,edge[j].dis+dist[kk[y]][to]);
            }
            if(mmin!=dist[0][0])cnt++,ans+=mmin;
        }
    }
    printf("%d\n%d",cnt,ans);
    return 0;
}
```


---

## 作者：iorit (赞：0)

[原题](https://www.luogu.com.cn/problem/P3096)

### 题意

给定一个有$n$个点，$m$条边的有向简单图，其中有$k$个点是枢纽，并告诉你这$k$个点。

$(1\le n,m\le 20000$，$1\le k\le 200)$

给定$1\le q\le 50000$个询问，第$i$个询问给出$u_i$和$v_i$，求

$\large\sum\limits_{i=1}^q{pos(u_i,v_i)}\quad$及$\quad\large\sum\limits_{i=1}^q{dis(u_i,v_i)}$

其中，当$u$可以经过至少一个枢纽到达$v$时，$pos(u,v) = 1$

否则$pos(u,v) = 0$；

而当$pos(u,v) = 0$时，$dis(u,v) = 0$

否则$dis(u,v)$为u经过至少一个枢纽到达v的最短路径长度。

~~怎么这么绕啊~~

### 思路

显然跑$n^3$的Floyd是会妥妥的T飞的。让我们换个角度思考。

注意到$k\le 200$~~十分好欺负~~，那么我们想怎么搞出一个依赖$k$的算法。

参考这道题的菜鸡版本[P3094](https://www.luogu.com.cn/problem/P3094)，我们可以枚举枢纽来计算最短路

因此我们不用计算出每两点间的最短路，只需计算：

(1)所有点到所有枢纽之间的最短路。

(2)所有枢纽到所有点之间的最短路。

想要计算(1)，我们可以建一个反向图，对所有枢纽跑一遍dijkstra；

计算(2)则只需对正向图中的所有枢纽跑一遍dijkstra。

最后枚举枢纽，统计一下即可。

小技巧：建边的时候每建一条$(u,v)$的边我们可以同时建一条$(v+n,u+n)$的边作为反向边，这样就避免了开两个数组。

### 代码

```cpp
// 此处应有头文件...
const int N = 4e4 + 10,M = 2e2 + 10;
const int inf = 0x3fffffff;
int n,m,s,k,q; // s为源点 
int cnt = 0;
int st[N][M]; // 记录所有点到所有枢纽之间的最短路 
int ed[M][N]; // 记录所有枢纽到所有点之间的最短路 
int mid[M]; // 枢纽
int dis[N];
bool vis[N];
int head[N];
struct edge
{
	int v,w;
	int nxt;
}edge[N];
struct node
{
	int dis,num;
	bool operator < (const node &x) const
		{return x.dis < dis;}
};
void add(int u , int v , int w)
{
	++cnt;
	edge[cnt].v = v;
	edge[cnt].w = w;
	edge[cnt].nxt = head[u];
	head[u] = cnt;
	return ;
}
void dijkstra()
{
	for(int i = 1;i <= n << 1;i++) // 循环开两倍，同时初始化反向边域 
		dis[i] = inf;
	memset( vis , false , sizeof(vis) ); 
	dis[s] = 0;
	pr_q<node> q;
	q.push( (node){0 , s} );
	while( !q.empty() )
	{
		int u = q.top().num;
		q.pop();
		if( vis[u] )
			continue;
		vis[u] = true;
		for(int i = head[u];i;i = edge[i].nxt)
		{
			int v = edge[i].v;
			if(dis[v] > dis[u] + edge[i].w) // relax
			{
				dis[v] = dis[u] + edge[i].w;
				q.push( (node){dis[v] , v} );
			}
		}
	}
}
int main()
{
	cin >> n >> m >> k >> q;
	int u,v,w;
	for(int i = 1;i <= m;i++)
		cin >> u >> v >> w,add(u , v , w),add(v + n , u + n , w); // 反向边 
	for(int i = 1;i <= k;i++)
	{
		cin >> mid[i];
		s = mid[i] + n; // 对反向图跑dijkstra. 
		dijkstra();
		for(int j = n + 1;j <= n << 1;j++) // 别忘了从n+1开始 
			if(dis[j] != inf)
				st[j - n][i] = dis[j];
			else
				st[j - n][i] = -1; // 这里赋成-1是为了处理询问时u或v就是枢纽的情况 
		s = mid[i]; // 对正向图跑dijkstra. 
		dijkstra();
		for(int j = 1;j <= n;j++)
			if(dis[j] != inf)
				ed[i][j] = dis[j];
			else
				ed[i][j] = -1;
	}
	int ans = 0,c = 0; // 最短路长度和，可到达的数量
	while(q--)
	{
		int minn = inf; 
		cin >> u >> v;
		for(int i = 1;i <= k;i++)
			if( st[u][i] != -1 && ed[i][v] != -1 )
				minn = min(st[u][i] + ed[i][v] , minn);
		if(minn != inf)
			++c,ans += minn;
	}
	cout << c << endl << ans << endl;
    return 0;
}
```
时间复杂度$O(nklogn+qk)$，不过听说这题SPFA跑的比dijkstra快

~~故而要开O2，不然妥妥的T飞~~

---

## 作者：meimu75 (赞：0)

一看到题，有些人就会想，写一个 Floyd，然后每次询问就枚举枢纽，计算最短路，然后求出答案。

时间复杂度 $O(n^3+qk)$，过不去，考虑优化。

还有一个思路就是每个询问，从起点开始跑 Dij，然后从终点跑**反图** Dij，最后枚举枢纽，用起点和终点到此枢纽的和加起来，取最小值，就是 $a$ 到 $b$ 的距离，然后拿距离计算答案。

但是这样一分析，时间复杂度变成了 $O(n((n+m)\log_2m+k))$，还是过不去。

但是发现 $k$ 很小，所以可以反过来，从每个枢纽开始跑，存起来，每次枚举枢纽然后 $O(1)$ 求出当前距离，单词询问 $O(k)$，这样预处理 $O(k((n+m)\log_2m))$ ，询问 $O(qk)$，是不会超时的。

> solve 的流程：
>
> 输入，建图。
>
> 枚举枢纽：
>
> > 计算当前枢纽到所有点的距离和所有点到当前枢纽的距离。
>
> 定义 $ans1$ 为起点能够到达终点的询问，初始值为 $q$。
>
> 定义 $ans2$ 为距离之和。
>
> 询问：
>
> > 输入起点和终点。
> >
> > 定义 $ans$ 为这一次 $a$ 到 $b$ 经过枢纽的最短路。
> >
> > 枚举枢纽：
> >
> > > 计算起点到当前枢纽的距离加当前枢纽到终点的距离。
> > >
> > > 取最小值（$ans$）。
> >
> > 如果最小值为极大值（就是到不了），那么 $ans1$ 减一。
> >
> > 能到达就 $ans2$ 加上 $ans$。

上代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,q;
struct node
{
	int v,w;
	bool operator<(const node &a)const
	{
		return a.w < w;
	}
};
//这是一个边的结构体，但是由于和 Dij 的优先队列的节点结构体相似，我把它合并了。
vector<node> g1[20005];//正图。
vector<node> g2[20005];//反图。
int dis1[205][20005];//正图的 dis。dis1[i][j]表示从第 i 个枢纽开始跑到点 j 的距离。
int dis2[205][20005];//反图的 dis。dis2[i][j]表示从点 j 开始跑到第 i 个枢纽的距离。
bool vis[20005];//标记。
int sn[20005];//存储所有枢纽点。
void Dij1(int s)//正图 Dij。
{
	for(int i = 1;i <= n;i++)
	{
		dis1[s][i] = 1e18;//清空。
		vis[i] = false;
	}
	priority_queue<node> pq;//优先队列。
	pq.push({sn[s],0});//初始点。
	dis1[s][sn[s]] = 0;//你懂的。
	while(!pq.empty())
	{
		int tx = pq.top().v;
		int tw = pq.top().w;
		pq.pop();
		if(vis[tx])continue;
		vis[tx] = true;
		for(auto it:g2[tx])
		{
			if(tw+it.w < dis1[s][it.v])
			{
				dis1[s][it.v] = tw+it.w;//松弛。
				pq.push({it.v,dis1[s][it.v]});
			}
		}
	}
}
void Dij2(int s)//反图 Dij。
{
	for(int i = 1;i <= n;i++)//清空。
	{
		dis2[s][i] = 1e18;
		vis[i] = false;
	}
	priority_queue<node> pq;//优先队列。
	pq.push({sn[s],0});//初始点。
	dis2[s][sn[s]] = 0;//你懂的。
	while(!pq.empty())
	{
		int tx = pq.top().v;
		int tw = pq.top().w;
		pq.pop();
		if(vis[tx])continue;
		vis[tx] = true;
		for(auto it:g1[tx])
		{
			if(tw+it.w < dis2[s][it.v])
			{
				dis2[s][it.v] = tw+it.w;//松弛。
				pq.push({it.v,dis2[s][it.v]});
			}
		}
	}
}
signed main()
{
	cin >> n >> m >> k >> q;
	for(int i = 1;i <= m;i++)
	{
		int u,v,d;
		cin >> u >> v >> d;
		g1[u].push_back({v,d});
		g2[v].push_back({u,d});
	}
	for(int i = 1;i <= k;i++)
	{
		cin >> sn[i];
		Dij1(i);//找到这个枢纽到所有点的距离。
		Dij2(i);//找到所有点到这个枢纽的距离。
	}
	int ans1 = q,ans2 = 0;
    //ans1:有多少个起点能够到达终点的询问，从 q 开始，有一个不行就减一。
    //ans2:表示距离之和。
	while(q--)
	{
		int a,b;
		cin >> a >> b;
		int ans = 1e9;
		for(int i = 1;i <= k;i++)
		{
			ans = min(ans,dis1[i][a]+dis2[i][b]);//计算当前枢纽的距离。
		}
        //得到最短路 ans。
		if(ans == 1e9)
		{
			ans1--;//有一个到不了。
		}
		else
		{
			ans2 += ans;//距离和加上去。
		}
	}
	cout << ans1 << "\n" << ans2;//输出。
	return 0;
}
//完结撒花！By meimu75
```

完结撒花❀！

**注意，本题中 dij 均可以换成其他单源最短路，Floyd 改成 Johnson 也不是不可以。**

---

## 作者：dsj2012 (赞：0)

# 题意简化
给定一个 $N$ 点 $M$ 条边的单向有权图同时给定 $K$ 个枢纽，和 $Q$ 个询问 $a , b$，要求经过至少一个枢纽让所有可行的方案中总和最小，并且输出有几个可行方案。
# 思路
根据范围可知 $K$ 并不大甚至可以说是极小了，那么我们其实就可以预处理每个点的答案了。

首先枚举 $K$ 个枢纽，然后我们就对这 $K$ 个枢纽跑两遍 dijkstra。那么为什么是两遍呢？

因为我们可以发现从 $u \rightarrow k \rightarrow v$ 时 $k \rightarrow v$ 边是正的，但是 $u \rightarrow k$ 是正的 $k \rightarrow u$ 却不是正的所以要跑两遍。并且跑第二遍是要重新建边。

值得注意的是我们要看看 $u$ 和 $v$ 是否一致，如果一致要特判否则答案会有误。

还有我们会发现 $N$ 有点大不能直接开二维。那么其实我们可以将枢纽的编号当其中一维，因为 $K$ 的大小不大。

# code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,q;
int dis1[755][20005],dis2[755][20005];
int u[20005],v[20005],w[20005];
bool vis[20005];
int cnt,sum;
int d[20005];
map<int, int> mp;
struct pi{
	int v,w;
};
vector<pi>E[20005];
struct node{
	int x,w;
	bool operator < (const node &nxt) const {
		return w > nxt.w;
	}
};
void dijkstra(int* dis,int x){
	for(int i = 1 ; i <= n ; i ++){
		vis[i] = 0;
		dis[i] = 1e18;
	}
	priority_queue<node> q;
	dis[x] = 0;
	q.push({x, dis[x]});
	while(!q.empty()){
		node u = q.top();
		q.pop();
		if(vis[u.x] == 1)continue;
		vis[u.x] = 1;
		for(int i = 0 ; i < E[u.x].size() ; i ++){
			int v = E[u.x][i].v;
			if(dis[v] > dis[u.x] + E[u.x][i].w){
				dis[v] = dis[u.x] + E[u.x][i].w;
				q.push({v , dis[v]});	
			}	
		}	
	} 
	return ;
}
signed main(){
	cin >> n >> m >> k >> q;
	for(int i = 1 ; i <= m ; i ++){
		cin >> u[i] >> v[i] >> w[i];
	}
	for(int i = 1 ; i <= k ; i ++) {
		cin >> d[i];
		mp[d[i]] = i;
	}
	for(int i = 1 ; i <= m ; i ++){
		E[u[i]].push_back({v[i], w[i]});
	} 
	for(int i = 1 ; i <= k ; i ++){
		dijkstra(dis1[i], d[i]);
	}
	for(int i = 1 ; i <= n ; i ++){
		E[i].clear();
	}
	for(int i = 1 ; i <= m ; i ++){
		E[v[i]].push_back({u[i], w[i]});
	}
	for(int i = 1 ; i <= k ; i ++){
		dijkstra(dis2[i] , d[i]);
	}
	while(q --){
		int l,r;
		cin >> l >> r;
		int ans = 1e18;
		if(mp[l])ans = dis1[mp[l]][r];
		if(mp[r])ans = min (ans, dis2[mp[r]][l]);
		if(ans == 1e18){
			for(int i = 1 ; i <= k ; i ++){
				ans = min(ans , dis2[i][l] + dis1[i][r]);
			}
		}
		if(ans != 1e18){
			cnt ++;
			sum += ans;
		}
	}
	cout << cnt << endl;
	cout << sum << endl;
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：0)

考虑k只有200.从题面得之他每条路不可能在两个非枢纽节点之间相连。

那么最终的答案也必定是 u-枢纽节点i-v。

i可以枚举得到。那么就要求dis（u,i）+dis（i,v）最短，k既然这么小，我们可以枚举每个枢纽节点，对原图，反图均做一遍最短路。当然堆优化dij比spfa优？？（我不确定这样的图spfa会不会被卡）

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define pa pair<int ,int >
using namespace std;
const int maxm=20005,maxn=20005;
struct edge{
	int link,next,val;
}e[maxm];
int n,m,k,q,tot,head[maxn];
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
inline void add_edge(int u,int v,int w){
	e[++tot]=(edge){v,head[u],w}; head[u]=tot;
}
int p1[maxn],p2[maxn],p3[maxn];
inline void init(){
	n=read(); m=read(); k=read(); q=read();
	for (int i=1;i<=m;i++){
		p1[i]=read(); p2[i]=read(); p3[i]=read();
		add_edge(p1[i],p2[i],p3[i]); 
	}
}
int nod[maxn],dis2[205][maxn],dis1[205][maxn],vis[maxn];
priority_queue<pa, vector<pa > ,greater<pa> >heap;
inline void dijkstra(int * dis,int x){
	memset(dis,60,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[x]=0; heap.push(make_pair(dis[x],x));
	while (!heap.empty()){
		int u=heap.top().second; heap.pop();
		if (vis[u]) continue;
		vis[u]=1;
		for (int i=head[u];i;i=e[i].next){
			int v=e[i].link;
			if (dis[v]>dis[u]+e[i].val){
				dis[v]=dis[u]+e[i].val;
				heap.push(make_pair(dis[v],v));
			}
		}
	}
}
const int inf=1e9;
int can,sum;
inline void solve(){
	for (int i=1;i<=k;i++){
		nod[i]=read();
	}
	for (int i=1;i<=k;i++) dijkstra(dis1[i],nod[i]);
	tot=0; memset(head,0,sizeof(head));
	for (int i=1;i<=m;i++){
		add_edge(p2[i],p1[i],p3[i]); 
	}
	for (int i=1;i<=k;i++) dijkstra(dis2[i],nod[i]);	
	for (int i=1;i<=q;i++){
		int u=read(),v=read(),ans=inf;
		for (int j=1;j<=k;j++){
			ans=min(ans,dis2[j][u]+dis1[j][v]); 
		}
		if (ans!=inf) can++,sum+=ans;
	}
	writeln(can); writeln(sum);
}
int main(){
	init();
	solve();
	return 0;
} 
```

---

