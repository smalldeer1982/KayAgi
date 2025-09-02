# [USACO09JAN] Best Spot S

## 题目描述

Bessie, always wishing to optimize her life, has realized that she really enjoys visiting F (1 <= F <= P) favorite pastures F\_i of the P (1 <= P <= 500; 1 <= F\_i <= P) total pastures (conveniently

numbered 1..P) that compose Farmer John's holdings.

Bessie knows that she can navigate the C (1 <= C <= 8,000) bidirectional cowpaths (conveniently numbered 1..C) that connect various pastures to travel to any pasture on the entire farm. Associated with each path P\_i is a time T\_i (1 <= T\_i <= 892) to traverse that path (in either direction) and two path endpoints a\_i and b\_i (1 <= a\_i <= P; 1 <= b\_i <= P).

Bessie wants to find the number of the best pasture to sleep in so that when she awakes, the average time to travel to any of her F favorite pastures is minimized.

By way of example, consider a farm laid out as the map below shows, where \*'d pasture numbers are favorites. The bracketed numbers are times to traverse the cowpaths.

```cpp

            1*--[4]--2--[2]--3
                     |       |
                    [3]     [4]
                     |       |
                     4--[3]--5--[1]---6---[6]---7--[7]--8*
                     |       |        |         |
                    [3]     [2]      [1]       [3]
                     |       |        |         |
                    13*      9--[3]--10*--[1]--11*--[3]--12*
```
The following table shows distances for potential 'best place' of pastures 4, 5, 6, 7, 9, 10, 11, and 12:

```cpp
      * * * * * * Favorites * * * * * *
 Potential      Pasture Pasture Pasture Pasture Pasture Pasture     Average
Best Pasture       1       8      10      11      12      13        Distance
------------      --      --      --      --      --      --      -----------
    4              7      16       5       6       9       3      46/6 = 7.67
    5             10      13       2       3       6       6      40/6 = 6.67
    6             11      12       1       2       5       7      38/6 = 6.33
    7             16       7       4       3       6      12      48/6 = 8.00
    9             12      14       3       4       7       8      48/6 = 8.00
   10             12      11       0       1       4       8      36/6 = 6.00 ** BEST
   11             13      10       1       0       3       9      36/6 = 6.00
   12             16      13       4       3       0      12      48/6 = 8.00

```
Thus, presuming these choices were the best ones (a program would have to check all of them somehow), the best place to sleep is pasture 10.

约翰拥有 $P(1 \leq P \leq 500)$ 个牧场，贝茜特别喜欢其中的 $F$ 个。所有的牧场由 $C(1 < C \leq 8000)$条双向路连接，第 $i$ 条路连接着 $a_i,b_i$，需要 $T_i(1 \leq T_i < 892)$ 个单位时间来通过。

作为一只总想优化自己生活方式的奶牛，贝茜喜欢自己某一天醒来，到达所有那 $F$ 个她喜欢的牧场的平均需时最小。那她前一天应该睡在哪个牧场呢？请帮助贝茜找到这个最佳牧场。

由样例解释可见，在样例环境下，牧场 $10$ 到所有贝茜喜欢的牧场的平均距离最小，为最佳牧场。


## 说明/提示

As the problem statement


As the problem statement.


## 样例 #1

### 输入

```
13 6 15 
11 
13 
10 
12 
8 
1 
2 4 3 
7 11 3 
10 11 1 
4 13 3 
9 10 3 
2 3 2 
3 5 4 
5 9 2 
6 7 6 
5 6 1 
1 2 4 
4 5 3 
11 12 3 
6 10 1 
7 8 7 
```

### 输出

```
10 
```

# 题解

## 作者：Cxs3 (赞：30)

题目链接：https://www.luogu.org/problemnew/show/P2935  
这题的题解好少呢，我也发布一篇吧

---

## 题目分析
题目要求哪个点与$F$个点的距离（即题面中的时间）和最小，就得求出**每个点分别到这$F$的点的最小距离**，可用 且 只能用$Floyd$.  

步骤：  
$1.$跑一遍$Floyd$；  
$2.$枚举每个点，算出距离总和，同时找距离和最小的一个点记录下标；  
$3.$输出这个下标即可。

时间复杂度$O(n^3)$.  
~~也快不到哪里去了QAQ~~

---

## 代码实现
这次就放完整代码了qwq：
```cpp
#include<bits/stdc++.h>
const int inf=0x3fffffff;
using namespace std;
int n,m,p,like[501];//n个点，m条边，p个喜欢的点（因为本人习惯，与题目中有所不同）
int ans,mi=inf,f[501][501];
int main()
{
	int i,j,k,u,v,c,sum;
	cin>>n>>p>>m;
	for(i=1;i<=n;i++)//初始化
	{
	  for(j=1;j<=n;j++) f[i][j]=inf;
	  f[i][i]=0;//点i到点i的最小距离为0
	}
	for(i=1;i<=p;i++) cin>>like[i];
	for(i=1;i<=m;i++)
	{
	  cin>>u>>v>>c;
	  f[u][v]=c;//采用类似邻接矩阵的方式读入
	  f[v][u]=c;
	}
	for(k=1;k<=n;k++)
	  for(i=1;i<=n;i++)
	    for(j=1;j<=n;j++)
	      f[i][j]=min(f[i][j],f[i][k]+f[k][j]);//DP动态转移方程
	for(i=1;i<=n;i++)
	{
	  sum=0;
	  for(j=1;j<=p;j++) sum+=f[i][like[j]];//累加距离和
	  if(sum<mi){mi=sum; ans=i;}//更新答案
	}
	cout<<ans<<endl;
	return 0;
}
```

---

愿我的题解能帮到大家，毕竟我只是个蒟蒻qwq

---

## 作者：zhaoyp (赞：10)

其实这题基本上就是 floyd 的模板题。

既然是模板题就有必要讲讲什么是 floyd ？

------------

##  什么是  floyd ？
- 思想：动态规划。
- $f_{k,i,j}$ 表示可经过 $1 \cdots k$号节点，$i$ 到 $j$ 的最短路。
- $f_{0,i,j}$ 表示初始权值（没有道路连通时为INF）。

不难发现，当 $k$ 每增加一后，$i$ 到 $j$ 的最短路是否会改变取决于 $i$ 到 $k$  再到 $j$ 的最短路（ $k$ 每增加一后，只多出一个节点可以行走）。

得到状态转移方程：$f_{k,i,j} = \min(f_{k-1,i,j},f_{0,i,k}+f_{0,k,j})$。

由于第 $k$ 层的数据都由第 $k-1$ 层和第 $0$ 层推导而来，所以可以用滚动数组滚掉一维。
- 时间复杂度$O(n^3)$，空间复杂度$O(n^2)$，$n$为结点数。
- 适用于多源最短路问题。

code：
```cpp
for(int k = 1;k <= p;++k)
		for(int i = 1;i <= p;++i)
			for(int j = 1;j <= p;++j)
				f[i][j] = min(f[i][j],f[i][k]+f[k][j]);
```
**注意三个循环顺序，小心翻车。**

## 题目分析

就是求所有牧场到喜欢的牧场的最短路。

多源最短路问题，适用 floyd。

### 具体步骤

1. 对整张图跑一遍 floyd ；
1. 遍历所有牧场，求出它们与喜欢的牧场的最短路之和，和最小的一个牧场即为答案。

### code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int p,f,c,x,y,t,cnt,ans=0x3fffffff,sum,a[505],floyd[505][505];
void inp()//数据输入与初始化操作 
{
	scanf("%d%d%d",&p,&f,&c);
	memset(floyd,0x3f3f3f3f,sizeof(floyd));//初始时赋inf 
	for(int i = 1;i <= p;++i)
		floyd[i][i] = 0;//一个点到自己的最短路为0 
	for(int i = 1;i <= f;++i)
		scanf("%d",&a[i]);
	for(int i = 1;i <= c;++i)
		scanf("%d%d%d",&x,&y,&t),floyd[x][y] = t,floyd[y][x] = t;//无向图记得反向存边 
}
void DP_floyd()//floyd最短路 
{
	for(int k = 1;k <= p;++k)
		for(int i = 1;i <= p;++i)
			for(int j = 1;j <= p;++j)
				floyd[i][j] = min(floyd[i][j],floyd[i][k]+floyd[k][j]);//DP状态转移方程 
}
void check()//遍历所有牧场 
{
	for(int i = 1;i <= p;++i)
	{
		sum = 0;
		for(int j = 1;j <= f;++j)
			sum += floyd[i][a[j]];
		if(sum < ans)	ans = sum,cnt = i;//注意如果最好的牧场多于一个，则选择最小的牧场。所以不能用 <= 
	}		
	printf("%d",cnt);	
}
int main()
{
	inp();
	DP_floyd();
	check();
}
```


---

## 作者：Caicz (赞：5)

## 这是一道floyd算法的模板题

**先说说题意**

本题是求出到所给的点的平均距离的最小的点

看一看数据 n<=300,那么就可以放心的用 floyd 了

由于本题是无向图，在输入时,f[ a ][ b ] = f[ b ][ a ];

下面就直接看代码
```c
#include<bits/stdc++.h>
using namespace std;
int g[505],f[505][505];
int T,n,m,sum,ans=999999999,p;
```
### ans赋极大值！！！！
###### ~~就是因为没赋极大值才挂了~~
**sum用于储存对于每一个点到所要求的的点的最小值和；ans之前点的最小值，p记录每次能更新ans时的最小值**
```c
int main()
{
	cin>>n>>T>>m;
	memset(f,0x3f,sizeof(f)); 
	for(int i=1;i<=T;i++)
		scanf("%d",&g[i]);
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		f[a][b]=f[b][a]=c;
	}
	for(int i=1;i<=n;i++)
		f[i][i]=0;
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
```
**双向储存距离**
```c

	for(int i=1;i<=n;i++)
	{
		sum=0;
		for(int j=1;j<=T;j++)
			sum+=f[g[j]][i];
		if(sum<ans)
		{
			ans=sum;
			p=i;
		}
	}
	cout<<p<<endl;
}
```
最后提一下

注意给 f 数组先每个赋为极大值，然后再将 f[x][x] 赋为 0；

---

## 作者：万弘 (赞：4)

看许多大佬用的Floyed，然而亲测强行Dijsktra也可过

就是对每个点都跑一次Dij，然后求到每个牧场的距离和，取min

复杂度$O(n^2logn)$~~竟然比Floyed快~~

然后注意输出的是编号而不是距离和

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
typedef long long ll;
const ll INF=1ll<<60;
ll min(ll a,ll b)
{
    return a<b?a:b;
}
struct Edge
{
    ll v,w;
};
std::vector<Edge>G[1001];
ll dis[1001],a[1001],p,f,c;
struct Heap
{
    ll u,dis;
    bool operator <(const Heap &v)const
    {
        return dis>v.dis;
    }
}t;
std::priority_queue<Heap>q;
ll Dij(ll s)
{
    for(ll i=1;i<=p;++i)dis[i]=INF;
    dis[s]=0;
    q.push((Heap){s,0});
    ll u,v,w,ans=0;
    while(!q.empty())
    {
        t=q.top();q.pop();
        u=t.u;
        if(dis[u]!=t.dis)continue;
        for(ll i=G[u].size()-1;i>=0;--i)
        {
            v=G[u][i].v,w=G[u][i].w;
            if(dis[u]+w<dis[v])
            {
                dis[v]=dis[u]+w;
                q.push((Heap){v,dis[v]});
            }
        }
    }
    for(ll i=1;i<=f;++i)
    {
        if(dis[a[i]]==INF)return INF;
        ans+=dis[a[i]];
    }
    return ans;
}
void start()
{
    scanf("%lld%lld%lld",&p,&f,&c);
    for(ll i=1;i<=f;++i)scanf("%lld",&a[i]);
    ll u,v,w;
    for(ll i=1;i<=c;++i)
    {
        scanf("%lld%lld%lld",&u,&v,&w);
        G[u].push_back((Edge){v,w});
        G[v].push_back((Edge){u,w});
    }
}
void work()
{
    ll minn=INF,ans=-1,k;
    for(ll i=1;i<=p;++i)
    {
        k=Dij(i);
        if(k<minn)
        {
            minn=k;
            ans=i;
        }
    }
    printf("%lld",ans);
}
int main()
{
    start();
    work();
    return 0;
}

```

---

## 作者：zfn07 (赞：3)

我看了一遍,竟然没有SPFA的题解,那我就来写一篇吧。

这道题就是1到n依次跑1遍SPFA,把到各个贝茜喜欢的牧场的距离累加取最小值，然后输出能取到最小值的牧场编号即可。
### 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505,M=8005; 
int n,m,ff,f[505],cnt,head[N],dis[N],ans=1e9,an;//n为牧场数,m为道路数
bool vis[N];//记录是否访问过
struct g{
    int to,w,next;
}e[M<<1];//使用链式前向星存图
void add(int u,int v,int w)//建边
{
    e[++cnt].to=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void spfa(int s){//SPFA
    for(int i=1;i<=n;i++)//初始化
        dis[i]=2147483647;
    dis[s]=0;vis[s]=1;
    queue<int> q;
    q.push(s);
    while(!q.empty()){//开始操作
        int u=q.front();//取出队头
        q.pop();
        vis[u]=0;//将u赋为未来过
        for(int i=head[u];i;i=e[i].next){//循环
            int v=e[i].to;
            if(dis[v]<=dis[u]+e[i].w)//如果原来的距离比新距离更短
                continue;
            dis[v]=dis[u]+e[i].w;//否则更新距离
            if(!vis[v])//如果v未来过
                q.push(v),vis[v]=1;//把v入栈
        }
    }
}
int main(){
    cin>>n>>ff>>m;
    for(int i=1;i<=ff;i++)
    	cin>>f[i];
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);//存双向边
        add(v,u,w);
    }
    for(int i=1;i<=n;i++){
    	spfa(i);//调用SPFA
    	int s=0;
    	for(int j=1;j<=ff;j++)
    		s+=dis[f[j]];//累加距离
    	if(ans>s){//如果比原距离短,更新
			ans=s;
    		an=i;
    	}
	}
	cout<<an;//输出编号，注意:是输出编号！
    return 0;
}
```


---

## 作者：孑彧 (赞：1)

# P2935 Best Spot

### 题目描述

现在有n个地点，其中f个是贝茜所喜欢的，给出m条路，求出一个到所有贝茜喜欢的地点的距离之和最小的地点

### 思路

因为我们要统计出每个节点到喜欢的节点的距离，所以要求出任意两个点之间的最短距离，可以用Floyd来做，复杂度$O(n^3)$，由于n很小，所以可以承受。接下来我们就需要统计出每个节点到喜欢的节点的总距离，可以用$O(nf)$枚举求出答案，总时间复杂度$O(n^3)$

### 贴代码

```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#define maxn 600
using namespace std;
long long map[maxn][maxn];
long long p,f,c;
long long l[maxn];
int main(){
	cin>>p>>f>>c;
	for(long long i=1;i<=f;i++){
		cin>>l[i];
	}
	for(int i=1;i<=p;i++){
		for(int j=1;j<=p;j++){
			map[i][j]=0x3fffffff; 
		}
	}
	long long x,y,z; 
	for(long long i=1;i<=c;i++){
		cin>>x>>y>>z;
		map[x][y]=min(map[x][y],z);
		map[y][x]=map[x][y];
	}
	for(long long i=1;i<=p;i++){
		map[i][i]=0;
	}
	for(long long i=1;i<=p;i++){
		for(long long j=1;j<=p;j++){
			for(long long k=1;k<=p;k++){
				map[j][k]=min(map[j][i]+map[i][k],map[j][k]);
			}
		}
	}
	long long num=22222222222222;
	long long id=0;
	for(long long i=1;i<=p;i++){
		long long ans=0;
		for(long long j=1;j<=f;j++){
			ans+=map[l[j]][i];
		}
		if(num>ans){
			num=ans;
			id=i;
		}
	}
	cout<<id;
} 
```



---

## 作者：lzxhdxx (赞：0)

# 题解[P2935](https://www.luogu.com.cn/problem/P2935)

### 题意
选出任意一个农场，使这个农场到Bessie喜欢的农场的距离和最小。

### 思路
题目需要我们求的是每个农场到这F个农场的最短路，就是多源最短路，可以用Floyd过，但是Dijkstra也可以过，只要把每个点到F个农场的最短路求出来，再求和确定最小值记录农场号码，最后输出就可以，时间复杂度$O(n^2logn)$。

整理得以下步骤：

- 每个点跑一遍Dijkstra求每个点到F个农场的最短路

- 求和，如果最小值比当前值大的话，更新最小值并记录农场号码

- 输出农场号码

### Code:
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int Max = 100010, INF = 1e9;
int p, f, c, cnt = 0, dist[Max], head[Max];
bool vis[Max] = { false };

struct Node
{
	int u, step;
	Node(int a, int sp)
	{
		u = a; step = sp;
	}
	bool operator<(const Node& a)const
	{
		return step > a.step;
	}
};

struct edge
{
	int to, dis, next;
}e[Max];

void add_edge(int u, int v, int w)//插入新边
{
	e[++cnt].to = v;
	e[cnt].dis = w;
	e[cnt].next = head[u];
	head[u] = cnt;
}

void add(int u, int v, int w)//双向边，两个方向都要插入一次
{
	add_edge(u, v, w);
	add_edge(v, u, w);
}

void init()//多次Dijkstra，要初始化
{
	memset(vis, false, sizeof(vis));
	for (int i = 1; i <= p; i++)
		dist[i] = INF;
}

void Dijkstra(int st)
{
	init();
	priority_queue<Node>Q;//堆优化
	Q.push(Node(st, 0));
	dist[st] = 0;
	while (!Q.empty())
	{
		Node it = Q.top(); Q.pop();
		int u = it.u;
		if (vis[u]) continue;//如果当前点到过，就说明已经找到了最短路，当前点是堆中的重复元素
		vis[u] = true;
		for (int i = head[u]; i; i = e[i].next)
		{
			int to = e[i].to, dis = e[i].dis;
			if (dist[u] + dis < dist[to] && !vis[to])//松弛操作
			{
				dist[to] = dist[u] + dis;
				Q.push(Node(to, dist[to]));
			}
		}
	}
}

int main()
{
	int u, v, w, minn = INF, sum = 0, ans = 0, farm[Max];
	scanf("%d%d%d", &p, &f, &c);
	for (int i = 1; i <= f; i++)
		scanf("%d", &farm[i]);
	for (int i = 1; i <= c; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);//双向插入
	}
	for (int i = 1; i <= p; i++)
	{
		Dijkstra(i);//每个点跑一遍Dijkstra
		sum = 0;
		for (int j = 1; j <= f; j++) 
			sum += dist[farm[j]];//求和
		if (sum < minn)	//如果当前值小于最小值
			minn = sum, ans = i;//刷新最小值，记录农场号码
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：kfhkx (赞：0)

P党的福利~

来一波链式前向星的dijkstra

直接暴力做n次dijkstra

时间还挺客观的~

### p2935.pas
----
```pascal
var
        n,m,k,i,j,ans,bns,sum,tot,head,minn,v,x,y,z:longint;
        he,ne,t,w,dis,a:array[0..200000] of longint;
        p:array[0..200000] of boolean;
procedure link(x,y,z:longint);//链式前向星存图
begin
        inc(tot);
        ne[tot]:=he[x];
        he[x]:=tot;
        t[tot]:=y;
        w[tot]:=z;
end;
procedure dij(x:longint);
var
        i:longint;
begin
//赋初始值
        for i:=1 to n do begin
                dis[i]:=maxlongint;
                p[i]:=false;
        end;
        dis[x]:=0;
        head:=x;
//
        while not p[head] do begin
                p[head]:=true;
                v:=he[head];
                while v>0 do begin
                        if (not p[t[v]]) and (dis[t[v]]>dis[head]+w[v]) then
                         dis[t[v]]:=dis[head]+w[v];
                        v:=ne[v];
                end;
                minn:=maxlongint;
                for i:=1 to n do if (not p[i]) and (minn>dis[i]) then begin
                        minn:=dis[i];
                        head:=i;
                end;
        end;
end;
begin
        ans:=maxlongint;
        readln(n,m,k);
        for i:=1 to m do readln(a[i]);
        for i:=1 to k do begin
                read(x,y,z);
                link(x,y,z);//无向图要正反各存一次
                link(y,x,z);
        end;
        for i:=1 to n do begin//直接暴力做n次dijkstra
                dij(i);
                sum:=0;
                for j:=1 to m do sum:=sum+dis[a[j]];//每次做完统计答案
                if ans>sum then begin//更优就替换
                        ans:=sum;
                        bns:=i;
                end;
        end;
        writeln(bns);//最后输出的是编号！
end.
```

---

## 作者：autoint (赞：0)

此题算法用**Floyd**不多说，给数组附初值时注意：

如果你用999...类型的，只用6位，其他都有问题，估计是溢出了

如果你用INF，那么计算时要来个特判，理由同上

下面是代码



```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<algorithm>
#define INF 2147483647
using namespace std;
inline int read(int&x) {
    int data=0,w=1;
    char ch=0;
    while(ch!='-' && (ch<'0' || ch>'9')) ch=getchar();
    if(ch=='-') w=-1,ch=getchar();
    while(ch>='0' && ch<='9') data=data*10+ch-'0',ch=getchar();
    return x=data*w;
}
inline void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
//以上为输入输出优化 
int dis[510][510],a[510];//a是f集合 
int main() {
    int p,f,c;
    read(p); read(f); read(c);
    for(int i=1;i<=f;++i)
        read(a[i]);
    memset(dis,999999,sizeof(dis));
    for(int i=1;i<=p;++i)//此处忘了没过的自己打脸
        dis[i][i]=0;
    for(int i=1;i<=c;++i){
        int a,b;
        read(a); read(b);
        read(dis[a][b]);
        dis[b][a]=dis[a][b];//由于是双向图
    }
    for(int k=1;k<=p;++k)//Floyd
        for(int i=1;i<=p;++i)
            for(int j=1;j<=p;++j)
                if(dis[i][k]+dis[k][j]<dis[i][j])
                    dis[i][j]=dis[i][k]+dis[k][j];
    int mv=INF,pos;
    for(int i=1;i<=p;++i){//此处枚举。 
        int sum=0;
        for(int j=1;j<=f;++j)
            sum+=dis[i][a[j]];
        if(sum<mv)
            mv=sum,
            pos=i;
    }
    write(pos);
    return 0;
}
```

---

## 作者：ws_fuweidong (赞：0)

裸的floyd。。

求出最短路 找出和那f个点距离之和最小的点

（除法有误差，不用除f，找和最小的点就行）

代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#define maxn 501
#define inf 99999999
using namespace std;
int dis[maxn][maxn],n,m,ff,f[maxn];
int main(){
    scanf("%d%d%d",&n,&ff,&m);
    for (int i=1;i<=ff;i++)
    scanf("%d",&f[i]);
    for (int i=1;i<=n;i++)
    for (int j=1;j<=n;j++)
    if (i==j) dis[i][j]=0;else
    dis[i][j]=inf;
    for (int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        dis[x][y]=z;
        dis[y][x]=z;
    }
    for (int k=1;k<=n;k++)
    for (int i=1;i<=n;i++)
    for (int j=1;j<=n;j++)
    if (dis[i][j]>dis[i][k]+dis[k][j])
    dis[i][j]=dis[i][k]+dis[k][j];
    int minn=0x7fffffff,l;
    for (int i=1;i<=n;i++)
    {
        int sum=0;
        for (int j=1;j<=ff;j++)
        if (dis[i][f[j]]!=inf)
        sum+=dis[i][f[j]];
        if (sum<minn){
            minn=sum;
            l=i;
        }
    }
    printf("%d",l);
    return 0;
}
```

---

## 作者：蛟川洋 (赞：0)

这一题题解好少啊，本蒟蒻还是贡献一下我的代码吧，不喜勿喷。

这就是最短路的问题呀，没什么大改动，就在最后加个筛选就行了，代码附上，具体内容见代码：

```cpp
program P2935;
const
        inf=250001;
var
        s:array[1..500,1..500] of longint;
        f1:array[1..500] of longint;
        p,f,c,a,b,t,s1,min,num,i,i1:longint;
procedure floyd;//图论最短路Floyd算法
var t,i,i1,i2:longint;
begin
for i:=1 to p do
 for i1:=1 to p do
  for i2:=1 to p do
   begin
   t:=s[i1,i]+s[i,i2];
   if s[i1,i2]>t then s[i1,i2]:=t;
   end;
end;
begin
        readln(p,f,c);
        for i:=1 to p do
         for i1:=1 to p do
          begin
          if i<>i1
             then s[i,i1]:=inf;//赋初值
          end;
        for i:=1 to f do
         begin
         readln(f1[i]);//读入最佳农场
         end;
        for i:=1 to c do
         begin
         readln(a,b,t);
         s[a,b]:=t;//编号为a的农场到编号为b的农场的路径
         s[b,a]:=t;//因为是无向（双向）图，所以a到b与b到a都要赋值。如果是有向（单向）图，则去掉这一行
         end;
        floyd;//调用Floyd，算出最短路
        for i:=1 to p do//循环变量i表示最佳农场编号
         begin
         s1:=0;//用来储存路径和，因为最佳农场个数一定，所以平均值最小的农场路径和也最小
         for i1:=1 to f do
          begin
          inc(s1,s[i,f1[i1]]);//将路程加上第i个农场到目标第f[i1]个农场的路径
          end;
         if (min>s1) or (min=0)//用来储存最小值
            then
            begin
            min:=s1;
            num:=i;//用来储存当路径和最小时的最佳农场
            end;
         end;
        writeln(num);//输出当路径和最小时的最佳农场
end.
```

---

## 作者：wqd008 (赞：0)

貌似没有p的代码  我便来贡献一下

与楼下一样 先对所有的路进行弗洛伊德算法 就是找出每个点的最短路 替换掉

然后再通过枚举每个点 当作起点 接着 找出其中能够走遍的点即可 找不到则推出

其实并不难

```cpp
program p2935;
var dis:array[1..500,1..500] of longint;
    love:array[1..500] of longint;
    i,j,m,n,p,f,c,a,b,l,sum,min,ans,k:longint;
begin
  read(p,f,c);
  for i:=1 to f do
  begin
    read(n);
    love[i]:=n;
  end;
  for i:=1 to p do
    for j:=1 to p do
    begin
      if i=j then begin dis[i,j]:=0;dis[j,i]:=0;end
      else dis[i,j]:=100000;
    end;//初始化
  for i:=1 to c do
  begin
    read(a,b,l);
    dis[a,b]:=l;
    dis[b,a]:=l;
  end;
  for k:=1 to p do
    for i:=1 to p do
      for j:=1 to p do
      begin
        if (dis[i,k]+dis[k,j])<dis[i,j] then
        dis[i,j]:=dis[i,k]+dis[k,j];
      end;//弗洛伊德
    sum:=0;min:=100000;
    for i:=1 to p do
    begin
    sum:=0;
      for j:=1 to f do
      begin
      if dis[i,love[j]]<>100000 then
         inc(sum,dis[i,love[j]])
      else begin inc(sum,100000);break;end;//有一个点不满足 则退出 否则tle
      end;
      if sum<min then begin min:=sum;ans:=i;end;//用min存储最小值用来比较
    end;
  writeln(ans);
end.
```

---

