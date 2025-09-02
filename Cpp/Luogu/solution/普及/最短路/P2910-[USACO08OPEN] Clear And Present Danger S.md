# [USACO08OPEN] Clear And Present Danger S

## 题目描述

农夫约翰正驾驶一条小艇在牛勒比海上航行．

海上有 $N(1\leq N\leq 100)$ 个岛屿，用 $1$ 到 $N$ 编号．约翰从 $1$ 号小岛出发，最后到达 $N$ 号小岛．

一张藏宝图上说，如果他的路程上经过的小岛依次出现了  $A_1,A_2,\dots ,A_M(2\leq M\leq 10000)$ 这样的序列（不一定相邻），那他最终就能找到古老的宝藏． 但是，由于牛勒比海有海盗出没．约翰知道任意两个岛屿之间的航线上海盗出没的概率，他用一个危险指数 $D_{i,j}(0\leq D_{i,j}\leq 100000)$ 来描述．他希望他的寻宝活动经过的航线危险指数之和最小．那么，在找到宝藏的前提下，这个最小的危险指数是多少呢？

## 样例 #1

### 输入

```
3 4 
1 
2 
1 
3 
0 5 1 
5 0 2 
1 2 0 
```

### 输出

```
7 
```

# 题解

## 作者：扬皓2006 (赞：68)

此题是简单的图论题（不用建图！邻接表&&邻接矩阵都不用！）数据范围100显示此题可以用Floyd（n立方不会超时）

于是，我们就开始愉快地做题啦

先介绍一下Floyd的模板:
```
for(int k=1;k<=n;k++)//k相当于阶段，初学者容易写成i,j,k，要注意哦
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);//这是松弛操作（也是最短路算法的基础）
                //由三角形两边之和大于第三边可以推出
			}
		}
	}
```
我们可能会奇怪，这个Floyd看起来为什么这么熟悉呢？

没错，它就是个DP！

完整代码如下:
```
#include<bits/stdc++.h>//万能头
using namespace std;
int n,m,ans=0;//计数器
int dis[101][101],a[10001];//距离数组及必经之路数组
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&a[i]);//输入必经之路
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&dis[i][j]);//输入距离
		}
	}
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
			}
		}
	}//上文所提到的Floyd算法模板
	for(int i=2;i<=m;i++)
	{
		ans+=dis[a[i-1]][a[i]];//计数
	}
	printf("%d",ans);//输出计数器
	return 0;
}
```
如果已学会Floyd算法的同学，可以接着学习Dijkstra,Bellman-Ford以及SPFA算法，它们比FLoyd能适应的数据范围更大！

最后，希望管理大大能通过此篇题解！

---

## 作者：Nero_Claudius (赞：19)

说起来这还是本蒟蒻学完Floyd之后做的第一道题。

emm...这是一道裸题，题目大致是说有一堆岛，岛之间有海盗，因此每一条边都有一个危险指数（权重），然后给出一段必须经过的路线，求从一号小岛走到N号小岛最小的危险指数是多少。

先介绍一下Floyd算法吧：

 _Floyd（弗洛伊德）算法是用来求解带权图（无论正负）中的多源最短路问题。算法的原理是动态规划。_
 
_用dist(i,j,k)表示从顶点i到顶点j只经过前k个顶点的最短路的长度。那么只有如下两种情况:_

_1.i,j之间的最短路不经过k+1，dist(i,j,k+1)<-dist(i,j,k)_

_2.i,j之间的最短路经过k+1，dist(i,j,k+1)<-dist(i,k+1,k)+dist(k+1,j,k)。_

_所以dist(i,j,k+1)<-min{dist(i,j,k),dist(i,k+1,k)+dist(k+1,j,k)}。_

_在算法实现的时候可以省略掉k那一维，只需要用一个二维数组即可。_

                        _——《ACM国际大学生程序设计竞赛 知识与入门》_

AC代码见下。

其中dist为dp数组，order用于储存要求必须走的那一段路程。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 105;  
	
int n, m, ans = 0;
int dist[maxn][maxn];
int order[10010];
    
int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) cin >> order[i];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++) {
        	cin >> dist[i][j];
		}
        
	for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                
    for(int i = 2; i <= m; i++) ans += dist[order[i - 1]][order[i]];
    ans += dist[1][order[1]];
    ans += dist[order[m]][n];
        
    cout << ans;
}
```

---

## 作者：jimmyzzt (赞：12)

## 为啥各位都要用弗洛伊德
  居然只有一位大佬用dijkstra...这题没有负边权，多好的一个dijkstra变式题。。。
  
  然后我的脑回路比较清奇，三七二十一地一个一个点地求最短路然后加起来，可能是这个方法太弱智各位大佬都不想用，所以貌似没有这种题解。
  
  于是本蒟蒻斗胆写一篇
```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;

int g[101][101],n,m,dij,minn;
int list[10001],dis[101];
bool vis[101];

int dijkstra(int curr,int end)
{
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=n;i++) dis[i]=2e9;
	dis[curr]=0;
	while(!vis[end])
	{
		vis[curr]=true;
		for(int i=1;i<=n;i++)
		{
			if(vis[i]) continue;
			if(dis[curr]+g[curr][i]>=dis[i]) continue;
			dis[i]=dis[curr]+g[curr][i];
		}
		minn=2e9;
		for(int i=1;i<=n;i++)
		{
			if(vis[i]) continue;
			if(minn>=dis[i])
			{
				minn=dis[i];
				curr=i;
			}
		}
	}
	return dis[end];
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d",&list[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&g[i][j]);
	for(int i=1;i<m;i++)
		dij+=dijkstra(list[i],list[i+1]);
	printf("%d",dij);
	return 0;
}
```

# 各位大佬看到错的务必指正啊QAQ

---

## 作者：littlesnake (赞：7)

### 前言

刚学习了 Floyd 算法，就想来写个题解，如果题解没有通过的话，就当作个人笔记好了。

我看题解区第一篇题解就只是简单讲了一下，又贴了个代码。我将在此题解中使用 2 种算法求解，比较它们的时间复杂度、空间复杂度，以及它们的耗时。并且讲解 Floyd 算法的原理。

### 分析

这道题是一个最短路题，但是它与其它题目不同之处在于它需要处理从不同点出发的最短路径，也就是**多源最短路径**。点的数量较少，但是任意两点之间都有连边（边的数量约为 $O(n^2)$ 级别）。最简单的方法是采用 $n$ 遍 Dijkstra 算法求最短路，其时间复杂度为 $O(n^3)$，已经足够通过本题。

代码如下：

```cpp
#include <bits/stdc++.h>
#define MAXN 105
#define MAXM 10005
#define inf 2147483647
using namespace std;
// 有点混乱，d 数组是 Dijkstra 用的
int n, m, ans, a[MAXM], dis[MAXN][MAXN], d[MAXN];
bool vis[MAXN];
// 裸的 Dijkstra
int Dijkstra(int b, int e) {
	memset(vis, 0, sizeof(vis)); // 需要初始化
	for(int i = 1; i <= n; i++) d[i] = inf;
	d[b] = 0;
	while(!vis[e]) {
		vis[b] = 1;
		for(int i = 1; i <= n; i++) {
			if(vis[i]) continue;
			if(d[b] + dis[b][i] < d[i]) 
				d[i] = d[b] + dis[b][i];
		}
		int minn = inf;
		for(int i = 1; i <= n; i++) {
			if(vis[i]) continue;
			if(d[i] < minn) {
				minn = d[i];
				b = i;
			}
		}
	}
	return d[e];
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= m; i++) cin >> a[i];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			cin >> dis[i][j];
	for(int i = 1; i < m; i++)
		ans += Dijkstra(a[i], a[i + 1]);
	cout << ans;
	return 0;
}

```

耗时 517ms。

---

但事实上，对于多源最短路，可以使用 **Floyd-Warshall** 算法（简称 Floyd 算法）更便捷地解决此类问题。

采用动态规划的思路，设 $dis_{i,j,k}$ 表示当只途径编号为 $1$ 到 $k$ 的点时（起始点和终点不算），$i$ 到 $j$ 的最短路的长度。特别地，$dis_{i,j,0}$ 代表初始时 $i$、$j$ 点间的边的边权。

考虑如何进行状态更新，显然从 $i$ 到 $j$ 且只经过编号为 $1$ 到 $k$ 的点的路径分为两类：

1. 从 $i$ 到 $j$，且只经过编号为 $1$ 到 $k - 1$ 的路径；

2. 从 $i$ 到 $k$，再从 $k$ 到 $j$，且只经过编号为 $1$ 到 $k$ 的点的路径。

显然对于第一类路径，最短者的长度就是 $dis_{i,j,k - 1}$。对于第二类路径，最短者的长度就是 $dis_{i,k,k - 1} + dis_{k,j,k - 1}$。两者当中取最小值，就得到转移方程：

$dis_{i,j,k} = \min (dis_{i,j,k - 1},dis_{i,k,k - 1} + dis_{k,j,k - 1})$

然后只需要依次枚举 $k,i,j$，并进行转移即可。最终结果为第三维为 $n$ 的数组。注意由于再第三维为 $k$ 的时候需要用到第三维为 $k - 1$ 的数据，所以在枚举是应当先枚举第三维 $k$，再枚举 $i$ 和 $j$。

代码非常简短，如下所示：

```cpp
for(int k = 1; k <= n; k++)
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			dis[i][j][k] = min(dis[i][j][k - 1], dis[i][k][k - 1] + dis[k][j][k - 1]);
```

时间复杂度 $O(n^3)$，空间复杂度 $O(n^3)$。在时间上已经难以对该算法进行优化，但在空间上可以。

显然 $dis_{i,k,k - 1}$ 与 $dis_{i,k,k}$、$dis_{k,j,k - 1}$ 与 $dis_{k,j,k}$ 分别都相等，所以我们可以发现数组第三维 $k$ 是多余的，可以直接使用二维数组来解决本题。这种优化方式叫做滚动优化，在动态规划算法里经常使用。转移方程则变为：

$dis_{i,j} = \min (dis_{i,j},dis_{i,k} + dis_{k,j})$

空间复杂度变为 $O(n^2)$，时间复杂度不变。最终代码如下：

```cpp
#include <bits/stdc++.h>
#define MAXN 105
#define MAXM 10005
using namespace std;
int n, m, a[MAXM], dis[MAXN][MAXN];
int main() {
	cin >> n >> m;
	for(int i = 1; i <= m; i++) cin >> a[i];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			cin >> dis[i][j];
	for(int k = 1; k <= n; k++)
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				dis[i][j] = min((long long)dis[i][j], (long long)dis[i][k] + dis[k][j]);
	int ans = 0;
	for(int i = 1; i <= m - 1; i++)
		ans += dis[a[i]][a[i + 1]];
	cout << ans;
	return 0;
}

```

耗时 41ms。

可以证明，当存在负权边时 Floyd 算法正确性可以保证。Floyd 算法既可以处理无向图，也可以处理有向图，注意设置 dis 的初始值即可。

但是为什么 Floyd 算法和 Dijkstra 算法运行的时间相差这么多呢？

因为 Dijkstra 是单源最短路径算法，而 Floyd 是多源最短路径算法。

### 小结

> 每种算法都有自己擅长的方面，没有最好的算法，只有适合的题目。

---

## 作者：__dper__ (赞：4)

这题蛮水的，直接跑一边floyd-warshall，然后按着给的路线前进就好了

注意从1开始，到N结束

             
             
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[10001],d[101][101],ans;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
      {
       scanf("%d",&a[i]);
     }
    for(int i=1;i<=n;i++)
    {
       for(int j=1;j<=n;j++)
       {
          scanf("%d",&d[i][j]);
       }
    }
    for(int k=1;k<=n;k++)
       for(int i=1;i<=n;i++)
          for(int j=1;j<=n;j++)
             d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
    for(int i=2;i<=m;i++)ans+=d[a[i-1]][a[i]];
    ans+=d[1][a[1]];ans+=d[a[m]][n];
    printf("%d",ans);
    return 0;
}
```

---

## 作者：dan_daning_L (赞：4)

## 这里是蒟蒻发的第一篇Floyed蒟蒻题解
### 这是一道纯Floyed题，所以一定会被Dijkstra和SPFA的大佬~~骂死~~虐得很惨
  因为Floyed最短路算法~~连我这样的蒟蒻都能~~较好理解，所以是萌新必备，但时间复杂度较大O（N^3），所以不如其他方法运用广泛。
  
####   本题解法
首先利用Floyed算法计算出每两座岛之间的最小伤害（最短路），之后将相邻每两个目的地岛屿的最短路相加即是最终答案。 
#### 献上来自蒟蒻的~~双膝~~代码
```cpp
#include <bits/stdc++.h>    //懒人必备 
using namespace std;
int main()
{
	long long f[101][101],a[10001],n,m,i,k,j,ans=0;
	cin>>n>>m;              //本人才学会的输入 
	for (i=1;i<=m;i++)       
	cin>>a[i];
	for (i=1;i<=n;i++)
	 for (j=1;j<=n;j++)
	 cin>>f[i][j];
	for (k=1;k<=n;k++)      //本人才学会的Floyed 
	 for (i=1;i<=n;i++)
	  for (j=1;j<=n;j++)
	    if (f[i][j]>f[i][k]+f[k][j]) 
	     f[i][j]=f[i][k]+f[k][j]; //if以k点为中继点i到j的距离小于i到j的直线距离，则交换    
	for (i=1;i<m;i++) 
	 ans+=f[a[i]][a[i+1]];  //累加相邻2个目的地的最短路径 
	cout<<ans;              //本人才学会的输出 
return 0;	
}
```
Floyed详见一本通 or [这里](https://blog.csdn.net/qq_35644234/article/details/60875818)

---

## 作者：zumgze (赞：2)

这是一道图论题（甚至还是完全图），危险度就相当于边权（甚至输入数据就是邻接矩阵），最小危险度就是最短距离
### 那么，就来到了最短路算法 n次dj/floyd（这里是dj）
发现其他题解基本都是floyd，剩下用了dj的也没有用优先队列优化dj的
用优先队列优化dj就是用优先队列的pop来代替每次遍历邻接矩阵找最短边，可以把n^2的复杂度优化到n*log（n）
```cpp
#include<iostream>
#include<queue>
using namespace std;
int a[100][100];
int ans[10000];
struct node//用于dj中的优先队列 
{
	int no,dis;
	node(int a,int b)
	{
		no=a;
		dis=b;
	}
};
bool operator<(node a,node b)
{
	return a.dis>b.dis;
}
bool operator>(node a,node b)
{
	return a.dis<b.dis;
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++)cin>>ans[i];//储存需要依次经过的点 
	for(int i=0;i<n;i++)//读入，初始化图 
		for(int j=0;j<n;j++)
			cin>>a[i][j];
	for(int i=0;i<n;i++)//每次计算i到其他各个点的最短路 
	{
		priority_queue<node> q;
		bool b[100];//判断一个点是否已经使用过 
		for(int j=0;j<n;j++)//把从i出发的每个点及其距离入队列 
			if(i==j)b[j]=false;
			else
			{
				b[j]=true;
				q.push(node(j,a[i][j]));
			}
		for(int j=0;j<n-1;j++)
		{			
			while(!b[q.top().no])q.pop();
			node now=q.top(); 
			b[now.no]=false;//标记 
			a[i][now.no]=now.dis;//更新图 
			for(int k=0;k<n;k++)//把从i出发途径now（当前位置）的每个点及其距离入队列 
				q.push(node(k,now.dis+a[now.no][k]));
		}
	}//现在a[i][j]就是i到j的最短距离了 
	long long kotae=0;
	for(int i=1;i<m;i++)//依次累加需要经过的点之间的距离 
		kotae+=a[ans[i-1]-1][ans[i]-1];
	cout<<kotae;
	return 0;
}
```

---

## 作者：绿绵羊 (赞：2)

这道题要用的是**floyd**算法，当然，**多做几次dijkstra算法用来打表也是可以的**。
### **floyd**算法的精髓是：利用枚举一个点，使其优化其他两点距离，从而找到最短路。
floyd是O（n^3）算法，所以用在这道题上的时间复杂度还是很可观的。
```cpp
#include <bits/stdc++.h>
using namespace std;
long long GA[111][111], r[11111];
int main()
{
	long long n, m, i, j, c, t=0;
	cin >> n >> m;
	for (i=1; i<=m; i++) cin >> r[i];
	for (i=1; i<=n; i++)
		for (j=1; j<=n; j++) cin >> GA[i][j];
	for (c=1; c<=n; c++) //枚举中间优化点 
		for (i=1; i<=n; i++) //枚举起始点 
			for (j=1; j<=n; j++) //枚举终止点 
				if (GA[i][c]+GA[c][j]<GA[i][j]) GA[i][j]=GA[i][c]+GA[c][j]; //如果可以优化，那就更改数值 
	for (i=2; i<=m; i++) t+=GA[r[i-1]][r[i]]; //按照邻接矩阵里的数据输出 
	cout << t << endl;
	return 0;
}
```
借用一下自己曾说过的话为大家解释一下为什么floyd好：

用floyd的原因是floyd是多源最短路径算法，而且代码量小，代码难度小，思维难度也更小，而dijkstra是单源最短路径算法，套上循环后时间复杂度在这道题上和dijkstra几乎一样，所以被人嫌弃了。

当然，如果这道题把M变成2，那么dijkstra就是更好的选择了。

---

## 作者：天下至菜 (赞：1)

显然是一道最短路题

题意大概就是按照他给的顺序走一遍就可以了？

先处理好所有点之间的距离就好了
```
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,k) for(ll i=j;i<=k;i++)//缩写for循环
#define F2(i,j,k) for(ll i=j;i>=k;i--)
using namespace std;
ll read(){//快读
	ll f=1,sum=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){sum=(sum<<1)+(sum<<3)+(ch^48);ch=getchar();}
	return f*sum;
}
ll n,m,f[105][105],to[10005],ans;
int main(){
	n=read();m=read();
	F(i,1,m)to[i]=read();
	F(i,1,n)F(j,1,n)f[i][j]=read();
	F(k,1,n)F(i,1,n)F(j,1,n)f[i][j]=min(f[i][j],f[i][k]+f[k][j]);//处理各个点之间的距离
	F(i,1,m-1){ans+=f[to[i]][to[i+1]];}//注意，一定要加到m-1
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：rain_forest (赞：1)

这道题显而易见是一道Floyd模板题，从Floyd的基本思想我们可以发现Floyd就是DP，那么我们不仅仅可以用二维数组，还可以用三维数组解决。

Floyd的基本思想就是~~绕路~~依靠中转站取最小值，那么我们考虑前p个中转站，``Map[p][i][j]``表示在第k个中转站时，i到j的最短距离，那么显而易见``Map[p][i][j]=min(Map[p-1][i][j],Map[p-1][i][p]+Map[p-1][p][j])``

代码奉上：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[10001],Map[101][101][101];
long long ans;
inline int min(const int &a,const int &b)
{
	return a<b?a:b;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=m;++i)
		scanf("%d",a+i);
	memset(Map,0x3f,sizeof(Map));
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=n;++j)
			scanf("%d",Map[0][i]+j);
	for(register int p=1;p<=n;++p)
		for(register int i=1;i<=n;++i)
			for(register int j=1;j<=n;++j)
				Map[p][i][j]=min(Map[p-1][i][j],Map[p-1][i][p]+Map[p-1][p][j]);
	for(register int i=2;i<=m;++i)
		ans+=Map[n][a[i-1]][a[i]];
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：蛟川洋 (赞：0)

本蒟蒻一看就会了，这题真心不难，代码附上，详见代码：

```cpp
program P2910;
var
        d:array[1..100,1..100] of longint;//用于储存危险值
        a:array[1..10000] of longint;
        n,m,s,i,i1:longint;
procedure floyd;//图论最短路Floyd算法
var t,i,i1,i2:longint;
begin
for i:=1 to n do
 for i1:=1 to n do
  for i2:=1 to n do
   begin
   t:=d[i1,i]+d[i,i2];
   if d[i1,i2]>t then d[i1,i2]:=t;
   end;
end;
begin
        readln(n,m);
        for i:=1 to m do
         begin
         readln(a[i]);//读入要求路线
         end;
        for i:=1 to n do
         begin
         for i1:=1 to n do
          begin
          read(d[i,i1]);//读入危险值
          end;
         readln;
         end;
        floyd;//调用最短路过程
        for i:=2 to m do//按照要求路线循环
         begin
         inc(s,d[a[i-1],a[i]]);//；累加路线和
         end;
        writeln(s);//输出路径和
end.
```

---

## 作者：Mogician (赞：0)

#pascal版题解

思路很简单，用floyd算法算出每个点之间的最短路，再按着地图走一遍累加答案即可

```cpp
var f:array[1..100,1..100] of longint;
    a:array[0..10000] of longint;
    i,j,k,t,m,n,p:longint;
begin
 assign(input,'233.in');
 reset(input);//关联文件便于调试
 for i:=1 to 100 do for j:=1 to 100 do f[i,j]:=maxlongint>>2;//初始化
 readln(n,m);
 for i:=1 to m do readln(a[i]);
 for i:=1 to n do for j:=1 to n do read(f[i,j]);
 for k:=1 to n do
  for i:=1 to n do
   for j:=1 to n do
    if f[i,j]>f[i,k]+f[k,j] then f[i,j]:=f[i,k]+f[k,j];//floyd算法
 a[0]:=1;
 for i:=1 to m do inc(t,f[a[i-1],a[i]]);//累加答案
 writeln(t);
end.
```

---

## 作者：hyoi_ctime (赞：0)

首先可以看出这是一个有向图（我是这么认为的），这个题的输入把每一个危险值都给了，所以就不需要初始化f数组了；跑一遍floyd；求出各个岛屿之间的最小危险值，然后就根据题目所要求的路径按照最小危险值走。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
const int maxn=100+5;
int n,m;
int a[10001],f[100][100];
inline void read()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)scanf("%d",&f[i][j]);
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
            }
    int ans=0,t=1;
    for(int i=1;i<=m;i++)
    {
        ans+=f[t][a[i]];
        t=a[i];//t为当前所处位置，每走一次就更新一次。
    }
    printf("%d",ans);
}
int main()
{
    read();
    return 0; 
}
```

---

## 作者：睿屿青衫 (赞：0)

#题解好少，我来一发C++的弗洛伊德

#提交前发现答案错了，想了想又改了回来，可能有人也会这样错，在这里说一下错的思路

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define maxn 300000
using namespace std;
int n,m,a[maxn],dis[110][110],tot=0;
int main()
{
    ios::sync_with_stdio(false);//cin快读
    cin>>n>>m;
    for(int i=1;i<=m;++i)
    {
        cin>>a[i];//记录必须经过的路径
    }
    memset(dis,999999,sizeof(dis));//初始化一个大值，后面进行择优
    for(int i=1;i<=n;++i)
    {
        for(int x,j=1;j<=n;++j)
        {
            cin>>x;
            dis[i][j]=x;
        }
    }
    for(int k=1;k<=n;++k)
     for(int i=1;i<=n;++i)
      for(int j=1;j<=n;++j)
       if(dis[i][j]>dis[i][k]+dis[k][j])
        dis[i][j]=dis[i][k]+dis[k][j];//弗洛伊德就这样写，k做中介，实在不明白背过
    tot=dis[1][a[1]];//sum记录步数，第一个必经点是要从1来的
    for(int i=2;i<=m;++i)//1已经确定了，从2更新
    {
        tot+=dis[a[i-1]][a[i]];//每次从前面那个点到现在这个点最短路，更新答案
    }
    printf("%d",tot);
    return 0;
}
```

---

