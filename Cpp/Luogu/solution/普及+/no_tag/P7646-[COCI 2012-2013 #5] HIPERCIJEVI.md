# [COCI 2012/2013 #5] HIPERCIJEVI

## 题目描述

在遥远的星系中，最快的运输方式是超级管道，它们将 $K$ 个站台连接在一起。从站台 $1$ 到达站台 $N$ 最少需要经过多少个站台?

## 说明/提示

**【样例解释#1】**

有两种方法从站台 $1$ 走到站台 $9$：

$1\Rightarrow 3\Rightarrow 6\Rightarrow 9$ 或 $1\Rightarrow 5\Rightarrow 6\Rightarrow 9$

共经过了 $4$ 个站台，可以证明这是经过站台最少的情况。


------------

**【数据范围】**

对于 $100\%$ 的数据，$1\le N\le 10^5$，$1\le K,M\le 1000$。


------------

**【说明】**

本题分值按 COCI 原题设置，满分 $120$。

题目译自 [COCI2012~2013](https://hsin.hr/coci/archive/2012_2013/) [CONTEST#5](https://hsin.hr/coci/archive/2012_2013/contest5_tasks.pdf) _**T4 HIPERCIJEVI**_。

## 样例 #1

### 输入

```
9 3 5
1 2 3
1 4 5
3 6 7
5 6 7
6 8 9```

### 输出

```
4```

## 样例 #2

### 输入

```
15 8 4
11 12 8 14 13 6 10 7
1 5 8 12 13 6 2 4
10 15 4 5 9 8 14 12
11 12 14 3 5 6 1 13```

### 输出

```
3```

# 题解

## 作者：Unordered_OIer (赞：4)

# P7646 题解
## Description
一根超级管道能够将 $K$ 个站台连接在一起。求从站台 $1$ 到达站台 $N$ 最少需要经过多少个站台。

## Solution
最短路裸题。

考虑将一根所谓的 $m$ 个“超级管道”变成 $m$ 个连接了 $k$ 个点的点，那么转化之后就是裸的最短路问题了。

看到目前为止其他两篇题解讲的答案需要 `dis[n]/2+1` 都不是很清楚，这里再讲一遍：

先看一下一个“超级管道”连接 $2$ 个点的情况，根据题意我们显然可以看作：

![](https://cdn.luogu.com.cn/upload/image_hosting/1t0m76yy.png)

但是，照着我们的思路，我们会把它变成：

![](https://cdn.luogu.com.cn/upload/image_hosting/ew8mt0z6.png)

原本 $1 \rightarrow 2$ 的路径会被拆成 $1 \rightarrow 3 \rightarrow 2$，也就是说我们求出的最短路径实际上是原来的 $2$ 倍。如果把 $1 \rightarrow n$ 的最短路记作 $dis[n]$，那么原来的最短路径就是 $\dfrac{dis[n]}{2}$。

因为要求的是点数，所以答案是 $\dfrac{dis[n]}{2}+1$。

最后的话这题卡空间**不能开 long long**，开了 long long 你就会和我一样提交了若干遍最后两个点 $\color{white}\colorbox{#052242}{MLE}$。

## Code

```cpp
inline void bfs(){
	memset(dst,-1,sizeof dst);
	queue<int> q;dst[1]=1;
	q.push(1);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=hd[u];i;i=es[i].nxt){
			int v=es[i].to;
			if(dst[v]==-1){
				dst[v]=dst[u]+1;
				q.push(v);
			}
		}
	}
}
int main(){
	n=read(),k=read(),m=read();
	for(int i=1;i<=m;i++)
		for(int j=1;j<=k;j++){
			int x=read();
			add(n+i,x),add(x,n+i);
		}
	bfs();
	writeln(dst[n]==-1?-1:dst[n]/2+1);
	return 0;
}
```

---

## 作者：mbzdf (赞：2)

# P7646 题解

[传送门](https://www.luogu.com.cn/problem/P7646)

## 题目大意
> 管道能够将 $k$ 个站台连接在一起。求从站台 $1$ 到达站台 $n$ 最少需要经过多少个站台。

## 分析一下

看到这道题第一时间想到**最短路**，但是如果我们给一个管道的每个点都互相建一个边，那时间复杂度就是 $O(mk^2)$，在 $m = k = 10^3$ 的情况下，总体时间复杂度为 $10^9$，严重超标。

换一种思路，如果**将管道也视为一个点**，那么我们只需要给每个站台与管道之间建边，那么总体时间复杂度就减少到了 $O(mk)$，可以通过。

#### 那么具体思路呢

为每一个点与管道建边，再使用 Dijkstra 算法，最后将答案输出。

### 三个需要注意的事情

> 内存限制：**32MB**

用指针链式前向星的同学，注意了。使用**指针**很可能会 MLE，建议使用数组模拟链表。

---

我们把点与管道，管道与点之间建边，每边长为 $1$，会导致结果为答案的两倍，需要将结果**缩小一倍**。

---

>## 输出格式
>一行，一个正整数，表示最少需要经过的站台数，如果到达不了站台 $N$，则输出 `-1`。

因为是最少**经过**的站台数，所以起点也算在内，那么我们需要再将结果**增加 $1$**，才是正确答案。

## AC 代码
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
void read(int &x)
{
	char v = getchar(); bool f = 0; x = 0;
	while((v < '0' || v > '9') && v != '-') v = getchar();
	v == '-' ? f = 1 : x = v & 15; v = getchar();
	while(v >= '0' && v <= '9') x = (x << 3) + (x << 1) + (v & 15), v = getchar();
	if(f) x = -x;
}
struct point
{
	int to;
	int l;
	bool operator < (point x)
	{
		return l < x.l;
	}
	bool operator >= (point x)
	{
		return l >= x.l;
	}
};
struct node
{
	int to;
	int next;
}li[2000005];
int head[101005];
int nr = 0;
void add(int go, int to)
{
	int p = ++nr;
	li[p].to = to;
	li[p].next = head[go], head[go] = p;
}
struct heap
{
	int r = 0;
	point g[1000005];
	bool empty()
	{
		return r == 0;
	}
	void add(point x)
	{
		g[++r] = x;
		int i = r;
		while(i > 1)
		{
			if(g[i >> 1] < g[i]) break;
			swap(g[i >> 1], g[i]);
			i >>= 1;
		}
	}
	void add(int to, int l)
	{
		point x;
		x.to = to, x.l = l;
		add(x);
	}
	point pop()
	{
		point v = g[1];
		g[1] = g[r--];
		int i = 1;
		while(i << 1 <= r)
		{
			int son = i << 1;
			if(son < r && g[son + 1] < g[son]) ++son;
			if(g[son] >= g[i]) break;
			swap(g[i], g[son]);
			i = son;
		}
		return v;
	}
}h;
int dis[101005];
bool vis[101005];
int n, k, m;
void dijkstra(int s)
{
	for(int i = 1; i <= 101000; ++i)
		dis[i] = 0x3fffffff,
		vis[i] = 0;
	dis[s] = 0;
	h.add(s, 0);
	while(!h.empty())
	{
		int x = h.pop().to;
		if(vis[x]) continue;
		vis[x] = 1;
		for(int p = head[x]; p != 0; p = li[p].next)
		{
			int y = li[p].to;
			if(dis[y] > dis[x] + 1)
			{
				dis[y] = dis[x] + 1;
				h.add(y, dis[y]);
			}
		}
	}
	return;
}
int main()
{
	cin >> n >> k >> m;
	for(int i = 1; i <= m; ++i)
	{
		int y = i + 100000;
		for(int j = 1; j <= k; ++j)
		{
			int x;
			read(x);
			add(x, y);
			add(y, x);
		}
	}
	dijkstra(1);
	if(dis[n] == 0x3fffffff)
		cout << -1 << endl;
	else
		cout << dis[n] / 2 + 1 << endl;
	return 0;
}
```

---

## 作者：2021changqing52 (赞：1)

# 思路：
朴素的连边方法就是对于两个在一条管道的点进行建边，但很明显空间时间都会炸掉。

应该**把一根管子表示成一个点，每个与这根管子相连的站台与这个点连边**，这样复杂度大大降低。再跑一遍单源最短路（BFS 也可以）就行了。注意答案应是**最短路除以二加一**，因为两点走的边要经过虚拟点，总边数是实际边数的两倍，而且题目求的是点数，点数是边数加一（小学植树问题）。
# Code：
```cpp
#include<bits/stdc++.h>
#define INF 0x7f7f7f7f
#define N 500005
using namespace std;
int vis[N],dis[N],n,k,m;
vector<int>g[N];
int main(){
	cin>>n>>k>>m;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=k;j++){
			int v;
			cin>>v;
			g[n+i].push_back(v);//把每根管子表示成一个点
			g[v].push_back(n+i);
		}
	queue<int>q;//BFS，也可以是最短路
	memset(dis,0x7f,sizeof dis);
	q.push(1),vis[1]=1,dis[1]=1;
	while(!q.empty()){
		int t=q.front();q.pop();
		if(t==n)break;
		for(int i=0;i<g[t].size();i++){
			int p=g[t][i];
			if(!vis[p]){
				vis[p]=1,dis[p]=dis[t]+1;
				q.push(g[t][i]);	
			}
		}	
	}
	if(dis[n]==INF)cout<<-1;//无解的情况
	else cout<<dis[n]/2+1;//最短路/2+1
	return 0;
}
```


---

## 作者：white_carton (赞：0)

[更好的阅读体验](https://starback24.github.io)

[题目链接](https://www.luogu.com.cn/problem/P7646)

### 分析

一道最短路板子题。

首先看起来把一条管道上的每两个点之间都建一条边再做一遍最短路就过了，但是仔细一想，就算不看加边的过程，极端情况下，边的总数会达到恐怖的 $N^2$，这是我们无法忍受的。

这时我们换一种思路，把管道也视为一个点，在一条管道上的点全都连一条向管道的边，这时最大总边数也就是 $mk$，显然是可以通过的。

若建图时将每条边的长度都设为 $1$，原题中通过一次管道在程序中就会计算为**从出发点到管道的一次**和**从管道到终点的一次**，因此， $\frac{dis[n]}{2}$ 即为经过的边数，又因为原题要求经过站点数，因此再加上 $1$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define endl '\n'
#define inf 0x3f3f3f3f
#define mkp make_pair
#define pb push_back
#define fir first
#define sec second
#define pii pair<int,int>
#define eb emplace_back
#define file(filename) freopen(filename".in","r",stdin);freopen(filename".out","w",stdout);
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Dor(i,a,b) for(int i=a;i>=b;i--)
//==============================================================================================
// Fast IO

template<typename T>
inline void read(T &a){
	T f=1,c=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(isdigit(ch)){
		c=(c<<1)+(c<<3)+(ch^48);
		ch=getchar();
	}
	a=f*c;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){
	read(x),read(args...);
}

//=============================================================================================
//code here
int n,k,m,x;
struct edge{
	int nxt,to;
}e[2001000];
int head[2001000],cnt,dis[2001000];
void add(int u,int v){
	e[++cnt]={head[u],v};
	head[u]=cnt;
}
void bfs(){
	memset(dis,-1,sizeof(dis));
	queue<int> q;
	q.push(1);
	dis[1]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int to=e[i].to;
			if(dis[to]==-1){
				dis[to]=dis[u]+1;
				q.push(to);
			}
		}
	}
}
signed main(){
	cin>>n>>k>>m;
	For(i,1,m){
		For(j,1,k){
			cin>>x;
			add(i+n,x);
			add(x,i+n);
		}
	}
	bfs();
	cout<<((dis[n]==-1)?-1:(dis[n]/2+1))<<endl;
}
```

---

## 作者：xyzcoolplayer (赞：0)

## [COCI2012-2013#5] HIPERCIJEVI 题解
### 众所周知（题意）
这是一道求最短路的题，重点是在空间限制（MLE）和输入的时间复杂度（TLE）中容易爆。
### 思路
在空间复杂度上，可以用邻接表来取代邻接矩阵，使空间复杂度降低，在输入时间复杂度上，可以把一条通道看成一个节点（注意把邻接表的空间大小改成 $101005$，否则 RE )，加到数组里，在通道和通道连接的节点间建一条边，最后用 dijkstra 或者 BFS 就行了。

### 下面附上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,nk,kk;
int inf = 1e9 + 7 ;
struct node {
	int id, num;
};
bool operator <(node a, node b) {
	return a.num > b.num;
}
vector<int> a[101005];
priority_queue<node> path;
int main(){
	cin>>n>>m>>k;
	nk=n+1;
	kk=n+k;
	for(int i=nk;i<kk;i++){
		for(int j=0;j<m;j++){
			int x;
			cin>>x;
			a[i-1].push_back(x-1);
			a[x-1].push_back(i-1);
		}
	}
	int bp = 0;
	cout<<a[bp].size();
	for(int i=0;i<a[bp].size();i++){//本人用的dijkstra
		if (a[bp][i])
			path.push({i, a[bp][i]});
	}
	while(path.size()) {
		int mn2 = path.top().id;
		int cp = path.top().id;
		for (int i = 0; i < n; i++) {
			if (a[bp][cp] + a[cp][i] < a[bp][i]) {
				a[bp][i] = a[bp][cp] + a[cp][i];
				path.push({i, a[bp][i]});
			}
		}
		path.pop();
	}
	cout<<a[bp][n-1];
	return 0;
}

```
完美收尾！(^o^)

---

## 作者：_zexal_ (赞：0)

考虑这种求至少，最小的，优先考虑最短路。注意到 $K \leq 1000$ 和 $M \leq 1000$ 的情况下。直接对于每一个点都和他能到达的所有边都建图空间为 $k^2\times m$ 肯定超了。所以，需要优化。让我们继续深挖题目性质，同一个管道内能到达的所有点花费都相同，所以，对于每一个管道建一个假点，就可以得到每个点都建边同样的效果，空间复杂度优化为 $m\times k$ 的大小，挺好的。把同一个管道的搞在一起，对假点建图跑最短路即可。

---

## 作者：caohan (赞：0)

# 思路

朴素的连边方法就是对于两个在一条管道的点进行建边。很明显的会炸掉空间。

复杂度 $2 \times m \times n^2=2 \times 10^9$。

正确的方法是新建一个假的点，把同一管道的点都连到这个假点上，这样就能满足题目要求。新建假点时，在 $[\ n,+\infty)$ 去新建即可。

复杂度 $2 \times m \times n=2 \times 10^6$.

剩下的就是一个单元最短路了。

不过注意，因为所采用的方法的限制，最后的答案应该为 $\frac{dis_n}{2}+1$ 。因为从同一管道中的一个点到另一个，题目中是一条边，我们是两条边。并且最短路是算边数，题目要求是点数，是双端植树 $+1$ 即可。

# 代码

```cpp
#include<bits/stdc++.h>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k,m;
int v[500000];
int d[500000];
vector<int> g[500005];
queue<int> q;
void bfs()
{
	memset(d,0x7f,sizeof(d));
	q.push(1);
	v[1]=1;
	d[1]=1;
	int now;
	while(q.size())
	{
		now=q.front();
		q.pop();
		if(now==n)
		{
			break;
		}
		for(int i=0;i<g[now].size();i++)
		{
			if(!v[g[now][i]])
			{
				v[g[now][i]]=1;
				d[g[now][i]]=d[now]+1;
				q.push(g[now][i]);
				
			}
		}
	}
}//bfs最短路
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>k>>m;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=k;j++)
		{
			int v;
			cin>>v;
			g[n+i].push_back(v);
			g[v].push_back(n+i);//建一个假点
		}
	}
	bfs();
	if(d[n]==0x7f7f7f7f)
	{
		cout<<-1;
	}
	else
	{
		cout<<(d[n]/2)+1;
	}//输出
}
```


---

## 作者：Undead2008 (赞：0)

本篇题解的解题思路为使用单源最短路。
### 解题思路
本题和一般最短路问题的最大不同在于“超级管道”的出现。如果将“超级管道”中的点两两连边，边数会达到 $1e9$，显然会爆内存。考虑对于每条管道新建一个结点，从该点向管道中各点连无向边。这样从管道中每个点都可以通过该点而到达管道中另外一个点。新建的点的下标肯定会大于 $n$，所以可以很轻易的辨识哪些点是我们新建的。因为要求的是最少经过几个站台，所以最后跑最短路即可。
### AC代码
下面贴出**核心**代码，以引出下一段讲解。

```cpp
//核心代码如下
void dijkstra(){//朴素最短路 
	memset(dis,114514,sizeof(dis));
	dis[1]=1;q.push(node{1,1});
	//起点也得算上 
	while(q.size()){
		node t_=q.top();q.pop();
		int x=t_.p;
		if(vis[x])continue;
		vis[x]=1;
		for(int i=0;i<l[x].size();i++){
			int to=l[x][i];
			if(dis[to]>dis[x]+(to<=n)){
				dis[to]=dis[x]+(to<=n);//←Why?
				if(!vis[to])
					q.push(node{dis[to],to});
			}
		}
	} 
}
int main(){
	for(int i=1;i<=m;i++)
		for(int j=1,t;j<=k;j++){
			cin>>t;
            //建边操作
			l[t].push_back(i+n);
			l[i+n].push_back(t);
		}
}
```
注意到这段代码的第 $13(14?)$ 行被打上了 `Why?` 的注释。该语句是本篇题解讲解的重点。这是因为由题意从原有的点走到另一个未经过的原有的的点会将该点标记为已经经过，边权为 $1$，所以我们假设从原有的点走到通道新建的点的边权为 $0$（因为走到通道新建的点不计入到答案内），从通道新建的点走到一个原有的未经过点的边权为 $1$ （因为走到已给出的未经过的点需要计入到答案内），原有的点下标是 $\le n$ 的，所以如果该点下标 $\le n$，就计入到答案，就有了这条语句。
### 时间复杂度
建边之后有 $n+m$ 个点，$mk$ 条无向边（$2mk$ 条边），所以该做法的时间复杂度为 $\Theta\small(mk\log(n+m))$。

---

## 作者：Otomachi_Una_ (赞：0)

把一根管子想象成一个额外点，每个与这根管子相连的站台与这个点连边，从起点开始跑一边最短路（甚至可以是 BFS）最终跑到 $N$ 站台的最短路除 $2$ 加 $1$ 即为答案。

另外，我的代码被被卡内存，仅低于最高内存 $0.25$ MB。

上代码：

```cpp
#include<iostream>
#include<queue>
using namespace std;
const int MAXN=101005;
const int MR=1e3+5;
int n,m,k;
bool f[MAXN];
queue<pair<int,int> > Q;
struct node{
	int from,to,next;
}line[MR*MR*2];
int last[MAXN];
int cnt=0;
void add(int u,int v){
	++cnt;
	line[cnt].from=u;
	line[cnt].to=v;
	line[cnt].next=last[u];
	last[u]=cnt;
}
int main(){
	cin>>n>>k>>m;
	for(int i=1;i<=m;i++){
		int where;
		for(int j=1;j<=k;j++){
			cin>>where;
			add(where,n+i);
			add(n+i,where);
		}
	}
	Q.push(make_pair(0,1));
	while(!Q.empty()){
		int step=Q.front().first,res=Q.front().second;
		Q.pop();
		if(f[res])
			continue;
		if(res==n){
			cout<<step/2+1;
			return 0;
		}
		f[res]=true;
		for(int i=last[res];i;i=line[i].next)
		    if(!f[line[i].to])
			Q.push(make_pair(step+1,line[i].to));
	}
	cout<<"-1";
	return 0;
}

```


---

## 作者：Mu_leaf (赞：0)


## [思路]
仔细阅读题目以后，发现唯一的难题就是每根超级管道所连接的站点。

于是，我们可以想到将每根超级管道看作是额外的点即可。此时数组大小需要开到 $10^5+10^3$。

同时，我们需要处理最后的输出。

可以发现在题目中 $1 \rightarrow 2$ 的路径，按照我们的思路变成了 
$1 \rightarrow 3 \rightarrow 2$ 可以发现走过的边数是原来的 $2$ 倍。

所以走过的边数就是 $\dfrac{\mathit{dis}_{n}}{2}$。

但是，这是对的吗？

仔细观察题目，发现要求的是点数，而不是走过的边数。

怎么求点数呢？小学植树问题都学过吧，求出来的最短路径就可以看作是双端植树问题。

所以，答案就变成了 $\dfrac{\mathit{dis}_{n}}{2}+1$。

到这里，一道绿题就这样变成 bfs 板子了。

# Code:

```cpp
#include <bits/stdc++.h>

using namespace std;
int n,k,m;
int x,v;
bool vis[110005];
int dep[110005];
vector<int> V[110005];
queue<int> q;
void Bfs(){
	memset(dep,-1,sizeof(dep));
	q.push(1);
	vis[1]=1;
	dep[1]=1;
	while(!q.empty()){
		int now=q.front();
		q.pop();
		if(now==n) break;
		for(int i=0;i<V[now].size();i++){
			if(!vis[V[now][i]]){
				vis[V[now][i]]=1;
				dep[V[now][i]]=dep[now]+1;
				q.push(V[now][i]);
			}
		}
	}
}
int main(){
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=k;j++){
			scanf("%d",&v);
			V[n+i].push_back(v);
			V[v].push_back(n+i); 
		}
	}Bfs(); 
	printf("%d\n",dep[n]==-1?-1:dep[n]/2+1);
	return 0;
}
```
拜拜。

---

