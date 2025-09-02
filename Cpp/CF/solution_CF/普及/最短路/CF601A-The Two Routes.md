# The Two Routes

## 题目描述

有个地方有一些城镇，城镇与城镇间有铁路或公路相连，如果有铁路相连，就不会有公路相连，没有铁路连接的城镇就会有公路相连。给你 $n$ 个城镇， $m$ 条铁路线，问同时从城镇1出发，分别坐火车和坐汽车到达城镇n，求两者都到达的时候最少的用时。其中火车和汽车不能同时到达中间点。

## 样例 #1

### 输入

```
4 2
1 3
3 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5 5
4 2
3 5
4 5
5 1
1 2
```

### 输出

```
3
```

# 题解

## 作者：Ganshuaige (赞：17)

//
Jzzhu and Cities
//

水题

个人认为难度应该为**普及+**

有n个节点m条铁路的图

不是铁路就是公路

有两个人分别走铁路和公路

问最后从1走到n的那个人用时多久

所以

必定有一个人可以直接从1走到n

数据范围n为400

所以很水，用**邻接链表**十分方便

若map[1][n]=0

将图取反跑一遍最短路

最后输出dis[n]
若dis[n]为inf就输出-1~

附上ac代码：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>

const int INF = 0x3f3f3f3f;
const int Maxn = 450;
using namespace std;

int map[Maxn][Maxn];

int n,m;
int dis[Maxn];
bool vis[Maxn];

void spfa(){
	memset(vis,0,sizeof(vis));
	memset(dis,INF,sizeof(dis));
	queue <int> q;
	q.push(1);
	vis[1]=1;
	dis[1]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int v=1;v<=n;v++){
			if(u==v)
				continue;
			if(map[u][v]){
				if(dis[v]>dis[u]+1){
					dis[v]=dis[u]+1;
					if(!vis[v]){
						vis[v]=1;
						q.push(v);
					}
				}
			}
		}
	}
}

int main(){
	int u,v;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		map[u][v]=map[v][u]=1;
	}
	if(map[1][n]==1)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(i==j)
					continue;
				map[i][j]=1-map[i][j];
			}
	spfa();
	if(dis[n]==INF)
		dis[n]=-1;
	printf("%d",dis[n]);
	return 0;
}
//////
/*

*///
```

---

## 作者：WaltVBAlston (赞：7)

顺着最短路查到的，不得不说，是一道挺好的题目。

这道题的数据不是很严，~~不然卡掉SPFA是分分钟的事~~，所以我们需要一种更靠谱的最短路算法：Dijkstra。

用w数组建图，d1d2记录最短路。

Dijkstra以贪心为基础，裸的Dijkstra时间复杂度为O（n^2），因为同样的原因，我使用优先队列（二叉堆）进行优化，优化后的时间复杂度为O（（n+m）logm）。

这里要注意两个点：

1.在非常稠密的图（近似于完全图）中，优先队列可能跑不过裸的Dijkstra，这个时候就要准确判断，进行取舍。

2.在负权图（有边权为负数的图）中，不能使用Dijkstra，只能使用~~已经死了的~~SPFA。

这里介绍一些优先队列的基本操作：

1.push 进入队列

2.pop 弹出队头元素

3.top（注意不是front） 访问队头元素

4.empty 队列是否为空

接下来贴代码：

```
#include<iostream>
#include<cstdio>
#include<queue>
#include<cmath>
#define ll long long
using namespace std;
int n,m;
bool w[1001][1001];
ll d1[1001],d2[1001];
struct node
{
	int index;
	ll dis;
	bool operator < (const node &x)const
	{
		return dis>x.dis;
	}
};
priority_queue <node> q;
bool flag[1001];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			w[i][j]=false;
		}
		d1[i]=2147483647;
		d2[i]=2147483647;
		flag[i]=false;
	}
	d1[1]=0;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		w[u][v]=true;
		w[v][u]=true;
	}
	q.push((node){1,0});
	while(!q.empty())
	{
		node x=q.top();
		q.pop();
		int k=x.index;
		if(flag[k]==true)
		{
			continue;
		}
		flag[k]=true;
		for(int i=1;i<=n;i++)
		{
			if(w[i][k]==false&&d1[i]>d1[k]+1)
			{
				d1[i]=d1[k]+1;
				q.push((node){i,d1[i]});
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		flag[i]=false;
	}
	d2[1]=0;
	q.push((node){1,0});
	while(!q.empty())
	{
		node x=q.top();
		q.pop();
		int k=x.index;
		if(flag[k]==true)
		{
			continue;
		}
		flag[k]=true;
		for(int i=1;i<=n;i++)
		{
			if(w[i][k]==true&&d2[i]>d2[k]+1)
			{
				d2[i]=d2[k]+1;
				q.push((node){i,d2[i]});
			}
		}
	}
	if(d1[n]==2147483647||d2[n]==2147483647)
	{
		printf("-1");
	}
	else
	{
		printf("%lld",max(d1[n],d2[n]));
	}
	return 0;
}

```

谢谢大家，喜欢的话记得三连哦（点赞评论关注）


---

## 作者：simonG (赞：4)

### 前言
dijkstra，优化后为$O(n\times \log n)$，但不能处理负权边,  
spfa,为$O(nm)$，但容易被卡,  
所以floyd，$O(n^3)$，既不用考虑负边，还不用想着被卡，随便用。

### 详解
>1,时间限制为2秒，$n<=400$,$n^3=64000000$，一秒都不到，所以floyd是可行的  
贴一个状态转移方程 $dp_{j,k}=\min(dp_{j,k},dp_{j,i}+dp_{i,k})$

>2,建图，邻接矩阵，先初始化公路为1，轨道为正无限。如果一条图被轨道连接了，那么这一条路在公路上赋值为正无限，反之亦然。

>3,汽车和火车要同时到达，就是求出每一条路的最短路，然后比较即可。如果最短路的数还为原来初始化的数，即输出$-1$

### 代码
有大佬的帖发了两个floyd，其实可以合并。
```cpp
#include<bits/stdc++.h>
#define INF 1e9
using namespace std;
int dis1[450][450],dis2[450][450];
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			dis1[i][j]=INF,dis2[i][j]=1;
	for (int i=1; i<=m; i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		dis1[x][y]=dis1[y][x]=1;
		dis2[x][y]=dis2[y][x]=INF;
	}
	for(int k=1; k<=n; k++)
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++) {
				if(dis1[k][i]+dis1[k][j]<dis1[i][j]) dis1[i][j]=dis1[k][i]+dis1[k][j];
				if(dis2[k][i]+dis2[k][j]<dis2[i][j]) dis2[i][j]=dis2[k][i]+dis2[k][j];
			}
	int ans=max(dis1[1][n],dis2[1][n]);
	printf("%d",ans==INF?-1:ans);
	return 0;
}
```
$26$行，简洁明了

### 后记
感谢@Ztemily的纠正，dijkstar已改正为dijkstra.


---

## 作者：UperFicial (赞：1)

# 水の图论

### 前言

非常适合图论新手，难度同 [$this$](https://www.luogu.com.cn/problem/P3371)。

这里给一个 $O(nlogn)$ 的 $\texttt{dijkstra}$ 做法，但可惜真正的复杂度是 $O(n^2)$，因为建图需要。

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/CF601A)。

### 题目简述

给您一张 $n$ 个点 $m$ 条边的无向图，两个点之间要么**只有**铁路或**只有**公路相连。问同时从 $1$ 号点出发，分别坐火车和坐汽车到达 $n$ 号点，求两者都到达的时候最少的用时，若有一个不能到到，输出 `-1`。

### 题目解析

设 $d1_i$ 为坐火车从 $1$ 号点到达 $i$ 号点的最短时间，$d2$ 为坐公交从 $1$ 号点到达 $i$ 号点的最短时间。

既然要求两者都到达，那么答案就是  $\max(d1_n,d2_n)$，如果有一个没到达另一个的用时就不算是都到达的用时，故**答案要取最大值**。

现在就是要求 $d1_n$ 和 $d2_n$ 的值，由于起点和重点固定的，所以很容易想到用 $\texttt{dijkstra}$。

并且由于题目中只给了我们铁路的图，所以还需要用 $O(n^2)$ 的复杂度去建公交的图。

[$code$](https://paste.ubuntu.com/p/h4KRv2SjZH/)

空间复杂度：$O(n^2)$。

时间复杂度：$O(n^2+2nlogn)=O(n^2)$。

$$\texttt{The End.by UF}$$

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

##### 主体思路

这道题可以用 `Floyd` 算法求解。

首先，输入一条铁路，就把距离更改为 $1$。

然后对于没有铁路的地方，建造公路。

最后对 $2$ 张无向图都跑一遍 `Floyd` 就好了。

##### 相撞情况

可以发现，无论如何，都有且仅有一条 $1\to n$ 的边，并且不是在铁路就是在公路。

这就意味着，一定有一种交通方式能够保证最短路长度为 $1$，另一种交通方式的最短路长度大于 $1$。

也就是说，一个人走 $1$ 的时间就可以到终点，另一个人不可能在 $1$ 的时间内来到终点。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
#define max_n 400
#define inf 0x3f3f3f3f
int n;
int m;
int g1[max_n+2][max_n+2];
int g2[max_n+2][max_n+2];
inline int mi(int a,int b){
	return a<b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF0601A_1.in","r",stdin);
	freopen("CF0601A_1.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			g1[i][j]=inf;
			g2[i][j]=inf;
		}
		g1[i][i]=0;
		g2[i][i]=0;
	}
	for(int i=1,u,v;i<=m;++i){
		scanf("%d%d",&u,&v);
		g1[u][v]=g1[v][u]=1;
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(g1[i][j]==inf)g2[i][j]=1;
		}
	}
	for(int k=1;k<=n;++k){
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				g1[i][j]=g1[j][i]=mi(g1[i][j],g1[i][k]+g1[k][j]);
				g2[i][j]=g2[j][i]=mi(g2[i][j],g2[i][k]+g2[k][j]);
			}
		}
	}
	if(g1[1][n]==inf||g2[1][n]==inf){
		printf("-1\n");
		return 0;
	}
	printf("%d\n",-mi(-g1[1][n],-g2[1][n]));//不想写max函数
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/57423890)

By **dengziyue**

---

## 作者：FR_qwq (赞：0)

这道题可以用 $dijkstra$ （~~什么？你不会 dij？请自行百度~~）来做：先读入一个无向图，然后用邻接矩阵把这个图存起来，最后跑两遍 $dijkstra$ 输出最大的值就 OK 了。但是要注意：要判断此图是否可以从 1 号节点走到 $n$ 号节点。可以用以下代码来实现：
```cpp
if(d[n]==d[0])return printf("-1\n"),0;//d[n] 是从 1 号节点走到 n 号节点的最短路，0 号即初始值，若 n 号节点的值等于初始值，那肯定不能从 1 号节点走到 n 号节点。
```
$Pascal$ 代码：
```pascal
if(d[n]=d[0])then
  begin
  writeln('-1');
  halt;
  end;//注释同上
```

这样，一串 $\color{green}\texttt{AC}$ 代码就浮现在我们的眼前了：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cmath>
#define INF ((1<<30)-1)//INF 为最大值，为了后面求最小用
using namespace std;
int ANS,mi,i,n,m,j,d[100010],a[1010][1010],us[100010],from,k,x,y,z;//定义
inline int read(){int x=0,f=1;char ch='\0';while(ch<'0'||ch>'9')f=(ch=='-')?(0-f):f,ch=getchar();
while(ch>='0'&&ch<='9')x=x*10+(ch^'0'),ch=getchar();return x*f;}//快读，也可以用 cin/scanf 来读入
int main(){
	n=read();m=read();
	for(i=1;i<=m;i++)x=read(),y=read(),a[x][y]=a[y][x]=1;//读并存图
	memset(d,127,sizeof(d));//给 d 数组全赋最大值，以便后面进行 dijkstra。
   d[1]=0;us[1]=1;from=1;//赋初值
	for(j=1;j<n;j++){//开始搞 dijkstra
		for(i=1;i<=n;i++)
			if(!us[i]&&a[from][i]&&d[i]>d[from]+1)
				d[i]=d[from]+1;//进行扩展
		mi=INF;
		for(i=1;i<=n;i++)
			if(!us[i]&&d[i]<=mi)
				k=i,mi=d[i];//求最小的节点
		from=k;
		us[k]=1;//继续扩展
	}
	ANS=d[n];//存储走铁路的最短路
	if(d[n]==d[0])return printf("-1\n"),0;//判断是否能到
	memset(d,127,sizeof(d));memset(us,0,sizeof(us));//因为还要跑一边 dij，所以要重新赋初值。
	d[1]=0;us[1]=1;from=1;//赋初值
	for(j=1;j<n;j++){//再跑一遍
		for(i=1;i<=n;i++)
			if(!us[i]&&!a[from][i]&&d[i]>d[from]+1)
				d[i]=d[from]+1;//扩展
		mi=INF;
		for(i=1;i<=n;i++)
			if(!us[i]&&d[i]<=mi)
				k=i,mi=d[i];//求最小节点
		from=k;
		us[k]=1;//继续扩展
	}
	if(d[n]==d[0])return printf("-1\n"),0;//判断是否能到
	printf("%d\n",max(ANS,d[n]));//求走铁路最短路和走公路最短路的最大值
	return 0;//完结撒花~
}
```
P 党看这：
```pascal
uses math;//这个库很有用，它里面有 min 函数和 max 函数
var ANS,mi,i,n,m,j,from,k,x,y,z:longint;
d,us:array[0..100010]of longint;
a:array[0..1010,0..1010]of longint;//定义
begin
readln(n,m);
for i:=1 to m do
  begin
  readln(x,y);
  a[x][y]:=1;a[y][x]:=1;
  end;//读入并存图
fillchar(d,sizeof(d),127);
d[1]:=0;us[1]:=1;from:=1;//初始化
for j:=1 to n-1 do//跑 dij
  begin
  for i:=1 to n do
    if(us[i]=0)and(a[from][i]=1)and(d[i]>d[from]+1)then
      d[i]:=d[from]+1;//扩展
  mi:=maxlongint;
  for i:=1 to n do
    if(us[i]=0)and(d[i]<=mi)then
      begin
      k:=i;
      mi:=d[i];
      end;//求最小节点
  from:=k;
  us[k]:=1;//继续扩展
  end;
ANS:=d[n];//存存储走铁路的最短路
if(d[n]=d[0])then
  begin
  writeln('-1');
  halt;
  end;//判断是否能到
fillchar(d,sizeof(d),127);fillchar(us,sizeof(us),0);
d[1]:=0;us[1]:=1;from:=1;//重新初始化
for j:=1 to n-1 do//再跑一遍 dij
  begin
  for i:=1 to n do
    if(us[i]=0)and(a[from][i]=0)and(d[i]>d[from]+1)then
      d[i]:=d[from]+1;//扩展
  mi:=maxlongint;
  for i:=1 to n do
    if(us[i]=0)and(d[i]<=mi)then
      begin
      k:=i;
      mi:=d[i];
      end;//求最小节点
  from:=k;
  us[k]:=1;//继续扩展
  end;
if(d[n]=d[0])then writeln('-1')//判断是否能到
else writeln(max(ANS,d[n]));//输出走公路的最短路与走铁路的最短路的最大值
end.//完结撒花~
```

---

## 作者：UKE自动稽 (赞：0)

这一题让我们算两种交通工具同时到达城镇n的**最短**用时，很明显是用最短路径解决。

把每条边的权值设为1（不要问我为什么，题目中说了），然后，两种交通工具跑一边最短路，最后取用时最长的（因为两种交通工具跑的时间都是最优的，题目问两种交通工具都到达终点的最优时间，所以就看慢者跑的时间）

  $\color{black} \text{}  \colorbox{black}{PS:代码有问题}$  

代码

```
#include <cstdio>
using namespace std;
#define maxn 411
#define INF 0x3f3f3f3f
int a1[maxn][maxn], a2[maxn][maxn];  //a1和a2分别表示两种交通工具
int n, m;
int d[maxn];
bool vis[maxn];

int dij (int a[maxn][maxn])              //裸的dijkstra，不多解释
{
	for (int i = 1; i <= n; i++) {
		d[i] = INF;
		vis[i] = 0;
	}
	d[1] = 0;
	for (int j = 1; j <= n; j++) {
		int k = -1;
		int Min = INF;
		for (int i = 1; i <= n; i++) {
			if (!vis[i] && d[i] < Min) {
				Min = d[i];
				k = i;
			}
		}
		if (k == -1)
			break;
		vis[k] = 1;
		for (int i = 1; i <= n; i++) {
			if (!vis[i])
				d[i] = min (d[i], d[k]+a[k][i]);
		}
	}
	return d[n];
}

int main ()
{
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			a1[i][j] = a2[i][j] = INF;   //初始化
		}
	}
	int u, v;
	for (int i = 1; i <= m; i++) {
		scanf ("%d%d", &u, &v);
		a1[u][v] = a1[v][u] = 1;         //无向图
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j)
				continue;
			if (a1[i][j] == INF)       //没有公路必然是铁路
				a2[i][j] = 1;
		}
	}
	int ans1 = dij (a1);//跑两遍dijkstra
	int ans2 = dij (a2);
	if (ans1 >= INF || ans2 >= INF)      //如果其中有一种交通工具不能到达或都不能到达终点，输出-1 。
		cout << "-1" << endl;
	else cout << max (ans1, ans2) << endl; //输出最大值
	return 0;
}

```

---

## 作者：CrTsIr400 (赞：0)

看没有人讲到$BFS$，本蒟蒻就放出宽搜大法($SPFA$)了$qwq$。

因为每条边边权为$1$

所以$BFS$大法好。（也可以使用$SPFA$，差不多的）

### $\texttt{1.如何存图？}$

首先，考虑一下数据范围

$2 \leq n \leq 400$

邻接矩阵空间复杂度：$400\times400=160000$

珂以接受。

~~我才不告诉你要双向存图~~

### $\texttt{2.如何BFS？}$

我们定义起始节点为$1$(题目讲到了)

```
struct node
{
	int pos;
	int step;
};
```

不过先得建立一个存储节点的结构体，

**$pos$代表当前的节点位置，$step$代表从$1$号节点到这个节点要用多少步。**

然后按照$BFS$**从$1$号节点一直扩展直到$n$号节点**。

```cpp
Fu(i,1,n)
if(!b[i]&&e[q.front().pos][i])
{
	b[i]=1;
	q.push({i,q.front().curr+1});
	if(i==n)return q.front().curr+1;
}
```
这就是$BFS$算法的核心：**扩展每条可以连接的边。**

就像倒水一样

**然后别忘记$pop$掉队首**！

整个$BFS$代码是这样的：

```cpp
struct node
{
	int pos;
	int curr;
};
queue<node>q;
int bfs(int e[401][401])
{
	while(!q.empty())q.pop();
	q.push({1,0});b[1]=1;
	while(!q.empty())
	{
		Fu(i,1,n)
		if(!b[i]&&e[q.front().pos][i])
		{
			b[i]=1;
			q.push({i,q.front().curr+1});
			if(i==n)return q.front().curr+1;
		}
		q.pop();
	}
	return inf;
}
```

其实可以改一下，变成$SPFA$,但是由读者自己进行扩展，本蒟蒻也就不打了。

### $\texttt{3.完整代码：}$

```cpp
#include<bits/stdc++.h>
#define inf (1<<30-1)
#define linf ((1<<62)ll-1)
#define Fu(i,a,b) for(register int i=a;i<=b;i++)
#define Fd(i,a,b) for(register int i=a;i>=b;i--)
#define Fn(i,a) for(register int i=las[a];i;i=nex[i])
int Fl,Pn,SI=100;char mch=' ',ch,Bf[21];
template<typename t>void in(t&a){a=0;ch=getchar();Fl=1;while((ch<'0')||(ch>'9'))Fl=(ch=='-')?-Fl:Fl,ch=getchar();while((ch>='0')&&(ch<='9'))a=a*10+ch-'0',ch=getchar();a*=Fl;}
template<typename t>void out(t a){if(a<0)putchar('-'),a=-a;if(a==0)putchar('0');while(a)Bf[++Pn]=a%10+'0',a/=10;while(Pn)putchar(Bf[Pn]),--Pn;putchar(mch);}
template<typename t,typename ...ARGS>void in(t&a,ARGS&...args){in(a);in(args...);}
template<typename t,typename ...ARGS>void out(t a,ARGS... args){out(a);out(args...);}
using namespace std;
int t[401][401],c[401][401],n,m,b[401],t1,t2;
struct node
{
	int pos;
	int curr;
};
queue<node>q;
int bfs(int e[401][401])
{
	while(!q.empty())q.pop();
	memset(b,0,sizeof(b));
	q.push({1,0});b[1]=1;
	while(!q.empty())
	{
		Fu(i,1,n)
		if(!b[i]&&e[q.front().pos][i])
		{
			b[i]=1;
			q.push({i,q.front().curr+1});
			if(i==n)return q.front().curr+1;
		}
		q.pop();
	}
	return inf;
}
int main()
{
	in(n,m);
	memset(c,1,sizeof(c));
	Fu(i,1,m)
	{
		in(t1,t2);
		t[t1][t2]=1;
		t[t2][t1]=1;
		c[t1][t2]=0;
		c[t2][t1]=0;
	}
	t1=bfs(t);
	t2=bfs(c);
	if(t1==inf||t2==inf)cout<<-1;
	else cout<<max(t1,t2);
	return 0;
}
```

### $\texttt{4.小彩蛋}$

$SPFA$在这道题不会死（

另外还有$dij$和$Floyd$解法，交了一交

$SPFA:$![cf601A(3).PNG](https://i.loli.net/2020/02/04/3uI9sDVvqFAd4fp.png)

$dijkstra:$![cf601A(2).PNG](https://i.loli.net/2020/02/04/RpKbFjcI2fzWZD9.png)

$Floyd:$![cf601A(1).PNG](https://i.loli.net/2020/02/04/nQfRPJ7Kl85HAsI.png)


---

## 作者：zhangyuhan (赞：0)

$emm 2\leq n \leq 400?$ $O(n^3)$的$floyd$都可以$A$。。。

看了看其他两篇题解，都是用$dijkstra/SPFA$做的，那我就来发$floyd$的版本吧！

本题思路：首先根据**除了铁路就是公路**这一条件，建两个图，一个是"铁路网"，一个是"公路网"。前者通过读入来建图，后者通过反铁路网来建图。

**什么叫反铁路网？**

就是存铁路网的矩阵中，某一条边在铁路网中没有，那么这条边一定属于公路网。

这两个图的每一条边的权值都是$1$。

接着，对于这两个图各跑一遍$floyd$就可以了。

**最后别忘加特判！**

$AC$ $Code$

```cpp
#include <iostream>
using namespace std;

const int MAXN=1010,INF=1e8;

int n,m;

int dis1[MAXN][MAXN],dis2[MAXN][MAXN];

void init(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dis1[i][j]=dis2[i][j]=INF;
}//一定要初始化！还有INF不要赋太大！否则floyd时相加容易溢出！

void floyd1(){
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis1[i][j]=min(dis1[i][j],dis1[i][k]+dis1[k][j]);
}

void floyd2(){
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis2[i][j]=min(dis2[i][j],dis2[i][k]+dis2[k][j]);
}

int main(){
	cin>>n>>m;
	init();
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		dis1[u][v]=dis1[v][u]=1;
	}//读入+建铁路网
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(i==j)
				continue;
			if(dis1[i][j]==INF)
				dis2[i][j]=1;
		}//建公路网
	floyd1();
	floyd2();
	if(dis1[1][n]==INF||dis2[1][n]==INF){
		cout<<-1<<endl;
		return 0;
	}//特判
	cout<<max(dis1[1][n],dis2[1][n])<<endl;
	return 0;//完结撒花！
}
```

---

