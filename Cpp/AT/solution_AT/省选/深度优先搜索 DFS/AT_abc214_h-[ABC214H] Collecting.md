# [ABC214H] Collecting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc214/tasks/abc214_h

$ N $ 頂点 $ M $ 辺の有向グラフがあります。  
 頂点は $ 1,\ \dots,\ N $ と番号付けられており、$ i\ \,\ (1\ \leq\ i\ \leq\ M) $ 番目の辺は頂点 $ A_i $ から頂点 $ B_i $ に向けて張られています。

はじめ、頂点 $ i\ \,\ (\ 1\ \leq\ i\ \leq\ N) $ には $ X_i $ 個の落とし物があります。これらの落とし物を $ K $ 人で拾うことになりました。

$ K $ 人は $ 1 $ 人ずつグラフ上を移動します。各々は次のような行動をとります。

- 頂点 $ 1 $ から出発し、辺をたどって移動することを任意の有限回繰り返す。訪れた各頂点（頂点 $ 1 $ も含む）について、落とし物がまだ拾われていなければ、全て拾う。

合計で最大何個の落とし物を拾うことができるか求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ K\ \leq\ 10 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- $ A_i\ \neq\ B_i $
- $ i\ \neq\ j $ ならば、$ A_i\ \neq\ A_j $ または $ B_i\ \neq\ B_j $
- $ 1\ \leq\ X_i\ \leq\ 10^9 $
- 入力は全て整数である。

### Sample Explanation 1

$ 2 $ 人がそれぞれ次のように行動することで、$ 18 $ 個の落とし物を拾うことができます。 - $ 1 $ 人目は、頂点 $ 1\ \rightarrow\ 2\ \rightarrow\ 3\ \rightarrow\ 2 $ の順に移動し、頂点 $ 1,\ 2,\ 3 $ にある落とし物を拾う。 - $ 2 $ 人目は、頂点 $ 1\ \rightarrow\ 5 $ の順に移動し、頂点 $ 5 $ にある落とし物を拾う。 $ 19 $ 個以上の落とし物を拾うことはできないので、$ 18 $ を出力します。

## 样例 #1

### 输入

```
5 5 2
1 2
2 3
3 2
1 4
1 5
1 4 5 2 8```

### 输出

```
18```

## 样例 #2

### 输入

```
3 1 10
2 3
1 100 100```

### 输出

```
1```

# 题解

## 作者：lzyqwq (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc214_h)。

神仙图论题。

# $\texttt{Description}$
- 一张 $n$ 个点 $m$ 条边的有向图，第 $i$ 个点上有 $x_i$ 个物品，有 $k$ 个人在点 $1$。每个人依次从起点遍历整个图，拿走所到节点的所有物品（只能拿一次，即第二个人经过时物品已经消失）。问最多能拿到多少物品。

- $1\le n,m\le 2\times 10^5$，$1\le k\le 10$。

# $\texttt{Solution}$

注意到一个强联通分量内的物品可以一次性全部拿走，所以先 tarjan 缩点。

接下来图就变成 DAG 了，问题可以看成是路径覆盖并使权值最大的问题，考虑网络流建图，先处理出每个强联通分量内的点权和 $val_i$，计 $num$ 为强连通分量总数，点 $i$ 所属的强联通分量编号为 $scc_i$。由于 tarjan 得到的是逆拓扑序，因此第 $i$ 个强连通分量在拓扑排序中的顺序就是 $num-i+1$（这点太毒瘤了，据说在 DAG 上再做一遍拓扑排序会 `TLE`）。

这里可以考虑先把 DAG 上的重边去了。

先考虑朴素建图。

为了限制流量，先将每个点 $u$ 拆为 $in_u$ 和 $out_u$。

记源点为 $S$，汇点为 $T$，$(u,v,w,c)$ 为从点 $u$ 到点 $v$ 容量为 $w$，费用为 $c$ 的有向边，这里的点都是缩点后的强连通分量拆点后的点。

- 对于 DAG 上一条边 $(i,j)$，建 $(out_i,in_j,k,0)$，表示所有人都可以经过这条边。

- 对于同一个点 $i$，建 $(in_i,out_i,1,val_i)$ 和 $(in_i,out_i,k,0)$，分别表示只可以取一次物品和可以经过任意次。

- 每个点 $i$ 建 $(out_i,T,k,0)$，表示所有人都可以走到这个点然后停下来。

- 对于起点，建 $(S,in_{scc_1},k,0)$，表示 $k$ 个人都从起点（所在的强连通分量）出发。

然后边权全部取相反数跑最小费用最大流，再把答案取反即为答案。

然而这样时间复杂度为 $\mathcal{O(knm)}$，由于 $n,m$ 同阶，空间复杂度为 $\mathcal{O(n)}$，不能接受。

所以可以反过来想，由于缩点后原图是个 DAG，所以走完一条边之后是不能回去的。一般来讲（以下 $i,j$ 均是强连通分量编号），从 $i$ 走到 $j$，必须满足 $i<j$（后继的拓扑序比自己更大），所以走过去之后就不能再经过 $i+1\sim j-1$ 了。因此走这条边就损失了 $\sum\limits_{k=i+1}^{j-1}val_k$ 的物品。因此可以考虑用总价值减去损失。先维护 $val$ 的前缀和数组 $sum$，然后这样建图（同样，出现描述点的字母均表示强连通分量）：

-  对于缩点后 DAG 上一条边 $(i,j)$，建 $(out_i,in_j,k,sum_{j-1}-sum_i)$，表示所有人都可以经过这条边，并且损失 $i+1\sim {j-1}$ 的物品（因为回不去了，下面同理）。

- 对于同一个点 $i$，建 $(in_i,out_i,1,0)$ 和 $(in_i,out_i,k,val_i)$，分别表示只可以取一次物品（不损失）和可以经过任意次（损失）。

- 每个点 $i$ 建 $(out_i,T,k,sum_{num}-sum_i)$，表示所有人都可以走到这个点然后停下来，损失后面没经过的 $i+1\sim n$ 的物品。

- 对于起点，建 $(S,in_{scc_1},k,sum_{scc_1-1})$，表示 $k$ 个人都从起点 $1$（所在的强连通分量）出发，损失 $1\sim scc_1-1$ 的物品。

然后跑最小费用最大流就是 $k$ 个人的最小损失，用 $k$ 个人的总和减去这个最小损失就是最大价值。所以我们要求的答案就是 $sum_{num}\times k-\operatorname{mincost}$。

这样的建图巧妙之处在于负权边较少。由于 Dijkstra 不能跑负权边的原因是负权边会使一个点重复被取出更新其它点，而算法中只让其更新了一次。如果让其重复进队取出更新其它点，复杂度不能保证。但是这里负权边较少，说明重复进队更新的次数会少，因此这里使用类似一个点可重复更新其他节点 Dijkstra 会大致保证原版 Dijkstra 优秀的复杂度。

这样一来，时间复杂度变成了 $\mathcal{O(km\log_2n)}$（会带一个较大的常数），由于 $n,m$ 同阶，空间复杂度为 $\mathcal{O(n)}$，可以接受。

# $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 1000005
int n,m,k,dfn[N],low[N],cnt=1,tot,id,scc[N],val[N],num,T,hd[N],dis[N],f[N],la[N],ans,sum[N];
vector<int>g[N];
stack<int>stk;
map<pair<int,int>,bool>mp;
bool is[N],vis[N];
struct edge{
	int v,w,c,ne;
}e[N*2];
struct node{
    int v,w;
    bool operator<(const node &b)const{
        return w>b.w;
    }
};
priority_queue<node>q;
void add(int u,int v,int w,int c){
	e[++cnt]={v,w,c,hd[u]};
	hd[u]=cnt;
	e[++cnt]={u,0,-c,hd[v]};
	hd[v]=cnt;
}
void tarjan(int x){
	dfn[x]=low[x]=++id;
	stk.push(x);
	is[x]=1;
	for(int i:g[x]){
		if(!dfn[i]){
			tarjan(i);
			low[x]=min(low[x],low[i]);
		}else if(is[i]){
			low[x]=min(low[x],dfn[i]);
		}
	}
	if(dfn[x]==low[x]){
		++num;
		while(1){
			int u=stk.top();
			stk.pop();
			scc[u]=num;
			is[u]=0;
			if(u==x){
				break;
			}
		}
	}
}
bool spfa(){
	for(int i=0;i<=T;++i){
		dis[i]=1e18;
	}
	f[0]=1e18;
	q.push({0,dis[0]=0});
	while(q.size()){
		node t=q.top();
		q.pop();
        if(t.w^dis[t.v]){//要使最终的最短路更新后继节点，dis表示当前的最短路，最终最短路肯定是某个“当前”的最短路，所以考虑是当前最短路就去更新后继，这使得一个点多次更新后继，带来大常数
            continue;
        }
		for(int i=hd[t.v];i;i=e[i].ne){
			if(e[i].w&&dis[e[i].v]>dis[t.v]+e[i].c){
				q.push({e[la[e[i].v]=i].v,dis[e[i].v]=dis[t.v]+e[i].c});
				f[e[i].v]=min(f[t.v],e[i].w);
			}
		}
	}
	return dis[T]<1e18;
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1,u,v;i<=m;++i){
		scanf("%lld%lld",&u,&v);
		g[u].push_back(v);
	}
	for(int i=1;i<=n;++i){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=1;i<=n;++i){
		if(!vis[i]){
            scc[i]=num-scc[i]+1;
            vis[i]=1;
        }
	}
	for(int i=1,x;i<=n;++i){
		scanf("%lld",&x);
		val[scc[i]]+=x;
	}
    for(int i=1,x;i<=n;++i){
		sum[i]=sum[i-1]+val[i];
	}
	T=num*2+1;
	for(int i=1;i<=n;++i){
		for(int j:g[i]){
			if(scc[i]^scc[j]&&!mp[make_pair(scc[i],scc[j])]){
				add(scc[i]+num,scc[j],k,sum[scc[j]-1]-sum[scc[i]]);
				mp[make_pair(scc[i],scc[j])]=1;
			}
		}
	}
	for(int i=1;i<=num;++i){
		add(i,i+num,1,0);
		add(i,i+num,k,val[i]);
		add(i+num,T,k,sum[num]-sum[i]);
		if(i==scc[1]){
			add(0,i,k,sum[i-1]);
		}
	}
    ans=k*sum[num];
	while(spfa()){
		ans-=dis[T]*f[T];
		for(int j=T;j;j=e[la[j]^1].v){
			e[la[j]].w-=f[T];
			e[la[j]^1].w+=f[T];
		}
	}
	printf("%lld",ans);
}
```

---

## 作者：EuphoricStar (赞：6)

好毒瘤啊……

首先考虑一个环内的 $a_i$ 到了就一定能拿完，所以肯定是要先缩点的。设 $s_i$ 为点 $i$ 所在强联通分量编号（按拓扑序编号），$b_i$ 为第 $i$ 个分量的点权和，$t$ 为分量个数。

考虑最大费用最大流。对每个点拆成入点和出点 $u, u'$。下面用 $(u, v, x, y)$ 表示 $u \to v$，容量为 $x$，单位流量费用为 $y$ 的边。考虑这样建图：

- $\forall u \in [1, t], (u, u', 1, b_u), (u, u', +\infty, 0)$，表示一个点只有第一个走的人能获得 $b_u$ 的权值。

- $\forall (u, v) \in E, (s_u', s_v, +\infty, 0)$，表示边不产生贡献。

- $(S, s_1, K, 0)$，表示所有人都要从 $s_1$ 出发；

- $\forall u \in [1, t], (u', T, +\infty, 0)$，表示任何点都能作为终点。

最后从 $S$ 到 $T$ 的最大流的最大费用。求最大费用最大流，可以把费用全部乘上 $-1$，做最小费用最大流。

但是这样是 $O(Knm)$ 的。

因为最大流很小，所以如果我们能把费用都变成非负的，就可以用 Primal-Dual 原始对偶算法，把时间复杂度优化到 $O(Km \log n)$ 了。因此考虑换一种建图方式，与其计算能得到的权值，不如计算损失了多少权值。

考虑因为缩点之后是一个 DAG，所以走一条边 $x \to y$ 意味着 $[x + 1, y - 1]$ 都走不到了。基于此尝试以下连边：

- $\forall u \in [1, t], (u, u', 1, 0), (u, u', +\infty, b_u)$。

- $\forall (u, v) \in E, (s_u', s_v, +\infty, \sum\limits_{i = u + 1}^{v - 1} b_i)$。

- $(S, s_1, K, \sum\limits_{i = 1}^{s_1 - 1} b_i)$。

- $\forall u \in [1, t], (u', T, +\infty, \sum\limits_{i = u + 1}^{t})$。

最后答案是 $(K \times \sum\limits_{i = 1}^t b_i) - \text{mincost}$。

这里简单讲一下 Primal-Dual 原始对偶算法。其思想是通过设置一个每个点的势能 $h_i$，把每条边的费用 $w$ 变成 $w + h_u - h_v$，使得它 $\ge 0$，这样就能跑 Dijkstra 找出增广路。每个点的初始势能是它到 $S$ 的最短路，每次增广，$h_u \gets h_u + d_u$，这样能保证费用非负。如果原图所有边费用都是非负的，第一次求 $h_i$ 也可以用 Dijkstra。对于具体证明，可以看[这里](https://oi-wiki.org/graph/flow/min-cost/#primal-dual-原始对偶算法)。

[code](https://atcoder.jp/contests/abc214/submissions/41914642)

---

## 作者：qczrz6v4nhp6u (赞：3)

其实这个题并不需要消除负权边，直接嗯做就是对的。

### Solution

首先同一个强连通内的点可以全部选上，缩点后转化为 DAG 上的问题。

考虑费用流。设 $s=1$ 为源点，$t$ 为汇点。记 $x\to y:(f,c)$ 表示从 $x$ 向 $y$ 连一条流量为 $f$，容量为 $c$ 的边。考虑建模：

- 对于每个点 $x$，拆点为 $x_1,x_2$，并执行三种连边：
  - $x_1\to x_2:(1,a_i)$；
  - $x_1\to x_2:(+\infty,0)$；
  - $x_2\to t:(+\infty,0)$。
- 对于 DAG 中的每一条边 $(u,v)$，执行 $u_2\to v_1:(+\infty,0)$。

不难说明答案即为流量至多为 $K$ 的最大费用流。直接跑的复杂度为 $O(nmK)$。

考虑优化。首先将费用取相反数转化为最小费用流。我们希望原始对偶能够跑这个网络，但是由于取相反数后费用变为负数，初始势能的计算不能直接 Dijkstra。注意到这张网络是个 DAG，所以我们可以拓扑排序计算势能。时间复杂度 $O(mK\log m)$。

关于正确性的说明：由 [oi-wiki](https://oiwiki.org/graph/flow/min-cost/#ssp-%E7%AE%97%E6%B3%95) 得知 SSP 算法的正确性基于原网络不存在负环，但是我们的网络是个 DAG，显然不存在环也不存在负环。

[submission](https://atcoder.jp/contests/abc214/submissions/59963513)。

---

哎我怎么忘记 Tarjan 可以直接求出逆拓扑序了。

---

## 作者：Phartial (赞：3)

# [ABC214H] Collecting

不难发现一个强连通分量里的点可以一次性被遍历到，所以先缩点，那么原图就变成了一张 DAG，问题转化为 DAG 上的最大路径覆盖，考虑以下网络流建模（$(x,y,w,c)$ 表示有一条 $x\to y$ 且容量限制为 $w$，单位费用为 $c$ 的有向边）：

- 我们将 DAG 上的一个点 $x$ 拆成两个点 $i_x,o_x$ 以限制每个点上的约束；
- 对 DAG 上的每条边 $(x,y)$，建边 $(o_x,i_y,k,0)$，表示这条边可以无限制的流且没有收益；
- 对 DAG 上的每个点 $x$，建边 $(i_x,o_x,1,v_x)$（其中 $v_x$ 为强连通分量 $x$ 包含的所有点的 $a_i$ 之和）与 $(i_x,o_x,k,0)$，表示第一个人可以收集这个强连通分量里的所有物品，而后面的人没有收益；
- 建边 $(S,i_{\mathrm{scc}_1},k,0)$，$\mathrm{scc}_1$ 表示 $1$ 所在的强连通分量编号；
- 对 DAG 上的每个点 $x$，建边 $(o_x,T,k,0)$。

取反所有边权后跑一遍最小费用最大流即可。时间复杂度 $\mathcal{O}(nmk)$，过不了一点。考虑优化。

首先我们可以用 Primal-Dual 原始对偶算法替换普通的 SSP（如果你不知道 Primal-Dual 原始对偶算法是啥，可以见[这篇博客](https://www.luogu.com.cn/blog/bykem/primal-dual-yuan-shi-dui-ou-suan-fa-xue-xi-bi-ji)），时间复杂度优化为 $\mathcal{O}(nm+mk\log n)$，仍然无法通过，复杂度瓶颈在于初始势能的计算：因为初始图中存在负权边，所以初始势能只能使用 SPFA 计算。

算法上我们无法进一步优化，于是考虑优化建图。我们不直接计算我们的收益，而是计算我们的“损失”。

先对这一张 DAG 拓扑排序并按拓扑序重新标号（在 tarjan 里求出的强连通分量其实已经按逆拓扑序排好了，所以不用再额外跑一遍拓扑排序），考虑 DAG 中的一条边 $(x,y)$，若我们走了这条边，则拓扑序在 $x+1$ 到 $y-1$ 之间的点都无法经过，我们损失了这些点能够带来的收益。那么我们可以对 $v$ 做一个前缀和 $s$，并这样建图（设 DAG 上的总点数为 $t$）：

- 我们将 DAG 上的一个点 $x$ 拆成两个点 $i_x,o_x$ 以限制每个点上的约束；
- 对 DAG 上的一条边 $(x,y)$，建边 $(o_x,i_y,k,s_{y-1}-s_x)$，表示经过这条边后就会损失编号为 $x+1\sim y-1$ 的点的收益；
- 对 DAG 上的一个点 $x$，建边 $(i_x,o_x,1,0)$ 和 $(i_x,o_x,k,v_x)$，表示第一个人可以无损失的经过这个点，而后面的人只能被迫损失这个点的收益；
- 建边 $(S,i_{\mathrm{scc}_1},k,s_{\mathrm{scc}_1-1})$，表示从 $1$ 所在的 SCC 出发时就会损失 DAG 上该点之前的所有点的收益；
- 对 DAG 上的每个点 $x$，建边 $(o_x,T,k,s_t-s_x)$，表示我们在 $x$ 点结束并损失之后的点的收益。

则我们对这张图跑最小费用最大流，答案即为 $ks_t-\mathrm{mincost}$。

不难发现这样建图后初始图中只有非负边，所以我们可以使用 Dijkstra 计算初始势能，时间复杂度优化至 $\mathcal{O}(mk\log n)$，可以通过。

可能需要一定的常数优化。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using LL = long long;

const int kN = 2e5 + 2;
const LL kI = 1e18;

int n, m, k, a[kN];
vector<int> e[kN];
int dn[kN][2], dc, b[kN], t;
vector<int> tl, bd[kN];
LL va[kN], vs[kN];
vector<int> be[kN];
bool ve[kN];
struct E {
  int y, f;
  LL c;
} ne[kN * 8];
int ce = 1, sp, ep, np;
vector<int> ed[kN * 2];
LL h[kN * 2], d[kN * 2];
int pe[kN * 2];
struct D {
  int x;
  LL d;

  D(int x, LL d) : x(x), d(d) {}
  bool operator<(const D &o) const { return d > o.d; }
};
priority_queue<D> q;
LL mc;

void T(int x) {
  dn[x][0] = dn[x][1] = ++dc, b[x] = -1;
  tl.push_back(x);
  for (int i : e[x]) {
    if (!dn[i][0]) {
      T(i);
      dn[x][1] = min(dn[x][1], dn[i][1]);
    } else if (b[i] == -1) {
      dn[x][1] = min(dn[x][1], dn[i][0]);
    }
  }
  if (dn[x][0] == dn[x][1]) {
    ++t;
    for (; tl.back() != x; tl.pop_back()) {
      bd[b[tl.back()] = t].push_back(tl.back());
    }
    bd[b[x] = t].push_back(x);
    tl.pop_back();
  }
}

void _A(int x, int y, int f, LL c) {
  ne[++ce] = {y, f, c};
  ed[x].push_back(ce);
}
void A(int x, int y, int f, LL c) {
  _A(x, y, f, c), _A(y, x, 0, -c);
}

void R(int x, int f, LL _d) {
  if (_d < d[x]) {
    d[x] = _d, pe[x] = f, q.emplace(x, _d);
  }
}
bool S() {
  fill_n(d + 1, np, kI);
  for (R(sp, 0, 0); !q.empty();) {
    D x = q.top();
    q.pop();
    if (x.d != d[x.x]) {
      continue;
    }
    for (int i : ed[x.x]) {
      if (ne[i].f) {
        R(ne[i].y, i, x.d + (ne[i].c + h[x.x] - h[ne[i].y]));
      }
    }
  }
  return d[ep] < kI;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> k;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    e[x].push_back(y);
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  T(1);
  for (int i = 1; i <= t; ++i) {
    for (int j : bd[i]) {
      va[t - i + 1] += a[j];
      for (int k : e[j]) {
        if (!ve[t - b[k] + 1] && b[k] != i) {
          ve[t - b[k] + 1] = 1;
          be[t - i + 1].push_back(t - b[k] + 1);
        }
      }
    }
    for (int j : be[t - i + 1]) {
      ve[j] = 0;
    }
  }
  for (int i = 1; i <= t; ++i) {
    vs[i] = vs[i - 1] + va[i];
  }
  sp = t * 2 + 1, ep = np = t * 2 + 2;
  A(sp, t - b[1] + 1, k, vs[t - b[1]]);
  for (int i = 1; i <= t; ++i) {
    A(t + i, ep, k, vs[t] - vs[i]);
    A(i, t + i, 1, 0);
    A(i, t + i, k, va[i]);
    for (int j : be[i]) {
      A(t + i, j, k, vs[j - 1] - vs[i]);
    }
  }
  S();
  copy_n(d + 1, np, h + 1);
  for (; S();) {
    for (int i = 1; i <= np; ++i) {
      h[i] += d[i];
    }
    int mf = k;
    for (int x = ep; x != sp; x = ne[pe[x] ^ 1].y) {
      mf = min(mf, ne[pe[x]].f);
    }
    for (int x = ep; x != sp; x = ne[pe[x] ^ 1].y) {
      mc += mf * ne[pe[x]].c;
      ne[pe[x]].f -= mf, ne[pe[x] ^ 1].f += mf;
    }
  }
  cout << k * vs[t] - mc << '\n';
  return 0;
}
```


---

## 作者：dxbt (赞：1)


## sol
在同一强连通分量内的物品，只需在第一次访问时拾取即可。因此，通过将各个强连通分量合并为一个，可以假定图是一个有向无环图。

以下假定图是一个有向无环图，顶点 1，2，…，N 按拓扑顺序排列。可以将问题转化为最小费用流问题。

首先想到的方法是：

对于 $1 \le u \le N$，准备顶点 $in_u$ 和 $out_u$。另外，准备起点和终点 $S,T$。
对于 $1 \le u \le N$，从 $in_u$ 到 $out_u$ 连边，容量为 1，费用为 $-X_u$。同时，还要连边，容量为 $\infty$，费用为 0。
对于每条边 $(u,v)$，从 $out_u$ 到 $in_v$ 连边，容量为 $\infty$，费用为 0。
从 $S$ 到 $in_1$ 连边，容量为 $\infty$，费用为 0。
对于 $1 \le u \le N$，从 $out_u$ 到 $T$ 连边，容量为 $\infty$，费用为 0。
将 $S$ 到 $T$ 的流量设为 $K$，再将最小费用乘上 $-1$，即为答案。

但是，用这种方法会产生负边。通过以下方法可以消除负边：

对于 $1 \le u \le N$，从 $in_u$ 到 $out_u$ 连边，容量为 1，费用为 0。同时，还要连边，容量为 $\infty$，费用为 $X_u$。
对于每条边 $(u,v)$，从 $out_u$ 到 $in_v$ 连边，容量为 $\infty$，费用为 $X_{u+1}+\cdots+X_{v-1}$。
从 $S$ 到 $in_1$ 连边，容量为 $\infty$，费用为 0。
对于 $1 \le u \le N$，从 $out_u$ 到 $T$ 连边，容量为 $\infty$，费用为 $X_{u+1}+\cdots+X_N$。
答案为流量为 $K$ 时 $S$ 到 $T$ 的最小费用减去 $K(\sum_u X_u)$。

---

## 作者：ghx0052 (赞：1)

# 思路：

很显然是费用流。

但是 spfa 会被卡。

需要用 dijkstra 费用流。

方法：令 $h_i$
表示当前从 $s$
到 $i$
的最短路减去上一次增广前 $s
$ 到 $i$ 
的最短路。

然后考虑对 $h$ 
跑对短路。

边权 $u \to v,w$ 
变成 $w + dis[u] - dis[v]$ 。可以发现这个总是 $\ge 0$ 。

然后就做完了。

# 代码
```cpp
#include<bits/stdc++.h>
#define rb(a,b,c) for(int a=b;a<=c;++a)
#define rl(a,b,c) for(int a=b;a>=c;--a)
#define LL long long
#define IT iterator
#define PB push_back
#define II(a,b) make_pair(a,b)
#define FIR first
#define SEC second
#define FREO freopen("check.out","w",stdout)
#define rep(a,b) for(int a=0;a<b;++a)
#define SRAND mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define random(a) rng()%a
#define ALL(a) a.begin(),a.end()
#define POB pop_back
#define ff fflush(stdout)
#define fastio ios::sync_with_stdio(false)
#define check_min(a,b) a=min(a,b)
#define check_max(a,b) a=max(a,b)
using namespace std;
//inline int read(){
//    int x=0;
//    char ch=getchar();
//    while(ch<'0'||ch>'9'){
//        ch=getchar();
//    }
//    while(ch>='0'&&ch<='9'){
//        x=(x<<1)+(x<<3)+(ch^48);
//        ch=getchar();
//    }
//    return x;
//}
#define int LL
typedef pair<LL,LL> mp;
/*}
*/
const int GRAPH_SIZE= 4e5+10;
int s=0,t=GRAPH_SIZE-1;
struct EDGE{
	int u,v,c,cos;
};
vector<EDGE> e;
vector<int> each[GRAPH_SIZE];
int maxflow,mincost;
int flow[GRAPH_SIZE];
int dis[GRAPH_SIZE],las[GRAPH_SIZE],h[GRAPH_SIZE];
bool fi=0;
int cnt=0;
bool spfa(){
	flow[s]=1e17;
	if(!fi){
		fi=1;
		fill(dis,dis+GRAPH_SIZE,1e17);
		dis[s]=0;
		rb(now,0,cnt*2){
			if(dis[now]==1e17) continue;
//			cerr<<now<<' '<<dis[now]<<endl;
			for(auto it:each[now]){
				int to,f,c;
				to=e[it].v;
				f=e[it].c;
				c=e[it].cos;
				if(f<=0) continue;
				assert(to>now);
				if(dis[to]>dis[now]+c){
					dis[to]=dis[now]+c;
					las[to]=it;
					flow[to]=min(flow[now],f);
				}
			}
		}
	}
	else{
		fill(h,h+GRAPH_SIZE,1e17);
		h[s]=0;
		priority_queue<mp,vector<mp>,greater<mp> > heap;
		heap.push(II(0,s));
		while(!heap.empty()){
			mp Now=heap.top();
			heap.pop();
			if(Now.FIR!=h[Now.SEC]) continue;
			int now=Now.SEC;
			for(auto it:each[now]){
				int to,f,c;
				to=e[it].v;
				f=e[it].c;
				c=e[it].cos+dis[now]-dis[to];
				if(f<=0) continue;
				if(h[to]>h[now]+c){
					h[to]=h[now]+c;
					las[to]=it;
					flow[to]=min(flow[now],f);
					heap.push(II(h[to],to));
				}
			}
		}
		rep(i,GRAPH_SIZE) dis[i]=min((LL)(1e17),dis[i]+h[i]);
	}
//	cerr<<dis[t]<<endl;
	return dis[t]<=1e16;
}
void KM(){
	while(spfa()){
		maxflow+=flow[t];
		mincost+=dis[t]*flow[t];
//		cout<<mincost<<" "<<maxflow<<endl;
		int now=t;
		while(now!=s){
			e[las[now]].c-=flow[t];
			e[las[now]^1].c+=flow[t];
			now=e[las[now]].u;
		}
	}
}
void make_edge(int U,int V,int C,int COS){
	EDGE tmp;
	tmp.u=U;
	tmp.v=V;
	tmp.c=C;
	tmp.cos=COS;
	e.PB(tmp);
	each[U].PB(e.size()-1);
	swap(tmp.u,tmp.v);
	tmp.c=0;
	tmp.cos=-COS;
	e.PB(tmp);
	each[V].PB(e.size()-1);
}
const int MAXN=2e5+10;
int n,m,k;
int in[MAXN],out[MAXN];
int belong[MAXN];
vector<int> g[MAXN],rg[MAXN];
int u[MAXN],v[MAXN];
stack<int> sta;
bool vis[MAXN];
map<mp,bool> app;
int x[MAXN];
void dfs(int now){
	vis[now]=1;
	for(auto it:g[now]) if(!vis[it]) dfs(it);
	sta.push(now);
}
void rdfs(int now){
	belong[now]=cnt;
	for(auto it:rg[now]) if(!belong[it]) rdfs(it);
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	rb(i,1,m){
		scanf("%lld%lld",&u[i],&v[i]);
		g[u[i]].PB(v[i]);
		rg[v[i]].PB(u[i]);
	}
//	cout<<g[1].size()<<endl;
	rb(i,1,n)
	if(!vis[i]) dfs(i);
	while(!sta.empty()){
		int now=sta.top();
		sta.pop();
		if(!belong[now]){
			++cnt;
			rdfs(now);
		}
	}
//	cout<<"!"<<cnt<<endl;
	rb(i,1,n){
		LL xx;
		scanf("%lld",&xx),x[belong[i]]+=xx;
	}
	rb(i,1,cnt) in[i]=i*2-1,out[i]=i*2;
	make_edge(s,in[belong[1]],k,0);
	rb(i,1,m){
		int U,V;
		U=belong[u[i]];
		V=belong[v[i]];
		if(U==0||V==0) continue;
		if(U!=V&&!app[II(U,V)]){
			app[II(U,V)]=1;
			assert(U<V);
//			cout<<out[U]<<" "<<in[V]<<endl;
			assert(out[U]<in[V]);
			make_edge(out[U],in[V],k,0);
		}
	}
//	cout<<cnt<<endl;
	rb(i,1,cnt) make_edge(in[i],out[i],1,-x[i]),make_edge(in[i],out[i],k,0);
	rb(i,1,cnt) make_edge(out[i],t,k,0);
	KM();
	cout<<-mincost<<endl;
	return 0;
}

```

管理大大求过审，谢谢！

---

## 作者：strcmp (赞：0)

首先我们可以重复走，因此一个联通分量里的都是可以取完的。

用个你喜欢的强联通分量算法缩点，问题弱化为 dag 上的 $k$ 大链。

还是不好做，直接考虑费用流。

$s \to 1$，容量为 $k$ 费用为 $0$。$u \to u'$ 容量为 $1$ 费用为 $-x_u$，$u \to u'$ 容量为 $+\infty$ 费用为 $0$，$u' \to v$ 容量为 $+\infty$ 费用为 $0$。$u' \to t$ 容量为 $+\infty$ 费用为 $0$。

跑最小费用最大流，总费用取相反数即为答案，当然这里的点都是缩点之后的图上结点，$u'$ 是 $u$ 拆出来的出点。

总流量不超过 $f = k$，暴力跑 MCMF 时间复杂度是 $\Theta(nmk)$ 的，不太能过。

原问题一定不弱于 DAG 的最小链覆盖，我们不得不跑 $k$ 次费用流。考虑原始对偶费用流，如果我们有办法能重建边权使得初始所有费用都为正，则可以使用 Dijkstra 加势的方法做到 $\Theta(km \log n)$，是可以通过的复杂度。

tips：解释一下不能直接 DAG 上 dp 求最长路的原因，因为我们增广了之后会出现反向的边，不可能保证不出现环，破坏了 DAG 的性质无法继续。如果不换建模，我们初始非流满的边就会有负权边，进而不能使用原始对偶算法（要求初始费用都为非负数，之后怎么样无所谓）。感觉很多题解没解释直接一笔带过了。

好，现在问题只是如何构造初始图使得初始边权都非负。注意到我们要取反边权是因为要跑最大费用最大流，跑最大费用最大流不可能避免负权边。因此考虑能不能直接跑正权的最小费用最大流，然后用总量减去费用。

因此我们不得不将原问题**对偶**，现在假设所有物品都被选择了，选出最少的物品踢出去使得我们能链覆盖掉。

先跑出来拓扑序，考虑有哪些物品是我们要放弃掉的。

**令 DAG 结点标号为拓扑序**，考虑 $u < v$ 的时候 $u \to v$ 产生了什么影响，发现我们可以钦定这种影响就是 $[u + 1,\,v - 1]$ 走不到了，直接让 $u \to v'$ 的费用为 $s_{v - 1} - s_{u}$（$s$ 是 $x$ 在拓扑序上的前缀和），容量为 $+\infty$。$u \to u'$ 连容量为 $1$ 费用为 $0$ 的边，代表第一次走可以不减贡献，然后 $u \to u'$ 连容量为 $+\infty$ 费用为 $x_u$ 的边（当然 $+\infty$ 容量的边设成 $k$ 也没问题）。

原始对偶算法跑最小费用最大流即可，时间复杂度 $\Theta(km \log n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using ull = unsigned long long int;
constexpr int maxn = 1e6 + 10, inf = 1e9, mod = 998244353;
struct edge { int fr, to, nxt; ll w, c; } nd[maxn << 1]; int h[maxn], cnt = 0; vector<int> g[maxn]; int scc[maxn], dfn[maxn], low[maxn], vis[maxn], st[maxn], top, dct, n, N, m, k;
inline void add(int u, int v, ll w, ll c) { nd[cnt].nxt = h[u], nd[cnt].fr = u, nd[cnt].to = v, nd[cnt].w = w, nd[cnt].c = c, h[u] = cnt++; }
inline void addE(int u, int v, ll w, ll c) { add(u, v, w, c), add(v, u, 0, -c); }
void tarjan(int u) {
	dfn[u] = low[u] = ++dct; st[++top] = u; vis[u] = 1;
	for (int v : g[u]) {
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		scc[u] = ++N; vis[u] = 0;
		while (st[top] != u) vis[st[top]] = 0, scc[st[top--]] = N;
		--top;
	}
}
set<pii> S; ll a[maxn], d[maxn], b[maxn]; int pre[maxn], s, t; ll sum = 0, ans = 0;
priority_queue<pli, vector<pli>, greater<pli>> q;
int dij() {
	rep(i, 1, t) d[i] = 1e16; d[s] = 0; q.push({ 0LL, s });
	while (!q.empty()) {
		int u = q.top().Y; ll k = q.top().X; q.pop();
		if (k > d[u]) continue;
		for (int i = h[u]; ~i; i = nd[i].nxt) {
			int v = nd[i].to; ll w = nd[i].c + b[u] - b[v];
			if (nd[i].w && d[v] > d[u] + w) d[v] = d[u] + w, pre[v] = i, q.push({ d[v], v });
		}
	}
	if (d[t] > 9e15) return 0;
	rep(i, 1, n) b[i] = min(b[i] + d[i], (ll)3e17); int u = t; ll w = 1e16;
	while (u != s) w = min(w, nd[pre[u]].w), u = nd[pre[u]].fr; u = t; sum += w;
	while (u != s) ans += w * nd[pre[u]].c, nd[pre[u]].w -= w, nd[pre[u] ^ 1].w += w, u = nd[pre[u]].fr;
	return 1;
}
void PrimalDual() { while (dij()); }
int main() {
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1, u, v; i <= m; i++) scanf("%d%d", &u, &v), g[u].pb(v);
	rep(i, 1, n) if (!dfn[i]) tarjan(i); 
	rep(i, 1, n) {
		ll x; scanf("%lld", &x);
		a[scc[i] = N - scc[i] + 1] += x; 
	}
	rep(i, 1, N) a[i] += a[i - 1]; s = 2 * N + 1, t = 2 * N + 2;
	rep(u, 1, n) for (int v : g[u]) if (scc[u] != scc[v] && !S.count({ scc[u], scc[v] })) S.insert({ scc[u], scc[v] }), addE(scc[u] + N, scc[v], inf, a[scc[v] - 1] - a[scc[u]]); 
	addE(s, scc[1], k, a[scc[1] - 1]);
	rep(u, 1, N) {
		addE(u, u + N, 1, 0);
		addE(u, u + N, inf, a[u] - a[u - 1]);
		addE(u + N, t, inf, a[N] - a[u]);
	}
	PrimalDual();
	printf("%lld\n", k * a[N] - ans);
	return 0;
}
```

---

