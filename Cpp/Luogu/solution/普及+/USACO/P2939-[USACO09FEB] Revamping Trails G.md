# [USACO09FEB] Revamping Trails G

## 题目描述

Farmer John dutifully checks on the cows every day. He traverses some of the M (1 <= M <= 50,000) trails conveniently numbered 1..M from pasture 1 all the way out to pasture N (a journey which is always possible for trail maps given in the test data). The N (1 <= N <= 10,000) pastures conveniently numbered 1..N on Farmer John's farm are currently connected by bidirectional dirt trails.  Each trail i connects pastures P1\_i and P2\_i (1 <= P1\_i <= N; 1 <= P2\_i <= N) and requires T\_i (1 <= T\_i <= 1,000,000) units of time to traverse.

He wants to revamp some of the trails on his farm to save time on his long journey. Specifically, he will choose K (1 <= K <= 20) trails to turn into highways, which will effectively reduce the trail's traversal time to 0. Help FJ decide which trails to revamp to minimize the resulting time of getting from pasture 1 to N.

TIME LIMIT: 2 seconds



## 说明/提示

K is 1; revamp trail 3->4 to take time 0 instead of 100. The new shortest path is 1->3->4, total traversal time now 1.


## 样例 #1

### 输入

```
4 4 1 
1 2 10 
2 4 10 
1 3 1 
3 4 100 
```

### 输出

```
1 
```

# 题解

## 作者：QQQfy (赞：116)

# 分层图板子题

### 1.闲聊&写作目的
本蒟蒻的第二篇题解

很久以前就想学分层图了，但一直找不到易于理解的教程（我太弱了）

本文旨在为和我一样弱的蒟蒻们提供良好的体验

与子共食

### 2.什么是分层图？

嘛，就是形如![](https://cdn.luogu.com.cn/upload/pic/10006.png)

的一个东西。（图自P1073@fy1234567ok的题解，侵删）

##### 啊！好珂怕！

然而它与普通图也并没有什么区别。我们发现，上图的三层图，其形态结构几乎一样，所不同的只是图之间的联系罢了。可以理解为把每一个点拆成多个点变成的多层的图。

##### 好！那么分层图中的边有什么意义吗？

### 3.分层图的意义？

分层图中的边权可以随着题目的改变而具备不同的意义。在本题中，边权的定义是：

**1.当边 <u,v,w> 位于第i层上时，表示已改建了i条道路，且不改建当前道路，由u向v耗费w**

**2. 当边 <u,v,w> 位于第i层与i+1层时，表示已改建了i条道路，且改建当前道路，由u向v耗费w**

在本题中，1中的边与原图的边没有区别，而2中的边权显然为0.

##### 好像很有道理，但它是怎么解决本题的呢？

由于本题求的是1到n的最短路，由于1到n能改建0到k中的任意次道路，再联系定义，得

ans=min（ans，dist[i]），其中i为1到n

dist数组记得开maxk* maxn（因为有k层图鸭）

##### 那么分层图能够解决什么类型的问题呢？

### 4.分层图的应用范围

~~并没有~~

大概是把一张图进行k次修改（本题），或者是改变图的定义使其满足本特点的问题（P1073）

### 5.代码实现

~~据说~~本题卡spfa

数组开大点不然紫一半

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=100100;
const int maxm=500500;

int nextt[maxm*42],w[maxm*42],to[maxm*42],head[maxn*42],cnt=0;

void add(int u,int v,int cost)
{
	cnt++;
	nextt[cnt]=head[u];
	head[u]=cnt;
	to[cnt]=v;
	w[cnt]=cost;
}

struct node
{
	int u,dis;
	bool operator<(const node x) const
	{
		return dis>x.dis;
	}
};

priority_queue<node> q;
int dist[maxn*21];

void dij(int s)
{
	memset(dist,0x3f,sizeof(dist));
	dist[s]=0;
	q.push((node){s,0});
	while (!q.empty())
	{
		node fr=q.top();q.pop();
		int u=fr.u,dis=fr.dis;
		if (dis!=dist[u]) continue;
		for (int v=head[u];v;v=nextt[v])
			if (dist[to[v]]>dist[u]+w[v])
			{
				dist[to[v]]=dist[u]+w[v];
				q.push((node){to[v],dist[to[v]]});
			}
	}
}

int n,m,k;

int main()
{
	cin>>n>>m>>k;
	for (int i=1;i<=m;i++)
	{
		int u,v,cost;
		cin>>u>>v>>cost;
		add(u,v,cost);add(v,u,cost);
		for (int j=1;j<=k;j++)
		{
			add(n*j+u,n*j+v,cost);add(n*j+v,n*j+u,cost);
			add(n*(j-1)+u,n*j+v,0);add(n*(j-1)+v,n*j+u,0);
		}
	}
	dij(1);
	int ans=dist[n];
	for (int i=1;i<=k;i++)
	{
//		cout<<"### dist["<<i*n+n<<"]: "<<dist[i*n+n]<<endl;
		ans=min(ans,dist[i*n+n]);
	}
	cout<<ans;
	return 0;
}
```

### 6. 骗赞

看我妖精军师这么可爱就给点赞呗

![](https://ss0.baidu.com/6ONWsjip0QIZ8tyhnq/it/u=672061410,767203769&fm=58&bpow=730&bpoh=1095)




---

## 作者：齐天の小猴 (赞：46)

本蒟蒻已经写了多次题解，但很多都没有过......

~~写的不好不要喷（玻璃的心）~~

### 有错误希望dalao指正

~~分层图最短路也是最近才学会的~~

根据题意，我们可以发现k的取值范围比较小，所以可以直接用分层图

把一个点强行拆分为k个，原图层代表使用0次升级路的机会，其他的图分别表示使用了1次、2次...k次升级路的机会，然后就可以连边了。考虑每层之间的关系，第i层与第i+1层的边的权值为0，等于用掉了一次升级路的机会。

最终跑一边dijktra，然后求出最小的距离，这道题就做完了
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 220010//因为k的范围到了20，我们可能会建立20+的图层，所以要开的大一点
using namespace std;
struct Edge
{
	int to,nexty,w;
}edge[4200010];//链式前向星存边
/*struct node
{
	int code,dis;
	bool operator < (const node& rhs) const {return dis>rhs.dis;}
};*/  //这是本蒟蒻一开始做题时开1维的堆跑dij，结果最后不知道为什么总是做不出来...所以最终改成了二维
bool vis[N];
int n,m,u,v,k,t,tmp;//n个牧场，m条道路，k次机会，u是一条路的起点，v是终点，t是消耗的时间，tmp用于后期运算
int dis[N],head[N],cnt;//存边时所需
//以下是快读的板子
template<typename int_t>//据说可以自动判断输入的类型
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while(ch<'0'||ch>'9') {ch=getchar();if(ch=='-') k=-1;}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	x*=k;
}
//存边
void add(int x,int y,int w)
{
	cnt++;
	edge[cnt].to=y;
	edge[cnt].nexty=head[x];
	edge[cnt].w=w;
	head[x]=cnt;
}
priority_queue< pair<int,int> > q;
//大根堆 优先队列 pair第一维为dist相反数（变成小根堆） 第二维为节点编号 
void dij()//dijkstral 跑最短路 （板子）
{
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;//dis初始化 起点为0，其余为正无穷
    memset(vis,0,sizeof(vis));//节点标记清除
    q.push(make_pair(0,1));
    while(q.size()){
        int x=q.top().second;
        q.pop();//取堆顶
        if(vis[x]) continue;
        vis[x]=1;//标记节点
        for(int i=head[x];i;i=edge[i].nexty)
        {//扫描所有出边
            int y=edge[i].to,z=edge[i].w;
            if(dis[y]>dis[x]+z)
            {
                dis[y]=dis[x]+z;
                q.push(make_pair(-dis[y],y));
            }
        } 
    } 
}
int main()
{
	readx(n);readx(m);readx(k);//读入
	for(int i=1;i<=m;i++)
	{
		readx(u);readx(v);readx(t);//读入
		add(u,v,t);add(v,u,t);//先存入原始图
		for(int j=1;j<=k;j++)//根据k的个数复制原始图
		{
			add(j*n+u,j*n+v,t);
			add(j*n+v,j*n+u,t);
			add((j-1)*n+u,j*n+v,0);//每层间的边的权值为0
			add((j-1)*n+v,j*n+u,0);
		}
	}
	tmp=n;//记录n
	dij();//最短路
	int ans=dis[tmp];//记录原图层上的最小值
	for(int i=1;i<=k;i++)
	{
		ans=min(ans,dis[i*n+tmp]);//与每一层上的最小值进行比较，并更新答案
	}
	printf("%d",ans);//输出
	return 0;
}
```
~~蒟蒻的博客里有关于分层图的知识哦~~~ 

### [不要脸](https://xiaohou.blog.luogu.org/)

---

## 作者：Diamiko (赞：19)

由于本人是蒟蒻，不会讲高深的语言，所以尽可能的以通俗易懂的讲法来让朋友们明白，自认为算比较详细的了
## 核心算法：分层图最短路

### 什么是分层图？
顾名思义，你建的图有好几层
### 有什么用？
解决可以使某些边的边权改变的情况
### 具体地？
每层图之间各自连边，与原图一样，在相邻的两层图之间根据原来的关系连边

我们在建图的时候，实际并不需要建多维，我们只要还在一维根据数量关系推算就好了

举个栗子

当有3个点，3层图时

1对应的就是`1+n`和`1+2*n`

2对应的就是`2+n`和`2+2*n`

......

当有n个点，k层图时，不难发现

1对应的（包括自己）就是

$1+n*0$，$1+n*1$，$1+n*2$……$1+n*(k-1)$

其他点也同理

我们每向下一层，就代表我们使用一次免费权，或者说改造这条道路，使其时间为0

**注意，只能从上面的图到下一层，下一层不能回到上一层**

为什么？

因为我们向下一层代表改造一条道路，我们不可能改造道路后再把它修回原来的样子

比如有五个点的图，有两层

那么1~5分别对应第二层的6~10

原图中1与2有连边，那么6与7之间也有连边

1连接2，所以1也连接7，边权为0

如果是双向边，那么**不是7连着1**，而是**2连接着6**


那么最后我们跑一遍最短路，统计所有到n点距离的最小值，就OK了

### 为什么是正确的？
因为我们从上一层下来之后，这条连接两层图的边边权为0，我们没有花费，接着我们还可以向下。

如果已经没有机会了，我们就会还按照原来的路径走完

单源最短路的特点就是，会把所有联通的点走完

那么我们就可以得到**在何时使用免费机会，以及使用多少次的所有情况**，得到正确答案

分层图其实就是暴力与DP的合体（个人见解）

### 细节问题
#### 我们要建多少层？
有k次机会，不难想出，我们要建k+1层
#### 数组开多大？
这是一个坑点，可能有的人直接就开`maxn*(maxk+1)`和`maxm*(maxk+1)`了

我们仔细想一想，点数确实就是k+1层，每层n个点，没问题

但边没有这么简单

k+1层图，每层都有m条边，是`m*(k+1)`

但是，相邻的两层之间还有连边，我们还要加边数

通常，我们选择 `m*(k+1)*4`

#### 最短路？

建议Dijkstra+堆优化

温馨提示：此题卡SPFA，别问我怎么知道的

### 代码实现（详见注释解释）
```cpp
#include<cstdio>
#include<queue>
#define read(x) scanf("%d",&x)//宏定义，个人习惯
#define INF 0x3f3f3f3f//伪极大值
using namespace std;
typedef pair<int,int> pii;//个人习惯
struct Node
{
	int head,dis;
}node[210100];//数组大小注意
struct Edge
{
	int to,len,next;
}edge[4200100];//数组大小注意
int n,m,k,u,v,w,cnt,ans=INF<<1;
void addEdge(int u,int v,int w)
{
	edge[++cnt]={v,w,node[u].head};
	node[u].head=cnt;
}
//链式前向星存图
void Dijkstra()
{
	for(int i=1;i<=n*(k+1);i++)
	{
		node[i].dis=INF;
	}
	//初始化时，要注意我们的点数已经不是n了，而是n*（k+1）
	node[1].dis=0;
	priority_queue<pii,vector<pii>,greater<pii> >q;
	//小根堆
	q.push({0,1});
	while(q.size())
	{
		pii tmp=q.top();
		q.pop();
		int d=tmp.first,u=tmp.second;
		if(d!=node[u].dis)continue;
		for(int e=node[u].head;e;e=edge[e].next)
		{
			int v=edge[e].to;
			if(node[v].dis>edge[e].len+d)
			{
				node[v].dis=edge[e].len+d;
				q.push({node[v].dis,v});
			}
		}
	}
}
//最短路板子不解释
int main()
{
	read(n),read(m),read(k);
	for(int i=1;i<=m;i++)
	{
		read(u),read(v),read(w);
		for(int j=0;j<=k;j++)
		{
			/*
			当j为0时，我们建立的是原图的边
			当j不为0时，我们建立的是分身的边
			 */
			addEdge(u+j*n,v+j*n,w);
			addEdge(v+j*n,u+j*n,w);
			//上面两行是每层图之间，自身的点的连线，边权不变
			if(j==k)break;
			/*
			为什么当j==k时，要退出循环呢？
			因为如果j==k时，还建下面的边，那么就超出范围了
			可以自行感性理解一下
			 */
			addEdge(u+j*n,v+(j+1)*n,0);
			addEdge(v+j*n,u+(j+1)*n,0);
			//这两行建立的是层与层之间的边，边权为0
		}
	}
	Dijkstra();
	//跑最短路
	for(int i=0;i<=k;i++)
	{
		ans=min(ans,node[n+i*n].dis);
		//统计每一层到n距离的最小值
	}
	printf("%d\n",ans);
	//输出答案
	return 0;
}
```
啊，写题解不易，个人认为还算比较详细的，希望能过审

朋友们如果有疑问也可以私聊我或者at我，我会尽一臂之力

---

## 作者：foreverlasting (赞：13)

分层图最短路模板题。

记dis[i][j]为用了j次免费机会到编号为i的点的最短路径长度，vis[i][j]相应的就是（i,j）这个两元组是否在队列中。

简单的跑一下spfa就行。spfa的时候分类讨论一下，要么用免费要么不用。然后这里需要注意一点，必须开**优先队列**，不开就会超时。（幸亏我交完后一秒就发现了。）
```
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
inline int read(){
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return s*w;
}
const int M=5*1e4+10,N=1e4+10,S=50;
int n,m,k,s,t;
struct mdzz1{
    int next,to,val;
}edge[M<<1];
int head[N],cnt;
inline void addedge(res u,res v,res w){
    edge[++cnt].to=v;
    edge[cnt].next=head[u];
    edge[cnt].val=w;
    head[u]=cnt;
}
int dis[N][S],vis[N][S];
struct mdzz{
	int sign,num;
}q[N];
int top;
//用sort的优先队列的常数会小一点...
inline bool cmp(mdzz p,mdzz q) {
    return dis[p.sign][p.num]>dis[q.sign][q.num];
}
#define push(x,y) q[top++]=(mdzz){x,y};push_heap(q,q+top,cmp)
#define pop() pop_heap(q,q+top--,cmp)
#define top() *q
#define empty() (!top)
inline void spfa(){
	memset(dis,inf,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[s][0]=0;
    vis[s][0]=1;
    push(s,0);
    while(!empty()){
    	mdzz u=top();
    	pop();
    	vis[u.sign][u.num]=0;
    	for(res i=head[u.sign];i!=-1;i=edge[i].next){
    		res tox=edge[i].to;
            //不用免费的情况
    		if(dis[tox][u.num]>dis[u.sign][u.num]+edge[i].val){
    			dis[tox][u.num]=dis[u.sign][u.num]+edge[i].val;
    			if(!vis[tox][u.num])push(tox,u.num),vis[tox][u.num]=1;
			}
            //用免费的情况
			if(u.num+1<=k&&dis[tox][u.num+1]>dis[u.sign][u.num]){
				dis[tox][u.num+1]=dis[u.sign][u.num];
				if(!vis[tox][u.num+1])push(tox,u.num+1),vis[tox][u.num+1]=1;
			}	    
		}
	}
}
int main(){
	memset(head,-1,sizeof(head));
    n=read(),m=read(),k=read();
    for(res i=1;i<=m;i++){
    	int x=read(),y=read(),z=read();
    	addedge(x,y,z);
    	addedge(y,x,z);
	}
    s=1,t=n;
    spfa();
    printf("%d",dis[t][k]);
    return 0;
}
```

~~涨了个教训，以后所有最短路都用优先队列。~~

---

## 作者：4biu (赞：8)

这道题有毒！！！！！！！蒟蒻被这道~~破~~题卡了2小时40分钟！！！

原因如下：~~dij的堆写错了~~，这道题是无向图。，。，。。，。

言归正传，蒟蒻不会什么分层图，一眼看上去，这不是dp吗
```
dp[i][j] 表示 经过不超过j条高速公路，从1号点到第i号点的最短路程
```
然后考虑到dp的后效性，本蒟蒻不知怎么脑抽写了个topo排序，然后数据中果然有环。，。，

接着想：那我按什么顺序跑dp？这dp不就像dij中的dis数组吗！

于是我们跑k遍dij
```
j是正在跑第几次dij
dis[i][j] 表示的含义就是dp[i][j]

（代码中用的是dis[i][K]）
if(!vis[v][K]&&dis[v][K]>min(dis[u][K]+w,dis[u][K-1]))
	dis[v][K]=min(dis[u][K]+w,dis[u][K-1]),Q.push(make_pair(dis[v][K],v));
这个转移其实也很明显了，dis[v][j]从dis[u][j]+w或dis[u][j-1]+0(省略了+0) 转移而来
```

最后~~没发现是无向图，下了超大的数据调试~~输出dis[n][k]即可

代码如下（自认为码风还不错）：

（其实不用开longlong 调试的时候开的）
```cpp
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
vector<long long> G[10001],W[10001];
long long vis[10001][21],dis[10001][21];
priority_queue<pair<long long,long long>,vector<pair<long long,long long> >,greater<pair<long long,long long> > > Q;
int main()
{
	int n,m,k;cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;cin>>u>>v>>w;
		G[u].push_back(v);W[u].push_back(w);
		G[v].push_back(u);W[v].push_back(w);
	}
	memset(dis,0x3f3f,sizeof(dis));dis[1][0]=0;
	for(int K=0;K<=k;K++)
	{
		Q.push(make_pair(0,1));
		while(!Q.empty())
		{
			pair<int,int> cur=Q.top();Q.pop();
			int u=cur.second;
			if(vis[u][K])continue;
			vis[u][K]=true;
			if(K>0)dis[u][K]=min(dis[u][K],dis[u][K-1]);
			for(int i=0;i<G[u].size();i++)
			{
				int v=G[u][i],w=W[u][i];
				if(K==0)
				{
					if(!vis[v][K]&&dis[v][K]>dis[u][K]+w)
						dis[v][K]=dis[u][K]+w,Q.push(make_pair(dis[v][K],v));
				}
				else
					if(!vis[v][K]&&dis[v][K]>min(dis[u][K]+w,dis[u][K-1]))
						dis[v][K]=min(dis[u][K]+w,dis[u][K-1]),Q.push(make_pair(dis[v][K],v));
			}
		}
	}
	cout<<dis[n][k];
	return 0;
}
```


---

## 作者：四糸乃 (赞：7)

1. 
题目：一共有M条双向路径，花费时间是Ti，有k次将某一路径花费的时间改为0的权利，问1到n花费的最短时间；
2. 
想法：直接看的网上大佬们的题解。用分层图跑dijkstra。其中dist[i][j]表示已经翻新了j次
道路后到i点的最短路，跑j次dijkstra。OK。
（其实刚开始想到如此跑k次SPFA，然后老板要用dijkstra，再然后没仔细想就看了题解，再然后题解说卡SPFA，就有了下面这个拙劣的东西。）
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#define maxn 100010
using namespace std;
struct node
{
	int val,v,next;
}edge[100010];
int vis[maxn][25],dist[maxn][25],head[maxn];
int tot=0,n,m,t,k; 
void add(int x,int y,int val)
{
	tot++;
	edge[tot].v=y;
	edge[tot].val=val;
	edge[tot].next=head[x];
	head[x]=tot;
	tot++;
	edge[tot].v=x;
	edge[tot].val=val;
	edge[tot].next=head[y];
	head[y]=tot;
}
void dijkstra()
{
	priority_queue <pair<int,int>,
    vector< pair<int,int> >,
	greater < pair<int,int> > >q;
	memset(dist,0x3F,sizeof(dist));
	dist[1][0]=0;
	q.push(make_pair(0,1));
	while(!q.empty())
	{
		int temp=q.top().second;
		q.pop();
		int level=temp/(n+1);temp=temp%(n+1);
		if(vis[temp][level]) continue;
		vis[temp][level]=1;
		for(int i=head[temp];i;i=edge[i].next)
		{
			int cnt=edge[i].v;
			if(dist[temp][level]+edge[i].val<dist[cnt][level])
			{
				dist[cnt][level]=dist[temp][level]+edge[i].val;
				q.push(make_pair(dist[cnt][level],level*(n+1)+cnt));
			}
			if(level==k) continue;
			if(dist[cnt][level+1]>dist[temp][level])
			{
				dist[cnt][level+1]=dist[temp][level];
				q.push(make_pair(dist[cnt][level+1],(level+1)*(n+1)+cnt));
			}
		}
	 } 
}
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z);
	}
	dijkstra();
	cout<<dist[n][k]<<endl;
	return 0;
}
```


---

## 作者：AFO_07 (赞：4)

# 一道神奇的题
一看经过修改k次，典型分层图。

------------
## 分层图应用
把图上一个点的几个状态分成多层，根据此题，每修改一次可以使图往下跑一层，每层内部根据输入数据连接不修改，最后用迪杰斯特拉跑最短路。

------------
## 建图
（借用 @EternalAlexander 这位dalao的OI Painter绘制）：
![](https://cdn.luogu.com.cn/upload/pic/19106.png)
用两层for建图，同层直接连，不同层交叉连。
```cpp
for(int i=1;i<=m;i++) 
	{
		cin>>a>>b>>c;
		if(a==b) continue;
		add(a,b,c);
		add(b,a,c);
		for(int j=1;j<=k;j++)
		{
			add(a+n*(j-1),b+n*j,0);//将上一层a与下一层b相连。
			add(b+n*(j-1),a+n*j,0);//将上一层b与下一层a相连。	
			add(a+n*j,b+n*j,c);
			add(b+n*j,a+n*j,c);
		}
	}
```
------------
## 附上AC代码
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int n,m,k,a,b,c,dis[2000001],head[2000001],cnt,u[2000001];
struct cyf
{
	int to,next,v;
} pre[50000001];
void add(int x,int y,int z)//存图。
{
	cnt++;
	pre[cnt].to=y;
	pre[cnt].next=head[x];
	pre[cnt].v=z;
	head[x]=cnt;
}
priority_queue< pair<int,int> > q;
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++) 
	{
		cin>>a>>b>>c;
		if(a==b) continue;
		add(a,b,c);
		add(b,a,c);
		for(int j=1;j<=k;j++)
		{
			add(a+n*(j-1),b+n*j,0);
			add(b+n*(j-1),a+n*j,0);	
			add(a+n*j,b+n*j,c);
			add(b+n*j,a+n*j,c);
		}
	}
	for(int i=1;i<=k;i++)
    {
        add(n+(i-1)*n,n+i*n,0);
    }
	for(int i=0;i<=n+n*k;i++) dis[i]=999999999;
	dis[1]=0;
	q.push(make_pair(0,1));
		while(q.empty()==0)
    {
        int k1=q.top().second;
        q.pop();
        if(u[k1]==1) continue;
        u[k1]=true;
        for(int i=head[k1];i;i=pre[i].next)
        {
            int ii=pre[i].to;
            if(u[ii]==0&&dis[ii]>dis[k1]+pre[i].v)
            {   
                dis[ii]=dis[k1]+pre[i].v;
                q.push(make_pair(-dis[ii],ii));
            }
        }
    }//迪杰斯特拉堆优化。
	cout<<dis[n+n*k];
}
```
------------
## 完结撒花
~~写的不好勿喷。~~


---

## 作者：ccsc (赞：4)

>如果你知道什么叫做分层图的话那就是个裸题
,否则就是个神题

首先在原图上处理肯定是不好做

那么我们把图分层，具体来说建K+1张原图，图与图之间的边权为0，

具体来说：
	
    k非常小啊，于是可以拆点，把一个点强行拽成k个，然后就可以连边了。怎么连呢？首先原来就有的边是不能不连的，而且还要在每一层图上都连。接下来就要确定每层图之间的关系了，从第i层到第i+1层的边边权全为0，等于说是用掉了一次免费卡，于是愉快的连一连，跑一跑堆优化dijktra，这道题就做完啦。


本题正解：：
	
    分层图最短路，把原图多建k层，若原图中存在edge(u,v)，那么把每层的u都往下一层的v连一条长度为0的有向边，然后跑最短路即可。答案为每一层终点的最短路的最小值


时间复杂度都是O((N+M)log(K*(N+M)))。给出分层图最短路的代码：

code:
```cpp
/*
	Name: 改造路luogu P2939
	Copyright: ccsc;
	Author: ccsc;
	Date: 14-10-19 19:14
	Description: 
*/

# include <bits/stdc++.h>
# define R register int

using namespace std;

int h,n,m,k,s,t,a,b,c,head[220009];
struct edge
{
    int vv,too,nxt;
}g[4200009];
int d[220009];
bool vis[220009];
typedef pair <int,int> pii;
priority_queue <pii,vector<pii>,greater<pii> > q;

void add(int x,int y,int vv)
{
    g[++h].too=y;
    g[h].vv=vv;
    g[h].nxt=head[x];
    head[x]=h;
}

void dis()
{
    memset(d,127,sizeof(d));
    d[s]=0;
    q.push(make_pair(d[s],s));
    int beg,j;
    while (q.size())
    {
        beg=q.top().second;
        q.pop();
        if(vis[beg]) continue;
        vis[beg]=true;
        for (R i=head[beg];i;i=g[i].nxt)
        {
            j=g[i].too;
            if(d[beg]+g[i].vv>=d[j]) continue;
            d[j]=d[beg]+g[i].vv;
            q.push(make_pair(d[j],j));
        }
    }
}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for (R i=1;i<=m;++i)
    {
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
        add(b,a,c);
        for (R j=1;j<=k;++j)
        {
            add(j*n+a,j*n+b,c);
            add(j*n+b,j*n+a,c);
            add((j-1)*n+a,j*n+b,0);
            add((j-1)*n+b,j*n+a,0);
        }
    }
    s=1,t=n;
    dis();
    int ans=d[t];
    for (R i=0;i<=k;++i)
        ans=min(ans,d[i*n+t]);
    cout<<ans;
    return 0;
}
```


---

## 作者：fy0123 (赞：4)

来解释一下分层图是个啥吧（~~其实也只是本蒟蒻瞎想的qwq~~）

就是把原图复制k份，形成一个三维的图形，**同一层**点之间的边权就是原图中的边权，**相邻两层**的点之间的边权都是零。然后dis[i][j]就表示在第j层、1~i的最短路，对于每一个点和其所在层数，有两种转移：1.转移到同层相邻的点 2.转移到下一层相邻的点。跑一个二维dijkstra（加堆优化）就好了。

贴下代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<queue>
#define Pair pair<int, int>
#define F first
#define S second
#define mp make_pair
using namespace std;

const int N = 10010, M = 50010, K = 25;
int n, m, k, cnt;
int head[N], dis[N][K];
bool vis[N][K];

struct Edge{
    int to, nex, v;
}e[M<<1];

inline int read()
{
    char ch = getchar(); int x = 0, flag = 0;
    while (!isdigit(ch)){ if (ch == '-') flag = 1; ch = getchar(); }
    while (isdigit(ch)){ x = x * 10 + ch - '0'; ch = getchar(); }
    return flag ? -x : x;
}

inline void add(int x, int y, int z)
{ e[++ cnt].to = y; e[cnt].v = z; e[cnt].nex = head[x]; head[x] = cnt; }

int main()
{
    n = read(), m = read(), k = read();
    for (int i = 1; i <= m; i ++){
        int x = read(), y = read(), z = read();
        add(x, y, z); add(y, x, z);
    }
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);
    priority_queue<pair<int, Pair> > q;
    q.push(mp(0, mp(1, 0)));
    dis[1][0] = 0;
    while (!q.empty()){
        Pair u = (q.top()).S; q.pop();
        if (vis[u.F][u.S]) continue; vis[u.F][u.S] = 1;
        for (int i = head[u.F]; i; i = e[i].nex){
            int v = e[i].to;
            if (dis[v][u.S] > dis[u.F][u.S]+e[i].v){
                dis[v][u.S] = dis[u.F][u.S]+e[i].v;
                q.push(mp(-dis[v][u.S], mp(v, u.S)));
            }
            if (u.S < k && dis[v][u.S+1] > dis[u.F][u.S]){
                dis[v][u.S+1] = dis[u.F][u.S];
                q.push(mp(-dis[v][u.S+1], mp(v, u.S+1)));
            }
        }
    }
    printf("%d\n", dis[n][k]);
    return 0;
}
```

---

## 作者：dz_ice (赞：3)

今天机房模拟赛的题目，先用爆搜做的，后面去写了dijkstra（~~没想到过掉了~~）

本菜鸡之前并没有学过分层图，所以我感觉用的是dijkstra加动态规划的思想

我们用$dis[i][j]$来表示到从1号牧场到第$i$号牧场升级$j$条路所花的最短时间，设第$x$号牧场与第$i$号牧场相连通，$road(i,x)$表示$i$到$x$的路径长度，从$i$到$x$，要么升级路径，要么就不升级，那么不难发现

$dis[x][j]=min(dis[i][j]+road(i,x),dis[x][j])$

$dis[x][j+1]=min(dis[i][j],dis[x][j+1])$

接下来讲讲我的dijkstra，用$k$个堆来存最小的$dis[i]$，从不升级路径枚举到升级k条路径，下面是这一部分的代码
```
	for(int j=0; j<=k; j++)  //枚举升级路径的条数
	{
		memset(vis,0,sizeof(vis));
		while(!q[j].empty())
		{
			p=q[j].top();
			q[j].pop();
			if(vis[p.a]==0) //未访问过
			{
				vis[p.a]=1;
				for(int i=0; i<l[p.a].size(); i++)
					if(vis[l[p.a][i]]==0)
					{
						son=l[p.a][i]; //与i相连的节点
						if(p.sum+l1[p.a][i]<dis[son][j]) //不升级路径
						{
							dis[son][j]=p.sum+l1[p.a][i];
							node txt;
							txt.a=l[p.a][i],txt.sum=dis[son][j];
							q[j].push(txt);
						}
						if(j!=k&&p.sum<dis[son][j+1]) //升级路径
						{
							dis[son][j+1]=p.sum;
							node txt;
							txt.a=l[p.a][i],txt.sum=dis[son][j+1];
							q[j+1].push(txt);
						}
					}
			}
		}
	}
```

也没什么其他要讲的啦，接下来是全部代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long //注意要long long！！！ 
struct node
{
	int a,sum;
	bool operator<(const node&aaa)const
	{
		return aaa.sum<sum;
	}
} p;
int n,m,k,dis[10003][23],x,y,w,ans=1e9,vis[10003],son;
vector<int>l[10003],l1[10003]; //vector存图
priority_queue<node>q[23]; //用堆优化dijkstra 
signed main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1; i<=m; i++)
	{
		scanf("%d%d%d",&x,&y,&w);
		l[x].push_back(y),l[y].push_back(x),l1[x].push_back(w),l1[y].push_back(w); //存图
	}
	for(int i=1; i<=n; i++)
		for(int j=0; j<=k; j++)
			dis[i][j]=1e9; //记得赋初值
	dis[1][0]=0,p.a=1,p.sum=0;
	q[0].push(p);
	for(int j=0; j<=k; j++)  //枚举升级路径的条数
	{
		memset(vis,0,sizeof(vis));
		while(!q[j].empty())
		{
			p=q[j].top();
			q[j].pop();
			if(vis[p.a]==0) //未访问过
			{
				vis[p.a]=1;
				for(int i=0; i<l[p.a].size(); i++)
					if(vis[l[p.a][i]]==0)
					{
						son=l[p.a][i]; //与i相连的节点
						if(p.sum+l1[p.a][i]<dis[son][j]) //不升级路径
						{
							dis[son][j]=p.sum+l1[p.a][i];
							node txt;
							txt.a=l[p.a][i],txt.sum=dis[son][j];
							q[j].push(txt);
						}
						if(j!=k&&p.sum<dis[son][j+1]) //升级路径
						{
							dis[son][j+1]=p.sum;
							node txt;
							txt.a=l[p.a][i],txt.sum=dis[son][j+1];
							q[j+1].push(txt);
						}
					}
			}
		}
	}
	cout<<dis[n][min(m,k)];
	return 0;
}
```



---

## 作者：交警 (赞：2)

# P2939题解
### 题目传送门：[P2939 改造路](https://www.luogu.org/problemnew/solution/P2939)

这道题第一眼看起来其实觉得有点难，但是仔细一看，其实就是一个分层图的~~假~~紫题。这道题的思路就是分层最短路，就是说多开一维记录机会信息（邻接表），建图时直接简称 $k + 1$层，然后再跑一遍最短路就可以A了。

所以说这道题现在唯一有点难做的地方就是建 $k+1$层图了。

别急，我来教你们

先看这个图：![](https://cdn.luogu.com.cn/upload/image_hosting/bxwy7o68.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这就是一个$k$层图啦~  
每一层与下一层的权值都是 $0$ ，这样做可以在跑最短路的时候直接走改造的路（也就是边权为 $0$ ）。

建 $k+1$层图的代码如下：
```cpp
//链式前向星存图方式
inline void Add ( register int u, register int v, register int w )
{
    Edge[++tot].next = head[u], head[u] = tot, Edge[tot].to = v, Edge[tot].len = w;
}
```

```cpp
//精髓在这里！！！
for ( register int i = 1 ; i <= m ; i ++ )
{
    int u = read(), v = read(), w = read();
    Add ( u, v, w ), Add ( v, u, w );
    for ( register int j = 1 ; j <= k ; j ++ )
    {
    	//每一层内，复制初始的图
        Add ( j * n + u, j * n + v, w ), Add ( j * n + v, j * n + u, w );
        //每一层之间的点边权赋为0，方便直接跑最短路来走改造路
        Add ( ( j - 1 ) * n + u, j * n + v, 0 ), Add ( ( j - 1 ) * n + v, j * n + u, 0 );
    }
}
```
这里的内容其实仔细看起来还是比较浅显易懂的，而且这个存多层图的方式在以后的题目中也可以巧妙地用

既然要存多层图，相应的数组的大小也要有所扩张
```cpp
int head[N*K], dis[N*K];
bool vis[N*K];
struct edge
{
    int next, to, len;
}Edge[M*K<<1];
```

接下来就是跑最短路的过程了。用SPFA的同学，很遗憾，这题会卡SPFA（NOI2018以后，感觉全世界都在卡SPFA）  
有队列优化的$Bellman-Ford$算法其实很优秀，但是它禁不起卡


---
### [SPFA评测 54](https://www.luogu.org/record/24379741)（这个开不开O2都只有54分）
```cpp
//SPFA
inline void SPFA ( register int s )
{
    memset ( dis, 0x7f, sizeof(dis) );
    vis[s] = true;
    queue < int > q;
    q.push ( s );
    dis[s] = 0;
    while ( !q.empty() )
    {
        register int x = q.front();
        q.pop();
        vis[x] = false;
        for ( register int i = head[x] ; i ; i = Edge[i].next )
        {
            register int v = Edge[i].to;
            if ( dis[v] > dis[x] + Edge[i].len )
            {
                dis[v] = dis[x] + Edge[i].len;
                if ( vis[v] == false )
                    q.push ( v );
                vis[v] = true;
            }
        }
    }
}
```

---
### [优化的SPFA评测（双端队列优化deque） 54](https://www.luogu.org/record/24380054)（这个开不开O2也都只有54分）
```cpp
//deque优化的SPFA
inline void SPFA ( register int s )
{
    memset ( dis, 0x7f, sizeof(dis) );
    deque < int > q;
    vis[s] = true;
    q.push_front ( s );
    dis[s] = 0;
    while ( !q.empty() )
    {
        register int x = q.front();
        q.pop_front();
        vis[x] = false;
        for ( register int i = head[x] ; i ; i = Edge[i].next )
        {
            register int v = Edge[i].to;
            if ( dis[v] > dis[x] + Edge[i].len )
            {
                dis[v] = dis[x] + Edge[i].len;
                //重点看这里！！！双端队列优化的SPFA主要实在这个地方有优化
                if ( vis[v] == false )
                    if ( dis[q.front()] > dis[v] )  q.push_front ( v );
                    else q.push_back ( v );
                vis[v] = true;
            }
        }
    }
}
```
---
然而优秀的堆优化的Dijkstra可以完美地跑过去，并且说，这个算法非常的稳定，它不怕被卡，时间复杂度也很优秀（NlogN）。Dijkstra不能处理负边权，所幸这题并没有给到负边权

### [堆优化Dijkstra评测 100](https://www.luogu.org/record/24381332)（这个不一样了，不开O2只有54分，开了O2可以A掉）
```cpp
//堆优化的DIjkstra
inline void Dijkstra ( register int s )
{
    memset ( dis, 0x7f, sizeof(dis) );
    priority_queue < pair < int, int >, vector < pair < int, int > >, greater < pair < int, int > > > q;
    dis[s] = 0;
    q.push ( make_pair ( 0, s ) );
    while ( !q.empty() )
    {
        register int x = q.top().second;
        q.pop();
        if ( vis[x] == true )  continue ;
        vis[x] = true;
        for ( register int i = head[x] ; i ; i = Edge[i].next )
        {
            register int v = Edge[i].to;
            dis[v] = min ( dis[v], dis[x] + Edge[i].len );
            q.push ( make_pair ( dis[v], v ) );
        }
    }
}
```

### 完整代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5, M = 5e5 + 5, K = 25, INF = 2147483647;

inline long long read()
{
    long long f = 1, sum = 0;  char ch = getchar();
    while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
    while ( isdigit(ch) ) { sum = (sum<<1) + (sum<<3) + (ch^48); ch = getchar(); }
    return f * sum;
}

int n, m, k, tot, ans = INF;
int head[N*K], dis[N*K];
bool vis[N*K];
struct edge
{
    int next, to, len;
}Edge[M*K<<1];
priority_queue < pair < int, int >, vector < pair < int, int > >, greater < pair < int, int > > > q;

inline void Add ( register int u, register int v, register int w )
{
    Edge[++tot].next = head[u], head[u] = tot, Edge[tot].to = v, Edge[tot].len = w;
}

inline void Dijkstra ( register int s )
{
    memset ( dis, 0x7f, sizeof(dis) );
    dis[s] = 0;
    q.push ( make_pair ( 0, s ) );
    while ( !q.empty() )
    {
        register int x = q.top().second;
        q.pop();
        if ( vis[x] == true )  continue ;
        vis[x] = true;
        for ( register int i = head[x] ; i ; i = Edge[i].next )
        {
            register int v = Edge[i].to;
            dis[v] = min ( dis[v], dis[x] + Edge[i].len );
            q.push ( make_pair ( dis[v], v ) );
        }
    }
}

int main()
{
    n = read(), m = read(), k = read();//输入
    for ( register int i = 1 ; i <= m ; i ++ )
    {
        int u = read(), v = read(), w = read();//还是输入
        Add ( u, v, w ), Add ( v, u, w );//建单层图
        for ( register int j = 1 ; j <= k ; j ++ )
        {
            Add ( j * n + u, j * n + v, w ), Add ( j * n + v, j * n + u, w );//建多层图
            Add ( ( j - 1 ) * n + u, j * n + v, 0 ), Add ( ( j - 1 ) * n + v, j * n + u, 0 );//层与层之间的处理
        }
    }
    Dijkstra ( 1 );//以1为起点跑最短路
    for ( register int i = 1 ; i <= k + 1 ; i ++ )
        ans = min ( ans, dis[i*n] );//注意！这个最短路不是1-n的最短路，而是要统计1到每一层的n的最短路的最小值，即为答案
    printf ( "%d", ans );
    return 0;
}
```

本蒟蒻太蒻了，只能写出这样的题解了，对比前方dalao的题解，心中自愧不如~~~

---

## 作者：回青绝影 (赞：1)

### 裸的分层图……

但是毒瘤毒瘤毒瘤………………！！！

![](https://www.z4请更换图床a.net/images/2019/10/20/image.md.png)

## 惨死在数组大小上！

###### 也许只有我会在这个地方错了……

------------

[P4822](https://www.luogu.org/problem/P4822)

[P4568](https://www.luogu.org/problem/P4568) <-一毛一样诶！！！

[P1948](https://www.luogu.org/problem/P1948)

[P2939](https://www.luogu.org/problem/P2939) <--毒瘤，卡数组大小

### 4倍经验！


------------

将上下两层之间连上权值为0的边就可以了！

然后就是分层图常规操作了

注意细节！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+1;
struct st{
    int dis,x;
    st (const int a,const int b){
        dis=a;
        x=b;
    }
    bool operator < (const st a)const {
        return dis>a.dis;
    }
};
priority_queue <st> q;
int n,m,cnt,s,t,k;
int nxt[2*N],last[2*N],a[2*N],w[2*N];
int dis[N];
bool l[N];
void add(int x,int y,int z){
    nxt[++k]=last[x];
    last[x]=k;
    a[k]=y;
    w[k]=z;
}
void dijkstra(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    q.push(st(0,s));
    while (!q.empty()){
        while (!q.empty()&&l[q.top().x]) q.pop();
        if (q.empty()) break;
        int x=q.top().x;q.pop();
        l[x]=1;
        for (int i=last[x];i;i=nxt[i]){
            int y=a[i];
            if (dis[y]>dis[x]+w[i]){
                dis[y]=dis[x]+w[i];
                q.push(st(dis[y],y));
            }
        }
    }
}
signed main(){
    scanf("%lld%lld%lld",&n,&m,&cnt);s=1;t=n;
    // for (int i=0;i<n;i++) last[i]=-1;
    for (int x,y,z,i=1;i<=m;i++){
        scanf("%lld%lld%lld",&x,&y,&z);
        add(x,y,z);add(y,x,z);
        for (int j=1;j<=cnt;j++){
            add(x+(j-1)*n,y+j*n,0);
            add(y+(j-1)*n,x+j*n,0);
            add(x+j*n,y+j*n,z);
            add(y+j*n,x+j*n,z);
        }
    }
    for (int i=1;i<=cnt;i++) add(t+(i-1)*n,t+i*n,0);
    dijkstra(s);
    printf("%lld",dis[t+cnt*n]);
    return 0;
}
```


---

## 作者：TheOldDriver (赞：1)

看了看题解，全是分层图 ~~dp的又没有讲到DP的核心状态&转移~~

我却感觉这道题的视为分层图不够合理（P3319的分层图做法更加典型），不如换一种理解方法

设有d数组，用d[z][x]表示在已经免费了z条边时，到x节点的最小时间

### 这时，我们可以把<z,x>二元组视为一个状态，将
```
if(z!=k&&!v[z+1][y]&&d[z+1][y]>d[z][x]) 
	d[z+1][y]=d[z][x];
if(!v[z][y]&&d[z][y]>d[z][x]+f[i].val) 
	d[z][y]=d[z][x]+f[i].val;
```
### 视为状态转移

现在，对DP比较熟悉的同学可能已经想到明白了

对DP不太熟的话，可以先思考图是单链时 其作为背包问题（直接for一遍，考虑免不免费掉每一条边）

再思考图作为树时，其作为树形DP（用dfs代替for）

最后考虑到无向图时，用dijkstra可以解决问题


```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int N=10005,M=50005;
int n,m,t,k,h[N],x,y,z,v[25][N],d[25][N],flag;
struct node{int num,dis,use;}p;
struct edge{int ver,val,next;}f[M*2];
priority_queue<node> q;
priority_queue<int> ans;
bool operator<(node a,node b){return a.dis>b.dis;}
void add(int x,int y,int z){f[++t].ver=y,f[t].val=z,f[t].next=h[x],h[x]=t;}
void dijkstra(int x){
	memset(d,0x3f,sizeof(d));d[0][x]=0;
	p.num=x;p.dis=d[0][x],p.use=0;q.push(p);
	while(q.size()){
		x=q.top().num;int z=q.top().use;q.pop();
		if(v[z][x]) continue;
		v[z][x]=1;
		for(int i=h[x];i;i=f[i].next){
			int y=f[i].ver;
			if(!v[z][y]&&d[z][y]>d[z][x]+f[i].val){
				d[z][y]=d[z][x]+f[i].val;
				p.num=y,p.dis=d[z][y],p.use=z,q.push(p);	
			}
			if(z!=k&&!v[z+1][y]&&d[z+1][y]>d[z][x]){
				d[z+1][y]=d[z][x];
				p.num=y,p.dis=d[z+1][y],p.use=z+1,q.push(p);
			}
		}
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;++i){
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z),add(y,x,z);
	}
	dijkstra(1);
	printf("%d",d[k][n]);
	return 0;
}

```


---

## 作者：Treaker (赞：1)

$$\color{cornflowerblue}{\mathcal{Treaker}}$$
# 分层图最短路

这不就是个分层图裸题嘛。。

$k$很小，那么我们直接分着层连边权为$0$的边就行了。

然后跑$dij$，$spfa$嘛不知道会怎么样，反正关于$spfa$，他已经死了。

推荐一道比较类似的题[P4568 [JLOI2011]飞行路线](https://www.luogu.org/problem/P4568)

两道题基本相同。

完整代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define pa pair<int,int>
#define mp make_pair
using namespace std;
const int N = 210005;
inline int read()
{
    int x = 0 , f = 1;  char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-')  f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
    return x * f;
}
int n , m , K , cnt;
int dis[N] , head[N];
bool vis[N];
struct Edge
{
	int to , dis , nxt;
}e[50002 * 2 * 21 * 2];
inline void add(int u,int v,int w) {e[++cnt] = (Edge){v,w,head[u]}; head[u] = cnt;}
inline void build(int u,int v,int w)
{
	for(int i = 0;i <= K;i ++)
	{
		add(n * i + u,n * i + v,w); add(n * i + v,n * i + u,w);
		if(i != K) add(n * i + u,n * (i + 1) + v,0) , add(n * i + v,n * (i + 1) + u,0);
	}
}
inline void dij()
{
	priority_queue<pa,vector<pa>,greater<pa> > q; memset(dis,0x7f,sizeof dis); dis[1] = 0;
	q.push(mp(dis[1],1));
	while(q.size())
	{
		int now = q.top().second; q.pop();
		if(vis[now]) continue;
		vis[now] = 1;
		for(int i = head[now];i;i = e[i].nxt)
		{
			int to = e[i].to;
			if(dis[to] > dis[now] + e[i].dis)
			{
				dis[to] = dis[now] + e[i].dis;
				q.push(mp(dis[to],to));
			}
		}
	}
}
int main()
{
	n = read(); m = read(); K = read();
	for(int i = 1 , u , v , w;i <= m;i ++)
	{
		u = read(); v = read(); w = read();
		build(u,v,w);
	}
	dij();
	printf("%d\n",dis[n*(K + 1)]);
	return 0;
}
```


---

## 作者：Isprime (赞：1)

## 题解P2939[USACO09FEB]改造路Revamping Trai

[配合Blog食用更佳](https://www.luogu.org/blog/149815/solution-p2939)

[原题传送门](https://www.luogu.org/problem/P2939)

**分层图模板题**

题意简化：有n个点，m条边，求s到t的最短路


原本是这样的（图很丑，请见谅）

![](https://cdn.luogu.com.cn/upload/pic/72236.png)

但题目中多了一个条件：我们至多可以让k条边的权值变为0（不一定要有k条边权值变成0）

这不就是分层图裸题吗，建k层图（因为k≤10，所以并不会占用太大的空间），举个栗子：x和y之间有一条权值为z的边，则第0到k层的x,y之间都要连权值为z的边,第0到k-1层的x或y连到第i+1层的y或x的权值改为0（代表一次免费乘坐飞机）

图就变成了下面这个样子↓

![](https://cdn.luogu.com.cn/upload/pic/72243.png)

~~乱七八糟，看都看不清~~

p.s.图中8和9的编号画反了 ~~，凑合着看吧~~

好吧等有时间了我会改

所以最终答案只需要跑一边Dijkstra再找出dis[i*(n+1)+t]的最小值即为答案

Code
```cpp
#include<cstdio>
#include<queue>
#define ri register int
#define MAXN 10001
#define MAXM 50001
#define INF 2147483647
using namespace std;
int n,m,k,edge_sum;
int head[MAXM*201],dis[MAXN*201];
bool vis[MAXN*201];
struct Edge{
	int next,to,dis;
}edge[MAXM*201];//前向星存图
inline void addedge(int from,int to,int dis){
	edge[++edge_sum].next=head[from];
	edge[edge_sum].dis=dis;
	edge[edge_sum].to=to;
	head[from]=edge_sum;
}
struct Node{
	int u,dis;
	bool operator <(const Node& rhs) const {
        return dis>rhs.dis;
    }
};
inline void dijkstra(){//堆优化Dij
	priority_queue<Node> q;//STL优先队列，用来优化Dij
	q.push((Node){1,0});
	while(!q.empty()) {
		int u=q.top().u;
		q.pop();
		vis[u]=1;
		for(ri i=head[u];i;i=edge[i].next)
			if(!vis[edge[i].to]&&dis[edge[i].to]>dis[u]+edge[i].dis){
				dis[edge[i].to]=dis[u]+edge[i].dis;		
				q.push((Node){edge[i].to,dis[edge[i].to]});
			}
	}
}
int main()
{
	scanf("%d %d %d",&n,&m,&k);
    for(ri i=1;i<=m;i++)
    {
    	int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        for(ri j=0;j<=k;j++) addedge(j*n+x,j*n+y,z),addedge(j*n+y,j*n+x,z);//因为是无向图所以存两次
        for(ri j=0;j<k;j++) addedge(j*n+x,(j+1)*n+y,0),addedge(j*n+y,(j+1)*n+x,0);//存第i层的x(y)和第i+1层的y(x)之间的边
    }
    for(ri i=1;i<=n*k+n;i++) dis[i]=INF;//初始值赋为INF
    dis[1]=0;
    dijkstra();//Dij求最短路
    int min=INF;
    for(ri i=0;i<=k;i++) if(min>dis[i*n+n]) min=dis[i*n+n];//寻找最优解
    printf("%d\n",min);
    return 0;
}

```
# 珍爱生命，远离抄袭

# 说句闲话：研究分层图的最好方法是
### A了2939,再A了4568，还要A了4822
**祝你们成功 (滑稽**

AC紫题+=3;

我都告诉你这么多了，不点个赞？

---

## 作者：Kendrick_Z (赞：1)

个人博客：[点一下玩一年](https://www.luogu.org/blog/142373/)

这题大概看了看数据范围（k）

其实这道题看起来也是一个普通的最短路问题

但是我们分析一下题目

我们有k个操作

是可以免费

那么我们第一种思路就是简单的暴力枚举

枚举哪一种不选

然后最后取一个最小值

这种算法十分暴力 只能得到局部分数

那我们来考虑正解

正解就是分层图算法

我们建立一个分层图一共有k层

第i层表示选择i次免费航线

那么我们在执行最短路的时候我们可以进行一次抉择（类似于动态规划）

到当前这一阶段时我们是否要进行使用免费航行

然后最后选择一个到终点的最优解就可以了

建图过程就是先正常建图

然后在不同的层之间建立一条免费航线 代表选择免费航行

那么的话我们建图跑一个最短路

鉴于SPFA这个半死不活的算法 我们考虑用dij+堆优化

这样的话就可以十分优秀的通过这个

希望大家打代码的时候可以细心点！！！

这样的话就不会平白的出现一堆诡异的错误（比如像我一样 没输入m,k结果大胆提交

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e7;
const int INF =0X3F3F3F3F;
inline int Min(int x,int y){
	return x<y?x;y;
}
struct edge{
	int next,to,w;
}e[N<<1];
int head[N],cnt,dis[N],n,m,k;
bool vis[N];
inline void add(int x,int y,int w){
	e[++cnt].next=head[x];
	e[cnt].to=y;
	e[cnt].w=w;
	head[x]=cnt;
}
priority_queue<pair<int ,int >,vector<pair<int ,int > >,greater<pair<int,int > > >q;//小根堆 
inline void dij(){//dij+堆优化 
	memset(dis,INF,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[1]=0;
	q.push(make_pair(dis[1],1));
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=true;
		for(int i=head[u];i;i=e[i].next){
				int v=e[i].to;
				int w=e[i].w;
				if(dis[v]>dis[u]+w){
					dis[v]=dis[u]+w;
					q.push(make_pair(dis[v],v));
			}
		}
	} 
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
		for(int j=1;j<=k;j++){
			add(u+(j-1)*n,v+j*n,0);//分层图建图 从当前层到下一层免费 
			add(v+(j-1)*n,u+j*n,0);
			add(u+j*n,v+j*n,w);
			add(v+j*n,u+j*n,w); 
		}
	}
	dij();
	int ans=0x7f7f7f7f;
	for(int i=0;i<=k;i++){
		ans=Min(ans,dis[i*n+n]);//枚举最小值 
	} 
	printf("%d",ans);
	return 0;
}
```

大概都在代码里 个人认为码风还是不错的....

**写在后面：**

分层图其实比较好理解

关键是和其他图论算法的结合

能否成功的建立模型 然后就可以进行最短路 网络流等算法

同时如果开一维数组dis

记得控制好空间！！！

不要MLE也不要RE!!!!



---

## 作者：zzr8178541919 (赞：0)

本道题是分层图最短路的模板题。

那么所谓的分层图最短路呢，它的特定的形式就是在dis的数组上多加上了一维。

从而实现了二维的最短路。

dis[i][j]指的就是在第j层，到达第i个节点的最短路。
dis[i][j]从而可以从dis[i][j-1]和dis[i][j]转移过来。

当然dp[i][j-1]的转移是有条件的，必须满足在k的限制之内。k在这里指的就是分层图中的层数。

注意：本体用spfa会超时两个点，建议用堆优化dij。在分层图下，堆优化的dij仍然可以使用。即按dis的大小从小到大排序。

具体的过程可以见代码：
```cpp

//本道题目是分层图最短路的模板题。
//是一道很好的练习题。 

#include<cmath>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#include<vector>
#define int long long
using namespace std;
struct vode
{
	int to;
	int next;
	int dis;
}edge[200005];
int wugui=0;
int head[200005];
int dp[50005][25];
void add(int x,int y,int d)
{
	wugui++;
	edge[wugui].to=y;
	edge[wugui].next=head[x];
	edge[wugui].dis=d;
	head[x]=wugui;
}
int n,m,k;
int vis[200005][35];

struct node{
	int dis;
	int times;
	int num;
};

priority_queue<node> q;

bool operator<(node x,node y)
{
	return x.dis>y.dis;
}

void spfa()
{
	dp[1][0]=0;
	node p;
	p.num=1;
	p.dis=0;
	p.times=0;
	q.push(p);
	while(!q.empty())
	{
		node point=q.top();
		q.pop();
		if(vis[point.num][point.times]==1)
		continue;
		vis[point.num][point.times]=1;
		for(int i=head[point.num];i;i=edge[i].next)
		{
			int t=edge[i].to;
			if(dp[t][point.times+1]>dp[point.num][point.times] && point.times<k)
			{
				dp[t][point.times+1]=dp[point.num][point.times];
				node p1;
				p1.num=t;
				p1.dis=dp[t][point.times+1];
				p1.times=point.times+1;
				q.push(p1);
			}
			if(dp[t][point.times]>dp[point.num][point.times]+edge[i].dis)
	    	{
			    dp[t][point.times]=dp[point.num][point.times]+edge[i].dis;
			    node p2;
			    p2.num=t;
			    p2.dis=dp[t][point.times];
			    p2.times=point.times;
			    q.push(p2);
		    }
		}
	}
}
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	int ans=0x3f3f3f3f;
	memset(dp,0x3f3f3f3f,sizeof(dp));
	spfa();
	for(int i=0;i<=k;i++)
	{
		ans=min(ans,dp[n][i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：EarthGiao (赞：0)

## 【思路】
分层图 + dijkstra     
一道分层图的裸题     
如果想了解分层图请看这里   
[了解分层图](https://www.cnblogs.com/acioi/p/11716483.html) 
 
## 【题目大意】 
从1到n跑    
其中可以让k条路的耗时变为0   
求最小耗时    

###【题目分析】
可以免去k条路    
如果你是因为看到了电话线那道题里面四倍经验的帖子   
所以才来做的这个题    
那你有可能失望而归了   
因为做电话线的大部分都是用的二分答案+SPFA   
那里面的三道题的确都是和电话线一个知识点   
不过这个知识点不是二分答案+SPFA而是分层图   
分层图就是专门针对这种可以免去k条路问题的   
不过需要开很大的内存   
想了解分层图的话请看上面那个链接或者去看其他大佬的博客   

### 【核心思路】
将题目给出的图建立k个    
然后两个图之间连接的路都标为0   
因为这两个图之间的路就是那高速路   
第i个图就是建立i条高速路的情况   
然后就是裸着跑dijkstra就好了   
最后比较用了1-k条高速公路到达n掉里面花费最少的输出就完结撒花！！！     
## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>

using namespace std;
const int Max = 4200005;
const int M = 420005;
struct point
{
	int w;//路径的长度 
	int x;//点的标号 
	bool operator < (const point & xx)const
	{
		return xx.w < w;
	}
};
struct node
{
	int y,ne,z;
}a[Max];
int sum = 0,head[M];
void add(int x,int y,int z)
{
	a[++ sum].y = y;
	a[sum].ne = head[x];
	a[sum].z = z;
	head[x] = sum;
}
priority_queue<point>q;
int d[M];
bool use[M];
void dj()
{
	memset(d,0x3f,sizeof(d));
	d[1] = 0;
	q.push((point){0,1});
	while(!q.empty())
	{
		point qwq = q.top();
		q.pop();
		int x = qwq.x,w = qwq.w;
		if(use[x] == true)
			continue;
		else
			use[x] = true;
		for(register int i = head[x];i != 0;i = a[i].ne)
		{
			int awa = a[i].y;
			if(d[awa] > d[x] + a[i].z)
			{
				d[awa] = d[x] + a[i].z;
				if(use[awa] == false)
					q.push((point){d[awa],awa});
			}
		}
	}
}

int main()
{
	freopen("walk.in","r",stdin);
	int n,m,k;
	cin >> n >> m >> k;
	for(register int i = 1;i <= m;++ i)
	{
		int x,y,z;
		cin >> x >> y >> z;
		add(x,y,z),add(y,x,z);
		for(register int j = 1;j <= k;++ j)
		{
			add(j * n + x,j * n + y,z);
			add(j * n + y,j * n + x,z);
			add((j - 1) * n + x,j * n + y,0);
			add((j - 1) * n + y,j * n + x,0);
		}
	}
	dj();
	int M = 0x7fffffff;
	for(register int i = 0;i <= k;++ i)
		M = min(M,d[i * n + n]);
	cout << M << endl;
	return 0;
}
```

---

## 作者：BinDir0 (赞：0)

## 分层图+堆优化的题

分层图，顾名思义就是将图分层，每一层代表一个不同状态。如本题中的一层就代表修建一次高速公路（或说将一条路免费），连接每一层图的则是边权为0的单向边。

因为我们并不需要将修建高速公路的机会使用完，所以最终答案应从每一层的节点N中找。

为了不T掉，我们要用堆优化降低复杂度。

因此思路如下：

- 根据题意建立k+1层，每层n个节点的分层图；
- 堆优化DIJ遍历；
- 在每一层的节点n中取最小值作为答案输出。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,s,t,w[100100],fst[100100],nex[100100],v[100100],dis[32][10100],a,b,c,tot,vis[32][10100];
struct item
{
    int lev,d,x;
    bool operator< (const item &x) const
    {
        return d>x.d;
    }
};
priority_queue<item>q;
void add(int a,int b,int c)
{
    nex[++tot]=fst[a];
    w[tot]=c;
    v[tot]=b;
    fst[a]=tot;
    return ;
}
void dij()
{
    dis[0][s]=0;
    q.push((item){0,0,s});
    while(!q.empty())
    {
        int x=q.top().x,d=q.top().d,lev=q.top().lev;
        //cout<<lev<<" "<<x<<" "<<d<<" "<<vis[lev][x]<<endl;
        //system("pause");
        q.pop();
        if(vis[lev][x])
        continue;
        vis[lev][x]=1;
        for(int i=fst[x];i!=-1;i=nex[i])
        {
            if(!vis[lev][v[i]]&&d+w[i]<dis[lev][v[i]])
            {
                dis[lev][v[i]]=d+w[i];
                q.push((item){lev,d+w[i],v[i]});
            }
            if(!vis[lev+1][v[i]]&&d<dis[lev+1][v[i]]&&lev+1<=k)
            {
                dis[lev+1][v[i]]=d;
                q.push((item){lev+1,d,v[i]});
            }
        }
    }
    return ;
}
int main()
{
    memset(fst,-1,sizeof(fst));
    memset(dis,0x7f/3,sizeof(dis));
    cin>>n>>m>>k;
    s=1;t=n;
    for(int i=1;i<=m;i++)
    {
    	scanf("%d%d%d",&a,&b,&c);
    	add(a,b,c);
    	add(b,a,c);
    }
    dij();
    int ans=1e8;
    for(int i=0;i<=k;i++)
    {
    	ans=min(ans,dis[i][t]);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：万弘 (赞：0)

分层图，不知道什么是分层图可以看一下[这题](https://www.luogu.org/problemnew/show/P1073)和我的[这篇题解](https://www.luogu.org/blog/73142/solution-p1073)

简单的说，就是将原图复制k分，第k个图表示经过k次转移后的状态（此题中转移即为走过的高速公路条数），再把这些图用某些方法连接，最后看成整体跑一些算法

回到此题：  
1.对于每一条边$(u,v,w)$，在k+1个图上分别存储（即走小路），之后跨一层图存储（这条边边权为0，即走高速公路）  
2.以1为起点跑最短路，输出到终点(n*(k+1))的最短距离

时间：$O(mklogn)$,空间$O(mk)$，不是非常优

**注：无向图！存两遍！**

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
typedef int ll;//本来想用long long，但怕爆空间
#define maxn 404020//我用邻接表，所以要多开几倍空间
#define maxm 5050040
ll n,m,k;
struct Edge
{
	ll v,w,nxt;
}e[maxm];
ll cnt,last[maxn];
void adde(ll u,ll v,ll w)
{
	for(ll i=0;i<=k;++i)
	{
		++cnt;//每个图中存边
		e[cnt].v=v+i*n;
		e[cnt].w=w;
		e[cnt].nxt=last[u+i*n];
		last[u+i*n]=cnt;
		if(i==0)continue;
		++cnt;//跨图存边
		e[cnt].v=v+i*n;
		e[cnt].w=0;
		e[cnt].nxt=last[u+(i-1)*n];
		last[u+(i-1)*n]=cnt;
	}
}

struct node//接下来是Dij模板了
{
	ll u,dis;
	bool operator <(const node& v)const
	{
		return dis>v.dis;
	}
};
std::priority_queue<node>q;
ll dis[maxn];
void Dij()
{
	for(ll i=1;i<=n*(k+1);++i)dis[i]=1<<30;
	dis[1]=0;
	q.push(node{1,0});
	ll u,v,w;
	node t;
	while(!q.empty())
	{
		t=q.top();q.pop();
		u=t.u;
		if(dis[u]<t.dis)continue;
		for(ll i=last[u];i;i=e[i].nxt)
		{
			v=e[i].v,w=e[i].w;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				q.push(node{v,dis[v]});
			}
		}
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	ll u,v,w;
	for(ll i=1;i<=m;++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		adde(u,v,w);
		adde(v,u,w);//存两遍
	}
	Dij();
	printf("%d",dis[n*(k+1)]);//复制k次，所以有k+1个图
	return 0;
}
```

---

## 作者：Waddles (赞：0)

~~蒟蒻根本不知道分层图是什么qwq~~

一开始看题，感觉有点像A journey to Greece，想到了一个状态，dp[i][k]表示到第i个牧场用了k此修改的最短路长度，很容易想到
```
dp[i][k]=min(dp[j][k]+dis[i][j],dp[j][k-1]);

```

但因为此题是个无向图（好像没有环吧），想理个拓扑序上dp，~~（可能是我太弱了）~~ 用dp搞不起来

然后想到最短路径的dijkstra算法，感觉本质上和这个差不多，每次松弛节点的时候类似上面的dp方程转移最短路，就AC了

~~所以这题是个dp思想的dijkstra~~

PS：有同学说我yy出了分层图，我。。。。。

下面是code:

```
#include<map>
#include<cmath>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
template<class Read>void in(Read &x){
    x=0;
    int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        f|=(ch=='-');
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x=f?-x:x;
    return;
}
struct Node{//链式前向星存图
    int to;
    int next;
    int sum;
}a[100005];
struct Queue{//dijkstra优先队列
    int x;//牧场编号
    int k;//改的路径个数
    ll c;//目前最短路
    bool operator < (Queue node) const{
        return c>node.c;
    }
}l,r;
priority_queue<Queue>q;
int n,m,k,top,head[10005];
ll f[10005][25];
void add(int x,int y,int c){
    a[++top].next=head[x];
    a[top].to=y;
    a[top].sum=c;
    head[x]=top;
}
int main(){
    in(n);in(m);in(k);
    for(int i=1;i<=n;i++){//初始化
        for(int j=0;j<=k;j++){
            f[i][j]=1ll<<62;
        }
    }
    for(int i=1;i<=m;i++){
        int x,y,c;
        in(x);in(y);in(c);
        add(x,y,c);
        add(y,x,c);
    }
    f[1][0]=0;
    l.x=1;
    l.c=0;
    l.k=0;
    q.push(l);
    while(!q.empty()){//开始dijkstra
        l=q.top();
        q.pop();
        if(f[l.x][l.k]!=l.c)continue;
        for(int i=head[l.x];i;i=a[i].next){
            int y=a[i].to;
            if(f[y][l.k]>f[l.x][l.k]+a[i].sum){//这条路不改
                f[y][l.k]=f[l.x][l.k]+a[i].sum;
                r.x=y;
                r.k=l.k;
                r.c=f[y][l.k];
                q.push(r);
            }
            if(l.k==k)continue;//改满k条就不能再改了
            if(f[y][l.k+1]>f[l.x][l.k]){//这条路改
                f[y][l.k+1]=f[l.x][l.k];
                r.x=y;
                r.k=l.k+1;
                r.c=f[y][l.k+1];
                q.push(r);
            }
        }
    }
    ll ans=1ll<<62;
    for(int i=0;i<=k;i++)ans=min(ans,f[n][i]);//求最短距离
    printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：01190220csl (赞：0)

分层图是什么？我这个~~连NOIP2018D2T3暴力都会爆零，结果只有360的~~蒟蒻完全不知道。

下面讲讲DP：

用$f[i][j]$表示从$1$号点出发，恰好经过$j$条高速公路，到达$i$点的最短路径长。现在要求的就是$f[n][k]$。

转移：分两种情况：

1.先经过$j-1$条高速公路，到达$i$旁边的一个节点，然后用一次高速公路。

2.先经过$j$条高速公路，到达$i$旁边的一个节点，然后直接走到$i$。

$f[i][j]=\displaystyle\min_{(u,i)\subseteq E}(\min(f[u][j-1],f[u][j]+w[u][i]))$

但是还有一个问题：样例中$f[2][2]$（先不管是否有用)是长什么样子的？

等待揭晓答案：

没有意义。

事实上，从$1$到$2$只需要一条高速公路就可以瞬时到达，强制经过恰好两条，当然没有意义（就当没有它）。

定义$len[i]$为从$1$到$i$需经过的至少边数（与权值无关），当$k>len[i]$时，$f[i][k]$当然没有意义。$len[i]$可以用一次BFS求出，然后就有下面的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
vector<pair<int, int> > edge[10001];
int len[10001], dis[10001][21];
bool visit[10001];
void bfs() {
	memset(len, 0x3f, sizeof(len));
	memset(visit, 0, sizeof(visit));
	len[1] = 0;
	queue<int> q;
	q.push(1);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		visit[u] = 1;
		for (int i = 0; i < edge[u].size(); i++) {
			int v = edge[u][i].first;
			if (len[u] + 1 < len[v]) {
				len[v] = len[u] + 1;
				q.push(v);
			}
		}
	}
}
int main() {
	int m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) {
		int p1, p2, t;
		cin >> p1 >> p2 >> t;
		edge[p1].push_back(make_pair(p2, t));
		edge[p2].push_back(make_pair(p1, t));
	}
	bfs();
	if (len[n] <= k) {
		cout << 0 << endl;
		return 0;
	}
	memset(dis, 0x3f, sizeof(dis));
	dis[0][0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < edge[i].size(); j++)
			dis[i][0] = min(dis[i][0], dis[edge[i][j].first][0] + edge[i][j].second); 
	for (int l = 1; l <= k; l++)
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < edge[i].size(); j++)
				dis[i][l] = min(dis[i][l], min(dis[edge[i][j].first][l-1], dis[edge[i][j].first][l] + edge[i][j].second)); 
	cout << dis[n][k] << endl;
} 
```

然后，把这段代码交上去，你就拿到了[9分的好成绩](https://www.luogu.org/recordnew/show/14319443)。

不对呀，转移没错呀，也没打错呀？

那是~~你没开long long~~转移有后效性。

所以白讲了？

当然不会。先对每个点处理出转移的第一种情况。然后考虑$len[i]=k$的部分，毫无疑问，$f[i][k]$都等于$0$。这些点当然都能转移。转移到的点中，最小的当然也是对的（还能变得更小吗），然后用这个点转移，再取下一次最小的，然后会发现这就是Dijkstra。$n$遍Dijkstra就能解决问题。

坑点：有些点的最优解在第一种情况，在首次进入时别忘了加入优先队列。

正确的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
vector<pair<int, int> > edge[10001];
int len[10001], dis[10001][21];
bool visit[10001];
void bfs() {
    memset(len, 0x3f, sizeof(len));
    memset(visit, 0, sizeof(visit));
    len[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visit[u] = 1;
        for (int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i].first;
            if (len[u] + 1 < len[v]) {
                len[v] = len[u] + 1;
                q.push(v);
            }
        }
    }
}
void dijkstra(int k) {
    memset(visit, 0, sizeof(visit));
    priority_queue<pair<int, int> > q;
    for (int i = 1; i <= n; i++)
        if (len[i] == k)
            q.push(make_pair(0, i));
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (visit[u]) continue;
        visit[u] = 1;
        for (int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i].first;
            if (edge[u][i].second + dis[u][k] < dis[v][k]) {
                dis[v][k] = edge[u][i].second + dis[u][k];
                q.push(make_pair(-dis[v][k], v));
            }
            else if (!visit[v]) q.push(make_pair(-dis[v][k], v));
        }
    }
}
int main() {
    int m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int p1, p2, t;
        cin >> p1 >> p2 >> t;
        edge[p1].push_back(make_pair(p2, t));
        edge[p2].push_back(make_pair(p1, t));
    }
    bfs();
    if (len[n] <= k) {
        cout << 0 << endl;
        return 0;
    }
    memset(dis, 0x3f, sizeof(dis));
    dis[1][0] = 0;
    dijkstra(0);
    for (int i = 1; i <= k; i++) {
        for (int u = 1; u <= n; u++) {
            if (len[u] <= i) {
                dis[u][i] = 0;
                continue;
            }
            for (int j = 0; j < edge[u].size(); j++) dis[u][i] = min(dis[u][i], dis[edge[u][j].first][i-1]);
        }
        dijkstra(i);
    }
    cout << dis[n][k] << endl;
} 
```

---

## 作者：joseph_cheung (赞：0)

贴一份使用STL优先队列以及Dijkstra跑拆点分层图的代码
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <functional>
using namespace std;
#define pb push_back
#define fi first
#define sc second
#define ll long long
#define elif else if
typedef pair<int,int> P;
#define FR(i,o,n) for(register int i=(o);i<(n);++i)
#define FE(i,o,n) for(register int i=(o);i<=(n);++i)
#define DR(i,o,n) for(register int i=(o);i>(n);--i)
#define DE(i,o,n) for(register int i=(o);i>=(n);--i)
#define RG register
inline int GetInt()
{
	char ch=getchar();int f=1,ret=0;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=getchar();}
	return f*ret;
}
#define In GetInt()
const int MAXN = (10000+10)*(20+1), INF = 0x3f3f3f3f;
int n,m,x,dis[MAXN];bool vis[MAXN];
vector<P> g[MAXN];
void Dijkstra(vector<P> *G,int *DIS,int S)
{
	priority_queue<P,vector<P>,greater<P> > q;
	memset(dis,0x3f,sizeof(dis));
	dis[S]=0;q.push(P(0,S));
	while(!q.empty())
	{
		P p=q.top();q.pop();
		int u=p.sc,siz=G[u].size();
		if(vis[u])continue;
		vis[u]=1;
		FR(i,0,siz)
		{
			P e=G[u][i];
			if(!vis[e.fi]&&DIS[u]+e.sc<DIS[e.fi])
			q.push(P(DIS[e.fi]=DIS[u]+e.sc,e.fi));
		}
	}
}
int main()
{
	int n=In,m=In,k=In;
	FE(i,1,m)
	{
		int u=In,v=In,w=In;
		g[u].pb(P(v,w)),g[v].pb(P(u,w));
		FE(j,1,k)
		{
			g[j*n+u].pb(P(j*n+v,w));
			g[j*n+v].pb(P(j*n+u,w));
			g[(j-1)*n+u].pb(P(j*n+v,0));
			g[(j-1)*n+v].pb(P(j*n+u,0));
		}
	}
	Dijkstra(g,dis,1);
	int ans=dis[n];
	FE(i,1,k)ans=min(ans,dis[(i+1)*n]);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：小泉花阳 (赞：0)

学校的OJ这题不上ctime卡时会超时=。=不过洛谷倒是不用卡。简单的思路就是分层图二维dijkstra，第二维表示当前修了多少传送门（并不），实现起来应该大部分人都会写就不讲解了。学校的数据似乎把SPFA卡了

```cpp
#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
#include<iostream>
#include<cstring>
#include<ctime>
#define mp make_pair
using namespace std;
typedef pair<int,int> pp;
vector<pp>G[10010];
priority_queue<pair<int,pair<int,int> > >Q;
const int inf=0x3c3c3c3c;
int n,m,k;
int dis[10010][21],ans;
inline void Read(int& x,bool mark=0){  
    char tt=getchar();  
    for(;tt<'0'||'9'<tt;tt=getchar()) if(tt=='-') mark=1;  
    for(x=0;'0'<=tt&&tt<='9';x=(x<<1)+(x<<3)+tt-'0',tt=getchar());  
    x=mark?-x:x;  
}
inline int mmin(int a,int b){
    return a<b?a:b;
}
void dijkstra_heap(){
    vector<pp>::iterator it;
    int i,j,x,y,mindis,len,num;
    memset(dis,0x3c,sizeof(dis));
    dis[1][0]=0;
    Q.push(mp(-dis[1][0],mp(1,0)));
    while(!Q.empty()){
        if(clock()>1100) return;
        x=Q.top().second.first;
        num=Q.top().second.second;
        mindis=-Q.top().first;
        Q.pop();
        if(mindis!=dis[x][num]) continue;
        for(it=G[x].begin();it!=G[x].end();it++){
            y=it->second,len=it->first;
            if(num<k&&mindis<dis[y][num+1]){  
                dis[y][num+1]=mindis;
                Q.push(mp(-dis[y][num+1],mp(y,num+1)));
            }
            if(dis[y][num]>dis[x][num]+len){
                dis[y][num]=dis[x][num]+len;
                Q.push(mp(-dis[y][num],mp(y,num)));
            }
        }
    }
}
int main(){
    int x,y,i,z;
    Read(n);
    Read(m);
    Read(k);
    for(i=1;i<=m;i++){
        Read(x);
        Read(y);
        Read(z);
        G[x].push_back(mp(z,y));
        G[y].push_back(mp(z,x));
    }    
    dijkstra_heap();
    ans=inf;
    for(i=1;i<=k;i++)  
        ans=mmin(ans,dis[n][i]);
    printf("%d\n",ans);
}

```

---

