# Buy a Ticket

## 题目描述

Musicians of a popular band "Flayer" have announced that they are going to "make their exit" with a world tour. Of course, they will visit Berland as well.

There are $ n $ cities in Berland. People can travel between cities using two-directional train routes; there are exactly $ m $ routes, $ i $ -th route can be used to go from city $ v_{i} $ to city $ u_{i} $ (and from $ u_{i} $ to $ v_{i} $ ), and it costs $ w_{i} $ coins to use this route.

Each city will be visited by "Flayer", and the cost of the concert ticket in $ i $ -th city is $ a_{i} $ coins.

You have friends in every city of Berland, and they, knowing about your programming skills, asked you to calculate the minimum possible number of coins they have to pay to visit the concert. For every city $ i $ you have to compute the minimum number of coins a person from city $ i $ has to spend to travel to some city $ j $ (or possibly stay in city $ i $ ), attend a concert there, and return to city $ i $ (if $ j≠i $ ).

Formally, for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938D/035d166bda223ecd5c31eb614a76bdcc9b8fe8c4.png) you have to calculate ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938D/f2e29a8bb6e05026242d6e3afeeabb7241997635.png), where $ d(i,j) $ is the minimum number of coins you have to spend to travel from city $ i $ to city $ j $ . If there is no way to reach city $ j $ from city $ i $ , then we consider $ d(i,j) $ to be infinitely large.

## 样例 #1

### 输入

```
4 2
1 2 4
2 3 7
6 20 1 25
```

### 输出

```
6 14 1 25 
```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 1
1 3 1
30 10 20
```

### 输出

```
12 10 12 
```

# 题解

## 作者：傅思维666 (赞：16)


## 题解：

推荐博客食用，口味更佳：

[本蒟蒻的博客](https://www.cnblogs.com/fusiwei/p/11673568.html)

这道题稍微有一点歧义（我是说翻译）。

正常人看这个翻译，都不会考虑返程的情况，即不会把路径乘以2.这是可以理解的。因为翻译上确实没有说看完演唱会还要回来。但是原题上有很清晰的说明：$min^n_{j=1}2d(i,j)+a_j$。

我个人认为，看了这个式子之后，整个题的正解就差不多出来了。

我们暴力的想法就是：对每一个点跑单源最短路，然后统计最短的。但这道题的数据范围显然不支持这种思路：即使你用任意的最短路算法，加各种优化甚至卡常，都卡不过这个数据范围。

我是看过英语题面之后才看明白正解的思路的：我们发现：这题的数据范围是标准的跑一遍最短路的数据范围。所以我们把思路向只跑一遍最短路靠拢。根据上面的式子，我们发现，只要我们再把每个点的点权也包含进最短路算法的求解范围，那么就完全可以用一次最短路算法解决这个问题。然后我们想到把点权化边权，但这并不能保证原图的正确性（这是显然的）。

在我们迷之蒙圈不知干啥的时候，请让我来介绍一下正解。

**建立虚拟源点**。

这的确是一种好用的小技巧。前面的两路大神也解释的比较清晰。但是作为一名蒟蒻，我在第一次接触到这个技巧的时候还是蒙圈了。所以我来用对新手友好的方式解释一下这种思路。

设想一下，现在有一张图，源点是确定的，我们**不考虑路径上的点权，只考虑终点的点权**（注意，这是使用虚拟源点法的一个重要前提！）。那么，我们就可以在每个点上再引出一条边，这条边的边权就是这个点的点权。这样的化，我们就相当于多走了一条边，但是答案依然是正确的（因为那条边就是那个点权）。

可是，这样做会导致一个后遗症：终点不再确定。

怎么解决这个问题呢？很好办，我们把所有边的“新加出”的这条边的去向汇成一个点，这个点就是我们所说的“虚拟源点”。那么，我们从这个点开始跑最短路，所得出的每个点的答案就是真正的答案。

画个图应该会很好想。

看代码可能会更好想：

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#define ll long long
using namespace std;
const int maxn=2*1e5+1;
priority_queue<pair<ll,int> >q;
int n,m;
int head[maxn],nxt[maxn*3],to[maxn*3],tot,v[maxn];
ll val[maxn*3];
ll dist[maxn];
void add(int x,int y,ll z)
{
    to[++tot]=y;
    val[tot]=z;
    nxt[tot]=head[x];
    head[x]=tot;
}
void dijkstra()
{
    memset(dist,0x3f,sizeof(dist));
    dist[0]=0;
    q.push(make_pair(0,0));
    while(!q.empty())
    {
        int x=q.top().second;
        if(v[x])
        {
            q.pop();
            continue;
        }
        x=q.top().second;q.pop();v[x]=1;
        for(int i=head[x];i;i=nxt[i])
        {
            int y=to[i];
            if(dist[y]>dist[x]+val[i])
                dist[y]=dist[x]+val[i],q.push(make_pair(-dist[y],y));
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)   
    {
        int u,v;ll w;
        scanf("%d%d%lld",&u,&v,&w);
        add(u,v,w * 2);
        add(v,u,w * 2);
    }
    for(int i=1;i<=n;i++)
    {
        ll w;
        scanf("%lld",&w);
        add(0,i,w);
    }
    dijkstra();
    for(int i=1;i<=n;i++)
        printf("%lld ",dist[i]);
    return 0;
}
```

注意：开Longlong，边权要乘二倍。

---

## 作者：Mr_think (赞：10)

## [CF938D Buy a Ticket](https://www.luogu.com.cn/problem/CF938D)

## 题目大意：

有一个乐队要开演唱会，在  $n$ 个城市的人都想去听，但每个城市票价不同，而他们都想少花钱。给定  $m$ 条路，包含  $u$,  $v$,  $w$ 表示从城市  $u$ 到城市  $v$ 要花  $w$ 元，再给出演唱会在  $i$ 城市的票价  $a[i]$，求每个人去听演唱会**并回来**的最小花费。

## solution:

暴力地去想，我们可以从  $i$ 出发求到城市  $j$ 的最短路加上城市  $j$ 的票价  $a[i]$ 取一个  $\min$ 就可以求出此人的最小花费，时间复杂度爆炸 $O(n\times(n+m)\log n)$（  $\text{Dijkstra}$ 堆优化）。当然我们也可以用  $\text{Floyd}\ O(N^3)$。

考虑优化：思考一下时间耗费在哪里了。我们发现在跑最短路时是不能确定终点的，最后还要通过加上最后城市的票价  $a[i]$ 才可以确定最小值。如果将演唱会的票价放到最短路里跑一边不就行了？这样一来，就可以直接求出最小花费。所以我们**化点权为边权**，建立一个**虚拟源点**——  $0$ 号节点，向其他城市  $i$ 连一条边权为  $a[i]$ 的边。

如图所示(样例一)：

![](https://cdn.luogu.com.cn/upload/image_hosting/b23qufct.png)

这样，我们每次从  $0$ 号节点作为起点跑最短路，就可以求出最小花费了。

### 正确性证明：

从  $0$ 号节点到  $i$ 的最短路径，必然**存在且只存在**一条从  $0$ 号节点连向城市  $j$ 的边，经过此边即代表去此城市听演唱会。

## 接下来是细节的处理：

1. 看了一眼数据范围  $1\le a_i,w_i\le 10^{12}$ 果断开  $\texttt{long long}$
2. 注意要往返，所以连边是边权为  $2\times w_i$
3. 边数要开三倍(无向图+虚拟源点连的边)

[同类题推荐[P7100 [w3R1] 团]](https://www.luogu.com.cn/problem/P7100)

看到这的同学，可以自己去写代码了(~~tf口吻~~)

[code](https://www.luogu.com.cn/paste/ibgghxm2)（  $\text{Dijkstra}$ 堆优化）
### End

## 作者的碎碎念：

有用留赞(~~言简意赅~~)

---

## 作者：FREEH (赞：5)

### 【题目】
[传送门](http://codeforces.com/contest/938/problem/D)
![题目](https://cdn.luogu.com.cn/upload/pic/33947.png)

### 【解题思路】
#### 方法一
- 建立一个虚拟源点，向每一个城市建立一条费用是该城市票价的边，然后再按照题目要求的方法建图（这里要注意费用要两倍，因为要一来一回），接着以虚拟源点为起点跑一波SPFA即可。最终的答案就是各个城市所代表的结点所对应的最短路径。

#### 方法二
- 不用建立虚拟源点，但是要用到虚拟源点的思想。只要按照原来的方法建图，然后跑一波SPFA。
	- 其中，要分别把每个结点的初始距离定为票价，然后SPFA的过程要用优先队列来优化。
    
### 【解题反思】
- 虚拟源点用于把图的点权转化为边权，易于使用最短路径算法。

### 【参考程序】
```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

typedef long long LL;
//#define int LL
#define N 500005
int head[N],cur,n,m;
LL dis[N],d[N];
struct EDGE{
	int t,next;
	LL c;
}e[2*N];

priority_queue < pair<LL,int> > que;

void add(int a,int b,LL c)
{
	cur++;
	e[cur].t=b;
	e[cur].next=head[a];
	e[cur].c=c;
	head[a]=cur;
}

void Put_it(int i,LL D)
{
	if (D>=dis[i]) return;
	dis[i]=D;
	que.push(make_pair(-dis[i],i));
}

void SPFA()
{
	while (!que.empty())
	{
		int now=que.top().second;
		LL nowx=que.top().first;
		que.pop();
		if (dis[now]!=-nowx) continue;
		for (int h=head[now];h!=-1;h=e[h].next)
		{
			int newx=e[h].t;
			Put_it(newx,dis[now]+e[h].c);
		}
	}
}

signed main()
{
//	ios::sync_with_stdio(false);
	scanf("%d%d",&n,&m);
	memset(head,-1,sizeof(head)); 
	for (int i=1;i<=m;i++)
	{
		int a,b;
		LL c;
		scanf("%d%d%I64d",&a,&b,&c);
		add(a,b,2*c);
		add(b,a,2*c);
	}
	for (int i=1;i<=n;i++)
	{
		scanf("%I64d",&d[i]);
		dis[i]=1e18;
		Put_it(i,d[i]);
	}
	SPFA();
	
	for (int i=1;i<=n;i++)
		printf("%I64d ",dis[i]);
	
	return 0;
}
```

---

## 作者：taozhiming (赞：3)

## CF938D Buy a Ticket

## 题目描述：
[原题面](https://www.luogu.com.cn/problem/CF938D)

## 题目分析：
本题让我们求从i出发，到别的点的最短路径是多少。

我们暴力的想法就是：对每一个点跑单源最短路，然后统计最短的。但这道题的数据范围显然不支持这种思路。( $n \le 2 \times 10^5$ )

所以我们就要思考一下别的算法，我最先开始想到的是各种卡常()，但是都没有什么用。

所以我们就要开始思考正解，有 
$$\min_{j=1}^{n} 2d(i,j)+a_j$$
我们就一定要求出来 $i,j$ 吗？

如果我们建立一个原点，定义为 $n+1$ ，对于这个图中的每个点 $i$ 都和 $n+1$ 连一条权为 $a_i$ 的边，对于原图当中的每一个 $i,j$ ，都赋上两倍的 $w_{i,j}$ 的边。

那么上文当中的式子，即
$$\min_{j=1}^{n} 2d(i,j)+a_j $$
都可以看作是 $n+1$ 这个原点到每一个 $i$ 的最短路，
我们只需要输出最后的 $dis[i]$ 数组就可以了。

到这里有没有一种豁然开朗的感觉。

## 代码详解：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
const int inf=1e18; //这个地方的最大值最好设的越大越好，我直接设为1e18 ，我最先开始设的0x7fffffff，直接wa一片，罚了四五遍才过
const int MAXN=2e6+5;
inline int read() //快读
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int n,m,head[MAXN],dis[MAXN],cnt; //dis数组就是存 n+1 到每个点的最短路径
bool vis[MAXN]; //vis 标记这个点之前是否走过

struct node{
	int to,nxt,val;
}e[2*MAXN];

void add(int from,int to,int val) //用链式前向星加边
{
	e[++cnt].to=to;
	e[cnt].val=val;
	e[cnt].nxt=head[from];
	head[from]=cnt;
}

void dij(int s) //Dijkstra 堆优化模板
{
	priority_queue<PII> q;
	for (int i=1;i<=n+1;i++) vis[i]=0,dis[i]=inf;
	dis[s]=0;
	q.push(make_pair(-dis[s],s));
	while(!q.empty())
	{
		int p=q.top().second;
		q.pop();
		if (vis[p]) continue; ////这里要用vis来标记这个点走没走过 
      		vis[p]=1;
		for (int i=head[p];i;i=e[i].nxt)
		{
			int to=e[i].to,val=e[i].val,newd=val+dis[p];
			if (!vis[to]&&dis[to]>newd) //这里要用vis来标记这个点走没走过
			{
				dis[to]=newd;
				q.push(make_pair(-dis[to],to));
			}
		}
	}
}

signed main()
{
	n=read(),m=read();
	for (int i=1;i<=m;i++)
	{
		int u=read(),v=read(),w=read();
		add(u,v,2*w); //这里加边要乘2，因为是来回
		add(v,u,2*w); //同上
	}
	for (int i=1;i<=n;i++)
	{
		int a=read();
		add(n+1,i,a); //从 n+1 到 i 加边，边权就是ai，即这里的a
	}
	dij(n+1); //Dijkstra 堆优化模板
	for (int i=1;i<=n;i++)
		printf("%lld ",dis[i]); //输出dis[i]
	return 0;  
}
```

最后吐槽：
我就因为 inf 开小了wa了四五发，气死我了！！！长记性了，来发篇题解解气！！！

---

## 作者：bits (赞：2)

题意就不说了。下面讲思路。

首先我们想到枚举每一个点作为起点，然后求出最短路。这样显然是不行的，因为$n<=2*10^5$。

换种角度想想，对于作为终点的每一个点（参加演唱会的地方），这个点都可能是许多个起点的最优解。因此，我们就将单源最短路径转换为**单终点最短路径**。

然而这样的时间复杂度仍然无法满足要求，因为我们需要枚举终点，以确定点权（演唱会费用），从而计算路费。我们不妨将点权转为边权，在计算路费同时也**捆绑**计算演唱会费用，这样只需跑一次最短路即可。

那么，该如何把点权转化为边权？只需建一个虚拟点，向各个城市加边，边权即为在这个城市参加演唱会的费用。

此外，要注意的是，题目中是无向边，且要计算往返的费用总和。只需把路费乘$2$，作为边权就行了。

详见代码
```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

char ss[1<<18],*A=ss,*B=ss;
inline char gc(){
    return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?EOF:*A++;
}
template<typename Tp>
inline void qr(Tp &s){
    char c=gc(); 
    s=0;
    for(;c<'0'||c>'9';c=gc());
    for(;c>='0'&&c<='9';c=gc())
        s=(s<<1)+(s<<3)+(c-'0');
}//快速读入

const int N=200005,M=600005;
struct Edge{
    int node,next;
    long long val;
}edge[M];
/*
题中说有m条无向边，建图时应存储两次，也就是2*m条有向边。另外，在将点权（演唱会费用）转换为边权时，会增加m条边。因此共计有3*m条边
*/
struct Head{
    int first;
    long long cost;
}head[N];
int n,m,tot;
long long dis[N];
bool vis[N];

struct qnode{
    int key;
    long long len;
    friend bool operator < (qnode x,qnode y){
        return x.len>y.len;
    }
};
priority_queue<qnode> q;
//将路径长作为键值，建立小根堆

inline void add_edge(int x,int y,long long l){
    edge[++tot].node=y;
    edge[tot].next=head[x].first;
    edge[tot].val=l;
    head[x].first=tot;
}

//堆优化的Dijkstra算法
void dijkstra(int s){
    for(int i=1;i<N;i++)
        dis[i]=1e18;
    dis[s]=0;
    q.push((qnode){s,0});
    qnode u;
    int v;
    while(!q.empty()){
        u=q.top();
        q.pop();
        if(vis[u.key])
            continue;
        vis[u.key]=1;
        for(int k=head[u.key].first;k;k=edge[k].next){
            v=edge[k].node;
            if(dis[u.key]+edge[k].val<dis[v]){
                dis[v]=dis[u.key]+edge[k].val;
                q.push((qnode){v,dis[v]});
            }
        }
    }
}

int main(){
    qr(n); qr(m);
    int x,y;
    long long l;
    for(int i=1;i<=m;i++){
        qr(x),qr(y),qr(l);
        add_edge(x,y,l*2);
        add_edge(y,x,l*2);
    }
    //将第n+1个点作为虚拟点，并作为源点计算最短路
    for(int i=1;i<=n;i++){
        qr(head[i].cost);
        add_edge(n+1,i,head[i].cost);
    }
    dijkstra(n+1);
    for(int i=1;i<=n;i++)
        printf("%lld ",dis[i]);
    return 0;
}
```

---

## 作者：yinxiaodi2006 (赞：1)

这一道题，我采用的思路是虚拟原点+优先队列优化的迪杰斯特拉

一开始过了样例，开心得要飞起，结果不开__见祖宗。。。。

# 思路

先看一下样例的图
![](https://cdn.luogu.com.cn/upload/image_hosting/vab92x31.png)

//画工丑QWQ

然后突然发现如果要去其他城市看演唱会的话需要一来一回，所以边权乘二。（如下图）
![](https://cdn.luogu.com.cn/upload/image_hosting/st3ygvrg.png)

接下来就是最重要的地方！！！

建立一个虚拟原点，向所有的城市都连出一条边，边权为这个城市的票价！（如下图）

![](https://cdn.luogu.com.cn/upload/image_hosting/shxpij8j.png)

然后你就会惊人的发现，答案就是从这个虚拟原点到其他所有点的最短距离，也就是一个单源最短路径，用优先队列的迪杰斯特拉就可以完美解决啦!

## 代码：

```cpp
#include<bits/stdc++.h>
#define maxn 600010
#define pa pair<long long,int>//第一个没开longlong WA掉
using namespace std;
long long dis[maxn];
bool vis[maxn];
priority_queue<pa,vector<pa>,greater<pa> > q;
struct edge
{
	long long val,to;
};
vector<edge> e[maxn];
void dijkstra(int n,int m,int s)
{
	for(int i=1;i<=n;i++)
		dis[i]=1e18;//优化小了 WA掉
	dis[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty())
	{
		long long x=q.top().second;
		q.pop();
		if(vis[x])
			continue;
		vis[x]=1;
		for(int i=0;i<e[x].size();i++)
		{
			long long y=e[x][i].to;
			if(dis[x]+e[x][i].val<dis[y])
			{
				dis[y]=dis[x]+e[x][i].val;
				q.push(make_pair(dis[y],y));
			}
		}
	}
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		long long x,y,z;
		cin>>x>>y>>z;
		edge tmp;
		tmp.val=z*2;//边权*2！！！
		tmp.to=y;
		e[x].push_back(tmp);
		edge tmp2;
		tmp2.val=z*2;//要注意从虚拟原点走出去的边都是单向边，所有的公路都是双向边！这里WA了一次
		tmp2.to=x;
		e[y].push_back(tmp2);
	}
	int nn=n+1;
	for(int i=1;i<=n;i++)
	{
		long long x;//要注意边权一定要开longlong
		cin>>x;
		edge tmp;
		tmp.to=i;
		tmp.val=x;
		e[nn].push_back(tmp);
	}
	dijkstra(nn,m+n,nn);//迪杰斯特拉函数，注意，因为多了一个虚拟原点，所以说点数要+1。边的数量则是正常的m和虚拟原点连出的n条边，起点为第n+1个点也就是虚拟原点
	for(int i=1;i<=n;i++)
		cout<<dis[i]<<' ';
	return 0;
}

```
思路就讲解完啦！

这道题还是非常有意思的，~~就是longlong有点坑~~

望管理大大通过！

---

## 作者：_Anchor (赞：1)

# 多源最短路

（本题解说说不用建超级源点的做法）

## 大致题意
给一个有n个顶点m条无向边的图，顶点有点权ai，

边也有权值wi，求每个顶点i的min(2d(i,j)+aj)，

其中d(i,j)为最短路径长度，i可以和j相同

## 错误示范

看到这题我一开始想到Floyd，但是最后看到数据才发现

~~原来我是个睿智~~



~~（然后我成功被数据劝退了）~~

这题数据很接近dijkstra最短路算法的复杂度nlogn,所以我就想想这样该怎么让它变成可以用dijkstra，这样就有了接下来的故事

~~之前几位写题解的大佬好像有用SPFA切掉这题的？！~~

## dijkstra

仔细一想发现这个题其实每个城市对应的最小费用是可以图上dp转移的

但复杂度的确高了，所以我们直接把点权转移到边权上面去

然后跑一遍dijkstra即可，注意这里初始化距离就是其点权


最后附上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
inline ll inc(int x,int v,int mod){x+=v;return x>=mod?x-mod:x;}
inline ll dec(int x,int v,int mod){x-=v;return x<0?x+mod:x;}
inline ll read(){ll x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline void write(ll x){if(x==0){putchar(48);return;}int len=0,dg[40];while(x>0){dg[++len]=x%10;x/=10;}for(register int i=len;i>=1;i--)putchar(dg[i]+48);}
const int MAXN=2e5+5;
struct node{
    int to;
    ll val;
    int next;
}e[MAXN<<1];
struct PII{
    int id;
    ll val;
    bool operator<(const struct PII &aa)const{
        return val>aa.val;
    }
};
priority_queue<struct PII> q;
ll head[MAXN],idx,dist[MAXN],c;
int n,m,a,b;
void add(int x,int y,ll z){
    e[idx].to=y;
    e[idx].val=z;
    e[idx].next=head[x];
    head[x]=idx++;
}
void dijkstra(){
    while(!q.empty()){
        PII now=q.top();
        q.pop();
        if(dist[now.id]<now.val)continue;
        for(int i=head[now.id];i!=-1;i=e[i].next){
            int v=e[i].to;
            if(dist[v]>dist[now.id]+e[i].val){
                dist[v]=dist[now.id]+e[i].val;
                PII ne;
                ne.id=v;
                ne.val=dist[v];
                q.push(ne);
            }
        }
    }
    return ;
}
int main(){
    n=read(),m=read();
    memset(head,-1,sizeof(head));
    while(m--){
        a=read(),b=read(),c=read();
        add(a,b,c*2);
        add(b,a,c*2);
    }
    for(int i=1;i<=n;i++){
        dist[i]=read();
        PII now;
        now.id=i;
        now.val=dist[i];
        q.push(now);
    }
    dijkstra();
    for(int i=1;i<=n;i++){
        write(dist[i]);
        cout<<" ";
    }
    return 0;
}
```



---

## 作者：_JF_ (赞：0)

## CF938D Buy a Ticket

简单最短路练手题。

首先每个点都有自己的点权，根据经验，这肯定是要转边权的。

再看看题目，题目要求求每个人的去看的费用最小值，一般不难想出要跑 $n$ 遍最短路，但是时间复杂度太高。

所以我们考虑建立一个虚拟原点，由于一开始的点是有点权的，所以我们把虚拟原点向所有的点连边，权值就是对应点的点权了。

这时候我们就可以只跑一边最短路， $dis$ 数组就是答案了。

注意，由于要来回，所以边的值要双倍。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
struct node
{
	int v;
	int w;
};
vector<node> g[N<<1]; 
int dis[N];
struct State{
	int u,d;
	bool operator<(const State &s) const {
		return d > s.d;
	}
};
void dijkstra(int s){
	priority_queue<State> que;
	memset(dis,0x3f,sizeof(dis));
	que.push(State{s,0}),dis[s] = 0;
	
	while(!que.empty()){
		int u = que.top().u,d = que.top().d;
		que.pop();
		if (d > dis[u]) continue;
		for (int i = 0;i < g[u].size();++i){
			int v = g[u][i].v,w = g[u][i].w;
			if (dis[u] + w < dis[v]){
				dis[v] = dis[u] + w;
				que.push(State{v,dis[v]});
			}
		}
	}
}
signed main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		g[u].push_back(node{v,w*2});
		g[v].push_back(node{u,w*2});  
	}
	for(int i=1;i<=n;i++)
	{
		int w;
		cin>>w;
		g[0].push_back(node{i,w}); 
	}
	dijkstra(0);
	for(int i=1;i<=n;i++)
		cout<<dis[i]<<" ";
	return 0;
}
```


---

## 作者：E1_de5truct0r (赞：0)

## 思路

首先考虑答案是怎么得来的：一定是从这个点经过若干条边，然后加上另一个点的点权得到的。因此我们考虑怎么计算它的答案。由于各个点实在太分散，我们可以建立一个超级源点表示“电影”，每个点向他连一条权值为点权的边。

那么这样，从它跑一遍最短路算出到各个点的最短距离，一定是从这个点出发，经过若干条边到达另一个点，这个点连向超级源点。那么这条路径的长度就是一个点权加上若干个边权，即 

$$dis_i = \min\limits_{j=1}^{n} \left(a_j + d(i,j)\right)$$

这里巧妙地运用了超级源点把点权转化成边权存储，再跑单源最短路。这个思路在图论和树里还是很有用的，像我这种菜鸡应该好好学习。

## 代码

- 注意：边权要两倍，因为是往返！

```cpp
#include <bits/stdc++.h>
#define mp make_pair
#define fir first
#define sec second
#define ll long long
const int MAXN=200005;
using namespace std;
ll dis[MAXN];
bool vis[MAXN];
vector<pair<int,ll> > E[MAXN];
void Dijkstra(){
	memset(dis,0x3f,sizeof(dis));
	priority_queue<pair<ll,int> >q;
	q.push(mp(0,0)); dis[0]=0;
	while(!q.empty()){
		int u=q.top().sec; q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=0;i<E[u].size();i++){
			int v=E[u][i].fir;
			ll w=E[u][i].sec;
			if(dis[u]+w<dis[v]){
				dis[v]=dis[u]+w;
				q.push(mp(-dis[v],v));
			}
		}
	}
}int main(){
	ios::sync_with_stdio(false); 
	int n,m; cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v; ll w;
		cin>>u>>v>>w;
		E[u].push_back(mp(v,w<<1));
		E[v].push_back(mp(u,w<<1));
	}for(int i=1;i<=n;i++){
		ll x; cin>>x;
		E[0].push_back(mp(i,x));
	}Dijkstra();
	for(int i=1;i<=n;i++) cout<<dis[i]<<" "; 
	return 0;
}
```

---

## 作者：hzoi_liuchang (赞：0)

## 分析

首先想到的肯定是暴力，从每一个点开始跑最短路，最后再分别输出结果，但是这样复杂度肯定吃不消

题目中也没有说给出的是一棵树，所以树形DP也不太可行

所以我们考虑建边时做一些处理

我们建一个超级源点跑最短路，和昂贵的聘礼那一道题有点像

对于边权，我们把它乘2再正常建边，因为我们要往返各一次

对于点权，我们从超级源点向该点建一条边，边权为点权，代表在某一个点停留所花费的时间

最后再从超级源点开始跑一个最短路就可以了

不要忘了开long long

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
typedef long long ll;
struct asd{
    ll from,to,next,val;
}b[maxn];
int head[maxn],tot=1;
void ad(ll aa,ll bb,ll cc){
    b[tot].from=aa;
    b[tot].to=bb;
    b[tot].val=cc;
    b[tot].next=head[aa];
    head[aa]=tot++;
}
struct jie{
    ll num,dis;
    jie(ll aa=0,ll bb=0){
        num=aa,dis=bb;
    }
    bool operator < (const jie& A) const{
        return dis>A.dis;
    }
};
priority_queue<jie> q;
ll dis[maxn];
bool vis[maxn];
void DIJ(){
    memset(dis,0x3f,sizeof(dis));
    dis[0]=0;
    q.push(jie(0,0));
    while(!q.empty()){
        int now=q.top().num;
        q.pop();
        if(vis[now]) continue;
        vis[now]=1;
        for(ll i=head[now];i!=-1;i=b[i].next){
            ll u=b[i].to;
            if(dis[u]>dis[now]+b[i].val){
                dis[u]=dis[now]+b[i].val;
                q.push(jie(u,dis[u]));
            }
        }
    }
}
int main(){
    memset(head,-1,sizeof(head));
    ll n,m;
    scanf("%lld%lld",&n,&m);
    for(ll i=1;i<=m;i++){
        ll aa,bb,cc;
        scanf("%lld%lld%lld",&aa,&bb,&cc);
        ad(aa,bb,cc*2ll);
        ad(bb,aa,cc*2ll);
    }
    for(ll i=1;i<=n;i++){
        ll aa;
        scanf("%lld",&aa);
        ad(0,i,aa);
    }
    DIJ();
    printf("%lld",dis[1]);
    for(ll i=2;i<=n;i++){
        printf(" %lld",dis[i]);
    }
    printf("\n");
    return 0;
}

```



---

## 作者：Instudy (赞：0)

提交了26次才过的这题……我一定要发篇题解。

#### 鸣谢：感谢@[小粉兔](https://www.luogu.com.cn/user/10703)  大爷的指导

首先，这道题卡了 $ spfa $算法，证据如下：

[卡spfa](https://www.luogu.com.cn/record/32158599)

于是~~果断~~不情愿的换了 $ heap-dij $算法，如果您不了解 $ heap-dij $算法，请移步：

[模板-最短路径-dij](https://www.luogu.com.cn/problem/P4779)

以上是这道题第一个坑点，第二个坑点：要开 $ long long $ ~~虽然我知道但是由于脑残中途一个变量开了 $ int $还要兔兔来解决~~

记住，边要 开 $ long long $，

第三个坑点：翻译的锅，没有说要一来一回，导致我第一次的错误。

这道题是个很常见的建虚拟源点的题，我们从0跑一遍最短路，于是输出就好了要不是卡 $ spfa $和 $ long long $这道题就是个黄题……

贴个代码吧：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N =2*1e5+1;
const int INF = 0x3f;
priority_queue<pair<ll,int> >q;
struct fake{
	int next,to;
	ll dis;

}
edge[3*N];
ll dist[3*N];

bool visit[N];
int n, m;
int cnt;
int head[N];
void addedge(int u,int v,ll w)
{
	edge[++cnt].next=head[u];
	edge[cnt].to=v;
	edge[cnt].dis=w;

	head[u]=cnt;
}
void dij()

{
	memset(dist,0x3f,sizeof(dist));

	dist[0]=0;

	q.push(make_pair(0,0));
	while(!q.empty())
	{
		int x=q.top().second;q.pop();
		if(visit[x])continue;
        visit[x]=1;
		for(int i=head[x];i;i=edge[i].next)
		{
			int y=edge[i].to;
            long long z=edge[i].dis;

			if(dist[y]>dist[x]+z)

			{
				dist[y]=dist[x]+z;

				q.push(make_pair(-dist[y],y));

			}
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);

	for(int i=1;i<=m;i++)
	{
		int a,b;

		ll c;
		scanf("%d%d%lld",&a,&b,&c);

		addedge(a,b,c*2);

		addedge(b,a,c*2);

	}
	for(int i=1;i<=n;i++)
	{
		ll a;
		scanf("%lld",&a);

		addedge(0,i,a);

	}
	dij();

	for(int i=1;i<=n;i++)
	 printf("%lld ",dist[i]);

	return 0;
}
```

小号写的题解，如有冲突不要在意。

---

## 作者：DarthVictor (赞：0)

# 题目
[原题地址](https://codeforces.com/problemset/problem/938/D)
# 解说
先说一下，洛谷上的中文翻译是有问题的，路程是往返的，汉语翻译没体现这一点，看一下原题里面的公式就行了。

这道题和之前我自己出的[02的爱恋](https://www.luogu.com.cn/problem/T132272)有些许相似，都需要把点权转化为边权。怎么转化呢？由于只有在终点处需要加上点权，所以我们自然地想到超级源点，从超级源点到每个点都连一条权值为点权的单向边保证只走一次，之后跑一次超级源点的单元最短路就行了。当然这就暗含了另一种思维方法：逆向。题目原意是只加终点的点权，但由于道路双向，我们从终点开始跑也是一样的，因此可以把终点当做起点跑最短路。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=200000+5;
int n,m,tot;
int head[maxn];
ll dis[maxn];
struct edge{
	int to,next;
	ll w;
}e[3*maxn];
struct node{
	int num;ll dis;
	node(int x,ll y){
		num=x;
		dis=y;
	}
	bool operator<(const node &a)const{
		return dis>a.dis;
	}
};
void add(int a,int b,ll w){
	e[tot].to=b;
	e[tot].w=w;
	e[tot].next=head[a];
	head[a]=tot;
	tot++;
}
void Dijs(){
	priority_queue<node> q;
	bool f[maxn];
	memset(f,0,sizeof(f));
	for (int i=1;i<=n;i++) dis[i]=4611686018427387903;
	dis[0]=0;
	q.push(node(0,0));
	while(!q.empty()){
		node p=q.top();q.pop();
		int k=p.num;
		if(f[k]) continue;
		f[k]=1;
		for (int i=head[k];i;i=e[i].next){
			int u=e[i].to;ll len;
			len=dis[k]+e[i].w;
			if(dis[u]>len){
				dis[u]=len;
				q.push(node(u,len));
			}
		}
	}
}
int main(){
	tot=1;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v; ll w;
		scanf("%d%d%lld",&u,&v,&w);
		add(u,v,2*w);//每条边要走两遍
		add(v,u,2*w);
	}
	for(int i=1;i<=n;i++){
		ll w;
		scanf("%lld",&w);
		add(0,i,w);//超级源点编号为0
	}
	Dijs();
	for(int i=1;i<=n;i++) printf("%lld ",dis[i]);
	return 0;
}
```
幸甚至哉，歌以咏志。

---

