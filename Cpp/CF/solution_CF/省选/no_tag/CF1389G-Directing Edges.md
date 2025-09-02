# Directing Edges

## 题目描述

给你一张 $n$ 个点 $m$ 条边的无向连通图。图上还有 $k$ 个特殊点。

你需要给每一条边定向，也可以保留该边无向。如果你保留了第 $i$ 条边无向，你需要支付 $w_i$ 个硬币，如果你给它定向，则无需支付任何费用。

我们称一个点是 *饱和的*，当且仅当所有特殊点通过图上的边，都可以到达这个点（如果一条边是无向的，则这条边可以双向通行）。在你给图定向完成后（可能保留一些边无向），对于每个饱和的点 $i$，你都能获得 $c_i$ 个硬币的收益。故而，你的总利润为 $\sum\limits_{i \in S} c_i - \sum\limits_{j \in U} w_j$，其中 $S$ 表示饱和的点集，$U$ 表示你选择保留无向的边集。

对于每个顶点 $i$，在要求强制选取 $i$ 为饱和点的情况下，计算你可能收获的最大利润。

## 样例 #1

### 输入

```
3 2 2
1 3
11 1 5
10 10
1 2
2 3```

### 输出

```
11 2 5```

## 样例 #2

### 输入

```
4 4 4
1 2 3 4
1 5 7 8
100 100 100 100
1 2
2 3
3 4
1 4```

### 输出

```
21 21 21 21```

# 题解

## 作者：Tweetuzki (赞：8)

> 给出一张 $n$ 个点 $m$ 条边的无向图，有 $k$ 个关键点。需要给所有无向边定向，如果第 $i$ 条边保留双向，要花费 $w_i$ 的代价。我们称定向后的图上一个点是饱和的，当且仅当所有关键点都能到达它。此时这个点能够有 $c_i$ 的收益。请对于每个 $i = 1, 2, \ldots, n$ 回答，强制选择 $i$ 号点为饱和点时，收益减代价的最大值。
> 
> $n, m \le 3 \times 10 ^ 5$。

这题就是把好多东西套在一块了，抢在比赛结束前半分钟 Rush 完了。

首先，对于一个点双连通分量，可以通过定向变成一个强连通分量，即两两可互达。所以我们可以把点双缩点，问题转化为树上问题。

接着，随便以一个关键点为根，把树变成有根树。

注意到对于内部没有关键点的子树，可以从离它最近的关键点一直走有向边定向过来。因此这些点的到达状态和离它们最近的关键点是相同的，可以把这些点缩起来。于是问题转化为叶子全部为关键点的问题。

然后，发现在所有叶子都是关键点的情况下，饱和点一定形成一个树上的连通块，且连通块内的边都是双向边，连通块外的边都定向为了指向这个连通块的有向边。

因此，我们实际要求的就是树上最优的一个连通块，使得连通块内点权之和减去边权之和最大。这个可以通过简单的树上 DP 解决。

准确的来说，$f_u$ 表示以点 $u$ 为根的子树中，包含点 $u$ 的连通块的权值最大值。转移枚举一个子树 $v$，设连接 $u, v$ 的边权为 $w$，有转移式 $f_u = \sum\limits_{v} \max(f_v - w, 0) + weight_u$，其中 $weight_u$ 为缩点后 $u$ 点的权值。

最后，要对每个点求这个答案，在树上做一遍换根 DP，每次存下根的答案即可。

时间复杂度 $\mathcal{O}(n)$。

代码：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int MaxN = 300000, MaxM = 300000;

int N, M, K, V, Rt;
bool Special[MaxN + 5];
int C[MaxN + 5];
struct edge_t { int u, v, w; } E[MaxM + 5];
std::vector<int> Gr[MaxN + 5];

template <typename Int>
inline void tense(Int &x, Int y) { if (y > x) x = y; }
template <typename Int>
inline void relax(Int &x, Int y) { if (y < x) x = y; }

void init() {
  scanf("%d %d %d", &N, &M, &K);
  for (int i = 1; i <= K; ++i) {
    int u;
    scanf("%d", &u);
    Special[u] = true;
  }
  for (int i = 1; i <= N; ++i) scanf("%d", &C[i]);
  for (int i = 1; i <= M; ++i) scanf("%d", &E[i].w);
  for (int i = 1; i <= M; ++i) {
    scanf("%d %d", &E[i].u, &E[i].v);
    Gr[E[i].u].push_back(E[i].v);
    Gr[E[i].v].push_back(E[i].u);
  }
}

int low[MaxN + 5], dfn[MaxN + 5], dfc;
int stk[MaxN + 5], tp;
int bel[MaxN + 5];

long long A[MaxN + 5], B[MaxN + 5];
bool O[MaxN + 5];
int SumO[MaxN + 5];
std::vector< std::pair<int, int> > Tr[MaxN + 5];

void tarjan(int u, int f) {
  low[u] = dfn[u] = ++dfc;
  stk[++tp] = u;
  for (int v : Gr[u]) {
    if (v == f) continue;
    if (dfn[v] == 0) {
      tarjan(v, u);
      relax(low[u], low[v]);
    } else relax(low[u], dfn[v]);
  }
  if (low[u] == dfn[u]) {
    V++;
    for (;;) {
      int v = stk[tp--];
      bel[v] = V;
      A[V] += C[v];
      O[V] |= Special[v];
      if (v == u) break;
    }
  }
}

int Par[MaxN + 5];
int find(int x) { return x == Par[x] ? x : Par[x] = find(Par[x]); }

void dfs1(int u, int f) {
  SumO[u] = O[u];
  B[u] = A[u];
  for (auto e : Tr[u]) {
    int v = e.first;
    if (v == f) continue;
    dfs1(v, u);
    SumO[u] += SumO[v];
    if (SumO[v] == 0) {
      Par[v] = u;
      B[u] += B[v];
    }
  }
}

void getBcc() {
  tarjan(1, 0);
  for (int i = 1; i <= M; ++i) {
    int u = E[i].u, v = E[i].v, w = E[i].w;
    u = bel[u], v = bel[v];
    if (u != v) {
      Tr[u].emplace_back(v, w);
      Tr[v].emplace_back(u, w);
    }
  }
  Rt = 0;
  for (int i = 1; i <= V; ++i)
    if (O[i] == true) Rt = i;
  for (int i = 1; i <= V; ++i) Par[i] = i;
  dfs1(Rt, 0);
}

long long F[MaxN + 5];
long long Ans[MaxN + 5];

void dfs2(int u, int f) {
  F[u] = B[u];
  for (auto e : Tr[u]) {
    int v = e.first, w = e.second;
    if (v == f || SumO[v] == 0) continue;
    dfs2(v, u);
    if (F[v] - w > 0) F[u] += F[v] - w;
  }
}

void dfs3(int u, int f) {
  Ans[u] = F[u];
  for (auto e : Tr[u]) {
    int v = e.first, w = e.second;
    if (v == f || SumO[v] == 0) continue;
    F[u] -= std::max(0LL, F[v] - w);
    F[v] += std::max(0LL, F[u] - w);
    dfs3(v, u);
    F[v] -= std::max(0LL, F[u] - w);
    F[u] += std::max(0LL, F[v] - w);
  }
}

void solve() {
  getBcc();
  dfs2(Rt, 0);
  dfs3(Rt, 0);
  for (int i = 1; i <= N; ++i) {
    int id = find(bel[i]);
    printf("%lld%c", Ans[id], " \n"[i == N]);
  }
}

int main() {
  init();
  solve();
  return 0;
}
```

---

## 作者：huayucaiji (赞：6)

~~有点意思的一道题~~

首先推荐阅读一下[DP之神UM的一篇关于换根DP的blog](https://sflsrick.blog.luogu.org/note-how-to-change-root)。阅读完后再来看本题解效果更佳。

好，我们切回正题。首先我们来简化条件。如果现在给我们的是一颗有 $n$ 个点的树。让我们来做这个问题，我们该怎么做呢？比如我们考虑下图这棵树：

![G1](https://cdn.luogu.com.cn/upload/image_hosting/o4fti5lv.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

我们容易想到我们要做的是 DP。我们定义：$f_u$ 表示以 $u$ 为根节点的子树里，保证 $u$ 是饱和的情况下，我们所能获得的最大收益为多少。假设我们已经知道了所有 $u$ 的子节点的值，即 $f_{v_1},f_{v_2},f_{v_3}....f_{v_d}$ 的值（其中 $v_1,v_2....v_d$ 为 $u$ 的子节点）那么我们现在需要考虑的就是连接 $u,v_i$ 的边的方向到底是什么了。现在我们就来考虑一下 $3$ 对 $f_1$ 的贡献。

如果我们的特殊点是 $3,9,11$，现在我们考虑蓝色的边的方向。我们发现所有的特殊点都在以 $3$ 为根的子树中。为了让 $1$ 饱和，那么蓝色的边的方向就应该是由 $3$ 到 $1$，从而让所有的特殊点都指向 $1$，同时 $f_1$ 也得到了 $f_3$ 的全部收益。**这种情况只有在所有特殊点都在一颗子树中时成立，我们可以决定这课子树到其父节点这条边的方向。** 如下图：

![G2](https://cdn.luogu.com.cn/upload/image_hosting/wkuxuitk.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

如果我们的特殊点是 $1,2,6,8$，现在我们考虑蓝色的边的方向。我们发现所有的特殊点都不在以 $3$ 为根的子树中。为了获得 $f_3$ 的收益，蓝色的边的方向就应该是由 $1$ 到 $3$。**这种情况只有在所有特殊点都在一颗子树外时成立，我们可以决定这课子树到其父节点这条边的方向。** 如下图：

![G3](https://cdn.luogu.com.cn/upload/image_hosting/nhip163j.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

还有一种情况就是在某一子树外和子树中都有特殊点，那么为了获得 $f_3$ 的收益，同时让 $1$ 饱和，我们必须要让这条边成为双向边。但如果这条边成为双向边的代价 $w_i>f_3$。我们宁愿抛弃 $f_3$。因为此时它带来的增益是负的。

因此我们总结一下：对于一个节点 $u$，已知他的儿子 $f_{v_1},f_{v_2},f_{v_3}....f_{v_d}$ 的值。我们令连接 $u,v_i$ 的边编号为 $j$，$size_u$ 为以 $u$ 为根节点的子树中有特殊点个数，那么我们有：

$$f_i=\sum\limits_{i=1}^d (f_{v_i}+calc(v_i))$$

$$clac(v)=\max \begin{cases}f_v&size_{v}=0,size_v=k\\f_v-e_j&f_v>e_j\\0&f_v\leq e_j\end{cases}$$

显然，我们想要算 $u$ 一定为饱和点的时候最大收益就是 $u$ 为根的时候 $f_u$ 的值。但是我们要把每个点的答案都算出来，时间复杂度就上升到了 $O(n^2)$。实在太大，无法接受。所以我们要采用换根DP的方式来优化复杂度。我们再来定义 $dp_u$ 为满足 $u$ 一定饱和的情况下，在以 $u$ 的根节点的**子树外**的最大收益。我们先以 $1$ 为根节点做一遍DFS求出 $f$ 数组的值。接着再做一遍DFS，算出 $dp$ 数组。具体的方法可以参照UM的blog，读者自己思考完成。实在不会可以看看代码。最后 $ans_u=f_u+dp_u-c_u$。因为 $dp_u,f_u$ 中都包含 $c_u$，也就是这个节点本身的收益。

提示一下初值：$dp_u=f_u=c_u$ 哦~

但是我们上面讨论的是树的情况下。但如果是一张图呢？我们就要来进行一下问题的转化。

我们一般把一个无向图转化为树的方法就是双联通分量缩点。我们来证明一下一个缩完点的双连通分量等同于树上的一个点。首先，我们知道一个双联通分量内部的边有向化，一定有至少一种方案使其成为强连通分量。所以这个双联通分量内部的点，要么全部饱和，要么全不饱和，其其内部的遍全有向化，代价为 $0$。因此，我们只需要缩个点，在进行换根DP即可解决此题。

代码至少150+，大家自便（不压行）~

```cpp
//Don't act like a loser.
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=3e5+10;

int n=0,m=0,k=0,h[maxn]={},cnt=0,low[maxn]={},dfn[maxn]={},col[maxn]={},num[maxn]={},size[maxn]={},d[maxn]={},tot=0;
int col_cnt=0,time_cnt=0,w[maxn]={},c[maxn]={},val[maxn]={},spe[maxn]={},f[maxn]={},dp[maxn]={};
vector<pair<int,int> > g[maxn];
bool vis[maxn]={},spec[maxn];

struct edge {
	int v,w,next;
}e[maxn<<1];

void addedge(int u,int v,int w) {
	e[++cnt].v=v;
	e[cnt].w=w;
	e[cnt].next=h[u];
	h[u]=cnt; 
}
void insert(int u,int v,int w) {
	addedge(u,v,w);
	addedge(v,u,w);
}

void dfs1(int u,int fa) {
	vis[u]=1;
	low[u]=dfn[u]=++time_cnt;
	int sz=g[u].size();
	for(int i=0;i<sz;i++) {
		int v=g[u][i].first;
		
		if(v!=fa) {
			if(!vis[v]) {
				dfs1(v,u);
				low[u]=min(low[u],low[v]);
			}
			else {
				low[u]=min(low[u],dfn[v]);
			}
		}
	}
	d[++tot]=u;
}

void dfs2(int u,int fa) {
	col[u]=col_cnt;
	spe[col_cnt]+=spec[u]? 1:0;
	val[col_cnt]+=c[u];
	
	int sz=g[u].size();
	for(int i=0;i<sz;i++) {
		int v=g[u][i].first;
		
		if(dfn[u]>dfn[v]||low[v]>dfn[u]) {//判断是否是桥。
			continue;
		}
		if(!col[v]) {
			dfs2(v,u);
		}
	}
}

void tarjan() {
	dfs1(1,0);
	
	for(int i=n;i;i--) {//反向循环
		if(!col[d[i]]) {
			col_cnt++;
			dfs2(d[i],0);
		}
	}
	
	for(int u=1;u<=n;u++) {//缩点后的建图
		int sz=g[u].size();
		
		for(int i=0;i<sz;i++) {
			int v=g[u][i].first;
			
			if(u<v&&col[u]!=col[v]) {//注意一条边不要建两次~
				insert(col[u],col[v],w[g[u][i].second]);
			}
		}
	}
}

void dfs3(int u,int fa) {//以1为根的DFS
	f[u]=val[u];
	size[u]=spe[u];
	for(int i=h[u];i;i=e[i].next) {
		int v=e[i].v;
		
		if(v!=fa) {
			dfs3(v,u);
			size[u]+=size[v];
			
			if(size[v]==0||size[v]==k) {
				f[u]+=f[v];
			}
			else {
				f[u]+=max(0LL,f[v]-e[i].w);
			}
		}
	}
}

void dfs4(int u,int fa) {//换根的部分
	int sum=0;
	
	for(int i=h[u];i;i=e[i].next) {
		int v=e[i].v;
		
		if(v!=fa) {
			if(size[v]==k||size[v]==0) {//注意分类
				sum+=f[v];
			}
			else {
				sum+=max(0LL,f[v]-e[i].w);
			}
		}
	}
	
	for(int i=h[u];i;i=e[i].next) {
		int v=e[i].v;
		
		if(v!=fa) {
			dp[v]=val[v];
			if(size[v]==0||size[v]==k) {//分类，由上而下更新dp数组
				dp[v]+=dp[u]+sum-f[v];
			}
			else {
				dp[v]+=max(0LL,dp[u]+sum-max(0LL,f[v]-e[i].w)-e[i].w);
			}
			dfs4(v,u);
		}
	}
}

signed main() {
	n=read();
	m=read();
	k=read();
	
	for(int i=1;i<=k;i++) {
		spec[read()]=1;
	}
	for(int i=1;i<=n;i++) {
		c[i]=read();
	}
	for(int i=1;i<=m;i++) {
		w[i]=read();
	}
	for(int i=1;i<=m;i++) {
		int a=read(),b=read();
		g[a].push_back(make_pair(b,i));
		g[b].push_back(make_pair(a,i));//第一次建图
	} 
	
	tarjan();
	
	dfs3(1,0);
	dp[1]=val[1];
	dfs4(1,0);
	
	for(int i=1;i<=n;i++) {
		printf("%lld ",dp[col[i]]+f[col[i]]-val[col[i]]);//注意-val[i]
	}
	
	return 0;
}
```

---

## 作者：dynamicpair (赞：5)

这篇题解主要针对看了 $DP$ 方程式觉得好像懂了却觉得哪里不对劲的同学

第一步我们可以考虑缩点，然后树形 $DP$ .......

嗯？为什么定义为“： $ fu $ 表示以 $u$ 为根节点的子树里，保证 $u$ 是饱和的情况下，我们所能获得的最大收益为多少”？？嗯？那我根节点怎么办，其他节点怎么办？？我现在只知道我当前子树的情况啊？？？我怎么知道外面的特殊点怎么让我满足呢？？？嗯？？？

~~然后懵乐~~

很明显我们搞错了树形 $DP$ 的某个本质东西，但是我们讲不清楚

于是我们换一种方式思考，我们先抛开树形 $DP$ 不谈。

现在我们先把无根树变有根树，我们考虑怎么样**只让根满足条件**。

满足根节点饱和的方式有很多种，其中**最不优最暴力**的方法就是所有边从下向上连，不耗费一分钱也赚不了多少钱，但是我们可以基于这个方案去优化。

我们先想想为什么要连从上向下的边，我们突然意识到连接从上向下的边 $u \longrightarrow v$  当且仅当**以 $v$ 为根的子树内是没有特殊点的**，这是因为，如果从下向上连接, $ v $ 节点和其子树内肯定是不会有贡献的，但是如果从上向下连接, $ v $ 及其子树内的节点还存在贡献的可能！

我们接下来思考连双向边的意义是什么，可以发现既然根节点一定能满足，我们想要获取其他的点的贡献，但是我们想要获取贡献的点的子树内是有特殊点的，我们不能直接从根节点连向他（这样根节点得不到特殊点了）所以只能连双向边了。

基于这个，我们进一步观察发现，所有连双向边的点一定形成了一个连通块且其中包含根节点，因为如果有两个连通块，连接这两个连通块的边一定是单向边，但是这些边你是没办法定向的，下面我们来证明一下：

#### 情况$ 1$ ：$ A $与 $ B $ 不连通

![](https://cdn.luogu.com.cn/upload/image_hosting/scajvi0n.png)

这种情况显然不会发生，如图：如果有一个特殊点指向 $A$ ，而 $A$ 与 $B$ 不连通，那么由于树上两点路径唯一，这个特殊点到不了 $B$ ，那么就不满足定义了；而假如没有特殊点指向 $A$ ，考虑我连双向边的意义，那我干吗不把 $A$ 里的边全部定为单向边呢？

#### 情况2：$ A $ 能到达 $ B $  （$ B $ 能到达 $ A $ 同理）

这里就不画图了，很容易根据情况1进行联想，首先肯定是没有特殊点指向 $B$ 的（因为 $A$ 不满足）那么说明所有特殊点指向了 $A$ ，那我为什么不把 $B$ 全部定为单向边呢？（参考上面讲从上向下指的边）

那么我们证明了所有双向边连接的点一定是一个联通块，而且连接从上向下的边 $u \longrightarrow v$ 当且仅当**以V为根的子树内是没有特殊点的**，我们就可以开始 $DP$ 了

这里 $f_v$ 的定义我更加倾向于：假如根节点饱和，**从根节点能达到点$v$** ，我能从点 $v$ 及其子树获得的贡献，但是如果在最终方案中我从根节点到不了点 $v$ ，那意味着我会在从 $v$ 到根的某个地方向上连接，到那时候我所有 $f_v$ 都会没用，但是这是之后要考虑的，准备工作还是要做好，万一选上了呢？

~~所以我认为树形 $DP$ 的本质也就在这里~~，

假如现在我要定 $U$ 连向 $V$ 的边的方向，那么下面是当时发生的两种可能的故事：

> $ U $ 节点：你好点 $ V $ ，我最终还是被根节点选中了，根节点有一条路径连向了我，我的贡献最终要给点 $ U $ 了，我好好考虑了一下，我觉得你和你子树的贡献能助我一臂之力，你愿意成为我的力量吗？

> $ V $节点：好的！既然你选择了我，说明你充分的信任我！那么我和我子树的情况你就不用操心了！你只用加上我给你的值 $f_v$ 就行了！

于是 $f_u$ 加上了 $f_v$

>  $ U $ 节点：你好点 $ V $ ，我最终还是被根节点选中了，根节点有一条路径连向了我，我的贡献最终要给点 $ U $ 了，我好好考虑了一下，我觉得你是个废物，我加了你的贡献后反而更劣了，你可以滚吗？

> $ V $ 节点：可是我的 $f_v$ 全部都是为你准备的啊。。。。

> $ U $ 节点：少废话快滚！

> $ V $ 节点：好好我滚我滚。。。

~~于是 $ f_u $ 没有加上 $ f_v $~~

~~结果$Fu$也在后面被拒绝掉了~~

> 做人留一线，日后好相见

鄙人觉得这其实才是树形 $DP$ 的本质，只考虑当前子树情况，以后你选不选我是你的事，选我，我就贡献我的 $f$ 值，你不选我，也没关系，不加我的贡献就行。而上面给出的 $DP$ 方程的解释也很好地体现了这一点。

那为什么在很多树形DP题目中没有体会到这一点呢？那是因为那些树形 $DP$ 的题目，没有明显的 **选 $U$ 的前提下才能选 $V$** 这个条件，但是仔细想想其实是有的，$ f_u $ 的值是包含着 $f_v$ 的，如果不选 $f_u$ 的话我怎么可能会去选 $f_v$ 呢？

状态转移方程这里就不给出了，其他的两篇题解讲得很详细很详细了。

最后是一点点自己的思考，其实我们会发现，这道题的本质问题是：
> 给定一棵树，根节点必须选择，我们还要选择一些节点使得这些节点和根节点构成一个连通块，每个点有一些价值，求最后价值最大的选择方案。

而对于这一道题的解法，就是对于这一类题目的一个通用解法

这里再提供一道题，个人认为可以加深一下理解：

[HDU6643](http://acm.hdu.edu.cn/showproblem.php?pid=6643)

---

