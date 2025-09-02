# [PA 2014] Kuglarz

## 题目描述

魔术师的桌子上有 $n$ 个杯子排成一行，编号为 $1,2,…,n$，其中某些杯子底下藏有一个小球，如果你准确地猜出是哪些杯子，你就可以获得奖品。

花费 $c_{ij}$ 元，魔术师就会告诉你杯子 $i,i+1,…,j$ 底下藏有球的总数的奇偶性。

采取最优的询问策略，你至少需要花费多少元，才能保证猜出哪些杯子底下藏着球？

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 2\times 10^3$，$1\le c_{ij}\le 10^9$。

## 样例 #1

### 输入

```
5
1 2 3 4 5
4 3 2 1
3 4 5
2 1
5```

### 输出

```
7```

# 题解

## 作者：逃离地球 (赞：51)

## 题目大意
* 桌子上有 $n$ 个杯子排成一行，其中某些杯子下藏有一个小球。你可以花费 $c(l,r)$ 元，询问区间 $[l, r]$ 内球总数的奇偶性。求猜出每个杯子是否有球的的最小花费。

* $n≤2×10^3$。

## 题解

* 猜出每个杯子里是否有小球相当于我们知道每个杯子里小球个数的奇偶性。
* 当我们知道区间 $[l,r_1]$ 和区间 $[l,r_2]$ 的奇偶性后，我们就能知道区间 $[r_1+1,r_2]$ 的奇偶性。
* 考虑把 $n$ 个杯子看作 $n$ 个点，把知道 $[l,r]$ 的奇偶性看作从 $l$ 点到 $r$ 点连边。那么图中有边 $(l,r_1)$ 和边 $(l,r_2)$ 就相当于图中有边 $(r_1+1,r_2)$。
* 但是感觉这条性质不是很好用，因为不能推导出连通性。如果能把 $r_1+1$ 里的 $+1$ 去了，就能推到出一条很强的性质：两点之间联通相当于两点之间有一条边。
* 于是考虑改变边的定义，知道 $[l,r]$ 的奇偶性相当于从 $l-1$ 到 $r$ 连边。那么有边 $(l,r_1)$ 和边 $(l,r_2)$ 就相当于有边 $(r_1,r_2)$。也就是说，两点之间联通相当于两点之间有一条边。

* 再看我们的目的：知道每个杯子里小球个数的奇偶性。放在那张图中，就是要让所有的点 $i-1$ 和点 $i$ 都联通。也就是说，这张图是一张连通图。

* 于是，我们先把图建出来，在点 $l-1$ 和 点 $r$ 之间连一条边权为 $c(l,r)$ 的边。然后再选出其中的一些边，使得这张图是一张连通图。
* 同时我们还要最小化花的钱，即最小化选出的边权的和。
* 求出这张图的最小生成树即可，时间复杂度 $O(n^2 \log n)$。

---

## 作者：PanH (赞：24)

**最小生成树好题。**

没想到异或什么的，但是思路其实差不多。

首先，有一个比较明显的结论:

**必须要知道每一个位置的奇偶性，才能知道所有位置有没有小球。**

再仔细一想，每一个位置的奇偶性可以有两种方法推出来：

- 直接花费 $a_{i,i}$ 得到；
- 花费两个区间的价值 $a_{i,j}+a_{i+1,j}$ 得到。

可是区间的价值又可以从两个区间推来，那就很难处理了。

考虑把点权变成边权，把位置 $i$ 变成 $i-1$ 与 $i$ 之间的一条边。

也就是说，我们要知道所有相邻点之间边的信息。

而之前已经的得到两种推出位置奇偶性的方法，可以用下图的两种方法表示：

![](https://cdn.luogu.com.cn/upload/image_hosting/wm3ptj7m.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

以上两种方法都可以得到 $2$ 和 $3$ 之间那个位置的信息。

总结一下，就是说，**我们要连边，使每个点都被连到。**

求最小生成树。

code：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<class T>inline void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
const int N=2e3+5;
int a[N][N],n,m;
struct edge{
	int next,to,w;
}e[N*N*2];
int head[N*N],cnt,ans,dis[N*N],vis[N*N];
void add(int u,int v,int w)
{
	e[++cnt]={head[u],v,w};
	head[u]=cnt;
}
signed main()
{
	read(n);
	for(int i=1;i<=n;i++)
		for(int j=i,w;j<=n;j++)
			read(w),add(i-1,j,w),add(j,i-1,w);
	priority_queue<pair<int,int> > q;
	memset(dis,0x3f,sizeof(dis));
	q.push(make_pair(0,1)),dis[1]=0;
	while(!q.empty())
	{
		int x=q.top().second;q.pop();
		if(vis[x])	continue;
		vis[x]=1,ans+=dis[x];
		for(int i=head[x];i;i=e[i].next)
		{
			int y=e[i].to;
			if(dis[y]>e[i].w)	dis[y]=e[i].w,q.push(make_pair(-dis[y],y));
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：7KByte (赞：17)

最小生成树好题。

第一眼看的像区间DP题。因为我们知道$[a,b]$和$[a,b+1]$的奇偶性，就知道$b+1$处是否有小球。

但这个想法太naive了，区间DP的复杂度$O(N^3)$显然是不可以的。

我们将问题转换一下。如果我们知道每一个位置是否有小球，那么就可以知道区间$[0,i]\ (1\le i\le n)$的奇偶性。

相反，如果我们知道区间$[0,i]\ (1\le i\le n)$的奇偶性，那么我们呢就可以知道每个位置是否有小球。所以我们只用花费最小代价求知每个$[0,i]$区间的奇偶性。

如果我们知道区间$[0,i-1]$和$[i,j]$的奇偶性，就可以知道$[0,j]$的奇偶性。同理，如果知道$[0,j]$和$[i,j]$的奇偶性，我们就可以知道$[0,i-1]$的奇偶性。

位置0是我们虚构的节点，该位置上一定没有小球，所以$[0,0]$为偶。

对于一次询问$[i,j]$，我们将$[0,i-1]$和$[0,j]$之间连一条权值为$c_{i,j}$的边，表示知道其中一个，花费$c_{i,j}$代价可以知道另一个。

只要保证所有点和$[0,0]$联通，即整个图联通，即可保证知道所有$[0,i]$的奇偶性，就可以知道所有位置上是否有小球。

图已经建好了，直接求最小生成树即可。边数较多，建议使用``Prim``，但笔者很菜只会``kruscal``。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 2005
typedef long long ll;
using namespace std;
int n,fa[N],T;
int get(int x){return x==fa[x]?x:fa[x]=get(fa[x]);}
struct node{int x,y,val;bool operator<(const node o){return val<o.val;}}a[N*N];
int main(){
	scanf("%d",&n);
	rep(i,1,n)fa[i]=i;
	rep(i,1,n)rep(j,i,n){
		int x;scanf("%d",&x);
		a[++T].x=i-1;a[T].y=j;a[T].val=x;
	}
	sort(a+1,a+T+1);
	ll ans=0;
	rep(i,1,T)if(get(a[i].x)!=get(a[i].y)){
		ans+=a[i].val;
		fa[get(a[i].x)]=get(a[i].y);
	}
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：Vocalise (赞：8)

题解竟只有一篇？这题私以为很经典。

首先这题给出的是一个 $n^2$ 大小的三角矩阵。稍微思考一下，就可以确定本题的时间下界是 $n^2$。

然后，正如另一篇题解所说，如果有球则该位置上的数为 $1$，否则为 $0$，那么一次询问就相当于得到 $xor$ 运算的前缀和相异或。（借用一个定义，设原数列为 $\{a_n\}$，$xor$ 前缀和为 $\{b_n\}$。）

那么，我们思考获得 $i$ 位置上的数的充分必要条件。不难发现， $a_i$ 可以看作 $b_i xor b_{i - 1}$。也就是说，必须要知道 $b_i$；再知道一个 $b_{i - 1}$。

上面都是从前缀绚问上思考的。如果拓展到任意区间询问，又如何呢？

不难看出，设区间 $[i,j]$ 异或和为 $d_{i,j}$，则要得到 $a_i$ 必然有一些询问区间与另一些询问区间相减，得到唯一一个元素 $a_i$。

好像再无可分析；但是我们可以考虑一下 $xor$ 运算的性质。显然有：

$$(a xor b)xor(b xor c)=a xor c$$

放在这题，有什么用呢？

那就是：如果已知 $a xor b$ 和 $b xor c$，那么可以求 $a xor c$。

这个性质可以拓展成无穷多个元素。

可发现，如果说 $a,b,c,d...$ 都是点， $a xor b,b xor c..$ 是边，那么这个性质左边可以看作一条图上的路径；右边则是一条边。

于是想到以杯子为点，区间为边（可以由 $xor$ 的交换律知道，是双向边）建出一个完全图，以图为基本结构接着思考。

回到先前的问题：求出 $a_i$ 的充分必要条件。只考虑前缀绚问的简单情况：

$$a_i = (b_i xor b_0) xor (b_{i - 1} xor b_0)$$

【$\texttt{P.S.}$ 这里我们需要考虑 $b_0$ 的存在，那么就有 $n + 1$ 个点了，当然为不影响答案，它的询问代价为 $0$】。

发现这个式子就是

$$a_i = b_i xor b_{i - 1}$$

经过一定对复杂情况的考虑，我们发现，区间上的减法和异或上的加法相似。即，不管询问的到底是哪些区间，这些区间上的值异或起来的结果都是 $b_i xorb_{i - 1}$。

换在图上思考，我们发现上面这个结论就是说，在选择的边集中，$i$ 必须要和 $i - 1$ 连边。当然，边即路径，所以有路径就相当于有边了。

大神大概上面的一大串分析都不用了直接看结论就懂了罢。

因为边是双向的，所以每一个 $i$ 要和 $i - 1$ 连通，即整个图连通。

所以我们需要在 $n + 1$ 个点的完全图中选择有 $n + 1$ 个点的连通图。

所以我们选择的是一颗最小生成树。

因此求最小生成树即可。这里因为是完全图，最好用 $\texttt{Prim}$ 来求，不用堆优化的。

（如果您没有搞懂异或，连边和询问的关系，您是否忘记了询问 $[l,r]$ 是 $l - 1$ 和 $r$ 连边？）

*最后评个分，大概是个普及+/提高的样子罢？*

代码如下，很短：

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>

typedef long long ll;
const int MAXN = 2001;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int u; ll w;
	Edge* nxt;
};

int n; ll c[MAXN][MAXN];
short vis[MAXN];
ll dist[MAXN];
Edge *adj[MAXN];

void ins(int v,int u,ll w) {
	Edge* e = new Edge;
	e -> u = u;
	e -> w = w;
	e -> nxt = adj[v];
	adj[v] = e;
}

int main() {
	std::cin >> n;
	for(int i = 1;i <= n;i++)
		for(int j = i;j <= n;j++) {
			std::scanf("%lld",c[i] + j);
			ins(i - 1,j,c[i][j]);
			ins(j,i - 1,c[i][j]);
		}
	ll ans = 0;
	memset(dist,INF,sizeof(dist));
	dist[0] = 0;
	for(int i = 0;i <= n;i++) {
		int v = 0,min = INF;
		for(int j = 0;j <= n;j++) {
			if(!vis[j] && min > dist[j]) min = dist[j], v = j;
		}
		ans += dist[v];
		vis[v] = true;
		for(Edge *i = adj[v];i;i = i -> nxt) {
			int u = i -> u;
			if(vis[u]) continue;
			if(dist[u] > i -> w) dist[u] = i -> w;
		}
	}
	std::printf("%lld\n",ans);
	return 0;
}
```

$c_{i,j} <= 10^9$，~~不开 `long long ` 大概没分。~~

---

## 作者：WanderOvO (赞：7)

# 前言

本题解秉承一步一步走的观念，将先从模拟样例出发，根据样例的模拟得到此题的一种使用MST的解法，然后逐步修正细节得到正解，尽量能让思考过程变得自然一些。

# 样例模拟

这道题如果每次单独询问每个容器，不用动脑子就可以知道每个容器内的状态（滑稽）。但是这个题目设计的询问开销中单个容器询问开销有的很高，不划算，反而是通过一个大区间和一个小区间询问来推断单点询问更省资源。并且不难发现，至少需要$n$次才能知道$n$ 个容器的情况（可以理解成$n$个方程解出$n$个未知数）。

但是刚读完题，我还不太清楚该怎么询问才好，所以先看一下样例，看看能不能有什么发现。

```cpp
5
1 2 3 4 5
4 3 2 1
3 4 5
2 1
5
```

初始化总消耗$sum=0$ 。单点访问$1$号消耗很少，$sum=1$ ;单点访问$2$号要消耗$4$，太贵了，不过考虑访问$1-2$，只消耗$2$，$sum=3$，这样也能知道$2$有没有；单点访问$3$号，要消耗$3$，但是那个矩阵里面还有更小的数呢，感觉能更少，所以先不管；单点访问$4$，还行，消耗$2$，$sum=5$ ；单点访问$5$太贵，但是访问$4-5$很便宜，$sum=6$ ；考虑区间$2-5$，因为$2$和$4-5$都确定了，所以只要知道$2-4$的奇偶性，就能知道$3$是什么状态了，消耗$1$，$sum=7$ ，所以样例结果是$7$。

# 样例的启示

刚才整个模拟样例的过程有点贪心的意思：只要矩阵里面有更小的数，那么我可能就要优先考虑是不是可以通过访问相应的那个区间以减少损耗。当然，如果那个区间里面的元素已经确定了，那么我们就不用去选那个了。

根据上面的分析，您可能也想到了：$kruskal$ 算法和这个差不多，都是优先选小的，都是不能有一些“冗余”的选择。所以，这个问题很可能是最小生成树问题。

# 思路建立与修改完善

下面想怎么建图。最朴素的想法肯定是直接把矩阵里的数变成边，比如**对于区间**$[i,j]$**的询问消耗为**$k$，**就给**$i,j$**结点连一条长度是**$k$**的边**，这样就有$n$个自环，不是简单图，求MST的话，肯定不会有自环，然而自环代表单点询问，根据样例可以知道，单点询问是可能作为最优决策的一部分的，所以这种建图方式不可取。并且， MST只有$n-1$条边，求不出$n$个点的信息。

要想有$n$ 条边，必须是对$n+1$个结点建立图，也就是说我们可能需要建立一个辅助结点来做一些事情。辅助结点需要做的第一件事就是把自环处理掉，而怎么处理掉自环呢？我最开始考虑的是加入一个$0$ 号结点，并且定义第$i$个结点和$0$ 号结点连接的边代表**单点查询**$i$ **的消耗**，而其他边照常连。这样的话，这个$n+1$个结点的图至少就没有环了。然而这会带来一个问题：$n+1$个结点的最小生成树必然会有$0$ 和其他节点直接相连的情况，也就是说这样求出的MST一定包含单点查询的情况，但是我们的最优查询方案中可能一个单点查询都没有，所以这样也是不对的。

上面的建图仍然出现问题的原因是标准不统一，即有些边代表区间查询，而有些起点终点编号不连续的边却代表单点查询（比如0号和2号连边在上面居然定义成了查询单点2号点）。我们最开始分析过的，两个区间查询能够推出一个更小的区间甚至单点的情况，即两个区间的查询结果“作差”。如果做过一些数论和数据结构的题，大家可能能想到出现奇偶性的题目就可能考虑异或运算（感觉是套路），而异或运算是很有趣的，有前缀和的一些性质（其他题解提到了），这意味着可以用前缀和搞事情根据这个思想，我们考虑根据前缀和去建图，**定义**$i,j$**结点连接一条边的意思是区间查询**$[i+1,j]$**区间所需要消耗的资源**，那么0号和$i$连接是就是$[1,i]$区间查询的消耗了，单点查询的消耗也容易表示了，比如对于$3$号结点的单点查询的消耗就是连接$2$和$3$号结点。这样看来，自环问题解决了，加入的$0$号结点也没有影响结果，直接在这个上面求MST就能得出答案。

因为这个是稠密图，所以要用朴素的prim算法（虽然我们是根据$kruskal$的算法过程发现的这个题考察的是MST）。

# 代码实现

代码异常地简洁，注意建图别建错了，以及$prim$循环次数要写对（n+1个点的MST）。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 9999999999999
using namespace std;
const int N=2e3+9;
const int M=N*(N-1);
typedef struct{
	ll to,nxt,weight;
}Edge;
Edge edge[M];
ll head[N],cnt,n,dist[N],ans;
bool intree[N];
void prim();
void add(ll x,ll y,ll z);
int main(){
	ll w;
	scanf("%lld",&n);
	for(int i=0;i<=n;i++){
		head[i]=-1;
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			scanf("%lld",&w);
			add(i-1,j,w);
			add(j,i-1,w);
		}
	}
	prim();
	printf("%lld\n",ans);
	return 0;
}
inline void prim(){
	ll minlen,minpos;
	for(int i=0;i<=n;i++){
		dist[i]=INF;
	}
	dist[0]=0;
	for(int j=0;j<=n;j++){ //对n+1个结点进行kruskal
		minlen=INF;
		for(int i=0;i<=n;i++){
			if(minlen>dist[i] && !intree[i]){
				minlen=dist[i];
				minpos=i;
			}
		}
		intree[minpos]=true;
		ans+=dist[minpos]; 
		for(ll i=head[minpos];i>=0;i=edge[i].nxt){
			if(!intree[edge[i].to])
				dist[edge[i].to]=min(dist[edge[i].to],edge[i].weight);
		}
	}
}
inline void add(ll x,ll y,ll z){
	edge[cnt].to=y;
	edge[cnt].weight=z;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
```



---

## 作者：东方澂 (赞：6)

&emsp;&emsp;我们用一个数列$\{a_n\}$来表示这些杯子，$a_n=1$表示第$n$个杯子下藏有小球，$a_n=0$表示没有。那么第$[l,r]$个杯子底下藏有球的总数的奇偶性就可以用这一段上的异或和（$a_l$ $xor$ $a_{l+1}\cdots$ $xor$ $a_r$）来表示。设$\{a_n\}$的异或前缀和为$\{b_n\}$（$b_n=a_1$ $xor$ $a_2$ $xor$ $a_3\cdots$ $xor$ $a_n$）。
> 花费$c_{i,j}$元，魔术师就会告诉你杯子$i,i+1,…,j$底下藏有球的总数的奇偶性。

&emsp;&emsp;也即每询问一次$[l, r]$，我们可以得到$b_r$ $xor$ $b_{l-1}$的结果。  
&emsp;&emsp;如果我们求出了$\{b_n\}$，便可以很快求出$\{a_n\}$，“保证猜出哪些杯子底下藏着球”。显然$b_0=0$，而$b_1∼b_n$是未知的。我们每询问一次，都可以得到一个方程。要解出这$n$个未知数，就需要$n$个方程联立。也就是说我们总共需要询问$n$次。  
&emsp;&emsp;将$\{b_n\}$看作一系列的点，将询问看作连接边$(l-1,r)$，那么我们所要求的就变成了用$n$条边连通$0∼n$这$n+1$个点，使得边权总和最小，即求最小生成树。该题给出的是稠密图，适合使用prim进行求解，复杂度为$\Theta(n^2)$。  
&emsp;&emsp;代码如下。  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=2010;
int n,t;
int e[MAXN][MAXN],dist[MAXN];
ll ans;
bool book[MAXN];

void prim(){
    memset(dist,0x3f,sizeof(dist));
    dist[0]=0;
    for(int i=0;i<n;++i){
        int x=-1;
        for(int j=0;j<=n;++j){
            if(book[j]) continue;
            if(x==-1 || dist[j]<dist[x]) x=j;
        }
        book[x]=true;
        for(int y=0;y<=n;++y){
            if(!book[y]) dist[y]=min(dist[y],e[x][y]);
        }
    }
}

int main(){
    scanf("%d",&n);
    memset(e,0x3f,sizeof(e));
    for(int i=0;i<=n;++i) e[i][i]=0;
    for(int l=1;l<=n;++l){
        for(int r=l;r<=n;++r){
            scanf("%d",&t);
            e[l-1][r]=e[r][l-1]=t;
        }
    }
    prim();
    for(int i=1;i<=n;++i) ans+=dist[i];
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：tommy0221 (赞：3)

[P5994 [PA2014]Kuglarz](https://www.luogu.com.cn/problem/P5994)

怎么十篇题解都是同一种建图方法啊，都好巧妙，这里来一种不同的建图方法。~~不知道为什么我每次做建图题做法都很鬼畜。~~

其实这题可以看做有 $n$ 个未知数 $x_1,x_2,\cdots,x_n$，要全部解出来。

每一次询问相当于付出 $c_{l,r}$ 的代价增加一个方程 $\bigoplus\limits_{i=l}^{r}x_i=y$ 。

异或方程是可以高斯消元的，所以找出 $n$ 个方程就可以了。

但是如果存在一些方程本质相同，那么就不是唯一解。

比如三次询问 $[x,y],[y+1,z],[x,z]$，显然前两个方程可以直接得到第三个方程，所以第三个是无用的。

再思考一下，如果把这个询问的两个端点连边就是不能出现环。选择每一条边有个代价，不能出现环，那么就是最小生成树。

写了一发 WA 得只剩两分，一看是我大 E 了，这个图是可以有自环的，而且 $n$ 个点 $n$ 条边不能跑最小生成树。

由于自环也得连边，那么就拆点，左边一个，右边一个，对应的编号分别为 $i,i+n$，可以理解为类似出入点的东西。

首先先连上 $(i+n,i+1)$，边权为 $0$，总共 $n-1$ 条边，表示这个点和下一个点是连接着的，这样每次区间连边连两个端点就好了。

每次区间 $[l,r]$ 连边，那么就连 $(l,r+n)$，边权为 $c_{l,r}$，总共需要 $n$ 条。

所以 $2n$ 个点，$2n-1$ 条边，跑最小生成树即可。

比如样例跑出来的生成树就长这样：

【注】这张图里自己选的边是 $(1,1),(2,5),(4,4),(1,2),(4,5)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/exluiz1h.png)

自带两倍常数但是跑起来好像还好。

Code：

```cpp
const int N = 4004;
int n, c[N][N], dis[N];
bool vis[N];
LL prim() {
	LL res = 0;
	memset(dis, 0x3f, sizeof(dis));
	rep(i, 1, n - 1) c[i + n][i + 1] = c[i + 1][i + n] = 0;
	dis[1] = 0;
	rep(t, 1, (n << 1)) {
		int id = 0, mi = 0x3f3f3f3f;
		rep(i, 1, n << 1) if(!vis[i] && ckmin(mi, dis[i])) id = i;
		vis[id] = 1, res += mi;
		rep(i, 1, n << 1) if(!vis[i]) ckmin(dis[i], c[id][i]);
	}
	return res;
}
signed main() {
	n = read();
	memset(c, 0x3f, sizeof(c));
	rep(i, 1, n) rep(j, i, n) c[i][j + n] = c[j + n][i] = read();
	cout << prim() << '\n';
}
```

---

## 作者：Aw顿顿 (赞：2)

首先，由于每一个杯子下都至多存在一个小球，所以对于一个杯子，奇数就是有球而偶数就是没有球。考虑区间是具有可减性的，所以对于两次询问 $[x,y]$ 和 $[x,z]$ 时，如果 $z>y$ 我们就相当于知道了 $[y+1,z]$。同样，如果我们知道 $[x,y)$ 和 $[y,z)$ 我们就知道 $[x,z)$ 了。

接下来考虑我们能怎样求出来一个点的花费。

- 直接花费 $c_{i,i}$ 的钱得到，
- 使用 $c_{i,j}$ 和 $c_{i+1,j}$ 相减得到。

我们把这种花费看成边权，也就是通过连边使得 $i$ 这个点与其他点联通，这样就像下图所示的两种方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/9fwmd010.png)

所以答案已经呼之欲出——最小生成树。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
int n,m;
struct edge{
	int v,w,next;
}e[2000005];
int head[1000005],cnt,ans,dis[1000005],vis[1000005];
void add(int u,int v,int w){
    e[cnt].w=w;//权值为 w 
    e[cnt].v=v;//终点为 v 
    e[cnt].next=head[u];//接到 u 的 "邻居链表" 开头 
    head[u]=cnt++;//把 "开头 " 更新为这条边 
}priority_queue<pii,vector<pii >,greater<pii > >q;
signed main(){
	cin>>n;
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++){
			int w;cin>>w;
			add(i-1,j,w);
			add(j,i-1,w);
		}
	q.push(make_pair(0,1)),dis[1]=0;
	while(!q.empty()){
		int x=q.top().second;
		q.pop();
		if(vis[x])continue;
		vis[x]=1;ans+=dis[x];
		for(int i=head[x];i;i=e[i].next){
			int v=e[i].v;
			if(dis[v]>e[i].w){
				dis[v]=e[i].w;
				q.push(make_pair(dis[v],v));
			}
		}
	}printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：nomonick (赞：2)

# 题解 P5994 【[PA2014]Kuglarz】

这道题第一眼拿到题目想法还是很多的。可惜都不可行，在我以为他不可做时，我想到了一个算法，最小生成树。

首先确定了一个点的奇偶性等于是获得这个杯子是否有小球。

同时知道这样的三个公式

$$
\forall
\begin{cases}
x \in \{\alpha | \alpha \bmod 2 = 0\}\\
y \in \{\alpha | \alpha \bmod 2 \ne 0\}
\end{cases}
$$

$$
\begin{cases}
x + x = x\\
x + y = y\\
y + y = x
\end{cases}
$$

所以对于区间 $[ls,rs]$ 只要知道区间 $[ls,k]$ 和 $[rs,k]$ 就可以直接推理得知。

因此只要把所有的杯子连成一棵树即可，保证花费最小。

然后就是裸的最小生成树。

# code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int NUM = 2e3 + 50;
const int SIZE = 4e6 + 50;

inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		f = (ch == '-' ? -1 : 1);
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f * x;
}

int n,num_edge,ans;
int fa[NUM];
struct node
{
	int to,from,val;
	friend bool operator < (node a,node b)
	{
		return a.val < b.val;
	}
};
node edge[SIZE << 1];

inline void add(int u,int v,int val)
{
	edge[++num_edge].to = v;
	edge[num_edge].val = val;
	edge[num_edge].from = u;
}

int get_root(int u)
{
	return fa[u] == u ? u : fa[u] = get_root(fa[u]);
}

bool pd(int u,int v)
{
	return get_root(u) == get_root(v) ? true : false;
}

void merge(int i,int u,int v)
{
	if (pd(u,v)) return ;
	fa[get_root(u)] = get_root(v);
	ans += edge[i].val;
}

signed main()
{
	n = read();
	for (int i = 1; i <= n; ++i)
	{
		fa[i] = i;
		for (int j = i; j <= n; ++j)
		{
			add(i-1,j,read());
		}
	}
	sort(edge+1,edge+1+num_edge);
	for (int i = 1; i <= num_edge; ++i)
	{
		merge(i,edge[i].from,edge[i].to);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Jayun (赞：2)

# 题目大意：

给定 $N$ 个点，每个点可能有一个标记，可以通过 $c_{i,j}$ 知道区间 $[i,j]$ 的奇偶性，问你至少需要花费多少，才能保证猜出哪些点有标记。

# 正文：

## 求导过程：

我做题时开始想的是通过知道两个区间 $[l,r-1],[l,r]$ 的奇偶性直接得到 $r$ 是否标记。而我们可以知道 $[0,r],[l,r]$ 得到 $[0,l-1]$ 的奇偶性，将区间作为树的节点，每次给出 $[l,r]$ 的代价 $w$ 时，连两点 $[0,r],[0,l-1]$ 为一代价是 $w$ 的线，即可最小生成树。

## 代码：

```cpp
int main()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = i; j <= n; j++)
		{
			int w;
			scanf ("%d", &w);
			add(i - 1, j, w);
		}
	}
	sort(e + 1, e + 1 + tot, cmp);
	for (int i = 1; i <= tot ; i++)
	{
		int f = FIND(e[i].from), t = FIND(e[i].to); 
		if (f == t) continue;
		fa[f] = t;
		ans += e[i].w * 1ll;
	}
	printf ("%lld", ans);
	return 0;
}

```

---

## 作者：pigstd (赞：1)

一种不一样的理解方法。

设 $sum_i$ 表示 $1-i$ 中藏有总数的和的奇偶性，那么知道 $sum_i$ 就能够知道哪些杯子底下藏着球。

那么对于一次询问 $[l,r]$，我们得到的答案就是 $sum_{l-1} \oplus sum_r$，其中 $\oplus$ 表示异或运算。

其次还有一个结论：如果我们知道 $[l,x],[x+1,r],[l,r]$ 中任意两个区间的答案，就能够知道剩下的一个数。将询问 $[l,r]$ 连为一条 $l-1$ 到 $r$，边权为 $c_{l,r}$ 的边，那么如果选择的方案所连成的边出现了一个环，那么显然就不是最优的。

此外，由于有 $n$ 个变量，显然需要 $n$ 个方程才能够解决，即至少要 $n$ 条边。

结合两个结论，相当于就是在 $n+1$ 个点上找一个生成树，并且不难验证这是可行的。由于答案要求最小，相当于找一个最小生成树就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int M=2e3+10;
int c[M][M],n,f[M],sum,ans;

struct edge
{
	int a,b,w;
}e[M*M];int cnt;

bool cmp(edge a,edge b)
{
	return a.w<b.w;
}

int find(int k){return f[k]==k?k:f[k]=find(f[k]);}

signed main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
		for (int j=i;j<=n;j++)
		{
			cin>>c[i][j];
			e[++cnt].a=i,e[cnt].b=j+1,e[cnt].w=c[i][j];
		}
	sort(e+1,e+1+cnt,cmp);
	for (int i=1;i<=n+1;i++)f[i]=i;
	for (int i=1;i<=cnt;i++)
	{
		if (find(e[i].a)==find(e[i].b))continue;
		sum++,ans+=e[i].w,f[find(e[i].a)]=find(e[i].b);
		if (sum==n)break;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：漠寒 (赞：1)

## 题意

有 $n$ 个杯子，会告诉你每一个区间 $i$ ， $j$ 需要的花费，从而得知这一区间内所有小球总和的奇偶性，因为我们知道每一个杯子下的小球只有一个或两个，因此这道问题便可以通过最短路的方式来做了

## 做法

在得到两个共端点的区间奇偶性后，就可以得到非共端点之间的奇偶性，例如，你知道了一到三号和一到四号的奇偶性，显而易见你就可以得到四号的奇偶性，所以，对于每一个 $c$ ，我们可以建一条边，然后跑最小生成树即可。

### 如何建边呢？

很显然我们是不能单纯从 $i$ 指向 $j$ 的，比如 $i=j$ 的边就作废了，所以建边策略为从 $i$ 建一条向 $j+1$ 的边，将端点数加一，再跑树。

### 最小生成树

常见的做法有两种， $Prim$ 和 $Kruskal$ 。这里介绍的是后者。

将一个连通块当做一个集合。首先将所有的边按从小到大顺序排序，并认为每一个点都是孤立的，分属于 $n$ 个独立的集合。然后按顺序枚举每一条边。如果这条边连接着两个不同的集合，那么就把这条边加入最小生成树，这两个不同的集合就合并成了一个集合；如果这条边连接的两个点属于同一集合，就跳过。直到选取了 $n-1$ 条边为止。

简单来说， $Kruskal$ 每次都选择一条最小的边，而且这条边的两个顶点分属于两个不同的集合。将选取的这条边加入最小生成树，并且合并集合。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,vis[2002],sum,tot,fa[2002];
long long ans;
struct node{//邻接表 
	int from,to,w;
}a[2001001];
void add(int q,int m,int bq){//加边 
	a[++tot].to=m;
	a[tot].from=q;
	a[tot].w=bq;
}
int find(int x){//判断联通块 
	if(!fa[x])return x;
	return fa[x]=find(fa[x]);//查询顺便更新该位置标志，会节省时间 
}
bool cmp(node x,node y){//按边权排序 
	return x.w<y.w;
}
inline int read(){
	int s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
	return s;
}
int main()
{
	n=read();
	int x;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n-i+1;j++){
			x=read();
			add(i,i+j,x);
		}
	}
	sort(a+1,a+tot+1,cmp);
	for(int i=1;i<=tot;i++){
		int xx=find(a[i].from),yy=find(a[i].to);
		if(xx==yy)continue;//已为同一联通块 
		if(xx!=yy){
			sum++;//连边 ，边数加一 
			fa[xx]=yy;//合并 
			ans=(long long)ans+a[i].w;
		}
		if(sum==n)break;//已建成最小生成树 
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：Tony102 (赞：1)

[Link](https://www.luogu.com.cn/problem/P5994)

[更好的阅读体验](https://tony102.xyz/index.php/2021/01/26/p5994-pa2014kuglarz/)

### Sol

其实我觉得这题就很适合作为联赛题。就是那种典型的水平、积累到了一定层次就会做，有区分度的题目。

首先我们来考虑一下，怎么样才能问出一个被子地下的奇偶性。加入我们问了一段区间$[l,r]$的奇偶性，又问一次$[l,r+1]$的奇偶性，那么$[r,r+1]$这段的有没有球就确定了。原因：假如这两段区间的奇偶性是一奇一偶，说明两个右端点组成的区间必是因为有球才导致的奇偶性不同。

那么我们来形式化地描述这种已经知道$[r,r+1]$的奇偶性的状态：从$[r,r+1]$连一条边。那么，知道$[l,r]$的奇偶性就是从$l$到$r$有一条边（对刚才的性质进行换元就可以了）。我们把按照这种方法建一张图，最终我们就只要选出一些边使这张图联通。最小生成树即可。

我觉得这道题改改可以出道交互题。



### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int SIZE = 2e3 + 5;

int n, m, num;
int fa[SIZE];

struct node {
	int from, to, v;

	bool operator< (const node &a) const {
		return v < a.v;
	}
} edge[SIZE * SIZE];

namespace ae86 {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (!isdigit(c))b ^= c == '-', c = fetch();
		while (isdigit(c)) a = a * 10 + c - 48, c = fetch();
		return b ? a : -a;
	}
}
using ae86::read;

void addEdge(int u, int v, int d) {
	edge[++ num].from = u, edge[num].to = v, edge[num].v = d;
}

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

signed main() {
	// freopen("code.in", "r", stdin);
	n = read();
	for (int i = 1; i <= n; ++ i) {
		for (int j = i, w; j <= n; ++ j) {
			w = read();
			addEdge(i - 1, j, w);
		}
	}
	std::sort(edge + 1, edge + num + 1);
	for (int i = 1; i <= n; ++ i) fa[i] = i;
	int tot = 0, cnt = 0;
	for (int i = 1, fx, fy; i <= num; ++ i) {
		fx = find(edge[i].from), fy = find(edge[i].to);
		if (fx != fy) {
			fa[fx] = fy, ++ cnt, tot += edge[i].v;
		}
		// if (cnt == n - 1) break;
	}
	printf("%lld\n", tot);
	return 0;
}
```



---

