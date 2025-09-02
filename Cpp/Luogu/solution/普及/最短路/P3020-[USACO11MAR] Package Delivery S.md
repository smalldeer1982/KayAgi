# [USACO11MAR] Package Delivery S

## 题目描述

Farmer John must deliver a package to Farmer Dan, and is preparing to make his journey. To keep the peace, he gives a tasty treat to every cow that he meets along his way and, of course, FJ is so frugal that he would like to encounter as few cows as possible.

农夫约翰必须送一个包裹给农夫丹，并准备去旅行。为了保持和平，他必须给每一头遇到的奶牛一些吃的，当然，FJ很节俭，他想可能遇到尽可能少的奶牛。

FJ has plotted a map of N (1 <= N <= 50,000) barns, connected by M (1 <= M <= 50,000) bi-directional cow paths, each with C\_i (0 <= C\_i <= 1,000) cows ambling along it. A cow path connects two distinct barns, A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i). Two barns may be directly connected by more than one path. He is currently located at barn 1, and Farmer Dan is located at barn N.

FJ 已经绘制了 $N(1 \le N \le 50000)$ 个谷仓的地图，通过 $M(1 \le M \le 50000)$ 条双向牛道，每条双向牛道上有 $c[i](0 \le c[i] \le 1000)$ 奶牛漫步。双向牛道连接两个不同的谷仓，$a[i]$ 和 $b[i](1 \le a[i] \le N,1 \le b[i] \le N, a[i] \neq b[i])$。两个谷仓可以由一条以上的小路直接连接。他目前在 $1$ 号谷仓，农夫丹位于 $N$ 号谷仓。

Consider the following map:

```cpp
           [2]---
          / |    \
         /1 |     \ 6
        /   |      \
     [1]   0|    --[3]
        \   |   /     \2
        4\  |  /4      [6]
          \ | /       /1
           [4]-----[5] 
                3  
```
The best path for Farmer John to take is to go from 1 -> 2 -> 4 -> 5 -> 6, because it will cost him 1 + 0 + 3 + 1 = 5 treats.

Given FJ's map, what is the minimal number of treats that he should bring with him, given that he will feed each distinct cow he meets exactly one treat? He does not care about the length of his journey.


## 样例 #1

### 输入

```
6 8 
4 5 3 
2 4 0 
4 1 4 
2 1 1 
5 6 1 
3 6 2 
3 2 6 
3 4 4 
```

### 输出

```
5 
```

# 题解

## 作者：Sober_Clever (赞：3)

最短路裸题

dij+heap

拿来练手还是很好的
```cpp
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN=50000 + 3;
int read()
{
    int x=0,w=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') w=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}
    return x*w;
}

struct Edge
{
    int to,w,next;
}e[MAXN<<1];
int cnt=0,head[MAXN]={0};
inline void add(int u,int v,int w)
{
    e[++cnt].to=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}

int d[MAXN]={0},vis[MAXN]={0};
void dij()
{
    memset(vis,0,sizeof(vis));
    memset(d,127,sizeof(d));
    priority_queue<pair<int,int> > Q;
    d[1]=0,Q.push(make_pair(0,1));
    while(!Q.empty())
    {
        int u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i;i=e[i].next)
        {
            int v=e[i].to;
            if(d[v]>d[u]+e[i].w)
            {
                d[v]=d[u]+e[i].w;
                Q.push(make_pair(-d[v],v));
            }
        }
    }

}

int main()
{
    int n=read(),m=read();
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read(),w=read();
        add(u,v,w);
        add(v,u,w);
    }
    
    dij();
    
    printf("%d\n",d[n]);
    return 0;	
}
```


---

## 作者：寒鸽儿 (赞：2)

dijkstra裸题？  
直接跑模板好了。  
建议使用if(dnow > d[cur]) continue; 来代替if(!vis[cur]),据说这样子更加快一些  
72ms
```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#define pii pair<int, int>

using namespace std;

const int maxn = 50010;

priority_queue<pii> q;
int n;

#define gc() getchar()
char buf[2000000];
inline void read(int &x) {
	x = 0;
	char ch = gc();
	while( ch < '0' || ch > '9' ) ch = gc();
	while(ch >= '0' && ch <= '9') x = (x<<3)+(x<<1)+(ch&15), ch = gc();
}

int head[maxn], ver[maxn<<1], wei[maxn<<1], nex[maxn<<1], tot = 0;
inline void addedge(int u, int v, int w) {
	ver[tot] = v; wei[tot] = w; nex[tot] = head[u]; head[u] = tot++;
	ver[tot] = u; wei[tot] = w; nex[tot] = head[v]; head[v] = tot++;
}

int d[maxn];

int main() {
	int m, u, v, w;
	memset(head, -1, sizeof(head));
	memset(d, 0x3f, sizeof(d));
	read(n); read(m);
	while(m--) {
		read(u); read(v); read(w);
		addedge(u, v, w);
	}
	d[1] = 0; q.push(make_pair(0, 1));
	while(!q.empty()) {
		int cur = q.top().second, dmen = -q.top().first; q.pop();
		if(dmen > d[cur]) continue;
		for(int i = head[cur]; i != -1; i = nex[i])
			if(d[ver[i]] > d[cur] + wei[i]) {
				d[ver[i]] = d[cur] + wei[i];
				q.push(make_pair(-d[ver[i]], ver[i]));
			}
	}
	printf("%d\n", d[n]);
	return 0;
}

```
欢迎互相关注(然而在oi界蒟蒻的圈很小)。  
最后安利一下[蒟蒻的洛谷博客](https://www.luogu.org/blog/oldherd/)  


---

## 作者：Zekrom (赞：2)

这道题没人做一定是因为没有标签  
可惜题目很简单就是最短路模板  
1.dijkstra  //159ms  
2.spfa //1163ms   
~~题解里没人写dij~~??  
上代码    
       
       1.dijstra
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define N 50010
#define M 100010 
using namespace std;
int n,m,d[N],tot,head[N];
bool vis[N];
struct Edge{
	int v,next,val;
}edge[M];
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
inline void add(int x,int y,int z){edge[++tot].v=y;edge[tot].next=head[x];edge[tot].val=z;head[x]=tot;}
void dijkstra(int x){
	priority_queue<pair<int,int> >q;
	memset(d,0x3f,sizeof(d));
	q.push(make_pair(0,x));d[x]=0;
	while(q.size()){
		int u=q.top().second;q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].v,z=edge[i].val;
			if(d[v]>d[u]+z){
				d[v]=d[u]+z;
				q.push(make_pair(-d[v],v));
			}
		}
	} 
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		add(x,y,z); add(y,x,z);
	}
	dijkstra(1);  //159ms
	printf("%d\n",d[n]); 
	return 0;
}

```   

	2.spfa
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define N 50010
#define M 100010 
using namespace std;
int n,m,d[N],tot,head[N];
bool vis[N];
struct Edge{
	int v,next,val;
}edge[M];
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
inline void add(int x,int y,int z){edge[++tot].v=y;edge[tot].next=head[x];edge[tot].val=z;head[x]=tot;}
void spfa(int x){
	queue<int >q;
	memset(d,0x3f,sizeof(d));
	q.push(x);d[x]=0;vis[x]=1;
	while(q.size()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].v,z=edge[i].val;
			if(d[v]>d[u]+z){
				d[v]=d[u]+z;
				if(!vis[v])q.push(v),vis[v]=1;
			}
		}
	} 
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		add(x,y,z); add(y,x,z);
	}
	spfa(1);
	printf("%d\n",d[n]);   //1163 ms
	return 0;
}

```




---

## 作者：Exschawasion (赞：1)

这篇题解主要是各种主流最短路算法的测评以及优劣分析，最短路算法是图论中比较基础的内容，这里就不对原理展开具体叙述了。

首先，让我们来简单的把这道题的题意复述一遍（英语不好的 OIer 看过来）：

- 首先起点是 $1$，结束点是 $N$；
- 每条路上都有一定数量的奶牛；
- 从起点走到终点，求怎么走能够使经过的路上的奶牛数量最少。

结论：这道题求的是一个无向图的最短路。


如果要论简单性，首选 Floyd 算法：

```
void floyd() {
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			}
		}
	}
}
```
且不提时间复杂度 $O(n^3)$ 能不能过，光这个空间就已经超了。事实上，在本人的机器上连编译都编不了，因为过于开的数组庞大。

虽然 Floyd 过不了，但我们可以从这个错误的解法中发现两点：

- 开不了邻接矩阵，空间会超过限制；

- 时间复杂度过高。

所以我们只能开邻接表。那么让我们来看看这道题的数据范围：$ n \leq 50000$，$ m \leq 50000$。

最短路中的堆优化 Dijkstra 算法，时间复杂度为 $O((M + N) logN)$，在可以接受的范围内。关键代码如下：


```
struct Pair {
	int first, second;
	Pair(int f, int s) : first(f), second(s) {}
};

bool operator < (Pair a, Pair b) { return a.first > b.first; }

void dijkstra() {
	priority_queue<Pair> Q;
	memset(d, 0x3f, sizeof(d));
	memset(vis, false, sizeof(vis));
	Q.push(Pair(0, 1)), d[1] = 1;
	while(!Q.empty()) {
		Pair pair = Q.top(); Q.pop();
		int x = pair.second;
		if(!vis[x]) {
			vis[x] = true;
			for(int i = head[x]; i; i = next[i]) {
				int to = ver[i], len = w[i];
				if(d[to] > d[x] + len) {
					d[to] = d[x] + len;
					Q.push(Pair(d[to], to));
				}
			}
		}
	}
}
```

我们还可以使用队列优化的 Bellman-Ford 算法（另称 SPFA），关键代码：

```
void spfa() {
	memset(d, 0x3f, sizeof(d));
	memset(vis, false, sizeof(vis));
	d[1] = 0, vis[1] = true;
	queue<int> Q;
	Q.push(1);
	while(!Q.empty()) {
		int x = Q.front(); Q.pop();
		vis[x] = false;
		for(int i = head[x]; i; i = next[i]) {
			int to = ver[i], len = w[i];
			if(d[to] > d[x] + len) {
				d[to] = d[x] + len;
				if(!vis[to]) Q.push(to), vis[to] = true;
			}
		}
	}
}
```
在一般情况下，SPFA 算法时间复杂度为 $O(kM)$，其中 $k$ 是一个常数。

这对于普通的题目来说已经足够快了。但是有些题目会故意用类似**网格图**的特殊数据等来**卡 SPFA**，有时候时间复杂度甚至不如优化的 Dijkstra 算法。

总结一下：

| 算法|时间复杂度|  优点| 缺点|
| :----------: | :----------: |:----------: |:----------: |:----------: |
| Floyd | $O(N^3)$ |代码量小 |时间空间复杂度高|
| Dijkstra |$O(N^2)$ | 代码量较小 |时间复杂度较高，无法处理负边 | TLE|
|Bellman Ford|$O(NM)$|泛用性好，能处理负边|时间复杂度较高|
|优化 Dijkstra|$O((N+M)logN)$|速度较快|无法处理负边|$172ms$|
|SPFA|平均情况$O(kM)$ 最坏 $O(NM)$|速度较快，能处理负边|代码量略大，可能会被卡掉|

SPFA 算法表现确实不错，但是如果真的采用了 SPFA ，那就得承担相应的被卡掉的风险。

所以本人认为，在比赛中尽量使用优化的 Dijkstra 的算法，除非出现负边否则不使用 SPFA。

下面是完整的 AC 代码：


```
#include <bits/stdc++.h>

using namespace std;

int tot;
const int maxn = 200000 + 5;
int head[maxn];
int next[maxn];
int w[maxn];
int ver[maxn];

void add(int x, int y, int v) {
	tot++, w[tot] = v, ver[tot] = y, next[tot] = head[x], head[x] = tot; 
}

int d[maxn];
bool vis[maxn];


void spfa() {
	memset(d, 0x3f, sizeof(d));
	memset(vis, false, sizeof(vis));
	d[1] = 0, vis[1] = true;
	queue<int> Q;
	Q.push(1);
	while(!Q.empty()) {
		int x = Q.front(); Q.pop();
		vis[x] = false;
		for(int i = head[x]; i; i = next[i]) {
			int to = ver[i], len = w[i];
			if(d[to] > d[x] + len) {
				d[to] = d[x] + len;
				if(!vis[to]) Q.push(to), vis[to] = true;
			}
		}
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
	spfa();
	printf("%d", d[n]);
	return 0;
}
```
（水平有限，如有错漏，恳请原谅。）

Remember to leave a like!

求通过~

---

## 作者：Chavapa (赞：1)

### 第一次写题解祭
# 此题为一道典型的最短路模版题

由于数据范围<=50000，故考虑采用**SPFA算法**。

关于SPFA算法不再赘述，这里值得提一点的是对于数组邻接表的**空间优化**。

倘若采用朴素的邻接表存储邻边，则空间复杂度 50000*50000，必炸无疑。

我们考虑将二维压成一维。



设c[i] 表示 结点i位于第几条邻边

  suc[i] 表示 第i条邻边的后继结点（如果x，y两点间存在从x到y的有向边，则suc[i]=y）
  
  last[i] 表示 当前邻边的上一条邻边编号
  
  len[i] 表示 第i条邻边长度
  
  
  这样，我们便可以很方便地调用每一条邻边。
  
  具体见代码：
  ```pascal
var n,m,i,t,w,cnt,x,y,z:longint;
    suc,last,c,len,f,sq:array[1..5000000] of longint;  //注意数据范围，太小会TLE（莫名其妙？？），太大会爆内存
  procedure addedge(x,y,z:longint);  //连边，从结点x到结点y的长度为z的有向边
  begin
    inc(cnt); suc[cnt]:=y; last[cnt]:=c[x]; c[x]:=cnt; len[cnt]:=z;
  end;
begin
  readln(n,m);
  for i:=1 to m do
  begin
    readln(x,y,z); addedge(x,y,z); addedge(y,x,z);  //由于为双向边，故连边两次
  end;
  t:=1; w:=1;
  fillchar(f,sizeof(f),63);  //最短路数组初始化
  f[1]:=0; sq[1]:=1;  //1号结点入队列，最短路初始为0
  while t<=w do
  begin
    i:=c[sq[t]];  //取出当前头结点所在的邻边编号
    while i>0 do  //当该条邻边存在时
    begin
      if f[sq[t]]+len[i]<f[suc[i]] then  //如果对于结点suc[i]存在一条更短的路径，则松弛此结点
      begin
        inc(w); sq[w]:=suc[i]; f[suc[i]]:=f[sq[t]]+len[i];  //该结点入队尾，同时答案更新
      end;
      i:=last[i];  //取该边的上一条边
    end;
    inc(t);
  end;
  writeln(f[n]);  //f[n]存放从结点1至结点n的最短路，即为所求
end.
```

---

## 作者：夢·壹生所愛 (赞：1)

这道题是一篇很裸的最短路问题；

思路：SPFA，直接跑出终点的值即可;

**上代码**
```
#include<cstdio>
#include<queue>
using namespace std;
int u,v,w;
struct node
{
	int to,next,w;
}edge[100010];
int k;
int head[100100];
int dist[100100];
void adde(int u,int v,int w)
{
	edge[++k].to=v;
	edge[k].next=head[u];
	edge[k].w=w;
	head[u]=k;
}
bool book[101000];
queue<int> q;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);//建图 
		adde(u,v,w);
		adde(v,u,w);//要建双边 
	}
	for(int i=1;i<=n;i++)
	dist[i]=0x7f7f7f7f;//初始化为无限大 
	q.push(1);//起点入队 
	book[1]=true;
	dist[1]=0;
	while(!q.empty())
	{
		int mb=q.front();//取出队列里的点 
		q.pop();//记得pop 
		for(int i=head[mb];i;i=edge[i].next)//便利 
		{
			int rp=edge[i].to;
			if(dist[rp]>dist[mb]+edge[i].w)//松弛 
			{
				dist[rp]=dist[mb]+edge[i].w;
				if(book[rp]==false)
				q.push(rp);
			}
		}
	}
	printf("%d",dist[n]);
	return 0;
}
```

---

## 作者：Leap_Frog (赞：0)

### PS.
我震惊了  
~~（此处开头吸引读者注意力，引出后文我的震惊~~  
这题实在太神奇了，所以过来写一篇题解。  
来分享一下自己这离谱的经历。  

### Problem.
首先看到这道题。  
这不就是一个单源最短路吗。。。  

### Solution.
详情可以看[P4779](https://www.luogu.com.cn/problem/P4779)  
首先，此题一看这个数据范围，就感觉有点危险。  
于是打了一个Dijkstra。  
然后一交：我就像雷峰塔倒掉一样被雷倒了  
~~（此处用了比喻，使文章趣味性更强，更生动形象地写出了我的震惊~~  
![](https://cdn.luogu.com.cn/upload/image_hosting/ec3re3u6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
我的天呐，竟然TLE了！  
于是，我调啊调啊调啊调啊调啊调啊调啊调啊调啊调啊调啊调啊……  
~~（此处用了反复的修辞手法，生动形象地写出我调代码的艰辛~~  
最后竟然发现，我犯了个如此sb的错误。  
我把题目中要求的单源最短路求成了单源最长路。  
然后改掉之后，发现竟然
![](https://cdn.luogu.com.cn/upload/image_hosting/vcuhuv6x.png)
AC了。。。  

我的天呐，把最短路求成最长路还能AC&TLE而不WA？？？  
~~（此处省略我的抱怨10000字~~  

### Coding.
顺便提供一个不同码风的题解QAQ。  
```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge{int to,w,nxt;}e[50005<<1];
//边
struct node{int x,w;bool operator<(node b) const {return w>b.w;}};
//Heap的结构体
int tot=0,n,m,head[50005],dis[50005];priority_queue<node>q;
//一大堆定义，我习惯priority_queue定义成全局的
inline void adde(int x,int y,int w) {e[++tot]=(edge){y,w,head[x]},head[x]=tot;}
//加边
inline void dij(int s,int t)
{
	memset(dis,0x3f,sizeof(dis)),q.push((node){s,0}),dis[s]=0;
//一大堆初始化，正常来说这里应该要加初始化priority_queue
	while(!q.empty())
	{
		int x=q.top().x,w=q.top().w;q.pop();if(dis[x]<w) continue;
//取出堆顶
		for(int i=head[x];i;i=e[i].nxt)
			if(dis[e[i].to]>dis[x]+e[i].w)
				dis[e[i].to]=dis[x]+e[i].w,q.push((node){e[i].to,dis[e[i].to]});
//向外扩展，更新最小值
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x,y,w;i<=m;i++) scanf("%d%d%d",&x,&y,&w),adde(x,y,w),adde(y,x,w);
//读入
	return dij(1,n),printf("%d\n",dis[n]),0;
//输出答案并返回
}
```

---

## 作者：Meatherm (赞：0)

这道题目SPFA并不会被卡死，但是用dijkstra+堆优化很大概更快。其他的就是模板了，这里不在阐述。不会的可以参考【模板】单源最短路径（标准版）的题解。并且我的博客里面也有相应的文章，例如香甜的黄油那道题目。


然后实在没有什么可以讲的东西。

```
# include <bits/stdc++.h>
# define rr register
const int N=50010;
bool c[N]; //标记最短路是否确定
int dis[N]; //记录1到每个点的最短路
struct Edge
{
    int to,next,v;
}edge[N<<1]; //邻接表
int sum; //邻接表附属部分
int head[N]; //同上
int n,m; //点数和边数
struct node
{
    int id,w;
};//堆优
bool operator < (node a,node b)
{
    return a.w>b.w; 
} //重载运算符。因为优先队列默认重大到小，所以要反过来
std::priority_queue <node> k; //定义优先队列（堆的STL版本）
inline void add(int x,int y,int z)
{
    edge[++sum].to=y;
    edge[sum].next=head[x];
    edge[sum].v=z;
    head[x]=sum;
    return;
} //建边
inline int read(void)//快读
{
    int res,f=1;
    char c;
    while((c=getchar())<'0'||c>'9')
        if(c=='-')f=-1;
    res=c-48;
    while((c=getchar())>='0'&&c<='9')
        res=res*10+c-48;
    return res*f;		
}
inline void dijkstra(void); //定义最短路函数
int main()
{
    n=read();
    m=read();
    for(rr int i=1,x,y,z;i<=m;++i)
    {
        x=read(),y=read(),z=read();
        add(x,y,z);
        add(y,x,z);
    }
    memset(dis,0x3f3f3f3f,sizeof(dis));
    dis[1]=0; //记得这里要把起点的最短路设成0
    dijkstra();//跑最短路板子
    printf("%d",dis[n]);
    return 0;
}
inline void dijkstra(void) //模板 实在没有什么好说的。
{
    k.push((node){1,0});
    while(!k.empty())
    {
        node tmp=k.top();
        k.pop();
        int i=tmp.id;
        c[i]=true;
        for(rr int j=head[i];j;j=edge[j].next)
            if(!c[edge[j].to]&&dis[i]+edge[j].v<dis[edge[j].to])
            {
                dis[edge[j].to]=dis[i]+edge[j].v;
                k.push((node){edge[j].to,dis[edge[j].to]});
            }
    }
    return;
}
```

---

