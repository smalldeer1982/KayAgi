# Domino Effect

## 题目描述

@[lin_toto](/space/show?uid=256)

题目名字：多米诺骨牌效应

您是否知道多米诺骨牌除了玩之外还可以用来做其他事情？拿一些多米诺骨牌，然后将它们排成一排，并在它们之间只留一小段距离。如果你做得对，你可以推倒第一张多米诺骨牌并使所有其他的多米诺骨牌依次倒下（这就是“多米诺骨牌效应”的由来）。

数量太少的多米诺骨牌有点毫无意义，所以有些人在八十年代初就走向了相反的极端。他们使用数以百万计的不同颜色和材料的多米诺骨牌，用倒下的精美多米诺骨牌组成的图案填满整个大厅，来创造（短命的）艺术品。在这些过程中，通常不只有一排多米诺骨牌同时倒下。你可以发现，时间是一个重要的影响因素。 

现在你的任务是编写一个程序，给定由多米诺骨牌组成的系统，计算最后一个多米诺骨牌在何时何地倒下。该系统由几个简单的关键多米诺骨牌和其之间的多米诺骨牌连接而成。当一个关键的多米诺骨牌倒下时，连接到该关键多米诺骨牌的所有多米诺骨牌都开始倒下（除了那些已经倒下的多米诺骨牌）。当倒下的多米诺骨牌到达尚未倒下的其他关键多米诺骨牌时，这些关键多米诺骨牌也会倒下并且引起与它们相连的多米诺骨牌开始倒下。多米诺骨牌行可能会从任何一端开始倒下。甚至有可能同一多米诺骨牌行从两端开始倒下，在这种情况下，该行倒下的最后一张多米诺骨牌位于其行两端的关键多米诺骨牌之间。您可以假设行中的多米诺骨牌以均匀的速度倒下。

## 样例 #1

### 输入

```
2 1
1 2 27
3 3
1 2 5
1 3 5
2 3 5
0 0```

### 输出

```
System #1
The last domino falls after 27.0 seconds, at key domino 2.
System #2
The last domino falls after 7.5 seconds, between key dominoes 2 and 3.```

# 题解

## 作者：Echoternity (赞：7)

### 题解：

[题目链接](https://www.luogu.com.cn/problem/UVA318)

**~~这道题明明很简单我却被卡了很多次~~**

说说这道题的思路：

题目很冗长，但其实理解下来很简单，~~不然为什么是黄题呢~~。

## 题意解释：

**_输入一个 $N$ 个点， $M$ 条边的无向图，每条边的起点，终点和权值。找出从编号为 $1$ 的点能够到达的最远地点，这个地点可以在点上，也可以在边上。_**

对于这道题来说，最远的地方，只会有两种情况：

___*在某一个点上；___

___*在某两点之间。___

从起点 $1$ 开始，对图上所有点走一遍最短路，找出到达最远的点，这就是第一种情况的答案，我们可以记录一次。然后将编号 $2$ 至编号 $N$ 的之间的全部点都跑一次，求出最远的边。

在这里，~~最朴素~~我刚开始想到的的方法就是求出到达两点的时间，然后根据时间差按比例分配这条边的权值，就是两边相遇的地点即时间。

但是，

实际上，换个角度思考，两组多米诺相遇的时间是一致的，所以从其中一点出发到另一点出发到的那个最远点时间一样，即是从起点到 $i$ 点加上起点到 $j$ 点的距离再加上这条边的权值。这条边的最远时间就是：

$Value_{i,j}=(Dis_i+Dis_j+Path_{i.j})/2$

上述即是对于答案的枚举，最坏情况为 $O(N^2)$ ，这道题的 $N≤500$ 完全足够。

### 最短路板块：

对于像我这种蒟蒻来说，有 $3$ 种方法：

### Floyd：

通过考虑最佳子路径来得到最佳路径。单独一条边的路径也不一定是最佳路径。从任意一条单边路径开始。所有两点之间的距离是边的权的和，(如果两点之间没有边相连,则为 $INF$ ）。从第一个顶点开始，依次将每个顶点作为媒介 $k$ ，然后对于每一对顶点 $u$ 和 $v$ ，查看其是否存在一条经过 $k$ 的，距离比已知路径更短的路径，如果存在则更新它。

```cpp
inline void underFloyd()
{
    for(int k=1;k<=N;++k)	//媒介点
    {
        for(int i=1;i<=N;++i)	//起点
        {
            for(int j=1;j<=N;++j)	//终点
            {
                F[i][j]=underMin(F[i][j],F[i][k]+F[k][j]);
            }
        }
    }
}
```
Floyd的时间复杂度为 $O(N^3)$ ，这种算法其实是拿来求全源最短路的，但放在单源最短路的题里依然使用，还是因为数据太小，所以可以选择。

### SPFA~~已经死了~~：

SPFA其实是另一种最短路算法Bellman-Ford的队列优化，但我们一般不使用。（因为太~~蒻~~了）

实际上，SPFA的实现与BFS相差无异。不同的是BFS中一个点如果出了队列就不再会进入队列，而在SPFA中如果一个点出了队列，它还有机会能够进入队列。因为一个点在对别的点进行松弛操作时，自己的最小值也同样会被自己修改过的点再次修改。

SPFA的复杂度并不是很稳定，最坏情况为 $O(NM)$ 。

一般来说，随机数据的题SPFA和Dijkstra无异，但一般来说，有负权的图使用SPFA，因为Dijkstra不能处理负边权；而在一些毒瘤题里，就会出现[关于SPFA……](https://www.baidu.com/s?ie=utf-8&f=3&rsv_bp=1&tn=monline_3_dg&wd=%E5%85%B3%E4%BA%8Espfa%E4%BB%96%E6%AD%BB%E4%BA%86&oq=%25E5%2585%25B3%25E4%25BA%258ESPFA&rsv_pq=87887f7600054917&rsv_t=4dbarFQevDh8Ep8JI96yOsaRl1SmYkP51au%2BYmWsvJiGd1oPs8BL8OoqeXZnXvEEMRfC&rqlang=cn&rsv_dl=ts_0&rsv_enter=1&rsv_sug3=1&rsv_sug1=1&rsv_sug7=100&rsv_sug2=1&rsv_btype=t&prefixsug=%25E5%2585%25B3%25E4%25BA%258ESPFA&rsp=0&rsv_sug4=729)

代码如下：

```cpp
inline void underSPFA(int x)
{
	Dis[x]=0;
	queue<Que>Q;
	Q.push(Que(x,0));
	while(!Q.empty())
	{
		Que u=Q.front();
		Q.pop();
		int k=u.now;
		Vis[k]=0;
		for(int e=First[k];e;e=Edge[e].next)
		{
			if(Dis[k]+Edge[e].value<Dis[Edge[e].to])
			{
				Dis[Edge[e].to]=Dis[k]+Edge[e].value;
				if(!Vis[Edge[e].to])
				{
                   			Vis[Edge[e].to]=1;
					Q.push(Que(Edge[e].to,Dis[Edge[e].to]));
				}
			}
		}
	}
}
```

## 这道题过了最多的正解——Dijkstra：

Dijkstra算法采用的是一种贪心的策略，建立一个数组 $dis$ 来保存源点到各个顶点的最短距离和一个保存已经找到了最短路径的顶点的集合： $T$ ，初始时，原点s的路径权重被赋为 $0$ （即 $dis_s=0$ ）。

若对于顶点 $s$存在能直接到达的边 $(s,m)$ ，则把 $dis_m$设为 $w(s,m)$ ,同时把所有其他（ $s$ 不能直接到达的）顶点的路径长度设为无穷大。

初始时，集合顶点 $s$ 。

然后，从 $dis$ 数组选择最小值，则该值就是源点s到该值对应的顶点的最短路径，并且把该点加入到 $T$ 中，此时完成一个顶点。

然后，我们需要看看新加入的顶点是否可以到达其他顶点并且看看通过该顶点到达其他点的路径长度是否比源点直接到达短——如果是，那么就替换这些顶点在dis中的值；然后，又从 $dis$ 中找出最小值，重复上述动作，直到 $T$ 中包含了图的所有顶点。

这就是Dijkstra的基本思路，但是在深度学习之后，我们一般使用的是Dijkstra的二叉堆（优先队列）优化：

```cpp
inline void underDijkstra(int x)
{
	Dis[x]=0;
	priority_queue<Que>Q;
	Q.push(Que(x,0));
	while(!Q.empty())
	{
		Que u=Q.top();
		Q.pop();
		int k=u.now;
		if(Vis[k])
		{
			continue;
		}
		Vis[k]=1;
		for(int e=First[k];e;e=Edge[e].next)
		{
			if(Dis[k]+Edge[e].value<=Dis[Edge[e].to])
			{
				Dis[Edge[e].to]=Dis[k]+Edge[e].value;
				if(!Vis[Edge[e].to])
				{
					Q.push(Que(Edge[e].to,Dis[Edge[e].to]));
				}
			}
		}
	}
}
```

而对于最短路来说，我们需要的是小根堆，优先队列初始大根堆。所以我们要重载一次。

结构体定义如下：

```cpp
struct Que
{
	int now;
    	int d;
	Que(int _now=0,int _d=0):now(_now),d(_d){}
    	bool operator<(const Que& test)const		//重载运算符
	{
		return d<test.d;
	}
};
```
### 这道题的其他注意事项：

__*因为有多组数据，所以记得初始化所有相关变量__

__*多米诺的英文复数加的是 $es$！！！__

__*输出格式严格按照题目要求，句子后有两个 $\n\n$__

### 补充一点我的代码风格：

__*我喜欢自己重写一些简单的函数代替STL库：$max$，$min$，$sort$__

__*每一个函数名之前都会加入一个类似于水印作用的标识符under，所以copy的同学记得删掉，而对于under的含义，请移步[Undertale](https://search.bilibili.com/all?keyword=undertale&from_source=webtop_search&spm_id_from=333.1007)__

蒟蒻第一篇题解，求过QWQ，~~并厚颜无耻的要波赞。~~

给上Dijkstra的AC代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include<iomanip>
#include<queue>
#include<stack>
#include<map>
#include<vector>
using namespace std;
int N,M,x,y,Total,Test;
struct Node
{
    int start,to,next,value;
    double time;
}Edge[1000001];
bool Vis[1001];
int First[1001];
int Dis[1001],z;
int Path[1001][1001];
struct Que
{
	int now;
    	int d;
	Que(int _now=0,int _d=0):now(_now),d(_d){}
    	bool operator<(const Que& test)const
	{
		return d<test.d;
	}
};
inline int underMin(int a,int b)
{
    return (a>b?b:a);
}
inline int underMax(int a,int b)
{
    return (a>b?a:b);
}
inline void underAdd(int x,int y,int z)
{
    Edge[++Total].value=z;
    Edge[Total].to=y;
    Edge[Total].next=First[x];
    Edge[Total].start=x;
    First[x]=Total;
}
inline void underDijkstra(int x)
{
	Dis[x]=0;
	priority_queue<Que>Q;
	Q.push(Que(x,0));
	while(!Q.empty())
	{
		Que u=Q.top();
		Q.pop();
		int k=u.now;
		if(Vis[k])
		{
			continue;
		}
		Vis[k]=1;
		for(int e=First[k];e;e=Edge[e].next)
		{
			if(Dis[k]+Edge[e].value<=Dis[Edge[e].to])
			{
				Dis[Edge[e].to]=Dis[k]+Edge[e].value;
				if(!Vis[Edge[e].to])
				{
					Q.push(Que(Edge[e].to,Dis[Edge[e].to]));
				}
			}
		}
	}
}
int main()
{
//  freopen("Domino.in","r",stdin);
//  freopen("Domino.out","w",stdout);
    scanf("%d%d",&N,&M);
    while(N!=0)
    {
        memset(Edge,0,sizeof(Edge));
        memset(Vis,0,sizeof(Vis));
        memset(First,0,sizeof(First));
        Total=0;
        memset(Dis,0x42,sizeof(Dis));
        for(int i=1;i<=M;++i)
        {
            scanf("%d%d%d",&x,&y,&z);
            underAdd(x,y,z);
            underAdd(y,x,z);
        }
        underDijkstra(1);
        for(int i=1;i<=Total;++i)
        {
            Edge[i].time=(Dis[Edge[i].to]+Dis[Edge[i].start]+Edge[i].value)/2.0;
        }
        int Dp;
        bool f=0;
        double Ans=-1;
        for(int i=1;i<=Total;++i)
        {
            if(Edge[i].time>Ans&&Edge[i].time<1e9)
            {
                Dp=i;
                Ans=Edge[i].time;
            }
        }
        for(int i=1;i<=N;++i)
        {
            if(Dis[i]>=Ans&&Dis[i]<1e9)
            {
                Dp=i;
                Ans=(double)Dis[i];
                f=1;
            }
        }
        ++Test;
        printf("System #%d\n",Test);
        if(f)
        {
            printf("The last domino falls after %.1lf seconds, at key domino %d.\n\n",Ans,Dp);
        }
        else
        {
            printf("The last domino falls after %.1lf seconds, between key dominoes %d and %d.\n\n",Ans,Edge[Dp].start,Edge[Dp].to);
        }
        scanf("%d%d",&N,&M);
    }
    return 0;
}
/*
2 1
1 2 27
3 3
1 2 5
1 3 5
2 3 5
0 0
*/
```


---

## 作者：ZPC2048 (赞：6)

这题解估计没人做...~~题面也没人翻译~~，POJ上也有这道题。废话不多说，开始~~扯皮~~正解。

------------

首先理解题意，本题中的key dominoes（关键多米诺骨牌）相当于一个图中的节点，而row（多米诺骨牌行）相当于图中的边，那么，本题的题意转变为给定多张图，求到1号节点最远的位置（注意，这个位置不一定是某个节点，也可能在某条边上）。

以输入样例的第二组数据为例（~~懂了的可以往下跳了2333~~），1号节点到2号和3号节点的距离为5，而2号和3号节点之间距离为5，三者构成了一个三角形，1号节点沿着边行走最远可以经由2号节点或3号节点到达2号和3号节点的中点。（~~图画得稀烂不要介意QAQ~~）

![Luogu](https://cdn.luogu.com.cn/upload/pic/30086.png)

### 根据题目说明，最远端只有两种情况：
#### 1. 在某个节点上
#### 2. 在某条边上

**那么思路就出来了：先跑一遍单源最短路（~~关于SPFA，它死了~~），得到所有的点到1号节点距离，取最大值；之后遍历所有的边，取（遍历到的边的长处+1号节点到该边两个端点的距离和）/2的最大值，即遍历所有的类似上图的三角形。两个最大值进行比较。**

下面是蒟蒻的代码QAQ，手打堆，C++选手可以选择替换为STL中的优先队列：

~~~cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<vector>
#include<iostream>
#include<algorithm>

/*************************************

POJ1135 Domino Effect

*************************************/

using namespace std;

const int MAXN = 500 + 2;
const int INF = 0x3f3f3f3f;

int n, m;

int map[MAXN][MAXN], dis[MAXN], visit[MAXN];//map邻接矩阵，dis距离，visit标记该节点最短路是否找到
int size;
pair<int, int>heap[MAXN << 2];//下面一堆手写堆代码，不解释，大家可以略过(*^▽^*)

void init(){
    size = 0;
    memset(heap, 0, sizeof(heap));
    memset(visit, false, sizeof(visit));
    memset(dis, 0x3f3f, sizeof(dis));
    memset(map, 0x3f3f, sizeof(map));
}

void push(int x, int d){
    heap[++size] = make_pair(x, d);
    int now = size;
    while(now >> 1){
        if(heap[now].second > heap[now >> 1].second) break;
        swap(heap[now], heap[now >> 1]);
        now >>= 1;
    }
}

int top(){
    return heap[1].first;
}

void pop(){
    heap[1] = heap[size--];
    int now = 1;
    while(now << 1 <= size || now << 1 < size){
        int exc = now << 1;
        if(exc < size && heap[exc + 1].second < heap[exc].second) ++exc;
        if(heap[now].second < heap[exc].second) break;
        swap(heap[now], heap[exc]);
        now = exc;
    }
}

void dijkstra(){//dijkstra单源最短路代码堆优化不解释
    while(size){
        int x = top(); pop();
        if(visit[x]) continue;
        visit[x] = true;
        for(int i = 1; i <= n; ++i){
            if(dis[i] > dis[x] + map[x][i] && !visit[i]){
                dis[i] = dis[x] + map[x][i];
                push(i, dis[i]);
            }
        }
    }
}

int main()
{
    //freopen("POJ1135.in", "r", stdin);
    //freopen("POJ1135.out", "w", stdout);
    int system = 1;
    while(scanf("%d%d", &n, &m) && n){
        init();
        for(int i = 0; i < m; ++i){
            int a, b, l;
            scanf("%d%d%d", &a, &b, &l);
            map[a][b] = map[b][a] = l;
        }
        dis[1] = 0;
        push(1, 0);
        dijkstra();
        double ans = -1;
        int first, second;
        bool flag = false;
        for(int i = 1; i <= n; ++i)//找在节点上的最长路
            if(ans < dis[i]){
                ans = max(ans, (double)dis[i]);
                first = i;
            }
        for(int i = 1; i <= n; ++i){//找在边上的最长路
            for(int j = i + 1; j <= n; ++j)
                if(ans < (dis[i] + dis[j] + map[i][j]) / 2.0 && map[i][j] != INF){
                    flag = true;
                    ans = (dis[i] + dis[j] + map[i][j]) / 2.0;
                    first = i;second = j;//升序输出
                }
        }
        printf("System #%d\n", system++);
        if(!flag) printf("The last domino falls after %.1f seconds, at key domino %d.\n\n", ans, first);
        else printf("The last domino falls after %.1f seconds, between key dominoes %d and %d.\n\n", ans, first, second);
    }
    return 0;
}
~~~

---

## 作者：Harry_Hedwig (赞：0)

>~~哭着承认这是一道**好**题~~。

# 0x00 思路
老规矩，先看题。
>给定由多米诺骨牌组成的系统，计算**最后一个**多米诺骨牌在何时何地倒下。当**一个关键**的多米诺骨牌倒下时，**连接到该关键多米诺骨牌的所有多米诺骨牌都开始倒下**（**除了那些已经倒下的多米诺骨牌**）。当倒下的多米诺骨牌到达尚未倒下的其他关键多米诺骨牌时，这些**关键多米诺骨牌也会倒下并且引起与它们相连的多米诺骨牌开始倒下**。多米诺骨牌行可能会从**任何一端**开始倒下。**甚至有可能同一多米诺骨牌行从两端开始倒下**，在这种情况下，该行倒下的最后一张多米诺骨牌位于其行两端的关键多米诺骨牌之间。您可以假设行中的多米诺骨牌以**均匀的速度**倒下（即为 $1s$）。

仍然看不懂？试试这个：
>关于多米诺骨牌游戏，有 $n$ 个关键骨牌，**关键骨牌之间都有一行普通骨牌**。告诉你关键骨牌**之间一行**骨牌倒下所需要的时间。开始时推倒编号为 $1$ 的关键骨牌，问你最后一个骨牌倒下的时间和位置。（**两个相邻关键骨牌可以同时倒下，则中间骨牌在两个关键骨牌之后倒下**）。

一开始看到题实际上是没有什么思路的。让我们分析分析样例：
```c
3 3
1 2 5
1 3 5
2 3 5
```
嘶……这个输入……有点像图啊。那我们把它理解成图试试看？
```c
n/*点数*/ m/*边数*/
u/*起点*/ v/*终点*/ w/*权值*/
//无向边
```
而我们的问题就成了：寻找权值最大的 点 / 边 即可。

那么由于起点固定（$1$），所以只需要打一个单源最短路，点就处理完了。

接下来看边。

由于已知：在这两个关键多米诺骨牌之间可以有一个普通骨牌。

因为我们可以在两个关键骨牌之间把普通骨牌任意摆放，那么我们可以近似理解成：在两个关键骨牌之间有无数个普通骨牌，而这些普通骨牌倒下的时间为这两个关键骨牌之间最后一块普通骨牌倒下的时间。

而我们在这两块关键骨牌之间能找到的最晚倒下的骨牌就一定是 $\dfrac{u+v+w}{2}$（把证明放在最后来写），暴力查找即可。

知道这些之后，我们就可以写出一份~~成熟的~~代码了。

但是，在这之前…… 
# 0x01 注意
**请仔细看输出格式以及样例输出！！！！！！**

第一，**多组输入输出**。

第二，不要忘了**在每组数据后输出一个空行**。

第三，注意一下：

**S**ystem #1

The last domino falls after 27.0 seconds, at key **domino** 2.

**S**ystem #2

The last domino falls after 7.5 seconds, between key **dominoes** 2 and 3.

第四，普通骨牌两边的关键骨牌**升序输出**。


~~血和泪的教训 QAQ~~
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,eat,times,d[100005];
bool b[100005];
typedef struct _dianquan
{
	int to,times;
}E;
bool operator<(const _dianquan& a,const _dianquan& b)
{
	return a.times>b.times;
}
E t1,t2;
int G[505][505];
void bl(int first)//单源最短路
{
	//清空数组+初始化
	memset(d,0x3f,sizeof(d));
	memset(b,0,sizeof(b));
	d[first]=0;
	priority_queue<E>q;
	b[first]=1;
	t1.to=first;
	t1.times=0;
	q.push(t1);
    
    //开始松弛操作
	int i;
	while(!q.empty())
	{
		int now=q.top().to;
		q.pop();
		b[now]=0;
		for(i=1;i<=n;i++)
		{
			if(G[now][i]<G[0][0]&&d[i]>d[now]+G[now][i])
			{
				d[i]=d[now]+G[now][i];
				if(!b[i])
				{
					b[i]=1;
					t1.to=i;
					t1.times=G[now][i];
					q.push(t1);
				}
			}
		}
	}
}
int main()
{
	int i,j,first,t=0,u,v,w;
	while(scanf("%d %d",&n,&m)!=EOF&&n)//多组输入输出
	{
		t++;
		memset(G,0x3f,sizeof(G));
		for(i=1;i<=n;i++)
			G[i][i]=0;
		for(i=0;i<m;i++)
		{
			scanf("%d %d %d",&u,&v,&w);
			G[u][v]=G[v][u]=w;
		}
		bl(1);
		double keymax=0;
		int keywhere=1;
		for(i=1;i<=n;i++)//最晚落下的关键骨牌
		{
			if(d[i]>keymax)
			{
				keymax=d[i];
				keywhere=i;
			}
		}
		double unkeymax=0;
		int unkey_little=0,unkey_bigger=0;
		for(i=1;i<=n;i++)//最晚落下的普通骨牌
		{
			for(j=i+1;j<=n;j++)
			{
				if((d[i]+d[j]+G[i][j])/2.0>unkeymax&&G[i][j]<G[0][0])
				{
					unkeymax=(d[i]+d[j]+G[i][j])/2.0;
					unkey_little=i;
					unkey_bigger=j;
				}
			}
		}
		printf("System #%d\n",t);
		if(keymax>=unkeymax)//至于为什么是>=，详见后面证明的情况2
			printf("The last domino falls after %.1lf seconds, at key domino %d.\n\n",keymax,keywhere);
		else
			printf("The last domino falls after %.1lf seconds, between key dominoes %d and %d.\n\n",unkeymax,unkey_little,unkey_bigger);
	}
	return 0;
}
```

# 0x02 证明
对于任一条边来说只有两种情况。

1. 这条边无法使其左右两边任何一个关键骨牌倒下（即左右两边的关键骨牌让这条边上的骨牌倒下）。

让我们看一下模式图：

![](https://cdn.luogu.com.cn/upload/image_hosting/elkbo0wg.png)

众所周知，多米诺骨牌只要一碰就倒，这也是为什么用其做出的艺术品十分短命。因此在长为 $w$ 的线段上左端点和右端点相遇的点最后下落。（令 $u\le v$）而这个点掉落的时间即为

$$v+[w-(v-u)\times 1]\div 2=v+\dfrac{w-v+u}{2}=\dfrac{u+v+w}{2}$$

得证。
2. 当某一边的关键骨牌倒下后，另一个关键骨牌会因这条边的存在而倒下。
同样看一下（假设 $u$ 先倒）：

![](https://cdn.luogu.com.cn/upload/image_hosting/8hwp81jq.png)

那么我们可以得到 $v=u+w$，而在此情况下 $\dfrac{u+v+w}{2}=\dfrac{2(u+w)}{2}=u+w=v$，也即是此普通骨牌在关键骨牌处，所以为了防止这样的错误发生，我们可以优先选择关键骨牌（即代码中的 `if(keymax>=unkeymax)`）然后才是普通骨牌。

那么至此，情况就考虑完了，接着这篇题解也该结束了，我们下次再见！

---

## 作者：wzkdh (赞：0)

本题为计算多米诺骨牌全部倒下的时间，因为一排只要在第一次被推的时候就开始倒下，所以是一个最短路的题目，而全部倒下的时间是最后一个倒下的时间，所以答案最短路中最长的时间。

以关键牌为结点，普通牌为边构造无向图；
关键牌i倒下的时刻：最短路径长度dis(i)；

但是本题还有可能最后在边上倒下，所以要二外考虑这种情况，具体情况如下。

普通牌（边）完全倒下的时刻：


$t(i--j)$ = $(dis(i)+dis(j)+e(i,j))/2.0$


$t1$ = $max${ $dis(i)$ }


$t2$ = $max${ $t(i--j)$ }


$ans$ = $max(t1, t2)$

本题的输出略有难度，可以参考代码：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
int n,m,tnt,g[510],v[510];
double d[510];
struct edge{
	int to,w,nxt,from;
	double t;
}b[100000];

struct node{
	int v,step;
	bool operator < (const node x)const{
			return step>x.step;
			}
};

priority_queue<node> p;

void addn(int x,int y,int w)
{
	b[tnt].w=w;
	b[tnt].to=y;
	b[tnt].from=x;
	b[tnt].nxt=g[x];
	g[x]=tnt++;
}

void dic(int s)
{
	memset(d,0x42,sizeof(d));
	d[s]=0;
	p.push((node){s,0});
	while(!p.empty())
	{
		node cur=p.top();
		p.pop();
		int t=cur.v;
		if(v[t]==0)
		{
			for(int i=g[t];i!=-1;i=b[i].nxt)
			{
				if(v[b[i].to]==0&&d[b[i].to]>d[t]+b[i].w)
				{
					d[b[i].to]=d[t]+b[i].w;
					p.push((node){b[i].to,d[b[i].to]});
				}
			}
		}
	}
}

int main()
{
	int c=1;
	while(cin>>n>>m)
	{
		memset(g,-1,sizeof(g));
		memset(v,0,sizeof(v));
		if(!n&&!m)
			return 0;
		for(int i=0;i<m;i++)
		{
			int a,b,t;
			cin>>a>>b>>t;
			addn(a,b,t);
			addn(b,a,t);
		}
		dic(1);
		for(int i=0;i<99999;i++)
		{
			b[i].t=(d[b[i].from]+d[b[i].to]+b[i].w)/2.0;
		}
		int ans=0,bd;
		double maxn=0;
		for(int i=0;i<99999;i++)
		{
			if(b[i].t>maxn&&b[i].t<100000000)
			{
				ans=i;
				maxn=b[i].t;
				bd=0;
			}
		}
		for(int i=0;i<509;i++)
		{
			if(d[i]>=maxn&&d[i]<100000000)
			{
				ans=i;
				maxn=(double)d[i];
				bd=1;
			}
		}
		cout<<"System #"<<c<<endl;
		c++;
		cout<<"The last domino falls after ";
		if(bd==1)
		printf("%.1f",maxn);
		else
		printf("%.1f",maxn);
		cout<<" seconds,";
		if(bd==0)
		{
			cout<<" between key dominoes "<<b[ans].from<<" and "<<b[ans].to<<".";
		}
		else
		{
			cout<<" at key domino "<<ans<<".";
		}
		cout<<endl;
		cout<<endl;
		tnt=0;
		memset(b,0,sizeof(b));
	}
}

---

## 作者：4帅气的牛仔4 (赞：0)

题意：有一些摆好的多米诺骨牌，推倒第一块，求最后倒下骨牌的位置和时间。

最短路。利用dijistra算法計算最短路，枚舉環找到最長的，輸出。

題目要求最后到下的骨牌，即为路径中到1号骨牌最短路最远；

因为可能存在环路，則最后在两个骨牌间倒下；

首先，计算骨牌1的单元最短路；

然后，枚举所有的最短路的环，找到最长的路径即可。

# code：
```cpp
#include <cstdio>
#include <cstdlib>
 
double oo = 1e20;
double maps[505][505];
double dist[505];
int    used[505];
 
int main()
{
	int n, m, u, v, s, cases = 1;
	while (~scanf("%d%d",&n,&m) && n) {
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= n; ++ j) {
				maps[i][j] = oo;
			} 
			maps[i][i] = 0;
		}
		for (int i = 1; i <= m; ++ i) {
			scanf("%d%d%d",&u,&v,&s);
			maps[u][v] = s;
			maps[v][u] = s;
		}
		
		for (int i = 1; i <= n; ++ i) {
			dist[i] = oo;
			used[i] = 0;
		}
		dist[1] = 0;
		used[1] = 1;
		int now = 1;
		for (int i = 2; i <= n; ++ i) {
			for (int j = 2; j <= n; ++ j) {
				if (maps[now][j] && dist[j] > dist[now] + maps[now][j]) {
					dist[j] = dist[now] + maps[now][j];
				}
			}
			
			double min = oo;
			for (int j = n; j >= 1; -- j) {
				if (!used[j] && dist[j] < min) {
					now = j;
					min = dist[j];
				}
			}
			used[now] = 1;
		}
		
		double ans = dist[now];
		int p1 = 1, p2 = 1, flag = 0;
		for (int i = 1; i <= n; ++ i) {
			for (int j = i+1; j <= n; ++ j) {
				if (maps[i][j] < oo && ans < 0.5*(dist[i]+dist[j]+maps[i][j])) {
					ans = 0.5*(dist[i]+dist[j]+maps[i][j]);
					p1 = i;
					p2 = j;
					flag = 1;
				}
			}
		}
		
		printf("System #%d\nThe last domino falls after %.1lf ",cases ++,ans);
		if (!flag) {
			printf("seconds, at key domino %d.\n\n",now);
		}else {
			printf("seconds, between key dominoes %d and %d.\n\n",p1,p2);
		}
	}
	
	return 0;
}
```


---

