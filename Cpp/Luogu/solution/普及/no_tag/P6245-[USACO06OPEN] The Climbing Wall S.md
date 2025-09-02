# [USACO06OPEN] The Climbing Wall S

## 题目背景

题目是经过简写保证不改变原有题意的题目。

## 题目描述

Bessie 要爬墙，墙宽 $30000$ ，高 $H$，墙上有 $F$ 个不同的落脚点 $(X,Y)$。

$(0,0)$ 在左下角的地面。任意落脚点至少相距 $300$。至少有一条路可以上去，Bessie 每次最多爬 $1000$ 个单位距离，且可以向任意方向爬行。

一旦她到达了一个高度距离 $H$ 不到 $1000$ 的落脚点，可以直接到墙顶。Bessie 的起点可以在任一高度不超过 $1000$ 的落脚点上。问Bessi爬到顶端的最少次数。

本题距离指**欧几里得距离**。

## 说明/提示

#### 样例说明

分别经过 $(600,800),(100,1300),(300,2100)$。

$1001\le H\le 3\times 10^4$

$1\le F\le 10^4$

## 样例 #1

### 输入

```
3000 5
600 800
1600 1800
100 1300
300 2100
1600 2300```

### 输出

```
3```

# 题解

## 作者：Diamiko (赞：8)

# 题解 P6245 【The Climbing Wall S】

## 核心算法：最短路

### 1.建模

我先来把问题简述一下：
在一个平面内，每个点都有其横坐标与纵坐标。Bessie想要从一个纵坐标不超过1000的点，爬到一个纵坐标为题目给定的H的点上。她每一步可以爬到与当前点距离不超过1000的点。问：最少爬多少步？

我们把题目中每一个落脚点就看作图中的点，把可以直接到达的两个点间建一条权值为1的边，代表走了一步。

那么跑一遍最短路，到终点的距离即为题目的答案。

### 2.细节

#### ①建图
可能有些朋友已经注意到了，题目的起点和终点不唯一。

难道我们要跑多源最短路？那题目的数据范围显然是不允许的。

**我们就要引入一种思想——虚拟点！**

~~我自己乱起的名字~~


>Bessie 的起点可以在任一高度不超过$1000$的落脚点上。

也就是说，所有纵坐标小于等于1000的点都可以作为起点。

那么我们可以建立一个虚拟起点，它到所有可以作为起点的点之间都建立一条边，权值为0（代表不增加次数）。这样，我们就可以以这个虚拟的起点为总起点跑单源最短路径了

**但还有个问题，怎么确定终点呢？**

>一旦她到达了一个高度距离 $H$ 不到 $1000$ 的落脚点，可以直接到墙顶。

很容易理解，墙顶就是我们的终点，但并不是一个横纵坐标都确定的点。那么，我们就可以自己把它建立出来！

所有纵坐标距离最大高度H不到1000的点我们都连上虚拟终点，是不是问题就简单了？

#### ②距离处理

我相信这个其实不用说，你们也知道。

欧几里得距离公式：

$$ \sqrt{(x_1-x_2)^2+(y_1-y_2)^2} $$

#### ③最短路

剩下的就是最短路模板了。

关于跑最短路，我还是秉持我一贯的观点：只要没有负边权，就用Dijkstra+堆优化。

~~关于SPFA，它死了~~

### 3.代码实现

我们前面一直只是纸上谈兵，那关键的操作如何实现呢？

很多朋友最短路相关问题，点和边的下标都是从1开始的。那么我们正好可以把0作为虚拟起点，把`f+1`作为虚拟终点。也很好理解不是吗？

当然也有朋友下标从0开始，其实把`f+1`作为虚拟起点，把`f+2`作为虚拟终点，也完全OK。


具体请见代码注释。

```cpp
#include<cmath>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
#define pii pair<int,int>//宏定义，个人习惯
using namespace std;
struct Node
{
    int head,dis;
    double x,y;
    //横坐标和纵坐标
}node[10005];
struct Edge
{
    int next,to,len;
}edge[99990005];
int h,f;
//与题目意义相同
bool cmp(Node a,Node b)
{
    if(a.y==b.y)return a.x<b.x;
    return a.y<b.y;
}
//排序函数，方便对点进行处理
double calc(double x_1,double y_1,double x_2,double y_2)
{
    return double(sqrt((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2)));
}
//求距离
int cnt;
void addEdge(int u,int v,int w)
{
    edge[++cnt].len=w;
    edge[cnt].next=node[u].head;
    edge[cnt].to=v;
    node[u].head=cnt;
}
//链式前向星存图
void Dijkstra()
{
    for(int i=0;i<=f+1;i++) node[i].dis=0x3f3f3f3f;
    //别忘了初始化
    priority_queue<pii,vector<pii>,greater<pii> >q;
    //STL小根堆
    node[0].dis=0;
    q.push({0,0});
    while(q.size())
    {
        pii tmp=q.top();
        q.pop();
        int d=tmp.first,u=tmp.second;
        if(d!=node[u].dis)continue;
        for(int e=node[u].head;e;e=edge[e].next)
        {
            int v=edge[e].to;
            if(node[v].dis>d+edge[e].len)
            {
                node[v].dis=d+edge[e].len;
                q.push({node[v].dis,v});
            }
        }
    }
}
//模板
int main()
{
    scanf("%d%d",&h,&f);
    for(int i=1;i<=f;i++)
    {
        scanf("%lf%lf",&node[i].x,&node[i].y);
    }
    sort(node+1,node+f+1,cmp);
    //排序
    for(int i=1;i<=f;i++)
    {
        for(int j=i+1;j<=f;j++)
        {
            double dist=calc(node[i].x,node[i].y,node[j].x,node[j].y);
            //求得距离
            if(dist<=1000)
            {
                //如果两个点间的距离不超过1000,
                //就可以直接到达
                //建立权值为1的边
                //表示爬一次
                addEdge(i,j,1);
                addEdge(j,i,1);
            }
        }
        if(h-node[i].y<1000)
        {
            //与最大距离H不到1000的点可以直接到达终点
            //那么就与虚拟终点连一条边
            addEdge(i,f+1,1);
            addEdge(f+1,i,1);
            //虚拟终点就是f+1
        }
        if(node[i].y<=1000)
        {
            //与地面距离不超过1000的点可以作为起点
            //那么就与虚拟起点连一条边
            addEdge(0,i,0);
            addEdge(i,0,0);
            //虚拟起点就是0
        }
    }
    Dijkstra();
    printf("%d\n",node[f+1].dis);
    //这里注意输出的是虚拟终点的距离
    return 0;
}
```
那么，题解到这里就结束了！

写题解不易，希望大家多多支持。如果还有不懂的可以at我或者私信我，我会尽力帮助的！





















---

## 作者：菲斯斯夫斯基 (赞：6)

### P6245 The Climbing Wall S 题解

###### 题目方法

直接 BFS 爆搜。

###### 思路

先找出 $ y \le 1000 $ 的落脚点，将这个落脚点的位置存入队列中，接着套入 BFS 的模板，判断当前的落脚点是否可以走到第 $ i $ 个落脚点，若可以则继续存入队列中（详见代码注释）。

###### 代码

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
queue<int>a,b,c;//a存x坐标 b存y坐标 c存步数
int ans,f,h;
int x[10010],y[10010],d[10010];
void bfs()
{
	int wx,wy,wz;
	while(!a.empty())
	{
		wx=a.front();
		a.pop();	
		wy=b.front();
		b.pop();	
		wz=c.front();
		c.pop();	//取出x坐标 y坐标 步数
		for(int i=1;i<=f;i++)
		{
			if(d[i])
				continue;//如果已经走过则不再走
			double dx=abs(wx-x[i]),dy=abs(wy-y[i]);
			double p=sqrt(dx*dx+dy*dy);//求出距离
			if(p>1000)
				continue;//如果距离大于1000则不能走这个落脚点
			if(y[i]>=h-1000)
			{
				ans=wz+1;
				return ;
			}//如果能直接到达墙顶则找到了答案 退出BFS
			d[i]=1;//标记这个落脚点已经走过
			a.push(x[i]);	
			b.push(y[i]);
			c.push(wz+1);//存入新的落脚点的x坐标 y坐标 步数
		}
	}
}
int main()
{
     cin>>h>>f;
	 for(int i=1;i<=f;i++)
	 {
		 cin>>x[i]>>y[i];
		 if(y[i]<=1000)
			 a.push(x[i]),b.push(y[i]),c.push(1);//将符合题意的落脚点存入队列中
	 }
	 bfs();
	 cout<<ans;
    return 0;
}
```



---

## 作者：xiaomuyun (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P6245)
## 题目分析

可以很容易从题目中看出最短路做法。但是问题是，不仅起始点不唯一，终点也不唯一。所以我们可以用一个神奇的东西：虚拟点。具体来讲就是把所有可能的起始点和一个另外的特别点连起来（假设那个点在 $(0,0)$，也就是 Bessie 的所在的位置，可以令其编号为 $n+1$），然后将所有可能的终点和再另外的一个新点连起来（令其编号为 $n+2$），然后跑 Dijkstra 求 $n+1$ 号点到 $n+2$ 号点的最短路即可。

## 代码实现

```cpp
#include<iostream>
#include<cmath>
#include<queue>
//n+2:end
//n+1:start
using namespace std;
typedef long long ll;
struct edge{
	ll v,w;
};
vector<edge> g[200005];
struct node{
	ll u,dis;
	bool operator <(const node &n) const{
		return dis>n.dis;
	}
};
struct stopover{
	ll x,y;
}p[200005];
ll n,h,dis[200005];
bool vis[200005];
inline void Dijkstra(ll s){
	priority_queue<node> q;
	for(ll i=1;i<=n+2;++i){
		vis[i]=false;
		dis[i]=0x3f3f3f3f;
	}
	dis[s]=0;
	q.push((node){s,dis[s]});
	while(!q.empty()){
		node no=q.top();
		q.pop();
		ll u=no.u,d=no.dis;
		if(vis[u]) continue;
		vis[u]=true;
		for(ll j=0;j<(ll)g[u].size();++j){
			ll v=g[u][j].v;
			ll w=g[u][j].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push((node){v,dis[v]});
			}
		}
	}
}
inline double dist(const stopover &a,const stopover &b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main(){
	cin>>h>>n;
	for(int i=1;i<=n;++i) cin>>p[i].x>>p[i].y;
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			double d=dist(p[i],p[j]);
			if(d<=1000){
				g[i].push_back((edge){j,1});
				g[j].push_back((edge){i,1});
			}
		}
		if(p[i].y<=1000){//和虚拟起点连边
			g[i].push_back((edge){n+1,0});
			g[n+1].push_back((edge){i,0});
		}
		if(h-p[i].y<1000){//和虚拟终点连边
			g[i].push_back((edge){n+2,1});
			g[n+2].push_back((edge){i,1});
		}
	}
	Dijkstra(n+1);
	cout<<dis[n+2]<<endl;
	return 0;
}
```

## 写在最后

希望大家阅读完这篇题解之后能有所收获，同时不要忘了轻轻地点一个赞！

---

## 作者：⊱⋛赫宇⋚⊰ (赞：1)

[题目](https://www.luogu.com.cn/problem/P6245)

[博客食用](https://blog.csdn.net/yhhy666/article/details/109267214)

/*一旦她到达了一个高度距离 H不到 1000的落脚点，可以直接到墙顶。Bessie 的起点可以在任一高度不超过 1000 的落脚点上。问Bessi爬到顶端的最少次数。*/

# 思路
题目中说要<=1000才能登顶，或者才能开始作为起始地点进行攀爬，因为找起始点和登上的终点很难，也不知道怎么找，所以我们可以**建立两个虚拟点**，**一个是起始点**，**一个是终点**，然后开始建立边分两种情况


## 点与点之间的建边
1.攀岩点和攀岩点之间的边，先给两个点进行求解
欧几里得距离然后判断距离是不是<=1000,如果距离满足，那么可以在两个之间进行建边


## 点与终点起点的建边
2.考虑终点和开始点的建边，如果一个点的纵坐标<=1000那么可以和起始点建边，如果这个点距离最高的地方的差值<=1000,，那么可以和终点建边

## 计算答案
3.然后就可以SPFA/迪杰斯特拉了


## 输出答案
4.最后输出dis[n]-1就好，因为最后一步不需要步数
```cpp
void Dijkstra()
{
   //迪杰斯特拉堆优化的模板
    for(int i=0;i<=f+1;i++) node[i].dis=0x3f3f3f3f;
    //别忘了初始化
    priority_queue<pii,vector<pii>,greater<pii> >q;
    //STL小根堆
    node[0].dis=0;
    q.push({0,0});
    while(q.size())
    {
        pii tmp=q.top();
        q.pop();
        int d=tmp.first,u=tmp.second;
        if(d!=node[u].dis)continue;
        for(int e=node[u].head;e;e=edge[e].next)
        {
            int v=edge[e].to;
            if(node[v].dis>d+edge[e].len)
            {
                node[v].dis=d+edge[e].len;
                q.push({node[v].dis,v});
            }
        }
    }
```


```cpp
#include<bits/stdc++.h>
#define maxn 10010
using namespace std;
int head[maxn*100],tot,vis[maxn];
int n,m;
struct make
{
	int to;
	int ne;
}edge[maxn*100];
inline void add(int x,int y)
{
	edge[++tot].to=y;
	edge[tot].ne=head[x];
	head[x]=tot;
}
inline int read()//读入优化
{
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){res=(res<<1)+(res<<3)+(ch&15);ch=getchar();}
    return res*f;
}
int ans[maxn];
struct node
{
	double x;
	double y;
}a[maxn];
inline double getans(double x1,double y1,double x2,double y2)
{
	return sqrt(  (x1-x2)*(x1-x2)  +   (y1-y2)*(y1-y2));//计算距离，注意要用double
}
queue<int>q;
inline void spfa()//标准spfa模板，跑一遍最短路
{
	for(int i=1;i<=n;i++)ans[i]=0x7fffffff/3;
	ans[1]=0;vis[1]=1;
    q.push(1);
    while(!q.empty())
    {
    	int k=q.front();q.pop();
    	vis[k]=0;
    	for(int i=head[k];i;i=edge[i].ne)
    	{
    		int t=edge[i].to;
    		if(ans[t]>ans[k]+1)
    		{
    			ans[t]=ans[k]+1;
    			if(!vis[t])
    			{
    				vis[t]=1;
    				q.push(t);
				}
			}
		}
	}
}
int main()
{
	m=read();n=read();
	for(int i=1;i<=n;i++)cin>>a[i+1].x>>a[i+1].y;
	n++;
	for(int i=2;i<=n;i++)//普通攀岩点的建边
	{
	   if(a[i].y<=1000)add(i,1),add(1,i);//起始点
	   if(a[i].y+1000>=m)add(i,n+1),add(n+1,i);//终点
	   for(int j=2;j<=n;j++)
	   {
	   if(getans(a[i].x,a[i].y,a[j].x,a[j].y)<=1000)add(i,j);	
	   }	
	}
    n++;
    /*for(int i=1;i<=n;i++)
    {
       for(int j=head[i];j;j=edge[j].ne)
       cout<<edge[j].to<<' ';
       cout<<endl;
	}*/
	spfa();
//	for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
	cout<<ans[n]-1;
	return 0;
}


```


---

## 作者：Instudy (赞：1)

裸题，直接一个爆搜+ $ spfa $即可

时间复杂度没测过但是~~好像$ bzoj $能过~~

~~我是不会告诉你这题 $ luogu $只有1 $s $的时限的~~

首先建个边：

```cpp
void addedge(int u,int v.,int w)
{
  edge[++cnt].next=head[u];
  edge[++cnt].to=v;
  edge[++cnt].dis=w;
  head[u]=cnt; 
}
```

然后跑个裸的最短路：

```cpp
  queue<int> Q;
	int i, now;
	memset(visit, false, sizeof(visit));
	for (i = 1; i <= n; i++)
		dist[i] = INF;
	dist[start] = 0;
	Q.push(start);
	visit[start]= true;
	while (!Q.empty())
	{
		now = Q.front();
		Q.pop();
		visit[now] = false;

		for (i = head[now]; i; i=edge[i].next)
		{
			if (dist[edge[i].to] > dist[now] + edge[i].dis)
			{
				dist[edge[i].to] = dist[now] + edge[i].dis;
				if (visit[edge[i].to] == 0)
				{
					Q.push(edge[i].to);
	                visit[edge[i].to] = true;
				}
			}
		}
	}
```



然后建个虚拟源点就可以跑过了吧（

注意边权要用欧几里得距离（~~好高深的样子拖出去欧拉一顿~~）


---

## 作者：_0x46EDC (赞：0)

[获得更好的阅读体验](https://www.luogu.com.cn/blog/jasonying/p6245-the-climbing-wall-s) [题目传送门](https://www.luogu.com.cn/problem/P6245)

---

### 题目分析

可以看作一张 $01$ 权无向图，结点是落脚点，只要两个落脚点的距离不大于 $1000$ 就连一条边。

对于起点和终点的处理，可以使用 **虚拟结点** 进行处理，即人为生成一个本来不存在的结点。

然后就可以用 Dijkstra 求单源最短路了。

---

接下来结合样例进行详细分析。

```
样例输入：

3000 5

600 800

1600 1800

100 1300

300 2100

1600 2300

样例输出：

3

```

#### Step1. 建图

- 对于距离 $\le1000$ 的两个点，连一条权为 $1$ 的边，代表经过这一条边次数加一。

![](https://i.loli.net/2020/08/09/x84Ud2MGwq9zrsf.png)

- 处理起点。生成编号为 $0$ 的虚拟结点，连接所有 $y_i\le1000$ 的结点，即 $1$ 号结点。注意边权为 $0$ ，代表不需要计算次数。

![](https://i.loli.net/2020/08/09/SCKrUERIndYP28J.png)

- 处理终点。生成编号为 $f+1$ 的虚拟结点，连接所有 $h-y_i\le1000$ 的结点，即 $4$ 号结点和 $5$ 号结点。

![](https://i.loli.net/2020/08/09/FPAIcVGTMoRhzdn.png)

求从 $0$ 号结点到 $f+1$ 号结点的最短距离，可得答案 $3$。

#### Step2. 求最短路

使用朴素版 Dijkstra 算法，几乎就是模板代码。

### 优化

为了缩短代码，我们也可以把这个问题简化为无权无向图。因为一定要从虚拟起点开始，可以将虚拟起点为端点的边权设为 $1$，输出答案时 $-1$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define N 100009
#define INF 0x3f3f3f3f
using namespace std;
vector<int> to[N];
int h,f,d[N];
struct pnt{
    double x,y;
}p[N];//定义结构体，保存每个点的x,y坐标
double dist(int a,int b){
    return sqrt((p[a].x-p[b].x)*(p[a].x-p[b].x)+(p[a].y-p[b].y)*(p[a].y-p[b].y));
}//求两点的欧几里得距离
void add(int u,int v){
    to[u].push_back(v);
    to[v].push_back(u);
}//建无向无权边
void build(){
    for(int u=1;u<=f;u++){
        for(int v=u+1;v<=f;v++){
            if(dist(u,v)<=1000)add(u,v);//如果两点距离不大于1000则建边
        }
        if(h-p[u].y<1000)add(u,f+1);//虚拟终点建边，代表可以一步走到终点
        if(p[u].y<=1000)add(0,u);//虚拟起点建边，代表起点
    }
}
void Dijkstra(){
    fill(d,d+f+9,INF);
    queue<int> q;
    d[0]=0;
    q.push(0);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int i=0;i<to[u].size();i++){
            int v=to[u][i];
            if(d[v]>d[u]+1){
                d[v]=d[u]+1;
                q.push(v);
            }
        }
    }
}//朴素版Dijkstra模板代码
int main(){
    cin>>h>>f;
    for(int i=1;i<=f;i++)cin>>p[i].x>>p[i].y;//保存每个结点的具体信息
    build();//建图
    Dijkstra();
    cout<<d[f+1]-1<<endl;//记得-1
    return 0;
}
```

### 结语

主要考察“虚拟结点”的运用，做完此题建议继续尝试其他图论题目。

---

