# [USACO05FEB] Part Acquisition S

## 题目描述

奶牛们接到了寻找一种新型挤奶机的任务，为此它们准备依次经过 $N(1\le N\le 5\times 10^4)$ 颗行星，在行星上进行交易。为了方便，奶牛们已经给可能出现的 $K(1\le K\le 10^3)$ 种货物进行了由 $1$ 到 $K$ 的标号。由于这些行星都不是十分发达。没有流通的货币，所以在每个市场里都只能用固定的一种货物去换取另一种货物。奶牛们带着一种上好的饲料从地球出发，希望在使用的物品的种类数量最少的情况下，最终得到所需要的机器。饲料的标号为 $1$，所需要的机器的标号为 $K$。如果任务无法完成，输出 $-1$。

## 说明/提示

奶牛们至少需要 $4$ 种不同标号的物品，先用 $1$ 去交换 $3$，再用 $3$ 去交换 $2$，最后用 $2$ 交换得到 $5$。

$1\le N\le 5\times 10^4$，$1\le K\le 10^3$。

## 样例 #1

### 输入

```
6 5
1 3
3 2
2 3
3 1
2 5
5 4```

### 输出

```
4```

# 题解

## 作者：DESCENDANTSOFDRAGON (赞：8)

## 题目意思：
设图 $ G(u,v) $，有 $ m $ 条边，每一条边的权值都是 $ 1 $，求点 $ 1 $ 到图上任意一点 $ k $ 的最短路。

## 思路

读完题后我们首先应反应到这是求单源最短路，而求单源最短路最快的方法就是 dijkstra，而 dijkstra 最大的弊端是不能处理负权边，但恰好这道题避免了这个 bug （ 每一条边的权值都是 $ 1 $ ）。


下面用 2 种方法写了一下最短路：

## 1. dijkstra 
### 算法流程：

假设现在要求出某一点 $ S $ 到其他所有点的最短距离，对于每一个点 $ V $ 维护一个“当前距离”$ dist_{v} $ 和“是否访问过” $ visited_{v} $。首先将 $ dist_{s} $ 初始化为 $ 0 $，将其他的点的距离初始化为 $ +\infty $，并将所有点初始化为未访问过。

记 $u\to v$ 的边权为 $ weight_{u\to v} $，然后进行以下几步：

1. 从所有从未访问过的点中，找到当前距离最小的，设为 $ u $，并将其标记为已访问过。


2. 调整 $ u $ 的所有边（若是有向图则为出边）连接的并且未被访问过的点 ：若 $ weight_{u\to v}+dist_{u}<dist_{v} $，则将 $ dist_{v} $ 更新为 $ dist_{u}+ weight_{u\to v} $。 

3. 重复步骤 1 和步骤 2，直到所有点都被标记为已访问过，则 $ dist_{i} $ 即 $ s $ 到 $ i $ 的最短距离。如果只想求从 $ s $ 到某一点的最短距离，那么该点被标记为访问过之后可直接退出。

### 时间复杂度

$ O ( m \log m ) $

## ACcode

```cpp
#include<bits/stdc++.h>  //万能头 
#define maxn 10000005   //太懒别管 
#define INF 1e9  //极大值 
using namespace std;
struct Edge{
    int u,v,w,next;
}edge[maxn];
int head[maxn],cnt,n,m,s,vis[maxn],dis[maxn];
struct node{
    int w,now;
    inline bool operator <(const node &x)const   //根优化 
    //重载运算符把最小的元素放在堆顶（大根堆）
    {
        return w>x.w;//这里注意符号要为'>'
    }
};
priority_queue<node>q;
//优先队列，其实这里一般使用一个pair，但为了方便理解所以用的结构体
inline void add(int u,int v,int w)
{
    edge[++cnt].u=u;
    //这句话对于此题不需要，但在缩点之类的问题还是有用的
    edge[cnt].v=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    //存储该点的下一条边
    head[u]=cnt;
    //更新目前该点的最后一条边（就是这一条边）
}
//链式前向星加边
void dijkstra()
{
    for(int i=1;i<=n;i++)
    {
        dis[i]=INF;
    }
    dis[1]=0;
    //赋初值
    q.push((node){0,1});
    while(!q.empty())
    //堆为空即为所有点都更新
    {
        node x=q.top();
        q.pop();
        int u=x.now;
        //记录堆顶（堆内最小的边）并将其弹出
        if(vis[u]) continue; 
        //没有遍历过才需要遍历
        vis[u]=1;
        for(int i=head[u];i;i=edge[i].next)
        //搜索堆顶所有连边
        {
            int v=edge[i].v;
            if(dis[v]>dis[u]+edge[i].w)
            {
            	dis[v]=dis[u]+edge[i].w;
            	//松弛操作
            	q.push((node){dis[v],v});
            	//把新遍历到的点加入堆中
            }
        }
    }
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
    	int x,y;
        cin>>x>>y;
        add(x,y,1);
    }
    dijkstra();
    if(dis[m]>n)
    {
    	cout<<-1<<endl;
    	return 0;
	}
    cout<<dis[m]+1<<endl;
    return 0;
}
```
## 2. spfa
### 算法流程：
1. 将除源点之外的所有的点当前距离初始化为无穷，并标记为未入队。源点的当前距离为 $ 0 $，将源点入队。

1. 取出队首 $ u $，遍历 $ u $ 的所有出边，检查是否能更新所连接的点 $ v $ 的当前距离。如果 $ v $ 的当前距离被更新并且 $ v $ 不在队中，则将 $ v $ 入队。重复该操作直到队列为空。

1. 检查是否存在负权环的方法为：记录一个点的入队次数，如果超过 $ V-1 $ 次说明存在负权环，因为最短路径上除自身外至多  $ V-1 $ 个点，故一个点不可能被更新超过 $ V-1 $ 次。

### 时间复杂度

$ O ( n + m ) $

## ACcode

```cpp
//spfa
#include<bits/stdc++.h>
#define INF 1e9
#define maxn 1000005
using namespace std;
int n,m,s,num_edge=0;
int dis[maxn],vis[maxn],head[maxn];
struct Edge{
    int next,to;
}edge[maxn]; //结构体表示静态邻接表
void add(int from,int to) //邻接表建图
{ 
    edge[++num_edge].next=head[from]; 
    edge[num_edge].to=to; 
    head[from]=num_edge; 
}
void spfa()
{
    queue<int> q; //spfa用队列，这里用了STL的标准队列
	for(int i=1;i<=n;i++)
		dis[i]=INF;
    q.push(1); 
	dis[1]=1; 
	vis[1]=1; //第一个顶点入队，进行标记
    while(!q.empty()) 
    {
        int u=q.front(); //取出队首
        q.pop(); 
		vis[u]=0; //出队标记
        for(int i=head[u];i;i=edge[i].next) //邻接表遍历
        {
            int v=edge[i].to; 
            if(dis[v]>dis[u]+1) //如果有最短路就更改
            {
                dis[v]=dis[u]+1;
                if(!vis[v]) //未入队则入队
                {
                   vis[v]=1; //标记入队
                   q.push(v);
                }
            } 
        }
    }
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
    	int x,y;
    	cin>>x>>y; 
    	add(x,y); //建图，有向图连一次边就可以了
    }
    spfa(); //开始跑spfa
    if(dis[m]!=INF)  //存在
	    cout<<dis[m]<<endl;
	else          //不存在
		cout<<-1<<endl;
    return 0;
} 
```

### 结束！！！求管理员通过qwq
### 感谢 @蒟酱


---

## 作者：jiangxinyang2012 (赞：5)

## 题意：
有 $k$ 件物品，其中有 $n$ 组物品可以交换，问物品 $1$ 最少需要几次交换可以得到物品 $k$。

## 分析：
我们可以将 $k$ 件物品看成一个有向图的 $k$ 个节点，$n$ 组交换关系看成有向图的 $n$ 条有向边，求出节点 $1$ 到节点 $k$ 的最短路径。

这道题最后就变成了这样：有一个有 $k$ 个节点 $n$ 条边的有向图，求出节点 $1$ 到节点 $k$ 的最短路径，若无法到达，输出 $-1$。

那这题就转化成了一个最短路径模板题了！
## 代码：
这里放一个 SPFA 的代码。
```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int v,next;
}edge[50001]; // 存放有向边 
int cnt=1,head[1010];
void add(int u,int v)
{
	edge[cnt].v=v;
	edge[cnt].next=head[u];
	head[u]=cnt++;
}
int n,k;
int dis[1010]; // dis[i] 表示从物品1得到物品 i 的最小交换次数 
bool vis[1010];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y); //链式前向星建边 
	}
	// 接下来是SPFA模板
	queue<int> q;
	memset(dis,1,sizeof(dis));
	q.push(1);
	vis[1]=1;
	dis[1]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u];i;i=edge[i].next)
		{
			int v=edge[i].v;
			if(dis[v]>dis[u]+1) 
			{
				dis[v]=dis[u]+1;
				if(!vis[v])
				{
					q.push(v);
					vis[v]=1;
				}
			}
		}
	} 
	if(dis[k]!=16843009) // 有解 
		printf("%d\n",dis[k]);
	else  // 无解 
		printf("-1\n");
 	return 0;
}
```
谢谢大家！

---

## 作者：Luxingguang (赞：3)

~~这是蒟蒻写的第四篇题解~~

[题目传送门](https://www.luogu.com.cn/problem/P1673)

## 一、简化版题意
------------
给定一个 $K$ 个节点 $N$ 条边的有向无权图。求从 $1$ 号节点到 $K$ 号节点的最短路径上的节点数。

## 二、思路分析
------------
用链式前向星存储每一条边，再用 dijkstra 的堆优化进行计算。注意：一定要判断无解情况。~~八十分血的教训啊啊啊!!!~~

## 三、代码实现
------------
```cpp
#include<bits/stdc++.h>
#define N 50005
using namespace std;
long long n,m,s,u,v,w,head[2*N],tot,dis[2*N];
bool vis[N];
priority_queue<pair<long long,long long> > q;
struct z{
	long long nxt,to,dis;
}edge[2*N];
void add_edge(long long x,long long y,long long w) {
	tot++;edge[tot].to=y;edge[tot].nxt=head[x];edge[tot].dis=w;head[x]=tot;
}
void dijkstra() {
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[1]=0;
	q.push(make_pair(0,1));
	while(q.size()){
		long long x=q.top().second;q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(long long i=head[x];i;i=edge[i].nxt){
			if(dis[edge[i].to]>dis[x]+edge[i].dis){
				dis[edge[i].to]=dis[x]+edge[i].dis;
				q.push(make_pair(-dis[edge[i].to],edge[i].to));
			}
		}
	}
}
signed main(){
	scanf("%lld%lld",&n,&s);
	for(long long i=1;i<=n;i++){
		scanf("%lld%lld",&u,&v);
		add_edge(u,v,1);
	}
	dijkstra();
	if(dis[s]==4557430888798830399) printf("-1");//0x3f3f3f3f3f3f3f3f=4557430888798830399
	else printf("%lld",dis[s]+1);
	return 0;
}
```


---

## 作者：RisefromtheAshes (赞：3)

题目意思：    
有 $m$ 个路径，从每个 $u_i$ 到 $v_i$ 都要花费 $1$，求 $1$ 到 $k$ 的最小花费。  
解决方案：   
bfs 跑一遍最短路就可以了，用不着那么高级的算法。   
代码如下：
```
#include<bits/stdc++.h>
#define ri register int
#define ll long long
#pragma G++ optimize(3)
using namespace std;
vector<int> G[50010];//存图
int n,dis[50010],m,u,v;
void bfs()//bfs跑最短路
{
	queue<int>z;
	z.push(1);
	memset(dis,0x3f,sizeof(dis));
	dis[1]=1;
	while(z.size())
	{
		int now=z.front();
		z.pop();//一定要出队！不然会死循环
		for(int i=0;i<G[now].size();i++)//遍历所有这个点的子节点
		{
			if(dis[G[now][i]]>dis[now]+1)//如果从这个点到那个点更少花费
			{
				dis[G[now][i]]=dis[now]+1;//更新最少花费
				z.push(G[now][i]);//入队
			}
		}
	}
	if(dis[n]==0x3f3f3f3f)printf("-1");//注意，这边是0x3f3f3f3f要不然会错
	else printf("%d",dis[n]);//最小花费
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		G[u].push_back(v);//存边
	}
	bfs();
	return 0;//好习惯
}
```


---

## 作者：_ouhsnaijgnat_ (赞：2)

最近刚学 dijkstra，写一道题来练练手。

# 题目大意

一群奶牛要依次经过 $N$ 星球进行交易，在这个宇宙共有 $K$ 种货币，第 $i$ 个星球愿意用 $A_{i}$ 换 $B_{i}$，注意是 $A}$ 换 $B$，$B$ 无法换 $A$。

奶牛先带了 $1$ 这个货币，请问要换取到 $K$ 这个货币，最少要经手的货币数量。

# 思路

这道题就是 dijkstra，将这些关系建成一个图，然后用 $dis_{i}$ 来表示用 $1$ 货币换取 $i$ 货币的最小经手货币数量。

先将所有的点置为无穷大，表示走不到。

接着从 $1$ 开始松弛，将每个点都取最小值。

随后，再在这 $K$ 个货币里寻找一个最小值，且不能被使用松弛过，此时，这个最小值的编号 $u$，我们便能确定他是用 $1$ 换取 $u$ 的最短路径。

简单一点，先看一个样例。


```
6 5
1 2
2 3
1 3
3 4
2 4
4 5
```

这个样例里，有 $6$ 个星球，要换到 $5$ 这个货币，我们便从 $1$ 开始松弛，将所有能用他换成另一种货币的都更新，起初 $dis_{1}=1$，因为此时只有 $1$ 这一个货币，接着， $2$ 和 $3$ 都能用 $1$ 换取，将 $dis_{2}$ 和 $dis_{3}$ 都更新成 $2$，表示有这两种货币。

接着，用 $2$ 和 $3$ 依次作松弛。用 $2$ 时，$dis_{3}=3$，比原来的要大，不取；$dis_{3}=2$，因为 $dis_{4}$ 原来等于无穷大，所以更新。用 $3$ 时照样做下去。

当所有点都被用松弛过了以后，$dis_{i}$ 就是从 $1$ 到 $i$ 的最小经手货币数量，很容易想。

综上，$dis_{K}$ 便是要换取到 $K$ 这个货币，最少要经手的货币数量。

代码献上。

# 代码
```cpp
#include<bits/stdc++.h>
#define maxn 10005
using namespace std;
int n,k;
int dis[maxn];
bool f[maxn][maxn],vis[maxn];

void dij(int st){
	memset(dis,0x3f,sizeof(dis));//置为无穷
	memset(vis,false,sizeof(vis));
	dis[st]=1;
	while(1){
		int u=-1;
		for(int i=1;i<=k;i++)
			if(!vis[i]&&(u==-1||dis[i]<dis[u]))
				u=i;
		if(u==-1)break;//都被用松弛过来
		vis[u]=true;
		for(int i=1;i<=k;i++)
			if(!vis[i]&&f[u][i])
				dis[i]=min(dis[i],dis[u]+1);//取最值
	}
}

int main(){
	memset(f,false,sizeof(f));
	scanf("%d%d",&n,&k);
	for(int i=1,u,v;i<=n;i++){
		scanf("%d%d",&u,&v);
		f[u][v]=true;
	}
	dij(1);
	if(dis[k]==0x3f3f3f3f)printf("-1");
	else printf("%d",dis[k]);
	return 0;
}
```


---

## 作者：2021changqing52 (赞：2)

# 思路：
设 $dis_i$ 表示机器 $i$ 至少交换几次，初始 $dis_1=1$，其余设为极大值。

转移：若机器 $i$ 能交换得到机器 $j$，则 $dis_j=dis_i+1$。

方程类似有向图中的最短路，在每个星球上把可交换的连一条边，再运行最短路（BFS 也行），答案就是 $dis_k$。
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,u,v,dis[50005];
vector<int>e[50005];
void bfs(){//BFS
	queue<int>q;
	q.push(1);
	memset(dis,0x3f,sizeof dis);
	dis[1]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(auto v:e[u]){
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				q.push(v);	
			}
		}
	}
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>u>>v;
		e[u].push_back(v); //连边
	}
	bfs();
	if(dis[k]!=0x3f3f3f3f)cout<<dis[k];
	else cout<<-1;//不能完成任务
	return 0;
}
```


---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/P1673)

这题本质上就是最短路。

题目上说每行的两个数字 $A_i$ 和 $B_i$ 表示第 $i$ 颗行为得到 $B_i$ 愿意提供 $A_i$，那么，我们就可以按照题目的说法画出下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/b5a0ec7i.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

简化一下就变成了一条从 $A_i$ 到 $B_i$ 的有向边。

我们要让点 $1$ 到点 $k$ 经过的点最少，那么肯定就要让走过的边最少，否则就有可能无法保证经过的点最少。

那么这题就可以转化为求单源最短路径了，边的权值就是单独一条边的边数，也就是 $1$。

求最短路有两种，bellman-ford 和 dijkstra，我就不细讲了，想了解请自行前往 [P3371](https://www.luogu.com.cn/problem/P3371)。

单源最短路径求完后并没有结束，因为我们求的是最短路径而不是最少点。我们都知道，最短路径的点会比路径边数多 $1$，这个结论其实就是植树问题的两端都栽树问题。所以我们输出答案时要输出 $dis_k+1$。

# CODE:
```cpp
//bellman-ford
#include<bits/stdc++.h>
using namespace std;
int n,k,u[50010],v[50010],dis[1010];
inline void ford()
{
	for(register int i=1;i<=k-1;i++)
		for(register int j=1;j<=n;j++)
			dis[v[j]]=min(dis[v[j]],dis[u[j]]+1);
}
int main()
{
	scanf("%d%d",&n,&k);
	for(register int i=1;i<=n;i++) scanf("%d%d",&u[i],&v[i]);
	for(register int i=1;i<=k;i++) dis[i]=999999999;
	dis[1]=0;
	ford();
	if(dis[k]==999999999) printf("-1");
	else printf("%d",dis[k]+1);
	return 0;
}
```

```cpp
//dijkstra
#include<bits/stdc++.h>
using namespace std;
int n,k,g[1010][1010],dis[1010],s=1,u,v;
bool b[1010];
inline void dij()
{
	while(!b[s])
	{
		b[s]=1;
		for(register int i=1;i<=k;i++)
			if(!b[i]&&g[s][i]) dis[i]=min(dis[i],dis[s]+1);
		int minn=999999999,x=0;
		for(register int i=1;i<=k;i++)
		{
			if(b[i]) continue;
			if(dis[i]<minn) minn=dis[i],x=i;
		}
		s=x;
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(register int i=1;i<=n;i++) scanf("%d%d",&u,&v),g[u][v]=1;
	for(register int i=1;i<=k;i++) dis[i]=999999999;
	dis[1]=0;
	dij();
	if(dis[k]==999999999) printf("-1");
	else printf("%d",dis[k]+1);
	return 0;
}
```

---

## 作者：Neilchenyinuo (赞：1)

- ~~一道最短路板子~~。

## 题目大意

奶牛有 $1$ 号物品，想通过交换得到 $m$ 号物品，求最少经手几样物品。

## Solution

- 转化一下问题：我们可以将 $m$ 件物品看成一个有向图的 $m$ 个节点，$n$ 组交换关系看成有向图的 $n$ 条有向边，求出节点 $1$ 到节点 $m$ 的最短路径。

- 跑一边 $1$ 至 $m$ 最短路，就可以了。

- 但是又有很多细节。

## 坑点

1. 首先，答案要加一。（因为本题是一道植树问题，点数为段数 $+1$）

2. 本题权值为一。

3. 是单向边不是双向边。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+5;
int n,m,s,dis[N],x,y,z;
bool vis[N];
struct edge
{
	int to,w;
};
vector<edge> nbr[N];
struct node//重载运算符
{
	int id,dist;
	bool operator<(const node&b)const
	{
		return dist>b.dist;
	}
};
void dijkstra(int s)//dj模板
{
	memset(vis,0,sizeof vis);
	for(int i=1;i<=n;i++)
		dis[i]=INT_MAX;
	priority_queue<node> pq;
	dis[s]=0;
	pq.push((node){s,0});
	while(!pq.empty())
	{
		int cur=pq.top().id;
		pq.pop();
		if(vis[cur])
			continue;
		vis[cur]=1;
		for(int j=0;j<nbr[cur].size();j++)
		{
			int nxt=nbr[cur][j].to,w=nbr[cur][j].w;
			if(dis[cur]<dis[nxt]-w)
			{
				dis[nxt]=dis[cur]+w;
				pq.push((node){nxt,dis[nxt]});
			}
		}
	}
	return ;
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>x>>y;
		nbr[x].push_back((edge){y,1});//蒟蒻用的是 vector 存图，也可以用链式前向星。
	}
	dijkstra(1);
	if(dis[m]==INT_MAX)
		return cout<<-1,0;
	cout<<dis[m]+1;//植树问题
	return 0;
}
```


---

## 作者：YangXiaopei (赞：0)

## 题目大意：

奶牛有 $1$ 号物品，想通过交换得到 $m$ 号物品，求最少经手几样物品。

## 思路：

明显的一个最短路问题，求出 $1$ 到 $m$ 的最短路，再加 $1$ 即可(一个简单的植树，点数为段数 $+ 1$)。

迪杰斯特拉算法算最短路：

```cpp
void dijkstra(){
	for(int i = 1; i <= n; i++){
	    dis[i] = 2147483647;
	}
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >q;
	dis[t] = 0;
	q.push(make_pair(0, t));
	while(q.size()){
		int tmp = q.top().second;
		q.pop();
		if(vis[tmp]){
		    continue;
		}
		vis[tmp] = 1;
		for(int i = head[tmp]; i; i =s [i].next){
			int v = s[i].v;
			int dist = s[i].w;
			if(dis[v] > dis[tmp] + dist){
				dis[v] = dis[tmp] + dist;
				q.push(make_pair(dis[v], v));
			}
		}
			
	}
}
```

最后，完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, t, u, v, w, cnt;
int head[1000100], dis[1000100];//head[]辅助存图，dis[]记录最短路
bool vis[1000100];//vis[]存是否走过
struct node{
	int u, v, w, next;
}s[1000100];
void add(int u, int v, int w){
	cnt++;
	s[cnt].u = u;
	s[cnt].v = v;
	s[cnt].w = w;
	s[cnt].next = head[u];
	head[u] = cnt;
}
void dijkstra(){
	for(int i = 1; i <= n; i++){
	    dis[i] = 2147483647;
	}
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >q;
	dis[t] = 0;
	q.push(make_pair(0, t));
	while(q.size()){
		int tmp = q.top().second;
		q.pop();
		if(vis[tmp]){
		    continue;
		}
		vis[tmp] = 1;
		for(int i = head[tmp]; i; i =s [i].next){
			int v = s[i].v;
			int dist = s[i].w;
			if(dis[v] > dis[tmp] + dist){
				dis[v] = dis[tmp] + dist;
				q.push(make_pair(dis[v], v));
			}
		}
			
	}
}
int main(){
	cin >> n >> m;
	t = 1;
	for(int i = 1; i <= n; i++){
		cin >> u >> v;
		add(u, v, 1);//存图
	}
	dijkstra();
	if(dis[m] > n){//算是否能到
		cout << -1;
		return 0;
	}
	cout << dis[m] + 1;//最后输出
	return 0;
}
```
## 完结撒花。

---

## 作者：I_will_AKIOI (赞：0)

一道最短路板子题。

首先我们将样例画出，将使用 $A_i$ 兑换 $B_i$ 理解成从 $A_i$ 到 $B_i$ 的一条路径。可以得到下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/xdlahiuy.png)

如何求 $1\sim 4$ 的最短路呢？Floyd 算法的复杂度为 $O(n^3)$，无法通过。~~其他的又不会~~怎么办？最简单的方法就是 BFS，搜到答案就退出，非常省时间。

其中判重部分可以一起记录到该点的最短时间，也能顺便求出到其他点的最短路。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct data
{
  int now,s;
}w;
vector<int>a[50001];
int n,m,ans,x,y,now,s,vis[50001];
queue<data>q;
int bfs()
{
  memset(vis,0x3f,sizeof(vis));//初始化最大值，后续方便判断
  w.now=1;
  w.s=0;
  q.push(w);
  while(!q.empty())
  {
    w=q.front();
    now=w.now,s=w.s;
    for(int i=0;i<a[now].size();i++)
    {
      int nx=a[now][i];
      if(s>=vis[nx]) continue;//不是最短路，跳过
      w.now=nx,w.s=s+1;
      vis[nx]=w.s;
      if(nx==m) return w.s+1;
      q.push(w);
    }
    q.pop();
  }
  return -1;
}
int main()
{
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++) 
  {
    scanf("%d%d",&x,&y);
    a[x].push_back(y);//将边压入vector中
  }
  ans=bfs();
  printf("%d",ans);
  return 0;
}
```

---

## 作者：technopolis_2085 (赞：0)

分析：

设 $dist_i$ 表示得到标号为 $i$ 的机器最少需要交换几次。

初始化：

由题意可知 $dist_1 = 1$，而其他状态赋成一个极大值。

转移：

对于每一个 $i$，

在每一个行星中，如果 $i$ 能交换得到 $j$，则 $dist_j = dist_i + 1$。

答案：

如果 $dist_K$ 等于极大值，则说明无法通过交换得到 $K$，输出 $-1$。

否则，答案为 $dist_K + 1$。

观察转移过程，发现这其实就是一个边权为 $1$ 的最短路。

由于边权为 $1$，可以通过 bfs 实现。

建议评黄。

code:
```
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
vector<int> G[maxn];
int dist[maxn];

int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	
	for (int i=1;i<=k;i++) dist[i]=114514;
	
	for (int i=1;i<=n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		
		G[u].push_back(v);
	}
	
	queue<int> q;
	while (!q.empty()) q.pop();
	
	q.push(1);
	dist[1]=0;
	
	while (!q.empty()){
		int u=q.front(); q.pop();
		
		for (int i=0;i<(int)G[u].size();i++){
			int v=G[u][i];
			if (dist[v]>dist[u]+1){
				dist[v]=dist[u]+1;
				q.push(v); 
			}
		}
	}
	
	if (dist[k]==114514) printf("-1");
	else printf("%d",dist[k]+1);
	return 0;
}
```


---

