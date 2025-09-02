# Minimum Path

## 题目描述

You are given a weighted undirected connected graph consisting of $ n $ vertices and $ m $ edges. It is guaranteed that there are no self-loops or multiple edges in the given graph.

Let's define the weight of the path consisting of $ k $ edges with indices $ e_1, e_2, \dots, e_k $ as $ \sum\limits_{i=1}^{k}{w_{e_i}} - \max\limits_{i=1}^{k}{w_{e_i}} + \min\limits_{i=1}^{k}{w_{e_i}} $ , where $ w_i $ — weight of the $ i $ -th edge in the graph.

Your task is to find the minimum weight of the path from the $ 1 $ -st vertex to the $ i $ -th vertex for each $ i $ ( $ 2 \le i \le n $ ).

## 样例 #1

### 输入

```
5 4
5 3 4
2 1 1
3 2 2
2 4 2```

### 输出

```
1 2 2 4```

## 样例 #2

### 输入

```
6 8
3 1 1
3 6 2
5 4 2
4 2 2
6 1 1
5 2 1
3 2 3
1 5 4```

### 输出

```
2 1 4 3 1```

## 样例 #3

### 输入

```
7 10
7 5 5
2 3 3
4 7 1
5 3 6
2 7 6
6 2 6
3 7 6
4 2 1
3 1 4
1 7 4```

### 输出

```
3 4 2 7 7 3```

# 题解

## 作者：wsyhb (赞：24)

## 题意简述

给定一个 $n$ 个点，$m$ 条边的无向连通图，第 $i$ 条边边权为 $w_i$，对于 $k$ 条边 $e_1,e_2,\cdots,e_k$ 组成的一条路径，定义其权值为 $\sum_{i=1}^k w_{e_i}-\max_{i=1}^k w_{e_i}+\min_{i=1}^k w_{e_i}$，你的任务是对于所有的 $2 \le i \le n$，分别求出 $1$ 到 $i$ 的所有路径中路径权值的最小值。

**数据范围**：$n,m \le 2 \times 10^5$，$1 \le w_i \le 10^9$。

## 分析 + 题解

由于式子中出现了 $\sum_{i=1}^k w_{e_i}$，考虑 **dijkstra** 求最短路。

考虑路径权值式子的本质——**权值最大的一条边不计权值，权值最小的一条边计双倍权值**。进一步**弱化**这个问题为，**选择任意一条边不计权值，选择任意一条边计双倍权值**，求路径的最小权值。事实上，**这个问题的答案与题目所求完全一致**，因为对于一条确定的路径，要使权值最小，一定会选择权值最大的一条边不计权值，权值最小的一条边计双倍权值。（贪心策略）

对于这个弱化的问题，我们只需在求解最短路的过程中**记录当前是否已选择边不计权值，是否已选择边计双倍权值**，即可按照普通最短路的方式进行计算。

具体来说，设 $dp[x][a][b]$ 为从 $1$ 到 $x$ 的最小路径权值，其中 $a,b$ 分别表示当前是否已选择边不计权值，是否已选择边计双倍权值，$a=1$ 表示“是”，$a=0$ 表示“不是”，$b$ 同理。（即 $a,b$ 为 bool 值）对于一条权值为 $w$ 的边 $(u,v)$，可进行下列转移：

1. $$dp[v][a][b]=\min(dp[v][a][b],dp[u][a][b]+w)$$

2. $$dp[v][1][b]=\min(dp[v][1][b],dp[u][0][b])$$

3. $$dp[v][a][1]=\min(dp[v][a][1],dp[u][a][0]+2w)$$

最终答案即为 $\min(dp[i][0][0],dp[i][1][1])$。（路径可能只有一条边，$\max$ 与 $\min$ 相抵消）

对这种做法的**理解**：可以理解为**按最短路的讨论顺序进行 DP 的转移**，或者**把一个点拆成四个点后跑最短路**。

## 代码实现

具体实现时，根据不同的理解可以有不同的写法。作者是按照拆点来理解的，并把上述的两个 `bool` 值作为**点编号的最低的两个二进制位**，其余的二进制位组成原来的点编号 $x$，即将 $x$ 拆成了 $4x$，$4x+1$，$4x+2$，$4x+3$ 四个点跑最短路。

建议结合代码中的注释进行理解。

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
const int max_n=2e5+5;
const int max_m=2e5+5;
int End[max_m<<1],Last[max_n],Next[max_m<<1],Len[max_m<<1],e;
inline void add_edge(int x,int y,int z)
{
	End[++e]=y;
	Next[e]=Last[x];
	Last[x]=e;
	Len[e]=z;
	End[++e]=x;
	Next[e]=Last[y];
	Last[y]=e;
	Len[e]=z;
}
typedef pair<long long,int> P;
priority_queue<P,vector<P>,greater<P> > q;
long long dis[max_n<<2];//记得开 long long 
void dijkstra()
{
	for(int i=1;i<=n;++i)
		for(int j=0;j<4;++j)
			dis[i<<2|j]=1e18;//初始化为 inf 
	dis[4]=0;//注意起点是 4*1=4 
	q.push(P(0,4));
	while(q.size())
	{
		long long d=q.top().first;
		int x=q.top().second;
		q.pop();
		if(dis[x]<d)
			continue;
		int u=x>>2,a=(x>>1)&1,b=x&1;//点 x 相当于上述转移方程中的 dp[u][a][b] 
		for(int i=Last[u];i;i=Next[i])
		{
			int v=End[i],w=Len[i];
			int y=(v<<2)|(a<<1)|b;//点 y 相当于上述转移方程中的 dp[v][a][b] 
			if(dis[y]>dis[x]+w)
			{
				dis[y]=dis[x]+w;
				q.push(P(dis[y],y));
			}
			if(a==0&&dis[y|2]>dis[x])//注意此处 a=0 才能转移，后一个同理 
			{
				dis[y|2]=dis[x];
				q.push(P(dis[y|2],y|2));
			}
			if(b==0&&dis[y|1]>dis[x]+w*2)
			{
				dis[y|1]=dis[x]+w*2;
				q.push(P(dis[y|1],y|1));
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
	}
	dijkstra();
	for(int i=2;i<=n;++i)
		printf("%lld%c",min(dis[i<<2],dis[i<<2|3]),i<n?' ':'\n');
	return 0;
}
```

---

## 作者：zzr8178541919 (赞：15)


『分层图』好题：

问题的转化思想非常巧妙。

分析题目的内容：对于一条路径，发现它的贡献就是减去了一个最大值，加上了一个最小值。为什么要给这样的一个式子呢，看上去好奇怪啊！

如果不需要考虑最大值和最小值，那这道题做法显然就是跑一个最短路。可现在加上了路径上最大值和最小值的限制，这个限制让我非常难受。

我决定，对这个限制进行一些修改。

还是原来的一条路径，现在我有两次机会，一次要选出一条边的权值加上，还一次要选出一条边的权值减去，要最后结果最小。规定两次机会必须使用。你会怎么选？

根据贪心，我肯定选一条最大的边减去，选一条最小的边加上。发现：这样不就和原题的那个式子是等价的吗？

给定两次机会，一次要选出一条边的权值加上，还一次要选出一条边的权值减去，要最后结果最小。这种改变机会次数有限，且对应不同的权值，求最优方案的问题，应该想到：用分层图！

我们建四层图，然后按以下方式建边：

- 1.每一层自己按题目的要求连$(x,y,w)$的边。

- 2.第一层向第三层，第二层向第四层连$(x,y,2*w)$的边，代表让这条边成为$\min$。

- 3.第一层向第二层，第三层向第四层连$(x,y,0)$的边，代表让这条边成为$\max$。

- 4.第一层向第四层连$(x,y,w)$的边，代表这条边同时作$\max$和$\min$。

跑一次$dij$最短路，最后的答案是所有到第四层的点的答案，因为如果要到达第四层，$\min$，$\max$的边肯定经过且仅经过了一次，符合题意。

$code:$

```cpp
#include<bits/stdc++.h>
#define int long long
#define reg register
using namespace std;
const int maxn=4e6+5;
const int mod=1e9+7;
const int INF=2e16;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
struct node
{
	int to;
	int nxt;
	int dis;
}edge[maxn];
int wugui=0;
int head1[maxn];
void add(int x,int y,int d)
{
	wugui++;
	edge[wugui].to=y;
	edge[wugui].nxt=head1[x];
	edge[wugui].dis=d;
	head1[x]=wugui;
}
struct vode
{
	int id;
	int dist;
}love;
priority_queue<vode> q;
bool operator<(vode a,vode b)
{
	return a.dist>b.dist;
}
int n,m;
//int dist[maxn];
void add1(int x,int y,int v)
{
	add(x,y+n,0),add(x+2*n,y+3*n,0);
	add(x,y+2*n,2*v),add(x+n,y+3*n,2*v);
	add(x,y+3*n,v);
	add(x,y,v),add(x+n,y+n,v),add(x+2*n,y+2*n,v),add(x+3*n,y+3*n,v);
}
int vis[maxn];
int dist[maxn];
int s,t;
void dij()
{
	for(reg int i=s;i<=t;i++)
	dist[i]=INF;
	dist[s]=0;
	vode p;
	p.id=s;
	p.dist=0;
	q.push(p);
	while(!q.empty())
	{
		vode point=q.top();
		q.pop();
		if(vis[point.id])
		continue;
		vis[point.id]=1;
		for(reg int i=head1[point.id];i;i=edge[i].nxt)
		{
			int to=edge[i].to;
			if(dist[to]>dist[point.id]+edge[i].dis)
			{
				dist[to]=dist[point.id]+edge[i].dis;
				vode p;
				p.id=to;
				p.dist=dist[to];
				q.push(p);	
			}
		}
	}
}
signed main()
{
	n=read(),m=read();
	for(reg int i=1;i<=m;i++)
	{
		int x=read(),y=read(),z=read();
		add1(x,y,z);
		add1(y,x,z);
	}
	s=1,t=4*n;
	dij();
	for(reg int i=2;i<=n;i++)
	{
		printf("%lld ",dist[i+3*n]);
	}
	printf("\n");
	return 0;
}
/*
*/
```


---

## 作者：Imakf (赞：6)

题意：我们定义一条路径的长度为经过边权的和减去最大边权加上最小边权。请求出 $1$ 到 $2 \sim n$ 所有结点的最短路。

~~Educational round 居然送温暖~~

不难发现：如果任意减去一条边权，那么减去最大边权最短；

如果任意加上一条边权，那么加上最小边权最短。

所以即对每个结点拆成 $4$ 个，表示 是否加上了一条边权和是否减去了一条边权。

然后对于这个新图跑最短路即可。

```cpp
#include <bits/stdc++.h>

#define debug(...) fprintf(stderr ,__VA_ARGS__)
#define __FILE(x)\
	freopen(#x".in" ,"r" ,stdin);\
	freopen(#x".out" ,"w" ,stdout)
#define LL long long

const int MX = 8e5 + 23;
const LL MOD = 998244353;

int read(){
	char k = getchar(); int x = 0;
	while(k < '0' || k > '9') k = getchar();
	while(k >= '0' && k <= '9') x = x * 10 + k - '0' ,k = getchar();
	return x;
}

int head[MX] ,tot;
struct edge{
	int node ,next ,w;
}h[MX * 5];
void addedge(int u ,int v ,int w){
	h[++tot] = (edge){v ,head[u] ,w} ,head[u] = tot;
}
int n ,m;
void add(int u ,int v ,int w ,int flg = 1){
	addedge(u ,v ,w);
	addedge(u ,v + n ,0);
	addedge(u ,v + 2 * n ,2 * w);
	addedge(u ,v + 3 * n ,w);

	addedge(u + n ,v + n ,w);
	addedge(u + n ,v + 3 * n ,2 * w);

	addedge(u + 2 * n ,v + 2 * n ,w);
	addedge(u + 2 * n ,v + 3 * n ,0);

	addedge(u + 3 * n ,v + 3 * n ,w);
	if(flg) add(v ,u ,w ,0);
}

struct node{
	int id;
	LL dis;
	bool operator <(const node& B)const{
		return dis > B.dis;
	}
};

LL dis[MX] ,vis[MX];
void dijkstra(){
	memset(dis ,0x3f ,sizeof dis);
	memset(vis ,0 ,sizeof vis);
	std::priority_queue<node> q;
	q.push((node){1 ,0});
	dis[1] = 0;
	while(!q.empty()){node tmp = q.top(); q.pop();
		int x = tmp.id;
		if(vis[x] || dis[x] != tmp.dis) continue;
		vis[x] = 1;
		for(int i = head[x] ,d ; i ; i = h[i].next){
			if(dis[x] + h[i].w < dis[d = h[i].node]){
				dis[d] = dis[x] + h[i].w;
				if(!vis[d]) q.push((node){d ,dis[d]});
			}
		}
	}
}

int main(){
	n = read() ,m = read();
	for(int i = 1 ,u ,v ,w ; i <= m ; ++i){
		u = read() ,v = read() ,w = read();
		add(u ,v ,w);
	}
	dijkstra();
	for(int i = 2 ; i <= n ; ++i)
		printf("%lld%c" ,dis[i + 3 * n] ," \n"[i == n]);
	return 0;
}
```

---

## 作者：PtrZ (赞：5)

## CF1473E Minimum Path
[题目传送门](https://www.luogu.com.cn/problem/CF1473E)

分析：这道题如果没有边集的计算的话，就是裸的 `dijistra` 。但此时题目中有边集的计算，$\sum_{i\in E}w_i-\max_{i\in E}w_i+\min_{i\in E}w_i$。所以每次点时有两种选择就是有两个分支。那么就可以用分层图来写，每次输入一条边就建三层图，就是中间的那层图有两个分支，一个是先用 $2w$ 再用 $0$,一个是先用 $0$ 再用 $2w$。建图完成后，再跑一遍 `dijistra`。最后在从第一次的 $n$ 点中和最后一次的 $n$ 中找出最小值。

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define PII pair<int,int>
vector<PII> g[1000000];
priority_queue<PII,vector<PII>,greater<PII> > q;
void add(int u,int v,int w){
	g[u].push_back(make_pair(v,w));
}
bool vis[1000000];
int dis[1000000];
signed main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=m;i++){ //建图
		int u,v,w; cin>>u>>v>>w;
		add(u,v,w),add(v,u,w);
		add(u+n,v+n,w),add(v+n,u+n,w);
		add(u+n*2,v+n*2,w),add(v+n*2,u+n*2,w);
		add(u+n*3,v+n*3,w),add(v+n*3,u+n*3,w);
		
		add(u,v+n,w*2),add(v,u+n,w*2);
		add(u,v+n*2,0),add(v,u+n*2,0);
		add(u+n,v+n*3,0),add(v+n,u+n*3,0);
		add(u+2*n,v+3*n,2*w),add(v+2*n,u+3*n,2*w);
	}
	for(int i=1;i<=n*4;i++){ //初始化
		dis[i]=1e18;
		vis[i]=0;
	} 
	dis[1]=0;
	q.push(make_pair(0,1));
	while(!q.empty()) //dijistra
	{
		int e=q.top().second;
		q.pop();
		if(!vis[e])
		{
			vis[e]=true;
			int len=g[e].size();
			for(int j=0;j<len;j++)
			{
				int v=g[e][j].first;
				int w=g[e][j].second;
				if(dis[v]>dis[e]+w)
				{
					dis[v]=dis[e]+w;
					q.push(make_pair(dis[v],v));
				}
			}
		}
	}
	for(int i=2;i<=n;i++){
		printf("%lld ",min(dis[i],dis[n*3+i]));
	}
	return 0;
}
```


---

## 作者：ZaireEmery (赞：2)

考虑这样一个问题，我们不是加上最小边权，减去最大边权，而是在路径上随意加上、减去一条边的边权，求从编号 $1$ 的点到编号为 $i$ 的点的最短路。易知，为了让路径最短，最短路一定是加上最小边权，减去最大边权的。所以，这个问题和原题完全相同。

接下来考虑如何解决这个问题。不难想到，可以把每个节点拆分成 $(0,0),(0,1),(1,0),(1,1)$ 四个状态，其中第一维表示有没有加上过边权，第二维表示有没有减去过边权，然后在新的图上跑 $dijkstra$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
#define F first
#define S second
#define mp make_pair
#define int long long//要开long long
using namespace std;
int n,m;
vector<pair<int,int> > v[200010];
int dist[200010][2][2];//第二维表示有没有加上过边权，第三维表示有没有减去过边权
set<pair<int,pair<int,pair<bool,bool> > > > s;
void upd(int i,int j,int k,int x){//用x来更新dist[i][j][k]
	if(x<dist[i][j][k]){
		s.erase(mp(dist[i][j][k],mp(i,mp(j,k))));
		dist[i][j][k]=x;
		s.insert(mp(dist[i][j][k],mp(i,mp(j,k))));
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y,z;
		cin>>x>>y>>z;
		v[x].push_back(mp(y,z));
		v[y].push_back(mp(x,z));
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<=1;j++)
			for(int k=0;k<=1;k++)
				dist[i][j][k]=1e18;
	dist[1][0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=1;j++)
			for(int k=0;k<=1;k++)
				s.insert(mp(dist[i][j][k],mp(i,mp(j,k))));
	for(int i=1;i<=4*n;i++){
		pair<int,pair<int,pair<bool,bool> > > p=*s.begin();
		int x=p.F,yi=p.S.F,yj=p.S.S.F,yk=p.S.S.S;
		s.erase(s.begin());
		if(yj==0&&yk==0){
			for(int j=0;j<v[yi].size();j++){
				upd(v[yi][j].F,0,0,x+v[yi][j].S);
				upd(v[yi][j].F,0,1,x);
				upd(v[yi][j].F,1,0,x+2*v[yi][j].S);
				upd(v[yi][j].F,1,1,x+v[yi][j].S);
			}
		}else if(yj==0&&yk==1){
			for(int j=0;j<v[yi].size();j++){
				upd(v[yi][j].F,0,1,x+v[yi][j].S);
				upd(v[yi][j].F,1,1,x+2*v[yi][j].S);
			}
		}else if(yj==1&&yk==0){
			for(int j=0;j<v[yi].size();j++){
				upd(v[yi][j].F,1,0,x+v[yi][j].S);
				upd(v[yi][j].F,1,1,x);
			}
		}else{
			for(int j=0;j<v[yi].size();j++)
				upd(v[yi][j].F,1,1,x+v[yi][j].S);
		}
	}
	for(int i=2;i<=n;i++)
		cout<<dist[i][1][1]<<" ";//最后只要输出加上过一条边权并减去过一条边权的最短路即可
	cout<<endl;
	return 0;
}
```


---

## 作者：lndjy (赞：2)

考虑把最大值和最小值的限制改成任意一条边免费，任意一条边二倍。

容易发现，当免费的这条边最大，二倍的这条边最小时，最短路就是答案。

所以问题变成了一条边免费，一条边二倍求最短路。

可以使用分层图求解。

第一层表示没用过的，第二层表示只用过免费的，第三层表示只用过二倍的，第四层表示都用过的，那么第四层的答案就是题目要求的答案。

根据上面的定义，容易得出第一层->第二层和第三层->第四层是免费边，第一层->第三层和第二层->第四层是二倍的。

另外还要注意一个细节，就是这两条边可能是同意条边，所以要和第一层的最短路取一个 $min$。

```cpp
#include<iostream>
#include<queue>
#include<cstring>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,cnt;
int head[N*5],dis[N*5];
struct edge
{
	int to,nxt,v;
}e[N*16];
void add(int u,int v,int w)
{
	e[++cnt].to=v;
	e[cnt].v=w;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
struct node
{
	int num,dis;
	node(int x,int y)
	{
		num=x;dis=y;
	}
	bool operator <(const node &p)
	const{
		return dis>p.dis;
	}
};
priority_queue<node> q;
int v[N*5];
void dij()
{
	memset(dis,0x3f,sizeof dis);
	dis[1]=0;
	q.push(node(1,0));
	while(!q.empty())
	{
		int now=q.top().num;q.pop();
		if(v[now]) continue;
		v[now]=1;
		for(int i=head[now];i;i=e[i].nxt)
		{
			if(dis[e[i].to]>dis[now]+e[i].v)
			{
				dis[e[i].to]=dis[now]+e[i].v;
				q.push(node(e[i].to,dis[e[i].to]));
			}
		}
	}
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
		for(int j=1;j<4;j++)
		{
			add(n*j+u,n*j+v,w);
			add(n*j+v,n*j+u,w);
		}
		add(u,n+v,0);
		add(v,n+u,0);
		add(u,2*n+v,2*w);
		add(v,2*n+u,2*w);
		add(n+u,3*n+v,2*w);
		add(n+v,3*n+u,2*w);
		add(2*n+u,3*n+v,0);
		add(2*n+v,3*n+u,0);
	}
	dij();
	for(int i=2;i<=n;i++)
	cout<<min(dis[i],dis[3*n+i])<<" ";
 	return 0;
}
```


---

## 作者：Maysoul (赞：1)

上课为数不多能听懂的题，写篇题解纪念一下。

## 简述思路：

如果除去最大值和最小值对贡献的影响的话，就是一道普通的最短路。

但是它现在要减去一个最大值，并加上一个最小值，那么我们就需要额外考虑一些东西。

在最短路中，我们已经求出了一个最小的边权集。

那么如果我们再减去边权集中的最大值，那么这个边权集仍然满足它的最小性。

同理，如果我们加上边权集中的最小值，那么它的最小性依然没有被破坏。

换句话说，减去最大边权最短，加上最小边权最短。

那就意味着，我们找出的最短路径性质实际上并没有被破坏。

所以，我们再来重新审视这道题的题意，它就可以变成：

在这个图中删去任意一条边，加上任意一条边的最短路。

所以，我们可以直接建分层图，对于每一条边，都有四种状态：

不变，是要被删去的最大值，是要被删去的最小值，既是最大又是最小值。

综上，那么如果被删去当前边权为 $0$，如果被加上边权为 $2\times w$ ，不变和既是最大又是最小的情况仍为 $w$。

跑最短路即可。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int MAXN=4e6+10;
const int INF=LLONG_MAX/2;
int num,ans;
struct linkstar{
	int from,to,next,w;
}edge[MAXN];
struct node{
	int id;
	int dist;
	node(){	id=0;dist=0;}
	node(int c,int d){id=c;dist=d;}
	bool operator < (const node &x)const{return x.dist<dist;}
};
int head[MAXN],escnt;
int dis[MAXN],vis[MAXN];
int n,m;
priority_queue<node> que;
void add(int from,int to,int w)
{
	edge[++escnt].from=from;
	edge[escnt].to=to;
	edge[escnt].w=w;
	edge[escnt].next=head[from];
	head[from]=escnt;
}
void init(int from,int to,int w)
{
	add(from,to,w);
	add(from,to+n,2*w);
	add(from,to+2*n,0);
	add(from,to+3*n,w);
	add(from+n,to+n,w);
	add(from+n,to+3*n,0);
	add(from+2*n,to+2*n,w);
	add(from+2*n,to+3*n,2*w);
	add(from+3*n,to+3*n,w); 
}
void Dijkstra()
{
	for (int i=1;i<=4*n;i++)	dis[i]=INF;
	dis[1]=0;
	que.push(node(1,0));
	while(que.size()){
		node cp=que.top();
		que.pop();
		if(vis[cp.id]) continue;
		vis[cp.id]=true;
		for (int i=head[cp.id];i!=-1;i=edge[i].next){
			if(dis[edge[i].to]>dis[cp.id]+edge[i].w){
				dis[edge[i].to]=dis[cp.id]+edge[i].w;
				if(!vis[edge[i].to]){
					que.push(node(edge[i].to,dis[edge[i].to]));
				}
			}
		}
	}
}
signed main()
{
	memset(head,-1,sizeof(head));
	int u,v,w;
	cin>>n>>m;
	for (int i=1;i<=m;i++){
		cin>>u>>v>>w;
		init(u,v,w);
		init(v,u,w); 
	}
	Dijkstra();
	for (int i=2;i<=n;i++){
		cout<<dis[3*n+i]<<" ";
	}
	return 0;
}
```


---

## 作者：初雪_matt (赞：1)

比较典的分层图。

考虑将式子转化，显然一条路径的权值可以转换成：路径中最大值的边权为 $0$，最小的边权为原来的两倍。

考虑怎样取值使上述式子最小化，按照贪心思想，即使题目是：路径中任选一条边赋值为 $0$，另一条为原权值的两倍，也是将最大值赋 $0$，最小值变两倍。

所以题目弱化成了任选一条边赋权值，这种情况可以考虑分层图求解。

考虑建 $4$ 层图：

- 第一层，指未用任何一次改变权值的机会，此层向 $2$ 层连 $0$ 边，向 $3$ 层连双倍权值。

- 第二层，指用了一次赋 $0$ 边权的机会，此层向 $4$ 层连双倍权值。

- 第三层，指用了一次赋双倍边权的机会，此层向 $4$ 层连 $0$ 的边。

- 第四层，指两种机会都用了。

答案最终在第四层取值。特殊的，如果最小值只有一条边，在第四层无法取到，所以答案还要对第一层取最小值。

---

## 作者：Umbrella_Leaf (赞：1)

### 题意

> 给定一个包含 $n$ 个点、$m$ 条边的简单无向图，边有边权。定义一条路径 $e_1,e_2,\cdots,e_k$ 的权值为：

> $$\sum_{i=1}^kw_{e_i}-\max_{i=1}^kw_{e_i}+\min_{i=1}^kw_{e_i}$$

> 对于所有 $2\le i\le n$，求 $1$ 号点到 $i$ 号点路径权值的最小值。

> $n,m\le 2\times 10^5$。

### 题解

观察到权值最小实际上是选一条边清零、选一条边翻倍之后的最短路。

考虑分层图最短路，第一层到第二层的边权是 $0$，第二层到第三层的边权是原本的两倍，同一层之间边权不变。直接跑最短路，用第三层的点更新答案。

或者交换清零和翻倍的顺序，两个答案取 $\min$。别忘了处理只经过一条边的情况。复杂度为最短路 $O(n\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,m;
int ex[200005],ey[200005],ez[200005];
vector<pair<int,int> > edge[600005];
ll dis[600005];int vis[600005];
ll ans[600005];
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > >que;
void Dijkstra(){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	que.push(make_pair(0,1));
	dis[1]=0;
	while(!que.empty()){
		int x=que.top().second;que.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(auto e:edge[x]){
			int y=e.first,z=e.second;
			if(dis[y]>dis[x]+z){
				dis[y]=dis[x]+z;
				que.push(make_pair(dis[y],y));
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	memset(ans,0x3f,sizeof(ans));
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&ex[i],&ey[i],&ez[i]);
		if(ex[i]==1)ans[ey[i]]=ez[i];
		if(ey[i]==1)ans[ex[i]]=ez[i];
	}
	for(int i=1;i<=m;i++){
		int x=ex[i],y=ey[i],z=ez[i];
		edge[x].emplace_back(y,z);
		edge[x+n].emplace_back(y+n,z);
		edge[x+n+n].emplace_back(y+n+n,z);
		edge[x].emplace_back(y+n,2*z);
		edge[x+n].emplace_back(y+n+n,0);
		edge[y].emplace_back(x,z);
		edge[y+n].emplace_back(x+n,z);
		edge[y+n+n].emplace_back(x+n+n,z);
		edge[y].emplace_back(x+n,2*z);
		edge[y+n].emplace_back(x+n+n,0);
	}
	Dijkstra();
	for(int i=2;i<=n;i++)ans[i]=min(ans[i],dis[i+n+n]);
	for(int i=1;i<=n+n+n;i++)edge[i].clear();
	for(int i=1;i<=m;i++){
		int x=ex[i],y=ey[i],z=ez[i];
		edge[x].emplace_back(y,z);
		edge[x+n].emplace_back(y+n,z);
		edge[x+n+n].emplace_back(y+n+n,z);
		edge[x].emplace_back(y+n,0);
		edge[x+n].emplace_back(y+n+n,2*z);
		edge[y].emplace_back(x,z);
		edge[y+n].emplace_back(x+n,z);
		edge[y+n+n].emplace_back(x+n+n,z);
		edge[y].emplace_back(x+n,0);
		edge[y+n].emplace_back(x+n+n,2*z);
	}
	Dijkstra();
	for(int i=2;i<=n;i++)printf("%lld ",min(ans[i],dis[i+n+n]));puts("");
	return 0;
}
```

---

## 作者：AsiraeM (赞：0)

题目中的式子可以理解为一条路径的长度，减去这条路径上最长的一条边的长度，再加上这条路径上最短的一条边的长度。

注意到，可以放宽限制，定义一种方案 $(Ed,a,b)$ 的权值为 $\sum_{i\in Ed}w_i-w_a+w_b$，其中 $Ed$ 是一条路径的所包含边的边集，$a\in Ed\ ,b\in Ed$，  
即 $Ed$ 中边的长度总和减去 $a$ 的长度，再加上 $b$ 的长度。  
假设一条路径的边集为 $E$，则这条路径的权值为 $\min_{i\in E\ ,j\in E} (E,i,j)$，要使 $(E,i,j)$ 最小，就要使 $i$ 最长，$j$ 最短，正好符合题目中的定义。

因此可以把每个点拆成四个，对应走到这个点时是否考虑了删去的边与计算两次的边，实现上有多种方法。

代码：
```cpp
//Talk is cheap.Show me your code.
#include<bits/stdc++.h>
namespace xcy{
typedef long long ll;
const int MAXN=200005;
ll head[MAXN],dis[MAXN][2][2],vis[MAXN][2][2],cnt,siz,n,m,i,j,k,l,s,mn,mx;
struct Edge{ll to,pre,val;}ed[MAXN<<1];
struct Node{
	ll val,n,mn,mx;
	bool operator<(Node A)const{return val<A.val;}
	bool operator<=(Node A)const{return val<=A.val;}
}hp[MAXN<<4];

inline void fread(ll &X){X=0;char C=getchar();while(!isdigit(C))C=getchar();while(isdigit(C))X=(X<<1)+(X<<3)+(C^48),C=getchar();}
inline void fout(ll X){if(X<0)X=-X,putchar('-');if(!X){putchar('0'),putchar(' ');return;}char C[25]{};ll Len=0;while(X)C[++Len]=X%10+'0',X/=10;for(;Len;--Len)putchar(C[Len]);putchar(' ');}
inline void add(ll F,ll T,ll V){ed[++cnt].to=T;ed[cnt].val=V;ed[cnt].pre=head[F];head[F]=cnt;}
inline void del()
{
	hp[1]=hp[siz--];ll J=1;
	while(!(J<<1>siz||(hp[J]<=hp[J<<1]&&hp[J]<=hp[(J<<1)+1])))
		if((J<<1)+1>siz||hp[J<<1]<=hp[(J<<1)+1])std::swap(hp[J],hp[J<<1]),J<<=1;
		else std::swap(hp[J],hp[(J<<1)+1]),J=(J<<1)+1;
}
inline void ins(ll V,ll N,ll Mn,ll Mx){hp[++siz]={V,N,Mn,Mx};ll J=siz;while(J!=1&&hp[J]<hp[J>>1])std::swap(hp[J],hp[J>>1]),J>>=1;}

int mian()
{
	fread(n),fread(m);
	memset(dis,0x3f,sizeof(dis));
	for(i=1;i<=m;++i)fread(j),fread(k),fread(l),add(j,k,l),add(k,j,l);
	ins(0,1,0,0);dis[1][0][0]=0;
	while(siz)
	{
		i=hp[1].n;mn=hp[1].mn;mx=hp[1].mx;del();
		if(vis[i][mn][mx])continue;vis[i][mn][mx]=1;
		for(j=head[i];j;j=ed[j].pre)
		{
			k=ed[j].to;
			if(dis[i][mn][mx]+ed[j].val<dis[k][mn][mx])
				dis[k][mn][mx]=dis[i][mn][mx]+ed[j].val,ins(dis[k][mn][mx],k,mn,mx);
			if(mn==0)if(dis[i][0][mx]+2*ed[j].val<dis[k][1][mx])
						dis[k][1][mx]=dis[i][0][mx]+2*ed[j].val,ins(dis[k][1][mx],k,1,mx);
			if(mx==0)if(dis[i][mn][0]<dis[k][mn][1])
						dis[k][mn][1]=dis[i][mn][0],ins(dis[k][mn][1],k,mn,1);
			if(mn==0&&mx==0)if(dis[i][0][0]+ed[j].val<dis[k][1][1])
							   dis[k][1][1]=dis[i][0][0]+ed[j].val,ins(dis[k][1][1],k,1,1);
		}
	}
	for(i=2;i<=n;++i)fout(dis[i][1][1]==0x3f3f3f3f3f3f3f3f?1000000000000000000:dis[i][1][1]);
	return 0;
}}
int main(){return xcy::mian();}

```


---

## 作者：I_am_Accepted (赞：0)

### Analysis

为了让最短路最短，边权不计算的一定是 $\max w_{e_i}$，双倍的一定是 $\min w_{e_i}$，所以我们将题目中的路径 weight 更改为

$$\sum\limits_{i=1}^{k}{w_{e_i}}-w_{e_x}+w_{e_y},\forall 1\le x,y\le k$$

不影响结果。

也就是说，**在路径上任意不选一条边权，任意一条双倍，求最短路。**

这可以用**拆点 Dijkstra** 解决。

具体地，将每个点拆成 $4$ 个，分别表示到这里 有/没有 不选某条边权，有/没有 双倍某条边权。

然后对于原图中的某条边 $(x,y)$，这样建图：

![](https://cdn.luogu.com.cn/upload/image_hosting/q1t6alsf.png)

↑建图方式（当然 $y\to x$ 要再建一遍对称的）

然后跑 Dij 即可 $O(n\log n+m)$ 解决。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 800010

const int inf=1e15;
int n,m,dis[N];
vector<pair<int,int> > e[N];
inline int num(int x,int y){return (x-1)*4+y;}
inline void adde(int x,int y,int z){
	For(i,1,4) e[num(x,i)].pb(mkp(num(y,i),z));
	e[num(x,1)].pb(mkp(num(y,2),2*z));
	e[num(x,1)].pb(mkp(num(y,3),0));
	e[num(x,1)].pb(mkp(num(y,4),z));
	e[num(x,2)].pb(mkp(num(y,4),0));
	e[num(x,3)].pb(mkp(num(y,4),2*z));
}
struct node{
	int id,dis;
	friend bool operator<(node x,node y){return x.dis>y.dis;}
};
priority_queue<node> q;
signed main(){IOS;
	cin>>n>>m;
	int x,y,z;
	For(i,1,m){
		cin>>x>>y>>z;
		adde(x,y,z);
		adde(y,x,z);
	}	
	For(i,1,4*n) dis[i]=inf;
	dis[num(1,1)]=0;
	q.push((node){num(1,1),0});
	int to,val;
	while(!q.empty()){
		x=q.top().id;
		y=q.top().dis;
		q.pop();
		if(dis[x]!=y) continue;
		for(auto i:e[x]){
			to=i.fir;val=i.sec;
			if(dis[to]<=dis[x]+val) continue;
			dis[to]=dis[x]+val;
			q.push((node){to,dis[to]});	
		}
	}
	For(i,2,n) cout<<dis[num(i,4)]<<" "; cout<<endl;
return 0;}
```

---

## 作者：Jayun (赞：0)

# 链接：

[洛谷](https://www.luogu.com.cn/problem/CF1473E)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/15573742.html)

# 题目大意：

给定一张 $n$ 个点 $m$ 条边的无向图，第 $i$ 条边边权为 $w_i$。

对于一条点 $1$ 到点 $n$ 的路径，设其经过的边集为 $E$，定义这条路径的长度为

$$\sum_{e\in E}w_e-\max_{e\in E}(w_e)+\min_{e\in E}(w_e)$$

求点 $1$ 到其他所有点的最短路。

# 思路：

这种路径长度中涉及最大最小，没法直接转移，考虑将题目变形。题目求 $\min\left\{\sum_{e\in E}w_e-\max_{e\in E}(w_e)+\min_{e\in E}(w_e)\right\}$，如果要使得长度最小，那么减掉的一定是最大，加上的一定是最小，所以这个题目好像在说废话，转化为长度之和加上、减去任意某边的最小值。

接下来实现加减操作可以建立分层图，每层都是正常连边，第一层到第二层连边权为 $0$ 的边，第二层到第三层连边权为 $2w$ 的边，答案就是从 $1$ 到第三层的各个点。

但这么做忽略了先加后减的情况，不妨再建一层，第一层到本层连边权为 $2w$ 的边，本层向终点层连边权为 $0$ 的边。

# 代码：

```cpp
const int N = 1e6 + 10;

inline ll Read() {
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

int n, m, T;
struct edge {
	int to, nxt; ll val;
}e[N * 3 << 1];
int head[N], tot;
void add (int u, int v, ll w) {
	e[++tot] = (edge) { v, head[u], w }, head[u] = tot;
}

struct node {
	int val; ll key;
	bool operator < (const node &a) const {
		return key > a.key;
	}
};

priority_queue <node> q;

ll dis[N]; 
bool vis[N];
void dij () {
	memset (dis, 127 / 3, sizeof dis);
	dis[1] = 0;
	q.push((node){ 1, 0 });
	while (!q.empty()){
		int u = q.top().val; q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (dis[v] > dis[u] + e[i].val) {
				dis[v] = dis[u] + e[i].val;
				q.push((node) { v, dis[v] });
			}
		}
	}
}

int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	n = Read(), m = Read();
	for (int i = 1; i <= m; i++) {
		int u = Read(), v = Read(); ll w = Read();
		add (u, v, w), add(v, u, w);
		add (u + n, v + n, w), add(v + n, u + n, w);
		add (u + 2 * n, v + 2 * n, w), add (v + 2 * n, u + 2 * n, w);
		add (u + 3 * n, v + 3 * n, w), add (v + 3 * n, u + 3 * n, w);
		
		add (u, v + n, 2 * w), add (v, u + n, 2 * w);
		add (u + n, v + 3 * n, 0), add(v + n, u + 3 * n, 0);
		
		add (u, v + 2 * n, 0), add (v, u + 2 * n, 0);
		add (u + 2 * n, v + 3 * n, 2 * w), add (v + 2 * n, u + 3 * n, 2 * w);
	}
	dij();
	for (int i = 2; i <= n; i++)
		printf ("%lld ", min(dis[i], dis[i + 3 * n]));
	return 0;
}

```

---

