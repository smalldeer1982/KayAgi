# [USACO4.2] 草地排水Drainage Ditches

## 题目背景

在农夫约翰的农场上，每逢下雨，贝茜最喜欢的三叶草地就积聚了一潭水。这意味着草地被水淹没了，并且小草要继续生长还要花相当长一段时间。因此，农夫约翰修建了一套排水系统来使贝茜的草地免除被大水淹没的烦恼（不用担心，雨水会流向附近的一条小溪）。作为一名一流的技师，农夫约翰已经在每条排水沟的一端安上了控制器，这样他可以控制流入排水沟的水流量。

## 题目描述

农夫约翰知道每一条排水沟每分钟可以流过的水量，和排水系统的准确布局（起点为水潭而终点为小溪的一张网）。需要注意的是，有些时候从一处到另一处不只有一条排水沟。

根据这些信息，计算从水潭排水到小溪的最大流量。对于给出的每条排水沟，雨水只能沿着一个方向流动，注意可能会出现雨水环形流动的情形。

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 4.2

**【数据范围】**

对于 $100 \%$ 的数据，$0 \le N, M \le 200$，$0 \le C_i \le {10}^7$。

## 样例 #1

### 输入

```
5 4
1 2 40
1 4 20
2 4 20
2 3 30
3 4 10```

### 输出

```
50```

# 题解

## 作者：KevinYu (赞：113)

### 注意:在此出现的代码均不保证可以AC，代码是我在AC这道题两个月以上后临时敲的，仅为笔者在写这篇题解时临时敲出来的，未进行过正确性验证，请不要尝试使用某两个快捷键。   
相当经典的一道网络流题目。        
分析题意，发现从1-M的最大流即为所求。    
刚好在这里介绍几个网络流算法(会网络最大流算法的同学们就可以跳过了):        
算法1.EK(Edmond-Karp)算法:       
EK是一个**增广路**算法。         
介绍增广路之前，我们要先介绍一个概念，**残余网络**    ：   
一个图的残余网络，指图中边容量与当前流量的差值边构成的集合。      
简单来说，就是流过一个流之后，我们的路径减少的容量。     
这个算法是基于这样一个事实的:     
残余网络中的任何一个从终点到起点的有向路径都对应着原图中的一条增广路径。          
我们将原图中的容量减去当前流量的动作叫做增广。     
但是，我们当前做出的选择未必是最优的，所以我们对每条边建立一条反向边，容量为正向边减少的容量之和。    
我们一直进行增广操作，直到我们无法在进行增广:已经**没有**可以从s流向t的流了，路径**堵塞**了。     
我们过一遍算法流程(以最小费用最大流为范例):     
1.我们需要用一个遍历算法来判断有没有从s到达t的流。    
只要能从s流向t，我们就进行增广。   
由于我们这里的是最小费用最大流，我们使用spfa来判断:
```cpp
void mcmf()
{
    while(spfa(s,t))
    {
```
我们将在讲完这个算法主过程后展示用于判断的spfa代码。                 
```cpp
    while(spfa(s,t))
    {
        int now=t;
        maxf+=flow[t];
        minc+=dist[t]*flow[t];
```
我们用```last[i]```表示流到i点的当前流量。    
根据到达t点的当前流量，我们更新网络总最大流。   
我们用```pre[i]```表示点i的前驱(即路径上i的**前一个**点)       
用```last[i]```表示路径中指向i的边(即**要**进行**流量减少**的边) 
```cpp
        while(now!=s)
        {
            a[last[now]].flow-=flow[t];
            a[last[now]^1].flow+=flow[t];
            now=pre[now];
        }
    }
}
```
我们再顺着前驱往前回溯，并沿途更新正反两条边的流量。         
mcmf主过程完整代码:
```cpp
void mcmf()
{
    while(spfa(s,t))
    {
        int now=t;
        maxf+=flow[t];
        minc+=dist[t]*flow[t];
        while(now!=s)
        {
            a[last[now]].flow-=flow[t];
            a[last[now]^1].flow+=flow[t];
            now=pre[now];
        }
    }
}
```
spfa过程详解:      
初始化：      
初始化中，我们要将当前最大流，当前最小费用置为INF，以及将vis数组置为0。
同时，将```dist[s]```置为0，将```pre[s]```置为-1(代表没有前驱)，再将s入队。      
```cpp
bool spfa(int s,int t)
{
    queue<int> q;
    memset(vis,0,sizeof(vis));
    memset(flow,INF,sizeof(flow));
    memset(dist,INF,sizeof(dist));
    q.push(s);
    dist[s]=0;
    pre[t]=-1;
    vis[s]=1;
```
我们与普通的spfa过程一样，顺序取出，遍历每个点:
```cpp
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        vis[now]=0;
        for(int i=head[now];i!=-1;i=a[i].next)
        {
            int v=a[i].to;
```
然后顺着最短路走。        
在这里，有几点要注意：       
1.我们跑的是**网络流**算法，所以我们只能经过**剩余流量大于零的路径**          
2.我们在这里要记录pre数组和last数组的值。      
3.有些人可能会怀疑spfa算法跑网络流的**正确性**，但由于我们只在**流量不为零的路径**上进行松弛，所以我们的spfa算法是正确的(我们取的**最短路径**也必定是一条**增广路径**)。      
4.我们在更新flow数组时，记得要取**min值**。
```cpp
            if(a[i].flow>0&&dist[v]>dist[now]+a[i].cost)
            {
                dist[v]=dist[now]+a[i].cost;
                pre[v]=now;
                last[v]=i;
                flow[v]=min(flow[now],a[i].flow);
                if(!vis[v])
                {
                    q.push(v);
                    vis[v]=1;
                }
```
算法结束:       
在这里的的spfa是一个判断算法，所以我们最后要输出一个bool值，在这里，我们判断```pre[t]```是否为-1即可。(即是否能够流向t)
```
            }
        }
    }
    return pre[t]!=-1;
}
```
spfa过程代码
```cpp
bool spfa(int s,int t)
{
    queue<int> q;
    memset(vis,0,sizeof(vis));
    memset(flow,INF,sizeof(flow));
    memset(dist,INF,sizeof(dist));
    q.push(s);
    dist[s]=0;
    pre[t]=-1;
    vis[s]=1;
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        vis[now]=0;
        for(int i=head[now];i!=-1;i=a[i].next)
        {
            int v=a[i].to;
            if(a[i].flow>0&&dist[v]>dist[now]+a[i].cost)
            {
                dist[v]=dist[now]+a[i].cost;
                pre[v]=now;
                last[v]=i;
                flow[v]=min(flow[now],a[i].flow);
                if(!vis[v])
                {
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
    return pre[t]!=-1;
}
```
EK算法求解草地排水完整代码：
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<algorithm>
#include<complex>
#include<iostream>
#include<map>
#include<queue>
#include<vector>
#define INF 0x3f3f3f3f
using namespace std;
struct edge
{
    int to,next,flow,cost;
}a[2000020];
int cnt(0);
int n,m,s,t;
int x,y,z,f;
int flow[1000010],head[1000010];
int dist[1000010],vis[1000010];
int pre[1000010],last[1000010];
int maxf(0),minc(0);
void addedge(int xi,int yi,int fi,int ci)
{
    a[cnt].to=yi;
    a[cnt].next=head[xi];
    a[cnt].flow=fi;
    a[cnt].cost=ci;
    head[xi]=cnt++;
}
bool spfa(int s,int t)
{
    queue<int> q;
    memset(vis,0,sizeof(vis));
    memset(flow,INF,sizeof(flow));
    memset(dist,INF,sizeof(dist));
    q.push(s);
    dist[s]=0;
    pre[t]=-1;
    vis[s]=1;
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        vis[now]=0;
        for(int i=head[now];i!=-1;i=a[i].next)
        {
            int v=a[i].to;
            if(a[i].flow>0&&dist[v]>dist[now]+a[i].cost)
            {
                dist[v]=dist[now]+a[i].cost;
                pre[v]=now;
                last[v]=i;
                flow[v]=min(flow[now],a[i].flow);
                if(!vis[v])
                {
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
    return pre[t]!=-1;
}
void mcmf()
{
    while(spfa(s,t))
    {
        int now=t;
        maxf+=flow[t];
        minc+=dist[t]*flow[t];
        while(now!=s)
        {
            a[last[now]].flow-=flow[t];
            a[last[now]^1].flow+=flow[t];
            now=pre[now];
        }
    }
}
int main()
{
    memset(head,-1,sizeof(head));
    scanf("%d%d",&m,&n);
    s=1,t=n;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&x,&y,&z,&f);
        addedge(x,y,z,f);
        addedge(y,x,0,-f);
    }
    mcmf();
    printf("%d",maxf);
    return 0;
}

```
算法2.Dinic算法:          
Dinic算法也是一个增广路算法。       
相信你们在看了前面的EK算法后，对增广路已经有了一定的了解。        
由于我们一般的增广路算法可能会一直会对同一条路径进行增广，会十分地浪费时间。       
例:       
![https://i.loli.net/2018/12/04/5c060e0682acd.jpg](https://i.loli.net/2018/12/04/5c060e0682acd.jpg)          
这可以说是一个经典例子了。       
考虑从2到3的，容量为1的有向路径，我们会反复地增广这条路径，甚至可能会对其进行1998次增广,十分的浪费时间。         
所以我们引入了**分层图**的概念:      
我们把图分为k层，一个点的层数对应其在bfs过程中的深度。         
在这种情况下，我们只从层次小的点走向层次大的点。      
我们用一个bfs过程来完成分层。     
bfs分层详解:      
与EK的spfa相似，Dinic的bfs过程也是一个判断函数，判断是否能从s走到t。      
来过一遍bfs流程:        
1.没什么好说的初始化：
```cpp
bool bfs(int s)
{
	queue<int> q;
	while(!q.empty())q.pop();
	memset(dep,-1,sizeof(dep));
	dep[s]=1;
	q.push(s);
```
注意这里将s的深度设为了1。        
2.接下来的过程与一般的bfs类似。       
只是注意这里要记录下深度(```dep[i]```)，并且判断流量是否为零(与EK的技巧是一样的)
```cpp
	while(!q.empty())
	{
		int t=q.front();
		q.pop();
		for(int i=head[t];i!=-1;i=a[i].next)
		{
			int v=a[i].to;
			int f=a[i].flow;
			if((f>0)&&(dep[v]==-1))
			{
				dep[v]=dep[t]+1;
				q.push(v);
			}
```
在结束时要记得返回bfs的判断值。
如果```dep[t]```不为-1时代表我们能搜到t。     
如下:
```cpp
		}
	}
	return dep[t]!=-1;
}
```
bfs代码:
```cpp
bool bfs(int s)
{
	queue<int> q;
	while(!q.empty())q.pop();
	memset(dep,-1,sizeof(dep));
	dep[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int t=q.front();
		q.pop();
		for(int i=head[t];i!=-1;i=a[i].next)
		{
			int v=a[i].to;
			int f=a[i].flow;
			if((f>0)&&(dep[v]==-1))
			{
				dep[v]=dep[t]+1;
				q.push(v);
			}
		}
	}
	return dep[t]!=-1;
}
```
bfs结束之后，我们使用dfs进行一次遍历，并且沿路更新我们的当前流。      
dfs过程详解:         
我们规定int dfs(int u,int dist)代表当前在流入的流量为dist，编号为u的点,返回的值为当前网络可行的最大流量。        
首先是边界条件：
```cpp
int dfs(int u,int dist)
{
	if(u==t)return dist;
```
如果搜到了终点，就输出流入的流量。      
然后我们向下一个点进行搜索:
```cpp
	for(int i=head[u];i!=-1;i=a[i].next)
	{
		int v=a[i].to;
		int f=a[i].flow;
```
在这之后，我们试图对每一个当前点能到达的，且层数比当前点大一的点进行递归。          
但若网络在这里的流量为0(即被"阻塞"了)，就不再行考虑了。
```cpp
		if((dep[v]==dep[u]+1)&&(f!=0))
		{
			int df(dfs(v,min(dist,f)));
```
df代表"Δf"(流量差)，即当前状况下可行的最大流量。
我们依据这个，对每个流经的边进行更新。
```cpp
			if(df>0)
			{
				a[i].flow-=df;
				a[i^1].flow+=df;
				return df;
			}
		}
	}
	return 0;
}
```
dfs过程完整代码:      
```cpp
int dfs(int u,int dist)
{
	if(u==t)return dist;
	for(int i=head[u];i!=-1;i=a[i].next)
	{
		int v=a[i].to;
		int f=a[i].flow;
		if((dep[v]==dep[u]+1)&&(f!=0))
		{
			int df(dfs(v,min(dist,f)));
			if(df>0)
			{
				a[i].flow-=df;
				a[i^1].flow+=df;
				return df;
			}
		}
	}
	return 0;
}
```
接下来分析dinic的主过程，有了我们前面的基础支持，理解起来就不会太难了。       
首先我们初始化最大流:       
```cpp
void dinic()
{
	maxf=0;
	int nowf(0);
```
然后我们不断地尝试去构建分层图。
```cpp
	while(bfs(s))
	{
		nowf=INF;
```
每构建一次分层图，我们就尝试一次增广,并更新流量:
```
		while(nowf)
		{
			nowf=dfs(s,INF);
			maxf+=nowf;
		}
	}
}
```
这样就结束了。   
dinic主过程完整代码:    
```cpp
void dinic()
{
	maxf=0;
	int nowf(0);
	while(bfs(s))
	{
		nowf=INF;
		while(nowf)
		{
			nowf=dfs(s,INF);
			maxf+=nowf;
		}
	}
}
```
dinic算法求解草地排水完整代码:   
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<algorithm>
#include<complex>
#include<iostream>
#include<map>
#include<queue>
#include<vector>
#define INF 0x3f3f3f3f
using namespace std;
struct edge
{
	int next,to,flow;
}a[2000020];
int n,m;
int s,t;
int cnt(0);
int head[1000010];
int dep[1000010];
int maxf(0);
void addedge(int xi,int yi,int fi)
{
	a[cnt].to=yi;
	a[cnt].next=head[xi];
	a[cnt].flow=fi;
	head[xi]=cnt++;
}
bool bfs(int s)
{
	queue<int> q;
	while(!q.empty())q.pop();
	memset(dep,-1,sizeof(dep));
	dep[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int t=q.front();
		q.pop();
		for(int i=head[t];i!=-1;i=a[i].next)
		{
			int v=a[i].to;
			int f=a[i].flow;
			if((f>0)&&(dep[v]==-1))
			{
				dep[v]=dep[t]+1;
				q.push(v);
			}
		}
	}
	return dep[t]!=-1;
}
int dfs(int u,int dist)
{
	if(u==t)return dist;
	for(int i=head[u];i!=-1;i=a[i].next)
	{
		int v=a[i].to;
		int f=a[i].flow;
		if((dep[v]==dep[u]+1)&&(f!=0))
		{
			int df(dfs(v,min(dist,f)));
			if(df>0)
			{
				a[i].flow-=df;
				a[i^1].flow+=df;
				return df;
			}
		}
	}
	return 0;
}
void dinic()
{
	maxf=0;
	int nowf(0);
	while(bfs(s))
	{
		nowf=INF;
		while(nowf)
		{
			nowf=dfs(s,INF);
			maxf+=nowf;
		}
	}
}
int main()
{
	memset(head,-1,sizeof(head));
	scanf("%d%d",&m,&n);
	s=1,t=n;
	for(int i=1;i<=m;i++)
	{
		int x,y,f;
		scanf("%d%d%d",&x,&y,&f);
		addedge(x,y,f);
		addedge(y,x,0);
	}
	dinic();
	printf("%d",maxf);
	return 0;
}

```
算法3.ISAP(Improved Shortest Augmenting Path，更优最短增广路径算法):     
我们发现，其实在dinic算法中，每次求分层图带来的区别并不大。      
例:(4个点，5条边，从4号点到3号点)
```cpp
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 40
```
在上例中，一共会求解3次分层图，得到的结果如下:
```cpp
第一次求解时:
第一层:4
第二层:2,3
第三层:1
第四层:空

第二次求解时:
第一层:4
第二层:2
第三层:1,3
第四层:空

第三次求解时:
第一层:4
第二层:2
第三层:1
第四层:3
```
可以发现，其实只有3号节点的层数发生了改变，而且每次改变都是层次+1的过程。   
可不可以省掉分层图重复的求解步骤呢?     
答案是可以。    
我们在ISAP算法中，只跑一次bfs,处理出每个点的深度，然后对于每一次更新后的点，我们将其进行"推移"——将它的深度+1。       
注意我们加上的几个优化:      
1.gap优化:```gap[i]```代表层数为i的分层图中的点数，若一个层次没有点了，就将当前点置为最高层点。      
2.当前弧优化:```arcs[i]```记录head的一个副本。    
我们来看看isap的bfs过程:       
我们还是老套路，过一遍算法流程。      
初始化:
```cpp
void bfs(int s)
{
	memset(dep,0,sizeof(dep));
	memset(gap,0,sizeof(gap));
	queue<int>q;
	dep[s]=1;
	gap[1]=1;
	q.push(s);
	while(!q.empty())
	{
		int t=q.front();
		q.pop();
```
我们除了处理点深度外，还要记录一个gap数组。      
别忘了将gap的第一项置为1(s的层次为1)。     
然后还是记录下深度，并更新gap数组:
```cpp
		for(int i=head[t];i!=-1;i=a[i].next) 
		{
			int v=a[i].to;
			if(!dep[v])
			{
				q.push(v);
				dep[v]=dep[t]+1;
				gap[dep[v]]++;
			}
		}
	}
}
```
bfs过程:  
```cpp
void bfs(int s)
{
	memset(dep,0,sizeof(dep));
	memset(gap,0,sizeof(gap));
	queue<int>q;
	dep[s]=1;
	gap[1]=1;
	q.push(s);
	while(!q.empty())
	{
		int t=q.front();
		q.pop();
		for(int i=head[t];i!=-1;i=a[i].next) 
		{
			int v=a[i].to;
			if(!dep[v])
			{
				q.push(v);
				dep[v]=dep[t]+1;
				gap[dep[v]]++;
			}
		}
	}
}
```
然后在dfs过程中也有一些小小的改动:      
在前面的都跟dinic的一样:
```cpp
int dfs(int u,int dist)
{
	if (u==t)return dist;
	int sum(0);
	int nowf(0);
	for (int i=arcs[u];i!=-1;i=a[i].next)
	{
		int v=a[i].to;
		if (dep[u]==dep[v]+1)
		{
			nowf=dfs(v,min(dist,a[i].flow));
			sum+=nowf;
			dist-=nowf;
			a[i].flow-=nowf;
			a[i^1].flow+=nowf;
			if(!dist)return sum;
		}
	}
```
但在算法结束前，我们要记录下每一个点的"偏移"。    
这样子我们就可以不用使用多次bfs来更新层次了:
```cpp
	if(!(--gap[dep[u]]))dep[s]=n+1;
	dep[u]++;
	gap[dep[u]]++;
	arcs[u]=head[u];
	return sum; 
} 
```
dfs过程:
```cpp
int dfs(int u,int dist)
{
	if (u==t)return dist;
	int sum(0);
	int nowf(0);
	for (int i=arcs[u];i!=-1;i=a[i].next)
	{
		int v=a[i].to;
		if (dep[u]==dep[v]+1)
		{
			nowf=dfs(v,min(dist,a[i].flow));
			sum+=nowf;
			dist-=nowf;
			a[i].flow-=nowf;
			a[i^1].flow+=nowf;
			if(!dist)return sum;
		}
	}
	if(!(--gap[dep[u]]))dep[s]=n+1;
	dep[u]++;
	gap[dep[u]]++;
	arcs[u]=head[u];
	return sum; 
} 
```
isap主过程:        
isap的主过程也十分的简单，主要分为以下几步:      
1.分层图初始化。    
2.通过dfs来更新最大流和分层图。    
isap主过程代码:
```cpp
void isap()
{
	maxf=0;
	bfs(t);
	memcpy(&arcs[1],&head[1],sizeof(int)*n);
	maxf=dfs(s,INF);
	while(dep[s]<=n)maxf+=dfs(s,INF);
}
```
isap求解草地排水完整代码:     
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<algorithm>
#include<complex>
#include<iostream>
#include<map>
#include<queue>
#include<vector>
#define INF 0x3f3f3f3f
using namespace std;
struct edge
{
	int next,to,flow;
}a[2000020];
int n,m;
int s,t;
int cnt(0);
int head[1000010];
int dep[1000010];
int arcs[1000010];
int gap[1000010];
int maxf(0);
void addedge(int xi,int yi,int fi)
{
	a[cnt].to=yi;
	a[cnt].next=head[xi];
	a[cnt].flow=fi;
	head[xi]=cnt++;
}
void bfs(int s)
{
	memset(dep,0,sizeof(dep));
	memset(gap,0,sizeof(gap));
	queue<int>q;
	dep[s]=1;
	gap[1]=1;
	q.push(s);
	while(!q.empty())
	{
		int t=q.front();
		q.pop();
		for(int i=head[t];i!=-1;i=a[i].next) 
		{
			int v=a[i].to;
			if(!dep[v])
			{
				q.push(v);
				dep[v]=dep[t]+1;
				gap[dep[v]]++;
			}
		}
	}
}
int dfs(int u,int dist)
{
	if (u==t)return dist;
	int sum(0);
	int nowf(0);
	for (int i=arcs[u];i!=-1;i=a[i].next)
	{
		int v=a[i].to;
		if (dep[u]==dep[v]+1)
		{
			nowf=dfs(v,min(dist,a[i].flow));
			sum+=nowf;
			dist-=nowf;
			a[i].flow-=nowf;
			a[i^1].flow+=nowf;
			if(!dist)return sum;
		}
	}
	if(!(--gap[dep[u]]))dep[s]=n+1;
	dep[u]++;
	gap[dep[u]]++;
	arcs[u]=head[u];
	return sum; 
} 
void isap()
{
	maxf=0;
	bfs(t);
	memcpy(&arcs[1],&head[1],sizeof(int)*n);
	maxf=dfs(s,INF);
	while(dep[s]<=n)maxf+=dfs(s,INF);
}
int main()
{
	memset(arcs,-1,sizeof(arcs));
	memset(head,-1,sizeof(head));
	scanf("%d%d",&m,&n);
	s=1,t=n;
	for(int i=1;i<=m;i++)
	{
		int x,y,f;
		scanf("%d%d%d",&x,&y,&f);
		addedge(x,y,f);
		addedge(y,x,0);
	}
	isap();
	printf("%d",maxf);
	return 0;
}

```
算法4(没错，还有):HLPP算法       
等着看ff的同学们很抱歉，ff下线了~~其实是我不会~~。    
相信大家已经看增广路看得脑袋都疼了。所以我来介绍一个~~玄学~~算法，不依赖增广路的那种。    
HLPP(Highest Label Preflow Push，最高标号预流推进)算法，是一个**预流推进**算法。      
预流推进算法需要了解几个定义:      
**超额流**:预流推进算法允许我们将流量**存储**在**任意**节点中。存储在**非原点**的节点中的流量就叫做超额流。       
**推送**:一个节点将其超额流送到下一个节点的过程叫做推送。    
**节点高度**:为了防止有些节点打太极(你推送给我，我推送给你，一直推送到TLE)，我们给每一个节点设定一个**高度**(类似于分层图)，并规定推送操作只能从**高点向低点**进行。    
特别地，我们将原点的高度设为n。以保证它可以在一开始流向任何节点。      
**重贴标签**：如果一个节点的**超额流**因为自身的**高度过低**而无法被推送，我们就将它**抬高**，这个过程叫重贴标签。      
有了这几个概念，我们就可以预流推进了。           
走一遍算法流程:     
首先是预流推进的bfs，作用是处理出每个点的高度。      
一步一步分析:     
1.先将每一个点的高度都置为INF。
```cpp
il bool bfs()
{
    queue<ll> q;
    memset(h+1,INF,sizeof(ll)*n);
    h[ed]=0;
    q.push(ed);
```
然后我们来一次逆向bfs，来判断是否存在一条从s到t的可行流。      
2.与一般的bfs过程一样，我们利用队列来遍历这张图，并保留当前节点。       
```cpp
    while(!q.empty())
    {
        ll t=q.front();
        q.pop();
        for(re ll i=head[t];i!=-1;i=a[i].next)
        {
            ll v=a[i].to;
```
3.我们对于每一条可行流，我们都将其入队，并更新其高度。      
注意：这里跑的是反向边，而我们通过正向边来判断可行流，所以是```a[i^1].flow```
```cpp
            if(a[i^1].flow&&h[v]>h[t]+1)
            {
                h[v]=h[t]+1;
                q.push(v);
            }
        }
    }
    return h[st]!=INF;
}
```
bfs过程代码:
```cpp
il bool bfs()
{
    queue<ll> q;
    memset(h+1,INF,sizeof(ll)*n);
    h[ed]=0;
    q.push(ed);
    while(!q.empty())
    {
        ll t=q.front();
        q.pop();
        for(re ll i=head[t];i!=-1;i=a[i].next)
        {
            ll v=a[i].to;
            if(a[i^1].flow&&h[v]>h[t]+1)
            {
                h[v]=h[t]+1;
                q.push(v);
            }
        }
    }
    return h[st]!=INF;
}
```
然后是几个关键操作:     
1.重贴标签操作:       
我们重贴标签的操作十分简单，原理就是将u的高度提高到恰好能使流量流向其所能到达的最低点。
```cpp
il void relabel(int u)
{
    h[u]=INF;
    for(re int i=head[u];i!=-1;i=a[i].next)
    {
        int v=a[i].to;
        if((a[i].flow)&&(h[v]+1<h[u]))h[u]=h[v]+1;
    }
}
```
2.推送操作:     
所谓推送，就是将超额流分摊到其他节点上。    
我们来看看算法过程:       
1.由于推送必定只能到一个点的相邻节点，我们就取出其每一个能到达的点:      
```cpp
il void push(int u)
{
    for(re int i=head[u];i!=-1;i=a[i].next)
    {
        int v=a[i].to;
```
然后我们就可以试图推送自己的流量了。    
推送有几个条件：     
1.高度要足够。     
2.边上要有剩余的容量。    
我们用e数组记录下每一个点的超额流量。    
```cpp
        if((a[i].flow)&&(h[v]+1==h[u]))
        {
            ll df=min(e[u],a[i].flow);
            a[i].flow-=df;
            a[i^1].flow+=df;
            e[u]-=df;
            e[v]+=df;
```
如果我们的目标点不是起点或中点，且不再优先队列里，我们就将其入队。
```cpp
            if((v!=st)&&(v!=ed)&&(!vis[v]))
            {
                pq.push(v);
                vis[v]=1;
            }
```
如果都推送完了，就可以结束了。
```cpp
            if(!e[u])break;
        }
    }
}
```
推送过程:
```cpp
il void push(int u)
{
    for(re int i=head[u];i!=-1;i=a[i].next)
    {
        int v=a[i].to;
        if((a[i].flow)&&(h[v]+1==h[u]))
        {
            ll df=min(e[u],a[i].flow);
            a[i].flow-=df;
            a[i^1].flow+=df;
            e[u]-=df;
            e[v]+=df;
            if((v!=st)&&(v!=ed)&&(!vis[v]))
            {
                pq.push(v);
                vis[v]=1;
            }
            if(!e[u])break;
        }
    }
}
```
hlpp主过程:      
我们来逐步分析一下hlpp的主过程:      
我们首先将图中点的高度都处理出来。      
```cpp
inline ll hlpp()
{
    if(!bfs())return 0;
    h[st]=n;
    memset(gap,0,sizeof(int)*(n<<1));
	for(re int i=1;i<=n;i++)if(h[i]!=INF)gap[h[i]]++;
```
然后我们将s点能直接到达的点入栈。       
```cpp
    for(re int i=head[st];i!=-1;i=a[i].next)
    {
        int v=a[i].to;
        if(ll f=a[i].flow)
        {
            a[i].flow-=f;a[i^1].flow+=f;
            e[st]-=f;e[v]+=f;
            if(v!=st&&v!=ed&&!vis[v])
            {
                pq.push(v);
                vis[v]=1;
            }
        }
    }
```
对于每一个原，汇点之外的点，只要它还有**残余**的**超额流**(即e数组中的值不为0)时，就进行推送，推送完后就重新贴标签。     
这样写的时间复杂度为```O(n^2*sqrt(m))```若将贴标签的动作前置（就像算法导论中做的那样），我们就可以得到复杂度为```O(n^3)```的另一种实现方式。   
注意:这里的pq是一个**优先队列**，排序依据是每一个点的高度，以保证当前取出的点最高。        
实现过程：
```cpp
    while(!pq.empty())
    {
        int  t=pq.top();pq.pop();
        vis[t]=0;push(t);
        if(e[t])
        {
            gap[h[t]]--;
            if(!gap[h[t]])
            {
                for(re int v=1;v<=n;v++)
                {
                    if(v!=st&&v!=ed&&h[v]>h[t]&&h[v]<n+1)
                    {
                        h[v]=n+1;
                    }
                }
            }
            relabel(t);gap[h[t]]++;
            pq.push(t);vis[t]=1;
        }
    }
```
hlpp主过程代码:
```cpp
inline ll hlpp()
{
    if(!bfs())return 0;
    h[st]=n;
    memset(gap,0,sizeof(int)*(n<<1));
	for(re int i=1;i<=n;i++)if(h[i]!=INF)gap[h[i]]++;
    for(re int i=head[st];i!=-1;i=a[i].next)
    {
        int v=a[i].to;
        if(ll f=a[i].flow)
        {
            a[i].flow-=f;a[i^1].flow+=f;
            e[st]-=f;e[v]+=f;
            if(v!=st&&v!=ed&&!vis[v])
            {
                pq.push(v);
                vis[v]=1;
            }
        }
    }
    while(!pq.empty())
    {
		int  t=pq.top();pq.pop();
        vis[t]=0;push(t);
        if(e[t])
        {
            gap[h[t]]--;
            if(!gap[h[t]])
            {
                for(re int v=1;v<=n;v++)
                {
                    if(v!=st&&v!=ed&&h[v]>h[t]&&h[v]<n+1)
                    {
                        h[v]=n+1;
                    }
                }
            }
            relabel(t);gap[h[t]]++;
            pq.push(t);vis[t]=1;
        }
    }
    return e[ed];
}
```
使用HLPP求解草地排水:
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<climits>
#include<ctime>
#include<algorithm>
#include<complex>
#include<iostream>
#include<map>
#include<queue>
#include<vector>
#define ll long long
#define INF ((1ll<<31ll)-1ll)*(1<<17ll)*2ll+1ll
#define re register
#define il inline
using namespace std;
struct edge
{
    int to,next;
	ll flow;
}a[2000020];
int head[10010];
int gap[10010];
ll h[10010];
ll e[10010];
int vis[10010];
int cnt(0);
int n,m,st,ed;
struct cmp
{
    il bool operator ()(int xi,int yi)const
    {
        return h[xi]<h[yi];
    }
};
priority_queue<int,vector<int>,cmp> pq;
il void addedge(int xi,int yi,ll fi)
{
    a[cnt].to=yi;
    a[cnt].next=head[xi];
    a[cnt].flow=fi;
    head[xi]=cnt++;
}
il bool bfs()
{
    queue<int> q;
    memset(h+1,INF,sizeof(ll)*n);
    h[ed]=0;
    q.push(ed);
    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        for(re int i=head[t];i!=-1;i=a[i].next)
        {
            int v=a[i].to;
            if(a[i^1].flow&&h[v]>h[t]+1)
            {
                h[v]=h[t]+1;
                q.push(v);
            }
        }
    }
    return h[st]!=INF;
}
il void push(int u)
{
    for(re int i=head[u];i!=-1;i=a[i].next)
    {
        int v=a[i].to;
        if((a[i].flow)&&(h[v]+1==h[u]))
        {
            ll df=min(e[u],a[i].flow);
            a[i].flow-=df;
            a[i^1].flow+=df;
            e[u]-=df;
            e[v]+=df;
            if((v!=st)&&(v!=ed)&&(!vis[v]))
            {
                pq.push(v);
                vis[v]=1;
            }
            if(!e[u])break;
        }
    }
}
il void relabel(int u)
{
    h[u]=INF;
    for(re int i=head[u];i!=-1;i=a[i].next)
    {
        int v=a[i].to;
        if((a[i].flow)&&(h[v]+1<h[u]))h[u]=h[v]+1;
    }
}
inline ll hlpp()
{
    if(!bfs())return 0;
    h[st]=n;
    memset(gap,0,sizeof(int)*(n<<1));
	for(re int i=1;i<=n;i++)if(h[i]!=INF)gap[h[i]]++;
    for(re int i=head[st];i!=-1;i=a[i].next)
    {
        int v=a[i].to;
        if(ll f=a[i].flow)
        {
            a[i].flow-=f;a[i^1].flow+=f;
            e[st]-=f;e[v]+=f;
            if(v!=st&&v!=ed&&!vis[v])
            {
                pq.push(v);
                vis[v]=1;
            }
        }
    }
    while(!pq.empty())
    {
		int  t=pq.top();pq.pop();
        vis[t]=0;push(t);
        if(e[t])
        {
            gap[h[t]]--;
            if(!gap[h[t]])
            {
                for(re int v=1;v<=n;v++)
                {
                    if(v!=st&&v!=ed&&h[v]>h[t]&&h[v]<n+1)
                    {
                        h[v]=n+1;
                    }
                }
            }
            relabel(t);gap[h[t]]++;
            pq.push(t);vis[t]=1;
        }
    }
    return e[ed];
}
signed main()
{
    memset(head,-1,sizeof(head));
    scanf("%d%d",&m,&n);
    st=1;ed=n;
    for(re int i=1;i<=m;i++)
    {
        int x,y;
		ll f;
        scanf("%d%d%lld",&x,&y,&f);
        addedge(x,y,f);
        addedge(y,x,0);
    }
    ll maxf=hlpp();
    printf("%lld",maxf);
    return 0;
}
```

---

## 作者：kouylan (赞：9)

## 题解 P2740 【[USACO4.2]草地排水Drainage Ditches】
### 【题意】
最大流模板。

### 【分析】
网络流中的最大流。

**几个定义**

1. **容量**：每条边上最大可以通过的水流，其实就是每条边的边权。

2. **流量**：每条边实际通过的水流，在具体情况中就是源点流到这条边的水的流量。

显然，**流量$\leq$容量**。

**此篇题解主要讲$Dinic$和$ISAP$两个算法。**

### 【$Dinic$算法】
### 主体思想
我们每一次选取一条路径，就可以求出这条路径上的最大流量$d$。至此，我们可以说这条路径已经没有用了（因为已经被我们算过了）！
接着，我们就可以把这条路径上的所有边的容量减去$d$，这样就可以保证这条路上至少有一条边的容量为$0$。

换句话说，这条路径已经不可能有水流到汇点，也就是这条路径已经被我们切断了。

接着，重复上述所有操作，直到没有水能从源点流到汇点，也就是整张图都被我们切断了。

最后$\Sigma d$就是最大流。

### 主要代码
#### 1. 建图
在此，我们使用邻接矩阵。无需赘述。

#### 2. 反边
我们来看下图
![fanbian](https://cdn.luogu.com.cn/upload/image_hosting/n5ric24y.png)

在此图中，如果选择$1-2$的流量为$9$，$1-4$的流量为$1$，那么答案是$2$。但是显然此图的最大流为$6$（上面的流量是$1$，下面的流量是$5$）。

为什么会发生这样的情况？

那是因为图都是单向边，没有方法让多余的流量流回去，选择其他更好的路。所以要给一个反悔的机会，给每条正边建一条反边，让多余的流量能够顺着反边往回流，选择更好的路径流，以此达到更优的方案。

反边的初始容量（权值）为$0$，在搜索中会修改其容量。

#### 3. $bfs$部分
所以在$bfs$中，我们要求出每个点的深度，如果汇点$t$没有深度，就说明每一条路都被我们搜索过了所有的路径，图已经被我们打断了，就可以停止搜索。
```cpp
bool bfs()
{
	memset(dep,0,sizeof(dep)); //初始化
	dep[s] = 1;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		for(int i=1;i<=n;i++)
			if(a[u][i]>0 && dep[i]==0) //如果这条边没有被打断 && 这个点没有被搜索过
			{
				dep[i] = dep[u]+1;
				q.push(i);
			}
		q.pop();
	}
	return dep[t]!=0; //判断图是否联通
}
```

#### 4. $dfs$部分
通过每次$dfs$，我们可以求出一条路径上的最大流$d$。但是有可能出现像上图那样非最优的情况。所以我们把正边减去$d$，再把反边加上$d$（避免出现流量过多的情况，可以往回流）。

人往高处走，水往低处流。搜索时，要保证深度连续，不然有可能出现回流的情况。

```cpp
int dfs(int x,int flow) //flow:当前路径的流量
{
	if(x==t) //可以流到汇点
		return flow;
	for(int i=1;i<=n;i++)
		if(a[x][i]>0 && dep[i]==dep[x]+1) //如果没有断 && 深度连续
		{
			int d=dfs(i,min(flow,a[x][i])); //计算这条路径上的最大流
			if(d>0)
			{
				a[x][i] -= d; //正边
				a[i][x] += d; //反边
				return d;
			}
		}
	return 0; //出现断层，到不了汇点。
}
```

#### 5. 求最大流的函数
我们知道，每一遍$bfs$都会根据先前更新过的正边和反边，去更新图中每个节点的深度。在此我们要分$2$种情况讨论。

- 当$dep_t>0$时，就说明图是联通的，依然有可行路径我们没有搜到，因此进行$dfs$即可
- 当$dep_t=0$时，说明图已经不连通，即没有可行路径的存在了，因此停止$dfs$即可。

```cpp
int maxflow()
{
	int ans=0;
	while(bfs()) //图是联通的(有可行路径)
	{
		int x=1;
		while(x!=0)
		{
			x = dfs(s,0x3f3f3f3f); //搜索所有的可行路径并计算出其最大流，假设初始流量为无限大
			ans += x;
		}
	}
	return ans;
}
```

下面是AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,s,t,a[5005][5005],dep[5005];
queue<int> q;

bool bfs()
{
	memset(dep,0,sizeof(dep));
	dep[s] = 1;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		for(int i=1;i<=n;i++)
			if(a[u][i]>0 && dep[i]==0)
			{
				dep[i] = dep[u]+1;
				q.push(i);
			}
		q.pop();
	}
	return dep[t]!=0;
}

int dfs(int x,int flow)
{
	if(x==t)
		return flow;
	for(int i=1;i<=n;i++)
		if(a[x][i]>0 && dep[i]==dep[x]+1)
		{
			int d=dfs(i,min(flow,a[x][i]));
			if(d>0)
			{
				a[x][i] -= d;
				a[i][x] += d;
				return d;
			}
		}
	return 0;
}

int maxflow()
{
	int ans=0;
	while(bfs())
	{
		int x=1;
		while(x!=0)
		{
			x = dfs(s,0x3f3f3f3f);
			ans += x;
		}
	}
	return ans;
}

int main()
{
	cin>>n>>m>>s>>t;
	for(int i=1,x,y,z;i<=m;cin>>x>>y>>z,a[x][y]+=z,i++);
	cout<<maxflow()<<endl;
	
	return 0;
}
```

### 【$ISAP$算法】

### 主要思想
与$Dinic$类似，我们每一次选取一条路径，就可以求出这条路径上的最大流量$d$。之后把这条路打断。

最后$\Sigma d$就是最大流。

### 主要部分
#### 1. 建图
在此，我们选取了与之前不一样的前向星见图。
```cpp
int ee=1,h[10005],nex[100005<<1],to[100005<<1],val[100005<<1];

void addedge(int x,int y,int z)
{
	nex[++ee] = h[x]; //边的下标从2开始
	to[ee] = y;
	val[ee] = z;
	h[x] = ee;
}

for(int i=1,x,y,z;i<=m&&cin>>x>>y>>z;i++)
{
	addedge(x,y,z);
	addedge(y,x,0); //反边的初始容量是0
}
```
为什么边要从$2$开始？

在$dfs$时，正边下标时$i$，反边与正边的下标差$1$，所以用$i$^$1$来表示，因此在一开始建图时，正边和反边肯定是$2k$和$2k+1$，其中$k$是整数。

#### 2. 反边
与$Dinic$算法的完全相同，在此就不再赘述。

#### 3. $bfs$部分
在$bfs$中，增加了一个$gap$数组，用来记录每一个深度的节点有多少个，即$gap_i$表示深度为$i$的节点的个数。

重要地，我们要从汇点$t$往源点$s$进行$bfs$，原因之后会讲。
```cpp
void bfs()
{
	queue<int> q;
	q.push(t);
	dep[t] = 1; //把t的深度设为1
	gap[1] = 1;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=h[x];i;i=nex[i])
			if(!dep[to[i]]) //没有搜到过(深度未更新)
			{
				dep[to[i]] = dep[x]+1;
				gap[dep[to[i]]]++;
				q.push(to[i]);
			}
	}
}
```

#### 4. $dfs$部分
每次选取一条路径搜索，我们可以求出一条路径上的最大流$d$。但是有可能出现像上图那样非最优的情况。所以我们把正边减去$d$，再把反边加上$d$。
在最后，因为已经把当前节点的所有边搜索完了，所以可以把这个节点打断，即把$dep_x$++。
```cpp
int dfs(int x,int flow)
{
	if(x==t)
	{
		ans += flow;
		return flow;
	}
	int used=0; //已经计算过(被分配过)的流量
	for(int i=h[x];i;i=nex[i])
		if(dep[to[i]]==dep[x]-1 && val[i]>0) //因为是从t往s进行bfs, 所以是dep[x]-1
		{
			int d=dfs(to[i],min(val[i],flow-used));
			if(d)
			{
				val[i] -= d;
				val[i^1] += d;
				used += d;
			}
			if(used==flow)
				return used;
		}
    //下面才是ISAP的灵魂
	gap[dep[x]]--;
	if(gap[dep[x]]==0) //如果当前深度一个点都没有，说明图已经被打断(不连通)了
		dep[s] = n+1;
	dep[x]++; //把x所连的边打断
	gap[dep[x]]++;
	return used;
}
```

### - 为什么要从$t$到$s$进行$bfs$？
我们还是看这张图
![bfs](https://cdn.luogu.com.cn/upload/image_hosting/n5ric24y.png)

假设我们已经计算好了上面一条路径的最大流，需要把$S-1-2-3-T$这条路径打断。

假设我们从$S$到$T$进行$bfs$，则会把$2$的深度变成$4$，但我们知道，从$2$到$1$要跑反边把多余的流量流回来。可是此时$1$的深度还是$2$，两点间出现断层，多于流量无法流回。

但是如果从$t$到$s$进行$bfs$，就不会出现此类问题。

因此，从$t$到$s$进行$bfs$有如下几个原因：
1. 保证多余流量可以沿着反边流回（如上例）。
2. 确保每次只打断已经搜索过的一条路径，而不会打断其他路径（可以自己举一个例子）。

#### 4. 求最大流的函数
在$ISAP$中，我们只需要进行$1$遍$bfs$。

与$Dinic$算法相同，我们仍然是判断图是否联通去进行$dfs$。在$dfs$中，每一次打断一条路径，都会把当前节点的深度+$1$，也就是原深度的节点数量需要-$1$。再根据 “人往高处走，水往低处流” 的思想，如果该深度中没有节点，则代表图不连通。正好在$dfs$中，有这样一句话：
```cpp
if(gap[dep[x]]==0)
	dep[s] = n+1;
```
所以判断图是否联通的条件句就是:
```cpp
while(dep[s]<=n)
```

下面是AC代码
```cpp
/*
luogu P2740 
*/ 
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 0x7f7f7f7f;

int n,m,s,t;
int ans=0;
int ee=1,h[10005],nex[100005<<1],to[100005<<1],val[100005<<1];
int dep[10005],gap[10005];

void addedge(int x,int y,int z)
{
	nex[++ee] = h[x];
	to[ee] = y;
	val[ee] = z;
	h[x] = ee;
}

void bfs()
{
	queue<int> q;
	q.push(t);
	dep[t] = 1;
	gap[1] = 1;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=h[x];i;i=nex[i])
			if(!dep[to[i]])
			{
				dep[to[i]] = dep[x]+1;
				gap[dep[to[i]]]++;
				q.push(to[i]);
			}
	}
}

int dfs(int x,int flow)
{
	if(x==t)
	{
		ans += flow;
		return flow;
	}
	int used=0;
	for(int i=h[x];i;i=nex[i])
		if(dep[to[i]]==dep[x]-1 && val[i]>0)
		{
			int d=dfs(to[i],min(val[i],flow-used));
			if(d)
			{
				val[i] -= d;
				val[i^1] += d;
				used += d;
			}
			if(used==flow)
				return used;
		}
	gap[dep[x]]--;
	if(gap[dep[x]]==0)
		dep[s] = n+1;
	dep[x]++;
	gap[dep[x]]++;
	return used;
}

int isap()
{
	bfs();
	while(dep[s]<=n)
		dfs(s,INF);
	return ans;
}

signed main()
{
	cin>>m>>n;
	s = 1;
	t = n;
	for(int i=1,x,y,z;i<=m&&cin>>x>>y>>z;i++)
	{
		addedge(x,y,z);
		addedge(y,x,0);
	}
	cout<<isap()<<endl;
	
	return 0;
}
```
祝大家AC愉快！

---

## 作者：顾z (赞：5)

> ### Background
>
> 在农夫约翰的农场上，每逢下雨，贝茜最喜欢的三叶草地就积聚了一潭水。这意味着草地被水淹没了，并且小草要继续生长还要花相当长一段时间。因此，农夫约翰修建了一套排水系统来使贝茜的草地免除被大水淹没的烦恼（不用担心，雨水会流向附近的一条小溪）。作为一名一流的技师，农夫约翰已经在每条排水沟的一端安上了控制器，这样他可以控制流入排水沟的水流量。 
>
> ### Description
>
> 农夫约翰知道每一条排水沟每分钟可以流过的水量，和排水系统的准确布局（起点为水潭而终点为小溪的一张网）。需要注意的是，有些时候从一处到另一处不只有一条排水沟。
>
> 根据这些信息，计算从水潭排水到小溪的最大流量。对于给出的每条排水沟，雨水只能沿着一个方向流动，注意可能会出现雨水环形流动的情形。
>
> ### Input
>
> 第1行: 两个用空格分开的整数N (0 <= N <= 200) 和 M (2 <= M <= 200)。N是农夫John已经挖好的排水沟的数量，M是排水沟交叉点的数量。交点1是水潭，交点M是小溪。
>
> 第二行到第N+1行: 每行有三个整数，Si, Ei, 和 Ci。Si 和 Ei (1 <= Si, Ei <= M) 指明排水沟两端的交点，雨水从Si 流向Ei。Ci (0 <= Ci <= 10,000,000)是这条排水沟的最大容量。
>
> ### Output
>
> 输出一个整数，即排水的最大流量。

裸的网络流,答案即为从$1$到$m$的最大流。

注意看清我的输入,稳稳$AC$

``代码``

```c++
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue> 
#include<iostream>
#define clear(a,b) memset(a,b,sizeof a)
#define R register

using namespace std;

const int gz=1500000+10;

inline void in(R int &x)
{
	R int f=1;x=0;char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}

int head[gz],depth[gz],tot,n,m,cur[gz],s,t;

struct cod{int u,v,w;}edge[gz];

inline void add(R int x,R int y,R int z)
{
    edge[++tot].u=head[x];
    edge[tot].v=y;
    edge[tot].w=z;
    head[x]=tot;
}

inline bool bfs()
{
	clear(depth,0);queue<int>q;
	depth[s]=1;q.push(s);
	for(R int i=1;i<=n;i++)cur[i]=head[i];
	while(!q.empty())
	{
		R int u=q.front();q.pop();
		for(R int i=head[u];i!=-1;i=edge[i].u)
		{
			if(depth[edge[i].v]==0 and edge[i].w>0)
			{
				depth[edge[i].v]=depth[u]+1;
				q.push(edge[i].v);
			}
		}
	}
	return depth[t];
}

inline int dfs(R int u,R int dist)
{
	if(u==t or !dist)return dist;
	R int di=0,f;
	for(R int i=cur[u];i!=-1;i=edge[i].u)
	{
		cur[u]=i;
		if(depth[edge[i].v]==depth[u]+1 and (f=dfs(edge[i].v,min(edge[i].w,dist))))
		{
			di+=f;dist-=f;
			edge[i].w-=f;edge[i^1].w+=f;
			if(dist==0)break;
		}
	}
	return di;
}

inline int dinic()
{
	R int ans=0;
	while(bfs())ans+=dfs(s,214748364);
	return ans;
}

int main()
{
	in(m),in(n);s=1,t=n;
	clear(head,-1);tot=-1;
	for(R int i=1,x,y,z;i<=m;i++)
	{
		in(x),in(y),in(z);
		add(x,y,z);add(y,x,0);
	}
	printf("%d\n",dinic());
}
```

---

## 作者：Vasily (赞：4)

这就是个网络流的模板题目。。。。大家不管是sap或者dinic甚至EK都可以过来练手。

那么，我就把EK和Dinic的发一下（Sap）还没写

```cpp
#include <bits/stdc++.h>
using namespace std ;
const int maxn = 210 ;
const int zhf = 0xfffffff ;
int G[maxn][maxn], pre[maxn], n, m ;
queue <int> q ;
bool vis[maxn] ;
bool bfs ( int s, int t ) {
    memset ( vis, false, sizeof(vis) ) ;
    memset ( pre, -1, sizeof(pre) ) ;
    vis[s] = true ;
    pre[s] = s ;
    while ( !q.empty() ) q.pop() ;
    q.push(s) ;
    while ( !q.empty() ) {
        int x = q.front() ;
        q.pop() ;
        for ( int i = 1 ; i <= n ; i ++ ) {
            if ( i != x && !vis[i] && G[x][i] > 0 ) {
                q.push(i) ; 
                pre[i] = x ;
                vis[i] = true ;
                if ( i == t ) return true ;
            }
        }
    }
    return false ;
}
int Max_flow ( int s, int t ) {
    int flow = 0 ;
    while ( bfs(s, t) ) {
        int min_flow = zhf ;
        for ( int u = t ; u != s ; u = pre[u] )
            min_flow = min ( min_flow, G[u[pre]][u] ) ;
        for ( int u = t ; u != s ; u = pre[u] ) {
            G[u][u[pre]] += min_flow ;
            G[u[pre]][u] -= min_flow ;
        }
        flow += min_flow ;
    }
    return flow ;
}
int main() {
    int i, j, k, u, v, w ;
    scanf ( "%d%d", &m, &n ) ;
    for ( i = 1 ; i <= m ; i ++ ) {
        scanf ( "%d%d%d", &u, &v, &w ) ;
        G[u][v] += w ;
    }
    printf ( "%d\n", Max_flow(1,n) ) ;
    return 0 ;
}
```

上面那个是EK，现在是Dinic：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std ;
const int maxn = 210 ;
const int zhf = 0xfffffff ;
int G[maxn][maxn], n, m, dis[maxn] ;
queue <int> q ;
bool bfs() {
    memset ( dis, -1, sizeof(dis) ) ;
    while ( !q.empty() ) q.pop() ;
    dis[1] = 0 ;
    q.push(1) ;
    while ( !q.empty() ) {
        int x = q.front() ;
        q.pop() ;
        for ( int i = 1 ; i <= n ; i ++ ) {
            if ( dis[i] == -1 && G[x][i] > 0 ) {
                dis[i] = dis[x]+1 ;
                if ( i == n ) return true ;
                q.push(i) ;
            }
        }
    }
    return false ;
}

int dfs ( int x, int val ) {
    int i, u, rec = 0 ;
    if ( x == n ) return val ;
    for ( i = 1 ; i <= n ; i ++ ) {
        if ( dis[i] == dis[x]+1 && G[x][i] > 0 && (rec = dfs(i,min(val, G[x][i]) )) ) {
            G[x][i] -= rec ;
            G[i][x] += rec ;
            return rec ;
        }
    }
    
    return false ;
}

int max_flow() {
    int flow = 0 ;
    while ( bfs() ) {
        flow += dfs(1,zhf) ;
    }
    return flow ;
}

int main() {
    int i, j, k, u, v, w ;
    scanf ( "%d%d", &m, &n ) ;
    for ( i = 1 ; i <= m ; i ++ ) {
        scanf ( "%d%d%d", &u, &v, &w ) ;
        G[u][v] += w ;
    }
    printf ( "%d\n", max_flow() ) ;
    return 0 ;
}
```

---

## 作者：SNiFe (赞：2)

这道题是最大网络流模板题，dinic模板就能AC。


我见各dalao代码太高级，我有点看不懂，于是写一篇题解给和我一样的蒟蒻看；


这有一博客，有助于蒟蒻们理解dinic


https://comzyh.com/blog/archives/568/

###代码：


```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=10000+10;
const int inf=0x7f7f7f7f;
struct nod
{
    int next,to,w;
}edge[maxn];
int head[maxn],lev[maxn]/*距源点距离,分层图 */,n,m,k=1,ans;    
void add(int u,int v,int val)
{
    edge[++k].next=head[u];
    edge[k].to=v;
    edge[k].w=val;
    head[u]=k;
}
bool bfs(int s,int t)
{
    queue<int>q;//BFS队列
    memset(lev,-1,sizeof(lev));
    q.push(s);lev[s]=0;
    while(!q.empty())
    {
        int now=q.front();q.pop();
        for(int i=head[now];i;i=edge[i].next)
        {
            if(lev[edge[i].to]==-1 && edge[i].w)
            {
                lev[edge[i].to]=lev[now]+1;
                if(edge[i].to==t) return true;
                q.push(edge[i].to);
            }
        }
    }
    return false;
}
//dfs代表一次增广,函数返回本次增广的流量,返回0表示无法增广 
int dfs(int x,int maxf)
{
    if(x==n)return maxf;
    int use=maxf;//use是源点到现在最窄的(剩余流量最小)的边的剩余流量
    for(int i=head[x];i;i=edge[i].next)
    {
        if(lev[edge[i].to]==lev[x]+1/*是分层图的下一层*/ && use && edge[i].w>0)
        {
            int flow=dfs(edge[i].to,min(use,edge[i].w));
            if(!flow) lev[edge[i].to]=-1;//不能到汇点
            use-=flow;
            edge[i].w-=flow;
            edge[i^1].w+=flow;
        }
    }
    return maxf-use;
}
void dinic(int s,int t)
{
    while(bfs(s,t))//要不停地建立分层图,如果BFS不到汇点才结束
    ans+=dfs(s,inf);//一次BFS要不停地找增广路,直到找不到为止
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,0);
    }
    dinic(1,n);printf("%d\n",ans);
}
//打完收工，欢迎各位大佬指正
```

---

## 作者：七喜 (赞：1)

~~首先，要写这道题你必须是个蒟蒻（像我一样）~~

审题，发现这是一道~~很简单~~的网络流题目

于是你把网络流的板子交了上去，然后发现自己WA地一声哭了

然后陷入沉思之中，发现你并没有累加道路

稍作修改，你又AC了

以下是bfs过程，代码很短，大概五十多行吧
```c
#include<bits/stdc++.h>
using namespace std;

const int N=202;

int n,m,pre[N],p[N],dis[N][N],res;

int bfs(int s,int t)
{
	queue<int>q;	memset(p,0,sizeof(p));
	p[s]=10000000*N;	q.push(s);
	while(!q.empty())
	{
		int u=q.front();	q.pop();
		for(int i=1;i<=m;i++)
			if(!p[i]&&dis[u][i])
			{
				p[i]=min(p[u],dis[u][i]);
				pre[i]=u;	q.push(i);
				if(i==t) return p[i];
			}
	}
	return 0;
}
int main()
{
	int mi;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		dis[a][b]+=c;//因为有些路径有多次出现，所以要累加起来，我之前因为这里一直WA
	}
	while(1)
	{
		mi=bfs(1,m);
		if(!mi) break;
		res+=mi;
		for(int i=m;i!=1;i=pre[i])
			dis[pre[i]][i]-=mi,
			dis[i][pre[i]]+=mi;
	}
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：Celebrate (赞：1)

这一道题我用了dinic算法来做

代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
struct node
{
	int x,y,c,next,other;//边 
}a[2110000];int len,last[510],st,ed;
int n,f,d;
inline void ins(int x,int y,int c)//建立边 
{
	int k1,k2;//为了防止出现错误，我就用k1,k2来记录两条边 
	len++;k1=len;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
	
	//反向边给我们反悔的机会 
	len++;k2=len;
	a[len].x=y;a[len].y=x;a[len].c=0;//反向边一开始流量为0
	a[len].next=last[y];last[y]=len;
	
	a[k1].other=k2;//记录反向边 
	a[k2].other=k1;
}
int head,tail,h[510],list[21000];//h记录层次，剪枝 
inline bool bt_h()//建立网络流的层次 
{
	memset(h,0,sizeof(h));h[st]=1;//起点的层次为1 
	list[1]=st;head=1;tail=2;
	while(head!=tail)
	{
		int x=list[head];
		for(int k=last[x];k;k=a[k].next)//访问亲朋好友 
		{
			int y=a[k].y;
			if(a[k].c>0 && h[y]==0)//如果是有流量的边，并且还没有标层次 
			{
				h[y]=h[x]+1;//记为下一层 
				list[tail]=y;tail++;
			}
		}
		head++;
	}
	if(h[ed]>0) return true;//如果可以到达最后的点 
	return false;
}
int findflow(int x,int f)//递归，x表示当前的点，f为带的流量 
{
	if(x==ed) return f;//如果到达了终点 
	int s=0,t;//s记为这一个点能到达终点的流量 
	for(int k=last[x];k;k=a[k].next)
	{
		int y=a[k].y;
		//如果边有流量
		//如果为下一层（剪枝）
		//如果s不超过能带上的流量 
		if(a[k].c>0 && h[y]==h[x]+1 && s<f)
		{
			s+=(t=findflow(y,min(a[k].c,f-s)));//往下搜索 
			a[k].c-=t;a[a[k].other].c+=t;
			//从这一条边通过了，就要减去t
			//现在反向边就能起到作用了----给了一个反悔的机会 
		}
	}
	if(s==0) h[x]=0;//如果这一个点到达不了终点，就把这个层次设置为0, 
	return s;//返还 
}
int ff[110],dd[110];
int main()
{
	int n,m;
	scanf("%d%d",&m,&n);
	st=1;ed=n;//起点和终点 
	for(int i=1;i<=m;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);
	}
	int s=0;
	while(bt_h()==true)//每次建立层次 
	{
		//如果可以到达终点 
		s+=findflow(st,999999999);//在第一个点是可以带无限的流量的 
		//这里用while是因为一次只能找一条路，难以找完整个图，所以要每次都找 
	}
	printf("%d\n",s);//输出 
	return 0;
}
```

---

## 作者：【天朝】MILK (赞：0)

此题考点为网络流之**最大流**

解决此类问题有四种方法：

------------
**1·Ford——Fulkerson算法；**
------------
------------
**实质就是随便找一条增光路进行增广。**

其**时间复杂度**为O（MV），其中M为边数，V为最大流量。

------------


**2·Edmonds——Karp算法；**
------------


------------
**利用BFS在残留网络中来增广。**

每次找包含弧最少的增广路进行增广。

其**时间复杂度**为O（NM^2）

------------



**3·Dinic算法；**
------------


------------
**基本思路：**

一直用BFS构造**层次图**，然后一直用**阻塞流**来增广。

其时间复杂度为O（MN^2）

注：

1.层次图：有路径深度的图。

2.阻塞流：不考虑反向流时的**极大流**。


------------
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int m,n,G[205][205]={0},s=1,Ans=0;
int v[205]={0},dis[205]={0};
int q[200005]={0};
int BFS()
{
	int left=1,right=1;
	memset(q,0,sizeof(q));
	memset(dis,-1,sizeof(dis));
	memset(v,0,sizeof(v));
	dis[s]=0;v[s]=1;q[1]=s;
	while(left<=right)
	{
		if(q[left]==n)return 1;
		for(int i=1;i<=n;i++)
		{
			if(G[q[left]][i]>0&&!v[i])
			{
				dis[i]=dis[q[left]]+1;v[i]=1;
				q[++right]=i;
			}
		}
		left++;
	}
	return 0;
}
int Min(int a,int b)
{
	if(a>b)return b;
	else return a;
}
int DFS(int x,int num)
{
	int i,r=0,d=0;
	if(x==n)return num;
	for(int i=1;i<=n;i++)
	{
		if(G[x][i]>0&&dis[i]==dis[x]+1)
		{
			d=DFS(i,Min(num,G[x][i]));
			if(d==0) dis[i]=0;
			G[x][i]-=d;G[i][x]+=d;
			r+=d;num-=d;
			if(num==0)return r;
		}
	}
	return r;
}
int main()
{
	int x,y,z;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		G[x][y]+=z;
	}
	while(BFS())Ans+=DFS(s,1<<30);
	printf("%d\n",Ans);
	return 0;
}
```
------------

**4·SUP算法；**
------------
------------
**Gap[i]:**所有节点中dis[j]==i的个数（其中j∈[1,n]）

**Dis[i]:**节点i的深度

------------------------
**注意：允许弧必须满足Dis[i]==Dis[j]+1且i与j有路径**

------------
**算法步骤：**

一：**初始化**Dis[i]=0,Gap[0]=n;

二：不断延可行弧找增广路增广;

三：遍历完当前节点之后为使下次有路可走，必须对当前节点的深度更新：**Dis[i]=min{Dis[j]|(i,j)}**;

四：当Dis[源点]>=总结点个数n是，算法结束.

------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=1e9;
int map[201][201]={0};
int Gap[201]={0},dis[201]={0};
int n,m,Ans=0;
int DFS(int x,int num)
{
	if(x==n)return num;
	int t=0,s=0;
	for(int i=1;i<=n;i++)
	{
		if(map[x][i]>0&&dis[x]==dis[i]+1)
		{
			s=DFS(i,min(num,map[x][i]));
			num-=s;t+=s;
			map[x][i]-=s;map[i][x]+=s;
			if(dis[0]==n+2||!num)return t;
		}
	}
	if(!(--Gap[dis[x]]))dis[1]=n+2;Gap[++dis[x]]++;
	return t;
}
int main()
{
	int x,y,z;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		map[x][y]+=z;
	}
	Gap[0]=n;
	while(dis[1]<n)Ans+=DFS(1,INF);
	printf("%d\n",Ans);
	return 0;
}
```


---

## 作者：feicx (赞：0)

这道题是裸的增广路算法。

将图的容量初始化，注意：读入边的信息时，必须只能单向读入，这是为了更好的增加残余网络的反向弧。

对图所有的流量均初始化为0。

首先我们应该寻找增广路，对于寻找一条增广路，我们可以这样做：

第一步：我们首先通过广度搜索或者深度搜索来求出这个图的其中一条路径。并用Pre数组记录前驱。

第二步：我们可以通过求出此路径的残余网络的最大瓶颈，其实其中一条边残余网络的瓶颈值就是路径的限制容量-当前的流量。

第三步：将整条路径增加流量。但是在增加流量的同时，我们需要反向添加其容量，所增加的值为第二步求得的瓶颈值。为何要增加反向弧，因为对于一个图，我们增加了其正边流量时就相当于减少了其正边的剩余容量，而反向的容量恰好会增加正边的容量的减少值，例如，张三欠了李四10元，而李四不让张三还10元，相当于张三增加了10元，此与原理相似。所以，利用反向弧定理，我们可以求出更多的增广路，求出更大的流量。

通过以上三步，我们就寻找到了一条增广路。

按照此算法循环下去，我们可以找到很多条增广路，且每找到一条增广路的同时，其两点间的网络流量会增加。这样，若找不到任意一条增广路，则容易证明当前的网络流量最大从而求出最大网络流。

对于求起点到终点的流量，我们一般会想到将终点汇聚的流量求和，但是我们知道，从起点流出去的流量之和是等于终点汇聚的流量的之和，利用这样的性质我们可以通过把对起点流出去的流量来求和从而求出最大网络流。


```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int f[210][210],c[210][210],pre[210];
bool flag=true,b[210];
int n,m,h,t,que[200*200+10],ans;
int main(){
    cin>>m>>n;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        c[u][v]=w;
    //输入边，注意，只能单向读入。 
    }
    flag=true;
    //将其作为一个标记，若其值为假，则找不到增广路。 
    while(flag){
        flag=false;
        memset(b,false,sizeof(b));
        h=0;
        t=1;
        que[1]=1;
        b[1]=true;
        //第一步，寻找一条路径作为增广路。 
        while(h<t){
            h++;
            int p=que[h];
            for(int i=1;i<=n;i++)
                if(!b[i] && f[p][i]<c[p][i]){
                    que[++t]=i;
                    pre[i]=p;
                    b[i]=true;
                    if(i==n){
                        flag=true;
             //找到一条增广路，将flag设为真。 
                        break;
                    }
                }
            if(flag)
                break;
        }
        if(!flag)
            break;
        //没找到增广路，直接跳出循环。 
        //求瓶颈的值。 
        int k=n,pj=0xfffffff;
        while(pre[k]){
            int u=pre[k];
            pj=min(pj,c[u][k]-f[u][k]);
            k=u;
        }
        k=n;
        //添加残余网络流量和反向弧。 
        while(pre[k]){
            int u=pre[k];
            f[u][k]+=pj;
            c[k][u]+=pj;
            k=u;
        }
    }
    //对流出流量求和。
    for(int i=2;i<=n;i++){
        ans+=f[1][i];
    }
    cout<<ans<<endl;
}
```

转自本人博客：<http://blog.csdn.net/u013245432/article/details/77269549>

要注意的是：本题题面
``` 
有些时候从一处到另一处不只有一条排水沟
```
因此本题的
```cpp
c[u][v]=w;
//要改为
c[u][v]+=w;
```

---

## 作者：flashy_yali (赞：0)

#网络流基本算法，利用广搜搜索增广路，当没有增广路时即可统计其最大流量，即为所求

##通过邻接矩阵存取图


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#define REP(i, N, M) for(register int i = N; i <= M; i++)//for循环恒定义

const int MAXN = 200 + 10;
const int inf = 0x3f3f3f3f;//定义inf最大值，以便比较求出最小值

using namespace std;

queue<int>Q;//队列以进行广搜

int Capacity[MAXN][MAXN]/*存取两点间的容量*/, Flow[MAXN][MAXN]/*存取两点间的流量*/, Previous[MAXN];//记录当前节点链接的上一个节点 
bool SignQ[MAXN];//标记进行判重
int N, M, Bottlenneck, cnt;

inline void IN();//输入函数

inline bool Search_Augmenting_Path();//求取增广路是否存在

inline void Search_Augmenting_Path_Bottlenneck();//求取当前增广路上最大的流量，即残存网络下的最大流量，也即剩余的容量最小值

inline void Calc_Flow();//对当前增广路上的流量进行统计

inline void OUT();//输出

int main()
{
//    freopen("ditch.in", "r", stdin);
//    freopen("ditch.out", "w", stdout);

    IN();

    while(Search_Augmenting_Path())//搜索增广路是否存在，当增广路存在时，即有一条路从源点到汇点的流量可以大于0，此时还可以增加流量;
    {
        Search_Augmenting_Path_Bottlenneck();
        Calc_Flow();
    }

    OUT();

    return 0;
}

inline void IN()
{
    cin >> N >> M;
    REP(i, 1, N)
    {
        int Node_u, Node_v, Node_Capacity;
        cin >> Node_u >> Node_v >> Node_Capacity;
        Capacity[Node_u][Node_v] += Node_Capacity;//读取从Node_u到Node_v路径上的容量 **注意，从一个点到另一个点的路径可能有多条，我们可以把它们视为同一条路径，其容量为从该点到另一个店的所有容量之和**

    }
}

inline bool Search_Augmenting_Path()
{
    while(!Q.empty())//清空队列
        Q.pop();
    memset(SignQ, 0, sizeof(SignQ));//清空标记
        
    Q.push(1);//入队，开始广搜
    SignQ[1] = true;
    while(!Q.empty())
    {
        int Node = Q.front();//取出队首
        REP(i, 1, M)
        {
            if(!SignQ[i] && Capacity[Node][i] > Flow[Node][i])
            {//枚举所有结点，当容量大于当前流量时，可以汇入流量
                Q.push(i);
                SignQ[i] = true;//将当前节点入队，标记设为true
                Previous[i] = Node;//记录当前节点的上一个结点，在后面统计当前增广路的流量时需要用到
                if(i == M)//当i等于M时，即找到了汇点，为一条增广路
                    return true;
            }

        }
        Q.pop();
    }
    return false;//否则返回false，此时没有增广路了，需要对最终答案进行统计
}

inline void Search_Augmenting_Path_Bottlenneck()
{
    Bottlenneck = inf;//将当前增广路的最大可行流量设为inf，即可以从这条增广路汇入源点的流量
    int Last_Node = M;
    while(Previous[Last_Node]){//当当前的结点不为源点时，继续执行
        Bottlenneck = min(Capacity[Previous[Last_Node]][Last_Node] - Flow[Previous[Last_Node]][Last_Node], Bottlenneck); 
                //更新当前的最大可行流量，即最小的剩余容量
        Last_Node = Previous[Last_Node];//将当前节点跳至上一节点，继续更新Bottlenneck
    }
}

inline void Calc_Flow()
{
    int Last_Node = M;
    while(Previous[Last_Node])//当当前节点不为源点时
    {
        Flow[Previous[Last_Node]][Last_Node] += Bottlenneck;
        Capacity[Last_Node][Previous[Last_Node]] += Bottlenneck;
        Last_Node = Previous[Last_Node];
//这里很重要！！当前增广路上的每一条路径需要加上此时的最大流量，同时为了返回上一节点，需要将此路径的反向路径容量加上当前最大流量，这使得下一次可以返回此节点以寻找下一条路
    }
}

inline void OUT()
{
    REP(i, 2, M)
    {
        cnt += Flow[1][i];
    }
    cout << cnt;
}
```

---

## 作者：huangjunqi1 (赞：0)

##网络流

这是一道网络流题，看题就知道从1点流到m点的最大流。

Dinic其实是在FF上的优化，找增广路时每次找残余网络上下一**层次**的点

层次(level数组)用bfs初始化即可

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,map[300][300],lev[1000],q[100000];
int bfs(int s,int t)
{
    memset(lev,0,sizeof(lev));
    int he=0,ta=1;
    q[0]=s;
    lev[s]=1;
    while (he<ta)
    {
        int u=q[he];
        if (u==t) return 1;
        for (int v=1;v<=n;v++)
            if (map[u][v]&&!lev[v])
            {
                lev[v]=lev[u]+1;
                q[ta++]=v;
            }
        he++;
    }
    return 0;
}
int dfs(int u,int t,int f)
{
    if (u==t) return f;
    //int fl=0;
    for (int v=1;v<=n;v++)
    {
        if (map[u][v]&&lev[v]==lev[u]+1)
        {
            int d=dfs(v,t,min(f,map[u][v]));
            if (!d) continue;
            map[u][v]-=d;
            map[v][u]+=d;
            return d;
        }
    }
    return 0;
}
int main()
{
    int m;
    memset(map,0,sizeof(map));
    scanf("%d%d",&m,&n);
    for (int i=1;i<=m;i++)
    {
        int u,v,s;
        scanf("%d%d%d",&u,&v,&s); 
        map[u][v]+=s;
    }
    int ans=0,MAXN=1<<29;
    while (bfs(1,n)) 
        ans+=dfs(1,n,MAXN);
    printf("%d\n",ans);
}
```

---

## 作者：czymkx (赞：0)

#solution

这是一道网路流的裸题，Dinic就可以Accepted。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<cstring>
using namespace std;
int en,head[1000000],vet[1000000],Next[1000000],f[1000000],n,m,level[1000000],que[1000000],qhead,qtail;
const int INF=2000000000;
void addedge(int u,int v,int val){
    vet[++en]=v;
    Next[en]=head[u];
    f[en]=val;
    head[u]=en;
}
bool bfs(int s,int t){
    memset(level,0,sizeof(level));
    level[1]=1;
    qhead=0;
    qtail=1;
    que[0]=1;
    while(qhead<qtail){
        int u=que[qhead++];
        if(u==t)
            return true;
        for(int i=head[u];i;i=Next[i])
            if(!level[vet[i]]&&f[i]){
                level[vet[i]]=level[u]+1;
                que[qtail++]=vet[i];
            }
    }
    return false;
}
int dfs(int u,int maxf,int t){
    if(u==t)
        return maxf;
    int ret=0;
    for(int i=head[u];i;i=Next[i]){
        int v=vet[i],flow=f[i];
        if(flow&&level[v]==level[u]+1){
            int Min=min(maxf-ret,flow);
            flow=dfs(v,Min,t);
            f[i]-=flow;
            f[((i-1)^1)+1]+=flow;
            ret+=flow;
            if(ret==maxf)
                return ret;
        }
    }
    return ret;
}
int Dinic(int s,int t){
    int ans=0;
    while(bfs(s,t))
        ans+=dfs(s,INF,t);
    return ans;
}
int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        addedge(x,y,z);
        addedge(y,x,0);
    }
    printf("%d\n",Dinic(1,n));
    return 0;
}
```

---

## 作者：「QQ红包」 (赞：0)

题解 by ylx

裸题
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
int n,m;
int mi;
int i;
int l,r;
int x,y,z;
int c[210][210];//容量 
int f[210][210];//目前排水管内水量 
int q[210];//bfs的时候标记用的
int flag; 
struct node
{
    int p;//上一个点在队列中的编号 
    int d;//点的编号    
}a[20000]; 
int main()
{
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        c[x][y]+=z;//x→y不止一条排水沟，所以加上去 
    }
    flag=1;//标记有没有增广路径
    while (flag)//反复找直到找不到增广路 
    {
        flag=0;//先标记为没有增广路 
        for (i=1;i<=m;i++) q[i]=1;//把所有的点标记为没走过 
        l=0;r=1;
        a[1].p=0;//起点入队 
        a[1].d=1;
        while (l<r)
        {
            l++;
            x=a[l].d;//队首出队 
            for (i=1;i<=m;i++) 
            if (q[i]&&(c[x][i]>f[x][i]||f[i][x]>0))//没走过  而且 容量大于目前水量 或者  有水从i流到x 
            {
                q[i]=0;//入队 
                r++;
                a[r].d=i;
                a[r].p=l;
                //cout<<i<<" ";
                if (i==m)//所以搜完了 
                {
                    //puts("23333");
                    flag=1;//标记 
                    break;//退出 
                } 
            } 
            //cout<<endl;
            if (flag==1) break;//这个循环也要退出 
        }
        //puts("23333");
        if (flag==0) break;//找不到增广路了 
        mi=1000000001;
        i=r; 
        while (a[i].p)
        {
            //puts("23333");
            x=a[i].d;//自己编号 
            y=a[a[i].p].d;//上一个点的编号 
            if (c[y][x]>f[y][x]&&c[y][x]-f[y][x]<mi)mi=c[y][x]-f[y][x];
            if (f[x][y]>0&&f[x][y]<mi) mi=f[x][y];
            i=a[i].p;
        } 
        i=r;
        while (a[i].p)
        {
            x=a[i].d;//自己编号 
            y=a[a[i].p].d;//上一个点的编号 
            if (c[y][x]>f[y][x]) f[y][x]+=mi;
            if (f[x][y]>0) f[x][y]-=mi;
            i=a[i].p;
        } 
    } 
    int ans=0;
    /*for (i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++) printf("%d ",f[i][j]);
        cout<<endl;
    }*/
    for (i=1;i<=n;i++) ans+=f[1][i];//统计输出
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：3269224138刘 (赞：0)

发题解的大神全都用C++,我只能发个Pascal......






```cpp
var
  a,pre,now,son,v,opp:array[-1..10000]of longint;  //a：记录当前点到源点所经过的最少点数，pre：记录当前列的父亲节点上一次当父亲的列的序号，
                                                   //now：记录这个点当前当父亲的最列的序号，son：记录当前列的子节点，v：记录当前管道的流量，
                                                   //opp：记录反向边的列的序号
  h:array[-1..100000]of longint;                   //h：记录队列元素
  tot,m,n,ans,aa,b,c,i:longint;                    //m：边数，n:点数，ans：记录总流量，aa，b，c：一条管子的开始点，结束点，流量
procedure cc(a,b,c:longint);                       //做指父链
begin
  inc(tot);
  pre[tot]:=now[a];
  now[a]:=tot;
  son[tot]:=b;
  v[tot]:=c;
end;
function bfs:boolean;
var
  t,w,p:longint;
begin
  fillchar(a,sizeof(a),255);
  t:=0;w:=1;                 //队列,t:头指针,w:尾指针
  h[1]:=1;                   //h:队列元素
  a[1]:=1;                   //a数组表示从原点到当前点所要经过的最少点数
  repeat
    inc(t);                  //从左到右依次搜索每一个数
    p:=now[h[t]];            //取现在的数的最后一次当父亲的那一列，赋值为p（即以当前数为父亲节点）
    while p>0 do             //只要t这个数还有当父亲的列，就继续搜索
    begin
      if (a[son[p]]=-1)and(v[p]<>0) then   //如果从父亲点到子节点有路，并且子节点还没赋过值
      begin
        a[son[p]]:=a[h[t]]+1;              //到子节点经过的点数等于到父节点经过的点数+1
        if son[p]=n then                   //如果走到了汇点
          exit(true);                      //表示这条路可以走，退出，用find函数使ans加上这条路可以通过的水量
        inc(w);                            //如果还没有走到汇点，
        h[w]:=son[p];                      //将这个子节点加入队列
      end;
      p:=pre[p];                           //向上一个t当父亲的列搜索
    end;
  until t=w;                               //一直搜索到没有新点，即已经从头搜索到尾了，就退出
  exit(false);        //如果将所有的点都搜索完了，还没有找到可以从源点走到汇点的路，表示所有的路都已经走过了，即ans不会再增加了，就退出
end;
function min(a,b:longint):Longint;        //取最小值
begin
  if a<b then
    exit(a);
  exit(b);
end;
function find(po,f:longint):longint;  //添加反向边（取消流）
var
  ans,p,k:longint;
begin
   ans:=0;
   if po=n then      //如果当前点为汇点，即已经从源点走到了汇点，就退出，ans加上这条路可以通过的水量
     exit(f);
   p:=now[po];       //以当前点为父亲节点，搜索
   while p>0 do      //只要当前点还有当父亲的行，就运行
   begin
     if (v[p]>0)and(a[po]<a[son[p]]) then     //如果父亲节点和子节点间有路可以走，并且子节点到源点经过的点数大于父亲节点到源点的点数
     begin
       k:=find(son[p],min(f,v[p]));     //以子节点为父亲节点，向下搜索，取这一点在单位时间内通过的水量和两点间管子单位时间内流量的最小值，
                                        //即求出两点间在单位时间内最大流量是多少
       dec(v[p],k);                     //将两点间管子的流量减去这两点间总流量的最大值，即表示这两点间的管子还可以在单位时间内流多少的水
       inc(v[opp[p]],k);                //当前边的反向边加上新的流量
       inc(ans,k);                      //总流量ans加上这一个管子可以流的流量（加上新算出的流量）
       dec(f,k);                        //这一点单位时间内汇入的水量减少
       if f=0 then                      //如果这个点的水全部都在单位时间内流完了，就退出，即这个点已经没用了
         break;
     end;
     p:=pre[p];                         //继续向上找
   end;
   if p=0 then                          //如果当前点当父亲节点的列都找完了
     a[po]:=-1;                         //标记当前点到源点的距离为-1，以后就不会再找这个点了
   exit(ans);                           //将这一次新找出的流量返回
end;
begin
  tot:=0;
  readln(m,n);
  for i:=1 to m do
  begin
    readln(aa,b,c);
    cc(aa,b,c);                         //正反两边做指父链
    cc(b,aa,0);
    opp[tot-1]:=tot;                    //opp：记录当前边的反向边        
    opp[tot]:=tot-1;
  end;
  ans:=0;
  while bfs do                          //将每个点都找一遍
     inc(ans,find(1,maxlongint));       //ans加上返回的新找出的流量
  writeln(ans);                         //输出
end.
```

---

## 作者：Mys_C_K (赞：0)

然而楼下的大神用的都是高效的dinic 和 sap 算法

蒟蒻表示默默地举出EK算法

当然优读是没什么必要的

还有求大神帮忙看看讨论里面的FF算法为什么会wa一个点……

丑陋的代码

[codec]

```cpp
//Edmonds-Karp algorithm
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#define INF 10000000
#define maxn 1000
#define maxm 10000
using namespace std;
struct edge{
    int from,to,cap,flow,pre;
}e[2*maxm+1];
queue<int> q;
int h[maxn+1],etop,pre[maxn+1],a[maxn+1];
int get_num()
{
    char c;
    bool flag=false;
    int num=0;
    while((c=getchar())==' '||c=='\n'||c=='r');
    if(c=='-') flag=true;
    else num=c-'0';
    while(isdigit(c=getchar())) num=num*10+c-'0';
    return (flag?-1:1)*num;
}
void addedge(int from,int to,int cap)
{
    etop++;
    e[etop].from=from;
    e[etop].to=to;
    e[etop].cap=cap;
    e[etop].flow=0;
    e[etop].pre=h[from];
    h[from]=etop;
}
int main()
{
    int n,m;etop=0;
    m=get_num();
    n=get_num();
    for(int i=1;i<=m;i++)
    {
        int u,v,c;
        u=get_num();
        v=get_num();
        c=get_num();
        addedge(u,v,c);
        addedge(v,u,0);
    }
    int s,t;
    //s=get_num();t=get_num();
    s=1;t=n;
    int flow=0;
    while(1)
    {
        memset(a,0,sizeof(a));
        while(!q.empty()) q.pop();
        q.push(s);a[s]=INF;pre[s]=0;
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int i=h[u];i!=0;i=e[i].pre)
            {
                int v=e[i].to;
                if(!a[v]&&e[i].cap>e[i].flow)
                {
                    a[v]=min(a[u],e[i].cap-e[i].flow);
                    pre[v]=i;
                    q.push(v);
                }
            }
            if(a[t]) break;
        }
        if(!a[t]) break;
        for(int u=t;u!=s;u=e[pre[u]].from)
        {
            e[pre[u]].flow+=a[t];
            e[(pre[u]-1)^1+1].flow-=a[t];
        }
        flow+=a[t];
    }
    printf("%d\n",flow);
    return 0;
}
[\codec]
```

---

## 作者：远航之曲 (赞：0)

竟然都是sap算法= =Dinic算法与EdmondsKarp算法都去哪了= =

这里篇幅太小直接上代码。。

安利一下自己的blog，假如要有人想学可以进去看看。。[远航休息栈-图的最大流算法](http://www.yhzq-blog.cc/图的最大流算法)


    

```cpp
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
int ans[300],g[300][300],m,n,x,y,z;
bool vis[300];
bool bfs(int s,int e)
{
    int now;
    queue<int>que;
    memset(ans,-1,sizeof ans);
    memset(vis,0,sizeof vis);
    ans[s]=s;
    vis[s]=1;
    que.push(s);
    while(!que.empty())
    {
        now=que.front();
        que.pop();
        for (int i=1;i<=n;i++)
            if (g[now][i]>0 && !vis[i])
            {
                vis[i]=1;
                ans[i]=now;
                if (i==e)
                    return true;
                que.push(i);
            }
    }
    return false;
}
int EdmondsKarp(int s,int e)
{
    int flow=0;
    while(bfs(s,e))
    {
        int dis=0x3f3f3f3f;
        for (int i=e;i!=s;i=ans[i])
            if (dis>g[ans[i]][i])
                dis=g[ans[i]][i];
        for (int i=e;i!=s;i=ans[i])
        {
            g[ans[i]][i]-=dis;
            g[i][ans[i]]+=dis;
        }
        flow+=dis;
    }
    return flow;
}
main()
{
    scanf("%d%d",&m,&n);
    {
        memset(g,0,sizeof(g));
        for (int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            g[x][y]+=z;
        }
        printf("%d\n",EdmondsKarp(1,n));
    }
}
#include <cstdio>
#include <queue>
#include <cstring>
#define min(x,y) ((x<y)?(x):(y))
using namespace std;
int dis[300],g[300][300],m,n,x,y,z;
int bfs(int s,int e)
{
    int now;
    queue<int>que;
    memset(dis,-1,sizeof dis);
    dis[s]=1;
    que.push(s);
    while(!que.empty())
    {
        now=que.front();
        que.pop();
        for (int i=1;i<=n;i++)
            if (g[now][i]>0 && dis[i]<0)
            {
                dis[i]=dis[now]+1;
                que.push(i);
            }
    }
    if (dis[e]>0) return 1;
    return 0;
}
int finds(int x,int low)
{
    int a;
    if (x==n) return low;
    for (int i=1;i<=n;i++)
        if (g[x][i]>0 && dis[x]+1==dis[i] && (a=finds(i,min(low,g[x][i]))))
        {
            g[x][i]-=a;
            g[i][x]+=a;
            return a;
        }
    return 0;
}
int Dinic(int s,int e)
{
    int flow=0;
    while(bfs(s,e))
    {
        while(x=finds(s,0x3f3f3f3f))
            flow+=x;
    }
    return flow;
}
main()
{
    scanf("%d%d",&m,&n);
    {
        memset(g,0,sizeof(g));
        for (int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            g[x][y]+=z;
        }
        printf("%d\n",Dinic(1,n));
    }
}
```

---

## 作者：jeffreyzfq (赞：0)

SAP大法好！

c++大法好！

邻接矩阵大法好！

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#define rep(i,a,b) for(int i = (a); i <= (b); i++)
#define per(i,a,b) for(int i = (a); i >= (b); i--)
#define INF 0x3f3f3f3f
#define M 1010
using namespace std;
typedef long long ll;
//---------------------------------------------head--------------------------------------------------
int n,m,a[M][M],pre[M],d[M],ans;
bool b[M];
int main()
{
    scanf("%d%d",&m,&n);
    rep(i,1,m)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        a[x][y] += z;
    }
    int now = 1,MIN = INF;
    while (d[1] < n)
    {
        bool get = 0;
        rep(i,1,n) if (d[i] == d[now] - 1 && a[now][i] > 0)
        {
            get = 1;
            if (a[now][i] < MIN) MIN = a[now][i];
            pre[i] = now;
            now = i;
            if (now != n) break;
            ans += MIN;
            while (now != 1)
            {
                int temp = now;
                now = pre[now];
                a[now][temp] -= MIN;
                a[temp][now] += MIN;
            }
            MIN = INF;
            break;
        }
        if (get) continue;
        int Min = n - 1;
        rep(i,1,n) if (a[now][i] > 0 && d[i] < Min) Min = d[i];
        d[now] = Min + 1;
        if (now != 1) now = pre[now];
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：新方法要加强 (赞：0)

极其简便的深搜版isap，代码长度仅为38行而且还有压缩空间，加入了gap优化提高效率，简洁明了，值得参考

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,maxflow,c[210][210],gap[210],dis[210];
int dfs_isap(int h,int flow)
{
    if(h==m)return flow;
    int res=flow,i,mi;
    for(i=1;i<=m;i++)
        if(c[h][i]>0&&dis[h]==dis[i]+1)
        {
            mi=dfs_isap(i,min(res,c[h][i]));
            c[h][i]-=mi;
            c[i][h]+=mi;
            res-=mi;
            if(!res)return flow;
        }
    gap[dis[h]]--;
    if(!gap[dis[h]])dis[1]=m;
    dis[h]++;
    gap[dis[h]]++;
    return flow-res;
}
int main()
{
    int i,x,y,w;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
    {
        scanf("%d%d%d",&x,&y,&w);
        c[x][y]+=w;
    }
    for(gap[0]=m;dis[1]<m;)maxflow+=dfs_isap(1,1e9);
    printf("%d\n",maxflow);
    return 0;
}
```

---

## 作者：_bestknife (赞：0)

我学习了代码，所以我的SAP很短，用的是邻接矩阵

 
 
 
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#define MAXN 300+20 
using namespace std;
int n;
int map[MAXN][MAXN];
int gap[MAXN],h[MAXN],d[MAXN];
int sap(int v,int flow){
    int rec=0;
    if (v==n) return flow;
    for (int i=0;i++<n;)
    {
      if (map[v][i]&&h[v]==h[i]+1)
      {
            int ret=sap(i,min(flow-rec,map[v][i]));
            map[v][i]-=ret;
            map[i][v]+=ret;
            d[v]=i;
            rec+=ret;
            if (rec==flow) return flow;
        }
    }
    d[v]=1;
    if (!(--gap[h[v]])) h[1]=n;
    gap[++h[v]]++;
    return rec;
}
int main(){
//    freopen("ditch.in","r",stdin);
//    freopen("ditch.out","w",stdout);
    int m;
    memset(map,0,sizeof(map));
    memset(gap,0,sizeof(gap));
    memset(h,0,sizeof(h));
    scanf("%d%d",&m,&n);
    while (m--)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        map[x][y]+=z;
    }
    gap[0]=n;
    for (int i=0;i++<n;) d[i]=1;
    int ans=0;
    while (h[1]<n)
    {
      ans+=sap(1,0x7fffffff);
    }
    printf("%d\n",ans);
//    fclose(stdin);
//    fclose(stdout);
    return 0;
}
```

---

## 作者：ztzshiwo001219 (赞：0)

我是蒟蒻我再次回来了 虽然已经有人交了sap的题解，但是我还可以交一个邻接表板的sap。。。。。。望采纳

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
const int maxn=210;
const int maxm=410; 
const int inf=0x3f3f3f3f;
using namespace std;
int bgn[maxn],nxt[maxm],to[maxm],c[maxm],cnt;
int n,m,level[maxn],pre[maxm],gap[maxn];
int cnte,edge[maxm];
void add_edge(int x,int y,int w)
{
    nxt[cnt]=bgn[x];bgn[x]=cnt;to[cnt]=y;c[cnt++]=w;
    nxt[cnt]=bgn[y];bgn[y]=cnt;to[cnt]=x;c[cnt++]=0;
}
int sap(int s,int t)
{
    memset(pre,-1,sizeof(pre));
    memset(gap,0,sizeof(gap));
    memset(level,0,sizeof(level));
    gap[s]=n;
    int u,v,flow=0,i;
    u=pre[s]=s;
    cnte=0;
    while(level[s]<n)
    {
        for(i=bgn[u];i!=-1;i=nxt[i])
        {
            v=to[i];
            if(level[u]==level[v]+1&&c[i]>0)break;
        }
        if(i!=-1)
        {
            pre[v]=u;
            edge[++cnte]=i;
            u=v;
            if(v==t)
            {
                int minf=inf;
                for(int i=1;i<=cnte;++i)
                    if(minf>c[edge[i]])minf=c[edge[i]];
                flow+=minf;
                for(int i=1;i<=cnte;++i)
                {
                    c[edge[i]]-=minf;
                    c[edge[i]^1]+=minf;
                }
                u=s;
                cnte=0;
            }
        }
        else
        {
            int minl=n;
            for(i=bgn[u];i!=-1;i=nxt[i])
            {
                int v=to[i];
                if(minl>level[v]&&c[i]>0)minl=level[v];
            }
            gap[level[u]]--;
            if(gap[level[u]]==0)break;
            level[u]=minl+1;
            gap[level[u]]++;
            u=pre[u];
            if(cnte>0)cnte--;
        }
    }
    return flow;
}
int main()
{
    int x,y,w;
    scanf("%d%d",&m,&n);
    memset(bgn,-1,sizeof(bgn));
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&w);
        add_edge(x,y,w);
    }
    printf("%d\n",sap(1,n));
    return 0;
}
```

---

## 作者：demerzel_iv (赞：0)

模板题。。。。这是sap的做法


```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1210,INF=1000000000;
int m[N][N];
int pre[N],level[N],gap[N];
int main()
{
    int n,dm,ans=0;
    scanf("%d%d",&dm,&n);
    for(int i=1;i<=dm;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        m[x][y]+=z;
    }
    int u=1,v;
    pre[1]=1;
    gap[0]=n;
    while(level[1]<n)
    {
        for(v=1;v<=n;v++)
            if(m[u][v] && level[u]==level[v]+1)
                break;
        if(v<=n)
        {
            pre[v]=u;
            u=v;
            if(u==n)
            {
                int mn=INF;
                for(int i=u;i^1;i=pre[i])
                    if(m[pre[i]][i] && m[pre[i]][i]<mn)
                        mn=m[pre[i]][i];
                ans+=mn;
                for(int i=u;i^1;i=pre[i])
                {
                    m[pre[i]][i]-=mn;
                    m[i][pre[i]]+=mn;
                }    
                u=1;
            }
        }
        else
        {
            int t=n;
            for(int i=1;i<=n;i++)
                if(m[u][i] && level[i]<t)
                    t=level[i];
            gap[level[u]]--;
            if(!gap[level[u]])break;
            level[u]=t+1;
            gap[level[u]]++;
            u=pre[u];
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

