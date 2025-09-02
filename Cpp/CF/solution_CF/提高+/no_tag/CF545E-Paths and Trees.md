# Paths and Trees

## 题目描述

Little girl Susie accidentally found her elder brother's notebook. She has many things to do, more important than solving problems, but she found this problem too interesting, so she wanted to know its solution and decided to ask you about it. So, the problem statement is as follows.

Let's assume that we are given a connected weighted undirected graph $ G=(V,E) $ (here $ V $ is the set of vertices, $ E $ is the set of edges). The shortest-path tree from vertex $ u $ is such graph $ G_{1}=(V,E_{1}) $ that is a tree with the set of edges $ E_{1} $ that is the subset of the set of edges of the initial graph $ E $ , and the lengths of the shortest paths from $ u $ to any vertex to $ G $ and to $ G_{1} $ are the same.

You are given a connected weighted undirected graph $ G $ and vertex $ u $ . Your task is to find the shortest-path tree of the given graph from vertex $ u $ , the total weight of whose edges is minimum possible.

## 说明/提示

In the first sample there are two possible shortest path trees:

- with edges $ 1–3 $ and $ 2–3 $ (the total weight is $ 3 $ );
- with edges $ 1–2 $ and $ 2–3 $ (the total weight is $ 2 $ );

And, for example, a tree with edges $ 1–2 $ and $ 1–3 $ won't be a shortest path tree for vertex $ 3 $ , because the distance from vertex $ 3 $ to vertex $ 2 $ in this tree equals $ 3 $ , and in the original graph it is $ 1 $ .

## 样例 #1

### 输入

```
3 3
1 2 1
2 3 1
1 3 2
3
```

### 输出

```
2
1 2 
```

## 样例 #2

### 输入

```
4 4
1 2 1
2 3 1
3 4 1
4 1 2
4
```

### 输出

```
4
2 3 4 
```

# 题解

## 作者：LawrenceSivan (赞：48)

# _CF545E Paths and Trees_

## 前言：

学这个的时候看了一些博客，感觉其实这一块网上很多博客和题解其实一些细节没有说太清楚。于是今天主要想说一下关于最短路径树的一些细节与处理问题。

## 最短路径树
$SPT$，就是从一张连通图中，有树满足从根节点到任意点的路径都为原图中根到任意点的最短路径的树。

$SBT$ 有以下特点：

- 树上任意不属于根的节点 $x$，$dis(root,x)=$ 原图走到 $x$ 的最短路。

- 全图联通，且有 $n-1$ 条边。

与最小生成树的区别：最小生成树只需要满足全图联通就可以了。

这个问题[这篇日报](https://xyzl.blog.luogu.org/Shortest-Path-Tree-SPT)写的很清楚。

一般用 _Dijkstra_ 实现。

大家都知道， _Dijkstra_ 实现过程就像是一条一条把边拉进来，于是我们只需要在松弛操作的时候记录一下前驱就可以了。

这个与一般的 _Dijkstra_ 无异。

```cpp
int pre[maxn];

bool vis[maxn];

ll dis[maxn],ans[maxn];

#define P pair<ll,int>
#define mp make_pair

inline void Dijkstra(int s){
	priority_queue <P,vector<P>,greater<P> > q;
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	q.push(mp(0,s));
	while(!q.empty()){
		int x=q.top().second;q.pop();
		if(vis[x])continue;
		vis[x]=true;
		for(re int i=head[x];i;i=nxt[i]){
			int v=to[i];
			if(dis[v]>=dis[x]+w[i]){
				dis[v]=dis[x]+w[i];
				pre[v]=i;//记录前驱
				q.push(mp(dis[v],v));
			}
		}
	}
}

```

复杂度 $O((n+m)logn)$

## 细节部分

### $1$：关于这道题的题目要求（权值和最小）：

#### 如何考虑

>给定一张带正权的无向图和一个源点，求边权和最小的最短路径树。

要求我们求出边权和最小的。

可以画图理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/ggl6h9qd.png)

显然，从节点 $1$ 到 节点 $5$ 有两条路径都是最短的。

如果选择 $1->2->3->5$ 这一条，那么最短路树长这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/5wt77kto.png)


权值和是 $1+1+1+1=4$.

如果选择 $1->4->5$ 这一条，最短路树长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/rwdssj97.png)


权值和是 $1+1+1+2=5$. 

根据题意，选择上面那一种。

为什么？

我们反向考虑：

当我们找到一个节点，发现有两条路径都是最短路，为了求最短路径树，必然只有一条路能被选到，也就是说，一个边会成为树边，另一个就是非树边，而最短路径树权值和最小是针对树边而言的，于是我们选择的问题就集中在连接这个点的两条边哪一个更小，并使之成为树边。

有的题解会这么写：

>为了满足本题的要求，还要生成树边权最小。自然是两点间路程相等情况下，经过的边数越多越好

其实这是不正确的。

通过一张图来看：

![](https://cdn.luogu.com.cn/upload/image_hosting/l4vi5ano.png)

可以发现，从节点 $1$ 到节点 $4$ 的最短路有两条。

路线一 $1->2->3->4$ ，边数是 $3$，

路线二 $1->5->6->7->8->9->4$ ， 边数是 $6$.

若选择路线一：

最短路树：

![](https://cdn.luogu.com.cn/upload/image_hosting/t475ygm8.png)

权值和为 $10+10+10+2+2+2+2+2=40$.

若选择路线二：

最短路树：

![](https://cdn.luogu.com.cn/upload/image_hosting/mzg6pz2m.png)


权值和为 $10+10+2+2+2+2+2+20=50$.

#### 代码实现

在满足这个问题的时候，大部分题解都会这么写：

```cpp
for(re int i=head[x];i;i=nxt[i]){
	int v=to[i];
	if(dis[v]>dis[x]+w[i]){
		dis[v]=dis[x]+w[i];
		pre[v]=i;
		q.push(mp(dis[v],v));
	}
	else if(dis[v]==dis[x]+w[i]&&w[i]<w[pre[v]])pre[v]=i;
}

```

就是说他们把权值相等时单独拿出来进行判断，进行松弛的时候如果松弛前的结果与松弛后的结果相等即 $dis[now]=dis[next]+w$，比较连接这条点的边的大小，即 $w[i]$ 与 $w[pre[next]]$ ，如果 $w[i]<w[pre[next]]$，那么更新当前的 $pre$ 。

其实这是完全**没必要**的。

画图理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/ggl6h9qd.png)

假如现在只有一个点没有在最短路树中。

由于我们使用的是堆优化的 _Dijkstra_ ，所以率先被扩展出来的点的 $dis$ 一定是更小的。

比如上图中，如果想要扩展到 $5$ ，那么只能从 $3$ 或者 $4$ 而来。

$dis[4]=1$ ,$dis[3]=2$ ，$dis[4]<dis[3]$， 显然是 $4$ 先扩展出来，然后才能扩展 $5$ 。

又因为他们的路径权值是一样的，这只能说明 连接 $3,5$ 的边的权值是小于连接 $4,5$ 的边的权值的。

根据上面的内容，我们需要选择 $3->5$ 这个边。

于是可以发现：

**在最短路相等的情况下，扩展到同一个节点，后出堆的点连的边权值一定更小**

所以我们直接就可以省去分类讨论的功夫，直接把他们写在一起：

```cpp
for(re int i=head[x];i;i=nxt[i]){
	int v=to[i];
	if(dis[v]>=dis[x]+w[i]){//这里加上等号
		dis[v]=dis[x]+w[i];
		pre[v]=i;
		q.push(mp(dis[v],v));
	}
	//else if(dis[v]==dis[x]+w[i]&&w[i]<w[pre[v]])pre[v]=i;
    //上面这行直接删掉
}

```

### $2$：关于边的 $id$ 记录

也有一些同志写的时候喜欢记录一下边的 $id$ ，虽然这样做也可以，但是我个人更喜欢另外一种方式：在循环的时候直接用 $i$ 来作为 $id$ ，这样做会省下一些空间~~虽然这些空间完全没有省下的必要~~

单独开 $id$ ：

```cpp

int head[maxn],to[maxn<<1],nxt[maxn<<1],id[maxn<<1],cnt;

ll w[maxn<<1];

inline void add(int u,int v,ll val,int i){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=val;
	id[cnt]=i;
	head[u]=cnt;
}

int main(){
	n=read();m=read();k=read();
	for(re int i=1,u,v;i<=m;i++){
		ll val;
		u=read();v=read();val=read();
		add(u,v,val,i);
		add(v,u,val,i);
	}
	
	...
}

```
用循环变量索引：

```cpp
int head[maxn],to[maxn<<1],nxt[maxn<<1],cnt;

ll w[maxn<<1];

inline void add(int u,int v,ll val){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=val;
	head[u]=cnt;
}


int main(){
	n=read();m=read();k=read();
	for(re int i=1,u,v;i<=m;i++){
		ll val;
		u=read();v=read();val=read();
		add(u,v,val);
		add(v,u,val);
	}
	
	...
}

```

但是需要注意的是，如果单独开一个 $id$ 数组用来记录 $id$ 的话，那么最后 $dfs$ 的时候 $id$ 就直接是答案了。

但是如果使用循环变量 $i$ 来进行索引，那么最后得出答案时需要 $(ans[i]+1)/2)$.

具体原因也很好想。

单独记录 $id$ 的话，双向边的 $id$ 是一样的，而循环变量索引却导致两条双向边 $id$ 不一样。

单独开 $id$ ：

```cpp
void dfs(int u){
	if(tot>=k)return;
	vis[u]=true;
	for(re int i=head[u];i;i=nxt[i]){
		int v=to[i],pos=id[i];
		if(vis[v])continue;
		if(dis[v]==dis[u]+w[i]){
			ans[++h]=pos;
			tot++;
			dfs(v);
			if(tot>=k)return;
		}
	}
}

int main(){
	
	...
	
	
	dfs(1);
	
	for(re int i=1;i<=h;i++){
		printf("%d ",ans[i]);
	}
	
}

```

用循环变量索引：

```cpp
void dfs(int u){
	if(tot>=k)return;
	vis[u]=true;
	for(re int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(vis[v])continue;
		if(dis[v]==dis[u]+w[i]){
			ans[++h]=i;
			tot++;
			dfs(v);
			if(tot>=k)return;
		}
	}
}

int main(){
	
	...
	
	
	dfs(1);
	
	for(re int i=1;i<=h;i++){
		printf("%d ",(ans[i]+1)/2);
	}
	
}

```

### $3$：关于输出问题

这个题完全不用排序啊。

>You may print the numbers of the edges in any order.

>If there are multiple answers, print any of them.

虽然题目翻译没说这个问题，但是关于输入输出的英文原文还是要看看的吧。

不太懂为什么别的题解要排一遍序。

_long long_ 还是要开的。

## CODE:

```cpp
//#define LawrenceSivan

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define re register
const int maxn=3e5+5;
#define INF 0x3f3f3f3f3f3f3f3f

int head[maxn],to[maxn<<1],nxt[maxn<<1],cnt;

ll w[maxn<<1];

inline void add(int u,int v,ll val){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=val;
	head[u]=cnt;
}

int pre[maxn];

bool vis[maxn];

ll dis[maxn],ans[maxn];

#define P pair<ll,int>
#define mp make_pair

inline void Dijkstra(int s){
	priority_queue <P,vector<P>,greater<P> > q;
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	q.push(mp(0,s));
	while(!q.empty()){
		int x=q.top().second;q.pop();
		if(vis[x])continue;
		vis[x]=true;
		for(re int i=head[x];i;i=nxt[i]){
			int v=to[i];
			if(dis[v]>=dis[x]+w[i]){
				dis[v]=dis[x]+w[i];
				pre[v]=i;
				q.push(mp(dis[v],v));
			}
			//else if(!vis[v]&&dis[v]==dis[x]+w[i]&&w[i]<w[pre[v]])pre[v]=i;
		}
	}
}

int n,m,s;

inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

int main(){
#ifdef LawrenceSivan
    freopen("aa.in","r",stdin);
    freopen("aa.out","w",stdout);
#endif
	n=read();m=read();
	for(re int i=1,x,y;i<=m;i++){
		ll val;
		x=read();y=read();val=read();
		add(x,y,val);
		add(y,x,val);
	}
	
	s=read();
	
	Dijkstra(s);
	
	ll sum=0,tot=0;
	for(re int i=1;i<=n;i++){
		if(i==s)continue;
		int pos=pre[i];
		sum+=w[pos];
		ans[++tot]=pos;
	}

	printf("%lld\n",sum);
	
	for(re int i=1;i<=tot;i++){
		printf("%lld ",(ans[i]+1)/2);
	}



    return 0;
}

```


---

## 作者：RuntimeErr (赞：6)

# 浅谈 SPT

本篇文章参考 [这篇日报](https://xyzl.blog.luogu.org/Shortest-Path-Tree-SPT)

## 介绍

SPT，即 Shortest Path Tree，最短路径树。

如下图，我们假设源点为 1，

![](https://cdn.luogu.com.cn/upload/image_hosting/0t8q2v1w.png)

则由它生成的 SPT 为：

![](https://cdn.luogu.com.cn/upload/image_hosting/vphk2sy3.png)

从中我们可以发现 SPT 要满足的一些性质：

- 是一颗生成树，每个点**连通**。
- 从**根节点到树上任意一点的距离**即为原图中**源点到该点**的**最短路**。

## 我们如何构造 SPT 呢？

我们可以用 Dijkstra、Floyd 等算法，这里我们只说用 Dijkstra 的做法。

我们记录一个数组 $pre$，$pre_i$ 表示从源点到点 $i$ 的**最短路径**上与 $i$ 相连的**边的编号**，即 $i$ 的上一条边，每次松弛时更新。

```cpp
//这是松弛的代码
for(int i=h[u];i;i=ne[i]){
	int v=e[i];
	if(dis[v]>=dis[u]+w[i]){
		dis[v]=dis[u]+w[i];
		q.push((node){v,dis[v]});
		pre[v]=i;
	}
}
```
这里我来解释一下为什么代码中 $dis_v>=dis_u+w_i$。首先 $dis_v>dis_u+w_i$ 时显然是要更新的；当 $dis_v=dis_u+w_i$ 时，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/p59wf170.png)

对于 $1$ 到 $5$，我们有两个路径：

1. `1->3->5`

2. `1->3->2->5`

它们的长度都是 $3$。但是我们来看一下两种路径下的生成树：

这是第一种：

![](https://cdn.luogu.com.cn/upload/image_hosting/wxzrsfen.png)

这是第二种：

![](https://cdn.luogu.com.cn/upload/image_hosting/fibp4592.png)

第一种的权值和为 $5$，第二种的权值和为 $4$，显然第二种才是我们要求的 SPT。从中我们可以看出，我们要使任意两点相连的边的**边权尽可能小**。

那为什么直接加个等于号就行了呢？[这篇博客](https://www.luogu.com.cn/blog/LawrenceSivan/cf545e-paths-and-trees-zui-duan-lu-jing-shu-post)讲的很好。

还是以原图为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/p59wf170.png)

我们要扩展到 $5$，首先会扩展到 $2$ 和 $3$。由于 $dis_2<dis_3$，根据 Dijkstra 的性质，会先扩展 **$dis$ 最小**的那一个，所以 $3$ 会先被扩展到。由于源点经过 $2$ 和 $3$ 到 $5$ 的路径长度相等，又 $dis_2>dis_3$，所以 $edge_{2,5}<edge_{3,5}$。因为 $2$ 是后扩展到的，所以直接覆盖就行了。如果还有点满足这种关系也同理。

再来说说输出解。SPT 是一颗树，也就是说，从根到某一结点**只有一条**简单路径，只有 $n-1$ 条边。那么除根结点外，**每一个结点都对应一条边**，也就是它们的 $pre$。由于加的是双向边，输出的时候应为 $(pre_i+1)/2$。

### tips: 不开 long long 见祖宗qwq

## $Code:$
```cpp
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

const int N=3e5+10,M=N<<1,inf=0x7f;

int n,m,s;
int h[N],e[M],ne[M],w[M],idx;
int pre[N];
long long dis[N];
bool vis[N];
struct node{
	int to;long long w;
	inline bool operator <(const node& a)const{
		return w>a.w;
	}
};
priority_queue<node>q;

inline void add(int a,int b,int c){
	e[++idx]=b,ne[idx]=h[a],w[idx]=c,h[a]=idx;
}

void dij(){
	memset(dis,inf,sizeof dis);
	q.push((node){s,0});dis[s]=0;
	while(!q.empty()){
		int u=q.top().to;q.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(int i=h[u];i;i=ne[i]){
			int v=e[i];
			if(dis[v]>=dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				q.push((node){v,dis[v]});
				pre[v]=i;
			}
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int a,b,c;scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);add(b,a,c);
	}
	scanf("%d",&s);
	dij();
	long long sum=0;
	for(int i=1;i<=n;++i){
		if(i==s)continue;
		sum+=w[pre[i]];
	}
	printf("%lld\n",sum);
	for(int i=1;i<=n;++i)if(i!=s)printf("%d ",pre[i]+1>>1);
	return 0;
}
```

---

## 作者：Farkas_W (赞：4)

### 思路：

$\quad$只需要以题目给定的 $u$ 为起点跑一遍 $Dijkstra$ 最短路即可，每次记录每个点的前驱(即到达这个点的边)，注意有多个可以选择的边中选择边权最小的，感觉很像一个最小生成树，最后记得要记录树上的边权并排序再输出，起点 $u$ 是没有前驱的，所以要从 $2$ 开始输出。

$\quad$如果还不能理解就看看代码吧，有一些关键的注释。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cstring>
using namespace std;
#define re register int
#define int long long
#define LL long long
#define il inline
#define next nee
#define inf 1e18
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=3e5+5;
int n,m,next[N<<1],go[N<<1],head[N],tot,dis[N],s[N<<1],t,du[N],ans;
bool b[N];
il void Add(int x,int y,int z)
{
  next[++tot]=head[x];head[x]=tot;
  go[tot]=y;s[tot]=z;
}
struct node{
  int pos,dis;
  il bool operator<(const node &x)const
  {return dis>x.dis;}
};
priority_queue<node>q;
il void Dijkstra(int p)//板子Dijkstra
{
  for(re i=1;i<=n;i++)dis[i]=inf;dis[p]=0;
  q.push((node){p,0});
  while(!q.empty())
    {
      node tmp=q.top();q.pop();
      int x=tmp.pos;
      if(b[x])continue;
      b[x]=1;
      for(re i=head[x];i;i=next[i])
	{
	  int y=go[i];
	  if(dis[y]>dis[x]+s[i])
	    {
	      du[y]=i;//du记录前驱编号为i的边
	      dis[y]=dis[x]+s[i];
	      q.push((node){y,dis[y]});
	    }
	  else if(dis[y]==dis[x]+s[i])//有多条最短路径时
	    {if(s[du[y]]>s[i])du[y]=i;}//选择边权小的
	}
    }
}
signed main()
{
  n=read();m=read();
  for(re i=1;i<=m;i++)
    {re x=read(),y=read(),z=read();Add(x,y,z);Add(y,x,z);}
  t=read();
  Dijkstra(t);
  for(re i=1;i<=n;i++)ans+=s[du[i]];//ans统计答案
  for(re i=1;i<=n;i++)dis[i]=du[i]+1>>1;
  sort(dis+1,dis+n+1);//别忘了排序
  print(ans);putchar('\n');
  for(re i=2;i<=n;i++)print(dis[i]),putchar(' ');//从2开始输出
  return 0;
}
```

---

## 作者：zsc2003 (赞：4)

由于本人比较弱，所以不会将题解的代码整齐的输出，所以只

好用截屏了。。。

本题共有60多个测试点，数据量非常的大。

标注和代码如下：

![](https://cdn.luogu.com.cn/upload/pic/19336.png)
![](https://cdn.luogu.com.cn/upload/pic/19338.png)
![](https://cdn.luogu.com.cn/upload/pic/19337.png)
![](https://cdn.luogu.com.cn/upload/pic/19339.png)

---

## 作者：ModestCoder_ (赞：3)

题意神奇，反正我是理解了好长的时间

差不多就是求一个生成树，使得任意点到源点的最短路等于原图中的最短路。再让这个生成树边权和最小

很显然得先dij一下

考虑dij过程中松弛的条件，跟一般的dij不一样，为了满足本题的要求，还要生成树边权最小。自然是两点间路程相等情况下，经过的边数越多越好（感性理解一下）

最短路跑出之后如何得知建出来的生成树？

简单，对于每个点开一个$pre$数组表示父亲连到自己的边的编号。然后可以通过这个解决题目交给我们的任务

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 300010
#define inf 1e18
#define int long long
using namespace std;
struct node{
	int val, len;
	bool operator < (const node &x) const{ return x.len < len; }
};
priority_queue <node> q;
struct Edge{
	int to, next, len;
}edge[maxn << 1];
int num, head[maxn], n, m, rt, vis[maxn], dis[maxn], pre[maxn];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

void addedge(int x, int y, int z){ edge[++num] = (Edge) { y, head[x], z }; head[x] = num; }

signed main(){
	n = read(), m = read();
	for (int i = 1; i <= m; ++i){
		int x = read(), y = read(), z = read();
		addedge(x, y, z); addedge(y, x, z);
	}
	rt = read();
	for (int i = 1; i <= n; ++i) dis[i] = inf; dis[rt] = 0;
	q.push((node) {rt, 0});
	while (!q.empty()){
		node tmp = q.top(); q.pop();
		int u = tmp.val, len = tmp.len;
		if (vis[u]) continue; vis[u] = 1;
		for (int i = head[u]; i; i = edge[i].next){
			int v = edge[i].to;
			if (dis[v] >= len + edge[i].len){//不一样的松弛条件，注意这个等号
				dis[v] = len + edge[i].len, pre[v] = i;
				if (!vis[v]) q.push((node) {v, dis[v]});
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) if (i != rt) ans += edge[pre[i]].len;
	printf("%lld\n", ans);
	for (int i = 1; i <= n; ++i) if (i != rt)  printf("%lld ", (pre[i] + 1) >> 1);
	return 0;
}
```


---

## 作者：Y_J_Y (赞：2)

一看这道题目,摆明的是让我们用最短路树的做法,然后看看题解,发现第一篇的题解有一点问题,复制之后好像过不去样例(并且代码中解释较少),所以就决定自己打一波发一下最短路树的题解

(下面的码风因为受到了lrj的dij的模板的影响,使用struct来封装)

下面就是最短路树的解释了:

(敲重点)

一般的方法是先用dij跑一遍,在跑的过程中不断的保存每个点的前驱,换句话说也就是每一个点的爸爸,然后在最终的输出中使用即可

### 也就是这个最短路树的每一条边是维护这源点到各个点的最短路

(希望这一篇简洁的代码能够成为各位打最短路树时的一个好借鉴)
(这个模板还可以在[这个中使用](https://www.luogu.com.cn/problem/CF1005F))各位大佬打完后还可以打打这道题

然后在那个松弛的时候的做法有一点不同

在下面代码的注释中会着重的辅助讲解
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf=1e18;
const int maxn=300050;
struct Edge{//dij用的,不解释
    int from,to,id;
    ll dist;
    Edge(int f,int t,type d,int i):from(f),to(t),dist(d),id(i){}
};
struct HeapNode{//这是优先队列,想必每个看到这道题并想打的人都会吧
    ll d;
    int u;
    HeapNode(ll dd,int uu):d(dd),u(uu){}
    bool operator<(const HeapNode& rhs)const{
        return d>rhs.d;
    }
};
struct Dijkstra{//真*模板
    int n,m;
    vector<Edge> edges;//记录的是边
    vector<int> g[maxn];
    bool done[maxn];//vis,即判断有无用过
    ll d[maxn];//dist 距离
    int p[maxn];//记录前驱
    void init(int n){//初始化
        this->n=n;
        for(int i=0;i<n;++i) g[i].clear();
        edges.clear();
    }
    void add(int from,int to,type dist,int id){//这是加边的操作
        edges.push_back(Edge(from,to,dist,id));
        m=edges.size();
        g[from].push_back(m-1);
    }
    void dijkstra(int s){
        priority_queue<HeapNode> q;
        for(int i=0;i<n;++i) d[i]=inf;
        d[s]=0;
        memset(done,0,sizeof(done));
        que.push(HeapNode(0,s));
        while(!que.empty()){
            HeapNode x=que.top();
            q.pop();
            int u=x.u;
            if(done[u]) continue;
            done[u]=true;
            for(int i=0;i<g[u].size();++i){
                Edge& e=edges[g[u][i]];
                if(d[e.to]>d[u]+e.dist){//这里就需要好好地理解了,当不相等的时候,显然就是一样的操作
                    d[e.to]=d[u]+e.dist;
                    p[e.to]=g[u][i];
                    q.push(HeapNode(d[e.to],e.to));
                }
                else if(d[e.to]==d[u]+e.dist && e.dist<edges[p[e.to]].dist){
                //但是当他们相等时,显然是要越多越好,想一想,为什么
                    p[e.to]=g[u][i];
                }
            }
        }
    }
    void solve(int s){//这就是做完dij后解决问题的东西了
        ll sum=0;
        vector<int> ans;//这个ans记录的就是答案了
        for(int i=0;i<n;++i){
            if(i==s) continue;//显然不记录自己到自己
            Edge& e=edges[p[i]];//前驱的作用
            ans.push_back(e.id);//记录标号,因为最后要输出路径
            sum+=e.dist;//这就是记录路长了
        }
        sort(ans.begin(),ans.end());
        printf("%lld\n",sum);//输出
        for(int i=0;i<ans.size();++i){
            printf("%d%c",ans[i],i+1==ans.size()?'\n':' ');
        }
    }
};
int n,m;
Dijkstra dij;//因为是struct
int main(){//下面很好理解
    scanf("%d%d",&n,&m);
    dij.init(n);
    for(int i=1;i<=m;++i){
        int u,v;
        ll d;
        scanf("%d%d%lld",&u,&v,&d);
        --u,--v;
        dij.add(u,v,d,i);
        dij.add(v,u,d,i);
    }
    int s;
    scanf("%d",&s);
    --s;
    dij.dijkstra(s);
    dij.solve(s);
    return 0;
}
```

~~望过啊~~

---

## 作者：Hexarhy (赞：1)

### Preface

最短路径树 (SPT) 模板题。看[洛谷日报](https://xyzl.blog.luogu.org/Shortest-Path-Tree-SPT)发现这玩意儿其实并不难学。

### Solution

在 dijkstra 求最短路的时候，每次对 $u\to v$ 松弛的时候，都更新 $u\to v$ 所选取的边的编号，即 $pre_v$。由于题目要求最小 SPT，因此松弛的条件要取等号，并更新更小的边。

题解区貌似没有比较简单的 `vector` 实现代码。链式前向星固然方便，不过对于 `vector` 党只需多开一个结构体存边，记录编号即可。 

### Code

```cpp
typedef const int cint;
typedef long long ll;
cint MAXN=3e5+5;
int n,m,s;
struct node
{
	int to;ll val;int id;//id 即编号
	bool operator<(const node& a)const
	{
		return val>a.val;
	}
};
struct Edge
{
	int u,v,w;
}e[MAXN];//记录边的编号
vector<node> edge[MAXN];
bool visit[MAXN];
ll dis[MAXN];
int pre[MAXN];

void dijkstra(void)
{
	#define pli pair<ll,int>
	for(int i=1;i<=n;i++)	dis[i]=LLONG_MAX;
	priority_queue<pli,vector<pli>,greater<pli>> q;
	q.emplace(make_pair(dis[s]=0,s));
	while(!q.empty())
	{
		const int u=q.top().second;
		q.pop();
		if(visit[u])	continue;
		visit[u]=true;
		for(const auto& cur:edge[u])
		{
			cint v=cur.to;const ll w=cur.val;
			if(dis[v]>=dis[u]+w)
			{
				if(dis[v]>dis[u]+w || e[pre[v]].w>w)	pre[v]=cur.id;//核心
				dis[v]=dis[u]+w;
				q.emplace(make_pair(dis[v],v));
			}
		}
	}
}

int main()
{
	read(n,m);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;read(u,v,w);
		e[i]=Edge{u,v,w};
		edge[u].emplace_back(node{v,w,i});
		edge[v].emplace_back(node{u,w,i});
	}
	read(s);
	dijkstra();
	ll sum=0;
	vector<int> ans;
	for(int i=1;i<=n;i++)
	{
		if(i==s)	continue;
		sum+=e[pre[i]].w;
		ans.emplace_back(pre[i]);
	} 
	sort(ans.begin(),ans.end());
	cout<<sum<<endl;
	for(const auto& Ans:ans)	cout<<Ans<<' ';
	cout<<endl;
	return 0;
}
```

---

## 作者：Vidoliga (赞：0)

# 题解

## 这很明显是一道$SPT$(最短路径树)的模板题。

### 前缀芝士$:$

1. **最短路径树**的定义及部分前缀芝士。

2. $Dijsktra$加**堆优化**。

## 1.思路$:$

首先我们得保证**源点**到任意的一点的距离一定是**最小的**。那么这个$Dijsktra$可以做到。

#### 重难点$:$

我们如何保证**整棵树的权值和**为最小的呢$?$此时，我们就要讨论一个**贪心**的思路$:$

我们在保证**每个点到源点的距离最小的前提下**，如果有一条边在进行**松弛**操作后，如果目前考虑的一条路线和之前的路线距离相等，那么我们选择上一个点到这个点之间的线段距离**短的那一条**。这样就可以做到每一条都是最小的。即**整棵树的权值和**为最小的。

## 2. 细节$:$

1. 如果我们是用**链式前向星**存图，因为我们是**无向图**，所以我们最后必须将节点信息$ans$转换为$(ans+1)/2$。(0<=ans<2n)
2. 记得$sort$一遍
3. $long$ $long$别忘记开$!$

## 3. $Code:$

```cpp
//代码没过多注释,前面讲解的够清楚了
#include<cstdio>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<algorithm>
#define INF 92233720354775807
#define LL long long
#define rint register int
#define maxn 300005
#define maxm 600010
using namespace std;
inline int read(){
	rint d(0),f(1);char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		d=(d<<1)+(d<<3)+(ch^48);
		ch=getchar();
	}
	return d*f;
}
void writes(LL x){
	if(x>9) writes(x/10);
	putchar(x%10+48);
}
inline void write(LL x){
	if(x<0) putchar('-'),writes(-x);
	else writes(x);
	putchar(' ');
}
struct Edge{
	int to,w;
	LL next;
}edge[maxm];
int n,m,s,cnt,head[maxn],pre[maxn];//pre是一个点前面的线,用于记录答案QwQ
LL dis[maxn],ans[maxn];
bool vis[maxn];
inline void add(int u,int v,int w){
	cnt++;
	edge[cnt].to=v;
	edge[cnt].w=w;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
struct node{
	int id;LL dist;
	bool operator < (const node &x) const{
		return dist>x.dist;
	}
};
void Dijkstra(int start){
	priority_queue<node> q;
	for(rint i=1;i<=n;i++){
		dis[i]=INF;vis[i]=false;
	}
	dis[start]=0;
	node Start;
	Start.dist=0,Start.id=start;
	q.push(Start);
	while(!q.empty()){
		node now=q.top();
		int u=now.id;
		q.pop();
		if(vis[u]) continue;
		vis[u]=true;
		for(rint i=head[u];i;i=edge[i].next){
			int next=edge[i].to,w=edge[i].w;
			if(dis[next]>dis[u]+w){
				dis[next]=dis[u]+w;
				node nt;
				nt.id=next;
				nt.dist=dis[next];
				q.push(nt);
				pre[next]=i;
			}
			else if(dis[next]==dis[u]+w&&w<edge[pre[next]].w) pre[next]=i;
		}
	}
}
signed main(){
	n=read(),m=read();
	for(rint i=1;i<=m;i++){
		int x=read(),y=read();
		LL w=read();
		add(x,y,w),add(y,x,w); 
	}
	s=read();
	Dijkstra(s);
	LL sum=0,tot=0;
	for(rint i=1;i<=n;i++){
		if(i==s) continue;
		int id=pre[i];
		sum+=edge[id].w;
		ans[++tot]=id;
	}
	sort(ans+1,ans+tot+1);
	write(sum);
	putchar('\n');
	for(rint i=1;i<=tot;i++) write((ans[i]+1)/2);
	return 0;
}

```

完结撒花$qwq$。

---

## 作者：银河AI (赞：0)

update->2021.4.24  21:05  更改了一些笔误（~~点的边权~~）

同 Hexarhy 大佬，也是从[日报](https://xyzl.blog.luogu.org/Shortest-Path-Tree-SPT)过来的。

### 前置芝士

- 1.最短路径树的各种定义。

- 2 .dijkstra堆优化
 
### 解题思路

首先这题是一道最短路径树的模板题（翻译都写了）

最短路径树可以用最短路算法（dijkstra或floyd） 来实现，以下说一下dij的堆优化算法实现。

首先跑 dij ，在每一次的 $x->y$ 松弛操作之后，考虑如果 $y$ 点的前驱比这条边要大，因为要求**最短路径树**，所以将 $y$ 点的前驱该为当前这条边。

边的序号话，链式前向星建边的时候就已经定好了序号，因为是双向边，所以每条边真正的编号是 $(i+1)/2$ ，$i$ 为原编号。

当然如果用 vector 建边的话，应该就不用考虑那么多了，具体的可参考[Hexarhy的博客](https://www.luogu.com.cn/blog/80049/solution-cf545e)

最后输出的是，除源点之外的每个点的前驱的边权和，和每个点的前驱的权（升序输出）。

### 参考代码

```cpp
#include<cstdio>
#include<cmath>
#include<queue>
#include<algorithm>
#define int long long
using namespace std;
const int N=3e5+1,inf=0x3f3f3f3f3f3f3f3f;
priority_queue<pair<int,int> ,vector<pair<int,int> >,greater<pair<int,int> > > pq;
int n,m;
int x,y,z;
int s,sum;
struct edge{
	int to,ne,dis;
}e[N<<1];
int adj[N],l;
int dis[N],vis[N],pre[N],ans[N],len;
inline void add(int x,int y,int z){e[++l].to=y,e[l].ne=adj[x],e[l].dis=z,adj[x]=l;}
inline void dij(int s){
	for(int i=1;i<=n;i++) dis[i]=inf;
	dis[s]=0;
	pq.push(make_pair(0,s));
	while(!pq.empty()){
		int x=pq.top().second,y=pq.top().first;pq.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=adj[x];i;i=e[i].ne){
			int y=e[i].to,z=e[i].dis;
			if(dis[y]>dis[x]+z){
				dis[y]=dis[x]+z;
				pq.push(make_pair(dis[y],y));
				pre[y]=i;
			}
			if(dis[y]==dis[x]+z&&z<e[pre[y]].dis) pre[y]=i;
		}
	}
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++) scanf("%lld%lld%lld",&x,&y,&z),add(x,y,z),add(y,x,z); 
	scanf("%lld",&s);
	dij(s);
	for(int i=1;i<=n;i++){	
		if(i==s) continue;
		int k=pre[i];
		sum+=e[k].dis;
		ans[++len]=k;
	}
	sort(ans+1,ans+len+1);
	printf("%lld\n",sum);
	for(int i=1;i<=len;i++) printf("%lld ",(ans[i]+1)/2);
} 
```




-------------------------------------------------------------------------------------

参考资料：[你谷日报](https://xyzl.blog.luogu.org/Shortest-Path-Tree-SPT)


---

## 作者：Gorenstein (赞：0)

这是一道最小路径树的板子题。

### 最短路径树

最短路径树指的是在一张连通图中，从**根到任意点的路径**都是**原图从根到任意点的最短路径**的生成树。

### 如何求解？

根据定义，我们可以想到单源最短路径的求法。代码以 $Dijkstra$ 为例。

每次选取 $dis$ 最小的未确定的点加入已确定的最短路集合 $S$。对于点 $v$，最终到 $v$ 点的最短路 $dis[v]=dis[u]+w(u,v)$，必然是由某次加入集合 $S$ 的点 $u$ 的出边 $w(u,v)$ 松弛产生的，且 $dis[u]$ 是到 $u$ 的最短路。

请各位理解这点。之后，套上 $Dijkstra$ 板子就**基本**完事了。

实际上就将其中一段改成了这样：

```cpp
for(int i=head[x];i;i=nxt[i]){
	int y=ver[i];
	if(d[y]>d[x]+val[i])
		pre[y]=i,	//记录松弛的边(前驱)
		d[y]=d[x]+val[i],
		q.push((node){y,d[y]});
}
```

也就是记录松弛它的边即可。

那么我们如何做到让数边权值和最小？我们采取贪心的思想。如果遇到**松弛前后结果相等**，即 $dis[v]=dis[u]+w(u,v)$，此时**对比连接这点的边的大小**，如果 $val[pre[v]]>val[u]$ 则更新 $pre$。

因此实际上也就多了这行代码：

```cpp
if(d[y]==d[x]+val[i]&&val[pre[y]]>val[i])pre[y]=i;
```

### 实现细节

- 需要注意的是此题需要开 $\text{long long}$。
- 另外注意让你输出的是什么。

至于代码，基本就是在dij上略加改动了。我已经将重要部分提出，因此不单独放完整代码，建议各位完全独立打出。

---

