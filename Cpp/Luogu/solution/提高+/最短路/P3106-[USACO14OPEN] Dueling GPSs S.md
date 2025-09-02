# [USACO14OPEN] Dueling GPSs S

## 题目描述

农夫约翰最近在网上购买了一辆新车，但由于匆忙，他在选择汽车的额外功能时不小心点击了两次“提交”按钮，结果车上配备了两个 GPS 导航系统！更糟糕的是，这两个系统经常对约翰应该走的路线做出相互矛盾的决定。

约翰所在地区的地图由 N 个交叉路口（2 <= N <= 10,000）和 M 条单向道路（1 <= M <= 50,000）组成。道路 i 连接交叉路口 A\_i（1 <= A\_i <= N）和 B\_i（1 <= B\_i <= N）。同一对交叉路口之间可能有多条道路连接，双向道路（允许双向通行）由两个相反方向的单向道路表示。约翰的家位于交叉路口 1，他的农场位于交叉路口 N。可以通过沿着一系列单向道路从他的家到达农场。

两个 GPS 单元使用的是上述相同的基础地图；然而，它们对每条道路的行驶时间有不同的看法。根据第一个 GPS 单元，道路 i 需要 P\_i 个时间单位来行驶，而根据第二个单元，道路 i 需要 Q\_i 个时间单位来行驶（每个行驶时间是范围在 1 到 100,000 的整数）。

约翰想从家里到农场。然而，每当约翰走一条（比如，从交叉路口 X 到交叉路口 Y）GPS 单元认为不是从 X 到农场的最短路线的一部分的道路时，每个 GPS 单元都会大声抱怨（如果约翰走的道路两个单元都不喜欢，甚至可能两个 GPS 单元都会抱怨）。

请帮助约翰确定如果他适当地选择路线，他可以收到的最少总抱怨次数。如果约翰走的道路让两个 GPS 单元都抱怨，这将计为 +2。


## 说明/提示

有 5 个交叉路口和 7 条单向道路。第一条道路从交叉路口 3 连接到交叉路口 4；第一个 GPS 认为这条路需要 7 个时间单位来行驶，而第二个 GPS 认为需要 1 个时间单位，等等。


如果约翰走 1 -> 2 -> 4 -> 5 的路径，那么第一个 GPS 会在 1 -> 2 的道路上抱怨（它更喜欢 1 -> 3 的道路）。然而，对于路径的其余部分 2 -> 4 -> 5，两个 GPS 都很满意，因为这对于每个 GPS 来说都是从 2 到 5 的最短路径。
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5 7 
3 4 7 1 
1 3 2 20 
1 4 17 18 
4 5 25 3 
1 2 10 1 
3 5 4 14 
2 4 6 5 
```

### 输出

```
1 
```

# 题解

## 作者：Reywmp (赞：14)

> _2018.11.18_ 才发现venus大佬的评论，修改一个小错误
> _2018.10.2_ 修改部分解释，添加代码注释

貌似没有人用Dijkstra写呢。

其实这一题可以用Dij写的。思路其实很简单

我们可以写一个标准的dij模板，然后一共跑3遍。

 _分别是分3次重新构建图：_ 

>1.我们将GPS1的图存入邻接表。跑一遍dij

>2.然后我们将GPS2的图再存入邻接表。再跑一遍dij

>3.最后我们将2次跑过的dij,得到的最短路后所发出的警告数(分别不在2个Gps的次数)上当成边权。再跑一遍dij。

简单来说是3*`汇点->源点`~~某大佬指教的说法~~

每次要用不同的数组存。

最后输出`dis3[1]`最小警告数即可

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
#define N 10005
#define M 50005
using namespace std;
void fastin(int &a){
	char c=getchar();
	a=0;
	while((c<'0'||c>'9')&&c!='-'){	c=getchar();}
	int f=1;
	if(c=='-'){f=-1;c=getchar();}
	while(c>='0'&&c<='9'){	a=(a<<1)+(a<<3)+c-48;c=getchar();}
	a*=f;
}
int n,m;
int cnt=0;
struct Node
{
	int from,to,VA1,VA2;
}E[M];
struct Rey
{
	int nxt,to,VA;
}e[M];
int ds1[N];
int ds2[N];
int ds3[N];
struct pq
{
	int to,VA;
	bool operator < (const pq &x)const{
		return VA>x.VA;//re define 
	}//dij需要使用堆，优先队列重定向。
};
int head[N];
int vis[N];
priority_queue<pq>q;
void ADDside(int u,int v,int w)
{
	++cnt;
	e[cnt].nxt=head[u];
	e[cnt].VA=w;
	e[cnt].to=v;
	head[u]=cnt;
}
void Dijkstra(int u,int *ds)
{
	pq now;
	for(int i=1;i<=n;i++)
	{
		ds[i]=1<<30;
		vis[i]=0;//初始化
	}
	now.to=u;
	now.VA=ds[u]=0;
	q.push(now);
	while(!q.empty())
	{
		u=q.top().to;
		q.pop();
		if(vis[u])continue;//访问过了跳过
		vis[u]=1;
		for(register int i=head[u];i!=0;i=e[i].nxt)
		{
			int v=e[i].to;
			int xl=ds[u]+e[i].VA;
			if(vis[v]==0&&xl<ds[v])
			{
				ds[v]=xl;
				now.to=v;
				now.VA=ds[v];
				q.push(now);//更新
			}
		}
	}
}//标准dij
int main()
{
	//freopen("gpsduel.in","r",stdin);
	//freopen("gpsduel.out","w",stdout);
	fastin(n);
	fastin(m);
	for(register int i=1;i<=m;i++)
	{
		fastin(E[i].to);
		fastin(E[i].from);
		fastin(E[i].VA1);
		fastin(E[i].VA2);
	}
	memset(head,0,sizeof(head));
	memset(e,0,sizeof(e));
	cnt=0;//每次都要先初始化edge，head数组，cnt也要清理，因为要重存图
	for(register int i=1;i<=m;i++)
	{
		ADDside(E[i].from,E[i].to,E[i].VA1);//存图
	}
	Dijkstra(n,ds1);
	memset(head,0,sizeof(head));
	memset(e,0,sizeof(e));
	cnt=0;
	for(register int i=1;i<=m;i++)
	{
		ADDside(E[i].from,E[i].to,E[i].VA2);//1次重构
	}
	Dijkstra(n,ds2);
	memset(head,0,sizeof(head));
	memset(e,0,sizeof(e));
	cnt=0;
	for(register int i=1;i<=m;i++)
	{
		int sum=0;
		if(ds1[E[i].to]!=ds1[E[i].from]+E[i].VA1)
		sum++;
		if(ds2[E[i].to]!=ds2[E[i].from]+E[i].VA2)
		sum++;
		ADDside(E[i].from,E[i].to,sum); //2次重存
	}
	Dijkstra(n,ds3);
	printf("%d",ds3[1]);//最少的警告数
	putchar('\n');
	return 0;
}
```

---

## 作者：zhangyuhan (赞：10)

一道较难的最短路变形题。

题目要求两条最短路的区别。

我们来思考一下。

首先我们需要知道两条最短路。由于我们需要知道任意节点到$n$号节点的最短路，不可能跑$n$次，所以我们可以建一个反向图，从$n$号节点出发，根据两个$GPS$系统跑两遍$SPFA$。

其次就是统计抱怨值。我们可以考虑枚举每一条边，判断其权值是否不等于这条边两个节点的最短路长度。如果不等于，考虑存一个计数器，则计数器$++$。因为有两个系统，所以计数器最大等于$2$。然后我们在根据这条边的两个节点，以计数器（即抱怨值）为权值，建一条新边，最后构成一个新图。

最终，在这个新图上跑$SPFA$即可。

$AC$ $Code$

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 10010, INF = 1e9;

struct edge {
	int to, cost;
};
std::vector<edge> G[MAXN], G1[MAXN], G2[MAXN];

int n, m, d1[MAXN], d2[MAXN], d[MAXN];
bool exist[MAXN];
queue<int> q;

void spfa1(int s) { //第一个GPS系统
	fill(d1+1, d1+1+n, INF);
	memset(exist, false, sizeof(exist));//初始化莫忘掉！
	d1[s] = 0;
	q.push(s);
	exist[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		exist[v] = false;
		for (int i=0; i<G1[v].size(); i++) {
			edge e = G1[v][i];
			if (d1[v] + e.cost < d1[e.to]) {
				d1[e.to] = d1[v] + e.cost;
				if (!exist[e.to]) {
					q.push(e.to);
					exist[e.to] = true;
				}
			} 
		}
	}
}

void spfa2(int s) { //第二个GPS系统
	fill(d2+1, d2+1+n, INF);
	memset(exist, false, sizeof(exist));//初始化莫忘掉！
	d2[s] = 0;
	q.push(s);
	exist[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		exist[v] = false;
		for (int i=0; i<G2[v].size(); i++) {
			edge e = G2[v][i];
			if (d2[v] + e.cost < d2[e.to]) {
				d2[e.to] = d2[v] + e.cost;
				if (!exist[e.to]) {
					q.push(e.to);
					exist[e.to] = true;
				}
			} 
		}
	}
}

void spfa(int s) { //计算抱怨值
	fill(d+1, d+1+n, INF);
	memset(exist, false, sizeof(exist));//初始化莫忘掉！
	d[s] = 0;
	q.push(s);
	exist[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		exist[v] = false;
		for (int i=0; i<G[v].size(); i++) {
			edge e = G[v][i];
			if (d[v] + e.cost < d[e.to]) {
				d[e.to] = d[v] + e.cost;
				if (!exist[e.to]) {
					q.push(e.to);
					exist[e.to] = true;
				}
			} 
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i=1; i<=m; i++) {
		int u, v, c1, c2;
		cin >> u >> v >> c1 >> c2;
		G1[v].push_back((edge){u, c1});
		G2[v].push_back((edge){u, c2});//注意！因为是有向图，所以在建反向图时，要注意方向。
	}//建反向图
	spfa1(n);
	spfa2(n);
	for (int i=1; i<=n; i++)
		for (int j=0; j<G1[i].size(); j++) {
			edge e1 = G1[i][j], e2 = G2[i][j];
			int cnt = 0;
			if (d1[e1.to] - d1[i] != e1.cost) cnt++;
			if (d2[e2.to] - d2[i] != e2.cost) cnt++; //注意！这里不能写成d2[i] - d2[e.to]，因为你之前建的是反向图，所以应该是e2.to的权值大。上一行同理。
			G[e1.to].push_back((edge){i, cnt}); //注意！因为最后一次跑SPFA时，是从1号节点出发的，所以建图时要是正向图。
		}
	spfa(1);
	cout << d[n]  << endl;
	return 0;//完结撒花！
}
```

---

## 作者：CreeperLordVader (赞：6)

一道有一定难度的最短路题目

我用的是dijkstra，还用了两次dfs

实际上这题的代码可以很方便地写出

我们很容易想出这样的思路框架，预处理每条边的警告次数，然后从1到n跑最短路

怎么预处理呢？

题面中有一句很重要的话

>如果边$ (u,v) $不在u到n的最短路径上，这条边就受到一次警告


## 1.两次反向图最短路

这摆明了要我们求出在两个GPS下，各个点到n的最短路

各个点到n的最短路不太好求?

我们就可以想到建出反向图，在反向图上从n开始跑最短路

## 2.使用两次dfs对边进行标记

最短路上的边很好标记，我们从n开始沿着反向图走

并且只经过满足$ d[y]=d[x]+w $的边$ (x,y,w) $

当然这个$ (x,y,w) $是反向边，对应的原图中的边应该是$ (y,x,w) $

我们可以先把原图中的边的警告次数预设为2

然后对于反向边在最短路上的边，我们就把对应的原图中的边的警告次数-1

当然这里的GPS是两个所以要标记两次~~~


## 3.在原图上根据警告次数跑最短路

这样的处理完毕以后我们就得到了每条边的警告次数

直接dijkstra即可

- - -

## 一些实现技巧

觉得信息过多不好存？反向边不好找？

我们可以使用如下结构体保存一条边的所有信息

```cpp
struct edge
{
    int from,to,wp,wq,w;
};
```

wp是第一个GPS下的边权，wq同理，w是警告次数

我们用一个vector作为边表存下所有的边，包括原边和反向边

对每个点，保存两个vector，一个只保存原边在边表中的编号，另一个只保存反向边在vector中的编号

这样处理起来就不会原边反向边傻傻分不清啦

连边时原边和反向边成对存储，这样反向边编号$ xor\  1$就是对应的原边编号啦

~~网络流常见存边方法~~

code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
    int u,d;
    friend bool operator <(const node& a,const node& b)
    {
        return a.d>b.d;
    }
};
struct edge
{
    int from,to,wp,wq,w;
};
vector<edge>e;
vector<int>v[50005],rev[50005];
int n,m,cnt,d[50005];
bool vis[50005];
void read(int& x)
{
    char c=getchar();
    x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
}
void link(int from,int to,int wp,int wq)
{
    e.push_back((edge){from,to,wp,wq,2});
    e.push_back((edge){to,from,wp,wq,0});
    cnt=e.size();
    v[from].push_back(cnt-2);
    rev[to].push_back(cnt-1);
}
void dijkstra(int s,int op)
{
    priority_queue<node>q;
    memset(d,0x3f3f3f3f,sizeof(d));
    memset(vis,0,sizeof(vis));
    d[s]=0;
    q.push((node){s,0});
    while(!q.empty())
    {
        node fa=q.top();
        q.pop();
        if(vis[fa.u])continue;
        vis[fa.u]=1;
        int x=fa.u;
        for(int i=0;i<rev[x].size();i++)
        {
            edge ed=e[rev[x][i]];
            int y=ed.to;
            int w;
            if(!op)w=ed.wp;
            else w=ed.wq;
            if(d[y]>d[x]+w)
            {
                d[y]=d[x]+w;
                if(!vis[y])q.push((node){y,d[y]});
            }
        }
    }
}
void dfs(int x,int op)
{
	vis[x]=1;
	for(int i=0;i<rev[x].size();i++)
	{
		edge& ed=e[rev[x][i]];
		int y=ed.to;
		if(vis[y])continue;
		int w;
		if(!op)w=ed.wp;
		else w=ed.wq;
		if(d[y]==d[x]+w)
		{
			e[rev[x][i]^1].w--;
			dfs(y,op);
		}
	}
}
int Dijkstra(int s,int t)
{
	priority_queue<node>q;
    memset(d,0x3f3f3f3f,sizeof(d));
    memset(vis,0,sizeof(vis));
    d[s]=0;
    q.push((node){s,0});
    while(!q.empty())
    {
        node fa=q.top();
        q.pop();
        if(vis[fa.u])continue;
        vis[fa.u]=1;
        int x=fa.u;
        for(int i=0;i<v[x].size();i++)
        {
            edge ed=e[v[x][i]];
            int y=ed.to;
            int w=ed.w;
            if(d[y]>d[x]+w)
            {
                d[y]=d[x]+w;
                if(!vis[y])q.push((node){y,d[y]});
            }
        }
    }
    return d[t];
}
int main()
{
    read(n);
    read(m);
    for(int i=1;i<=m;i++)
    {
        int x,y,wp,wq;
        read(x);
        read(y);
        read(wp);
        read(wq);
        link(x,y,wp,wq);
    }
    dijkstra(n,0);
    memset(vis,0,sizeof(vis));
    dfs(n,0);
    dijkstra(n,1);
    memset(vis,0,sizeof(vis));
    dfs(n,1);
    printf("%d\n",Dijkstra(1,n));
}
```


---

## 作者：Expecto (赞：4)

首先以n为起点两边spfa，之后再判断所有的边是否在最短路上，再次spfa

```cpp
#include<bits/stdc++.h>
using namespace std;
struct data{
    int u, v;
};
vector<data> f[10010], g[10010], h[10010];
int dis1[10010], dis2[10010], dis3[10010];
    int n, m;
int vis[10010];
void spfa(vector<data> g[10010], int d[], int x){
    memset(d, 127/3, sizeof(d));
    for (int i = 1; i <= n; i++) d[i]=233333333;
    memset(vis, 0, sizeof(vis));
    vis[x] = 1;
    d[x] = 0;
    queue<int> q;
    q.push(x);
    while (!q.empty()){
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for (int i = 0; i < g[x].size(); i++){
            int u = g[x][i].u, v = g[x][i].v;
            if (d[u] > d[x] + v){
                d[u] = d[x] + v;
                if (!vis[u]){
                    q.push(u);
                    vis[u] = 1;
                }
            } 
        }
    }
}
int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++){
        int a, b, c, d;
        scanf("%d%d%d%d", &b, &a, &c, &d);
        f[a].push_back({b, c});
        g[a].push_back({b, d});
    }
    spfa(f, dis1, n);
    spfa(g, dis2, n);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < f[i].size(); j++){
            int u = f[i][j].u, p = f[i][j].v, q = g[i][j].v, r = 0;
            if (dis1[u] - dis1[i] != p) r++;
            if (dis2[u] - dis2[i] != q) r++;
            h[u].push_back({i, r});
        }
    spfa(h, dis3, 1);
    cout<<dis3[n];
    return 0;
}
```

---

## 作者：冈崎梦美 (赞：3)

一道很烦的最短路题目，要跑\*3次SPFA…\*…慢慢写？**当然不**！

这份题解的思路和下方基本一致：先反向跑两次最短路，然后将每条在最短路中的边在第三张图的权值更新（- -），最后把抱怨次数当成第三张图的权值再正向跑一次最短路。

但是，这份题解对于编程复杂度~~和卡常~~方面有很大优化。


1.楼下dalao们都写了两个SPFA函数用于模拟GPS和FJ的路径，但实际上只需要一个就够了！


2.不需要多开数组和重新建图，只需要将edge和head数组设置成二维，三次反向建图就可以在一个函数内完成了！


~~3.打读优难道不好吗（误人子弟中）~~


下面贴上代码方便理解：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
    int next;
    int to;
    int dist;
}edge[4][100005];//二维处理邻接表
int n,m;
int head[4][100005];
int num_edge=0;
int read()//（误人子弟）的读优
{
    int x=0;char ch;
    for(;!isdigit(ch);ch=getchar());
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x;
}
void addedge(int from,int to,int dis,int mode)//对第mode加边
{
    edge[mode][num_edge].next=head[mode][from];
    edge[mode][num_edge].to=to;
    edge[mode][num_edge].dist=dis;
    head[mode][from]=num_edge;
}
void spfa(int start,int mode)
{
    int dist[100005];bool vis[100005];//dist之类都当成局部变量即可
    queue<int>team;
    memset(dist,0x7f,sizeof(dist));
    memset(vis,false,sizeof(vis));
    team.push(start);
    vis[start]=true;
    dist[start]=0;
    while(!team.empty())
    {
        int q=team.front();
        team.pop();
        for(int i=head[mode][q];i>0;i=edge[mode][i].next)
        {
            if(dist[edge[mode][i].to]>dist[q]+edge[mode][i].dist)
            {
                dist[edge[mode][i].to]=dist[q]+edge[mode][i].dist;
                if (!vis[edge[mode][i].to])
                {
                    team.push(edge[mode][i].to);
                    vis[edge[mode][i].to]=true;
                }
            }
        }
        vis[q]=false;
    }
    if (mode==3) cout<<dist[n];//对于第三张图进行处理
    else
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=head[mode][i];j>0;j=edge[mode][j].next)
            {
                if (dist[i]+edge[mode][j].dist==dist[edge[mode][j].to])
                {
                    edge[3][j].dist--;//对于在最短路中的边，更新其在第三张图里的权值
                }
            }
        }
    }
}
int main()
{//清爽的主程序
    memset(head,-1,sizeof(head));
    n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        num_edge++;
        int u=read();
        int v=read();
        int w=read();
        int r=read();
        addedge(v,u,w,1);
        addedge(v,u,r,2);
        addedge(u,v,2,3);//第三张图初始权值均为2
    }
    spfa(n,1);
    spfa(n,2);
    spfa(1,3);//三次SPFA
    return 0;
}
```

---

## 作者：Dzhao (赞：2)

### [博客食用更佳呦](https://www.luogu.org/blog/qshjydzh/solution-p3106)

我们通过观察这道题发现，这道题就是一道最短路问题，但是，需要加入一定的优化，如果我们懒得去敲，是肯定敲不出来的。

----------------------------------------------------我是分割线----------------------------------------------------

首先，我们来分析题目：
因为最短路到每一个点都会变，于是我们可以倒着求一遍SPFA，这样即可用一遍SPFA解决警告次数问题，然后我们再跑一遍SPFA，求出最少警告次数，就好了


我们来看一下代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 10009
#define M 50009
#define P 100000
int max(int x,int y) {return x>y?x:y;}
struct node
{
	int nxt,v1,v2,end;
};
node a[M];
int h[N],tot=0,q[M][2],opt[N][2],dis[N][2],n,m,d[N];
bool inq[N][2];
void add(int x,int y,int z1,int z2)
{
	a[tot].end=y;
	a[tot].v1=z1;
	a[tot].v2=z2;
	a[tot].nxt=h[x];
	h[x]=tot;
	tot++;
}
void SPFA(int s)
{
	memset(dis,-1,sizeof(dis));
	int e1=0,f1=1,e2=0,f2=0;
	inq[s][0]=inq[s][1]=1;
	dis[s][0]=dis[s][1]=0;
	opt[s][0]=opt[s][1]=-1;
	e1++;
	q[e1][0]=s;
	e2++;
	q[e2][1]=s;
	while(1)
	{
		if(f1<=e1)
		{
			int u=q[f1][0]; //取队首 
			f1++;
			for(int i=h[u];i!=-1;i=a[i].nxt)
			{
				int v=a[i].end;
				int tmp=dis[u][0]+a[i].v1;
				if(dis[v][0]==-1 || dis[v][0]>=tmp) //如果是最优方案，那就更新 
				{
					dis[v][0]=tmp;
					opt[v][0]=u; //加入最优路径方案中 
					if(!inq[v][0]) //不在队列里，入队 
					{
						inq[v][0]=1;
						e1++;
						q[e1][0]=v;						
					}
				}
			}
			inq[u][0]=0;
		}
		else if(f2<=e2)
		{
			int u=q[f2][1]; //取队首 
			f2++;
			for(int i=h[u];i!=-1;i=a[i].nxt)
			{
				int v=a[i].end;
				int tmp=dis[u][1]+a[i].v2;
				if(dis[v][1]==-1 || dis[v][1]>=tmp) //如果是最优方案，那就更新 
				{
					dis[v][1]=tmp;
					opt[v][1]=u; //加入最优路径方案中 
					if(!inq[v][1]) //不在队列里，入队 
					{
						inq[v][1]=1;
						e2++;
						q[e2][1]=v;						
					}
				}
			}
			inq[u][1]=0;
		}
		else break;
	}	
}
void getans()
{
	memset(d,-1,sizeof(d));
	inq[n][0]=1;
	int e=0,f=1;
	d[n]=0;
	e++;
	q[e][0]=n;
	while(f<=e)
	{
		int u=q[f][0];
		f++;
		for(int i=h[u];i!=-1;i=a[i].nxt)
		{
			int v=a[i].end;
			int tmp=d[u]+2-(opt[v][0]==u)-(opt[v][1]==u); //计算走这条路要警告几次 
			if(d[v]==-1 || d[v]>tmp) 
			{
				d[v]=tmp;
				if(!inq[v][0])
				{
					inq[v][0]=1;
					e++;
					q[e][0]=v;
				}
			}
		}
		inq[u][0]=0;
	}
}
int main()
{
	memset(h,-1,sizeof(h));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y,z1,z2;
		scanf("%d%d%d%d",&x,&y,&z1,&z2);
		add(y,x,z1,z2); //反向加边，可以加快对每个点到终点的最短路径方案计算 
	}
	SPFA(n);
	getans();
	printf("%d\n",d[1]);
	return 0;
}
```
>这是一道较为繁琐的SPFA，需要自己敲一遍，这样水平可以得到很大的提高。

---

## 作者：Memorize (赞：1)

由题目描述很容易得知反向建边后跑两个个从终点出发的单源最短路径树 然后再根据题目 把警告当做权值正向跑一遍spfa

那么现在问题主要是如何建警告为权值的边

我最先的想法是先把所有的边全部建为权值为2的边 在跑单源最短路径树记录前驱 把属于最短路的路径权值-1 结果会WA 因为最短路可能存在多条 所以下面介绍正确算法（受高人指点..）

我们用一个二维数组dist记录第一次与第二次的单源最短路径树

则
if(dist[x][1]-dist[y][1]==r[i].w[1]&&dist[x][2]-dist[y][2]==r[i].w[2])

add2(x,y,0);//表示这条路在两个GPS的最短路中

        else if(dist[x][1]-dist[y][1]==r[i].w[1]||dist[x][2]-dist[y][2]==r[i].w[2]) 
add2(x,y,1);//表示这条路在某个GPS的最短路中

else add2(x,y,2);表示这条路不在GPS的最短路中

最后跑一遍spfa即可

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
struct node{
    int to,next,w;
};
node e[100010],ed[100010];
struct node2{
    int x,y;
    int w[3];
}r[100010];
int n,m,k=0,k1=0;
int head[10010],head1[10010],dist[10010][3],dist1[10100];
bool vis[10010],vis1[10010];
int que[1000100],que1[1000100],qhead,qtail;
void add1(int u,int v,int w)
{
    e[++k].next=head[u];
    e[k].to=v;
    e[k].w=w;
    head[u]=k;
}
void add2(int u,int v,int w)
{
    ed[++k1].next=head1[u];
    ed[k1].to=v;
    ed[k1].w=w;
    head1[u]=k1;
}
void spfa1(int x)
{
    memset(vis,false,sizeof(vis));
    qhead=qtail=0;
    dist[n][x]=0,vis[n]=true;
    que[++qtail]=n;
    while(qhead<qtail)
    {
        int p=que[++qhead];
        vis[p]=false;
        for(int i=head[p];i;i=e[i].next)
        {
            if(dist[e[i].to][x]>dist[p][x]+e[i].w)
            {
                dist[e[i].to][x]=dist[p][x]+e[i].w;
                if(!vis[e[i].to])
                {
                    que[++qtail]=e[i].to;
                    vis[e[i].to]=true;
                }
            }
        }
    }
}
void spfa2()
{
    memset(dist1,0x7f7f7f,sizeof(dist1));
    memset(vis1,false,sizeof(vis1));
    qhead=qtail=0;
    dist1[1]=0,vis1[1]=true;
    que1[++qtail]=1;
    while(qhead<qtail)
    {
        int p=que1[++qhead];
        vis1[p]=false;
        for(int i=head1[p];i;i=ed[i].next)
        {
            if(dist1[ed[i].to]>dist1[p]+ed[i].w)
            {
                dist1[ed[i].to]=dist1[p]+ed[i].w;
                if(!vis1[ed[i].to])
                {
                    que1[++qtail]=ed[i].to;
                    vis1[ed[i].to]=true;
                }
            }
        }
    }
}
int main()
{
    memset(dist,0x7f7f7f,sizeof(dist));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    scanf("%d%d%d%d",&r[i].x,&r[i].y,&r[i].w[1],&r[i].w[2]);
    for(int p=1;p<=2;p++)
    {
       memset(head,0,sizeof(head));
       k=0;
       for(int i=1;i<=m;i++)
       add1(r[i].y,r[i].x,r[i].w[p]);    
       spfa1(p);
    }
    for(int i=1;i<=m;i++)
    {
        int x=r[i].x,y=r[i].y;
        if(dist[x][1]-dist[y][1]==r[i].w[1]&&dist[x][2]-dist[y][2]==r[i].w[2])
         add2(x,y,0);
        else if(dist[x][1]-dist[y][1]==r[i].w[1]||dist[x][2]-dist[y][2]==r[i].w[2]) 
         add2(x,y,1);
        else add2(x,y,2); 
    }
    spfa2();
    printf("%d",dist1[n]);    
    return 0;
}
```

---

## 作者：例子 (赞：1)

身为全洛谷最菜的蒟弱，本蒟弱要来发布本蒟弱的第一篇题解了

奈何前面大佬的做法我看都看不懂，所以把我自认为最简单最好想的办法发出来

借鉴了前面一篇题解大佬的办法，记录路径（倒着建图，记下路上点的前驱）

思路：总共三次spfa，两遍spfa分别处理两个系统的最短路，记下来路径(这要倒着找建图(源点n，目标1))
分别是导航仪1和2的最短路，用f1，f2数组记录每一个最短路上边的一个点的后继，但由于我们倒着建图，因此之后是当作前驱来用的

倒着建图就不用多说了，u到v边权w的边建图的时候改成v到u边权w就行

再根据之前找到的两个最短路径，建一张新图，边权初始值都是2，如果这个边在一个最短路上，就给它减一（详细请看注释）
，这一次spfa就要正着用了

蒟弱头脑简单，代码太长，重复的内容太多（代码能力太烂怕出错）求不喷
```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#define inf 0x3f3f3f
using namespace std;
struct edge{
	int w,to,next;
}e1[201100];
edge e2[201100];
edge e3[201100];
int head1[101100],head2[101100],head3[101100];
int d1[101100],d2[101100],d3[101100];
int f1[101100],f2[101100];//记路的数组
int n,en1,en2,en3,m;
void add1(int v,int u,int w){//倒着建图，add2也是
	en1++;
	e1[en1].to=v;
	e1[en1].w=w;
	e1[en1].next=head1[u];
	head1[u]=en1;
}
void add2(int v,int u,int w){
	en2++;
	e2[en2].to=v;
	e2[en2].w=w;
	e2[en2].next=head2[u];
	head2[u]=en2;
}
void add3(int u,int v,int w){//给叫唤次数建图
	en3++;
	e3[en3].to=v;
	e3[en3].w=w;
	e3[en3].next=head3[u];
	head3[u]=en3;
}
void sp1(int s){//导航仪1的最短路
	queue<int> q;
	int inq[20010];
	memset(inq,0,sizeof(inq));
	for(int i=1;i<=n;i++)d1[i]=inf;
	q.push(s);inq[s]=1;d1[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();inq[u]=0;
		for(int i=head1[u];i;i=e1[i].next){
			int v=e1[i].to,w=e1[i].w;
			if(d1[v]>d1[u]+w)
			{
				d1[v]=d1[u]+w;
				f1[v]=i;//记路
				if(!inq[v]){
					inq[v]=1;
					q.push(v);
				}
			}
		}
	}
}
void sp2(int s){//导航仪2的最短路
	queue<int> q;
	int inq[20010];
	memset(inq,0,sizeof(inq));
	for(int i=1;i<=n;i++)d2[i]=inf;
	q.push(s);inq[s]=1;d2[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();inq[u]=0;
		for(int i=head2[u];i;i=e2[i].next){
			int v=e2[i].to,w=e2[i].w;
			if(d2[v]>d2[u]+w)
			{
				d2[v]=d2[u]+w;
				f2[v]=i;
				if(!inq[v]){
					inq[v]=1;
					q.push(v);
				}
			}
		}
	}
}
void sp3(int s){//叫唤次数的最短路
	queue<int> q;
	int inq[20010];
	memset(inq,0,sizeof(inq));
	for(int i=1;i<=n;i++)d3[i]=inf;
	q.push(s);inq[s]=1;d3[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head3[u];i;i=e3[i].next){
			int v=e3[i].to,w=e3[i].w;
			if(i==f1[u])w--;
			if(i==f2[u])w--;//要是在各自最短路上，就给它减一，因为对应的系统在最短路上不会叫唤
			if(d3[v]>d3[u]+w)
			{
				d3[v]=d3[u]+w;
				if(!inq[v]){
					inq[v]=1;
					q.push(v);
				}
			}
		}inq[u]=0;
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		add1(a,b,c);
		add2(a,b,d);
		add3(a,b,2);//要是都不在最短路上，两个系统各叫唤一次，一共就是两次
	}
	sp1(n);//倒着建图，所以源点是n
	sp2(n);
	sp3(1);
	cout<<d3[n];
}
```

---

## 作者：wycissilly (赞：0)

做了题怎么能不发篇题解呢？


首先，我们对两个GPS分别建图，跑spfa，求出两条路径。


怎么记录呢？只要记录这个点的前驱即可，如代码中的f数组。


然后，再跑一遍spfa，算出至少需要抱怨多少次，边权的话，其实可以在线统计的啦。


上代码！


``` javascript
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int N=10001,M=50001;
int headf[N],vf[2*M],nxtf[2*M],disf[2][2*M],d[2][N],b[N],f[2][N],head[N],v[2*M],nxt[2*M],tot,n,m;
bool inq[N];
inline void add(int x,int y,int w1,int w2){
    v[++tot]=y;nxt[tot]=head[x];head[x]=tot;
    vf[tot]=x;disf[0][tot]=w1;disf[1][tot]=w2;nxtf[tot]=headf[y];headf[y]=tot;
}
inline void SPFA_GPS(int mode){
    for(int i=1;i<=n;i++)d[mode][i]=0x7fffffff;
    d[mode][n]=0;
    inq[n]=true;
    queue<int>q;
    q.push(n);
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for(int i=headf[x];~i;i=nxtf[i]){
            if(d[mode][x]+disf[mode][i]<d[mode][vf[i]]){
                d[mode][vf[i]]=d[mode][x]+disf[mode][i];
                f[mode][vf[i]]=i;
                if(!inq[vf[i]]){
                    q.push(vf[i]);
                    inq[vf[i]]=true;
                }
            }
        }
        inq[x]=false;
    }
}
inline void SPFA_FJ(){
    for(int i=1;i<=n;i++)b[i]=0x7fffffff;
    b[1]=0;
    inq[1]=true;
    queue<int>q;
    q.push(1);
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for(int i=head[x];~i;i=nxt[i]){
            int p=0;
            if(i!=f[0][x])p++;
            if(i!=f[1][x])p++;
            if(b[x]+p<b[v[i]]){
                b[v[i]]=b[x]+p;
                if(!inq[v[i]]){
                    q.push(v[i]);
                    inq[v[i]]=true;
                }
            }
        }
        inq[x]=false;
    }
}
int main(){
    memset(head,-1,sizeof(head));
    memset(headf,-1,sizeof(headf));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v,w1,w2;
        scanf("%d%d%d%d",&u,&v,&w1,&w2);
        add(u,v,w1,w2);
    }
    SPFA_GPS(0);
    SPFA_GPS(1);
    SPFA_FJ();
    printf("%d\n",b[n]);
}
```

---

