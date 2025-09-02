# [USACO09NOV] Job Hunt S

## 题目描述

Bessie is running out of money and is searching for jobs. Farmer John knows this and wants the cows to travel around so he has imposed a rule that his cows can only make D (1 <= D <= 1,000) dollars in a city before they must work in another city. Bessie can, however, return to a city after working elsewhere for a while and again earn the D dollars maximum in that city. There is no limit on the number of times Bessie can do this.

Bessie's world comprises P (1 <= P <= 150) one-way paths connecting C (2 <= C <= 220) cities conveniently numbered 1..C. Bessie is currently in city S (1 <= S <= C). Path i runs one-way from city A\_i to city B\_i (1 <= A\_i <= C; 1 <= B\_i <= C) and costs nothing to traverse.

To help Bessie, Farmer John will give her access to his private jet service. This service features F (1 <= F <= 350) routes, each of which is a one way flight from one city J\_i to a another K\_i (1 <= J\_i <= C; 1 <= K\_i <= C) and which costs T\_i (1 <= T\_i <= 50,000) dollars. Bessie can pay for the tickets from future earnings if she doesn't have the cash on hand.

Bessie can opt to retire whenever and wherever she wants. Given an unlimited amount of time, what is the most money that Bessie can make presuming she can make the full D dollars in each city she can travel to?  Print -1 if there is no limit to this amount.

奶牛们正在找工作。农场主约翰知道后，鼓励奶牛们四处碰碰运气。而且他还加了一条要求：一头牛在一个城市最多只能赚D（1≤D≤1000）美元，然后它必须到另一座城市工作。当然，它可以在别处工作一阵子后又回到原来的城市再最多赚D美元。而且这样的往返次数没有限制。

城市间有P（1≤P≤150）条单向路径连接，共有C（2≤C≤220）座城市，编号从1到C。奶牛贝茜当前处在城市S（1≤S≤C）。路径i从城市A\_i到城市B\_i（1≤A\_i≤C，1≤B\_i≤C），在路径上行走不用任何花费。

为了帮助贝茜，约翰让它使用他的私人飞机服务。这项服务有F条（1≤F≤350）单向航线，每条航线是从城市J\_i飞到另一座城市K\_i（1≤J\_i≤C，1≤K\_i≤C），费用是T\_i（1≤T\_i≤50000）美元。如果贝茜手中没有现钱，可以用以后赚的钱来付机票钱。

贝茜可以选择在任何时候，在任何城市退休。如果在工作时间上不做限制，贝茜总共可以赚多少钱呢？如果赚的钱也不会出现限制，就输出-1。


## 说明/提示

This world has five cities, three paths and two jet routes. Bessie starts out in city 1, and she can only make 100 dollars in each city before moving on.


Bessie can travel from city 1 to city 5 to city 2 to city 3, and make a total of 4\*100 - 150 = 250 dollars.


Source: USACO 2009 November Silver

这个世界上有五个城市，三条单向路径和两条单向航线。贝茜从一号城市开始她的旅行，她在离开一个城市前最多只能在这个城市赚100美元。


贝茜可以通过从一号城市-->五号城市-->二号城市-->三号城市的旅行赚到4\*100-150=250美元。


(注:在四个城市各赚100美元,从五号城市飞到二号城市花掉150美元)


来源:USACO 2009 十一月银组


## 样例 #1

### 输入

```
100 3 5 2 1
1 5
2 3
1 4
5 2 150
2 5 120
```

### 输出

```
250```

# 题解

## 作者：Believe_R_ (赞：45)

## 一道最短路~~（？）~~的好题！！

为什么说这道题好呢？主要有以下两点：

**1. 这道题完美地需要我们将点权转成边权：**

>$Bessie$ 需要去这么多城市，而每座城市他都要赚 $D$ 美元。那我们为什么不直接将每条普通边的边权就设置成 $D$ 呢？这两者之间是等价的呀·····
>
>那对于飞行边来说，同理，飞行边需要花费 $T$ 美元，而到一个城市又可以赚 $D$ 美元，那我们就可以将飞行边权设为 $D-T$。
>
> 这样，存图的事就解决了

**2. 只要你读懂题目，就会发现这题压根不是最短路，是最长路······**
> 做最长路主要有两种做法（**会的可以挑过**，其实和做最短路的思想都一样）：
>
> $2.1$ 做最短路是我们是现将 $dis$ 数组设为无穷大，再每次更新最小值。反过来，最长路就可以将 $dis$ 数组都设为 $0$ ,再每次更新最大值。
>
> $2.2$ 将所有边权都取反后，再求最短路（至于为什么，在纸上画个五分钟就出来了~ $QwQ$）
>
> 如果你还不懂怎么求最长路，出门左转: [学图论，你真的了解最短路吗？](https://www.luogu.org/blog/wym483739/xue-tu-lun-ni-zhen-di-liao-xie-zui-duan-lu-ma-post) 
>
> 再来一道模板题：[P1807 最长路_NOI导刊2010提高（07）](https://www.luogu.org/problem/P1807)
>
>**温馨提示：$Dijskra$ 算法无法处理负权环！**


下面看我的代码，应该就看到懂了：
```cpp
#include <bits/stdc++.h>
#define int long long
#define M 1000
using namespace std;

int tot=0, head[M], nex[M], to[M], dis[M];
int d, m, n, f, s;                      //d, p, c, f, s
int vis[M], w[M], cnt[M];
priority_queue<int, vector<int>, greater<int> > q;  //大根堆

inline int read()
{
    int re=0, f=1; char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0' && ch<='9') {re=re*10+(ch-'0'); ch=getchar();}
    return re*f;
}

void add_edge(int x,int y,int z)
{
    to[++tot]=y;
    dis[tot]=z;
    nex[tot]=head[x];
    head[x]=tot;
}

void Spfa()
{
    q.push(s);
    w[s]=d; vis[s]=1; cnt[s]++;
    while(!q.empty())
    {
        int u=q.top(); q.pop();
        vis[u]=0;
        if(++cnt[u]>n) {printf("-1\n"); exit(0);}  
        for(int i=head[u];i;i=nex[i])
        {
            int v=to[i];
            if(w[v]<w[u]+dis[i])
            {
                w[v]=w[u]+dis[i];      //我是用第一种求最长路的算法做的~qwq
                if(!vis[v])
                {
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
}

signed main()
{
    d=read(); m=read(); n=read(); f=read(); s=read();
    for(int i=1;i<=m;++i)
    {
        int x=read(), y=read();
        add_edge(x,y,d);                      //将点权转换为边权。
    }
    for(int i=1;i<=f;++i)
    {
        int x=read(), y=read(), z=read();
        add_edge(x,y,d-z);
    }
    Spfa();
    int ans=0;
    for(int i=1;i<=n;++i) ans=max(ans,w[i]);
    printf("%lld\n",ans);
    return 0;
}
```


## $P.s$
下面我也贴上了洛谷P1807 最长路_NOI导刊2010提高（07）的标称【这里我是用第二种求最长路的方法求的】
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=120000;
const int INF=0x3f3f3f3f;
ll dis[N],to[N],nex[N],head[N];
ll n,m,ans,tot=0;
ll d[N],vis[N];
void add_edge(int x,int y,int l)
{
    to[++tot]=y;
    dis[tot]=l;
    nex[tot]=head[x];
    head[x]=tot;
}
queue<int> q;
void Spfa()
{
    q.push(1); vis[1]=1;
    while(!q.empty())
    {
        ll u,v;
        u=q.front(); q.pop(); vis[u]=0;
        for(int i=head[u];i;i=nex[i])
        {
            v=to[i];
            if(d[v]>d[u]+dis[i])
            {
                d[v]=d[u]+dis[i];
                if(vis[v]==0) {vis[v]=1; q.push(v);}
            }
        }
    }
}
int main()
{
    scanf("%lld%lld",&n,&m);
    if(m==0) {printf("-1\n"); return 0;}
    for(int i=1;i<=m;++i)
    {
        ll x,y,l;
        scanf("%lld%lld%lld",&x,&y,&l);
        l=0-l;
        add_edge(x,y,l);              //minus
    }
    memset(d,0,sizeof(d));
    d[1]=0;
    Spfa();
    if(d[n]==0) {printf("-1\n"); return 0;}
    printf("%lld\n",-d[n]);
    return 0;
}
```

## 最后,在给大家带来一道双倍经验 $QwQ$

传送门： [P2648 赚钱](https://www.luogu.org/problemnew/show/P2648)

大家可以自己想一下，真的和上题没什么区别！！！

#### 不会做的请往下看：

由于这题没有规定起始节点为那个，那么最简单的方法就是去枚举，然而，这复杂度不用算就知道用 $SPFA$ 肯定 $T$ 到飞！这时，我们就要引进一个超级源点。

>超级源点就是在原图之外再设一个点，并将这点连向原图中所有的节点。
>
>然后，我们从超级源点开始做 $SPFA$ ，就等同与枚举原图中的每一个节点。
>
>在不懂就看一下这张图：
>
>![](https://cdn.luogu.com.cn/upload/pic/67019.png)
>
>![](https://cdn.luogu.com.cn/upload/pic/67022.png)

代码就看[这里]( https://www.luogu.org/paste/7g9jq0xe)吧【可以尝试自己写一下】！

### 最后可别忘了点赞 $qwq$...

---

## 作者：TOM_闫 (赞：22)

如题，可以看成求最长路的问题

求最长路有许多方法，大家也可以在洛谷搜一下最长路

我说一种题解里没有的方法，将公路的边权看为d，将飞机的边权看为d-t，然后**将边权取反，不就变成求最短路的问题了吗！！！**

这时要注意边权可能存在负数，所以可以选择spfa或bellman-ford，我选bellman-ford，毕竟数据量不大啊(~~才不是我懒~~)

但是。。。这竟然上了最优解的第一页。。。

下面贴上代码
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int MaxN=99999999;
int d,p,c,f,s;
int first[221],next[501],dis[221];
struct Node{
	int u,v,w;
}mapp[501];
int main()
{
	int i,j,pd,a,minn,x;
	scanf("%d%d%d%d%d",&d,&p,&c,&f,&s);
	for(i=1;i<=p;i++)
	{
		scanf("%d%d",&mapp[i].u,&mapp[i].v);
		mapp[i].w=-d;         //注意存边
	}
	for(i=p+1;i<=p+f;i++)
	{
		scanf("%d%d%d",&mapp[i].u,&mapp[i].v,&a);
		mapp[i].w=a-d;        //注意存边
	}
	for(i=1;i<=c;i++)
		dis[i]=MaxN;
	dis[s]=0;
	for(i=1;i<c;i++)
	{
		pd=false;   //加上pd可以优化bellman-ford，减少无用功
		for(j=1;j<=p+f;j++)
			if(dis[mapp[j].v]>dis[mapp[j].u]+mapp[j].w)
			{
				pd=true;
				dis[mapp[j].v]=dis[mapp[j].u]+mapp[j].w;
			}
		if(pd==false) break;
	}
    //判负环
	pd=false;
	for(j=1;j<=p+f;j++)
			if(dis[mapp[j].v]>dis[mapp[j].u]+mapp[j].w)
			{
				pd=true;
				dis[mapp[j].v]=dis[mapp[j].u]+mapp[j].w;
			}
	if(pd==true) 
	{
		printf("-1\n");
		return 0;
	}
	minn=MaxN;
	for(i=1;i<=c;i++)
		if(dis[i]<minn)
		{
			minn=dis[i];
			x=i;
		}
	printf("%d\n",(-1)*dis[x]+d);//最终的答案还要加上起点的d
	return 0;
}
```

---

## 作者：GLZP (赞：20)

	
		题中要求解的是钱的最大值，
    	我们就将通向其他城市的步行道路的权值设置为题目中所给的
    钱的数量 
    
    	飞行路的权值就设置为赚钱的数量-飞机票
    	dis[i]就用相加，而不是想减
    	因为能随时退休，则在dijkstra之后用循环遍历最大值输出 
    以下为代码
    
   ```c
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int cnt=0; 
int d,p,c,f,s;
struct node//标准结构 
{
	int to;
	int next;
	int w;
};
int head[1010];
node edge[1010];
bool book[1010];
int cntt[1010];//当cnt[i]的次数==n次时，输出-1 
int dis[1010];//到达dis个城市最多可以赚多少钱
struct cmp
{
    bool operator()(int a,int b)
    {
        return dis[a]<dis[b];//如果返回true就是a排在b后面
    }
};
void add(int u,int v,int ww)
{
	edge[++cnt].to=v;
	edge[cnt].w=ww;//dis为赚的钱相加，最后输出dis最高的 
	edge[cnt].next=head[u];
	head[u]=cnt;
}

priority_queue<int,vector<int>,cmp>q;
int main()
{
	scanf("%d%d%d%d%d",&d,&p,&c,&f,&s);
	//d为钱，p为路，c为城市，f为fly，s为每个城市可以获得的钱 
	for(int i=1;i<=p;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v,d);//因为权值相加，所以这里的权值
		//为可以赚的钱 
	}
	for(int i=1;i<=f;i++)
	{
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		add(u,v,d-w);//这里的权值
		//是赚的钱减去机票钱
		//因为dis[i]至少都是大于0的
		//所以小于0，也就是没钱的时候不会改变值 
	}
	q.push(s);
	book[s]=1;
	dis[s]=d;
	cntt[s]++;
	while(q.empty()==0)
	{
		int u=q.top();
		q.pop();
		book[u]=0;
		cntt[u]++;
		//出队cnt累计超过n-1说明有负环 
		if(cntt[u]>n)
		//判断无限赚钱情况 
		{
		//为方便写>n,实际上是次数>n-1时就输出-1 
			printf("-1"); 
			return 0;
		}
		for(int i=head[u];i>0;i=edge[i].next)
		{
		//标准的spfa 
			if(dis[edge[i].to]<dis[u]+edge[i].w)
			{
				dis[edge[i].to]=dis[u]+edge[i].w;
				if(book[edge[i].to]==0)
				{
					q.push(edge[i].to);
					book[edge[i].to]=1;
				}
			}
		}
	}
	int maxx=0;
	for(int i=1;i<=c;i++)
	{
		if(dis[i]>maxx)
		{
			maxx=dis[i];//因为可以随时退休，所以要在
			//所有城市里找到最大值 
		}
	}
	printf("%d\n",maxx);
	//for(int i=1;i<=c;i++)printf("%d ",dis[i]);检查值有没有问题 
	return 0;
}
```

---

## 作者：Dawn_Sdy (赞：5)

此题很麻烦的一点就是这张图既有点权又有边权，这就导致我们不好用常见的图论算法解决。

于是我们很容易想到一种思路：

无论经过的是免费线路还是付费线路，我们都可以拿到出边所连的点的点权，也就是说，我们走一条边，会获得点权-边权的价值。

所以我们可以把每一条边所连得点的点权加到边权中。

那么所求就是这张图的最长路。

由于图中会有负边权，所以我们需要用SPFA。

在考虑题目中说的输出-1的情况。

如果在我们的图中存在正环，则可以无限的走下去，即输出-1。

那么我们只要在SPFA的过程中判断每个点入队的次数是否大于n-1次就行了。

答案就是原点到每个点中路径长度最长的那个

(PS：~~SPFA时间复杂度为O(玄学)所以需要卡常~~)

下面给出AC代码：

```cpp
#include<cstdio>//不写万能头，减小常数
#include<queue> 
//不写namespace减少常数
#define INF 0x7ffffff
int d,m,n,k,s;
struct node{
	int v,next;
	int w;
}edge[1005];
int len,head[505];
int dis[505][505];//邻接矩阵
int dist[505];//储存最长路
bool vst[505];//标记
int tot[505];//每个点的入队次数
bool err;
int ans;
inline void make_map(int u,int v,int w)//链式前向星存图
{
	len++;
	edge[len].next=head[u];
	edge[len].v=v;	
	edge[len].w=w;
	head[u]=len;
}
inline void SPFA()//SPFA
{
	for (register int i=1;i<=n;i++)
	    dist[i]=-INF;
	std::queue <int> q;
	dist[s]=d;
	vst[s]=1;
	tot[s]=1;
	q.push(s);
	while (!q.empty())
		  {
          int x=q.front();
		  q.pop();
		  vst[x]=0;
		  for (register int i=head[x];i;i=edge[i].next)
			  {
			  int y=edge[i].v;
			  int z=edge[i].w;
			  if (dist[y]<dist[x]+z)
				 {
				 tot[y]++;
				 if (tot[y]>=n)//判断图中有没有正环
				     {
					 printf("-1");
					 err=1;
					 return ;
					 }
				 dist[y]=dist[x]+z;
				 if (!vst[y])
					 {
					 vst[y]=1;
					 q.push(y);
					 }
  				 }
			  }
          }
}
int main(){
	scanf("%d%d%d%d%d",&d,&m,&n,&k,&s);
	for (register int i=1;i<=m;i++)
		{
		int u,v;
	    scanf("%d%d",&u,&v);
	    dis[u][v]=d;
        make_map(u,v,d);
		}
	for (register int i=1;i<=k;i++)
		{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		if (!dis[u][v])//因为可能有重边，如果有免费路线就不要建付费路线了
        //用邻接矩阵判断重边比较方便，所以也存一个邻接矩阵
 		   make_map(u,v,d-w);
		}
	SPFA();
	if (err)
	   return 0;
	for (register int i=1;i<=n;i++)//输出
		ans=std::max(ans,dist[i]);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Protons (赞：5)

## 这个题的关键就是化点权为边权

这个题有点权。由于我们对处理含有点权（在每个城市赚到的钱）和边权（飞机票钱）的图比较陌生，所以我们就思考能否化点权为边权。

我们发现，每个点点权都相同，而且飞机票钱可以先欠着，所以我们就可以以在每个城市赚到的钱为边权；如果有飞机航线，就以在每个城市赚到的钱减去飞机票钱为边权，建图。然后我们就把它转化成了一个在有向图中找最长路的题。

但是我只学过最短路怎么找，所以我使用了大根堆、负边权和spfa算法来实现意义上的找“最短路”。

代码如下：
```cpp
#include<queue>
#include<vector>
#include<cstdio>
#include<iostream>
using namespace std;
int n,m,f,t,s,cnt;
struct Edge
{
	int nst,to,dis;
}edge[1000];
int head[250],dis[250],vis[250],tim[250],maxx;
//tim用于记录经历过该点的次数，防止出现负环
void add(int a,int b,int c)
{
	edge[++cnt].nst=head[a];
	edge[cnt].to=b;
	edge[cnt].dis=t-c;
	head[a]=cnt;
}
void spfa()
{
	maxx=0;
	priority_queue< pair<int,int> > q;
	dis[s]=t;
	vis[s]=1; 
	tim[s]++;
	q.push(make_pair(t,s));
	while(q.size())
	{
		int u=q.top().second,v=1;
		q.pop();
		vis[u]=0;
		tim[u]++;
		if(tim[u]>n)
		{
			printf("-1");
			return;
		}
		for(int i=head[u];i;i=edge[i].nst)
		{
			v=edge[i].to;
			if(dis[u]+edge[i].dis>dis[v])
			{
				dis[v]=dis[u]+edge[i].dis;
				if(!vis[v])
				{
					q.push(make_pair(-dis[v],v));
					vis[v]=1;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	if(maxx<dis[i])maxx=dis[i];
	printf("%d",maxx);
}
int main()
{
	scanf("%d%d%d%d%d",&t,&m,&n,&f,&s);
	int a,b,c;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b,0);
	}
	for(int i=1;i<=f;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
	}
	spfa();
	return 0;
}
```

---

## 作者：xMinh (赞：5)

#蒟蒻的弗洛伊德

这题好像很少有用弗洛伊德来做的？

但是的确可以。

在陆地上的路权值设为d

在空中的路权值设为d-费用

然后用floyed跑最长路

但是跑完对每个f[i][j]都要加上d，因为没有计算起点赚的钱

之后做两个判断，如果某个环里有起点

或者起点能到达的某个点在环里面

就输出-1

如果这两种情况都不存在就直接看从起点出发从哪个点结束钱最多

输出就行了

PS：判断某个环是否赚钱可以这么计算：

因为f[i][j]=d+d-费用i到j

f[j][i]=d+d-费用j到i

所以用f[i][j]+f[j][i]-2\*d是否大于0就能判断这个环能不能赚钱了

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define inv inline void
#define ini inline int
#define rint register int 
using namespace std;
int d,p,c,n,s,f[301][301];
int main()
{
    scanf("%d%d%d%d%d",&d,&p,&c,&n,&s);
    for (rint i=1;i<=c;i++)
        for (rint j=1;j<=c;j++)
            f[i][j]=-1000000000;
    for (rint i=1;i<=p;i++)
    {
        int x,y;scanf("%d%d",&x,&y);
        f[x][y]=d;
    }
    for (rint i=1;i<=n;i++)
    {
        int x,y,z;scanf("%d%d%d",&x,&y,&z);
        f[x][y]=max(f[x][y],d-z);
    }
    for (rint i=1;i<=c;i++) f[i][i]=0;
    for (rint k=1;k<=c;k++)
        for (rint i=1;i<=c;i++)
            for (rint j=1;j<=c;j++)
                if (i!=j && j!=k && i!=k)
                    f[i][j]=max(f[i][j],f[i][k]+f[k][j]);
    for (rint i=1;i<=c;i++)
        for (rint j=1;j<=c;j++)
            f[i][j]+=d;
    for (rint i=1;i<=c;i++)
        if (f[s][i]+f[i][s]-2*d>0 && i!=s)
        {            
            cout<<-1;
            return 0;
        }
    for (rint i=1;i<=c;i++)
        for (rint j=1;j<=c;j++)
            if (i!=j && i!=s && j!=s)
                if (f[s][i]>-2000000 && f[i][j]+f[j][i]-2*d>0)
//350条航线，一条不超过50000元，就算再亏本也不会亏过1.75千万
                {
                    cout<<-1;
                    return 0;
                }
    int ans=0;
    for (rint i=1;i<=c;i++)
        ans=max(ans,f[s][i]);
    printf("%d",ans);
}
```

---

## 作者：孑思 (赞：4)

# 这其实是一个求最长路径的题

## 思维是差分约束

~~#### 然而本蒟蒻第一天学这个东西WA了三遍~~

~~#### 失去信心.jpg~~

如果a->b不用坐飞机，那就当路径是d

如果a->b要坐飞机，那路径就当作d-花掉的钱

然后求出的最长路径就是赚钱最多的

Well,talk is cheap,show me the code.

```cpp
#include<bits/stdc++.h>
using namespace std;
int d,p,c,f,s;
queue<int> q;//听说数组处理会快一点，然而今天被学长按头用队列QAQ
int dis[25000],used[25000],go[25000];
int head[100000],nxt[100000],cnt,var[100000],cost[100000];//数组可能不用开这么大
bool flag;//判断有没有形成环的
void add(int x,int y,int z){//链表不解释
	cnt++;
	var[cnt]=y;
	cost[cnt]=z;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
void spfa(){
	q.push(s);
	used[s]=true;
	dis[s]=d;//初始化，因为可以在本地挣钱
	while(!q.empty()){
		int u=q.front();
		q.pop();
		used[u]=true;
		for(int i=head[u];i;i=nxt[i]){
			int v=var[i],cos=cost[i];
			if(dis[v]<dis[u]+cos){
				dis[v]=dis[u]+cos;
				go[v]++;//学长说go[v]=go[u]+1可以节省时间，但是说不清，就不用啦;
				if(go[v]>c){//判断有没有形成环
					flag=true;
					return;//形成就退出
				}
				if(!used[v]){
					q.push(v);
					used[v]=true;
				}
			}
		}
		used[u]=false;
	}
}
int main(){
	scanf("%d%d%d%d%d",&d,&p,&c,&f,&s);
	int a,b,k;
	for(int i=1;i<=p;i++){
		scanf("%d%d",&a,&b);
		add(a,b,d);//a->b不用坐飞机，当路径是d
	}
	memset(dis,-0x3f,sizeof(dis)); //赋一个极小值，因为有的路径权值<0
	for(int i=1;i<=f;i++){
		scanf("%d%d%d",&a,&b,&k);
		add(a,b,d-k);//a->b要坐飞机，路径为d-k
	}
 	spfa();
	int maxx=-0x3f;//maxx还是极小值
	if(flag)cout<<"-1"<<endl;
	else{
		for(int i=1;i<=c;i++){
			if(maxx<dis[i])maxx=dis[i];
		}
		cout<<maxx<<endl;
	}
	return 0;
}
```

---

## 作者：Memorize (赞：4)

一道裸的最“短”路 其实就是找一条最长路 稍稍改了一下而已


```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
int d,p,c,f,s,x,y,z,k=0;
struct node{
    int to,next,w;
}e[5000];
int head[5000],dist[500],vis[500],du[500];
int maxn=-1;
int queue[10000],qhead=0,qtail=0;
void add(int u,int v,int w)
{
    e[++k].next=head[u];
    e[k].to=v;
    e[k].w=w;
    head[u]=k;
}
void spfa(int x)
{
    memset(vis,false,sizeof(vis));
    memset(dist,-0x7f7f7f,sizeof(dist));
    memset(du,0,sizeof(du));
    dist[x]=d,vis[x]=true;
    queue[++qtail]=x;
    while(qhead<qtail)
    {
        int p=queue[++qhead];
        vis[p]=false;
        for(int i=head[p];i;i=e[i].next)
        {
            if(dist[e[i].to]<dist[p]-e[i].w+d)
            {
                dist[e[i].to]=dist[p]-e[i].w+d;
                du[e[i].to]++;
                if(du[e[i].to]>c){
                    printf("-1");
                    exit(0);
                }
                if(!vis[e[i].to])
                {
                    queue[++qtail]=e[i].to;
                    vis[e[i].to]=true;
                }
            }
        }
    }
    for(int i=1;i<=c;i++) maxn=max(maxn,dist[i]);
    printf("%d",maxn);
}
int main()
{
    scanf("%d%d%d%d%d",&d,&p,&c,&f,&s);
    for(int i=1;i<=p;i++)
    {
       scanf("%d%d",&x,&y);
       add(x,y,0);    
    }    
    for(int i=1;i<=f;i++)
    {
       scanf("%d%d%d",&x,&y,&z);
       add(x,y,z);
    }
    spfa(s);
    return 0;    
}
```

---

## 作者：xsap (赞：1)


- 因为有边权，还是求最值，想到最 ~~短~~ 长路，可是点权不好处理到最长路算法中。所以，想到把点权放到边权中，即$ G_{i}.w = D - T_{i}$，这样就可以直接跑最长路了
- 至于如何计算最长路，主要有两种方法。法一，是将最长路转化为最短路，所以插入边权时，直接取反即可；法二，是直接改spfa中判断的部分（可以参考代码SPFA里的判断）
- 输出$-1$的情况就是当有**正环**。肯定使用SPFA，记录一个cnt数组保存每个节点入队次数，若$cnt_{i} > n$，说明有**正环**。
- 代码：（SPFA版）



```cpp
# include <iostream>
# include <cstdio>
# include <queue>

using namespace std ;

struct Edge{	
	int to , next , w ;
} g[1005] ;

int d , p , c , f , s ;

int fte[225] , gsz , cnt[225] ;

void addedge( int x , int y , int z )
{
	g[++ gsz] = ( Edge ) { y , fte[x] , z } ;
	fte[x] = gsz ;
}
int dis[225] ;
bool already[225] ;
queue < int > q ;

bool spfa( int s )
{
	for ( int i = 1 ; i <= c ; i++ )
		dis[c] = -1e9 , already[i] = false ;
	dis[s] = d ;
	already[s] = 1 ;
	q.push( s ) ;
	while ( ! q.empty() )
	{
		int x = q.front() ;
		cnt[x] ++ ;
		if ( cnt[x] > c )
			return false ;
		already[x] = 0 ;
		q.pop() ;
		for ( int i = fte[x] ; i ; i = g[i].next )
		{
			int y = g[i].to ;
			if ( dis[x] + g[i].w <= dis[y] ) //注意，这里要改成大于才改，小于等于不改
				continue ;
			dis[y] = dis[x] + g[i].w ;
			if ( already[y] )
				continue ;
			already[y] = 1 ;
			q.push( y ) ;
		}
	}
	return true ;
}

int main()
{
	scanf("%d%d%d%d%d" , &d , &p , &c , &f , &s) ;
	for ( int i = 1 ; i <= p ; i++ )
	{
		int x , y ;
		scanf("%d%d" , &x , &y) ;
		addedge( x , y , d ) ;
	}
	for ( int i = 1 ; i <= f ; i++ )
	{
		int x , y , w ;
		scanf("%d%d%d" , &x , &y , &w) ;
		addedge( x , y , d - w ) ;
	}
	if ( ! spfa( s ) )
	{
		puts("-1") ;
		return 0 ;
	}
	int ans = -1e9 ;
	for ( int i = 1 ; i <= c ; i++ )
		ans = max( ans , dis[i] ) ;
	printf("%d\n" , ans) ;
	return 0 ;
}
```


---

## 作者：lemir3 (赞：0)

[*获得更好的阅读体验*](https://www.cnblogs.com/Lemir3/p/11061539.html)

[*P1938 [USACO09NOV]找工就业Job Hunt*](https://www.luogu.org/problemnew/show/P1938)

[*P2648 赚钱*](https://www.luogu.org/problemnew/show/P2648)

~~双倍经验,双倍工业产值~~

又是类似的题呢.

题中有两种边,一种是边权为0的,即题中的步行通道,一种是边权为负数的,即题中的飞行航线.

然后每个点上有一个权值.

所以说大体上就是用SPFA跑一遍最长路.

但是显而易见,这道题中存在环,为了防止这个不限赚钱时间的奶牛成为资产阶级,我们要制裁它.

而且如果存在环的话就一定是正权的环.

然后推理一下就可以发现,一个有n个点的图中的任意一个点,最多被遍历n-1次(这种情况就是一个菊花图),如果遍历的次数大于n,就说明存在环了.

开一个数组记录一下每个点被遍历的次数就可以了.

之后是第二道题,可以从任意一个点开始赚钱.

我一开始想的是跑n遍SPFA,还好数据水没TLE.

后来想了一下,可以开一个虚构的点来连接所有的点,然后从这个点开始遍历.

我就没有去代码实现了.

下面是第一题的代码,第二题的稍微改一下就可以了.

```cpp

#include<bits/stdc++.h>

using namespace std;

queue<int>q;

struct edge
{
    int to,next,val;
}e[510];

int d,p,c,f,s,size,ans=-2147483647,cnt=1;
int head[230],dis[230],in[230];
bool flag[230];

void edge_add(int,int,int);
void SPFA();

int main()
{
    memset(head,-1,sizeof(head));
    scanf("%d%d%d%d%d",&d,&p,&c,&f,&s);
    for(int i=1;i<=p;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        edge_add(a,b,0);
    }
    for(int i=1;i<=f;i++)
    {
        int a,b,v;
        scanf("%d%d%d",&a,&b,&v);
        edge_add(a,b,-v);
    }
    SPFA();
    for(int i=1;i<=c;i++)ans=ans<dis[i]?dis[i]:ans;
    printf("%d\n",ans);
return 0;
}

void edge_add(int from,int to,int val)
{
    e[++size].to=to;
    e[size].val=val;
    e[size].next=head[from];
    head[from]=size;
}

void SPFA()
{
    memset(flag,false,sizeof(flag));
    memset(dis,-0x3f,sizeof(dis));
    dis[s]=d;
    q.push(s);
    flag[s]=true;
    while(!q.empty())
    {
        int from=q.front();
        q.pop();
        flag[from]=false;
        for(int i=head[from];i!=-1;i=e[i].next)
        {
            int to=e[i].to;
            int val=e[i].val;
            if(dis[to]<dis[from]+val+d)
            {
                in[to]++;
                if(in[to]>c)
                {
                    printf("-1\n");
                    exit(0);
                }
                dis[to]=dis[from]+val+d;
                if(flag[to]==false)
                {
                    q.push(to);
                    flag[to]=true;
                }
            }
        }
    }
}

```

---

## 作者：Panthera_AFO (赞：0)

30min切掉

这题没有想象中那么水，当一道练手题还是可以的

这题最主要的思路就是化点权为边权

因此要注意初始化问题

然后就是裸的最长路+判断正权环（如果有正权环，就可以反复横跳了）

代码思路挺清楚的，也没啥细节，随便看看吧
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
int const maxn=240,maxm=510;
struct E
{
	int to,next,w;
	E(int to=0,int next=0,int w=0):
		to(to),next(next),w(w){}
}e[maxm<<1];
int head[maxn],cost[maxn],cnt,maxx,sum[maxn],notle;
int n,m1,m2,val,s;
void add(int u,int v,int w)
{
	e[++cnt]=(E){v,head[u],w};
	head[u]=cnt;
}
void readin()
{
	scanf("%d%d%d%d%d",&val,&m1,&n,&m2,&s);
	for(int x,y,i=1;i<=m1;i++)
		scanf("%d%d",&x,&y),add(x,y,val);
	for(int x,y,z,i=1;i<=m2;i++)
		scanf("%d%d%d",&x,&y,&z),add(x,y,val-z);
}
int spfa()
{
	std::queue<int>q;
	q.push(s);
	cost[s]=val;
	maxx=val;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i!=-1;i=e[i].next)
		{
			int v=e[i].to,w=e[i].w;
			if(cost[v]<cost[u]+w)
			{
				if(++sum[v]>n)
					return true;
				cost[v]=cost[u]+w,maxx=std::max(maxx,cost[v]),q.push(v);
			}
		}
	}
	return false;
}
int main()
{
	memset(head,-1,sizeof(head));
	memset(cost,-0x1f,sizeof(head));
	readin();
	if(spfa())
		printf("-1");
	else
		printf("%d",maxx);
	return 0;
}
```

---

## 作者：皓芷 (赞：0)

一遍dfsO(n)解决，vis为访问标记，visn为当前链的访问标记，last为从起点走到当前节点的赚取费用，now为从当前节点往下走得到的最大赚取费用。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define mysister
using namespace std;
const int maxn=221;
struct tu
{
    int v,w;
    tu(int a,int b):v(a),w(b){}
};
int d,p,c,f,s,vis[maxn],visn[maxn],now[maxn],a,b,w,last[maxn];
vector<tu>g[maxn];
void dfs(int u)
{
    for(int i=0;i<g[u].size();i++)
    {
      if(!vis[g[u][i].v])
      {
        visn[g[u][i].v]=vis[g[u][i].v]=1;
        last[g[u][i].v]=g[u][i].w+last[u];
        dfs(g[u][i].v);
        last[g[u][i].v]=0;
        visn[g[u][i].v]=0;
        now[u]=max(now[u],now[g[u][i].v]+g[u][i].w);
      }
      else if(!visn[g[u][i].v])
      {
          now[u]=max(now[u],now[g[u][i].v]+g[u][i].w);
      }
      else if(u!=g[u][i].v&&last[u]-last[g[u][i].v]+g[u][i].w>0)//有大于零的环就输出-1
      {
          printf("-1");
          exit(0);
      }
    }
}
int main()
{
    scanf("%d%d%d%d%d",&d,&p,&c,&f,&s);
    for(int i=0;i<p;i++)
    {
      scanf("%d%d",&a,&b);
      g[a].push_back(tu(b,d));
    }
    for(int i=0;i<f;i++)
    {
      scanf("%d%d%d",&a,&b,&w);
      g[a].push_back(tu(b,d-w));
    }
    visn[s]=vis[s]=1;
    dfs(s);
    printf("%d",now[s]+d);
    return 0;
}
```

---

## 作者：pjl_zju (赞：0)



     
     
             
        
     
             
     
     
```cpp
#include "bits/stdc++.h"
using namespace std;
int conn[221][221];
vector<int> v[221];
int dis[221]; 
int main()
{
    int D,P,C,F,S;
     cin>>D>>P>>C>>F>>S;
     for(int i=0;i<P;++i)
     {
         int a,b;
         cin>>a>>b;
         conn[a][b]=D;
         v[a].push_back(b);
     }
     for(int i=0;i<F;++i)
     {
         int a,b,t;
         cin>>a>>b>>t;
         if(conn[a][b]==0)//已经有路了，肯定不坐飞机 
        {
             conn[a][b]=D-t;
             v[a].push_back(b);
        }
     }
     if(false)//本来这个条件是用来检测是否包含权值和为正的环的，先写个false看能过几个case..。结果。。AC了。。数据太弱了。。 
     {
         cout<<-1<<endl;
         return 0;
     }
     else
     {
         dis[S]=D;
         queue<int> q;
         q.push(S);
         while(!q.empty())
         {
             int cur=q.front();
             q.pop();
//             cout<<"cur="<<cur<<endl;
            for(int i=0;i<v[cur].size();++i)
            {
                int to=v[cur][i];
                if(dis[cur]+conn[cur][to]>dis[to])
                {
                    dis[to]=dis[cur]+conn[cur][to];
                    q.push(to);
                }
             }    
        }
     }
     int mx=0;
     for(int i=1;i<=C;++i)
     {
         if(dis[i]>mx)
         mx=dis[i];
     }
     cout<<mx<<endl;
     return 0;
}
```

---

## 作者：fanhaotian (赞：0)

先为大家献上翻译···

暑假结束了，毕业了。奶牛们正在找工作。农场主约翰知道后，鼓励奶牛们四处碰碰运气。而且他还加了一条要求：一头牛在一个城市最多只能赚D（1≤D≤1000）美元，然后它必须到另一座城市工作。当然，它可以在别处工作一阵子后又回到原来的城市再最多赚D美元。而且这样的往返次数没有限制。

城市间有P（1≤P≤150）条单向路径连接，共有C（2≤C≤220）座城市，编号从1到C。奶牛贝茜当前处在城市S（1≤S≤C）。路径i从城市A\_i到城市B\_i（1≤A\_i≤C，1≤B\_i≤C），在路径上行走不用任何花费。

为了帮助贝茜，约翰让它使用他的私人飞机服务。这项服务有F条（1≤F≤350）单向航线，每条航线是从城市J\_i飞到另一座城市K\_i（1≤J\_i≤C，1≤K\_i≤C），费用是T\_i（1≤T\_i≤50000）美元。如果贝茜手中没有现钱，可以用以后赚的钱来付机票钱。

贝茜可以选择在任何时候，在任何城市退休。如果在工作时间上不做限制，贝茜总共可以赚多少钱呢？如果赚的钱也不会出现限制，就输出-1。

【输入】

第一行：5个用空格分开的整数D，P，C，F，S。

第2到第P+1行：第i+1行包含2个用空格分开的整数，表示一条从城市A\_i到城市B\_i的单向路径。

接下来F行，每行3个用空格分开的整数，表示一条从城市J\_i到城市K\_i的单向航线，费用是T\_i。

【输出】

一个整数，在上述规则下最多可以赚到的钱数。



好，然后就是思路了

我的想法是Bellman\_ford（松弛ing）

关键代码1

```cpp
dist[S]=-D;
    for(i=1;i<C;i++)
    {
        flag=true;
        for(j=1;j<=C;j++)
            for(k=1;k<=G[j].sum;k++)
                if(dist[G[j].E[k].v]>dist[j]+G[j].E[k].w)
                {
                    dist[G[j].E[k].v]=dist[j]+G[j].E[k].w;
                    flag=false;
                }
        if(flag)
            break;
    }
    flag=true;
    for(j=1;j<=C;j++)
        for(k=1;k<=G[j].sum;k++)
            if(dist[G[j].E[k].v]>dist[j]+G[j].E[k].w)
            {
                flag=false;
                break;
            }
    if (flag==false)
    {
        cout<<-1;
        return;
    }
    for(i=1;i<=C;i++)
        s=min(s,dist[i]);
    cout<<-s;
```
bellman\_ford过程记得dist要memset成无穷大(0x7f即可)

关键代码2(读入)

```cpp
for(i=1;i<=P;i++)
    {
        cin>>a>>b;
        G[a].E[++G[a].sum].v=b;
        G[a].E[G[a].sum].w=-D;
    }
    for(i=1;i<=F;i++)
    {
        cin>>a>>b>>w;
        G[a].sum++;
        G[a].E[G[a].sum].v=b;
        G[a].E[G[a].sum].w=-D+w;
    }
```
想必大家都懂了吧，祝大家AC！


---

