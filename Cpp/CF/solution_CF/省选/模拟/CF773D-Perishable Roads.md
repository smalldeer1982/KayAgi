# Perishable Roads

## 题目描述

In the country of Never, there are $ n $ cities and a well-developed road system. There is exactly one bidirectional road between every pair of cities, thus, there are as many as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF773D/c0359cb82752ff2b028ccb729bac55ece58968d2.png) roads! No two roads intersect, and no road passes through intermediate cities. The art of building tunnels and bridges has been mastered by Neverians.

An independent committee has evaluated each road of Never with a positive integer called the perishability of the road. The lower the road's perishability is, the more pleasant it is to drive through this road.

It's the year of transport in Never. It has been decided to build a museum of transport in one of the cities, and to set a single signpost directing to some city (not necessarily the one with the museum) in each of the other cities. The signposts must satisfy the following important condition: if any Neverian living in a city without the museum starts travelling from that city following the directions of the signposts, then this person will eventually arrive in the city with the museum.

Neverians are incredibly positive-minded. If a Neverian travels by a route consisting of several roads, he considers the perishability of the route to be equal to the smallest perishability of all the roads in this route.

The government of Never has not yet decided where to build the museum, so they consider all $ n $ possible options. The most important is the sum of perishabilities of the routes to the museum city from all the other cities of Never, if the travelers strictly follow the directions of the signposts. The government of Never cares about their citizens, so they want to set the signposts in a way which minimizes this sum. Help them determine the minimum possible sum for all $ n $ possible options of the city where the museum can be built.

## 说明/提示

The first example is explained by the picture below. From left to right, there is the initial road network and the optimal directions of the signposts in case the museum is built in city 1, 2 and 3, respectively. The museum city is represented by a blue circle, the directions of the signposts are represented by green arrows.

For instance, if the museum is built in city 3, then the signpost in city 1 must be directed to city 3, while the signpost in city 2 must be directed to city 1. Then the route from city 1 to city 3 will have perishability 2, while the route from city 2 to city 3 will have perishability 1. The sum of perishabilities of these routes is 3.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF773D/5887985fd626a2ff9e975202ab209676c3725e09.png)

## 样例 #1

### 输入

```
3
1 2
3
```

### 输出

```
2
2
3
```

## 样例 #2

### 输入

```
6
2 9 9 6 6
7 1 9 10
9 2 5
4 10
8
```

### 输出

```
6
5
7
5
7
11
```

# 题解

## 作者：lsj2009 (赞：16)

## Description

给定一个 $n$ 个点的完全图 $\mathcal{G}(V,E)$，边带权。

我们定义其一个生成树 $\mathcal{T}(V'=V,E'\subseteq E)$ 的权值是：

1. 我们认为一个点 $u$ 的权值树上根到 $u$ 路径上边权的最小值。
2. 我们认为树 $\mathcal{T}$ 的权值是所有节点权值之和。

请对于每一个节点 $u\in V$ 求出所有**以他为根的生成树中权值的最小值**。

$1\le n\le 2000$。

## Solution

闲话：

这真的是 2700 吗？？？

机房三个人想了 1h+ 都没做出来，汗流浃背了/dk/dk/dk

（虽然可能当时想得差不多了，但是没有完全做出来就是了。）

### Observation 1

我们尝试观察最终树 $\mathcal{T}$ 的形态，通过直觉下面结论：

- 树 $\mathcal{T}$ 一定**形如一种「扫把」的形态**，也就是 **链 + 菊花**，大概如下：

![](https://s21.ax1x.com/2024/10/16/pAN5676.png)

约定：

1. 我们称下半部分为「**菊花**」。
2. 我们称菊花与链衔接的那条边（在上图中为 $(3,4)$）为「**把颈**」。
4. 在链上除去把颈的其于部分为「**把柄**」。

证明：

- 首先来证明**下半部分必然为菊花**：如果不为菊花，必然存在若干个儿子会继续向下拓展延申出去，我们**逐个考虑每个不合法的儿子**，进行调整；则对于每个儿子：
   - 如果下方延申出去的边存在某个小于我的「把颈」，那不妨令那条边成为我新的「把颈」，如下：
     - ![](https://s21.ax1x.com/2024/10/16/pAN5X9g.png)
     - 也就是 $w(5,8)<w(3,4)$。容易发现我这样调整权值必然不劣。
     - 如果我这个儿子下面是条链那就没了；否则如果下面也形如一棵多叉树那么我考虑逐层**从下往上归纳调整**即可。
   - 如果下方延申出去的边均大于我的「把颈」，那我将下面所有的点直接挂到「把颈」上即可。
     - 其实就是把上面的调整反一下，容易发现这样调整权值不变。  
- 再来考虑说明上半部分必然是一条链：
   - 我们考虑找出生成树 $\mathcal{T}$ 的最小边 $(u,v)$（设 $u$ 是 $v$ 父亲，其实也就是我们的「把颈」），然后取出其到根的路径 $\mathcal{P}=\text{root}\to u$ 和 $v$ 的子树 $\mathcal{T'}$，则我们将不在 $\mathcal{P}\cup\mathcal{T'}$ 上的点全部挂到「把颈」下即可：
     - ![](https://s21.ax1x.com/2024/10/16/pANIE34.png)
     - 其中 $\min{w}=w(3,4)$；容易发现这样操作权值必然不劣。
     - 此时虽然下半部分不满足是菊花图，但其实我们按照上面对于菊花图的处理进行调整即可。
 
这样子我们给出了证明：$\mathcal{T}$ 的形态必然是一个「扫把」。

### Observation 2

更进一步的，我们可以说明：**「把颈」必然是全局最小边**（如有多个则任意一个均可）。

反证：

- 设 $\min{w}=w(u,v)$。如果不是，则把颈为某条边 $(u',v')$，则考虑如下方案：
  - 我们考虑「把柄」部分不变，「菊花」部分连边：$(v',u),(u,v)$，这显然比我们将 $u,v$ 都挂在 $v'$ 下面优秀，然而这和我们前面说明的 **下部分必然是菊花图** 矛盾了。
  - 当然这里有一个特殊情况是：如果 $u/v$ 在「把柄」中出现过了咋办？？？这并不会有。因为你都在把柄中遇到 $\min{w}=w(u,v)$ 了，那让他成为「把颈」岂不会更优？？

### Observation 3

另一个结论：「把柄」部分除去最后一条边之外**从上往下权值单调不增**。

证明：

- 如果我们出现这样一种情况：
  - ![](https://s21.ax1x.com/2024/10/16/pANIyvj.png)
  - 同样考虑调整：
  - ![](https://s21.ax1x.com/2024/10/16/pANIgrn.png)
  - 因为我们注意到无论如何我们都有 $\Delta=\operatorname{value}(3)=\operatorname{value'}(5)=w(1,2)$ 对答案额外产生的贡献（显然期望情况下就是节点权值递减）（然而第二个等号其实也不一定成立，因为 $w(2,5)$ 的权值是 ？，也就是我们并不关心其具体权值，虽然其有可能小于 $w(1,2)$，但对我们证明没有影响），那我不妨直接令其于节点直接获得 $\min{w}$ 的权值，这陷入不劣！
- 注意还有一种特殊情况：我们无法保证 $w(2,5)<w(1,2)$！
  - 这也就是最开始说的，**除去最后一条边之外**从上往下权值单调不增。

### Full solution

根据 Observation 1~3 我们尝试推导出完整做法（设 $\min{w}=(u,v)$）：

1. 对于 $\text{root}=u/v$ 我们显然有 $\text{answer}=(n-1)\min{w}$。
2. 否则考虑从 $u/v$ 向上拓展到 $\text{root}$。具体的，考虑 Observation 1~2，观察「扫把」的形状，我们每次从「菊花」中拉出一个点 $x$ 让他成为 $\text{root}$，也就是在「把柄」的最上端加入一个点。
   - 考虑答案的变化：显然这时候 $x$ 不再对答案产生贡献，所以 $\text{answer}\gets \text{answer}-\min{w}$，但是注意到「把柄」上的点对答案贡献会产生变化：
     - 考察加入 $x$ 前的 $\text{root}=y$，则 $y$ 显然会新加贡献 $w(x,y)$。
     - 考虑 Observation 3，由于「把柄」上满足**从上往下权值单调不增**，所以 $w(x,y)$ 不会对其于「把柄」上的点权产生影响。
   - 所以 $\text{answer}$ 变化为：$\text{answer}\gets \text{answer}+(w(x,y)-\min{w})$。
3. 注意到我对 $\Delta\text{answer}$ 的写法了吗！我们考虑建新图 $\mathcal{G'}(V'=V,E'=\{(x,y,w(x,y)-\min{w})|(x,y)\in E\})$，对其跑关于 $u/v$ 的最短路即可！！！
   - 这种做法在几点上形成了惊人的自洽：
     - 注意到我们有 $w(x,y)\ge \min{w}$，所以在新图上边权非负，我们可以直接跑 Dijkstra！而根据 Dijkstra 的特性，**我们跑出来的图必然是一个 DAG（即最短路 DAG）**，所以从 $u/v\to x$ 的一条路径**必然是简单路径**，也就是「把柄」！
     - 我们有 $w'(u,v)=0$，所以无论是从 $u$ 还是 $v$ 开始跑都可以得到相同的结果！
4. 然而其实还有一个不太优雅的 corner case：
   - 我们的 Observation 3 有一个小 case：**除去最后一条边之外**从上往下权值单调不增。
   - 也就是其实「$w(x,y)$ 不会对其于「把柄」上的点权产生影响」不完全正确。
   - 处理是简单的，我们考虑「把柄」上倒数第二条边，他会对答案有**两次**的贡献，在初始化时设置即可，具体详见代码。

复杂度 $\mathcal{O}(n^2)$。

## Code

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(3,"Ofast","inline")
#define int long long
#define i128 __int128
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define ld double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
#define pcnt(x) __builtin_popcount(x)
#define lg(x) (31-__builtin_clz(x))
using namespace std;
void file_IO() {
//	system("fc .out .ans");
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
bool M1;
const int N=2e3+5;
int g[N][N],dis[N],n;
bool used[N];
void dijkstra(int st) {
	cl(dis,0x3f);
	rep(i,1,n) {
		dis[i]=g[st][i];
		rep(j,1,n)
			chkmin(dis[i],g[i][j]*2);
	}
	rep(_,1,n) {
		int k=0;
		rep(i,1,n) {
			if(!used[i]&&dis[i]<dis[k])
				k=i;
		}
		if(!k)
			continue;
		used[k]=true;
		rep(i,1,n) {
			if(!used[i]&&dis[i]>dis[k]+g[k][i])
				dis[i]=dis[k]+g[k][i];
		}
	}
}
void solve() {
	cl(g,0x3f);
	scanf("%lld",&n);
	int mn=INFLL,p=0;
	rep(i,1,n) {
		rep(j,i+1,n) {
			int x;
			scanf("%lld",&x);
			g[i][j]=g[j][i]=x;
			if(mn>x) {
				mn=x;
				p=i;
			}
		}
	}
	rep(i,1,n) {
		rep(j,1,n)
			g[i][j]-=mn;
	}
	dijkstra(p);
	rep(i,1,n)
		printf("%lld\n",dis[i]+(n-1)*mn);
}
bool M2;
signed main() {
	//file_IO();
	int testcase=1;
	//scanf("%d",&testcase);
	while(testcase--)
		solve();
	fprintf(stderr,"used time = %ldms\n",1000*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"used memory = %lldMB\n",(&M2-&M1)/1024/1024);
	return 0;
}
```

---

## 作者：ycyaw (赞：11)

简述一下题意：给出$n$个点的完全图，对于完全图中的每个点$i$，$i$作为终点时，要使其他每个点到点$i$的“距离”和最小，对于每个点都输出这个最小值。
这里的“距离”是指对于其他每个点，那个点到点$i$路径上的最小值。且对于每个点$i$，计算答案时应保证图内每条边的方向一定。（有点难解释，可以参考原文）

**题意很难表述清楚，建议看懂原题后再来看此题解。**

考虑对于每个终点$i$，最后连接所有点后图的形态，应该是一棵树接上一条链。如图：![](https://s2.ax1x.com/2019/04/30/E8iUmR.jpg)

------------
### 我会贪心&&搜索！
从终点开始倒搜，对于当前搜到的点$now$，每次找到未$vis$的且与$now$相连的边权最小的点，向那个点继续搜。

~~很显然这个想法是非常非常错误的，直接排除~~

------------
### 考虑优化贪心：
既然让每个点到终点路径上的最小边权和最小，那么很容易想到将所有点都连到边权最小的边的一端，再从这个点连向终点。$($下文我们将这个点称为“最小点”$)$

但这个还是错误的，如果连向终点的那条边权值特别大$(INF)$，那么答案就会非常劣。如图：![](https://s2.ax1x.com/2019/04/30/E8itX9.jpg)

那怎么办呢？我们就考虑让“最小点”去间接的连向终点，即从那些直接连向“最小点”的点中取一些出来，与“最小点”构成一条链，使这一条链加上那棵树的答案更优。我们称这条链$($起点为最小点,终点为$t$ $)$的答案为$dis[t]$。如图：![](https://s2.ax1x.com/2019/04/30/E8ia01.jpg)

怎么计算答案呢？我们设那条链上除终点外有$x$个点，那么那棵树上就有$n-1-x$个点，设最小边长度为$minn$，那么答案为$dis[t]+minn*(n-1-x)$。这个$x$很难计算，考虑消去。即计算$dis[t]$前先对所有边权减去一个$minn$，设新链答案为$dis'[t]$，那么答案会变成$(dis'[t]+minn*x)+minn*(n-1-x)$，即$dis'[t]+minn*(n-1)$，$x$就消去了。所以我们计算$dis'[t]$即可。

因为要求最优解，我们跑最短路求$dis$ $($定义见上$)$。一开始的状态是上面图2，即向终点直接连边，所以赋为终点与最小点的边权$($详见代码$)$。还有一种状态，即考虑那条链上有3个点。设加入的为点$j$，那么链的答案可能为最小点到终点的答案加上$j$到终点的答案，即$f[i][j]*2$ $($ $f$数组为邻接矩阵，$i$是终点 $)$。最后$dij$松弛即可$($模板$)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[3005][3005],vis[3005],dis[3005];
inline int read(){
	int ret=0,ff=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') ff=-1;ch=getchar();}
	while(isdigit(ch)){ret=(ret<<3)+(ret<<1)+(ch^48);ch=getchar();}
	return ret*ff;
}
inline void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+48);
}
void dij(int st){
	for(int i=1;i<=n;i++){
		dis[i]=f[st][i];
		for(int j=1;j<=n;j++)
			if(i!=j) dis[i]=min(dis[i],f[i][j]*2);
	}
	vis[st]=1;
	for(int i=1;i<=n-1;i++){
		int minn=2e9+1,k;
		for(int j=1;j<=n;j++)
			if(!vis[j]&&dis[j]<minn){
				minn=dis[j];
				k=j;
			}
		vis[k]=1;
		for(int j=1;j<=n;j++)
			if(!vis[j])
				dis[j]=min(dis[j],dis[k]+f[j][k]);
	}
}
int main(){
	int minn=2e9+1,k;
	n=read();
	for(int i=1;i<=n-1;i++)
		for(int j=1;j<=n-i;j++){
			f[i][i+j]=f[i+j][i]=read();
			if(f[i][i+j]<minn){
				minn=f[i][i+j];
				k=i;
			}
		}
	for(int i=1;i<=n-1;i++)
		for(int j=1;j<=n-i;j++){
			f[i][i+j]-=minn;
			f[i+j][i]=f[i][i+j];
		}		
	dij(k);
	for(int i=1;i<=n;i++) printf("%d ",dis[i]+minn*(n-1));
	return 0;
}
```



---

## 作者：应吟吟 (赞：5)

## 题目大意

- 附近有$n$个城市，城市两两之间都有双向的道路，道路的长度为$w$，某位旅行者的目的地是城市$s$，但是他不认路，所以他每到一个城市都会向那里的居民询问该往那里走才能到城市$s$，到一个城市的代价为所经过的道路的最小值，现在他想知道从任意一个城市出发到$s$的最小的代价和。他要去的城市$s$还没有定下来，所以请你求出对于所有的$s$的代价和。城市里的居民都很聪明，会对他指出使代价和最小的方案。

要部分分以及中文翻译的同学可以点开[这里](https://www.luogu.org/problemnew/show/U64505)

- ~~出题人太菜了不知道什么部分分的算法，所以数据随机，并且给了正确性较高的乱搞部分分。~~

- 如果有用乱搞得到高分的选手可以先上来分享一下做法

## 题目分析

###  我一开始的错误想法

​	很显然，这个路标连接起来之后是一棵树，对于每一个城市的贡献就是这个城市到终点城市$s$的路上的最小值。

​	然后我就有了一个~~非常睿智的~~想法：就是对于任意一个终点城市$s$，把所有的城市都连在最短边的一端，再由最短边直接连到终点城市$s$。

​	~~然后。。。这个东西显然是假的~~

### 正确的想法

​	不过我们可以考虑对它进行一些~~微$(jù)$小$(dà)$的~~修改让它成为正确的。

​	考虑这个想法的错误之处：在于最短边的一端到终点的距离可能很长，

​	所以我们考虑对这个进行计算

​	最短边的一边到终点城市的路径显然是一条链。

​	可以发现这条链如果是从终点城市开始递减的

​	那么答案就是这条链的长度

​	我们考虑把这个东西再转化一下

​	对于一个中间有边比之后的边要小的话，那么显然它之前的所有边直接连到最短边就好了。

​	那么这条最短边的贡献应该为两倍的权值

​	然后对于一个最短边的点到一个点的距离可以简化成本来存在的路或者是这个点连着一条边的两倍	

​	然后以最短边的点为起点跑最短路就好了

​	最后记得加上剩下的边数乘最短边

## 献上我的~~丑陋码风~~代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>


char gc()
{
    static char buf[1<<20],*p1=buf,*p2=buf;
    if(p1==p2)
    {
        p2=(p1=buf)+fread(buf,1,1<<20,stdin);
        if(p1==p2)return EOF;
    }
    return *p1++;
}

#define getchar gc

template<typename _Tp>
_Tp read(_Tp& x)
{
    x=0;
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x;
}


using namespace std;

long long n,s,ans,minn,a[5005][5005],dis[5005];
bool vis[5005];

inline void dijkstra(int s)
{
    memset(vis,0,sizeof(vis));
    memset(dis,0x7f,sizeof(dis));
    for(int i=1;i<=n;i++)
    {
        dis[i]=a[s][i];
        for(int j=1;j<=n;j++)
        {
            if(i!=j)dis[i]=min(dis[i],a[i][j]*2);
        }
    }
    vis[s]=1;
    for(int i=1;i<=n-1;i++)
    {
        long long minn=~(1LL<<63),v;
        for(int j=1;j<=n;j++)
        {
            if(!vis[j]&&dis[j]<minn)
            {
                minn=dis[j];v=j;
            }
        }
        vis[v]=true;
        for(int j=1;j<=n;j++)
        {
            if(!vis[j])
            {
                dis[j]=min(dis[j],dis[v]+a[v][j]);
            }
        }
    }
}

int main()
{
    read(n);
    minn=0x7fffffffffffffff;
    for(int i=1;i<=n-1;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            read(a[i][j]);
            a[j][i]=a[i][j];
            if(a[i][j]<minn)minn=a[i][j],s=i;
        }
    }
    for(int i=1;i<=n-1;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            a[i][j]-=minn;
            a[j][i]=a[i][j];
        }
    }
    dijkstra(s);
    for(int i=1;i<=n;i++)
    {
        printf("%lld ",dis[i]+minn*(n-1));
    }
}

```



---

## 作者：lgswdn_SA (赞：4)

主要是看了官方题解的思路……所以主要也是官方题解的思考步骤……

Observation 1：最终连成的一定是链。假设出现了 $a\to u$，$b\to u$ 的情况，假设 $a\to u$ 的代价更小，则我们连接 $b\to a$ 后 $b$ 走到 $u$ 的代价一定更小。

Observation 2：既然一定存在代价链上最小的边 $x$，则我们将每一条边的代价都减去 $x$，然后所有经过这条边的路径的代价就都是 $0$。

设 $w_i$ 表示反向链上第 $i$ 条边的代价。对于距离第一条零边 $>3$  的边，一定有 $w_i>w_{i+1}$。否则我们将第 $i+1$ 条边换成连向一个零边 $k$ 的出点的边，然后将 $i+2,i+3,...,k$ 全部反向后一定不差，甚至更优。

所以现在唯一出现决策的是 $w_{k-2}>w_{k-1}$ 或者 $w_{k-2}\le w_{k-1}$。对于 $w_{k-2}>w_{k-1}$，显然答案为它到 museum 的最短路；对于 $w_{k-2}\le w_{k-1}$，设边 $k-2$ 的出点为 $u$，答案为 $2w_{k-2}+dis_{u,t}$。（$t$ 为 museum）。

考虑建立超级源到每个点 $u$ 的距离为 $2\min a_{u,i}$。然后走最短路。最后要记得加上减去的 $(n-1)x$。

http://codeforces.com/contest/773/submission/112301043

---

## 作者：Schwarzkopf_Henkal (赞：3)

这个翻译比较有误导性，村民并不会根据不同的人指不同的路，如果是那样的话答案永远是 $w_{\min}\times (n-1)$。

首先容易发现，所有节点到终点的路径组成了一棵树。但是这个描述还不太准确，我们容易发现如果终点的度数大于 $1$ 总是会有更优的方案的，例如，我们总是可以把多出来的子树“移栽”到最短边的后面。

![CF773D-1](https://picgo-1302619124.file.myqcloud.com/C/CF773D-1.png)

也就是说，最后这形成了一条链+一棵树的形态，你可以在别的题解里看到这一说法；树的形态不重要，树的大小和链的形态/大小是重要的。

由于要每个终点往最小边上对的开销太大，我们考虑求出对于最小边接到每一个终点的链的贡献 $dis_i$。设链的大小（不包括终点，从最小边靠近终点的那端的节点算起）为 $x$，则 $ans_i=w_{\min}\times(n-1-x)+dis_i$。

有个 $x$ 很烦，我们希望消掉，如果所有边的权值都减掉一个特定的值 $val$，那么总的贡献一定减少了 $n\times val$。我们考虑让所有边的权值都减掉 $w_{min}$，最终的答案就变成了 $ans_i=w_{\min}\times(n-1)+dis_i$。考虑如何求这个 $dis_i$，首先初始值有两种情况，一是最小点直接连 $i$，值为 $f_{\min p,i}$，或者是经过两条边。这样能把最小点的贡献消掉。随后像真的 Dij 那样跑最短路就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,N,a[2005][2005],mn=2000000000,mnp,dis[2005],vis[2005];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			cin>>a[i][j];
			if(a[i][j]<mn){
				mn=a[i][j];
				mnp=i;
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			a[i][j]=a[j][i]=a[i][j]-mn;
	// for(int i=1;i<=n;i++)
	// 	a[i][i]=-mn;
	for(int i=1;i<=n;i++)
		dis[i]=a[mnp][i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(j!=i)
				dis[i]=min(dis[i],min(dis[j],a[j][i])+a[j][i]);
	dis[0]=2000000000;
	vis[mnp]=1;
	for(int FUCK=1;FUCK<n;FUCK++){
		int cur=0;
		for(int i=1;i<=n;i++)
			if(dis[i]<=dis[cur]&&!vis[i])
				cur=i;
		vis[cur]=1;
		for(int i=1;i<=n;i++)
			if(!vis[i])
				dis[i]=min(dis[i],dis[cur]+a[i][cur]);
	}
	for(int i=1;i<=n;i++)
		cout<<1ll*mn*(n-1)+dis[i]<<'\n';
}/*
*/
```



---

## 作者：Demeanor_Roy (赞：2)

- [原题链接](https://www.luogu.com.cn/problem/CF773D)。

------------

注意到给出的图是**完全图**，这对于这道题是一个很美的条件。基于此，对于任意一棵以 $T$ 为根的生成树，我们假设边 $(u,v)$ 是边权最小的边，点 $T$ 在 $u$ 这部分连通块，那么我们把除去 $T \rightarrow v$ 这条路径上剩余所有点全部接到 $v$ 上一定不劣。所以生成树的形态一定是一条链和一个菊花拼起来。

我们不妨把所有边边权减去全局最小值，问题转化为：把边权为全局最小值的边的端点称作关键点，对每个点求出一条到关键点的路径，使得边权前缀最小值之和最小。

依旧是利用图是**完全图**的性质，注意到如果该路径除去最后一条边的边权不严格递减，那么我们从破坏单调性的地方直接连向某个关键点一点不劣，故在特殊处理最后一条边的情况下，路径权值可以等价于所有边边权和。

于是倒过来跑最短路，额外加一维 $0/1$ 表示是否是第一条边即可。时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2010;
bool vis[N][2];
int n,mx=1e9,g[N],w[N][N];long long f[N][2];
int main()
{
	memset(f,127,sizeof f);
	memset(g,0x3f,sizeof g);
	scanf("%d",&n);
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			scanf("%d",&w[i][j]),w[j][i]=w[i][j],mx=min(mx,w[i][j]);
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++) 
		{
			w[i][j]-=mx;w[j][i]-=mx;
			if(!w[i][j]) f[i][1]=f[j][1]=0;
		}
	priority_queue<pair<long long,pair<int,bool>>> q;
	for(int i=1;i<=n;i++) if(!f[i][1]) 
		for(int j=1;j<=n;j++) g[j]=min(g[j],w[i][j]);
	for(int i=1;i<=n;i++) f[i][0]=0,q.push({0,{i,0}});
	while(q.size())
	{
		int u=q.top().second.first,st=q.top().second.second;q.pop();
		if(vis[u][st]) continue;vis[u][st]=true;
		for(int v=1;v<=n;v++)
		{
			if(u==v||vis[v][1]) continue;
			bool ex=false; 
			if(!st&&f[u][0]+w[u][v]+min(w[u][v],g[u])<f[v][1])
			{
				f[v][1]=f[u][0]+w[u][v]+min(w[u][v],g[u]);
				ex=true;
			}
			else if(st&&f[u][1]+w[u][v]<f[v][1])
			{
				f[v][1]=f[u][1]+w[u][v];
				ex=true;
			}
			if(ex) q.push({-f[v][1],{v,1}});
		}
	}
	for(int i=1;i<=n;i++)
	{
		long long c=1e18;
		for(int j=1;j<=n;j++) c=min(c,min(f[i][1],f[i][0]+g[i]));
		printf("%lld\n",c+1ll*mx*(n-1));
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：2)

首先找出权值最小的边。我们发现我们造出的树一定是一条链，到权值最小的边的一端，然后底下造个菊花图连接所有其他的点。

考虑反证，如果说这棵树不是一条链加上一个菊花图，取出一个链外、菊花图外的点，把他放到菊花图里面，这样他的贡献一定是边权最小的边，不劣于原方案。

同时我们发现，对于链上，至多有一组边满足前面小于后面。因为这样的话可以把这个点扔到菊花图里，仍然不劣。至于为什么有一组边可以有，这是到权值最小的边的一端时的特殊情况。

考虑反着做 $dp_i$ 表示到 $i$ 位置的链上点最小代价。考虑转移，有两种情况，一种是直接和一个其他的点连边，另一种是到一个其他的点再接过去。预处理出两种转移的最小值，跑个最短路式的 dp 即可。总复杂度 $O(n^2\log n)$。

```cpp
#pragma GCC optimize("Ofast","inline")
#include <bits/stdc++.h>
#define int long long 
#define mid ((l+r)>>1)
using namespace std;
int a[2005][2005],dp[2005],sur[2005],vis[2005];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int n; cin>>n;
	int minv=1e18;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			cin>>a[i][j];
			minv=min(minv,a[i][j]);
			a[j][i]=a[i][j];
		}
	}
	memset(dp,1,sizeof(dp));
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			if(a[i][j]==minv){
				dp[i]=dp[j]=0;
				pq.push(make_pair(0,i));
			}
			a[i][j]-=minv;
		}
	}
	for(int j=1;j<=n;j++){
		sur[j]=1e18;
		for(int i=1;i<=n;i++){
			if(i==j) continue;
			sur[j]=min(sur[j],a[i][j]); 
		}
		for(int i=1;i<=n;i++){
			a[i][j]=min(a[i][j],sur[j]*2);
		}
	}
	for(int i=1;i<=n;i++) if(dp[i]==0) pq.push(make_pair(0,i));
	while(!pq.empty()){
		int f=pq.top().second; pq.pop();
		if(vis[f]==1) continue; vis[f]=1;
		for(int i=1;i<=n;i++){
			if(dp[f]+a[f][i]<dp[i]){
				dp[i]=dp[f]+a[f][i];
				pq.push(make_pair(dp[i],i));
			}
		}
	}
	for(int i=1;i<=n;i++) cout<<dp[i]+minv*(n-1)<<"\n";
	return 0;
}
```

---

## 作者：MoonPie (赞：2)

## Solution - CF773D

[题目链接](https://codeforces.com/problemset/problem/773/D)

### 题意

一张 $n$ 个点的无向完全图.
有一个终点 $e$，需要你给每一点确定一个后继.
使按照规定的后继走，所有点到 $e$ 的路径上的最小边权的和最小
当 $e$ 取 $[1,n]$ 时，输出每次的答案.

### 题解

真是一道妙妙题，几个机智的观察让这道题变的非常容易.

---

#### 观察1：

首先我们会有一个十分 $naive$ 的贪心，

就是让其他所有点通过 **最小的边** 与 $e$ 相连，

这样的话所有的点的代价都是最小边的长度，一定是最优的.

但是这个生成树不一定造的出来，因为最小的边不一定与 $e$ 直接相连，

可以发现，此时的最优情况就是 **一条链 + 一棵树** .  且最小边在树、链的连接处.

我们记最小的边长度为 $min$ ，树上的点代价全部为 $min$ ，链上的点代价需要另外计算.

---

#### 观察2：

可以发现，一定可以构造出一种最优情况，使链上的点从与最小边相连的点 到 $e$ 是 **依次递增** .

这个结论可以用反证法证明：

如果链上有一条递减的边，那么把这条边放到链的起始位置答案肯定不劣，

因为前面较大的边并不会对链上的代价作出任何贡献.

由于链上的边权依次递增，每条边都只会作出一次贡献，相当于是一条 **路径**.

所以我们从与最小边相连的点 $s$ 出发跑一遍最短路就可以计算得到，

以所有点为终点的链上的最小代价.

---

让我们考虑一下如何计算答案，可以把答案分为两部分：树上的和链上的.

我们记链上一共有 $x$ 个点，与最小边相连的点是 $s$ ，终点为 $e$ ，那么：
$$
ans = (n-x-1)\times min+dis(s,e)
$$
考虑到这个 $x$ 是不确定的，所以很难 **在最后** 进行计算，

那么我们就可以考虑 **花费提前** 的思想，在计算 $dis$ 时，把 $-x\times min$ 一并算掉.

也就是把所有的边权全部减去 $min$ 后跑最短路.

---

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int N=2005;
int n,m=0,g[N][N],mi=1e18,sta,dis[N],vis[N];
bool checkmin(int &x,int y){return y<x?x=y,1:0;}
void dijstra()
{
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	vis[sta]=1;
	for(int i=1;i<=n;++i)
	{
		dis[i] = g[sta][i];
		for(int j=1;j<=n;++j) if(j!=i) checkmin(dis[i],g[i][j]*2); 
	}
	for(int i=1;i<n;++i)
	{
		int u=-1; for(int j=1;j<=n;++j) if(!vis[j] && (u==-1||dis[j]<dis[u])) u=j;
		vis[u]=1; for(int v=1;v<=n;++v) if(!vis[v]) checkmin(dis[v],dis[u]+g[u][v]);
	}
}
signed main()
{
	cin >> n;
	for(int x,i=1;i<=n-1;++i) for(int j=1;j<=n-i;++j) {
		scanf("%lld",&x);
		g[i][i+j]=g[i+j][i]=x; 
		if(checkmin(mi,g[i][i+j])) sta=i;
	}
    
	for(int i=1;i<=n;++i) for(int j=i+1;j<=n;++j) g[i][j]-=mi,g[j][i]-=mi;
	dijstra();
	for(int i=1;i<=n;++i) cout << (n-1)*mi + dis[i] << endl; 

	return 0;
}
```

---

## 作者：crpboy (赞：2)

**对于题意不懂的可以看看[ιχγббб巨佬的博客](https://www.luogu.org/blog/27858/solution-cf773d)**

基本思路是贪心+玄学最短路。

我们设一点为最终答案的终点，假设最终答案是一条链且其呈递增，即越靠近终点边的权值越大，那么每个点的答案也是递增的，且是这个情况下的最优解。

如果这条链的某一处出现了递减边，那么把这条边放到链的起始位置，答案肯定更优（由于链是递增，链的起始位置对应的边最小，再接一个较劣点对答案没有影响）。因此最后的答案一定满足是一条递增的链+一颗树。

设一条起点为最小点，终点为$i$的链的答案为$dis[i]$，由于这条链所接的树上节点个数很难统计，但最终答案和最短边的权值有关，我们可以考虑把所有的$dis$都减去最短边的距离，这样就消除了树对答案的影响。

接下来就开始乱搞了：由于递增链最优，我们用最短路求出最优链，并把没用的点无脑丢到树上。同时，考虑链上两点$i,s$，若以点$j$为中转站更优，答案就是$i,j$间距离的两倍。

总之这道题还是很玄学的，大家自行理解

记得开long long，以下为AC代码

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
#define dd ch=getchar()
inline int read()
{
    int x=0;bool f=false;char dd;
    while(!isdigit(ch)){f|=ch=='-';dd;}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;dd;}
    return f?-x:x;
}
#undef dd
inline void write(int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+48);
}
const int N=2005,INF=0x7fffffff;
int n,a[N][N];
struct node
{
    int w,id;
    inline friend bool operator <(const node x,const node y){return x.w>y.w;}
};
int d[N];
bool vis[N];
priority_queue<node>q;
inline void dijkstra(const int s)
{
    memset(d,0x3f,sizeof(d));
    memset(vis,false,sizeof(vis));vis[s]=true;
    for(int i=1;i<=n;i++)
    {
        d[i]=a[s][i];
        for(int j=1;j<=n;j++)
            if(i!=j)
                d[i]=min(d[i],a[i][j]<<1);
        q.push((node){d[i],i});
    }
    while(!q.empty())
    {
        int u=q.top().id;q.pop();
        if(vis[u])continue;
        vis[u]=true;
        for(int v=1;v<=n;v++)
        {
            if(v==u)continue;
            if(d[v]>d[u]+a[u][v])
                d[v]=d[u]+a[u][v],q.push((node){d[v],v});
        }
    }
}
signed main()
{
    n=read();
    for(int i=1;i<n;i++)
        for(int j=i+1;j<=n;j++)
            a[j][i]=a[i][j]=read();
    int minn=INF,s;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(a[i][j]<minn)
                minn=a[i][j],s=i;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            a[j][i]=a[i][j]=a[i][j]-minn;
    dijkstra(s);
    for(int i=1;i<=n;i++)
        write(d[i]+minn*(n-1)),putchar('\n');
    return 0;
}
```

---

## 作者：Genius_Star (赞：2)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18394307)
### 思路：

注意到答案应该是链加上一串贡献相同的树的贡献，因为若 $a \to u$ 的贡献 比 $b \to u$ 的贡献小，那么可以连 $b \to a$，答案会更优。

那么有一个贪心思路，对于每个根，找到连向这个根的最短边，然后对于这条边的另一个端点，也找到连向这个端点的最短边，以此类推；很显然，这个假了。

设 $T$ 为当前根，考虑找到全局最短边 $(u,v,w)$，考虑令 $u \to T$，然后其它所有点都连 $v$，这样其它点到 $T$ 的贡献必然是最小的，但是若 $u \to T$ 的贡献非常大，那这样也是不优的。

则考虑组成一个 $u \to T$ 的一条链，使得这条链的贡献加上其它所有点的贡献最优，设 $d_T$ 表示从 $u$ 到 $T$ 组成的链的贡献的最小值，$x$ 为 $u \to T$ 除 $T$ 以外的点的个数。

则贡献为 $d_T + (n-x-1) w$，发现这个 $x$ 很烦，考虑去掉，即我们计算 $d$ 的时候，对于全局边都减去一个 $w$，则 $d_T' = d_T - x \times w$ 了。

此时贡献为 $d_T + (n-1)w$，则我们要求出 $d_T$ 的最小值，发现是个单源最短路问题，直接跑 dijkstra 即可。

时间复杂度为 $O(N^2)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(register int i=l;i<=r;i++)
#define _For(i,l,r) for(register int i=r;i>=l;i--)
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=2020,INF=1e18;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,w,Min=INF,id;
ll a[N][N],d[N];
bool f[N];
void dijkstra(ll s){
	f[s]=1;
	For(i,1,n){
		d[i]=a[s][i];
		For(j,1,n){
			if(i==j)
			  continue;
			d[i]=min(d[i],a[i][j]*2);
		}
	}
	For(i,1,n-1){
		Min=INF,id=0;
		For(j,1,n){
			if(f[j])
			  continue;
			if(d[j]<Min){
				Min=d[j];
				id=j;
			}
		}
		f[id]=1;
		For(j,1,n){
			if(f[j])
			  continue;
			d[j]=min(d[j],d[id]+a[id][j]);
		}
	}
}
bool End;
int main(){
//	open("A.in","A.out");
	n=read();
	For(i,1,n){
	    For(j,i+1,n){
	    	a[i][j]=a[j][i]=read();
	    	if(a[i][j]<Min){
	    		Min=a[i][j];
	    		id=i;
			}
		}
	}
	For(i,1,n)
	  For(j,1,n)
		if(a[i][j])
		  a[i][j]-=Min;
	w=Min;
	dijkstra(id);
	For(i,1,n){
		write(d[i]+(n-1)*w);
		putchar('\n');
	}
	cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

## 作者：Ming_dao (赞：0)

今天模拟赛考到了。

答案用的 dijkstra。

考场上想到了一个另类做法，考后将其完善。但基本思路可以说是大差不差。

考虑到生成树会先是一条链走到最小权值的那条边上，然后就是一个大菊花。答案也会是 $d_{root,min}+(n-x+1)V_{min}$。会发现答案和最短路以及最短路途经的点的是数量有关，大胆设 dp 状态：令 $dp_{i,j,0/1}$ 表示  $i$ 途径 $j$ 个点走到权值最小的边对应的两个点所需的代价，转移方程就是 $dp_{i,j,0/1}=dp_{k,j-1,0/1}+val(i,k)$ 就可以转移了。

具体的 $val(i,k)$，因为我们是从子节点往根节点走的，所以如果当前边的权值 $w\times (j-1)<dp_{k,j-1,0/1}$ 就直接替换，否则将答案直接加 $w$。

预处理 $n^2$，计算答案 $n^2$。

---

## 作者：FAQmother (赞：0)

首先可以发现这个路标建出来是一颗树，对于每一个点的贡献是这个点到终点的路径上的最小值。然后有一个十分机智的想法就是对于所有终点，把所有点都连在最短的边的一端，然后另一端连向终点。

然后这个东西显然是假的

不过我们可以考虑对它进行一些微小的修改让它成为正确的。

考虑这个想法的错误之处在于最短边的一端到终点的距离可能很长，所以我们考虑对这个进行计算，最短边的一边到终点路径显然是一条链。可以发现这条链如果是从终点开始递减的那么答案就是这条链的长度。

我们考虑把这个东西再转化一下，对于一个中间有边比之后的边要小的话，那么显然它之前的所有边直接连到最短边就好了。那么这条最短边的贡献应该为两倍的权值。然后对于一个最短边的点到一个点的距离可以简化成本来存在的路或者是这个点连着一条边的两倍。

然后以最短边的点为起点跑最短路就好了，最后记得加上剩下的边数乘最短边。、
代码
```cpp
#include <bits/stdc++.h>

#define Max 3005
#define ll long long

using namespace std;

ll n,s,ans,minn,a[Max][Max],dis[Max];
bool vis[Max];

inline void dijkstra(int s){
	memset(vis,0,sizeof vis);
	memset(dis,0x7f,sizeof dis);
	for(int i=1;i<=n;i++){
		dis[i]=a[s][i];
		for(int j=1;j<=n;j++){
			if(i!=j)dis[i]=min(dis[i],a[i][j]*2);
		}
	}
	vis[s]=1;
	for(int i=1;i<=n-1;i++){
		ll minn=1e9,v;
		for(int j=1;j<=n;j++){
			if(!vis[j]&&dis[j]<minn){
				minn=dis[j];v=j;
			}
		}
		vis[v]=true;
		for(int j=1;j<=n;j++){
			if(!vis[j]){
				dis[j]=min(dis[j],dis[v]+a[v][j]);
			}
		}
	}
	return;
}

int main(){
//    freopen("233333.in","r",stdin);
//    freopen("233333.out","w",stdout);
	ios::sync_with_stdio(false);//读入优化
	cin>>n;
	minn=1e9;
	for(int i=1;i<=n-1;i++){
		for(int j=i+1;j<=n;j++){
			cin>>a[i][j];
			a[j][i]=a[i][j];
			if(a[i][j]<minn)minn=a[i][j],s=i;
		}
	}
	for(int i=1;i<=n-1;i++){
		for(int j=i+1;j<=n;j++){
			a[i][j]-=minn;
			a[j][i]=a[i][j];
		}
	}
	dijkstra(s);
	for(int i=1;i<=n;i++)cout<<dis[i]+minn*(n-1)<<" ";
	return 0;
}
```




---

