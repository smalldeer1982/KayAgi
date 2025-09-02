# Dijkstra?

## 题目描述

给定一张无向有权图，请输出任意一条从 $1$ 到 $n$ 的最短路径。

## 样例 #1

### 输入

```
5 6
1 2 2
2 5 5
2 3 4
1 4 1
4 3 3
3 5 1
```

### 输出

```
1 4 3 5 ```

# 题解

## 作者：Yoo_ (赞：18)

**基本**和单源最短路是重题

[同时发表在本人博客园](https://www.cnblogs.com/j1yx/p/11066192.html)

因为题目中说了Dijkstra，干啥还用~~死了的SPFA?~~

估计用Floyd100%会挂...

那么就用堆优化的Dijkstra~~（迪杰克斯歘）~~

虽然我看题解区的确有Dijkstra了，但是没有介绍，我就发一篇吧，希望你们能从中获益QaQ

关于什么是Dijkstra?

[左转百度](https://baike.baidu.com/item/%E8%BF%AA%E6%9D%B0%E6%96%AF%E7%89%B9%E6%8B%89%E7%AE%97%E6%B3%95/4049057?fr=aladdin)

但是我自己都觉得那个讲的太复杂，就简单的讲一下吧

Dijkstra不会死去的条件：

该有权图不含负权边时间复杂度为O(n^2)

介绍一下：

Dijkstra类似于贪心

首先先确定一个源点（这里就是1号点），先把所有Dis(1,i)（i!=1）都定为INF，然后先遍历一遍，把与点1相连的点（即只用走一个连边）的点i的距离都第一次直接处理为Dis(1,i)

第二次遍历把与`Dis(1,i)<INF`的点有连接的点j的Dis处理为Dis(1,i,j)意为用i点的Dis来给j点附上Dis，可以说`Dis(1,j)=Dis(1,i)+Dis(i,j)；`

之后我们重复第二次的操作，不过这次会多一种情况，即用Dis(j)来处理Dis(i)，就是说这次遍历到j点的时候，如果有`Dis(1,j,i)<Dis(1,i)<INF`,我们就Dis(1,i)的值变为 `min(Dis(1,j),Dis(1,j)+Dis(j,i))`

遍历过后，如果仍有Dis(k)=INF的话，就证明点1无法到点k，所以我们只需要输出`-1`就可以了

那么什么是堆优化Dijkstra呢？

每次扩展一个距离最小的点，再更新与其相邻的点的距离。
如何寻找距离最小的点？
优化方案是建一个小根堆，小根堆里存储由当前结点更新距离的所有点，那么堆顶就是距离最小的点

建一个小根堆，用来存储结点的序号，用一个数组来存储第i个结点在堆中的位置，用一个标记数组来记录结点是否在堆中

对于小根堆的操作还是基本的put() 和get() ，但由于有的结点已经在堆中了，所以可以把put() 拆为插入堆和调整位置两个部分

```
1.将与源点相邻的点进行松弛操作后加入堆
2.取出位于堆顶的结点
3.若取出的点为终点，则结束算法
4.将与当前结点相邻的点进行松弛操作
(1)如果该点已经在堆中，就调整在堆中的位置
(2)如果该点不在堆中，就加入堆
```

代码如下

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;
const int MAXN = 1e5 + 10;
const ll INF = 1ll<<62;
vector<int>e[MAXN];
vector<int>w[MAXN];
bool vis[MAXN];
ll d[MAXN];
int pre[MAXN];
int n;

struct Node {
	ll d;
	int u;
	bool operator < (const Node & rhs) const {
		return d > rhs.d;
	}
};

void Dijkstra() {
	priority_queue<Node>q;
	for( int i=1; i<=n; i++ ) d[i] = INF;
	d[1] = 0;
	memset(vis, 0, sizeof(vis));
	Node tn;
	tn.d = 0, tn.u = 1;
	q.push(tn);
	while(!q.empty()) {
		Node t = q.top();
		q.pop();
		int u = t.u;
		if(vis[u]) continue;
		vis[u] = true;
		for( int i=0; i<e[u].size(); i++ ) {
			int v = e[u][i];
			if(d[v] > d[u] + w[u][i]) {
				d[v] = d[u] + w[u][i];
				pre[v] = u;
				tn.d = d[v], tn.u = v;
				q.push(tn);
			}
		}
	}
}

int main() {
	int m;
	while(scanf("%d%d", &n, &m) != EOF) {
		for( int i=1; i<=n; i++ ) e[i].clear(), w[i].clear();
		int a, b, c;
		for( int i=0; i<m; i++ ) {
			scanf("%d%d%d", &a, &b, &c);
			e[a].push_back(b);
			w[a].push_back(c);
			e[b].push_back(a);
			w[b].push_back(c);
		}
		Dijkstra();
		if(d[n] == INF) printf("-1\n");
		else {
			e[1].clear();
			e[1].push_back(n);
			while(pre[n] != 1) {
				n = pre[n];
				e[1].push_back(n);
			}
			e[1].push_back(1);
			for( int i=e[1].size()-1; i>0; i-- ) printf("%d ", e[1][i]);
			printf("%d\n", e[1][0]);
		}
	}
	return 0;
}
```


---

## 作者：MorsLin (赞：17)

- 刚开始看以为是最短路的模板题，就直接用堆优化dijkstra+输出路径搞了一波。结果十分惨烈……

这道题坑还是有的，比如：
- 边是双向边（这一点翻译没有很好的说明）
- 后边的数据大到要开long long

知道了这些后，这题就比较简单了，直接最短路+路径输出 就可以了

在下用的是堆优化dijkstra

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstdio>
using namespace std;
struct yyy{
    int f,
        t,
        len,
        nex;
}e[500100*2]; //前向星存图 
struct node{
    int x; long long y;
    bool operator < (const node& hhh) const{ return y>hhh.y; } //重载运算符实现小根堆 
}; 
priority_queue <node> q; //STL大法好 
int tot,head[100100];
void add(int x,int y,int z) //加边函数 
{
    e[++tot].f=x;
    e[tot].t=y;
    e[tot].len=z;
    e[tot].nex=head[x];
    head[x]=tot;
}
long long int dis[100100]; //一定要开long long 
int flag,ans[100100],pos[100100]; //存储路径 
int main()
{
    int n,m,s;
    cin>>n>>m; s=1;
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z); //双向边 
        add(y,x,z);
    }
    for(int i=1;i<=n;i++)
      dis[i]=9223372036854775806;
    dis[s]=0; ans[flag]=s;
    q.push(node{s,dis[s]});
    while(!q.empty())  //dijkstra主体 
    {
        node ww=q.top(); q.pop();
        int k=ww.x;
        if(ww.y!=dis[k]) continue;
        for(int j=head[k];j;j=e[j].nex)
          if(dis[e[j].t]>dis[k]+e[j].len)
          {
            dis[e[j].t]=dis[k]+e[j].len;
            q.push(node{e[j].t,dis[e[j].t]});
            pos[e[j].t]=k; //存储路径 
          }
    }
    bool flag2=1; //判断能否找到起点 
    for(int i=n;i;i=pos[i]) //到着从终点找回去
    {
        ans[++flag]=i;
        if(i==1) //如果找到起点，更改判断变量 
          flag2=0;
    }

    if(flag2){
        cout<<-1; return 0;
    } //没有找到起点，输出"-1"

    for(int i=flag;i>=1;i--) //因为是倒着找回去的，所以要倒序输出 
      cout<<ans[i]<<" ";
    return 0;
}
```

---

## 作者：houpingze (赞：16)

大家好，我是hpz，我非常喜欢暴力，所以我就用暴力通过了此题。

这一题裸暴力`dfs`想都别想，所以必须大力优化，本篇题解主要就是讲优化。

1. 记忆化。

这是比较常见的优化。

我们在`dfs`函数中，一般需要有$\text{n}$（当前节点编号），和$\text{w}$（目前走过的路径权值），我们可以定义一个一维数组$\text{f}$，其中$f_{i}$表示走到节点$\text{i}$目前所需要花费的时间。

那么在`dfs`过程中，我们可以剪个枝，如果$f_n \leq w$就直接跳出。


2. 如果当前的$\text{w}$已经比我们的当前答案$\text{ans}$要大，直接跳出。

3. 玄学优化

这一点要实现得用$\text{vector}$存图。

我们在每条边存完以后，对于每一个点，从这个点出发的所有边按照**节点编号**排序。

至于为什么……就是防止CF的毒瘤Hacker给了一大堆边，但其实有$1-n$的边，而且就是最短路径的情况。

然后就可以通过了。

[code](https://www.luogu.com.cn/paste/akrypxop)

---

## 作者：wally (赞：8)

## 思路：

由标题可得，用dijkstra

既然都用了dijkstra，不妨加上堆优化吧

再记录路径即可

## 特别注意：

1.dis的常数一定要开的够大，必须long long 本蒟蒻在#31卡了很久

2.路径个数不一定只有n个从#3开始就有大于n个了

3.注意没路径输出“-1”

上代码：
```cpp
#include<cstdio>
#include<queue>
#include<iostream>
#include<cstring>

using namespace std;

struct edge//链式前向星
{
	int to,next;
	long long val;
}g[500005];
int n,m;
long long dis[500005];
int vis[5000005];
int cnt;
int head[500005];
int road[500005];

void add(int a,int b,long long c)//链式前向星存图
{
	cnt++;
	g[cnt].to=b;
	g[cnt].val=c;
	g[cnt].next=head[a];
	head[a]=cnt;
}

struct Point//重构小根堆
{
	int num;
	long long dist;
	bool operator<(Point t) const
	{
		return dist>t.dist;
	}
};

priority_queue <Point> q;

void dijkstra()//dijkstra+堆优化
{
	Point tmp;
	tmp.num=1;
	tmp.dist=0;
	dis[1]=0;
	memset(vis,0,sizeof(vis));
	q.push(tmp);
	while(!q.empty())
	{
		Point u=q.top();
		q.pop();
		if(vis[u.num]==1)continue;
		vis[u.num]=1;
		for(int i=head[u.num];i!=0;i=g[i].next)
		{
			int v=g[i].to;
			if(dis[v]>dis[u.num]+g[i].val && vis[v]!=1)
			{
				road[v]=u.num;//记录路径
				dis[v]=dis[u.num]+g[i].val;
				tmp.num=v;
				tmp.dist=dis[v];
				q.push(tmp);
			}
		}
	}
}

int main(void)
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int x,y;
		long long z;
		scanf("%d%d%lld",&x,&y,&z);
		add(x,y,z);//双向
		add(y,x,z);
	}
	for(int i=1;i<=n;i++)dis[i]=9223372036854775806;//开大常数
	dijkstra();
	bool flag=1;
	for(int i=n;i!=0;i=road[i])if(i==1)flag=0;//判断是否有路径
	if(flag==1)
	{
		printf("-1");
		return 0;
	}
	else
	{
		vector<int> ans;//用vector存不定个数的路径
		for(int i=n;i!=0;i=road[i])ans.push_back(i);
		for(int i=ans.size()-1;i>=0;i--)printf("%d ",ans[i]);
	}
}
```

# AC通知书~~~

---

## 作者：Eason_AC (赞：6)

## Content
给定一张 $n$ 个点 $m$ 条边的无向图，请判断是否有一条可行的从 $1$ 到 $n$ 的路径，有的话输出长度最短的，没有的话输出 `-1`。

**数据范围：$2\leqslant n\leqslant 10^5$，$0\leqslant m\leqslant 10^5$，每条边的长度不超过 $10^6$。**
## Solution
这道题的标题当中看上去是在误导你不用 $\textsf{Dijkstra}$，其实已经给出了这道题目的做法就是：$\textsf{Dijkstra}$。为了优化复杂度，我用了堆优化 + $\textsf{Dijkstra}$。

那么 $\textsf{Dijkstra}$ 如何做到能够输出路径呢？这里我们就需要用到一个 $\textit{pre}$ 数组，其中 $\textit{pre}_i$ 表示最短路径中在 $i$ 点前面的点。我们可以在 $\textsf{Dijkstra}$ 处理 $\textit{dis}$ 数组的时候就把这个 $pre$ 更新一遍，就像这样：

```cpp
for(int i = h[x]; i; i = e[i].nxt) {
	int y = e[i].to, z = e[i].v;
	if(dis[y] > dis[x] + z) { //更新最短路
		dis[y] = dis[x] + z, pre[y] = x; //更新最短路的长度和当前点在最短路上的前一个节点。
		q.push(make_pair(-dis[y], y));
	}
}
```

那么我们又如何判断是否存在从 $1$ 到 $n$ 最短路径呢？这里给出两种方法：

第一种，还记得我们在跑 $\textsf{Dijkstra}$ 的时候要先做什么吗？没错，初始化 $\textit{dis}$ 数组。由于是最短路，我们需要将这个 $\textit{dis}$ 数组的初值设得尽可能大，又因为在数据范围中我们发现：

> $0\leqslant m\leqslant 10^5$，每条边的长度不超过 $10^6$。

所以我们就知道了，可能最长的最短路长度为 $10^5\times 10^6=10^{11}$，因此我们需要开 long long，并将这个 $\textit{dis}$ 数组赋初值赋在 $10^{11}$ 以上，下面这一段以笔者在代码中赋的初值 $10^{18}$ 为准。

然后我们就可以通过这个来判断是否存在到 $n$ 的最短路径了：只需要判断是否有 $\textit{dis}_n\neq10^{18}$ 即可，因为如果 $\textit{dis}_n=10^{18}$，那么就说明 $\textit{dis}_n$ 还从来没有更新过，自然也就不存在从 $1$ 到 $n$ 的最短路径了。

第二种，就要用到这一题中所引入的 $\textit{pre}$ 数组了，我们可以从 $n$ 开始，直接利用 $x\leftarrow\textit{pre}_x$ 向前推最短路径上的节点，看是否能够推到 $1$，如果最终不能够推到 $1$ 就说明不存在从 $1$ 到 $n$ 的最短路径。

两种方法虽然看上去第一种的表述要多一些，但实际上这两种方法的实现程度都是不难的，因此推荐大家把两种写法都写一遍。

另外，我们也可以从这道题目中吸取一些教训：**标题并不一定就决定了你的做题思路，你的做题思路应当从题面中通过思考而得出**。

## Code 1
```cpp
const int N = 1e5 + 7, M = N << 1;
int n, m, u, v, w, cnt, fl, vis[N], h[M], ans[N], pre[N];
ll dis[N];
struct edge {int v, to, nxt;}e[M];
pq<pair<ll, int> > q;

iv a_e(int u, int v, int w) {e[++cnt] = (edge){w, v, h[u]}; h[u] = cnt;}
iv dj() {
	F(i, 1, 100000) dis[i] = 1e18;
	dis[1] = 0, q.push(mp(0, 1));
	while(!q.empty()) {
		int x = q.top().se; q.pop();
		if(vis[x]) continue; vis[x] = 1;
		E {
			int y = e[i].to, z = e[i].v;
			if(dis[y] > dis[x] + z) {
				dis[y] = dis[x] + z, pre[y] = x;
				q.push(mp(-dis[y], y));
			}
		}
	}
}

int main() {
	n = Rint, m = Rint;
	F(i, 1, m) {
		u = Rint, v = Rint, w = Rint;
		a_e(u, v, w), a_e(v, u, w);
	}
	dj();
	for(int cur = n; cur; cur = pre[cur]) ans[++ans[0]] = cur;
	if(dis[n] != (ll)1e18) R(i, ans[0], 1) write(ans[i]), putchar(" \n"[i == n]);
	else puts("-1");
    return 0;
}
```

## Code 2
```cpp
const int N = 1e5 + 7, M = N << 1;
int n, m, u, v, w, cnt, fl, vis[N], h[M], ans[N], pre[N];
ll dis[N];
struct edge {int v, to, nxt;}e[M];
pq<pair<ll, int> > q;

iv a_e(int u, int v, int w) {e[++cnt] = (edge){w, v, h[u]}; h[u] = cnt;}
iv dj() {
	F(i, 1, 100000) dis[i] = 1e18;
	dis[1] = 0, q.push(mp(0, 1));
	while(!q.empty()) {
		int x = q.top().se; q.pop();
		if(vis[x]) continue; vis[x] = 1;
		E {
			int y = e[i].to, z = e[i].v;
			if(dis[y] > dis[x] + z) {
				dis[y] = dis[x] + z, pre[y] = x;
				q.push(mp(-dis[y], y));
			}
		}
	}
}

int main() {
	n = Rint, m = Rint;
	F(i, 1, m) {
		u = Rint, v = Rint, w = Rint;
		a_e(u, v, w), a_e(v, u, w);
	}
	dj();
	for(int cur = n; cur; cur = pre[cur]) {
		ans[++ans[0]] = cur;
		if(cur == 1) fl = 1;
	}
	if(fl) R(i, ans[0], 1) write(ans[i]), putchar(" \n"[i == n]);
	else puts("-1");
    return 0;
}
```

---

## 作者：JBLee (赞：6)

堆优化的DJ

注意要开long long

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
struct node
{
	int next;
	int to;
	long long value;
}edge[4*maxn];
int n,m;
int x,y,v;
int head[maxn],cnt,tot;
bool flag;
long long dis[maxn],nxt[maxn],pre[maxn],vis[maxn],pa[maxn];
priority_queue< pair<long long,long long> >q;
void add(int x,int y,int v)
{
	edge[++cnt].next=head[x];
	edge[cnt].to=y;
	edge[cnt].value=v;
	head[x]=cnt;
}
void dijkstra()
{
	for(int i=1;i<=n;i++)
	{
		dis[i]=9e13+7;
	}
	memset(vis,false,sizeof(vis));
	q.push(make_pair(0,1));
	dis[1]=0;
	while(q.size()!=0)
	{
		int x=q.top().second;
		q.pop();
		if(vis[x])
		{
			continue;
		}
		vis[x]=true;
		for(int i=head[x];i;i=edge[i].next)
		{
			int h=edge[i].to;
			if(dis[x]+edge[i].value<dis[h])
			{
				dis[h]=dis[x]+edge[i].value;
				q.push(make_pair(-dis[h],h));
				pre[h]=x;
			}
			
		}
	}
}
void print()
{
	for(int i=n;i;i=pre[i])
	{
		pa[++tot]=i;
		if(i==1)
		{
			flag=true;
		}
	}
	if(flag)
	{
		for(int i=tot;i>=1;i--)
		{
			printf("%d ",pa[i]);
		}
	}
	else
	{
		printf("-1");
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&v);
		add(x,y,v);
		add(y,x,v);
	}
	dijkstra();
	print();
	return 0;
}
```


---

## 作者：会打沙包的猫 (赞：6)

看到题解里都是结构体+重载运算符的做法

我来发一发pair的前向星~~蒟蒻专属福利~~
、、、cpp
~~~cpp
#include<bits/stdc++.h>
using namespace std;
struct xing{
	long long next,to,w;//别误会，这虽然是结构体，但这不是存进堆的，只是前向星存边
};
xing xx[10000002];
long long dis[100009],vis[100009],cnt,pos[100009],flag,boo=1,ans[100009];
priority_queue< pair<long long,long long> > q;//啦啦啦，我就是pair的前向星
long long  head[100009],n,m,g;
inline void spfa()
{
	for(int j=1;j<=n;j++)
	  dis[j]=9e13;//初始化
	q.push(make_pair(0,g));
	dis[g]=0;
	while(!q.empty())
	{
	    int now=q.top().second;//对首出队
		q.pop();
		if(vis[now]==1)continue;
		vis[now]=1;
		for(int j=head[now];j;j=xx[j].next)
		{
			int v=xx[j].to;
			if(dis[v]>dis[now]+xx[j].w)
			  {
			  	dis[v]=dis[now]+xx[j].w;
			  	q.push(make_pair(-dis[v],v));//加上-，就是大根堆模拟小跟堆了（优先队列）
			  	pos[v]=now;
			  }
		}
	}
}
int main()
{
     cin>>n>>m;
     g=1;//起点
     int a,b,c;
     for(int i=1;i<=m;i++)
     {
     	cin>>a>>b>>c;
     	xx[++cnt].to=b;//双向边存边
     	xx[cnt].next=head[a];
     	xx[cnt].w=c;
     	head[a]=cnt;
     	xx[++cnt].to=a;
     	xx[cnt].next=head[b];
     	xx[cnt].w=c;
     	head[b]=cnt;
     }
     spfa();
     for(int i=n;i;i=pos[i]) 
    {
        ans[++flag]=i;
        if(i==1)
         boo=0;
    }
    if(boo)//特判一下-1的情况
	  {
	  	cout<<-1;
	  	return 0;
	  }
    else
      for(int i=flag;i>=1;i--)
        cout<<ans[i]<<" ";//打印路径
     return 0;
}

~~~

---

## 作者：Paranoid丶离殇 (赞：6)

### 题意翻译

题目大意

给出一张图，请输出其中任意一条可行的从点 111 到点 nnn 的最短路径。

输入输出格式

输入格式

第一行：两个整数n，m，分别表示点数和边数

接下来m行：每行三个整数u，v，w，表示u和v之间连一条边权为w的双向边。

输出格式

一行：一个可行的路径，如果不存在这种路径输出-1

2<=n<=105，0<=m<=105

### 题目描述

You are given a weighted undirected graph. The vertices are  enumerated from 1 to n n n . Your task is to find the shortest path  between the vertex 1 1 1 and the vertex n n n .

### 输入格式

The first line contains two integers n n n and m m m (  2<=n<=105,0<=m<=105 2<=n<=10^{5},0<=m<=10^{5}  2<=n<=105,0<=m<=105 ), where n n n is the number of vertices  and m m m is the number of edges. Following m m m lines contain one  edge each in form ai a_ ai , bi b_ bi and wi w_ wi (  1<=ai,bi<=n,1<=wi<=106 1<=a_,b_<=n,1<=w_<=10^{6}  1<=ai,bi<=n,1<=wi<=106 ), where ai,bi a_,b_ ai,bi are edge  endpoints and wi w_ wi is the length of the edge.

It is possible that the graph has loops and multiple edges between pair of vertices.

### 输出格式

Write  the only integer -1 in case of no path. Write the shortest  path in  opposite case. If there are many solutions, print any of them.

### 输入输出样例

**输入 #1**

> 5 6 1 2 2 2 5 5 2 3 4 1 4 1 4 3 3 3 5 1

**输出 #1**

> 1 4 3 5

**输入 #2**

> 5 6 1 2 2 2 5 5 2 3 4 1 4 1 4 3 3 3 5 1

**输出 #2**

> 1 4 3 5

### 题解

最短路模板题。。。

在计算最短路过程中，pre[i]记录点 i 的最短路前驱。

利用pre[i]数组输出答案即可。

注意最后一个点范围爆long long.

### code:

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 2e5 + 5;
int n, m;
struct edge { int to, nxt, val; } e[N];
int cnt, head[N];
void add(int from, int to, int val) {
	e[++ cnt].to = to;
	e[cnt].val = val;
	e[cnt].nxt = head[from];
	head[from] = cnt;
}
int dis[N], vis[N], pre[N];
LL ans[N];
void spfa() {
	for(int i = 1;i <= n;i ++) dis[i] = 1e15;
	queue <int> q; q.push(1);
	dis[1] = 0; vis[1] = 1;
	while(! q.empty()) {
		int tp = q.front(); q.pop();
		vis[tp] = 0;
		for(int i = head[tp]; i ;i = e[i].nxt) {
			int to = e[i].to, val = e[i].val;
			if(dis[to] > dis[tp] + val) {
				dis[to] = dis[tp] + val;
				pre[to] = tp;
				if(! vis[to]) q.push(to), vis[to] = 1;
			}
		}
	}
}
signed main() {
	cin >> n >> m;
	for(int i = 1, a, b, l;i <= m;i ++) {
		cin >> a >> b >> l;
		add(a, b, l); add(b, a, l);
	}
	spfa();
	if(dis[n] == 1e15) { cout << "-1"; return 0; }
	int t = n, tot = 0;
	while(t != 1) {
		ans[++ tot] = t;
		t = pre[t];
	}
	ans[++ tot] = 1;
	for(int i = tot; i ;i --) cout << ans[i] << " ";
	return 0;
}
```

~~就这样，我又水了一篇题解。~~



---

## 作者：retired_LeoStrange (赞：5)

>Dijkstra?

Yeah.it is Dijkstra.

~~看[P3371](https://www.luogu.org/problem/P3371)和[P4779](https://www.luogu.org/problem/P4779)的题解挺多的，就来写[CF20C](https://www.luogu.org/problem/CF20C)的题解了~~

### 下面介绍Dijkstra算法

算法思想：贪心

常用题型：单源最短路径

限制条件：边权非负

主要方法：用个数组存该节点到所给节点（即“单源最短路”中的“源”）的最短路径长度

简单嘚啵一下流程(加了堆优化$ ^*$):

1. 初始化：所给节点dis为0，其余点的dis为一个较大的数

1. 以dis大小为比较条件建立小根堆，把所给节点扔到堆里（要用一个pair类型储存dis的值和节点标号）

1. 若堆不为空，每次取出堆顶元素(即dis最小的一个元素)的节点标号x，然后弹出堆顶元素。若已访问过该节点，就continue；否则枚举所有与x节点有边直接相连的节点y：若**dis[x]+ x和y之间的边的权值 < dis[y]** (即找到了节点y的更优的解)则更新dis[y],并把节点y扔到堆里

--------------------------------------------

\*加堆优化后时间复杂度为$O((n+m)log n)$，而不加堆优化时间复杂度为$O(n^2)$

在稠密图中$m$接近$n^2$，故不必用堆优化。

---------------------------------------------
#### 另外，对于这道题目
用一个数组记录当前节点到所给节点的最短路径上的前一个节点是什么

这样就可以得到具体的路径。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;      //本题要开long long
const int N = 1e5 + 5;
template <typename T> inline void read(T &x) //读入优化
{
	x=0; char ch=0; int f=1;
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-f;
	for(; isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+ch-48;
	x*=f;
}
template <typename T> inline void wrote(T x) //输出优化
{
	if(x<0) {putchar('-'); wrote(-x); return;}
	if(x<10){putchar(x+48);return;}
	wrote(x/10);
	putchar(x%10+48);
}
vector < pair<int,ll> > g[N]; //用vector的邻接表存图
priority_queue < pair<ll,int> > q; //用相反数建立小根堆
deque <ll> ans; //存路径,方便输出
ll dis[N],vis[N],pre[N];
int n,m;
int main()
{
	read(n); read(m);
	for(int i=1; i<=m; ++i)
	{
		int u,v,w;
		read(u); read(v); read(w);
		g[u].push_back(make_pair(v,w));
		g[v].push_back(make_pair(u,w));
	}
	q.push(make_pair(0,1));
	memset(dis,0x7f,sizeof(dis));
	dis[1]=0;
	while(!q.empty())
	{
		int u=q.top().second; q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=0; i<g[u].size(); ++i)
		{
			int y=g[u][i].first; int z=g[u][i].second;
			if(dis[y]>dis[u]+z)
			{
				dis[y]=dis[u]+z;
				pre[y]=u;
				q.push(make_pair(-dis[y],y));
			}
		}
	}
	if(dis[n]==0x7f7f7f7f7f7f7f7f)
	{
		puts("-1");
		return 0;
	}
	int x=n;
	while(pre[x])
	{
		ans.push_back(x);
		x=pre[x];
	}
	ans.push_back(1);
	while(!ans.empty())
	{
		wrote(ans.back());
		putchar(' ');
		ans.pop_back();
	}
	return 0;
}
```

---

## 作者：KaenbyouRin (赞：5)


~~这绝对不是正解~~

没错，spfa是被卡了。

然而，spfa有一个特点，储存脏顶点的容器可以随便选。一般大家用的都是队列，所以数据卡的也是队列。因此我们可以考虑换一种数据结构储存脏顶点。

栈试过了，30# TLE了。

尝试优先队列，居然过了。而且我的优先队列的元素是顶点编号……这也太玄学了

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <limits>
#include <stack>
using namespace std;

#define INF (std::numeric_limits<long long>::max())
struct Edge
{
	int to, w;
};

vector<Edge> g[100005];
vector<int> last(100005, -1);
vector<long long> dis(100005, INF);
vector<bool> vis(100005, false);
int n, m;

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].push_back({ v, w });
		g[v].push_back({ u, w });
	}
	//对的，你没有看错，关于顶点编号的最大堆
	//别问，问就是玄学
	priority_queue<int> q;
	vis[1] = true;
	dis[1] = 0;
	q.push(1);
	while (!q.empty()) {
		int f = q.top();
		q.pop();
		vis[f] = false;
		for (auto e : g[f]) {
			if (dis[e.to] > dis[f] + e.w) {
				dis[e.to] = dis[f] + e.w;
				last[e.to] = f;
				if (!vis[e.to]) {
					vis[e.to] = true;
					q.push(e.to);
				}
			}
		}
	}
	if (dis[n] == INF) {
		cout << -1 << endl;
	}
	else {
		stack<int> stk;
		int cur = n;
		while (cur != -1) {
			stk.push(cur);
			cur = last[cur];
		}
		while (!stk.empty()) {
			cout << stk.top() << " ";
			stk.pop();
		}
	}
	return 0;
};
```


---

## 作者：西卡洛斯 (赞：5)

几乎接近模板题。

~~题目后面加了问号表示这题一定有坑（~~

除了题面上的双向边外，后面的数据要开 long long 才能过。

剩下的就是 dijkstra 求最短路+路径输出了。
```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N=1e5+10,MAX=1e15;
struct Edge{int u,v,w;}edge[N*2];
int head[N],cnt;
int m,n;
void addedge(int u,int v,int w)
{
	edge[++cnt].v=v;
	edge[cnt].w=w;
	edge[cnt].u=head[u];
	head[u]=cnt;
}
struct Node
{
	int dis,pos;
	bool operator < (const Node &x) const {return x.dis<dis;}
};
priority_queue <Node> q;
long long dis[N],vis[N],pre[N],ans[N];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
		addedge(v,u,w);
	}
	for(int i=1;i<=n;i++) dis[i]=MAX;
	dis[1]=0;
	q.push((Node){0,1});
	while(!q.empty())
	{
		Node t=q.top();
		q.pop();
		int x=t.pos,y=t.dis;
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x];i;i=edge[i].u)
		{
			int y=edge[i].v,z=edge[i].w;
			if(dis[y]>dis[x]+z)
			{
				dis[y]=dis[x]+z;
				pre[y]=x;//记录路径
				q.push((Node){dis[y],y});
			}
		}
	}
	if(dis[n]==MAX) {puts("-1");return 0;}
	int cnt=0;
	while(n!=1)
	{
		ans[++cnt]=n;
		n=pre[n];
	}
	ans[++cnt]=1;
	for(int i=cnt;i;i--) printf("%lld ",ans[i]); 
	return 0;
}
```


集训前一天写题解，RP++。

---

## 作者：Sober_Clever (赞：2)

我决定再水一篇题解~

在求1~i最短路时顺便保留i的前驱（所有最短路中的一个可行前驱）即可

别忘了倒序输出和-1的特判

```cpp
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=1e5 + 2;
typedef long long ll;
const ll inf=1e12; 
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
	int to,next;
	ll w;
}e[MAXN<<1];
int head[MAXN]={0},cnt=0;
inline void add(int u,int v,ll w)
{
	e[++cnt].to=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}

ll d[MAXN];
int vis[MAXN]={0},last[MAXN]={0},n,m;
//last[i]存i的前驱
priority_queue<pair<ll,int> > Q;
void dij()
{
	for(int i=1;i<=n;i++) d[i]=inf;
	d[1]=0;
	Q.push(make_pair(-d[1],1));
	while(!Q.empty())
	{
		pair<int,int> p=Q.top();
		Q.pop();
		int u=p.second;
     if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(d[v]>d[u]+e[i].w)
			{
				d[v]=d[u]+e[i].w;
				last[v]=u;
				Q.push(make_pair(-d[v],v));
			}
		}
	}
}

int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read(),w=read();
		add(u,v,w);
		add(v,u,w); 
	}
	int now=n;
	dij();
	int path[MAXN],num=0;
	while(now)
	{
		path[++num]=now; 
		now=last[now];
	}
	if(!last[n])
	{
		printf("-1\n");
		return 0;
	}
	for(int i=num;i>1;i--)
		printf("%d ",path[i]);
	printf("%d\n",path[1]);
	return 0;	
}
```


---

## 作者：Dog_Two (赞：2)

不仔细看原文或者题解还真的注意不到题目给定的边都是双向边。

这里使用Heap_Dijkstra实现，我们会发现，根据各种最短路算法的松弛特性，我们可以在更新最短路的时候顺手就记录某个节点的“上一个点”了。

具体实现和小细节在代码注释里。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const long long INF=1e12;
int n,m;
struct edge{
	int u,v,w;
};
edge E[maxn];
vector<int>G[maxn];
int p[maxn];//p[k]记录最短路上到达k的节点 
long long dis[maxn];
bool vis[maxn];
struct Node{
	int u,d;
	bool operator < (const Node &tmp)const{
		return d>tmp.d;
	}
};
priority_queue<Node>q;
//一揽子Heap_Dijkstra需要的变量 
 
void readin(){//读入数据 
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int u,v,w; scanf("%d%d%d",&u,&v,&w);
		E[i]=(edge){u,v,w};
		E[i+m]=(edge){v,u,w};//处理双向边
		G[u].push_back(i);
		G[v].push_back(i+m);//处理双向边 
	}
}

bool Dijkstra(){
	fill(dis+1,dis+n+1,INF);
	fill(vis+1,vis+n+1,false);
	dis[1]=0;
	q.push((Node){1,0});
	while(!q.empty()){
		Node tmp=q.top(); q.pop();
		if(vis[tmp.u]) continue;
		vis[tmp.u]=true;
		for(int i=0;i<G[tmp.u].size();++i){
			edge &e=E[G[tmp.u][i]];
			if(dis[e.v]>dis[e.u]+e.w){
				dis[e.v]=dis[e.u]+e.w;
				q.push((Node){e.v,dis[e.v]});
				p[e.v]=e.u;//“顺带”记录一下路径 
			}
		}
	}
	return !(dis[n]==INF);//dis[n]==INF 即为不连通 
}

void print_G(int k){//递归打印路径 
	if(p[k]!=-1) print_G(p[k]);//递归终点，对应Give_Ans中p[1]=-1 
	printf("%d ",k);
}

void Give_Ans(bool if_pas){//判断答案是否存在 
	if(!if_pas){
		puts("-1");
		return;
	}
	p[1]=-1;
	print_G(n);
}

int main(){
	readin();
	bool if_pas=Dijkstra();
	Give_Ans(if_pas);
	return 0;
}
```

---

## 作者：Enterpr1se (赞：1)

Yes, Dijkstra. ~~Because SPFA  has died.~~  


------------
言归正传。  
↖这个屑没看题目直接写了个最短路模板 ~~（虽然某种意义上这题就是）~~ ，结果显然惨不忍睹。  
需要注意的有以下几点：  
+ 题目所求是最短路经过的点，而非最短路长度。（这种错误应该也只有博主这样的屑才会犯了
+ 十年 OI 一场空，不开 `long long` 见祖宗。  

剩下的就是简单的 Djikstra 模板了。  
唯一需要特别说明的就是路径记录方式。此处题解区好多大佬选择用 `vector` 存，但是这个屑觉得 `vector` 太慢，就自己写了个 DFS：  
```cpp
int prpt[100005];
void putans(int id){
	if(id) putans(prpt[id]),printf("%d ",id);
}
```
好的，可以上代码了。  
**注：本题中使用的存图方法为链式前向星，不会使用的读者请自行查找有关资料。**  
```cpp
//Luogu-CF20C Solution
//Luogu @Enterpr1se (Userid 363523)
//@_Qijia (Userid 363524) AK IOI!
#include<cstdio>
#include<cstring>
#include<queue>
#define regll register long long
#define regint register int
#define regshort register short
#define _Qijia using
#define AK namespace
#define IOI std
_Qijia AK IOI;
int n,m,u,v,ecnt/*前向星变量*/,last[100005]/*前向星变量*/,prpt[100005]/*记录路径上的点*/;
/*令人想辱骂出题人的*/long long w,dist[100005],temp;
bool vis[100005]; 
struct edge{
	int to,prev;
	long long wei;
} fig[200005];
struct node{
	int id;
	long long di;
	const operator < (const node &tocomp) const {
		return di>tocomp.di;
	}
} curr;
priority_queue<node> pqu;
inline void add(int s,int e,int w){
	++ecnt;
	fig[ecnt]={e,last[s],w};
	last[s]=ecnt;
	++ecnt;
	fig[ecnt]={s,last[e],w};
	last[e]=ecnt;
	return;
}
void putans(int id){
	if(id) putans(prpt[id]),printf("%d ",id);
}
signed main(){
	scanf("%d%d",&n,&m);
	for(regint i=1;i<=m;++i) scanf("%d%d%lld",&u,&v,&w),add(u,v,w);
	pqu.push({1,0});
	memset(dist,0x3f,sizeof(dist));
	dist[1]=0;
	//Dijkstra本体的循环 
	while(pqu.size()){
		curr=pqu.top();
		pqu.pop();
		vis[curr.id]=true;
		for(regint i=last[curr.id];i;i=fig[i].prev){
			if(vis[fig[i].to]) continue;
			temp=curr.di+fig[i].wei;
			if(temp<dist[fig[i].to]){
				dist[fig[i].to]=temp;
				pqu.push({fig[i].to,temp});
				prpt[fig[i].to]=curr.id;//本题需要加入的特殊处理：记录上一个点 
			}
		}
	}
	if(prpt[n]/*判断是否有解*/) putans(n);
	else putchar('-'),putchar('1');
	return 0;
}
```
$\mathtt{Thanks}\text{ }\mathtt{for}\text{ }\mathtt{reading.}$

---

