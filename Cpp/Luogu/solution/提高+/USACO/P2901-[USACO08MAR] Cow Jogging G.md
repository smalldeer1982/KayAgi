# [USACO08MAR] Cow Jogging G

## 题目描述


贝西终于尝到了懒惰的后果，决定每周从谷仓到池塘慢跑几次来健身。当然，她不想跑得太累，所以她只打算从谷仓慢跑下山到池塘，然后悠闲地散步回谷仓。

同时，贝西不想跑得太远，所以她只想沿着通向池塘的最短路径跑步。一共有 $M$ 条道路，其中每一条都连接了两个牧场。这些牧场从 $1$ 到 $N$ 编号，如果 $X>Y$，则说明牧场 $X$ 的地势高于牧场 $Y$，即下坡的道路是从 $X$ 通向 $Y$ 的，$N$ 为贝西所在的牛棚（最高点），$1$ 为池塘（最低点）。

然而，一周之后，贝西开始对单调的路线感到厌烦，她希望可以跑不同的路线。比如说，她希望能有 $K$ 种不同的路线。同时，为了避免跑得太累，她希望这 $K$ 条路线是从牛棚到池塘的路线中最短的 $K$ 条。如果两条路线包含的道路组成的序列不同，则这两条路线被认为是不同的。

请帮助贝西算算她的训练强度，即将牧场网络里最短的 $K$ 条路径的长度分别算出来。你将会被提供一份牧场间路线的列表，每条道路用 $(X_i, Y_i, D_i)$ 表示，意为从 $X_i$ 到 $Y_i$ 有一条长度为 $D_i$ 的下坡道路。

## 说明/提示

#### 样例 1 解释

这些路线分别为 $(5\to 1)$、$(5\to 3\to 1)$、$(5\to 2\to 1)$、$(5\to 3\to 2\to 1)$、$(5\to 4\to 3\to 1)$ 和 $(5\to 4\to 3\to 2\to 1)$。

#### 数据规模与约定

对于全部的测试点，保证 $1 \le N \le 1,000$，$1 \le M \le 1\times10^4$，$1 \le K \le 100$，$1 \le Y_i < X_i\le N$，$1 \le D_i \le 1\times 10^6$， 

## 样例 #1

### 输入

```
5 8 7 
5 4 1 
5 3 1 
5 2 1 
5 1 1 
4 3 4 
3 1 1 
3 2 1 
2 1 1 
```

### 输出

```
1 
2 
2 
3 
6 
7 
-1 
```

# 题解

## 作者：HPXXZYY (赞：34)

## $\color{green}{\text{Front Knowledge - A}^{*} \text{ algorithm}}$

`A* 算法`，就是启发式的 `BFS` 算法。它依赖于以下几个函数：

- $g$ 函数：即从开始到当前状态的花费。
- $g^*$ 函数：估计的从开始到当前状态的花费。由于 `BFS` 的特殊性，我们一定有 $g=g^*$。
- $h$ 函数：从当前状态到结束状态的**实际**花费。
- $h^*$ 函数：从当前状态到结束状态的**估计**花费。
- $f$ 函数：从起始状态到当前状态再到结束状态的总花费。即 $f=g+h$。
- $f^*$ 函数：从起始状态到当前状态再到结束状态的估计花费。即 $f^* = g^*+h^* = g +h^*$。

我们的 `A*算法` 就是根据 $f^*$ 从小到大来遍历搜索节点（因为它最有可能最优）。

为了保证正确性，我们要求 $h^* \leq h$。同时 $h^*$ 越大，`A*算法` 速度越快，所以 $h^*$ 函数的好坏决定了整个算法的好坏。

---------------------------------------------------------------

## $\color{green}{\text{K}^{\text{th}} \text{ Shortest Path}}$

顾名思义，就是求一张图的第 $K$ 短的路径。

考虑暴力，我们可以求出所有的可能路径，然后排序，取第 $K$ 小值即答案。但是，求所有可能路径的算法会 `TLE`。

考虑如何用 $\text{A}^{*}%$ 优化这个过程。我们先求出所有的点到终点的距离 $dis_i$，然后跑一遍 `A*` 算法。$d^{*}$ 函数就是当前状态（点）的 $dis$ 值，记从起点到当前点的花费为 $t$，故而 $f^{*} = d^{*} + g = dis + t$。

我们发现这个 $d^{*}$ 函数是相当优秀的。首先，它一定 $\leq d$，为什么？因为从一个点到终点的花费肯定 $\geq dis$（否则 $dis$ 就不是最短路径了呀）。其次，它足够优秀，足够大，是我们暂时能想到的，最好求，最大的 $d^{*}$ 函数了。

这么做还有一个好处，就是第 $u$ 次到达终点就是第 $u$ 短路。

```
1.求出所有的 dis (一遍SPFA/dijkstra) 搞定
2.把起点入队列
3.扩展 dis + t 最小的点
4.然后它是终点，则记录，如果求出 K 短路，再见
5.不断进行 3 直至出解
```

------------------------------------------------------------

## $\color{green}{\text{P2901\ \ \ \ \ [USACO08MAR]Cow Jogging G}}$

$\color{blue}{\text{【题意】：}}$ 输出一张 $n$ 个点，$m$ 条边，输出其 $K$ 短路，若无，就输出 `-1`。

$\color{blue}{\text{【思路】：}}$ `K 短路` 的模板题。

$\color{blue}{\text{【代码】：}}$
```cpp
typedef long long ll;int n,m,k;
const int N=1e3+100,M=1e6+100;
struct edge{int next,to;ll len;};
edge e[M],E[M];int h[N],H[N],tot,Tot;
inline void add(int a,int b,int c){
	e[++tot]=(edge){h[a],b,c};h[a]=tot;
}//链式前向星——正向图 
inline void Add(int a,int b,int c){
	E[++Tot]=(edge){H[a],b,c};H[a]=Tot;
}//链式前向星——反向图 
int dis[N];//点到终点的长度 
bool vis[N];//SPFA判重用数组 
inline void spfa_algorithm(){
	queue<int> q;q.push(1);
	memset(dis,127,sizeof(dis));
	memset(vis,true,sizeof(vis));
	vis[1]=false;dis[1]=0;
	while (q.size()){
		int u=q.front();q.pop();vis[u]=1;
		for(int i=H[u];i;i=E[i].next){
			register int to=E[i].to;
			if (dis[to]>dis[u]+E[i].len){
				dis[to]=dis[u]+E[i].len;//updata
				if (vis[to]){vis[to]=0;q.push(to);}
			}//单源最短路的松弛操作 
		}//特别注意，我们跑的是反向图 
	}
}
struct node{int pos;ll len;};
bool operator < (node a,node b){
	return a.len+dis[a.pos]>b.len+dis[b.pos];
}//特别注意，因为使用了STL的优先队列
 //所以这里的“小于”必须定义为“大于” 
int A_star_algorithm(int &ret){
	priority_queue<node> q;
	q.push((node){n,0});
	while (q.size()){
		node z=q.top();q.pop();
		if (z.pos==1){//又到终点了 
			printf("%lld\n",z.len);
			if ((--ret)==0) return 0;
		}
		register int u=z.pos,i;
		for(i=h[u];i;i=e[i].next){
			register int to=e[i].to;
			q.push((node){to,z.len+e[i].len});
		}
	}
	return ret;
}
int main(){
	n=read();m=read();k=read();
	for(int i=1,u,v,w;i<=m;i++){
		u=read();v=read();w=read();
		add(u,v,w);Add(v,u,w);
	}
	spfa_algorithm();
	A_star_algorithm(k);
	while (k--) printf("-1\n");
	return 0;
}



read() 函数就是快读函数（我写得丑，就不给大家了）
```

--------------------------------------

大家有空可以做做这题：[模板】k短路 / [SDOI2010]魔法猪学院](https://www.luogu.com.cn/problem/P2483)。它卡 `STL` 哦·！！！

---

## 作者：xtx1092515503 (赞：22)

为什么诸位神仙用的都是$A^*$或是广搜这种神仙算法呀……老老实实DP它不香吗？

我们设$f[i][j]$表示：以第$i$个点为终点的第$j$短路的长度。

为了方便，我们将序列翻转，即从$1$号点出发，到达$n$号点。

然后，对于一条路径$(x,y,z)$，我们尝试从$x$转移到$y$。

我们可以令一个辅助数组$g$，其中$g[j]=f[x][j]+z$，即为从$x$点出发，到达$y$点的第$j$短的路的长度。

因为$g$和$f[y]$显然都是递增的，因此直接归并一下完成。

什么？你太懒了不想写归并排序？

没关系，有个C++内置函数叫做```merge```。

 ```merge``` _函数的作用是：将两个有序的序列合并为一个有序的序列。_ 

 _函数参数：_ ```merge(first1,last1,first2,last2,result,compare)```

```first1``` _为第一个容器的首迭代器，_ ```last1``` _为第一个容器的末迭代器，_ ```first2``` _为第二个容器的首迭代器，_ ```last2``` _为容器的末迭代器，_ ```result``` _为存放结果的容器，_ ```compare``` _为比较函数（可略写，默认为合并为一个升序序列）。_ 

 _——译自C++官网_ 
 
 因此直接调用这个函数就可以非常轻松地实现转移。复杂度$O(mk)$。
 
 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,f[1010][110],g[210],h[210],sz[1010];
vector<pair<int,int> >v[1010];
int main(){
	scanf("%d%d%d",&n,&m,&q),memset(f,0x3f3f3f3f,sizeof(f)),f[1][sz[1]=1]=0;
	for(int i=1,x,y,z;i<=m;i++)scanf("%d%d%d",&x,&y,&z),v[y].push_back(make_pair(x,z));
	for(int i=1;i<=n;i++)for(auto j:v[i]){
		for(int k=1;k<=sz[i];k++)g[k]=f[i][k]+j.second;
		merge(g+1,g+sz[i]+1,f[j.first]+1,f[j.first]+sz[j.first]+1,h+1);
		sz[j.first]+=sz[i],sz[j.first]=min(sz[j.first],q);
		for(int k=1;k<=sz[j.first];k++)f[j.first][k]=h[k];
	}
//	for(int i=1;i<=n;i++){for(int j=1;j<=q;j++)printf("%d ",f[i][j]);puts("");}
	for(int i=1;i<=q;i++)printf("%d\n",f[n][i]==0x3f3f3f3f?-1:f[n][i]);
	return 0;
} 
```


---

## 作者：Grisses (赞：9)

[题面](https://www.luogu.com.cn/problem/P2901)

# upd:

2023/1/17: 感谢 @Code_星云，已修改“入队”为“出队”。

---

$K$ 短路是一种经典的题型，其正解是使用“可持久化可并堆”，~~（但我不会）~~。这里介绍的是 `A*` 算法。

`A*` 算法是一种优化 BFS 的算法，通过估价函数求得剩余花费，来“贪婪”地搜索，优先扩展更优秀的状态。在本题里，我们设 $h(i)$ 表示 $i$ 点到终点的最短路，$g(i)$ 表示目前到 $i$ 点已走过的距离。类似于 Dijkstra 算法，唯一不同的是使用 `A*` 的 BFS 需要让节点重复入队于出队，当 $i$ 号点第 $k$ 次出队时，所走的路线就是从起点到第 $i$ 号点的第 $k$ 短路。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,m,s,t,tot,ans[105],h[1005],cnt,H[1005],ecnt;//tot是目前ans的长度；h、cnt、H、ecnt是链式前向星的辅助变量
  int k;
  struct edge{
      int v,nxt;
      double w;
  }e[10005],E[10005];//存储边
  void adde(int u,int v,int w){
      e[++cnt].nxt=h[u];
      h[u]=cnt;
      e[cnt].v=v;
      e[cnt].w=w;
  }//建边
  void Adde(int u,int v,int w){
      E[++ecnt].nxt=H[u];
      H[u]=ecnt;
      E[ecnt].v=v;
      E[ecnt].w=w;
  }//建边
  int dis[1005];//到终点的最短距离
  bool vis[1005];//标记是否到达过
  struct node{
      int x;
      int k;
      node(){}
      node(int a,int b){x=a,k=b;}
      bool operator<(const node &t)const{
          return k>t.k;//重载运算符
      }
  };
  void D(){//Dijkstra
      priority_queue<node>q;
      q.push(node(t,0));
      for(int i=1;i<=n;i++)dis[i]=1e9;
      dis[t]=0;//初始化
      while(!q.empty()){
          node tmp=q.top();
          q.pop();
          if(vis[tmp.x])continue;
          vis[tmp.x]=1;
          for(int i=H[tmp.x];i;i=E[i].nxt){
              if(tmp.k+E[i].w<dis[E[i].v]){
                  dis[E[i].v]=tmp.k+E[i].w;//松弛
                  q.push(node(E[i].v,dis[E[i].v]));
              }
          }
      }
  }
  struct Node{//准备A*
      int x;
      int k;
      Node(){}
      Node(int a,int b){x=a,k=b;}
      bool operator<(const Node &t)const{
          return k+dis[x]>t.k+dis[t.x];
      }
  };
  void st(){
      priority_queue<Node>q;
      q.push(Node(s,0));
      while(!q.empty()){
          Node tmp=q.top();
          q.pop();
          if(tmp.x==t){//到了终点
              ans[++tot]=tmp.k;//存储
              if(tot==k)return;//k条都有了
              continue;
          }
          for(int i=h[tmp.x];i;i=e[i].nxt){
              q.push(Node(e[i].v,tmp.k+e[i].w));//扩展
          }
      }
  }
  int main()
  {
      scanf("%d%d%d",&n,&m,&k);s=n,t=1;//从n号点到1号点
      int u,v,w;
      for(int i=1;i<=m;i++){
          scanf("%d%d%d",&u,&v,&w);
          adde(u,v,w);//正向边
          Adde(v,u,w);//反向边（求到终点最短路）
      }
      D();
      st();
      for(int i=1;i<=tot;i++)printf("%d\n",ans[i]);//输出答案
      for(int i=tot+1;i<=k;i++)printf("-1\n");//不够的补全
      return 0;
  }
```

---

## 作者：Hale (赞：9)


（废话开始：A_star算法大法好）

在mike的指导下总算学会了

第一道k短路的题，学了一个星期
中间没连着总算搞掉了，嘤嘤嘤

首先你要知道估价函数这个东西

总体感觉a*算法思想其实还是广搜

广搜楼上大佬已经说过了，很详细

我主要是用SPFA跑了一遍反向图

然后搞了个估价函数就a了

我知道你们喜欢看代码直接，哭唧唧

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=0x7fffffff;
const int M=100010;
int m,n,k,l,cnt;
int d[M];
bool inque[M];
int ans[M];
struct node
{ int now;
  int step;
  int g;
  bool operator<(const node & x) const 
  {return (x.g==g)?x.step<step:x.g<g;}
};
priority_queue<node> que;
queue<int> q;
struct edge
{ int to;
  int dist;
};
vector<edge>g[5010],lg[5010];
void add_edge(int u,int v,int w)
{ g[u].push_back((edge){v,w});lg[v].push_back((edge){u,w});}
void SPFA()
{ for (int i=1;i<=n;i++) d[i]=INF;
  d[1]=0;q.push(1);inque[1]=true;
  while (!q.empty())
 { int s=q.front();q.pop();
   for (int i=0;i<lg[s].size();i++)
   { int y=lg[s][i].to,dd=lg[s][i].dist;
     if (d[y]>d[s]+dd)
     { d[y]=d[s]+dd;
       if (!inque[y])
       { inque[y]=true;q.push(y);}
	 }
   }
   inque[s]=false;
  } 
}
int shrt[5050];
void a_star()
{ node zz;zz.now=n;zz.g=0;zz.step=0;
  que.push(zz);
  while (!que.empty())
  { node zz=que.top();que.pop();
    int u=zz.now;
    if (u==1)
    { cnt++;
      ans[cnt]=zz.step;
      if (cnt>k) return;
	}
	shrt[u]++;
	if (shrt[u]>k) continue;
	for (int i=0;i<g[u].size();i++)
	{ int y=g[u][i].to,dd=g[u][i].dist;
	  node mm;
	  mm.now=y;mm.step=zz.step+dd;
	  mm.g=mm.step+d[y];
	  que.push(mm);
	}
  }
}
int read()
{ int f=1,x=0;char c=getchar();
  while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
  while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
  return x*f;
}
int main()
{ n=read();m=read();k=read();
  for (int i=1;i<=m;i++)
  { int x,y,z;
    x=read();y=read();z=read();
    add_edge(x,y,z);
  }
  SPFA();
  memset(ans,-1,sizeof(ans));
  a_star();
  for (int i=1;i<=k;i++)
  printf("%d\n",ans[i]);
  return 0;
}
```

---

## 作者：NaVi_Awson (赞：4)

一种比较朴素(裸)的算法...

理解起来可能比下面那种更方便些

广搜实现，将所以可行的点入队

对于重要部分，下有注解

```cpp
#include<cmath>
#include<string>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
 using namespace std;
const int N=5000000;
struct tt
{
    int next,to,cost;
}edge[10005];
int n,m,k;
int x,y,c;
int path[1005],top;
int team[N+5][2],head,tail;
int ans[N+5],num,maxn;
void add(int x,int y,int c);
void bfs();
int main()
{
    memset(path,-1,sizeof(path));
    scanf("%d%d%d",&n,&m,&k);
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&c);
        add(x,y,c);
    }
    team[tail++][0]=n;
    bfs();
    sort(ans+1,ans+1+num);
    for (int i=1;i<=k;i++)
    {
        if (ans[i]==0) printf("%d\n",-1);
        else printf("%d\n",ans[i]);
    }
    return 0;
}
void add(int x,int y,int c)
{
    edge[++top].to=y;
    edge[top].next=path[x];
    edge[top].cost=c;
    path[x]=top;
    return;
}
void bfs()
{
    while(head!=tail)
    {
        for (int i=path[team[head][0]];i!=-1;i=edge[i].next)
        if (!(team[head][1]+edge[i].cost>=maxn&&num>=k))//如果已求出k个解且待加入的点已大于求出解的最大值，不入队
        {
            if (edge[i].to==1)
            {
                ans[++num]=team[head][1]+edge[i].cost;
                maxn=max(maxn,ans[num]);
            }
            else
            {
                team[tail][0]=edge[i].to;
                team[tail++][1]=team[head][1]+edge[i].cost;
                tail%=N;
            }
        }
        head++;
        head%=N;
    }
    return;
}
```

---

## 作者：喵仔牛奶 (赞：4)

本题是弱化的 $K$ 短路模板题。

~~第一个一发 $\text{A}$ 掉的紫题~~



------------

前置芝士：

$\text{A*}$ 算法与 $\text{Dijkstra}$ 算法。

------------


众所周知，对于 $\text{A*}$ 算法， $f(i)=g(i)+h(i)$ 。在本题中， $g$ 为已消耗的体力，而**乐观估值函数** $h$ 为到达终点的**最短路**最合适。



------------


为什么 $\text{A*}$ 算法做这题正确？

因为我们是优先拓展估值最短的路径，所以当前最短路一定是在优先队列顶上的。

还有对于到达终点的 $f(1)$ 有 $f(1)=g(1)$ ，而 $\text{A*}$ 算法是从优先队列里取数的，所以一定正确。

------------


为什么 $\text{A*}$ 算法快速？

因为 $\text{A*}$ 算法可以快速地拓展当前最优解，从而快速地达到目标。


------------

如果有负边权， $\text{A*}$ 算法还正确吗？

加上了 $h(i)$ ……用 $\text{Dijkstra}$ 跑最短路当然不正确，用某已死算法跑就正确。

------------



那么 $\text{A*}$ 算法具体流程是：

1. 取出**优先队列**首的节点。

1. 拓展该节点的下一个节点，并将他们入队。

1. $K--$ ，如果 $K=0$ ，代表前 $K$ 短路以及输出完了，直接返回。

1. 重复 $1$ 。

至于到终点的最短路，建一个反向图跑一遍 $\text{Dijkstra}$ 即可。



------------

有注释。

```cpp
#include <bist/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
struct edge {
	int w, next, to;
} e[N], e1[N]; // e为正图，e1为反图
struct node {
	int pos, w;
	node(int _, int __) :
		pos(_), w(__) {}
	bool operator < (const node& x) const {
		return x.w < w;
	}
}; // Dij的节点。
int n, m, k, x, y, z, cnt, cnt1, dis[N], head[N], head1[N];
bool vis[N];
struct fuct {
	int pos, w;
	fuct(int _, int __) :
		pos(_), w(__) {}
	bool operator < (const fuct& x) const {
		return x.w + dis[x.pos] < w + dis[pos];
	}
}; // A*算法的节点。
void add(int u, int v, int w) {
	e[++ cnt].to = v;
	e[cnt].w = w;
	e[cnt].next = head[u];
	head[u] = cnt;
}
void add1(int u, int v, int w) {
	e1[++ cnt1].to = v;
	e1[cnt1].w = w;
	e1[cnt1].next = head1[u];
	head1[u] = cnt1;
}
void dijstra() {
	priority_queue<node> q;
	for (int i = 1; i <= n; i ++)
		dis[i] = 0x7fffffff;
	dis[1] = 0;
	q.push(node(1, 0));
	while (!q.empty()) {
		node u = q.top(); q.pop();
		if (vis[u.pos]) continue;
		vis[u.pos] = true;
		for (int i = head1[u.pos]; i; i = e1[i].next) {
			int v = e1[i].to;
			if (dis[v] > dis[u.pos] + e1[i].w) {
				dis[v] = dis[u.pos] + e1[i].w;
				if (!vis[v]) q.push(node(v, dis[v]));
			}
		}
	}
}
void A_star() { 
	priority_queue<fuct> q;
	q.push(fuct(n, 0));
	while (!q.empty()) {
		fuct u = q.top(); q.pop();
		if (u.pos == 1) {
			cout << u.w << '\n';
			if (!(-- k)) return; // 还剩下K-1短路
		}
		for (int i = head[u.pos]; i; i = e[i].next) {
			int v = e[i].to;
			q.push(fuct(v, u.w + e[i].w));
		}
	}
}
int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i ++)
		cin >> x >> y >> z, add(x, y, z), add1(y, x, z); // 建反图，跑Dij
	dijstra();
	A_star();
	while (k --) cout << -1 << '\n'; // 不足K短路，剩下的输出-1。
	return O;
}
```

时间复杂度 $O(nk\log k)$

在本题最坏情况可以过啦

------------


求过qwq

---

## 作者：Ryo_Yamada (赞：3)

因为只能从高向低走，所以图是一个 DAG。考虑在拓扑的同时更新答案。对于一个点，我们只需要记录它的前 $k$ 短路即可。即每个点记录一个大根堆，更新时向里插入答案，如果堆大小 $>k$ 就弹出最大的数。

注意可能有一些点入度 $=0$ 但编号不为 $n$（即无法到达）。这些点同样需要入队，但是没有答案。

对于每个点，我们需要弹出它的 $k$ 短路。更新答案操作最多只会进行 $m$ 次。所以时间复杂度为 $O((n+m)k \log k)$。

$\text{Code}$：

```cpp
def(N, int, 1005)
def(M, int, 1e4 + 5)

int n, m, k;
vector<pii > e[N];
priority_queue<int> dis[N];
int deg[N], ans[N];
int nw[N], cnt;

void topo() {
	dis[n].push(0);
	queue<int> q;
	per(i, n, 1) if(!deg[i]) q.push(i);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		cnt = 0;
		while(!dis[u].empty()) nw[++cnt] = dis[u].top(), dis[u].pop();
		for(pii x : e[u]) {
			int v = x.fi, w = x.se;
//			if(v == 1) cout << "qwq\n";
			--deg[v];
			rep(i, 1, cnt) {
				dis[v].push(nw[i] + w);
				if(dis[v].size() > k) dis[v].pop();
			}
			if(!deg[v]) q.push(v);
		}
		rep(i, 1, cnt) dis[u].push(nw[i]);
	}
}

int main() {
	qread(n, m, k);
	rep(i, 1, m) {
		int x, y, w;
		qread(x, y, w);
		++deg[y];
		e[x].pb(mp(y, w));
	}
	topo();
	int tot = 0;
	while(!dis[1].empty()) ans[++tot] = dis[1].top(), dis[1].pop();
	reverse(ans + 1, ans + tot + 1);
	rep(i, 1, k) {
		if(i > tot) puts("-1");
		else printf("%d\n", ans[i]); 
	}
	return 0;
}
```


---

## 作者：＂黎筱っ (赞：3)


据说是$k$短路模板，要用$A^*$，然而我不会。我是用拓扑排序加堆优化广搜水过去的。第一道完全靠自己做出来的紫题，调了两个小时，交了两遍。果然我还是太菜了。

正解的话，可以看[红太阳的博客](https://www.cnblogs.com/cellular-automaton/p/8379540.html)


**拓扑排序加堆优化广搜**

以下是我的神奇做法。

要找前$k$条最短路，怎么找？我观察了一下样例的图，发现每个点的路径长度会被更新很多次，但都是由直接指向他的点更新来的（废话），也就是说，他前面的点怎样更新的我不关心，我只关心这个点前$k$条最短路的长度。

那直接用堆存一下就好了。

但是我们要保证他前面的点已经更新完了。前面说了这是一个有向无环图，自然想到拓扑排序。

但我之前犯了一个错误，它花费了我一个多小时的时间。这个题要求必须从$n$号点出发，但是有些点$n$号点到不了，它们一开始入度就为零。如果不把这些点的影响去掉，后面就会出错。果然我菜鸡的本质难以掩盖。

**Code**

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
long long read(){
	long long x=0;int f=0;char c=getchar();
	while(c<'0'||c>'9')f|=c=='-',c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}

int n,m,k;
struct Dier{//前向星
	int to,next,w;
}a[10004];
int head[1001],cnt;
void add(int x,int y,int z){//单向边
	a[++cnt].to=y,a[cnt].next=head[x],a[cnt].w=z,head[x]=cnt;
}

priority_queue<int,vector<int>,greater<int> >q[1005];//小根堆
int in[1001],Q[1001],h,t;
//  入度     队列

int main(){
	n=read(),m=read(),k=read();
	for(int i=1,x,y,z;i<=m;++i){
		x=read(),y=read(),z=read();
		add(x,y,z),in[y]++;
	}
    
    //拓扑
	for(int i=n;i;--i)
		if(!in[i]) Q[++t]=i;
	for(int i=1;i<=t;++i){
		if(Q[i]==n) continue;//n号点的影响不应该去掉
		int u=Q[i];
		for(int i=head[u],v;v=a[i].to,i;i=a[i].next){
			in[v]--;
			if(!in[v]) Q[++t]=v;//斩草不除根，后面麻烦无穷
            //只要不是从n号点直接或间接转移过来的入度都要去掉，因为他们会妨碍我们后面的入队
		}
	}
    
	t=1,Q[1]=n;//初始化一下
	q[n].push(0);
	while(h<t){//广搜
		int u=Q[++h],ls=0;
		while(u!=1&&!q[u].empty()&&++ls<=k){//只取前k条就好
          //保证1号点的距离不会被pop掉
			for(int i=head[u],v;v=a[i].to,i;i=a[i].next)
				q[v].push(q[u].top()+a[i].w);//更新距离
			q[u].pop();
		}
        //计算入度一定要独立出来，不能和更新距离放在一起，因为那样会导致入度被减很多次
		for(int i=head[u],v;v=a[i].to,i;i=a[i].next){
			in[v]--;
			if(!in[v]) Q[++t]=v;
		}
	}
	while(!q[1].empty()&&k){//输出答案
		printf("%d\n",q[1].top()),q[1].pop(),k--;
	}
	for(int i=1;i<=k;++i) printf("-1\n");//有可能并没有k条路可以走
	return 0;
}
```
欢迎指正评论O(∩_∩)O~~

---

## 作者：Yaha (赞：2)

### $A^*$

题意：求前 $k$ 短路。问题比较经典，容易想到 $A^*$ 。

路径评分：$F=G+H$ 

 $G$ 值是从 $S$ 沿已知路径到该点的距离， $H$ 值是该点到 $T$ 的预估距离，也被称为估价函数。每次找 $F$ 值最小的来拓展，常用优先队列实现。

题目要求出前 $k$ 短路，跑 $A^*$ 的过程中，走到终点的前 $k$ 次就是前 $k$ 短路。到终点时， $H$ ，即预估距离为 $0$ ，故 $F$ 值就是 $G$ 值，即就是离 $S$ 点的距离。既然在小根堆栈顶，说明不会有更优却不在栈顶的方案了。

有的题，因为估价函数的存在，在栈顶时可能并没有更新到最优，但这道题就不用考虑，因为估价函数是求到的实际值，够准确，点在栈顶时其距离也已更到最新。

求估价函数我用的是 $Dijkstra$ ——从终点到起点反向跑一遍 $Dijkstra$ ，就能得到每个点实际到终点的最短距离，以此作为估价函数。再跑一遍 $A^*$ 就能得到答案了。



代码：

```cpp
#include<bits/stdc++.h>
#define x first
#define y second

using namespace std;

const int amou=1e3+90,M=2e4+90;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;

int head[amou],hh[amou],nxt[M],ver[M],cnt,edge[M];
bool we[amou];
int H[amou],times[amou];
int n,m,k,S,T;

void add(int head[],int a,int b,int c){
	nxt[++cnt]=head[a],head[a]=cnt,ver[cnt]=b,edge[cnt]=c;
}

void Dijkstra(){
	priority_queue<PII,vector<PII>,greater<PII> >kl;
	
	kl.push({0,T});
	memset(H,0x3f,sizeof H);
	H[T]=0;
	while(!kl.empty())
	{
		PII tou=kl.top();
		kl.pop();
		int i=tou.y;
		if(we[i]) continue;
		we[i]=1;
		for(int io=hh[i];io;io=nxt[io])
		{
			int v=ver[io];
			if(H[v]>H[i]+edge[io])
			{
				H[v]=H[i]+edge[io];
				kl.push({H[v],v});
			}
		}
	}
}

void Astar(){
	priority_queue<PIII,vector<PIII>,greater<PIII> >kl;
	
	kl.push({H[S],{0,S}});
	while(!kl.empty())
	{
		PIII tou=kl.top();
		kl.pop();
		int i=tou.y.y,G=tou.y.x;
		times[i]++;
		if(i==T)
		{
			printf("%d\n",G);
			if(times[T]==k) return;
			continue;
		}
		for(int io=head[i];io;io=nxt[io])
		{
			int v=ver[io];
			if(times[v]<k)//小优化
				kl.push({edge[io]+G+H[v],{edge[io]+G,v}});
		}
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	S=n,T=1;
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(head,a,b,c);
		add(hh,b,a,c);//建反向边，是为了Dijkstra中求点到终点的距离
	}
	Dijkstra();
	Astar();
	for(int i=times[T]+1;i<=k;i++)//可能不足k条，既然已经输出了times[T]条，剩下得用-1补完
		printf("-1\n");
	
	return 0;
}
```


---

## 作者：AmadeusSG (赞：2)

[博客食用](hackblogs.home.blog)

[本文部分参考](https://blog.csdn.net/z_mendez/article/details/47057461)

这道题的大意就是给你一个图，让你求从S到T的最短路。

DFS与BFS都属于非启发式搜索，又称盲目型搜索，它们最大的不同就是启发式搜索的选择不是盲目的，可以通过一个启发函数进行选择。

![如图](https://i.loli.net/2019/07/28/5d3d5da59e03678980.bmp)

假如正常的搜索方式，我们会不断移动，直至遇到障碍物，显然这种方法是很愚蠢的，但是正常的方法的确是这样进行的，那么我们就希望扩展一个运动算法，用于对付上图所示的障碍物。或者避免制造凹形障碍，或者把凹形出口标识为危险的(只有当目的地在里面时才进去): 

![如图](https://i.loli.net/2019/07/28/5d3d5db9affe085905.bmp)


## A*算法：

为启发式算法中很重要的一种，被广泛应用在最优路径求解和一些策略设计的问题中。而A*算法最为核心的部分，就在于它的一个估值函数的设计上： 

```
f(n)=g(n)+h(n) 
```

## 估价函数=当前值+当前位置到终点的距离

其中f(n)是每个可能试探点的估值，它有两部分组成：一部分为g(n)，它表示从起始搜索点到当前点的代价（通常用某结点在搜索树中的深度来表示）。另一部分，即h(n)，它表示启发式搜索中最为重要的一部分，即当前结点到目标结点的估值，h(n)设计的好坏，直接影响着具有此种启发式函数的启发式算法的是否能称为A*算法。


典型**A*** 算法题。
因为估价公式为fx+gx，估价必须小于实际距离，所以用最短路径，就一定小于实际距离。建反图求最短路，再用A* 算法求k短路，第k次出队就是第k短路。

代码：（~~Warning:开O2~~）
```
#include<bits/stdc++.h>
using namespace std;
const int INF=0x7fffffff,maxn=1000000;
int n,ans,m;
int vst[100005];
int dis[100005]/*边长*/,prt[10005]/*父亲*/,vis[10005];
struct EDGE{int next,to,v;}e[100005],fe[100005];
int cnt,h[100005],fcnt,fh[100005];
int S,T,K,N;
struct node{
	int f,g,to;
	bool operator <(const node &x)const{return f>x.f;}
};
void add(int x,int y,int z)
{
	e[++cnt].to=y;
	e[cnt].next=h[x];
	e[cnt].v=z;
	h[x]=cnt;
}
void add2(int x,int y,int z)
{
	fe[++fcnt].to=y;
	fe[fcnt].next=fh[x];
	fe[fcnt].v=z;
	fh[x]=fcnt;
}
int q[100005],bj[10005];
void SPFA() //单源spfa求最短路（估价）
{ 
    queue<int>q;
    for(int i=1;i<=n;i++)dis[i]=INF;
    dis[1]=0;vis[1]=1;
    q.push(T);
    while(!q.empty()) 
	{
        int x=q.front();
        q.pop();
        vis[x]=0;
        for(int i=fh[x];i;i=fe[i].next) 
		{
            int y=fe[i].to;
            if(dis[y]>dis[x]+fe[i].v) 
			{
                dis[y]=dis[x]+fe[i].v;
                if(!vis[y])
				{
                    q.push(y);
                    vis[y]=1;
                }
            }
        }
    }
}
int A_star(int K)//A* 算法
{
	node Q;
	int tot=0,i;
	if(N==1)K++;
	if(dis[N]==INF)return -1;
	Q.f=dis[N];
	Q.g=0;
	Q.to=N;
	priority_queue<node>heap;
	heap.push(Q);
	while(!heap.empty())
	{
		node x=heap.top();
		heap.pop();
		vst[x.to]++;
		if(x.to==1)tot++;
		if(tot==K)return x.g;//满足k次出队，即为k短路
		if(vst[x.to]>K)continue;
		for(i=h[x.to];i;i=e[i].next)
		{
			Q.g=x.g+e[i].v;
			Q.f=Q.g+dis[e[i].to];
			Q.to=e[i].to;
			heap.push(Q);
		}
	}
	return -1;
}
int main()
{
	int i,j;
	scanf("%d%d%d",&N,&m,&K);
	for(i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);//前向星存储
		add2(y,x,z);//反图求最短路 
	}
	SPFA();
	for(i=1;i<=K;i++)
	{
		memset(vst,0,sizeof(vst));
		printf("%d\n",A_star(i));
	}
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

### 前置知识
[A\*](https://pzj.blog.luogu.org/post-xue-xi-bi-ji-qi-fa-shi-sou-suo#)
### 解法
首先，我们要了解 A* 解决 k 短路的方法。

对于 A\*，我们要知道，它是以 $F(x)=g(x)+h(x)$ 为估价函数，其中 $g(x)$ 是当前的路程，现在考虑 $h(x)$。

首先，我们知道其实 `dij` 是以 $g(x)$ 在搜索。也就是说，其实 `dij` 就是在盲目地搜索。比如下面这个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/z5h7keg2.png)

首先，我们知道在最优策略下，我们是从 $1$ 到 $4$ 的。但是 `dij` 却是把最近的拉入最短路，也就是说，我们会先遍历 $3$，再遍历 $4$。

那么，我们可以构建一条长链，并且最后是一条权值很大的边。这样就可以诱导 `dij` 进入错误的子树，比如：

![](https://cdn.luogu.com.cn/upload/image_hosting/lyiqtywi.png)

那么，此时，`dij` 就会从 $2$ 一直遍历到 $9$，然后才遍历正解 $10$，并且是从 $1$ 到 $10$，此时前面的遍历就浪费了。

那么，我们可以发现，如果是 $n$ 个结点，构造这样一条长链，就会浪费 $n-1$ 个点。那么，$k$ 次操作后，就会浪费 $kn$ 个点，复杂度直接爆炸。

此时，我们可以发现：其实，我们可以加上当前节点到达终点的最短路径，作为 $h(x)$，因为它是我们至少要走的距离。

现在有人可能会问：如果是这样，那么我们不就要求全源最短路吗？

`dij` 单次的复杂度是 $O(m\log m)$，跑 $n$ 次的复杂度就是 $O(nm\log m)$。（这个复杂度好像可以承受？）

注意常数问题，我们可以转化一下问题：我们确定了终点，现在要求到达起点的最短路。

那么，此时我们只需要反向建边即可，然后跑一次 `dij`，求出的最短路做 $h(x)$。

这样，我们就 $O(m\log m)$ 地求出了 $h(x)$。

接下来就是一个 A* 的模板。

最后算一下：每个点最多遍历 $k$ 次，每次入队是 $O(\log n)$，那么最坏复杂度就是 $O(kn\log n)$，本题可过，具体细节见代码：
```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f//极大值
using namespace std;
const int maxn=1005;
int n,m,cnt,k,dis[maxn],ans[maxn];
bool vis[maxn];
inline int read(){
	int res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=getchar();
	}
	return res;
}//读入优化
struct edge{
	int to,val;
	bool operator <(const edge &t) const{
		return val>t.val;
	}
};
vector<edge> G[maxn],g[maxn];
priority_queue<edge> q;
inline void dij(int s){
	q.push(edge({s,0}));
	memset(dis,inf,sizeof(dis));
	dis[s]=0;
	while(!q.empty()){
		int u=q.top().to,w=q.top().val;
		q.pop();
		if(vis[u])
			continue;
		vis[u]=1;
		for(int i=0,len=g[u].size();i<len;++i){
			int v=g[u][i].to,r=g[u][i].val;
			if(dis[v]>dis[u]+r){
				dis[v]=dis[u]+r;
				q.push(edge({v,dis[v]}));
			}
		}
	}
}//初始化 h(x)
struct node{
	int id,val,F;
	bool operator <(const node &t) const{
		return F>t.F;
	}
};
priority_queue<node> Q;
vector<int> v;
inline void BFS(int s,int t,int k){
	Q.push(node({s,0,dis[s]}));
	while(!Q.empty()){
		int a=Q.top().id,b=Q.top().val;
		Q.pop();
		if(a==t){
			ans[++cnt]=b;
			if(cnt==k)
				return;
			continue;
		}
		for(int i=0,len=G[a].size();i<len;++i){
			int v=G[a][i].to,r=G[a][i].val;
			Q.push(node({v,b+r,b+r+dis[v]}));
		}
	}
	return;
}//A*
int main(){
	n=read(),m=read(),k=read();
	for(int i=1,u,v,w;i<=m;++i){
		u=read(),v=read(),w=read();
		if(v>u)
			swap(u,v);
		G[u].push_back(edge({v,w}));//建图
		g[v].push_back(edge({u,w}));//反向建图
	}
	dij(1);
	BFS(n,1,k);
	for(int i=1;i<=cnt;++i)
		printf("%d\n",ans[i]);
	for(int i=cnt+1;i<=k;++i)
		puts("-1");
	return 0;
}
```

---

## 作者：Weak_Konjak (赞：1)

##  $A * $ 大法好


##  1. 题目分析

### 就是求前k短路，而求k短路，当然就想到了A*算法


####  $ A *$ 算法是一种搜索算法，也被称为启发式搜索算法。

#### 我们$DFS$需要剪枝，而 $A *$ 算法则利用一个估值函数，让我们直奔答案搜索。

- 在本题中**求k短路**，如果记每个点i到终点1的距离为 $G(i) $ ,当前走到点i所走距离为 $F(i)$ , 那么，我们选取的估值函数就是 $F(i)+G(i)$


+ 如果这样做，并优先搜索估值较小的拓展节点，那么最先到达终点的就一定是最短路，第 $K$ 个到达终点的就是第 $K$ 短路。

- **正确性证明**：
考虑如果一条路径当前已经扩展到终点，那么$ G(x)=0$ ，$ 
F(x)+G(x)=F(x)$ 。
所以扩展到终点的路径都是按其实际长度从小到大出队的。

## 2. 代码实现

- 对于 $G(i)$ , 我们从终点开始走反向边求最短路，就可求得每个点到终点最短距离。
- 为了处理每个拓展节点的搜索顺序，使用优先队列存储，并重载运算符。
- 每次到达终点，输出答案，并使 $K$- - 。
- 最后处理-1的情况

## 3.代码
```cpp
#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
#define N 50000
using namespace std;
queue<int>q;
struct Node{
	int pos,dis;
};
#define node Node
priority_queue<Node> Q;
struct Edge{
	int to,w,nxt;
}edge[N],_edge[N];
int n,m,head[N],_head[N],g[N],tot,_tot,in[N];
bool operator < (const node &a,const node &b){
	return a.dis+g[a.pos]>b.dis+g[b.pos];
}
void add(int a,int b,int c)
{
	edge[++tot]=(Edge){b,c,head[a]};
	head[a]=tot;
}
void _add(int a,int b,int c)
{
	_edge[++_tot]=(Edge){b,c,_head[a]};
	_head[a]=_tot;
}
void SPFA()
{
	memset(g,0x3f,sizeof(g));
	g[1]=0;
	q.push(1);
	in[1]=1;
	while(q.size()){
		int u=q.front();q.pop();
		for(int i=_head[u];i;i=_edge[i].nxt){
			int v=_edge[i].to;
			if(g[v]>g[u]+_edge[i].w){
				g[v]=g[u]+_edge[i].w;
				if(!in[v]) q.push(v),in[v]=1;
			}
		}
		in[u]=0;
	}
}
int A_star(int k)
{
	Q.push((node){n,0});
	while(Q.size()){
		int u=Q.top().pos,dis=Q.top().dis;Q.pop();
		if(u==1){
			k--;
			cout<<dis<<'\n';
			if(!k) return 0;
		}
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].to,w=edge[i].w;
			Q.push((Node){v,w+dis});
		}
	}
	return k;
}
int main()
{
	int k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
		_add(b,a,c);
	}
	SPFA();
	int last=A_star(k);
	while(last--) puts("-1");
}
```




---

## 作者：小木虫 (赞：0)

### Preface  
这是一道 A* K 短路模板题。  
### Problem  
标准 K 短路题目。  
### Solution  
众所周知，我们可以利用可持久化左偏树来高效实现 K 短路。但是那个很难。我们有一个效率更低但是码量更小更简单的方法：A* 算法！  

接下来讲一下算法流程：  
1.跑一次反向最短路，求出每个点到终点的最短路。  
2.开始 A\*，设估值函数 $f(x)=g(x)+h(x)$，其中 $g$ 为搜索时的参数，表示已经走过的距离，$h$ 为从该点到终点的最短路。  
3.设立一个小根堆，以 $f$ 为关键字，更小的先出列进行搜索，一旦一个点被访问了超过 $k$ 次就不用再次入堆计算了，因为不会有需要计算的更大路径了。

接下来讲一下证明：  
我们发现，估值函数越小的元素，其就更有可能延伸出估值函数小的元素，或者说一定会延伸出一个比其它大估值函数元素的估值函数更小的元素，因为沿最短路走估值函数不变，颅内模拟一下，发现这个搜索过程非常的神奇：先走完最短路后会迅速找到第二短路的长度再沿着第二短路走一次...直到走完 $k$ 次。换句话说，那个估值函数实际上就是一条路径的长度。走完一条路径就相当于把最短的路径给删除了并把这条路径相邻的其它路径扩展出来，所有扩展出来的边集相当于没有走这条路时那个优先队列内的起始点包含的边集减去这条边。  

因为对于同一个点来说，到终点的最短路是一定的，所以到达一个点第 $j$ 次即代表这是从起点到该点的第 $j$ 短路。但其本身要是入队次数超过 $k$ 次显然就不对答案有贡献了，因为最多 $k$ 条路都经过它。  

不难发现这个算法复杂度是 $O(nk \log n)$ 的。

最后贴一下代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n,m,k,x,y,d;
struct EDGE{int v,w;};
vector <EDGE> edge[N];
vector <EDGE> G[N];
bool vis[N];int dis[N];
struct shortest_path{
	queue <int> Q;
	void SPFA(){
		for(int i=1;i<=n;i++)dis[i]=2e9;
		dis[1]=0;vis[1]=true;Q.push(1);
		while(!Q.empty()){
			int u=Q.front();Q.pop();
			vis[u]=false;
			for(int i=0;i<G[u].size();i++){
				int v=G[u][i].v;int w=G[u][i].w;
				if(dis[v]>dis[u]+w){
					dis[v]=dis[u]+w;
					if(!vis[v]){
						Q.push(v);
						vis[v]=true;
					}
				}
			}
		}
	}
}S;
int cnt[N];vector <int> res;
struct node{
	int u;int f;
	bool operator <(const node &a)const{
		return a.f+dis[a.u]<f+dis[u];
	}
};
priority_queue <node> Q;
int main(){
	//freopen("P2901_2.in","r",stdin);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&d);
		if(x<y)swap(x,y);
		edge[x].push_back((EDGE){y,d});
		G[y].push_back((EDGE){x,d});
	}
	S.SPFA();
	Q.push((node){n,0});
	while(!Q.empty()){
		int u=Q.top().u;
		int D=Q.top().f;
		Q.pop();cnt[u]++;
		if(cnt[u]>k)continue;
		if(u==1)res.push_back(D);
		for(int i=0;i<edge[u].size();i++)
			Q.push((node){edge[u][i].v,edge[u][i].w+D});
	}
	for(int i=0;i<res.size();i++)
		printf("%d\n",res[i]);
	for(int i=res.size()+1;i<=k;i++)
		printf("-1\n");
	return 0;
}
```


---

