# Edges in MST

## 题目描述

You are given a connected weighted undirected graph without any loops and multiple edges.

Let us remind you that a graph's spanning tree is defined as an acyclic connected subgraph of the given graph that includes all of the graph's vertexes. The weight of a tree is defined as the sum of weights of the edges that the given tree contains. The minimum spanning tree (MST) of a graph is defined as the graph's spanning tree having the minimum possible weight. For any connected graph obviously exists the minimum spanning tree, but in the general case, a graph's minimum spanning tree is not unique.

Your task is to determine the following for each edge of the given graph: whether it is either included in any MST, or included at least in one MST, or not included in any MST.

## 说明/提示

In the second sample the MST is unique for the given graph: it contains two first edges.

In the third sample any two edges form the MST for the given graph. That means that each edge is included at least in one MST.

## 样例 #1

### 输入

```
4 5
1 2 101
1 3 100
2 3 2
2 4 2
3 4 1
```

### 输出

```
none
any
at least one
at least one
any
```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 1
1 3 2
```

### 输出

```
any
any
none
```

## 样例 #3

### 输入

```
3 3
1 2 1
2 3 1
1 3 1
```

### 输出

```
at least one
at least one
at least one
```

# 题解

## 作者：MyukiyoMekya (赞：16)

先随便生成一棵最小生成树，

先处理不在最小生成树上的边：$(u,v,w)$，如果树上 $(u,v)$ 路径上的边权 $<w$，那么说明这个边没用，输出 `none`，

否则一定 $=w$ ，输出 `at least one`，然后对于树上每条边开个 $x_i$ ，把 $(u,v)$ 路径上的 $x_i$ 对 $w$ 取 $\min$

然后处理在树上的边：$(u,v,w)$ ，如果 $(u,v)$ 所在的 $x_i>w$ 那么这个边没有其他替代边，一定要选，输出 `any`

否则 $x_i=w$ ，输出 `at least one`。

维护方法就开个线段树然后树剖一下就好了，$\mathcal O(n\log ^2n)$。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define ALL(x) (x).begin(),(x).end()
#define mem(x,y) memset(x,y,sizeof x)
#define ln std::puts("")
#define pb push_back
#define MP std::make_pair
const int MaxN=1e5+50;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
template <class t>inline bool checkmin(t&x,t y){if(x>y){x=y;return 1;}return 0;}
template <class t>inline bool checkmax(t&x,t y){if(x<y){x=y;return 1;}return 0;}
int W[MaxN];
struct edge
{
	int u,v,w,idx,ok;
	inline bool operator < (const edge &nt) const{return w<nt.w;}
}e[MaxN];
struct Edge
{
	int nxt,to,idx;
}E[MaxN<<2];
int hd[MaxN],en,n,m;
inline void adde(int u,int v,int idx){E[++en]=(Edge){hd[u],v,idx},hd[u]=en;}
int f[MaxN],toed[MaxN],edto[MaxN];
inline int getf(int x){return f[x]==x?x:f[x]=getf(f[x]);}
int dfn[MaxN],siz[MaxN],top[MaxN],F[MaxN],dep[MaxN],rev[MaxN],gson[MaxN],dfncnt;
inline void dfs(int u,int fa)
{
	siz[u]=1,F[u]=fa,dep[u]=dep[fa]+1;
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(v==fa)
			continue;
		toed[v]=E[i].idx;
		dfs(v,u),siz[u]+=siz[v];
		if(siz[gson[u]]<siz[v])
			gson[u]=v;
	}
}
inline void dfs2(int u,int ftop)
{
	rev[dfn[u]=++dfncnt]=u;
	top[u]=ftop;
	if(!gson[u])return;
	dfs2(gson[u],ftop);
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(v==F[u]||v==gson[u])
			continue;
		dfs2(v,v);
	}
}
#define lson (u<<1)
#define rson (u<<1|1)
int mn[MaxN<<2],mx[MaxN<<2],lazy[MaxN<<2];
inline void pushup(int u)
{
	mn[u]=std::min(mn[lson],mn[rson]);
	mx[u]=std::max(mx[lson],mx[rson]);
}
inline void pushdown(int u)
{
	if(lazy[u]!=1e9)
	{
		checkmin(lazy[lson],lazy[u]),checkmin(lazy[rson],lazy[u]);
		checkmin(mn[lson],lazy[u]),checkmin(mn[rson],lazy[u]);
		lazy[u]=1e9;
	}
}
inline void buildtr(int u,int l,int r)
{
	lazy[u]=1e9;
	if(l==r)
	{
		mn[u]=1e9,mx[u]=W[toed[rev[l]]];
		return;
	}
	reg int mid=(l+r)>>1;
	buildtr(lson,l,mid),buildtr(rson,mid+1,r);
	pushup(u);
}
inline void modify(int u,int l,int r,int ql,int qr,int k)
{
	if(ql<=l&&r<=qr)
		return checkmin(mn[u],k),checkmin(lazy[u],k),void();
	pushdown(u);
	reg int mid=(l+r)>>1;
	if(ql<=mid)
		modify(lson,l,mid,ql,qr,k);
	if(mid<qr)
		modify(rson,mid+1,r,ql,qr,k);
	pushup(u);
}
inline int query(int u,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr)
		return mx[u];
	pushdown(u);
	reg int mid=(l+r)>>1,res=-1e9;
	if(ql<=mid)
		checkmax(res,query(lson,l,mid,ql,qr));
	if(mid<qr)
		checkmax(res,query(rson,mid+1,r,ql,qr));
	return res;
}
inline int qmax(int u,int v)
{
	reg int res=-1e9;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]])std::swap(u,v);
		checkmax(res,query(1,1,n,dfn[top[u]],dfn[u])),u=F[top[u]];
	}
	if(dep[u]<dep[v])std::swap(u,v);
	if(u!=v)checkmax(res,query(1,1,n,dfn[v]+1,dfn[u]));
	return res;
}
inline void mdf(int u,int v,int k)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]])std::swap(u,v);
		modify(1,1,n,dfn[top[u]],dfn[u],k),u=F[top[u]];
	}
	if(dep[u]<dep[v])std::swap(u,v);
	if(u!=v)modify(1,1,n,dfn[v]+1,dfn[u],k);
}
int ans[MaxN]; // -1 none   0 at least one   1 any
inline void over(int u,int l,int r)
{
	if(l==r)
	{
		if(l==1)return;
		reg int x=toed[rev[l]];
		if(mn[u]!=W[x])ans[x]=1;
		return;
	}
	pushdown(u);
	reg int mid=(l+r)>>1;
	over(lson,l,mid),over(rson,mid+1,r);
}
signed main(void)
{
	std::mem(hd,-1);W[0]=1e9;
	read(n,m);
	for(int i=1;i<=n;++i)f[i]=i;
	for(int i=1;i<=m;++i)
		read(e[i].u,e[i].v,e[i].w),W[i]=e[i].w,e[i].idx=i;
	std::sort(e+1,e+m+1);
	for(int i=1;i<=m;++i)
	{
		reg int a=getf(e[i].u),b=getf(e[i].v);
		if(a==b)continue;
		f[b]=a,e[i].ok=1;
		adde(e[i].u,e[i].v,e[i].idx),adde(e[i].v,e[i].u,e[i].idx);
	}
	dfs(1,0),dfs2(1,1);
	buildtr(1,1,n);
	for(int i=1;i<=m;++i)
		if(!e[i].ok)
		{
			if(e[i].w!=qmax(e[i].u,e[i].v))
				ans[e[i].idx]=-1;
			mdf(e[i].u,e[i].v,e[i].w);
		}
	over(1,1,n);
	for(int i=1;i<=m;++i)
		std::puts(ans[i]?ans[i]>0?"any":"none":"at least one");
	return 0;
}
```



---

## 作者：樱洛CHANGE (赞：15)

总共两篇 $\text{Tarjan}$ 求桥的题解都没看懂，由于这种做法的思想实在神仙，所以自己写一篇题解。

--------------------

首先我们根据 $\text{Kruskal}$ 求 $\text{MST}$ 的思路，将边权从小到大排序，容易发现：**若一条边的两个端点在之前就被比它边权更小的边所联通，则这条边一定不会出现在 $\text{MST}$ 里。**

则根据该思路，我们对同一边权的边分别进行处理，首先，我们去除掉刚才说的显然不存在的边，然后把其他的边加入到原图（重边无影响）中，然后显然，图中的割边就是一定会出现在所有 $\text{MST}$ 中的边。

举个栗子，假设当前处理到边权为 $\large x$ 那么我们先把所有小于 $\large x$ 的边加进去，那由上述思路可知，**这两个边的集合一定不连通，否则这条边显然不存在**，这个时候两个集合之间可能会有若干个权值为 $\large x$ 的边，而**连接这两个集合的一定是这些权值为 $\large x$ 的边**，不可能更大，这一点由 $\text{Kruskal}$ 的贪心显然可知，而此时，从这些 $\large x$ 中我们只需**选出一条**即可，所以这些 $\large x$ **至少存在于一个** $\text{MST}$ 中，而如果**只有一个** $\large x$，则它一定是桥，则**必然出现于所有** $\text{MST}$ 中。

根据这个思路，我们可以想出一个~~显（bing）然（bu）~~ 的优化，由于我们在考虑当前权值时，并不关心图的其他部分，所以我们在处理一类边权时，对当前图进行缩点，可以做到时间的优化。

众所周知，缩点有两种写法：给新点安排一个新编号、用点集的某个元素，但去掉与其相连的边。

而为了方便我们本题的找边操作，我们选择第二种方法进行缩点，缩点后找桥的过程，我们只需要初始化所有新边两端点的 $\text{dfn}$ 为 $0$，不必要全部初始化，因为显然缩完点之后图中只剩缩完以后的点了。

关于重边和缩点的正确性问题，由于都不会对求桥产生影响，所以只要满足贪心从小到大即可保证正确性。

由于我太菜了，所以复杂度不会算，YY了一下差不多是 $\large O(n\log n)$ 的。

代码
```cpp
#include<bits/stdc++.h>
#define awa 2147483647
#define zhale exit(0)
#define re register
#define rint re int
using namespace std;
/*Shioiri Kukuri*/

typedef long long ll;
typedef unsigned long long ull;
typedef double qwq;
typedef pair<int,int> P;
typedef pair<ll,ll> llP;
#define rll re ll
#define rqwq re qwq

/*Otho Ai*/

template<class T>
void Swap(T &x,T &y)
{
    T z=x;
    x=y;
    y=z;
}

//#define PairOP
#ifdef PairOP
template<class T1,class T2>
inline const pair<T1,T2> operator + (const pair<T1,T2> &p1,const pair<T1,T2> &p2){
    return pair<T1,T2>(p1.first+p2.first,p1.second+p2.second);
}

template<class T1,class T2>
inline const pair<T1,T2> operator - (const pair<T1,T2> &p1,const pair<T1,T2> &p2){
    return pair<T1,T2>(p1.first-p2.first,p1.second-p2.second);
}
#endif

//#define FastIO
#ifdef FastIO
    char buf[1<<21],*p1,*p2;
    #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif

template<class T>
T Read()
{
    T x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^'0');
        ch=getchar();
    }
    return x*f;
}
//int (*read)()=Read<int>;
ll (*readll)()=Read<ll>;
#define read Read<int>

const int N=1e5+5;
int n,m;
namespace Dsu{
    int fa[N];
    inline int Find(rint x){
        return fa[x]==0?fa[x]=x:fa[x]==x?x:fa[x]=Find(fa[x]);
    }
}
using Dsu::Find;

class Edge{
    public:
        int from,to,val,id;
        inline friend bool operator < (const Edge &a,const Edge &b){
            return a.val<b.val;
        }
        inline void In(rint i){
            from=read(),to=read(),val=read(),id=i;
        }
}edge[N];

namespace Graph{
    class Edge_{
        public:
            int to,id;
            Edge_(rint _to,rint _id):to(_to),id(_id){}
    };
    vector<Edge_>e[N];
    inline void add(rint x,rint y,rint id){
        e[x].push_back(Edge_(y,id));
        e[y].push_back(Edge_(x,id));
    }
    inline void SuoNode(rint x,rint y){
        e[x].clear(),e[y].clear(),Dsu::fa[x]=y;
    }
}

namespace Tarjan{
    int cnt,dfn[N],low[N],bridge[N];
    inline void tarjan(rint x,rint faid){
        low[x]=dfn[x]=cnt++;
        for(auto i:Graph::e[x]){
            rint y=i.to,id=i.id;
            if(id==faid) continue;
            if(!dfn[y]){
                tarjan(y,id);
                low[x]=min(low[x],low[y]);
                if(low[y]>dfn[x]) bridge[id]=1;
            }
            else low[x]=min(low[x],dfn[y]);
        }
    }
    inline void InitEdge(rint x,rint y,rint id){
        dfn[x]=dfn[y]=0,bridge[edge[id].id]=-1;
    }
    inline void FindBridge(rint x){
        cnt=0,tarjan(x,-1);
    }
    inline void Print(rint i){
        puts(!bridge[i]?"none":bridge[i]==1?"any":"at least one");
    }
}

inline int True()
{
//#define Freopen
#ifdef Freopen
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif

//#define Clock
#ifdef Clock
    rint STR=clock();
#endif

    n=read(),m=read();
    for(rint i=1;i<=m;++i) edge[i].In(i);
    sort(edge+1,edge+1+m);
    for(rint i=1,j;i<=m;i=j)
    {
        j=i+1;
        while(j<=m&&edge[i].val==edge[j].val) ++j;
        for(rint k=i;k<j;++k)
        {
            rint x=Find(edge[k].from),y=Find(edge[k].to);
            if(x==y) continue;
            Graph::add(x,y,edge[k].id);
            Tarjan::InitEdge(x,y,k);
        }
        for(rint k=i;k<j;++k)
        {
            rint x=Find(edge[k].from),y=Find(edge[k].to);
            if(x==y||Tarjan::dfn[x]) continue;
            Tarjan::FindBridge(x);
        }
        for(rint k=i;k<j;++k)
        {
            rint x=Find(edge[k].from),y=Find(edge[k].to);
            if(x==y) continue;
            Graph::SuoNode(x,y);
        }
    }
    for(rint i=1;i<=m;++i)
    Tarjan::Print(i);

#ifdef Clock
    rint END=clock();
    printf("Time:%dms\n",int((END-STR)/(qwq)CLOCKS_PER_SEC*1000));
    printf("Time:%ds\n",int((END-STR)/(qwq)CLOCKS_PER_SEC));
#endif
    return (0-0);//q(0-0)p q(>-<)p
}

int Love=True();

signed main(){;}
```

---

## 作者：oneton429 (赞：10)

# CF160D Edges in MST  

[Problem Link](https://www.luogu.com.cn/problem/CF160D)

本篇题解参考了部分题解  

使用`vector`进行存图，对`vector`用户极为友好，弥补了题解区没有`vector`的空白  

~~使用`base64`存储图片，不用担心图片丢失的遗憾~~  

望管理通过qwq

## 题目大意

给你一个图，判断每条边是否可能在$MST$(最小生成树)上。如果不可能在输出`none`，在所有上$MST$出现就输出`any`，在某些$MST$出现上输出`at least one`。

## 简单点?

### 如果没有边权和$MST$的要求?

那么问题就转化为，给你一个图，求出为了维护整张图的连通性，哪些边一定要出现，哪些边在其他某些边已经出现的情况下可以不用出现。

那么问题就很简单了。用`Tarjan`求下桥就好了。

在这里默认在座的各位都会`Kruskal`求最小生成树和`Tarjan`求桥。

## 思路

根据`Kruskal`求最小生成树的思路，首先要按边权从小到大排序。

那么很显然的一点：**如果一条边的两端在之前就被比它边权更小的边联通了，那么这条边一定不会出现在$MST$里**。

那么顺着这个思路，我们可以尝试将同一边权的边，去除掉上文已经证明不存在的边，加入图中。

然后对这个图求桥就好了。

### 优化

可以看到，![1](data:image/png;base64,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)和![2](data:image/png;base64,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)求桥的结果是一样的(假设$(1,3)$是新加进来的边)

所以说，可以用**缩点**来进行优化。原因是这些边肯定都是在这个连通块内的，以后再做`Tarjan`的时候除了让你的程序变慢外毫无帮助(因为按边`dfs`)。

> 缩点有两种方法，

> - 给新点安排一个新编号
> - 用点集内某个元素，但把它的边全部去掉

我用的第二种方法。

每次我们判断是否是桥的时候**只需要初始化所有要新边的两端的`dfn`(`dfs`时间戳)为$0$**就好了，不必全部初始化，因为这个图里只有孤立的(缩完的)点了。

## Code

为了便于理解，我将有关的代码放到同一个`namespace`里 ~~(防止变量重名好习惯)~~

以及还有一些细节要看代码

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using std::sort;

int n, m, f[100010], ans/*-1为at least one, 0为nong, 1为any*/[100010];

namespace graph { //Tarjan部分
	using std::min;
	using std::vector;

	struct node {
		int to, id;
	};
	static int nowtime, dfn[100010], low[100010];
	vector < node > e[100010];
	struct node1 {
		int from, to, v, id;
		bool operator < (const node1 & a) const {
			return v < a.v;
		}
	}
	edge[100010];

	inline void addedge(int from, int to, int id) { //加边
		e[from].push_back(node{to, id}),
		e[to].push_back(node{from, id});
	}

	void tarjan(int now, int faid) { //faid为当前转移到now这个点的边的编号
		low[now] = dfn[now] = nowtime++;
		for (register int i = 0; i < (int) e[now].size(); ++i) {
			if (e[now][i].id == faid)
				continue;
			if (!dfn[e[now][i].to]) {
				tarjan(e[now][i].to, e[now][i].id),
					low[now] = min(low[now], low[e[now][i].to]);
				if (low[e[now][i].to] > dfn[now])
					ans[e[now][i].id] = 1;
			} else
				low[now] = min(low[now], dfn[e[now][i].to]);
		}
	}
}

inline int getf(int x) {
	return f[x] = x == f[x] ? x : getf(f[x]);
}

inline void init() {
	scanf("%d%d", & n, & m);
	for (register int i = 1; i <= n; ++i)
		f[i] = i;
	for (register int i = 1; i <= m; ++i)
		scanf("%d%d%d", & graph::edge[i].from, & graph::edge[i].to, & graph::edge[i].v),
		graph::edge[i].id = i;
	sort(graph::edge + 1, graph::edge + m + 1);
}

inline void work() {
	int j;
	for (register int i = 1; i <= m; i = j) {
		j = i + 1;
		while (j <= m && graph::edge[i].v == graph::edge[j].v) //寻找相同边权的边的范围[左闭右开区间)
			++j;
		for (register int l = i; l < j; ++l) {
			int x = getf(graph::edge[l].from), y = getf(graph::edge[l].to);
			if (x == y)   //已经在之前就被比它边权更小的边联通了
				continue; //ans = none
			graph::addedge(x, y, graph::edge[l].id), //加边
			graph::dfn[x] = graph::dfn[y] = 0, //初始化新边两端的dfn为0
			ans[graph::edge[l].id] = -1; //ans可能为at least one
		}
		for (register int l = i; l < j; ++l) {
			int x = getf(graph::edge[l].from), y = getf(graph::edge[l].to);
			if (x == y || graph::dfn[x]) //如果再之前的Tarjan里已经遍历过了就不用再求桥了
				continue;
			graph::nowtime = 0,
			graph::tarjan(x, -1); //Tarjan求桥
		}
		for (register int l = i; l < j; ++l) {
			int x = getf(graph::edge[l].from), y = getf(graph::edge[l].to);
			if (x == y)
				continue;
			graph::e[x].clear(), //缩点，即把它的边全部去掉
			graph::e[y].clear(),
			f[x] = y;
		}
	}
}

int main(void) {
	init();
	work();
	for (register int i = 1; i <= m; ++i)
		if (ans[i] == 1) puts("any");
		else if (ans[i] == 0) puts("none");
		else puts("at least one");
	return 0;
}
```

运行时长/空间: $2.84s / 9.92MB$

---

## 作者：_J_C_ (赞：9)

CF上AC了，然而不知道为什么，洛谷这边~~想刷一个AC记录时~~出现了Unknown Error……什么时候想起来了回头再来交交看吧。

首先，如果每条边边权都为1，原题就退化成了~~大水题~~找桥的问题（**图论里的桥，不是赵州桥**）。找桥，我选择Tarjan。[广告滑稽]

对于被削了一刀的题目来说，**如果一条边在图里是桥**，即割开它后将产生两个及以上的子图，**那么显然这条边是必选的**。

但是原题有很多很多边权……那么我们先读入并储存边，在把它们按边权从小到大排序。

显然，**对于最小的边权，按照上述的方法排除就好了**，也不可能会出现“none”，要么就可被替代，要么是桥而不能被替代。原因是它权值已经最小了，不可能被权值大的边替换掉。

那么我们顺着这个思路，将同一边权的边集中起来处理。每一次操作直接尝试将所有同一边权的边加入图中——尝试失败的条件是左右**两个连通块已经连通了**，即在更小的权值内连通了（所以需要**并查集**）——换句话说，**要你这条边干嘛**。直接ans[] = -1带走（"none"）。

如果你对这个判断方法感到很没有把握，不妨这样想。我们将用更小的边所能连通的连通块**缩成一个点**，而且这样肯定没毛病：如果有更大的边加入了这个点的内部，那肯定是亏了。这样子，问题**又转化成了边权全部统一、有一大堆孤立点的问题**，就与最开始被削了一刀的问题一样了（递归的一个过程）。

要说有什么优化嘛……缩点后，要么给新点新安排一个编号，要么用点集内某个元素而把它的边全部去掉。原因是这些边肯定都是在这个连通块内的，对以后除了让你的程序变慢外毫无帮助。

每次我们判断是否是桥的时候**只需要初始化所有要新边的两端的vistime（dfs时间戳）为0**就好了，不必全部初始化，因为这个图里只有孤立的（缩）点了。

顺便建议一下写两个边的结构体，如果你用同一个结构体进行存储边表、建立图的话，代码会比较乱。。

读入输出优化之类的嘛……看心情用吧。

```cpp
#include <cstdio>
#include <cstdlib>

#include <algorithm>

#define READ_3(a, b, c) read(a);read(b);read(c)

//#define PAUSE while(1);

namespace set//并查集
{
	int belong[112345];

	int find(int n)
	{
		return belong[n] == n ? n : belong[n] = find(belong[n]);
	}

	inline void combine(int fth, int son)
	{
		int f(find(fth)), s(find(son));
		if (f ^ s) belong[s] = f;
	}
}

class edge
{
public:
	int fr, to, len, rank;

	bool operator<(const edge& ed) const
	{
		return len < ed.len;
	}
}all[112345];

class graph
{
public:
	graph() : iEnd(2) {}
	class edge
	{
	public:
		int to, len, next, rank;
	}all[212345];
	int iEnd;
	int iHead[112345];
	
	void add(int fr, int to, int len, int rank)
	{
		all[iEnd].to = to;
		all[iEnd].len = len;
		all[iEnd].rank = rank;
		all[iEnd].next = iHead[fr];
		iHead[fr] = iEnd++;
	}
}map;//维护一张图

void read(int& v)
{
	char c(getchar());
	while (c < '0' || c > '9') c = getchar();
	v = c - '0'; c = getchar();
	while (c >= '0' && c <= '9')
	{
		v = v * 10 + c - '0';
		c = getchar();
	}
}
int n, m;

int ans[112345];

int front;

inline void GetMin(int& a, int b) { if (b < a) a = b; }
namespace tar//Tarjan
{
	int low[112345], vistime[112345], nowtime(1);
	bool bIsCut[112345];
	void find_bridge(int now, int father, int edrk)//这里是Tarjan找桥的算法，写法当然有很多，我的这个写法是自己靠理解的原理写的。。网上可能有更精彩、精炼的写法。
	{
		low[now] = vistime[now] = nowtime++;
		int tofth(0);
		for (int i(map.iHead[now]); i; i = map.all[i].next)
		{
			int to(map.all[i].to);
			if (!vistime[to])
			{
				find_bridge(to, now, i);
				GetMin(low[now], low[to]);
			}
			else
			{
				if (to != father) GetMin(low[now], vistime[to]);
				else ++tofth;
			}
		}
		if (edrk != -1 && tofth == 1 && low[now] >= vistime[now]) bIsCut[map.all[edrk].rank] = true;
	}
}

void judge(int beg, int end)//得到当前相同边权的所有边的答案
{
	tar::nowtime = 1;
	for (int i(beg); i != end; ++i)
	{
		if (!tar::vistime[all[i].fr])
		{
			tar::find_bridge(all[i].fr, -1, -1);//-1为无效值
		}
		if (tar::bIsCut[all[i].rank])
		{
			ans[all[i].rank] = 1;
		}
		set::combine(all[i].fr, all[i].to);
		map.iHead[all[i].fr] = 0;//把缩完后的点的边全部去掉
	}
}

int main()
{
	read(n); read(m);
	for (int i(1); i <= n; ++i) set::belong[i] = i;
	for (int i(0); i != m; ++i)
	{
		READ_3(all[i].fr, all[i].to, all[i].len);
		all[i].rank = i;
	}
	std::sort(all, all + m);
	map.add(all[0].fr, all[0].to, all[0].len, all[0].rank);
	map.add(all[0].to, all[0].fr, all[0].len, all[0].rank);
	for (int i(1); i != m; ++i)
	{
		all[i].fr = set::find(all[i].fr);
		all[i].to = set::find(all[i].to);
		if (all[i].len == all[i - 1].len)
		{
			if (set::find(all[i].fr) == set::find(all[i].to))
			{
				ans[all[i].rank] = -1;
			} 
			else
			{
				map.add(all[i].fr, all[i].to, all[i].len, all[i].rank);
				map.add(all[i].to, all[i].fr, all[i].len, all[i].rank);
				tar::vistime[all[i].fr] = tar::vistime[all[i].to] = 0;
			}
		}
		else
		{
			judge(front, i);
			front = i;//front是上一次操作到的位置
			all[i].fr = set::find(all[i].fr);
			all[i].to = set::find(all[i].to);
			if (set::find(all[i].fr) == set::find(all[i].to))
			{
				ans[all[i].rank] = -1;
			}
			else
			{
				map.add(all[i].fr, all[i].to, all[i].len, all[i].rank);
				map.add(all[i].to, all[i].fr, all[i].len, all[i].rank);
				tar::vistime[all[i].fr] = tar::vistime[all[i].to] = 0;
			}
		}
	}
	judge(front, m);//还剩一段小尾巴要处理
	for (int i(0); i != m; ++i)//输出
	{
		if (ans[i] == -1) puts("none");
		else if (ans[i] == 0) puts("at least one");
		else puts("any");
	}
	//PAUSE
	return 0;
}
```

---

## 作者：Nightingale_OI (赞：7)

### 大意

给定一个无向连通图，随机生成一棵最小生成树。

求其中每条边是否有可能或一定在该最小生成树中。

### 思路

先任意找一棵最小生成树，再来看剩下的边 $ (x,y,z) $。

设 $ g[i][j] $ 表示 $ i $ 跳 $ 2^j $ 次父亲所经过的路径上边的最大权值。

我们先找到 $ x $ 和 $ y $ 在这棵 MST 的最近公共祖先 $ c $ 同时求得路径上权值最大值为 $ eg $。

如果 $ eg < z $，说明这条边一定会换掉最小生成树中某条边，最小生成树求错了。

如果 $ eg = z $，说明这条边可以换掉最小生成树中某条边，即它有可能。

如果 $ eg > z $，说明这条边无法替换最小生成树中任意的边，即它不可能。

在倍增找 LCA 的同时，我们同时更新 $ h[i][j] $ —— $ i $ 跳 $ 2^j $ 次父亲经过的所有边要小于 $ h[i][j] $ 才不会被替换掉。

最后再做一次深搜，先更新 $ h[i][j] $，再判断当前点到父亲的边是否一定在。

对于一条树上的边 $ (fa,x,g[x][0]) $。

如果 $ h[x][0] < g[x][0] $，说明这条边一定会被换掉，最小生成树求错了。

如果 $ h[x][0] > g[x][0] $，说明这条边一定不会被换掉，一定在其中。

如果 $ h[x][0] = g[x][0] $，说明这条边可能被换掉，即有可能。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int n,m,s,l;
const int N=101010,k=20;
struct xy{int x,y,id;};
struct xyz{int x,y,z,id;}b[N];
inline void Min(int&x,int y){if(x>y)x=y;}
inline void Max(int&x,int y){if(x<y)x=y;}
vector<xy>q[N];
int fa[N],d[N],p[N];
int f[N][30],g[N][30],h[N][30];
inline bool cmp(xyz a,xyz b){return a.z<b.z;}
int fifa(int x){return x==fa[x]?x:fa[x]=fifa(fa[x]);}
void dfs1(int x,int fa,int v){
	f[x][0]=fa;g[x][0]=v;d[x]=d[fa]+1;
    f(i,1,k)f[x][i]=f[f[x][i-1]][i-1];
    f(i,1,k)g[x][i]=max(g[x][i-1],g[f[x][i-1]][i-1]);
    f(i,0,k)h[x][i]=N*N;
	for(xy e:q[x])if(e.x!=fa)dfs1(e.x,x,e.y);
}
void dfs2(int x,int fa,int id){
    for(xy e:q[x])if(e.x!=fa)dfs2(e.x,x,e.id);
    g(i,k,1){
        Min(h[x][i-1],h[x][i]);
        Min(h[f[x][i-1]][i-1],h[x][i]);
    }
	p[id]=(g[x][0]<h[x][0])+1;
}
inline void to(int&x,int i,int z,int&eg){Min(h[x][i],z);Max(eg,g[x][i]);x=f[x][i];}
void lca(int id){
    static int x,y,z,eg;
    x=b[id].x;y=b[id].y;z=b[id].z;eg=0;
    if(d[x]<d[y])swap(x,y);
    g(i,k,0)if(d[f[x][i]]>=d[y])to(x,i,z,eg);
    g(i,k,0)if(f[x][i]!=f[y][i]){
        to(x,i,z,eg);to(y,i,z,eg);
    }
    if(x!=y)to(x,0,z,eg),to(y,0,z,eg);
    if(z==eg)p[b[id].id]=1;
}
signed main(){
	int x,y,z,id;
    cin>>n>>m;
    f(i,1,n)fa[i]=i;
    f(i,1,m)scanf("%lld %lld %lld",&b[i].x,&b[i].y,&b[i].z),b[i].id=i;
    sort(b+1,b+m+1,cmp);
    f(i,1,m){
        s=fifa(x=b[i].x);l=fifa(y=b[i].y);z=b[i].z;id=b[i].id;
        if(s!=l){
            q[x].push_back((xy){y,z,id});
            q[y].push_back((xy){x,z,id});
            b[i].z=0;fa[s]=l;
        }
    }
    sort(b+1,b+m+1,cmp);
    dfs1(1,0,0);
    f(i,n,m)lca(i);
    dfs2(1,0,0);
    f(i,1,m){
        if(p[i]==0)printf("none\n");
        if(p[i]==1)printf("at least one\n");
        if(p[i]==2)printf("any\n");
    }
    return 0;
}
```

---

## 作者：mrsrz (赞：5)

首先随意找一棵最小生成树.

然后考虑新加入一条边$(u,v)$,会使树上多出一个环.由于最小生成树的特性,环上的边不会大于新加的边(否则把环上一条大于它的边替换成这条边显然更优,不符合最小生成树的定义).

如果环上有边权等于该边的其他边(就是$u,v$在树上路径上的边),则这条边是可以存在在最小生成树上的.否则不能.用主席树记录到根路径的权值情况,然后差分判断即可.

下面考虑树边.考虑$(u,v)$是一条非树边,其边权为$w$,则$(u,v)$路径上所有边权为$w$的边都可能不在最小生成树上.没有则一定在.

可以在考虑非树边的情况的时候,在节点上打差分标记.然后线段树合并上去判断即可.

时间复杂度$O(n\log W)$.$W$为边权最大值(窝直接取了$10^6$).

## Code:
```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1e5+6;
const int M=1e6+3;
struct edge{
    int u,v,w,id;
    inline bool operator<(const edge&rhs)const{return w<rhs.w;}
}e[N];
vector<int>G[N],w[N],num[N];
int n,m,ans[N],iid[N];
//0: cannot  1: can  2: must
namespace MST{
    int fa[N],usd[N];
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void work(){
        sort(e+1,e+m+1);
        for(int i=1;i<=n;++i)fa[i]=i;
        for(int i=1,ok=0;i<=m&&ok!=n-1;++i){
            int x=e[i].u,y=e[i].v;
            int fx=find(x),fy=find(y);
            if(fx!=fy){
                fa[fx]=fy;
                ++ok;
                G[x].push_back(y),G[y].push_back(x);
                w[x].push_back(e[i].w),w[y].push_back(e[i].w);
                num[x].push_back(e[i].id),num[y].push_back(e[i].id);
                usd[e[i].id]=1;
            }
        }
    }
}
namespace seg{
    int d[M*10],ls[M*10],rs[M*10],nod=0;
    void ins(int&o,int pre,int l,int r,const int&pos){
        d[o=++nod]=d[pre]+1;
        if(l<r){
            const int mid=l+r>>1;
            if(pos<=mid)ins(ls[o],ls[pre],l,mid,pos),rs[o]=rs[pre];else
            ins(rs[o],rs[pre],mid+1,r,pos),ls[o]=ls[pre];
        }
    }
    int query(int u,int v,int f,int l,int r,const int&pos){
        if(l==r)return d[u]+d[v]-2*d[f];
        const int mid=l+r>>1;
        if(pos<=mid)return query(ls[u],ls[v],ls[f],l,mid,pos);
        return query(rs[u],rs[v],rs[f],mid+1,r,pos);
    }
}
int rt[N],dep[N],fa[N],son[N],sz[N],top[N];
void dfs(int now){
    sz[now]=1,son[now]=0;
    for(int i=0;i<G[now].size();++i)
    if(!dep[G[now][i]]){
        const int v=G[now][i];
        seg::ins(rt[v],rt[now],1,1000000,w[now][i]);
        dep[v]=dep[now]+1;
        fa[v]=now;
        dfs(v);
        sz[now]+=sz[v];
        if(!son[now]||sz[son[now]]<sz[v])son[now]=v;
    }
}
void dfs2(int now){
    if(son[now])top[son[now]]=top[now],dfs2(son[now]);
    for(int i=0;i<G[now].size();++i){
        const int v=G[now][i];
        if(v!=son[now]&&dep[v]>dep[now])dfs2(top[v]=v);
    }
}
inline int LCA(int x,int y){
    while(top[x]!=top[y])if(dep[top[x]]>dep[top[y]])x=fa[top[x]];else y=fa[top[y]];
    return dep[x]<dep[y]?x:y;
}
namespace mgT{
    int d[M<<3],ls[M<<3],rs[M<<3],nod=0;
    void add(int&o,int l,int r,const int&pos,const int&dlt){
        if(!o)o=++nod;d[o]+=dlt;
        if(l<r){
            const int mid=l+r>>1;
            if(pos<=mid)add(ls[o],l,mid,pos,dlt);else
            add(rs[o],mid+1,r,pos,dlt);
        }
    }
    int merge(int ld,int rd,int l,int r){
        if(!ld||!rd)return ld|rd;
        if(l==r){
            d[ld]+=d[rd];
            return ld;
        }
        const int mid=l+r>>1;
        ls[ld]=merge(ls[ld],ls[rd],l,mid);
        rs[ld]=merge(rs[ld],rs[rd],mid+1,r);
        return ld;
    }
    int query(int o,int l,int r,const int&pos){
        if(l==r)return d[o];
        const int mid=l+r>>1;
        if(pos<=mid)return query(ls[o],l,mid,pos);
        return query(rs[o],mid+1,r,pos);
    }
}
int root[N];
void get(int now){
    for(int i=0;i<G[now].size();++i){
        const int v=G[now][i];
        if(dep[v]>dep[now]){
            get(v);
            ans[num[now][i]]=mgT::query(root[v],1,1000000,w[now][i])?1:2;
            root[now]=mgT::merge(root[now],root[v],1,1000000);
        }
    }
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i)
    cin>>e[e[i].id=i].u>>e[i].v>>e[i].w;
    MST::work();
    dfs(dep[1]=1);dfs2(1);
    for(int i=1;i<=m;++i)iid[e[i].id]=i;
    for(int i=1;i<=m;++i)
    if(!MST::usd[i]){
        int x=e[iid[i]].u,y=e[iid[i]].v;
        cerr<<i<<" : "<<iid[i]<<" "<<e[iid[i]].w<<endl;
        int lca=LCA(x,y);
        if(seg::query(rt[x],rt[y],rt[lca],1,1000000,e[iid[i]].w)){
            mgT::add(root[x],1,1000000,e[iid[i]].w,1);
            mgT::add(root[y],1,1000000,e[iid[i]].w,1);
            mgT::add(root[lca],1,1000000,e[iid[i]].w,-2);
            ans[i]=1;
        }else ans[i]=0;
    }
    get(1);
    for(int i=1;i<=m;++i)
    if(ans[i]==0)cout<<"none\n";else if(ans[i]==1)cout<<"at least one\n";else cout<<"any\n";
    return 0;
}

```

---

## 作者：Feyn (赞：4)

[link](https://www.luogu.com.cn/problem/CF160D)

给一种码量较小的 $O(M\log M)$ 的写法。

首先判断哪些边不可能出现在 MST 上。按照 Kruskal 的思路，一条边可能成为 MST 的一员当且仅当所有边权**严格**比它小的边无法使这条边连接的两个点合并在一起。

于是我们可以把那些边权相同的边分成一组，按组枚举，对于组内每条边去看边的两个点是否在同一个集合内，如果是，说明这条边肯定是不在 MST 上，直接忽略它即可；如果不是，说明它有可能在 MST 上，至于是否一定，后面再判断。判断完了之后呢，我们再遍历组内所有边，把每条边对应的两个集合合并，这样就可以准确的找出那些不可能再 MST 中的边。

那么哪些边一定在 MST 中呢？这样的边一定是不可取代的，而上一段我们已经找出了那些不能被比自己小的边取代的边，那么剩下的边中，只要不能被和自己一样大的边取代的边就一定在 MST 中了。

如何判断上面那个呢？可以想到，假如我们把之前形成的每个连通块当成一个点，把当前这一组的边全部加进去，一条边可能被一样大的边取代当且仅当它在一个环里。换句话说就是当这条边是割边的时候，它就一定在 MST 中了。

复杂度，排序是 $O(M\log M)$，求割边是 $O(N+M)$，所以复杂度是 $O(M\log M)$。注意每次求割边做好初始化。代码写出来挺短的。

```cpp
#include<bits/stdc++.h>
//#define feyn
const int N=100010;
using namespace std;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}
inline int min(int s1,int s2){return s1<s2?s1:s2;}

int m,n,f[N],ans[N];
inline int find(int wh){return f[wh]==wh?wh:f[wh]=find(f[wh]);}
struct node{int id,a,b,v;}a[N];
inline bool cmp(node s1,node s2){return s1.v<s2.v;}
struct edge{int t,v,nxt;}e[N<<1];
int head[N],esum,t[N],nt;
inline void add(int fr,int to,int val){
	if(t[fr]^nt)t[fr]=nt,head[fr]=0;
	e[++esum]=(edge){to,val,head[fr]};head[fr]=esum;
}
int dfn[N],cnt,low[N],about[N],vis[N],st[N<<1],top;
void dfs(int wh,int come){
	dfn[wh]=low[wh]=++cnt;vis[wh]=nt;
	if(t[wh]^nt)return;
	for(int i=head[wh],th;i;i=e[i].nxt){
		if((i^come)==1)continue;
		if(about[th=e[i].t]^nt)continue;
		if(dfn[th]&&vis[th]==nt)low[wh]=min(low[wh],dfn[th]);
		else{
			dfs(th,i);low[wh]=min(low[wh],low[th]);
			if(low[th]>dfn[wh])ans[e[i].v]=1;
		}
	}
}
char out[3][20]={"none","at least one","any"};

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(n);
	for(int i=1;i<=n;i++){read(a[i].a);read(a[i].b);read(a[i].v);a[i].id=i;}
	sort(a+1,a+n+1,cmp);for(int i=1;i<=m;i++)f[i]=i;
	for(int i=1;i<=n;){
		top=cnt=0;esum=1;nt++;int j=i;while(a[j+1].v==a[i].v)j++;
		for(int k=i;k<=j;k++){
			if(find(a[k].a)^find(a[k].b)){
				int fa=find(a[k].a),fb=find(a[k].b);
				add(fa,fb,a[k].id),add(fb,fa,a[k].id);
				about[fa]=about[fb]=nt;
				st[++top]=fa,st[++top]=fb;
			}
			else ans[a[k].id]=-1;
		}
		for(int k=1;k<=top;k++)if(vis[st[k]]^nt)dfs(st[k],0);
		for(;i<=j;i++)f[find(a[i].a)]=find(a[i].b);
	}
	for(int i=1;i<=n;i++)printf("%s\n",out[ans[i]+1]);
	
	return 0;
}
```

---

## 作者：Rosyclouds (赞：3)

## 树链剖分写法
题意：给出n个点，m条边，问每条边的类型：

0:可能在最小生成树上

1：一定在最小生成树上

2:一定不在最小生成树上

首先造出一颗最小生成树，记录最小生成树上的最长边的边权val，然后可以将边分成三类：

①:树边(最小生成树上的边)

②:非树边且边权<=val

③:非树边且边权>val


对于第三类，答案一定为2，所以我们只需要考虑①与②。对于①，答案要么为0，要么为1；对于②，答案要么为0，要么为2

对于每条①边，其作用为连接两个端点分别所在的集合，如果存在一条②边，边长和作用皆与其相同，则该①边的答案为0,否则为1

对于每条②边，可代替的①边在且仅在两个端点的路径上(画个图就能理解了)，所以用树链剖分+线段树维护每条①边可以被代替的最短②边边长

对于②边的答案，找出其能代替的最长①边的边长，用倍增维护即可


```c++
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define ls p<<1
#define rs p<<1|1
#define debug puts("debug");
const int M=1e5+5,P=1e9+7,base=269;
int n,m,totedge,head[M],faa[M],MX[M][18],vis[M],Mx,dep[M],tot,dfn[M],fa[M][18],top[M],son[M],sz[M],mi[M<<2],ans[M];
int find(int x){
	if(faa[x]==x)return x;
	return faa[x]=find(faa[x]);
}
struct EDGE{
	int x,y,val,id;
	bool operator < (const EDGE &_)const{
		return val<_.val;
	}
}B[M];
struct edge{
	int to,val,id,nxt;
}e[M<<1];
inline void add(int x,int y,int id,int v){
	e[++totedge]=(edge){y,v,id,head[x]};
	head[x]=totedge;
}
inline int rd(){
	int x=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x;
}
void dfs(int x,int f){
	fa[x][0]=f,dep[x]=dep[f]+1,sz[x]=1;
	for(int i=1;i<=17;++i){
		fa[x][i]=fa[fa[x][i-1]][i-1];
		MX[x][i]=max(MX[x][i-1],MX[fa[x][i-1]][i-1]);
	}
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f)continue ;
		MX[y][0]=e[i].val;
		dfs(y,x);
		sz[x]+=sz[y];
		if(sz[son[x]]<sz[y])son[x]=y;
	}
}
void dfs2(int x,int tp){
	top[x]=tp;dfn[x]=++tot;
	if(son[x])dfs2(son[x],tp);
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa[x][0]||y==son[x])continue ; 
		dfs2(y,y);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])x=fa[top[x]][0];
		else y=fa[top[y]][0];
	}
	return dep[x]>dep[y]?y:x;
}
void build(int l,int r,int p){
	mi[p]=2e9;
	if(l==r)return ;
	int mid=l+r>>1;
	build(l,mid,ls);
	build(mid+1,r,rs);
}
void update(int l,int r,int L,int R,int v,int p){
	if(l>=L&&r<=R){
		mi[p]=min(mi[p],v);
		return ;
	}
	int mid=l+r>>1;
	if(L<=mid)update(l,mid,L,R,v,ls);
	if(R>mid)update(mid+1,r,L,R,v,rs);
}
void Pre_update(int a,int b,int v,int id){
	int lca=LCA(a,b),now,mx=0;
	now=a;
	for(int i=17;~i;--i){
		if(dep[fa[now][i]]>=dep[lca]){
			mx=max(mx,MX[now][i]);
			now=fa[now][i];
		}
	}
	while(top[a]!=top[lca]){
		update(1,n,dfn[top[a]],dfn[a],v,1);
		a=fa[top[a]][0];
	}
	if(a!=lca)update(1,n,dfn[lca]+1,dfn[a],v,1);
	now=b;
	for(int i=17;~i;--i){
		if(dep[fa[now][i]]>=dep[lca]){
			mx=max(mx,MX[now][i]);
			now=fa[now][i];
		}
	}
	while(top[b]!=top[lca]){
		update(1,n,dfn[top[b]],dfn[b],v,1);
		b=fa[top[b]][0];
	}
	if(b!=lca)update(1,n,dfn[lca]+1,dfn[b],v,1);
	if(mx>=v)ans[id]=0;
	else ans[id]=2;
}
int query(int x,int l,int r,int res,int p){
	res=min(res,mi[p]);
	if(l==r)return res;
	int mid=l+r>>1;
	if(x<=mid)return query(x,l,mid,res,ls);
	return query(x,mid+1,r,res,rs);
}
void dfs3(int x,int f){
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f)continue ;
		int tmp=query(dfn[y],1,n,2e9,1);
		if(tmp>e[i].val)ans[e[i].id]=1;
		else ans[e[i].id]=0;
		dfs3(y,x);
	}
}
int main(){
	freopen("mstagain.in","r",stdin);
	freopen("mstagain.out","w",stdout);
	int a,b;
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)faa[i]=i;
	for(int i=1;i<=m;++i){
		B[i].x=rd(),B[i].y=rd(),B[i].val=rd();
		B[i].id=i;
	}	
	sort(B+1,B+m+1);	
	for(int i=1;i<=m;++i){
		a=find(B[i].x),b=find(B[i].y);
		if(a==b)continue ;
		vis[i]=1;
		faa[a]=b;
		add(B[i].x,B[i].y,B[i].id,B[i].val);
		add(B[i].y,B[i].x,B[i].id,B[i].val);
		Mx=B[i].val;
	}
	dfs(1,0);
	dfs2(1,1);
	build(1,n,1);
	for(int i=1;i<=m;++i){
		if(vis[i])continue ;
		if(B[i].val>Mx){
			ans[B[i].id]=2;
			continue ;
		}
		Pre_update(B[i].x,B[i].y,B[i].val,B[i].id);
	}
	dfs3(1,0);
	for(int i=1;i<=m;++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}



```


---

## 作者：WeLikeStudying (赞：2)

- [类题](https://www.luogu.com.cn/blog/luo1gu1zui1bang1/post-tu-lun-zui-xiao-ge)。

**题意**
- [链接](https://www.luogu.com.cn/problem/CF160D)。
- 给定一个无向连通图，判断它的每条边属于这三种情况的哪一种：在所有最小生成树上，在部分最小生成树上，不在任何最小生成树上。
- 点数 $n$ 和边数 $m$ 不大于 $10^5$。

**分析**
- 回想 $\text{Kruskal}$ 最小生成树算法：贪心加入最小的边，使之不成环。
- 我们可以获得一个极其平凡的判定不在任何生成树上的充分条件：若某条边在加入时已经连通，而且它的简单路径上不含任何等于该边权的边，那么它一定不在该生成树上。
- 容易证明它的必要性，如果存在一条边，把那条删掉然后换上这条，它也是最小生成树了。
- 那么接下来的问题在于如何确定某条边在所有最小生成树上，很容易想到类似的做法，如果我们在那个过程中找到了边，那么这条边本身和它所有的边一定只在部分最小生成树上。
- 那么可不可以用这个判定呢？我们回看 $\text{Kruskal}$ 算法，容易发现当小于某个值的所有边都被算入，图的连通性完全相同（因为相当于对一些不连通的子图跑最小生成树），如果我们尝试构造出一种反例就违反了它。
- 好啊，我们找到了一个很好的判断标准，但是它跑暴力会超时耶。
- 我们可以使用 [Link Cut Tree](https://www.luogu.com.cn/blog/luo1gu1zui1bang1/post-shuo-ju-jie-gou-dong-tai-shu-jie-gou)，可以暴力访问当前的最大值并打标记，时间复杂度 $O(m\log n)$。
- 当然这太奇葩了，为了这么个简单的东西你要写一个动态树结构，所以下一步我们探索实现细节。

**实现**
- 首先我们可以使用并查集完成不在任何最小生成树的点的判定，具体就是先把相同的边加一次（做到这一步，我们可以使用树链剖分+线段树完成接下来的操作）。
- 接下来问题在于如何判断是否一定在最小生成树上，容易发现，所有可行的边把连通块连成了这个样子。
![](https://cdn.luogu.com.cn/upload/image_hosting/1lc07zn6.png)
- 所以我们（并查集）缩点，然后使用 $\text{Tarjan}$ 找桥（注意没连过边的点不应该被加入否则复杂度会错），复杂度 $O(m\log n)$，瓶颈为排序。
- [代码实现](https://www.luogu.com.cn/paste/rlmup072)。

---

## 作者：fighter_OI (赞：2)

## 题意简述：

对于给定的无向连通图（无重边，自环），对于每一条边，考虑其：

1.一定在最小生成树上；

2.可能在最小生成树上；

3.一定不在最小生成树上。

## 思路：

当然要先找一棵最小生成树。

考虑树上的边，要么是情况1，要么是情况2；

考虑未被选中的边，如果将它加入生成树，势必会形成一个环，而将环上的任意一条边删除，仍是一棵生成树；

也就是说，对于一条未被选中的边，如果最小生成树上此边两端之间的路径（与此边组成一个环）上有一条边等于此边长，则将那条边替换为此边，仍为最小生成树，即那条边与此边均为情况2；

如果最小生成树上此边两端之间的路径上每条边都小于此边长，则该边为情况3，因为不存在一种替换方案；

不可能最小生成树上此边两端之间的路径上存在一条边比此边长，因为替换后会使生成树大小减小，就与原树为最小生成树矛盾。

此外为情况1。

## 做法
考虑轻重链剖分。使用轻重链剖分维护树上路径中的最大边权，

做完最小生成树后，枚举每一条未被选中的边（边权记为l），求出最小生成树上此边两端之间的路径上的最大边权max_l；

如果是情况3，较好判断，（l>maxl）；

如果是情况2，较好判断，（l=max_l）；

考虑在情况2时，也要将树上路径中权值等于l的边标记为2，使用线段树维护，详情见代码；

然后就没有了。
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
struct edge
{
	int u,v,l,num;
	bool operator<(const edge a)const
	{
		return l<a.l;
	}
}e[100005];//存边
int F[100005],n,m;
inline int getf(int k)
{
	return F[k]==k?k:(F[k]=getf(F[k]));
}//并查集
struct node
{
    int to,next,l,no;
}g[300021];
int h[100005];
int tot=0,tmp=0;
int to[100005],from[100005],a[100005],type[100005],at[100005];
inline void add(int u,int v,int l,int no)//加边
{
    tot++;
    g[tot].to=v;
    g[tot].next=h[u];
    g[tot].l=l;
    g[tot].no=no;
    h[u]=tot;
}
bool in[100005];
int siz[100005],son[100005],top[100005],d[100005],fa[100005];
inline void dfs_1(int k,int f)//第一遍dfs
{
    siz[k]=1;
    for(int i=h[k];i;i=g[i].next)
    {
        int v=g[i].to;
        if(v==f)continue;
        d[v]=d[k]+1;
        a[v]=g[i].l;
        at[v]=g[i].no;
        fa[v]=k;
        dfs_1(v,k);
        siz[k]+=siz[v];
        if(siz[v]>siz[son[k]])son[k]=v;
    }
}
inline void dfs_2(int k,int fa)//第二遍dfs
{
    top[son[k]]=top[k];
    to[k]=++tmp;
    from[tmp]=k; 
    if(son[k]==0)return;
    dfs_2(son[k],k);
    for(int i=h[k];i>0;i=g[i].next)
    {
        int v=g[i].to;
        if(v==fa||v==son[k])continue;
        top[v]=v;
        dfs_2(v,k);
    }
}
int f[400005];
bool tag[400005];
#define lc (k<<1)
#define rc (k<<1|1)
inline void bt(int l,int r,int k)//建立线段树
{
    if(l==r)
    {
        f[k]=a[from[l]];
        return;
    }
    int mid=(l+r)>>1,t=k<<1;
    bt(l,mid,t);
    bt(mid+1,r,t|1);
    f[k]=max(f[t],f[t|1]);
}
inline int query(int l,int r,int l1,int r1,int k)//查询区间最大
{
    if(l==l1&&r==r1)return f[k];
    int mid=(l+r)>>1;
    if(r1<=mid)return query(l,mid,l1,r1,lc);else
    if(l1>mid)return query(mid+1,r,l1,r1,rc);else
    {int t1=query(l,mid,l1,mid,lc),t2=query(mid+1,r,mid+1,r1,rc);
    return max(t1,t2);}
}
inline void Tag(int l,int r,int l1,int r1,int k,int t)//标记，标记的含义为该区间内所有等于最大值的节点被标记
{
	if(f[k]<t)return;//t一定不会为该区间子区间最大值
	if(l==l1&&r==r1)
	{
		if(f[k]==t){tag[k]=1;return;}//标记
		int mid=l+r>>1;
		if(f[lc]>=t)Tag(l,mid,l,mid,lc,t);//可能被标记
		if(f[rc]>=t)Tag(mid+1,r,mid+1,r,rc,t);//可能被标记
		return;
	}
	int mid=l+r>>1;
	if(r1<=mid)Tag(l,mid,l1,r1,lc,t);else
	if(l1>mid)Tag(mid+1,r,l1,r1,rc,t);else
	Tag(l,mid,l1,mid,lc,t),Tag(mid+1,r,mid+1,r1,rc,t);
}
inline int q_path(int u,int v)//树上路径最值查询
{
    int ans=0;
    while(top[u]^top[v])
    {
        if(d[top[u]]<d[top[v]])u^=v,v^=u,u^=v;
        ans=max(ans,query(1,n,to[top[u]],to[u],1));
        u=fa[top[u]];
    }
    if(to[u]==to[v])return ans;
    if(to[u]>to[v])u^=v,v^=u,u^=v;
    ans=max(ans,query(1,n,to[u]+1,to[v],1));
    return ans;
}
inline void t_path(int u,int v,int tmp)//路径标记
{
    int ans=100000;
    while(top[u]^top[v])
    {
        if(d[top[u]]<d[top[v]])u^=v,v^=u,u^=v;
        Tag(1,n,to[top[u]],to[u],1,tmp);
        u=fa[top[u]];
    }
    if(to[u]==to[v])return;
    if(to[u]>to[v])u^=v,v^=u,u^=v;
    Tag(1,n,to[u]+1,to[v],1,tmp);
}
inline void pushdown(int l,int r,int k)//下传标记以得到最终的答案
{
	if(l==r)
	{
		if(tag[k])type[at[from[l]] ]=2;return;
	}
	if(tag[k])
	{
		if(f[lc]==f[k])tag[lc]=1;
		if(f[rc]==f[k])tag[rc]=1;
	}
	int mid=l+r>>1;
	pushdown(l,mid,lc);
	pushdown(mid+1,r,rc);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v,l;
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].l);
		e[i].num=i;
	}
	sort(e+1,e+1+m);
	for(int i=1;i<=n;i++)F[i]=i;
	int k=1,tmp=0;
	while(tmp<n-1)
	{
		int t1=getf(e[k].u),t2=getf(e[k].v);
		if(t1!=t2)
		{
			in[k]=1;
			add(e[k].u,e[k].v,e[k].l,e[k].num);
			add(e[k].v,e[k].u,e[k].l,e[k].num);
			F[t1]=t2;
			tmp++;
		}
		k++;
	}//最小生成树
	fa[1]=top[1]=1;
	dfs_1(1,0);
	dfs_2(1,0);
	bt(1,n,1);//轻重链剖分
	for(int i=1;i<=m;i++)
	{
		type[e[i].num]=1;
		if(!in[i])
		{
			int tmp=q_path(e[i].u,e[i].v);
			if(e[i].l>tmp)type[e[i].num]=3;else
			{
				type[e[i].num]=2;
				t_path(e[i].u,e[i].v,tmp);
			}
		}
	}
	pushdown(1,n,1);
	for(int i=1;i<=m;i++)puts(type[i]==1?"any":(type[i]==2?"at least one":"none"));
	return 0;
}
```
代码太丑勿喷……




---

## 作者：orz_z (赞：0)

### 题目大意

给定带权无向连通图（无重边，自环），对于每一条边：

* 情况 $1$：一定在最小生成树上，输出 `any`；

* 情况 $2$：可能在某个最小生成树上，输出 `at least one`；

* 情况 $3$：一定不在最小生成树上，输出 `none`。

### 解题思路

首先根据 `Kruskal` 找到任意一棵最小生成树。

考虑新加入一条未选中的边 $(u,v)$，边权记为 $l$，那么必会形成一个环，由于最小生成树的特性，环上的边的权值不会大于 $l$，若满足前面的性质，那么 $(u,v)$ 这条边即为情况 $3$。

情况一，最小生成树上 $(u,v)$ 两端之间的路径上有一条边等于 $l$，则将那条边替换为此边，仍为最小生成树，即那条边与此边均为情况 $2$。

情况二，如果最小生成树上 $(u,v)$ 两端之间的路径上每条边都小于此边长，则该边为情况 $3$，因为不存在一种替换方案。

此外为情况 $1$。

考虑树链剖分，维护树上路径中的最大边权，

做完最小生成树后，枚举每一条未被选中的边（边权记为 $l$），求出最小生成树上此边两端之间的路径上的最大边权 $maxl$。

如果是情况 $3$，那么就是 $l>maxl$。

如果是情况 $2$，那么就是 $l=maxl$。

考虑在情况 $2$ 时，也要将树上路径中权值等于 $l$ 的边标记起来，使用线段树维护。

详见代码。

### CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int u, v, l, num;
    bool operator<(const edge a) const
    {
        return l < a.l;
    }
} e[100005];

int F[100005], n, m;

inline int getf(int k)
{
    return F[k] == k ? k : (F[k] = getf(F[k]));
}

struct node
{
    int to, next, l, no;
} g[300021];

int h[100005];

int tot = 0, cnt_node = 0;

int to[100005], from[100005], a[100005], type[100005], at[100005];

inline void add(int u, int v, int l, int no)
{
    tot++;
    g[tot].to = v;
    g[tot].next = h[u];
    g[tot].l = l;
    g[tot].no = no;
    h[u] = tot;
}

bool in[100005];

int siz[100005], son[100005], top[100005], d[100005], fa[100005];

inline void dfs1(int k, int f)
{
    siz[k] = 1;
    for (int i = h[k]; i; i = g[i].next)
    {
        int v = g[i].to;
        if (v == f)
            continue;
        d[v] = d[k] + 1;
        a[v] = g[i].l;
        at[v] = g[i].no;
        fa[v] = k;
        dfs1(v, k);
        siz[k] += siz[v];
        if (siz[v] > siz[son[k]])
            son[k] = v;
    }
}

inline void dfs2(int k, int fa)
{
    top[son[k]] = top[k];
    to[k] = ++cnt_node;
    from[cnt_node] = k;
    if (son[k] == 0)
        return;
    dfs2(son[k], k);
    for (int i = h[k]; i > 0; i = g[i].next)
    {
        int v = g[i].to;
        if (v == fa || v == son[k])
            continue;
        top[v] = v;
        dfs2(v, k);
    }
}

int f[400005];

bool tag[400005];

#define lc (k << 1)

#define rc (k << 1 | 1)

inline void build(int l, int r, int k)
{
    if (l == r)
    {
        f[k] = a[from[l]];
        return;
    }
    int mid = (l + r) >> 1, t = k << 1;
    build(l, mid, t);
    build(mid + 1, r, t | 1);
    f[k] = max(f[t], f[t | 1]);
}

inline int query(int l, int r, int l1, int r1, int k)
{
    if (l == l1 && r == r1)
        return f[k];
    int mid = (l + r) >> 1;
    if (r1 <= mid)
        return query(l, mid, l1, r1, lc);
    else if (l1 > mid)
        return query(mid + 1, r, l1, r1, rc);
    else
    {
        int t1 = query(l, mid, l1, mid, lc), t2 = query(mid + 1, r, mid + 1, r1, rc);
        return max(t1, t2);
    }
}

inline void update(int l, int r, int l1, int r1, int k, int t)
{
    if (f[k] < t)
        return;
    if (l == l1 && r == r1)
    {
        if (f[k] == t)
        {
            tag[k] = 1;
            return;
        }
        int mid = l + r >> 1;
        if (f[lc] >= t)
            update(l, mid, l, mid, lc, t);
        if (f[rc] >= t)
            update(mid + 1, r, mid + 1, r, rc, t);
        return;
    }
    int mid = l + r >> 1;
    if (r1 <= mid)
        update(l, mid, l1, r1, lc, t);
    else if (l1 > mid)
        update(mid + 1, r, l1, r1, rc, t);
    else
        update(l, mid, l1, mid, lc, t), update(mid + 1, r, mid + 1, r1, rc, t);
}

inline int querypath(int u, int v)
{
    int ans = 0;
    while (top[u] ^ top[v])
    {
        if (d[top[u]] < d[top[v]])
            u ^= v, v ^= u, u ^= v;
        ans = max(ans, query(1, n, to[top[u]], to[u], 1));
        u = fa[top[u]];
    }
    if (to[u] == to[v])
        return ans;
    if (to[u] > to[v])
        u ^= v, v ^= u, u ^= v;
    ans = max(ans, query(1, n, to[u] + 1, to[v], 1));
    return ans;
}

inline void updatepath(int u, int v, int cnt_node)
{
    int ans = 100000;
    while (top[u] ^ top[v])
    {
        if (d[top[u]] < d[top[v]])
            u ^= v, v ^= u, u ^= v;
        update(1, n, to[top[u]], to[u], 1, cnt_node);
        u = fa[top[u]];
    }
    if (to[u] == to[v])
        return;
    if (to[u] > to[v])
        u ^= v, v ^= u, u ^= v;
    update(1, n, to[u] + 1, to[v], 1, cnt_node);
}

inline void pushdown(int l, int r, int k)
{
    if (l == r)
    {
        if (tag[k])
            type[at[from[l]]] = 2;
        return;
    }
    if (tag[k])
    {
        if (f[lc] == f[k])
            tag[lc] = 1;
        if (f[rc] == f[k])
            tag[rc] = 1;
    }
    int mid = l + r >> 1;
    pushdown(l, mid, lc);
    pushdown(mid + 1, r, rc);
}

signed main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v, l;
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].l);
        e[i].num = i;
    }
    sort(e + 1, e + 1 + m);
    for (int i = 1; i <= n; i++)
        F[i] = i;
    int k = 1, cnt_node = 0;
    while (cnt_node < n - 1)
    {
        int t1 = getf(e[k].u), t2 = getf(e[k].v);
        if (t1 != t2)
        {
            in[k] = 1;
            add(e[k].u, e[k].v, e[k].l, e[k].num);
            add(e[k].v, e[k].u, e[k].l, e[k].num);
            F[t1] = t2;
            cnt_node++;
        }
        k++;
    }
    fa[1] = top[1] = 1;
    dfs1(1, 0);
    dfs2(1, 0);
    build(1, n, 1);
    for (int i = 1; i <= m; i++)
    {
        type[e[i].num] = 1;
        if (!in[i])
        {
            int cnt_node = querypath(e[i].u, e[i].v);
            if (e[i].l > cnt_node)
                type[e[i].num] = 3;
            else
            {
                type[e[i].num] = 2;
                updatepath(e[i].u, e[i].v, cnt_node);
            }
        }
    }
    pushdown(1, n, 1);
    for (int i = 1; i <= m; i++)
        puts(type[i] == 1 ? "any" : (type[i] == 2 ? "at least one" : "none"));
    return 0;
}
```



---

