# Two-Paths

## 题目描述

给定一棵带权树（无向连通无环图，无自环，无重边），共有 $n$ 个顶点。第 $j$ 条边 $\{u_j, v_j\}$ 的权值为 $w_j$。每个顶点 $i$ 有一个权值 $a_i$。

我们定义一条从顶点 $u$ 到顶点 $v$ 的路径为“2-路径”，如果每条边在路径中出现次数不超过两次（无论方向如何）。顶点在 2-路径中可以多次出现（起点和终点也可以多次出现）。

对于某条 2-路径 $p$，其收益定义为
$$
\text{Pr}(p) = \sum\limits_{v \in \text{路径中所有不同顶点}}{a_v} - \sum\limits_{e \in \text{路径中所有不同边}}{k_e \cdot w_e}
$$
其中 $k_e$ 表示边 $e$ 在路径 $p$ 中出现的次数。也就是说，顶点的权值只计算一次，但边的权值按出现次数累加。

你需要回答 $m$ 个询问。每个询问给出一对顶点 $(qu, qv)$。对于每个询问，求从 $qu$ 到 $qv$ 的所有 2-路径中，收益 $\text{Pr}(p)$ 最大的那一条。

## 说明/提示

关于样例询问的解释：

1. $(1, 1)$ —— 一条最优 2-路径为：$1 \rightarrow 2 \rightarrow 4 \rightarrow 5 \rightarrow 4 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 1$。$\text{Pr}(p) = (a_1 + a_2 + a_3 + a_4 + a_5) - (2 \cdot w(1,2) + 2 \cdot w(2,3) + 2 \cdot w(2,4) + 2 \cdot w(4,5)) = 21 - 2 \cdot 12 = 9$。
2. $(4, 4)$：$4 \rightarrow 2 \rightarrow 1 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 4$。$\text{Pr}(p) = (a_1 + a_2 + a_3 + a_4) - 2 \cdot (w(1,2) + w(2,3) + w(2,4)) = 19 - 2 \cdot 10 = 9$。
3. $(5, 6)$：$5 \rightarrow 4 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 1 \rightarrow 2 \rightarrow 4 \rightarrow 6$。
4. $(6, 4)$：$6 \rightarrow 4 \rightarrow 2 \rightarrow 1 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 4$。
5. $(3, 4)$：$3 \rightarrow 2 \rightarrow 1 \rightarrow 2 \rightarrow 4$。
6. $(3, 7)$：$3 \rightarrow 2 \rightarrow 1 \rightarrow 2 \rightarrow 4 \rightarrow 5 \rightarrow 4 \rightarrow 2 \rightarrow 3 \rightarrow 7$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7 6
6 5 5 3 2 1 2
1 2 2
2 3 2
2 4 1
4 5 1
6 4 2
7 3 25
1 1
4 4
5 6
6 4
3 4
3 7
```

### 输出

```
9
9
9
8
12
-14
```

# 题解

## 作者：GoPoux4 (赞：8)

考试做到了类似的一道题 [LOJ#6699](https://loj.ac/problem/6699)，题解是换根DP。但是我不会换根，所以用倍增过了这道题qwq。

---

#### 题意

给定一棵树，有点权和边权。询问从 $u$ 到 $v$，每条边最多经过两次（即往返两次），经过的点权减边权（点权只算一次）的最大值。

#### 题解

先考虑从点 $u$ 开始，进入它的子树再返回所能得到的最大价值。不难想出如下转移方程：

$$
f(u)=a_u+\sum_{v \in son_u} {\rm{max}}\{0,f(v)-w(u,v)-w(v,u)\}
$$

跑一遍树形DP将其计算出来。

然后考虑如何倍增。

记录 $ p(u,i) $ 表示从 $u$ 结点向上跳 $2^i$ 层后所到达的结点，这可以通过递推的方式求出：
$$
p(u,i)=p(p(u,i-1),i-1)
$$
记录 $F(u,i)$ 表示从 $u$ 结点到达 $p(u,i)$ 或从 $p(u,i)$ 到 $u$ 所能得到的最大价值（因为这道题在一条边上往返的花费都一样，所以只用记一个数组），也就是说途中可以从路径上的任意一个点进入它的子树再返回。然后我们~~凭直觉~~写出这个转移方程：
$$
F(u,i)=F(u,i-1)+F(p(u,i-1),i-1)
$$
但是这样转移，会有一部分信息重复计算，考虑用容斥的思想将这部分剔出去。

$F(u,i-1)$ 记录了图中红色区域内的信息，$F(u,i)$ 记录了图中蓝色区域内的信息：

![a8aMtA.png](https://s1.ax1x.com/2020/08/01/a8aMtA.png)

观察一下，缺失的部分正好是 $F(p(u,i-1),i-1)-f(p(u,i-1))$ 。于是我们得到了正确的转移方程：
$$
F(u,i)=F(u,i-1)+F(p(u,i-1),i-1)-f(p(u,i-1))
$$
接着考虑如何统计答案。

由于我们已经把信息记录到了倍增数组 $F$ 里面，所以现在只需要进行倍增求LCA的操作，并合并答案。

考虑如何在从 $u$ 跳到 $p(u,i)$ 时把 $F(u,i)$ 拼接到答案中去。

图中红色区域已经统计入答案，蓝色区域是跳到 $p(u,i)$ 后统计入答案的区域：

![a8Dsw8.png](https://s1.ax1x.com/2020/08/01/a8Dsw8.png)

类比上面 $F(u,i)$ 的计算过程，发现需要计入答案的就是 $F(u,i)-f(u)$ ，边倍增边统计答案即可。

然而当一个结点是另一个结点祖先时，这样统计没什么问题，而当两结点的的LCA不是他们其中任何一个时，在LCA处答案有重复，我们再考虑容斥来解决问题。

当 $u$ 与 $v$ 都跳到LCA下面时，有下面这个图：

蓝色部分是从 $v$ 到 $LCA$ 计算入答案的 $LCA$ 的其他子树部分，也就是说答案可能包含由 $LCA$ 进入蓝色区域的贡献，红色区域同理。绿色区域代表 $f(LCA)$ 。

![a8gBOs.png](https://s1.ax1x.com/2020/08/01/a8gBOs.png)

可以发现，$a_{LCA}$ 和 $LCA$ 除了 $u,v$ 的子树信息被计算了两次，而 $LCA$ 的子树中 $u,v$ 的子树信息不应该统计入答案，多余的信息恰好是 $f(LCA)$ ，已经算好了，将这部分在答案中剔除即可。

然后我就这样码了出来，结果样例都过不去。

![a82REt.png](https://s1.ax1x.com/2020/08/01/a82REt.png)

LCA还可以向它的祖先走，而上面完全没考虑这点，只在子树中统计。

经过~~乱搞~~分析，这个信息可以通过它的父亲转移过来，于是再记 $g(u)$ 代表从 $u$ 向它的祖先走再返回所能得到的最大贡献（注意，这里并没有将 $a_u$ 计入 $g(u)$ ）。用 $F$ 和 $f$ 来辅助 $g$ 的转移：
$$
g(u)= {\rm{max}}\{0,g(fa)+F(u,0)-f(u)-w(fa,u)\}
$$
由于只有 $LCA$ 才能向上走，所以最终答案再加上 $g(LCA)$ 即可。

---

$\text{Code}:$

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define maxn 300005
#define R register
#define INF 0x3f3f3f3f
using namespace std;
typedef long long lxl;

inline lxl read()
{
	lxl x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}

struct edge
{
	int v,w,next;
}e[maxn<<1];

int head[maxn],k;

inline void add(int u,int v,int w)
{
	e[k]=(edge){v,w,head[u]};
	head[u]=k++;
}

int n,q;
lxl f[maxn],a[maxn];

inline void dp(int u,int fa)
{
	f[u]=a[u];
	for(int i=head[u];~i;i=e[i].next)
	{
		int v=e[i].v;
		if(v==fa) continue;
		dp(v,u);
		if(f[v]-e[i].w-e[i^1].w>0)// 若为负则一定不会进入这棵子树，因为这样会让答案更劣
            f[u]+=f[v]-e[i].w-e[i^1].w;
	}
}

int p[maxn][30];
lxl F[maxn][30],g[maxn];
int dep[maxn];

inline void dfs(int u,int fa)
{
	dep[u]=dep[p[u][0]=fa]+1;
	for(int i=1;i<=25;++i)
	{
		p[u][i]=p[p[u][i-1]][i-1];
		F[u][i]=F[u][i-1]+F[p[u][i-1]][i-1]-f[p[u][i-1]];
	}
	for(int i=head[u];~i;i=e[i].next)
	{
		int v=e[i].v;
		if(v==fa) continue;
		F[v][0]=f[v]+f[u]-e[i^1].w;
		if(f[v]-2*e[i].w>0) F[v][0]-=f[v]-e[i].w-e[i^1].w;// 如果f[u]中包含了f[v]，则将其除去，避免重复计算
		g[v]=max(g[v],g[u]+F[v][0]-e[i].w-f[v]);
		dfs(v,u);
	}
}

inline lxl Query(int u,int v)// 倍增
{
	lxl ans=0;
	int a=u,b=v;
	if(dep[v]>dep[u]) swap(u,v);// 从深度深的开始跳
	for(int i=25;i>=0;--i)
		if(dep[p[u][i]]>=dep[v])
		{
			ans+=F[u][i]-f[u];
			u=p[u][i];
		}
	if(u==v) return ans+((dep[a]>dep[b])?f[a]:f[b])+g[u];
	for(int i=25;i>=0;--i)
		if(p[u][i]!=p[v][i])
		{
			ans+=F[u][i]-f[u]+F[v][i]-f[v];
			u=p[u][i];v=p[v][i];
		}
	return ans+F[u][0]-f[u]+F[v][0]-f[v]-f[p[u][0]]+f[a]+f[b]+g[p[u][0]];
}

int main()
{
	// freopen("CF1000G.in","r",stdin);
	n=read(),q=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	memset(head,-1,sizeof(int)*(n+5));
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		lxl w=read();
		add(u,v,w);
		add(v,u,w);
	}
	dp(1,0);//计算 f
	dfs(1,0);// 倍增预处理
	while(q--)
	{
		int u=read(),v=read();
		printf("%lld\n",Query(u,v));
	}
	return 0;
}

```



---

## 作者：Limit (赞：5)

# 题目大意

给出一棵树,多次查询两个点之间的 $\mathcal{Two-Path}$ 的权值的最大值,以下为 $\mathcal{Two-Path}$ 路径权值的定义:
$$
value=\sum\limits_{p\in path}a_p-\sum\limits_{e\in path}(w_ek_e)
$$
(其中 $a_i$ 表示 $i$ 的点权,$w_e$ 表示边 $e$ 的边权,$k_e$ 表示边 $e$ 被经过的次数,且要求 $0\leq k_e\leq 2$,即每条边最多被走过两次).

# 分析

假如给出的树长这个样子:

![](https://images.cnblogs.com/cnblogs_com/Sxy_Limit/1864899/o_2010161210391.jpg)

考虑有一次 $3\to 6$ 的查询.

显然对于 $3\to 6$ 这条简单路径上的边是只能走一次的(如果走了至少 $2$ 次,那么肯定要走至少 $3$ 次,这样是不合法的),所以考虑贡献的时候只需要去考虑不在这条简单路径上的部分即可,也就是如下部分(蓝色和绿色部分):

![](https://images.cnblogs.com/cnblogs_com/Sxy_Limit/1864899/o_2010161214204.jpg)

其中绿色部分是路径上的点的部分子节点的贡献,蓝色部分仅在 $\operatorname{LCA}(3,6)$(每次查询的两个节点的最近公共祖先)处存在.先考虑绿色部分的贡献.

显然可以先处理出 $f_i$ 表示 $i$ 节点的**所有**子节点对 $i$ 的贡献的最大值,显然有如下转移方程:

$$f_i=\sum\limits_{u\in son_i}\max\{f_u-2*VAL+val_u,0\}$$

($VAL_u$ 表示 $u$ 到 $u$ 的父亲这条边的边权,$val_u$ 表示 $u$ 节点的权值)

但是对于两个点查询的时候并不能把路径上所以的 $f$ 加起来,如下图:

![](https://images.cnblogs.com/cnblogs_com/Sxy_Limit/1864899/o_2010161232213.jpg)

我们需要的是蓝色部分以及绿色部分的贡献,但是对于 $4$ 号节点存的贡献是红色部分给它的,但实际应该是只能有绿色部分,也就是说要减去蓝色部分的贡献,再理解理解后就可以得到以下式子:

$$p=f_i+f_{fa}-{\color{red}\max\{f_i-2*VAL_i+val_{i},0\}}$$

($p$ 表示 $i,fa$ 的部分对当前这次查询的贡献,$fa$ 是 $i$ 的父节点,$fa,i$ 都是查询两个点再树上的简单路径上的点($i$ 为 $u$ 或 $v$,如果 $i\not= u$ 且 $i\not= v$,那么对于这条路径上的 $i$ 的子节点也需要减去自身对 $i$ 的贡献))

其中红色部分其实就是 $i$ 对 $fa$ 的贡献,将这部分拎出来就变成了所以非 $\operatorname{LCA}$ 的节点都需要减去自己为根节点的子树对父节点的贡献.因为这个东西是固定的,所以可以直接树上差分快速计算.这样就可以通过计算一次 $\operatorname{LCA}$ 的复杂度计算出所有路径节点的子树对路径的贡献.

下面只需要计算出 $\operatorname{LCA}$ 的父节点对它的贡献即可,可以发现这个东西可以换根 $\operatorname{dp}$ 求出:

$$g_i=\max\{g_{fa}+f_{fa}+val_{fa}-2*VAL_{i}-\max\{f_i-2*VAL_i+val_{i},0\},0\}$$

($g_i$ 表示 $i$ 的父节点对 $i$ 的贡献,具体推导比较显然,不展开)

对于查询两点的简单路径的贡献也可以直接树上差分,所以单次查询的复杂度 $=$ 计算两点 $\operatorname{LCA}$ 的复杂度.

因为不会 $\mathcal{Tarjan\ LCA}$ 所以用了树剖,但还是比倍增做法快了不少.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;last<=i;--i)
namespace IO
//快读模板
using namespace IO;
using namespace std;
const int MAXN=3e5+5;
const int MAXM=MAXN<<1;
int n,m;
long long val[MAXN];
struct Edge
{
	int to,next;
	long long val;
}edge[MAXM];
int edge_head[MAXN];
int edge_cnt=0;
#define FOR(now) for(int edge_i=edge_head[now];edge_i;edge_i=edge[edge_i].next)
#define TO edge[edge_i].to
#define VAL edge[edge_i].val
inline void AddEdge(int from,int to,long long val)
{
	edge[++edge_cnt].to=to;
	edge[edge_cnt].val=val;
	edge[edge_cnt].next=edge_head[from];
	edge_head[from]=edge_cnt;
}
long long f[MAXN];//f 同分析中的 f
long long sumf[MAXN];//f 函数的树上前缀和
long long d[MAXN];//每个点对父节点的贡献
long long sumdec[MAXN];//需要减去部分的树上前缀和
long long tof[MAXN];//每个点到父节点的边的边权
long long sump[MAXN],sume[MAXN];//点权与边权的树上前缀和
long long g[MAXN];//g 同分析中的 g
//以下变量为树剖所需变量
int point_deep[MAXN];
int point_father[MAXN];
int point_son[MAXN];
int point_size[MAXN];
int chain_cnt=0;
int point_id[MAXN];
int point_val[MAXN];
int chain_top[MAXN];
//树剖部分不会做说明,如有不理解建议先做模板题
void DFS_1(int now=1)//第一次 DFS
{
	sump[now]=sump[point_father[now]]+val[now];//树上前缀点权
	int max_size=-1;
	point_size[now]=1;
	FOR(now)
	{
		if(point_father[now]!=TO)
		{
			point_father[TO]=now;
			point_deep[TO]=point_deep[now]+1;
			tof[TO]=VAL;
			sume[TO]=sume[now]+VAL;//树上前缀边权
			DFS_1(TO);
			f[now]+=d[TO];//计算 f
			point_size[now]+=point_size[TO];
			if(point_size[TO]>max_size)
			{
				max_size=point_size[TO];
				point_son[now]=TO;
			}
		}
	}
	d[now]=max(f[now]-2*tof[now]+val[now],0ll);//计算这个点对父节点的贡献
}
void DFS_2(int now=1,int top=1,long long on=0/*从父节点转移来的 gi*/)
{
	g[now]=on;
	sumf[now]=sumf[point_father[now]]+f[now];
	sumdec[now]=sumdec[point_father[now]]+d[now];
	point_id[now]=++chain_cnt;
	point_val[chain_cnt]=val[now];
	chain_top[now]=top;
	if(!point_son[now])
	{
		return;
	}
	DFS_2(point_son[now],top,max(on+f[now]+val[now]-d[point_son[now]]-2*tof[point_son[now]],0ll));
	FOR(now)
	{
		if(TO!=point_father[now]&&TO!=point_son[now])
		{
			DFS_2(TO,TO,max(on+f[now]+val[now]-d[TO]-2*VAL,0ll));
		}
	}
}
int LCA(int u,int v)
{
	while(chain_top[u]!=chain_top[v])
	{
		if(point_deep[chain_top[u]]<point_deep[chain_top[v]])
		{
			swap(u,v);
		}
		u=point_father[chain_top[u]];
	}
	if(point_deep[v]<point_deep[u])
	{
		swap(u,v);
	}
	return u;
}
long long Query(int u,int v)
{
	int lca=LCA(u,v);
	return sumf[u]+sumf[v]-2*sumf[lca]+f[lca]-sumdec[u]-sumdec[v]+2*sumdec[lca]+g[lca]-sume[u]-sume[v]+2*sume[lca]+sump[u]+sump[v]-sump[lca]-sump[point_father[lca]];//又臭又长的树上差分
}

int main()
{
	Read(n,m);
	REP(i,1,n)
	{
		Read(val[i]);
	}
	int u,v,w;
	REP(i,1,n-1)
	{
		Read(u,v,w);
		AddEdge(u,v,w);
		AddEdge(v,u,w);
	}
	DFS_1();
	DFS_2();
	REP(i,1,m)
	{
		Read(u,v);
		Writeln(Query(u,v));
	}
	return 0;
}
```



---

## 作者：NuoCarter (赞：3)

# CF1000G Two-Paths 题解

## 题意

给定一颗树，询问一条以 `u`,`v` 为起点与重点的路径的  点权和-边权和，
每条边最多经过两次，点权仅能算一次所能得到的最大值。

## 思路：换根DP

![](https://cdn.luogu.com.cn/upload/image_hosting/dw13y5w1.png)

首先对于上面这个图，我们可以发现整个路径的特征，**边的编号表示一种可能的遍历顺序**：

1.（其实可以先遍历 `u` 的子树，只不过图中未画出。）

2.在 `u` 到 `LCA` 的路径上的一点 `x` ，可以选择遍历完 `x` 的子树后再往 `x` 的父亲走。

3.到达了 `LCA` 后，可以选择遍历完 `LCA` 的子树后再遍历 `LCA` 向上的那一部分。

4.从 `LCA` 到 `v` 的路径上一点 `x` 可以选择遍历完  `x`  除了向 `v` 的那一部分在向 `v` 那边走.

--------
于是设一个`dp` 方程 `dp[x][0]` 与 `dp[x][1]` 

`dp[x][0]` 表示从 `x` 往下走最终回到 `x ` 的最大价值。

`dp[x][1]` 表示从 `x` 随便走（即以 `x` 为出发点的全局最大值），最终回到 `x` 的最大价值。

**PS:上文的遍历是在最优选择下的遍历，并不是全部遍历完的意思。**

 ## DP的转移：

仅仅选择子树的话很简单，设当前点为 `u` , 出点为 `v` 。

如果当前 `u` 最优可以选择 `v` ，一定是可以获得的价值 >0 ，即 `dp[v][0]-edge[i]-edge[i^1]` ，`edge[i]` 表示这条边，而`edge[i^1]` 就是这条边的反边。（因为过去还要回来，所以是这个代价）

于是方程也很简单：`dp[u][0]` 的初始值首先设为 `a[x]` 然后 `dp[x][0]+=max(0,dp[y][0]-edge[i]-edge[i^1])`

也就是一个简单的 `Dfs` 可以解决。

而 `dp[u][1]` 仅仅需要一个换根就解决了。

但是注意转移时，因为 `dp[u][1]` 表示的是全局，可能会对 `dp[v][1]` 产生重复计算，这个时候我们需要剪掉重复计算的部分，即 `dp[v][0]` ，当然，`dp[v][0]` 可能对 `dp[u][1]` 无贡献。计算一下是否 `dp[v][0]-edge[i]-edge[i^1]` 是否>0即可，转移时同样计算 `dp[u][1]` 是否可以对它的产生贡献，也就是除去重复的贡献后再剪掉两个边的边权，具体可以看代码。

两个 `Dfs` 即可搞定，一次预处理，一次换根就可以了。

## 处理答案

首先发现 `u->LCA->v` 这条路径是必定经过的，所以预先处理出这个边权，

设 `h(u,v)` 为 `v` 是否计入 `u` 的贡献，即 $\max(0,dp[v][0]-e_{u->v}-e_{v->u})$ 

发现整个 `u->LCA` 的代价可以表示为 $\sum_{i=1}^n dp[u_i][0]-h(fa_{u_i},u_i)$ （这个式子的意思就是选完路径上每一个点的最优子树然后剪掉这个点对于他父亲的重复贡献。

同理的`v->LCA` 的代价也珂以用一个类似的式子表示，最后加上 `dp[LCA][1]` 再减去路径边权即可。

然后上面的那个式子可以用一个前缀和优化掉。这样就可以直接求出答案了。

用了树剖求 `LCA`，于是处理路径的边权和会包含在了树剖中的 `DFS1` 里面。

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=false;
	while(!isdigit(ch))	f|=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;return;
}
template <typename T>
inline void print(T x){
	if(x<0)	putchar('-'),x=-x;
	if(x>9)	print(x/10);
	putchar(x%10^48);return;
}
#define int long long
const int N=3e5+3;
int head[N],to[N<<1],Next[N<<1],edge[N<<1],tot=1,n,a[N],q;
inline void Addedge(int u,int v,int w){
	to[++tot]=v,edge[tot]=w,Next[tot]=head[u],head[u]=tot;
	return;
}
//Tree&DP
int fa[N],siz[N],son[N],dep[N],up[N],down[N];
inline void Dfs1(int x,int f){
	dep[x]=dep[f]+1,siz[x]=1,fa[x]=f;
	for(register int i=head[x];i;i=Next[i]){
		int y=to[i];if(y==f)	continue;
		down[y]=down[x]+edge[i],up[y]=up[x]+edge[i^1];
		Dfs1(y,x);siz[x]+=siz[y];
		son[x]=siz[son[x]]<siz[y] ? y :son[x];
	}
	return;
}
int top[N];
inline void Dfs2(int x){
	top[x]=son[fa[x]]==x ? top[fa[x]] : x;
	if(son[x])	Dfs2(son[x]);
	for(register int i=head[x];i;i=Next[i]){
		int y=to[i];
		if(y==fa[x]||y==son[x])	continue;
		Dfs2(y);
	}
	return;
}
inline int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]) u=fa[top[u]];
		else v=fa[top[v]];
	}
	return dep[u]>dep[v] ? v: u;
}
//DP
int dp[N][2];
inline int Get(int v,int i){return dp[v][0]-edge[i]-edge[i^1];}
int g[N];
inline void Dfs(int x){
	dp[x][0]=a[x];
	for(register int i=head[x];i;i=Next[i]){
		int y=to[i];
		if(y==fa[x])	continue;
		Dfs(y);
		if(Get(y,i)>0)	dp[x][0]+=Get(y,i);
	}
	return;
}
inline void Croot(int x){
	for(register int i=head[x];i;i=Next[i]){
		int y=to[i];
		if(y==fa[x])	continue;
		int tmp=0;if(Get(y,i)>0)	tmp=Get(y,i);
		if(dp[x][1]-tmp-edge[i]-edge[i^1]>0) dp[y][1]=dp[y][0]+dp[x][1]-tmp-edge[i]-edge[i^1];
		else dp[y][1]=dp[y][0];
		g[y]=g[x]+dp[y][0]-tmp;
		Croot(y);
	}
	return;
}

signed main(){
	read(n),read(q);
	for(register int i=1;i<=n;++i)	read(a[i]);
	for(register int i=1;i<n;++i){
		int x,y,z1,z2;read(x),read(y),read(z1),z2=z1;
		Addedge(x,y,z1),Addedge(y,x,z2);
	}
	Dfs1(1,0),Dfs2(1);
	Dfs(1);dp[1][1]=dp[1][0];Croot(1);
	while(q--){
		int u,v;read(u),read(v);
		int l=LCA(u,v);
		int ans1=up[u]-up[l]+down[v]-down[l],ans2=g[u]+g[v]-2*g[l]+dp[l][1];
		print(ans2-ans1),putchar('\n');
	}
	return 0;
}

```



---

## 作者：Mobius127 (赞：2)

[link](https://www.luogu.com.cn/problem/CF1000G)

顺着 [loj6699](https://loj.ac/p/6699) 过来的，不难发现 loj 那题是在这题的加强版，那么直接给出 loj 的做法。

设 $w(x, y)$ 分别为 $x \to y$ 的边权和，$f_x$ 为在 $x$ 子树中走一遍并回到 $x$ 的最优价值。

那么有 $f_x=a_x+\sum_{(x, y)\in T} \max(0, f_y-w(x, y)-w(y, x))$。

设上式 $y$ 对 $x$ 的贡献为 $g_x$。

设所求为 $h(u, v)$ 拆成两条路径，变为 $h(u, \operatorname{LCA})+h(\operatorname{LCA}, v)+D(\operatorname{LCA})$，其中 $D(\operatorname{LCA})$ 为 $\operatorname{LCA}$ 处额外的贡献。

考虑一条最优路径 $P(u, v)$，在走的过程中我们只会经过 $u\to v$ 的简单路径上的边一次，在走到简单路径上的某个点时，会走到其他子树中再折返回来，也就是说，$P(u, v)$ 中除去简单路径上的边后，剩下的边都从两个方向分别走了一次，直接利用 $g_x$ 容斥掉多余的贡献即可，因此有：

$$h(x, anc)=-w(x, anc)+g_{anc}+\sum_{v\in P(x, anc)} f_v-g_v$$

$$h(anc, x)=-w(anc, x)+g_{anc}+\sum_{v\in P(x, anc)} f_v-g_v$$

其中 $anc$ 是 $x$ 的祖先。

考虑求 $D(\operatorname{LCA})$，首先 $f_{\operatorname{LCA}}$ 被算了两次，减去一个。

从 $\operatorname{LCA}$ 可以向子树外走，设 $r_x$ 为只走 $x$ 子树外后回到 $x$ 的最优权值。

那么有 



$$r_x=a_x+\max(0, r_{fa_x}-w(x, fa_x)-w(fa_x, x)+\sum_{(fa_x, y)\in T\wedge x\ne y} \max(0, f_y-w(fa_x, y)-w(x, fa_x)))$$

然后发现后面那东西就是 $f_{fa_x}-a_{fa_x}-g_x$，所以

$$r_x=a_x+\max(0, r_{fa_x}-w(x, fa_x)-w(fa_x, x)+f_{fa_x}-a_{fa_x}-g_x)$$

那么直接预处理出 $f, g, r, dis$ 和 $f_x-g_x$ 的前缀和即可，复杂度为 $O(n\log n+m)$，瓶颈在于求 $\operatorname{LCA}$。

[code](https://loj.ac/s/1693048)



---

## 作者：Piwry (赞：1)

码代码时很担心最后怎么调试，不过还好基本没出什么岔子几下就调出来了X

## 解析

考虑一条从 $x$ 到 $y$ 的 2-Path。如果中途 “离开” 了 $(x, y)$ 的路径，最后一定得回到这条路径上；假设 2-Path 从 $(x, y)$ 路径上的点 $u$ 离开了路径，就会类似在 $u$ 的子树内（不含路径）走了一圈，最后再回到 $u$

我们暂时先不考虑子树包含路径的问题，考虑怎么算这个值（从子树里绕一圈回来得到的最大贡献）。这显然可以 dp。具体来说，设 $dp(u)$ 表示只允许走 $u$ 子树内的结点，2-Path（就是题目定义的那样）$p(u, u)$ 的最大值；其转移方程即为 $dp(u)=a_u+\sum\limits_{v}\max(0, dp(v)-2w(u, v))$，其中 $v$ 是 $u$ 的儿子，$w(u, v)$ 指边 $(u, v)$ 的权值

然而 dp 出了这东西后还是很麻烦，需要分类讨论太多了。接着发现这东西挺好换根的，因此可以考虑用换根 dp 做出以每个点为根时各点的 dp 值；对每个询问 $(x, y)$，我们就在**以 $x$ 为根时**处理它

考虑对于询问 $(x, y)$，并且此时的 dp 值以 $x$ 为根，我们该怎么计算出 2-Path $p(x, y)$ 的最大值

可以发现，设路径上的两点 $u, v$，且 $u$ 为 $v$ 的父亲，那么答案就为 $\sum(dp(v)-\max(0, dp(v)-2w(u, v))-w(u, v))+dp(x)$（其中 $\max(0, dp(v)-2w(u, v))$ 是为了去掉 $u$ 的 dp 值中走入 $v$ 的贡献）

这个东西可以用各种方式快速维护；但考虑换根时还需做（单点）修改，因此要用 树剖/lct 维护

于是这题就做完了。总复杂度 $O(n\log n)$

## CODE

为了方便我就直接复制了 lct 的模板X

lct 中我对每个结点维护了两个权值，分别为 $dp(v)$ 和 $(\max(0, dp(v)-2w(u, v))+w(u, v))$；并且我没显式地在最后加上 $dp(x)$，而是将 $w(x, 0)$ 设为 $0$，并设 $x$（树根）的父亲为 $0$，直接套用了上面的维护

注意代码细节很多。尤其换根 dfs 中每次从儿子返回记得**还原**修改，毕竟还要做树链查询的

```cpp
#include <cstdio>
#include <algorithm>
#define ll long long
using std::sort;
using std::max;

const int MAXN =3e5+50, MAXQ =4e5+50;

/*------------------------------Lct------------------------------*/

int Lct_c[2][MAXN], Lct_fa[MAXN];
ll Lct_sum1[MAXN], Lct_val1[MAXN], Lct_sum2[MAXN], Lct_val2[MAXN];
bool rev[MAXN];

#define c Lct_c
#define f Lct_fa

inline void pushdown(const int &x){
	if(rev[x]){
		rev[c[0][x]] ^=1, rev[c[1][x]] ^=1;
		c[0][x] ^=c[1][x] ^=c[0][x] ^=c[1][x];
		rev[x] =0;
	}
}

inline void pushup(const int &x){
	Lct_sum1[x] =Lct_sum1[c[0][x]]+Lct_sum1[c[1][x]]+Lct_val1[x];
	Lct_sum2[x] =Lct_sum2[c[0][x]]+Lct_sum2[c[1][x]]+Lct_val2[x];
}

inline bool isroot(const int &x){ return ((c[0][f[x]] != x && c[1][f[x]] != x) || f[x] == 0); }

inline bool rotate_get(const int &x){ return (c[1][f[x]] == x); }

inline void rotate(int x){
	bool r =rotate_get(x), rf =rotate_get(f[x]);
	int y =f[x], z =f[y], a =c[!r][x];
	f[x] =z; if(!isroot(y)) c[rf][z] =x;
	f[y] =x, c[!r][x] =y;
	f[a] =y, c[r][y] =a;
	pushup(y);
}

void pushall(int x){
	if(!isroot(x))
		pushall(f[x]);
	pushdown(x);
}

void splay(int x){
	pushall(x);
	for(; !isroot(x); rotate(x))
		if(!isroot(f[x]))
			rotate((rotate_get(f[x]) == rotate_get(x)) ? f[x] : x);
	pushup(x);
}

void access(int x){
	for(int pre =0; x; pre =x, x =f[x]){
		splay(x);
		c[1][x] =pre;
		pushup(x);
	}
}

inline void setroot(int x){
	access(x), splay(x);
	rev[x] =1;
}

inline void link(int x, int y){
	setroot(x); f[x] =y;
}

inline ll Lct_query1(int x, int y){
	setroot(x), access(y), splay(y);
	return Lct_sum1[y];
}

inline ll Lct_query2(int x, int y){
	setroot(x), access(y), splay(y);
	return Lct_sum2[y];
}

inline void updata(int x, const ll &val1, const ll &val2){
	splay(x);
	Lct_val1[x] =val1, Lct_val2[x] =val2;
	pushup(x);
}

#undef c
#undef f

/*------------------------------Map------------------------------*/

int first[MAXN], tote;
struct edge{
	int to, net, w;
}e[MAXN<<1];

inline void addedge(const int &u, const int &v, const int &w){
	++tote;
	e[tote].to =v, e[tote].net =first[u], e[tote].w =w;
	first[u] =tote;
	++tote;
	e[tote].to =u, e[tote].net =first[v], e[tote].w =w;
	first[v] =tote;
}

/*------------------------------Dfs------------------------------*/

int dfn[MAXN], tot;

/*------------------------------Query------------------------------*/

struct Query{
	int x, y, qid;
	
	bool operator < (const Query &B) const{
		return dfn[x] < dfn[B.x];
	}
}query[MAXQ];
ll Ans[MAXQ];
int cur_q;

/*------------------------------Dp------------------------------*/

int a[MAXN], w_fa[MAXN];
ll dp[MAXN];/*u 子树内的 2-Path(u, u) 的最大值*/

void dfs1(int u, int fa){
	dfn[u] =tot++;
	dp[u] =a[u];
	for(int l =first[u]; l; l =e[l].net)
		if(e[l].to != fa){
			w_fa[e[l].to] =e[l].w;
			dfs1(e[l].to, u);
			if(dp[e[l].to]-2*e[l].w > 0)
				dp[u] +=dp[e[l].to]-2*e[l].w;
		}
}

void dfs2(int u, int fa){
	while(query[cur_q].x == u){
		int y =query[cur_q].y;
		Ans[query[cur_q].qid] =Lct_query1(u, y)-Lct_query2(u, y);
		++cur_q;
	}
	for(int l =first[u]; l; l =e[l].net)
		if(e[l].to != fa){
			ll delta1 =max(0ll, dp[e[l].to]-2*w_fa[e[l].to]);
			dp[u] -=delta1;
			w_fa[u] ^=w_fa[e[l].to] ^=w_fa[u] ^=w_fa[e[l].to];
			ll delta2 =max(0ll, dp[u]-2*w_fa[u]);
			dp[e[l].to] +=delta2;
			updata(u, dp[u], w_fa[u]+delta2);
			updata(e[l].to, dp[e[l].to], 0);
			
			dfs2(e[l].to, u);
			
			dp[u] +=delta1;
			w_fa[u] ^=w_fa[e[l].to] ^=w_fa[u] ^=w_fa[e[l].to];
			dp[e[l].to] -=delta2;
			updata(u, dp[u], 0);
			updata(e[l].to, dp[e[l].to], w_fa[e[l].to]+delta1);
		}
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<3)+(x<<1)+(48^c), c =getchar();
	return (f) ? -x : x;
}

int main(){
	int n =read(), q =read();
	for(int i =1; i <= n; ++i)
		a[i] =read();
	for(int i =0; i < n-1; ++i){
		int u =read(), v =read(), w =read();
		addedge(u, v, w);
	}
	for(int i =0; i < q; ++i){
		query[i].x =read(), query[i].y =read();
		if(dfn[query[i].x] > dfn[query[i].y])/*不交换也无大碍*/
			query[i].x ^=query[i].y ^=query[i].x ^=query[i].y;
		query[i].qid =i;
	}
	
	dfs1(1, 0);
	for(int x =1; x <= n; ++x){
		Lct_val1[x] =Lct_sum1[x] =dp[x];
		Lct_val2[x] =w_fa[x];
		if(x != 1 && dp[x]-2*w_fa[x] > 0){
			Lct_val2[x] +=dp[x]-2*w_fa[x];
			Lct_sum2[x] +=dp[x]-2*w_fa[x];
		}
	}
	for(int i =1; i <= tote; i +=2)
		link(e[i].to, e[i+1].to);
	sort(query, query+q);
	dfs2(1, 0);
	
	for(int i =0; i < q; ++i)
		printf("%lld\n", Ans[i]);
}
```

---

## 作者：FjswYuzu (赞：1)

代码其实是 [LOJ6699](https://loj.ac/p/6699) 稍微改了一下。

这个题简直是令人无语。

首先 2-Path 这种定义就有够无语了。显然最优情况下，不在路径上的边只会顺向走一次，其他的边最多走两次。

我们维护三个数组 $f,g,h$。分别表示：

- $f_i$：在以 $1$ 为根的树中，从 $i$ 开始只在以 $i$ 为根的子树中走的最大的贡献；   
- $g_i$：在以 $1$ 为根的树中，从 $i$ 的父亲 $p$ 开始，只在以 $p$ 为根的子树中走并且不经过 $i$ 的最大的贡献；   
- $h_i$：以 $i$ 为起点不加其他限制的最大的贡献。

考虑计算 $f_i$。显然一个子树只有经过或者不经过两种可能，两种情况取 $\max$。

在处理 $f_i$ 后，我们可以处理所有 $x \in \operatorname{son}_i$ 的 $g_x$。方法是要么走还是不走，相当于除去计算 $f_i$ 的时候，$g_x$ 的贡献。

然后要弄出 $h_i$ 出来。这是显然的换根 dp，方法是：

- 如果当前结点 $p$ 是 $1$，$h_p \gets f_p$；   
- 否则，我们将其父亲结点 $q$ 的 $h$ 值先减去当前子树在 $f_q$ 中的贡献减去在 $p,q$ 间往返一次的花费作为 $p$ 往 $q$ 走的贡献，然后再加上 $f_p$ 就可以算出 $h_p$。

最后需要计算答案。注意到我们预处理了很多东西，但是我们还是需要分类讨论……

令 $u,v$ 为询问的点，$p$ 为两点间 LCA，$u'$ 为 $p$ 向 $u$ 走一步的点，$v'$ 同理。这些东西可以预处理倍增数组，算 $u'$ 可以倍增求出 $u,p$ 间距离，减去一后再从 $u$ 倍增跳。（虽然但是，好深比啊。）

- 如果 $u=v$：输出 $h_u$；   
- 如果 $u,v$ 在同一条链上（即，两点 LCA 为两点之一）：先确定谁在上面谁在下面（在这个题里面其实不太需要），这里假设 $u$ 在下面。分析发现，$u$ 可以往其子树走，$p$ 可以往上走，但是要排去向 $u'$ 走的贡献。答案就是 $u \to u'$ 上所有结点的 $g$ 值，加上 $f_u$ 值，加上 $h_p$ 并减去 $g_{u'}$ 在 $h_p$ 内的贡献，最后减去 $u \to v$ 路径上所有边的花费加上应有的点的贡献（点权具体实现方法具体处理，原因是我们可能已经在 $f,g,h$ 里面算了点的贡献）；   
- 否则，我们将路径拆成两条链 $u\to u',v \to v'$ 并且特殊处理 $p$。沿用上面的方法就行，有一些多余的细节。

细节很多，推荐看代码。如果感觉有问题可以看一下 $f(dp),g(dp_1),h(dp_2)$ 的计算方式。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
LL read()
{
	LL x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')	f=(c=='-'?-1:f),c=getchar();
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x*f;
}
void write(LL x)
{
	if(x<0)	putchar('-'),x=-x;
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
vector<LL> G[300005];
LL n,a[300005],sum[300005],sd[300005],U[300005],V[300005],Z1[300005],Z2[300005],dep[300005],fa[19][300005],lgs[300005],sz1[300005],sz2[300005],dp[300005],dp1[300005],dp2[300005],rev[300005];
void dfs(LL now,LL pre)
{
	fa[0][now]=pre;
	dep[now]=dep[pre]+1;
	for(auto st:G[now])	if(st^pre)	dfs(st,now);
}
LL LCA(LL u,LL v)
{
	if(dep[u]>dep[v])	swap(u,v);
	while(dep[u]<dep[v])	v=fa[lgs[dep[v]-dep[u]]][v];
	if(u==v)	return u;
	for(LL i=18;~i;--i)	if(fa[i][u]!=fa[i][v])	u=fa[i][u],v=fa[i][v];
	return fa[0][u];
}
LL queKth(LL u,LL ac)
{
	LL ret=0;
	for(LL i=18;~i;--i)	if(dep[fa[i][u]]>=dep[ac])	u=fa[i][u],ret|=(1<<i);
	return ret;
}
LL getKth(LL u,LL kt)
{
	for(LL i=18;~i;--i)	if((kt>>i)&1)	u=fa[i][u];
	return u;
}
void dfs1(LL now,LL pre)
{
	sum[now]=dp[now]=a[now];
	for(auto st:G[now])	if(st^pre)	dfs1(st,now);
	for(auto st:G[now])	if(st^pre)	dp[now]+=max(dp[st]-Z1[rev[st]]-Z2[rev[st]],0ll);
	for(auto st:G[now])	if(st^pre)	sd[st]=dp1[st]=dp[now]-max(dp[st]-Z1[rev[st]]-Z2[rev[st]],0ll)-a[now];
}
void dfs2(LL now,LL pre)
{
	if(!pre)	dp2[now]=dp[now];
	else	dp2[now]=max(0ll,dp2[pre]-max(dp[now]-Z1[rev[now]]-Z2[rev[now]],0ll)-Z1[rev[now]]-Z2[rev[now]])+dp[now];
	for(auto st:G[now])	if(st^pre)	dfs2(st,now);
}
void maintain(LL now,LL pre){for(auto st:G[now])	if(st^pre)	sum[st]+=sum[now],sd[st]+=sd[now],sz1[st]+=sz1[now],sz2[st]+=sz2[now],maintain(st,now);}
int main(){
	n=read();
	LL q=read();
	for(LL i=1;i<=n;++i)	a[i]=read();
	for(LL i=1;i<n;++i)	U[i]=read(),V[i]=read(),Z1[i]=Z2[i]=read(),G[U[i]].push_back(V[i]),G[V[i]].push_back(U[i]);
	dfs(1,0);
	for(LL i=1;i<n;++i)	if(dep[U[i]]<dep[V[i]])	swap(U[i],V[i]),swap(Z1[i],Z2[i]);
	for(LL i=1;i<=18;++i)	for(LL j=1;j<=n;++j)	fa[i][j]=fa[i-1][fa[i-1][j]];
	for(LL i=2;i<=n;++i)	lgs[i]=lgs[i>>1]+1;
	for(LL i=1;i<n;++i)	rev[U[i]]=i,sz1[U[i]]=Z1[i],sz2[U[i]]=Z2[i];
	dfs1(1,0);
	dfs2(1,0);
	maintain(1,0);
	while(q-->0)
	{
		LL u=read(),v=read(),lca=LCA(u,v);
		if(u==v)	write(dp2[u]),puts("");
		else if(u!=lca && v!=lca)
		{
			LL disu=queKth(u,lca),disv=queKth(v,lca);
			--disu,--disv;
			LL xu=getKth(u,disu),xv=getKth(v,disv);
			LL ans=dp[u]+dp[v]-a[u]-a[v]-a[lca]+sum[u]+sum[v]-sum[lca]-sum[fa[0][lca]]+sd[u]+sd[v]-sd[xu]-sd[xv]+dp2[lca]-max(0ll,dp[xu]-Z1[rev[xu]]-Z2[rev[xu]])-max(0ll,dp[xv]-Z1[rev[xv]]-Z2[rev[xv]])-sz1[u]-sz2[v]+sz1[lca]+sz2[lca];
			write(ans),puts("");
		}
		else
		{
			LL down=dep[u]>dep[v]?u:v;
			LL disu=queKth(down,lca);
			--disu;
			LL xu=getKth(down,disu);
			LL ans=dp[down]-a[down]+sd[down]-sd[xu]+dp2[lca]-max(0ll,dp[xu]-Z1[rev[xu]]-Z2[rev[xu]]);
			if(down==u)	ans-=sz1[u]-sz1[v];
			else	ans-=sz2[v]-sz2[u];
			ans+=sum[down]-sum[fa[0][lca]];
			ans-=a[lca];
			write(ans),puts("");
		}
	}
	return 0;
}
```

---

## 作者：极寒神冰 (赞：0)

这是一种既需要离线跑得还非常慢的树状数组做法。



令$dp_i$表示一些`2-path`从$i$号点开始又以$i$号点结束的最大收益。

令$f_i$表示只能从$i$的子树走的最大收益。

$f_i$的转移相对好想，即枚举它的所有儿子，然后选或不选即可。
$$
f_u=a_u+\sum_{v\in son(u)} \max(0,f_v-2\cdot w(u,v))
$$
然后考虑计算$dp_i$，与$f$的转移不同的是它不仅可以从它的儿子转移过来，它还可以从它的父亲转移过来
$$
dp_u=a_u+\sum_{v\in Neighbour(u)} \max(0,f_v-2\cdot w(u,v))
$$
但是显然这样直接转移一条边的贡献会算多次，所以要剔除原先自己的贡献，每次往儿子方向转移时记录所有的$\max(0,f_v-2\cdot w(u,v))$丢到$dv(u,v)$中，并更新$f_u=dp_u-\max(0,f_v-2\cdot w(u,v))$。

然后考虑处理所有的询问

为了取得最大收益，一条路径$(u,v)$一定是在两点的简单路径基础上走一些其他并不是简单路径上的边然后返回取得的。

由于已经预处理出了$dp$和$dv$，假设要求出$(u,u)$的`2-path`并且不能走$(u,v_1),(u,v_2)$的最大收益，显然为$dp_u-dv(u,v_1)-dv(u,v_2)$。

所以对于每个询问$(qu,qv)$，令$l=\operatorname{lca}(qu,qv)$，可以将询问拆成$(qu,l),(qv,l)$。

考虑将所有询问离线下来，然后进行一次dfs，并且维护一个支持单点修改的数据结构（如树状数组）。

当到达点$u$时，在$dep(u)$处增加$dp_u-dv(v,fa_v)$，并且在回溯时注意删除。

而对于每一个询问$(u,l)$，显然最大利益为$[dep_l,dep_u]$的和（注意这里还要处理好$l$处的值）

当从$u$转移到$v$时，需要删除在$dep_u$处删除$dv(u,v)$的值（这里可以直接减去$w(u,v)$）

具体实现可以见代码

时间复杂度$O((n+m)\log n)$

```c++
const int N=4e5+10;
int n,m;
int a[N];
vector<pii>e[N],qs[N];
int dep[N];
ll f[N],dp[N];
int st[22][1111111],fa[N],tim,bg[N];
ll ans[N];
int Lg[1111111];
vector<ll>dv[N];
void dfs1(int u)
{
	bg[u]=++tim;
	st[0][tim]=u;
	f[u]+=a[u];
	int v;
	for(auto qwq:e[u])
	{
		v=qwq.fi;
		if(v==fa[u]) continue;
		fa[v]=u;
		dep[v]=dep[u]+1;
		dfs1(v);
		f[u]+=max(0ll,f[v]-2ll*qwq.se);
		st[0][++tim]=u;
	}
}
void dfs2(int u)
{
	dp[u]=a[u];
	int v;
	ll cur;
	for(auto qwq:e[u]) 
	{
		v=qwq.fi;
		cur=max(0ll,f[v]-2ll*qwq.se);
		dp[u]+=cur;
		dv[u].pb(cur);
	}
	cur=f[u];
	for(int i=0;i<(int)e[u].size();i++)
	{
		v=e[u][i].fi;
		if(fa[u]==v) continue;
		f[u]=dp[u]-dv[u][i];
		dfs2(v);
	}
	f[u]=cur;
}
inline int get_lp(int x,int y) {return dep[x]<dep[y]?x:y;}
inline void init_ST()
{
	R(i,2,tim+5) Lg[i]=Lg[i>>1]+1;
	for(int i=1;(1<<i)<=tim;i++) 
	{
		int w=(1<<i);
		R(j,1,tim-w+1) st[i][j]=get_lp(st[i-1][j],st[i-1][j+(w>>1)]);
	}
}
inline int get_LCA(int x,int y)
{
	x=bg[x],y=bg[y];
	if(x>y) Swap(x,y);
	int i=Lg[y-x+1],w=(1<<i);
	return get_lp(st[i][x],st[i][y-w+1]);
}
inline ll get_dv(int u) 
{
	int f=fa[u];
	int pos=(lower_bound(e[u].begin(),e[u].end(),pii(f,-1))-e[u].begin());
	if(pos>=(int)e[u].size()||e[u][pos].fi!=f) return 0;
	return dv[u][pos];
}
ll BIT[N];
inline int lowbit(int x) {return x&(-x);}
inline void modify(int pos,ll val) 
{
	for(int i=pos;i<N;i+=lowbit(i)) BIT[i]+=val;
}

inline ll query(int pos) 
{
	ll ret=0;
	for(int i=pos;i;i-=lowbit(i)) ret+=BIT[i];return ret;
}
inline ll query_SUM(int l,int r) {return query(r)-query(l-1);}
void dfs3(int u)
{
	ll vadd=dp[u]-get_dv(u);
	modify(dep[u],vadd);
	int v;
	ll cur;
	for(auto qwq:qs[u])
	{
		v=qwq.fi;
		ans[qwq.se]+=query_SUM(dep[v],dep[u])+get_dv(v);
	}
	for(int i=0;i<(int)e[u].size();i++) 
	{
		v=e[u][i].fi;
		if(fa[u]==v) continue;
		cur=dv[u][i]+e[u][i].se;
		modify(dep[u],-cur);
		dfs3(v);
		modify(dep[u],cur);
	}
	modify(dep[u],-vadd);
}
signed main()
{	
	n=read(),m=read();
	R(i,1,n) a[i]=read();
	int u,v;
	ll d;
	R(i,2,n)
	{
		u=read(),v=read(),d=read();
		e[u].pb(mkp(v,d));
		e[v].pb(mkp(u,d));
	}
	R(i,1,n) sort(e[i].begin(),e[i].end());
 	dfs1(1);
 	R(i,1,n) dep[i]++;
 	init_ST();
 	dfs2(1);
 	R(i,1,m) 
 	{
 		u=read(),v=read();
 		int L_A=get_LCA(u,v);
 		ans[i]=-dp[L_A];
 		qs[u].pb(mkp(L_A,i));
 		qs[v].pb(mkp(L_A,i));
 	}
 	dfs3(1);
 	R(i,1,m) writeln(ans[i]);

}
```


---

## 作者：leozhang (赞：0)

更清晰的阅读体验戳https://blog.csdn.net/lleozhang/article/details/83659914 这里

蜜汁树形dp...

首先分析一下：他要求一条边至多只能经过两次，那么很容易会发现：从x到y这一条路径上的所有边都只会被经过一次。（如果过去再回来那么还要过去，这样就三次了，显然不合法）

那么其他能产生贡献的部分就只有一下几个部分：x，y的子树内部，LCA（x,y）的上半部分的树以及x-y路径上的点向外延伸所形成的部分

这三部分互相独立又互相关联，所以我们设计三个dp对他们进行转移

记dp1[x]代表x的子树内所形成的的贡献，dp3[x]表示x以上的树所形成的贡献（包括x的兄弟节点）

这样就设计出了第一个和第三个状态

至于第二个，我们可以发现这个情况等价于路径上所有点向他的所有兄弟节点去跑，这样延伸出来的一种情况。

那么我们设计dp2[x]代表x的兄弟节点对x的贡献

接下来我们考虑转移：

首先，dp1非常好转移，只需向下dfs，每次回溯时只要能产生正的贡献就向上更新，同时记录每个点是否可以向上更新即可

当dp1出来了之后，dp2也就很好转移了，因为如果父节点的dp1没有利用这个节点进行更新，那么这个节点的dp2就是他父节点的dp1

如果dp1利用了这个节点进行更新，那就将dp1减掉这个节点提供的贡献赋给dp2即可

而dp3，很显然dp3要分为两部分，一部分是父节点向上，一部分是兄弟节点，兄弟节点部分就是dp2，而父节点向上那就是父节点的dp3，这也就完成了更新

这样三个dp就维护出来了

如果对概念不是特别清楚，画几个图来理解一下就行：

 那么更新完这三个，查询也就变得简单了：首先统计x-y路径上的部分，然后统计x子树内，y子树内，LCA（x，y）以上的部分，以及x-y路径上的点向外延伸的部分，而这部分可以在树链上用前缀和维护。

但是这里有个小问题：由于x和y在跳到LCA上时会跳到LCA的两个子节点上，那么对这两个子节点，我们不能加两次兄弟节点的贡献（这样就加重了），所以我们去掉一部分即可。

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#define ll long long
using namespace std;
struct Edge
{
	int next;
	int to;
	ll val;
}edge[600005];
int head[300005];
int f[300005][30];
ll dp1[300005];
ll dp2[300005];
ll dp3[300005];
ll fv[300005];
bool used1[300005];
ll dis[300005];//边权距离 
ll d[300005];//点权距离
ll v[300005];
ll s[300005];
int dep[300005]; 
int cnt=1;
int n,q;
void init()
{
	memset(head,-1,sizeof(head));
	cnt=1;
}
void add(int l,int r,ll w)
{
	edge[cnt].next=head[l];
	edge[cnt].to=r;
	edge[cnt].val=w;
	head[l]=cnt++;
}
void dfs(int x,int fx)//处理dp1 
{
	f[x][0]=fx;
	dep[x]=dep[fx]+1;
	for(int i=head[x];i!=-1;i=edge[i].next)
	{
		int to=edge[i].to;
		if(to==fx)
		{
			continue;
		}
		fv[to]=edge[i].val;
		dis[to]=dis[x]+edge[i].val;
		d[to]=d[x]+v[to];
		dfs(to,x);
		if(dp1[to]+v[to]-2*edge[i].val>=0)
		{
			dp1[x]+=dp1[to]+v[to]-2*edge[i].val;
			used1[to]=1;
		}
	}
	for(int i=head[x];i!=-1;i=edge[i].next)
	{
		int to=edge[i].to;
		if(to==fx)
		{
			continue;
		}
		if(!used1[to])
		{
			dp2[to]=dp1[x];
		}else
		{
			dp2[to]=dp1[x]-(dp1[to]+v[to]-2*edge[i].val);
		}
	}
}
void redfs(int x,int fx)
{
	s[x]+=dp2[x];
	for(int i=head[x];i!=-1;i=edge[i].next)
	{
		int to=edge[i].to;
		if(to==fx)
		{
			continue;
		}
		dp3[to]=max((ll)0,dp3[x]+v[x]-2*edge[i].val+dp2[to]);
		s[to]+=s[x];
		redfs(to,x);
	}
}
void getf()
{
	for(int i=1;i<=25;i++)
	{
		for(int j=1;j<=n;j++)
		{
			f[j][i]=f[f[j][i-1]][i-1];
		}
	}
}
int LCA(int x,int y)
{
	if(dep[x]>dep[y])
	{
		swap(x,y);
	}
	for(int i=25;i>=0;i--)
	{
		if(dep[f[y][i]]>=dep[x])
		{
			y=f[y][i];
		}
	}
	if(x==y)
	{
		return x;
	}
	int ret;
	for(int i=25;i>=0;i--)
	{
		if(f[x][i]!=f[y][i])
		{
			x=f[x][i];
			y=f[y][i];
		}else
		{
			ret=f[x][i];
		}
	}
	return ret;
}
ll cal(int x,int y)
{
	ll ret=0;
	if(dep[x]>dep[y])
	{
		swap(x,y);
	}
	int f1=LCA(x,y);
	if(f1!=1)
	{
		ret+=d[x]+d[y]-d[f1]-d[f[f1][0]];
		ret-=dis[x]+dis[y]-2*dis[f1];
	}else
	{
		ret+=d[x]+d[y]-d[f1];
		ret-=dis[x]+dis[y]-dis[f1];
	}
	if(x==f1)
	{
		ret+=dp1[y];
		ret+=dp3[x];
		ret+=s[y];
		ret-=s[x];
	}else
	{
		ret+=dp1[x];
		ret+=dp1[y];
		ret+=dp3[f1];
		int ff1=x,ff2=y;
		for(int i=25;i>=0;i--)
		{
			if(dep[f[ff1][i]]>dep[f1])
			{
				ff1=f[ff1][i];
			}
			if(dep[f[ff2][i]]>dep[f1])
			{
				ff2=f[ff2][i];
			}
		}
		ret+=s[x]-s[ff1];
		ret+=s[y]-s[ff2];
		ret+=dp2[ff1];
		if(used1[ff2])
		{
			ret-=dp1[ff2]+v[ff2]-2*fv[ff2];
		}
	}
	return ret;
}
inline int read()
{
	int f=1,x=0;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main()
{
	n=read(),q=read();
	init();
	for(int i=1;i<=n;i++)
	{
		v[i]=(ll)read();
	}
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read(),z=read();
		add(x,y,(ll)z);
		add(y,x,(ll)z);
	}
	d[1]=v[1];
	dfs(1,1);
	getf();
	redfs(1,1);
	for(int i=1;i<=q;i++)
	{
		int x=read(),y=read();
		printf("%lld\n",cal(x,y));
	}
	return 0;
}

```


---

