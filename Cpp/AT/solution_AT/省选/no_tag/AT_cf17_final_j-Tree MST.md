# Tree MST

## 题目描述

[problemUrl]: https://atcoder.jp/contests/cf17-final/tasks/cf17_final_j

りんごさんは $ N $ 頂点の木を持っています。 この木の $ N-1 $ 本の辺のうち $ i $ 番目の辺は頂点 $ A_i $ と頂点 $ B_i $ を繋いでおり、重みは $ C_i $ です。 また、頂点 $ i $ には $ X_i $ の重みがついています。

ここで $ f(u,v) $ を、「頂点 $ u $ から頂点 $ v $ までの距離」と「$ X_u\ +\ X_v $」の和と定めます。

$ N $ 頂点の完全グラフ $ G $ を考えます。 頂点 $ u $ と頂点 $ v $ を繋ぐ辺のコストは $ f(u,v) $ です。 グラフ $ G $ の最小全域木を求めて下さい。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 200,000 $
- $ 1\ \leq\ X_i\ \leq\ 10^9 $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- 与えられるグラフは木である。
- 入力は全て整数である。

### Sample Explanation 1

頂点 $ 1 $ と $ 2 $、頂点 $ 1 $ と $ 4 $、頂点 $ 3 $ と $ 4 $ を繋ぐとそれぞれのコストは $ 5,8,9 $ となり、合計は $ 22 $ となります。

## 样例 #1

### 输入

```
4
1 3 5 1
1 2 1
2 3 2
3 4 3```

### 输出

```
22```

## 样例 #2

### 输入

```
6
44 23 31 29 32 15
1 2 10
1 3 12
1 4 16
4 5 8
4 6 15```

### 输出

```
359```

## 样例 #3

### 输入

```
2
1000000000 1000000000
2 1 1000000000```

### 输出

```
3000000000```

# 题解

## 作者：command_block (赞：32)

**题意** : 给定一棵 $n$ 个点的树,边有边权。

按照如下规则建立一张完全图 : $x,y$之间的边长为$w[x]+w[y]+dis(x,y)$

求完全图的 `MST` 边权和。

$n\leq 2\times 10^5$,时限$\texttt{5s}$.

------------

- $O(n\log^2 n)$

一般地,对于(完全图)`MST`问题,我们可以先选定一个**边集**,做一次`MST`(不连通不管),把剩余的边保留,最后再做一次`MST`,这样一定能得到最优解。

这是个树形结构,我们可以点分治,考虑跨越重心的路径所生成的边集。

以分治中心为根,令$p[u]=w[u]+dep[u]$,则连接两个点的代价就是$p[u]+p[v]$(关建边的长度)

我们只需保留$p$最小的一个点,然后把其他点都和他相连,显然就是`MST`了。

这里会产生子树内自己连的路径,但是比直接连劣所以不会影响答案。

点分治一共会产生$O(n\log n)$条边,然后跑一个`kruskal`就$O(n\log^2 n)$

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
#define ll long long
#define MaxN 200500
using namespace std;
inline int read()
{
  int X=0;char ch=0;
  while(ch<48||ch>57)ch=getchar();
  while(ch>=48&&ch<=57)X=X*10+(ch^48),ch=getchar();
  return X;
}
vector<int> g[MaxN],l[MaxN];
int tp[MaxN],tn,ms[MaxN],siz[MaxN];
bool vis[MaxN];
void pfs(int u,int fa)
{
  tp[++tn]=u;
  siz[u]=1;ms[u]=0;
  for (int i=0,v;i<g[u].size();i++)
    if ((v=g[u][i])!=fa&&!vis[v]){
      pfs(v,u);
      siz[u]+=siz[v];
      ms[u]=max(ms[u],siz[v]);
    }
}
int getrt(int u)
{
  tn=0;pfs(u,0);
  int rt=0;
  for (int i=1;i<=tn;i++){
    ms[tp[i]]=max(ms[tp[i]],tn-siz[tp[i]]);
    if (ms[tp[i]]<ms[rt])rt=tp[i];
  }return rt;
}
ll w[MaxN],dep[MaxN],mp;
void dfs(int u,int fa)
{
  if (w[mp]+dep[mp]>w[u]+dep[u])mp=u;
  for (int i=0,v;i<g[u].size();i++)
    if ((v=g[u][i])!=fa&&!vis[v]){
      dep[v]=dep[u]+l[u][i];
   	  dfs(v,u);
    }
}
struct Line
{int f,t;ll len;}s[MaxN<<5];
int tot;
void solve(int u)
{
  dep[u]=mp=0;dfs(u,0);
  ll sav=w[mp]+dep[mp];
  for (int i=1;i<=tn;i++)
    s[++tot]=(Line){tp[i],mp,sav+w[tp[i]]+dep[tp[i]]};
  vis[u]=1;
  for (int i=0,v;i<g[u].size();i++)
    if (!vis[v=g[u][i]])
   	  solve(getrt(v));
}
int n,f[MaxN];
bool cmp(const Line &A,const Line &B)
{return A.len<B.len;}
int findf(int u)
{return f[u]==u ? u : f[u]=findf(f[u]);}
bool merge(int x,int y)
{
  x=findf(x);y=findf(y);
  if (x==y)return 0;
  f[x]=y;return 1;
}
int main()
{
  n=read();w[0]=1ll<<60;ms[0]=n+1;
  for (int i=1;i<=n;i++)w[i]=read();
  for (int i=1,fr,to,len;i<n;i++){
    fr=read();to=read();len=read();
    g[fr].push_back(to);
    l[fr].push_back(len);
    g[to].push_back(fr);
    l[to].push_back(len);
  }solve(getrt(1));
  ll ans=0;
  for (int i=1;i<=n;i++)f[i]=i;
  sort(s+1,s+tot+1,cmp);
  for (int i=1;i<=tot;i++)
    if (merge(s[i].f,s[i].t))
      ans+=s[i].len;
  printf("%lld",ans);
}
```

- $O(n\log n)$

考虑使用用Boruvka算法。

每一轮,我们要对每个连通块找到最小出边(到达其他连通块)

对于一个已经联通块染色的局面,我们可以进行`up and down DP`.

首先求出从子树到达本身的最优决策,问题来了,颜色不能相同……

$\texttt{stO EI Orz}$

我们记录最大值和次大值即可,对颜色去重,这样万一最大的碰了还有补刀的。 (本蒟蒻这里可能写丑了)

然后再次`dfs`计算从上面延伸过来的即可。

每轮会使连通块个数减半,复杂度就是$O(n\log n)$,常数较大。

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
#define ll long long
#define MaxN 200500
using namespace std;
inline int read()
{
  int X=0;char ch=0;
  while(ch<48||ch>57)ch=getchar();
  while(ch>=48&&ch<=57)X=X*10+(ch^48),ch=getchar();
  return X;
}
vector<int> g[MaxN],l[MaxN];
int w[MaxN],c[MaxN];
#define Pr pair<ll,int>
#define mp make_pair
#define fir first
#define sec second
struct Data
{
  Pr x,x2;int c;
  bool chk(const Data &t){
    if (t.c==c){
      x=min(x,t.x);
      x2=min(x2,t.x2);
    }else {
      if (t.x<=x){
        x2=min(x,t.x2);
        c=t.c;x=t.x;
      }else x2=min(x2,t.x);
    }
  }
  Pr get(int tc){
    if (tc==c)return x2;
    return x;
  }
}f[MaxN];
void dfs1(int u,int fa)
{
  f[u].x=mp(w[u],u);
  f[u].c=c[u];
  for (int i=0,v;i<g[u].size();i++)
    if ((v=g[u][i])!=fa){
   	  dfs1(v,u);
   	  f[v].x.fir+=l[u][i];
   	  f[v].x2.fir+=l[u][i];
   	  f[u].chk(f[v]);
   	  f[v].x.fir-=l[u][i];
      f[v].x2.fir-=l[u][i];
   	}
}
void dfs2(int u,int fa)
{
  for (int i=0,v;i<g[u].size();i++)
    if ((v=g[u][i])!=fa){
      f[u].x.fir+=l[u][i];
      f[u].x2.fir+=l[u][i];
      f[v].chk(f[u]);
   	  dfs2(v,u);
   	  f[u].x.fir-=l[u][i];
      f[u].x2.fir-=l[u][i];
    }
}
int n,cnt;
int findf(int u)
{return c[u]==u ? u : c[u]=findf(c[u]);}
bool merge(int x,int y)
{
  x=findf(x);y=findf(y);
  if (x==y)return 0;
  c[x]=y;return 1;
}
#define INF (1ll<<60)
Pr p[MaxN];
int main()
{
  n=read();
  for (int i=1;i<=n;i++)w[i]=read();
  for (int i=1,fr,to,len;i<n;i++){
    fr=read();to=read();len=read();
    g[fr].push_back(to);
    l[fr].push_back(len);
    g[to].push_back(fr);
    l[to].push_back(len);
  }for (int i=1;i<=n;i++)c[i]=i;
  ll ans=0;
  while(cnt<n-1){
    for (int i=1;i<=n;i++){
      p[i].fir=f[i].x.fir=f[i].x2.fir=INF;
      f[i].x.sec=f[i].x2.sec=f[i].c=0;
    }dfs1(1,0);dfs2(1,0);
    for (int i=1;i<=n;i++){
      Pr sav=f[i].get(c[i]);
      sav.fir+=w[i];
      p[c[i]]=min(p[c[i]],sav);
    }for (int i=1;i<=n;i++)
      if (p[i].fir<INF&&merge(i,p[i].sec))
        {ans+=p[i].fir;cnt++;}
    for (int i=1;i<=n;i++)findf(i);
  }printf("%lld",ans);
}
```


---

## 作者：liangbowen (赞：26)

[problem](https://www.luogu.com.cn/problem/AT_cf17_final_j) & [blog](https://www.cnblogs.com/liangbowen/p/17542298.html)。

萌萌点分治，积累个 trick /qq。

---

> 对于完全图 $(V,E)$，将 $E$ 分成 $E_1, E_2, \cdots, E_k$（$E_1 \cup E_2 \cup \cdots \cup E_k = E$）。对每个边集求 MST，得到新边集 $E_1^{'}, E_2^{'}, \cdots, E_k^{'}$，再求 MST。最终剩下的边集，**等同于原边集的 MST**。

反证是平凡的，就不证了。

对照上面那玩意，$E_i$ 是可以随便选的，所以直接上点分治。对于一个中心，按照板子求遍 $dis_u$。那么 $(u,v)=w_u+w_v+dis_{u,v}=(w_u+dis_u)+(w_v+dis_v)$。故可以按照 $w_u+dis_u$ 为关键字，取其中最小的那个，和同一次 divide 时获得的其他 $u$，构成边并加入 Kruskal 边集。

按照 trick 的理论，跑遍 Kruskal 就是答案了。

~~所以甚至比洛谷模板题还好写。~~

[代码](https://atcoder.jp/contests/cf17-final/submissions/43460920)，看起来是两只 log 的，不是很会证这种东西所以不管了。


---

## 作者：暴力出奇迹 (赞：19)

**题意：** 给定一棵 $n$ 个点的树，点和边都有权值，有张 $n$ 个点的完全图，$(x,y)$ 权值为 $w_x+w_y+dis(x,y)$，其中 $w_x$ 和 $w_y$ 为权值，$dis(x,y)$ 表示 $x$ 和 $y$ 在树上的带权距离。求这张图的最小生成树的边权之和。$n \le 2 \times 10^5$。

这是一类经典的最小生成树题目，这类题目的特征是：$n$ 个点的完全图，**两点之间的距离通过某个公式计算得到**（例如 $x$ 和 $y$ 点之间的边权 $w(x,y)=A_x \operatorname{xor} A_y$），要求出这个完全图的最小生成树。

首先这种题目的点数是可以出到 $10^5$ 级别的，因为虽然任意两点之间都有连边，但是边权是通过公式计算得到的，所以在输入中只需要给出 $n$ 个点的权值即可，~~毒瘤出题人。~~

那么用 Kruskal 算法的复杂度是 $O(n^2 \log ^2 n)$ 的，用 Prim 算法稍快一点，但是复杂度仍然为 $O(n^2)$ 级别，过不了。那么对于这类生成树题目，我们一般使用一个特殊的算法：**Boruvka 算法**。

### **Boruvka 算法的大体流程：**

1. 维护当前所有点形成的连通块，初始时没有选择任何边，也就是每个点单独形成一个连通块。

2. Boruvka 算法进行若干轮连边，在每一轮中，**为每个连通块找到一条权值最小的连向该连通块外部的边，** 并将这条边连接起来。（连接之前判断一下是否已经连通，因为本轮连边的之前连接的若干条边可能已经使得这条边两端结点已经连通。）

3. 直到某一轮发现所有点已经在一个连通块内时，算法结束。

不难发现，若连通块的数量为 $2n$，那么一轮连边之后剩余连通块数量最多只剩 $n$ 个（最坏情况是 $1$ 和 $2$ 连边，$3$ 和 $4$ 连边，...，$2n-1$ 和 $2n$ 连边），**因此 Boruvka 算法的连边轮数是 $O(\log n)$ 级别的。**

如果只是正常的图，Boruvka 算法每一轮连边要检查图中所有的边，时间复杂度大约为 $O((n+m)\log n)$，也不比 Kruskal 快到哪里去；**但是在这一类完全图生成树问题中，Boruvka 算法有着特殊的优势。** 以这道题目为例介绍一下。

先转化一下边权 $w(x,y)=w_x+w_y+dis(x,y)$，由于 $dis(x,y)=sum_x+sum_y-2\times sum_{lca(x,y)}$（$sum_x$ 表示 $x$ 点到根的距离），所以 $w(x,y)=w_x+w_y+sum_x+sum_y-2 \times sum_{lca(x,y)}$。

为了简化，我们假设 $W_x=w_x+sum_x$，有 $w(x,y)=W_x+W_y-2 \times sum_{lca(x,y)}$。

根据 Boruvka 算法的流程，我们每一轮要为所有点 $x$，找到尚未与之连通的点 $y$，并最小化 $w(x,y)$，也就是相当于我们要最小化 $W_y-2 \times sum_{lca(x,y)}$。我们考虑去枚举这个 $z=lca(x,y)$，然后在 $z$ 的子树中枚举 $y$ 即可。

但是这样真的对吗？有没有可能出现一种情况：枚举到的 $y$ 和 $x$ 在 $z$ 的同一棵子树内，使得 $lca(x,y)$ 并不是 $z$？

是有这种可能的，但是并不影响算法的正确性，因为在这种情况下 $lca(x,y)$ 是 $z$ 的后代，而此时的 $z$ 一定不优（因为 $sum_z<sum_{lca_(x,y)}$，导致 $W_y-2 \times sum_z>W_y-2 \times sum_{lca(x,y)}$），而这个更优的情况会在 $z=lca(x,y)$ 时被枚举到，所以并不影响。

我们把这个找点的过程大体分为两个阶段：

1. 将所有是 $z$ 后代的 $y$ 的权值“挂到”结点 $z$ 上。

也就是我们对于每个 $z$，维护 $W_y-2 \times sum_z$ 的最小值，实质就是计算 $W_y$ 的最小值。这个可以通过一次 dfs，自下而上递推得出。

2. 对于每个点 $x$，枚举所有可能的 $z$，并取 $W_y-2 \times sum_z$ 的最小值。

不难发现这样的 $z$ 一定全是 $x$ 的祖先（包括自己），所以我们再 dfs 一遍，自上而下递推不难得出。

但是我们似乎忘了一个限定条件？**每一轮要找的边的两个端点，必须属于不同的已有连通块。** 这样我们求出的最小值对应的点 $y$，可能正好和 $x$ 已经连通了。

解决方法是：**同时维护最小值和次小值，并且限定最小值和次小值对应的 $y$ 结点不在同一连通块中。** 这样若最小值对应的 $y$ 点和 $x$ 不在同一连通块中，就选择这个最小值，否则选择“替补”的次小值即可。

连边轮数是 $O(\log n)$ 的，每一轮两次 dfs 是 $O(n)$ 的，总复杂度为 $O(n \log n)$。

代码如下：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define LL long long
const int N = 200010;
const LL inf = 1e18 + 10;
struct Edge {
	int to, cost, nxt;
}edges[N << 1]; int head[N], nedge;
struct Edge2 {
	int u, v;
}link2[N];
inline LL min(LL x, LL y) {return x < y ? x : y;}
struct Tuple {
	int idx, col; LL dist; //idx 表示对应的 y 结点，col 表示 y 结点所在的连通块（代表元），dist 表示计算的权值
};
struct Solution {
	Tuple minv, secmin;
	Solution operator * (const Tuple &rhs) const {
		Solution ret = (Solution){minv, secmin};
		if(rhs.col == ret.minv.col) //先特殊处理在同一个连通块的情况：直接取 min 即可。
			ret.minv.dist = min(ret.minv.dist, rhs.dist);
		else if(rhs.col == ret.secmin.col) {
			ret.secmin.dist = min(ret.secmin.dist, rhs.dist);
			if(ret.secmin.dist < ret.minv.dist)
				swap(ret.secmin, ret.minv); //注意可能要交换最小值和次小值！
		}
		else if(rhs.dist <= ret.minv.dist) {
			ret.secmin = ret.minv;
			ret.minv = rhs;
		}
		else if(rhs.dist < ret.secmin.dist)
			ret.secmin = rhs;
		return ret;
	}
	Solution operator + (const Solution &rhs) const {
		return (rhs * minv) * secmin;
	}
}sol[N];
LL A[N], sum[N];
int link[N]; LL cost[N];
LL cost2[N];
int fa[N], n;
int par[N], col[N];
inline int findroot(int x) {return par[x] == x ? x : par[x] = findroot(par[x]);}
inline void unite(int x, int y) {par[findroot(x)] = findroot(y);}
inline bool same(int x, int y) {return findroot(x) == findroot(y);}
void addedge(int u, int v, int w) {
	edges[++nedge].to = v;
	edges[nedge].cost = w;
	edges[nedge].nxt = head[u];
	head[u] = nedge;
}
void dfs(int u) {
	A[u] += sum[u];
	for(int i = head[u]; i; i = edges[i].nxt) {
		int v = edges[i].to, w = edges[i].cost;
		if(fa[u] == v) continue;
		fa[v] = u;
		sum[v] = sum[u] + w; dfs(v);
	}
}
void dfs1(int u) { //第一轮 dfs：自下而上递推
	sol[u].minv = (Tuple){u, col[u], A[u]};
	sol[u].secmin = (Tuple){0, 0, inf};
	for(int i = head[u]; i; i = edges[i].nxt) {
		int v = edges[i].to;
		if(fa[u] == v) continue;
		dfs1(v); sol[u] = sol[u] + sol[v];
	}
}
void dfs2(int u) { //第二轮 dfs：自上而下递推
	if(u == 1) {
		sol[u].minv.dist -= 2 * sum[u];
		sol[u].secmin.dist -= 2 * sum[u];
	}
	if(sol[u].minv.col == col[u]) {
		link[u] = sol[u].secmin.idx;
		cost[u] = A[u] + sol[u].secmin.dist;
	} else {
		link[u] = sol[u].minv.idx;
		cost[u] = A[u] + sol[u].minv.dist;
	}
	for(int i = head[u]; i; i = edges[i].nxt) {
		int v = edges[i].to;
		if(fa[u] == v) continue;
		sol[v].minv.dist -= 2 * sum[v];
		sol[v].secmin.dist -= 2 * sum[v];
		sol[v] = sol[v] + sol[u]; dfs2(v);
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%lld", &A[i]);
	for(int i = 1; i < n; ++i) {
		int u, v, w; scanf("%d %d %d", &u, &v, &w);
		addedge(u, v, w); addedge(v, u, w);
	}
	dfs(1);
	for(int x = 1; x <= n; ++x) par[x] = x;
	LL ans = 0;
	while(true) {
		for(int x = 1; x <= n; ++x) col[x] = findroot(x);
		bool flag = true;
		for(int x = 2; x <= n; ++x)
			if(col[x] != col[1]) {flag = false; break;}
		if(flag) break;
		dfs1(1); dfs2(1);
		for(int u = 1; u <= n; ++u) cost2[u] = inf;
		for(int u = 1; u <= n; ++u)
			if(cost[u] < cost2[col[u]]) {
				link2[col[u]] = (Edge2){u, link[u]};
				cost2[col[u]] = cost[u];
			}
		for(int u = 1; u <= n; ++u)
			if(cost2[u] < inf) {
				int x = link2[u].u, y = link2[u].v;
				if(!same(x, y)) {unite(x, y); ans += cost2[u];}
			} //注意最后的连边，是每个连通块选一条连向外部的最小的边！
	}
	printf("%lld", ans);
	return 0;
}
```

附一些 Boruvka 算法的练习题：

[CF888G Xor-MST](https://www.luogu.com.cn/problem/CF888G)

[CF1550F Jumping Around](https://www.luogu.com.cn/problem/CF1550F)

---

## 作者：pengyule (赞：10)

## 思想及流程
Boruvka 是 Kruskal 和 Prim 两者的结合算法，“博采众长”因此能轻松解决一类两者很难快速解决的问题，尤其是完全图（稠密图）的 MST。

Boruvka 的思想是：最开始每个点都是一个孤立的连通块，之后经过多轮的迭代，向 MST 边集中加边，把边的两端的连通块合并。加边的方法是：对每个连通块找到离它最近的连通块，这条边叫做这个连通块的“最小边”，每一轮结束时将所有拥有最小边的连通块的最小边加入 MST 边集；这一步可以用 $O(E)$ 地枚举边并更新两端连通块的最小边来做到，但很多时候也会采用 dp 等方法直接求得这个离它最近的连通块。每一轮结束后，所有连通块都设为“没有最小边”，并进入下一轮。对于一个连通图来说，合并一轮下来，都会将连通块的数量至少减半，极端情况是 $V/2$ 个连通块和另外 $V/2$ 个连通块刚好分别是 $V/2$ 个最小边的两端。这样一来，最多只会迭代 $\log V$ 轮，常见时间复杂度为 $O(E\log V)$。（当然主要取决于找最小边的方法）

## 推荐题目
[CODE-FESTIVAL-2017-FINAL Tree MST](https://www.luogu.com.cn/problem/AT3611)


这个题就是典型的使用了 dp 的方法来寻找连通块的最近连通块。在每轮中，我们可以用树形 dp 维护一个点的子树里离它最近的两个颜色互异的点（最近的含义是“完全图”中边权最小）。这样一来，这两个点中至少一个的颜色和 $x$ 不一样，而这样的信息也容易为父亲所用。再进行一道换根 dp，得到离每个点最近的、跟这个点颜色不一样的点，用“点的最小边”更新点所在连通块的最小边，照搬 Boruvka 的流程即可。

```cpp
/*
Todo list:
1. How to embed 'whether a node has miniedge' into ppp
2. How to connect in BCJ
3. You haven't changed vertex to color! DONE
*/
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define ppp pair<pii,pii >
#define fi first
#define se second
#define mkp make_pair
using namespace std;
const int N=2e5+5,INF=1e17;
const ppp nu=mkp(mkp(INF,0),mkp(INF,0));
int n,n_v,n_e,ans,w[N],fa[N];
bool bk[N];
vector<pii>gr[N],G[N];
vector<ppp>f[N]; // nearest 2 colors in x's subtree
pair<pii,int>mn[N]; // to store the miniedges for each routine
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void unite(int x,int y){fa[find(y)]=find(x);}
inline void adde(int u,int v,int w){
	gr[u].push_back(mkp(v,w)),gr[v].push_back(mkp(u,w));
}
void dfs0(int x,int p){
	for(int i=0;i<gr[x].size();i++){
		int y=gr[x][i].first,z=gr[x][i].second;
		if(y^p)G[x].push_back(mkp(y,z)),dfs0(y,x);
	}
}
inline pair<pii,int>gm(pair<pii,int>a,pair<pii,int>b){
	return a.se<b.se?a:b;
}
inline ppp merge(ppp a,ppp b){
	vector<pii>tmp;
	tmp.push_back(a.fi),tmp.push_back(a.se),tmp.push_back(b.fi),tmp.push_back(b.se);
	sort(tmp.begin(),tmp.end(),[](pii a,pii b){return a.fi<b.fi;});
	ppp c;
	c.fi=tmp[0];
	if(tmp[0].se!=tmp[1].se)c.se=tmp[1];
	else c.se=tmp[2];
	return c;
}
void de(ppp a){
	printf("(%lld %lld, %lld %lld)\n",a.fi.fi,a.fi.se,a.se.fi,a.se.se);
}
void dfs1(int x){
	vector<ppp>pre,suf;
	f[x].resize(G[x].size()+1),pre.resize(G[x].size()),suf.resize(G[x].size());
	for(int i=0;i<G[x].size();i++){
		int y=G[x][i].first,z=G[x][i].second;
		dfs1(y);
		ppp tmp=f[y][G[y].size()],tmp2=mkp(mkp(w[y],find(y)),mkp(INF,0));
		tmp=merge(tmp,tmp2);
		tmp.fi.fi+=z,tmp.se.fi+=z; 
		pre[i]=(!i)?tmp:merge(pre[i-1],tmp);
	}
	for(int i=(int)G[x].size()-1;~i;i--){
		int y=G[x][i].first,z=G[x][i].second;
		ppp tmp=f[y][G[y].size()],tmp2=mkp(mkp(w[y],find(y)),mkp(INF,0));
		tmp=merge(tmp,tmp2);
		tmp.fi.fi+=z,tmp.se.fi+=z; 
		suf[i]=i==G[x].size()-1?tmp:merge(suf[i+1],tmp);
	}
	for(int i=0;i<G[x].size();i++){
		f[x][i]=merge((!i)?nu:pre[i-1],i==G[x].size()-1?nu:suf[i+1]);
	}
	f[x][G[x].size()]=G[x].size()?suf[0]:nu;
	
}
void dfs2(int x,int p,int pe,int pid){
	if(p){
		ppp tmp=f[p][pid],tmp2=mkp(mkp(w[p],find(p)),mkp(INF,0));
		tmp=merge(tmp,tmp2);
		tmp.fi.fi+=pe,tmp.se.fi+=pe;
		for(int i=0;i<=G[x].size();i++){
			f[x][i]=merge(f[x][i],tmp);
		}
	}
//	printf("%lld: ",x),de(f[x][G[x].size()]);
	if(f[x][G[x].size()].fi.fi<INF&&f[x][G[x].size()].fi.se!=find(x))mn[find(x)]=gm(mn[find(x)],mkp(mkp(find(x),f[x][G[x].size()].fi.se),f[x][G[x].size()].fi.fi+w[x]));
	else if(f[x][G[x].size()].se.fi<INF&&f[x][G[x].size()].se.se!=find(x))mn[find(x)]=gm(mn[find(x)],mkp(mkp(find(x),f[x][G[x].size()].se.se),f[x][G[x].size()].se.fi+w[x]));
	for(int i=0;i<G[x].size();i++){
		int y=G[x][i].first,z=G[x][i].second;
		dfs2(y,x,z,i);
	}
}
void Boruvka(){
	n_v=n_e=0;
	for(int i=0;i<=n;i++)f[i].clear(),mn[i]=mkp(mkp(0,0),INF);
	dfs1(1),dfs2(1,0,0,0);
	for(int i=1;i<=n;i++)if(find(mn[i].fi.fi)!=find(mn[i].fi.se))unite(mn[i].fi.fi,mn[i].fi.se),ans+=mn[i].se/*,printf("%lld %lld %lld\n",e[i].fi.fi,e[i].fi.se,e[i].se)*/;
//	puts("......");
	for(int i=1;i<=n;i++)bk[find(i)]=1;
	for(int i=1;i<=n;i++)n_v+=bk[i],bk[i]=0;
}
inline int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
signed main(){
//	freopen("input.in","r",stdin);freopen("output.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)w[i]=read(),fa[i]=i;
	for(int i=1,u,v,_w;i<n;i++){
		u=read(),v=read(),_w=read();
		adde(u,v,_w);
	}
	dfs0(1,0);
	n_v=n;
	for(int i=1;n_v>1;i++)Boruvka();
	cout<<ans;
}
```

---

## 作者：lahlah (赞：8)

首先有个显然的结论，对于一般图的MST（最小生成树），我们可以把**边集**分为两部分分别做最小生成树，然后再把两部分最小生成树的边拿出来再做一次最小生成树，得到的就是原图的最小生成树

证明很显然

直接算两个点的距离要用$lca$，我们可以发现$lca$一定在它们之间的路径上

于是我们就可以愉快地搞路径啦

对于经过重心的两个点的路径 u,v，它们的边长就是 $(w[u] + dis[u]) + (w[v]+dis[v])$,就是两个点到根（重心）的路径长+点的权值

然后发现

每个点$x$都是要加上自己的点权和到根的路径长$w[x]+dis[x]$，另外一边肯定是选最小的$w[y]+dis[y]$,所以这题直接找到子树中最小的$w[y]+dis[y]$再和其它点连边就好了


把这些边存下来，最后再跑一次$kruskal$ 就好了

一共$nlogn$条边，$O (n log^2n)$

看代码能看懂

code:
```cpp

#include<bits/stdc++.h>
#define N 2000005
#define int long long
#define ll long long
using namespace std;
struct edge {
	int v, nxt, c;
} e[N << 1];
int p[N], eid;
void init() {
	memset(p, -1, sizeof p);
	eid = 0;
}
void insert(int u, int v, int c) {
	e[eid].v = v;
	e[eid].c = c;
	e[eid].nxt = p[u];
	p[u] = eid ++;
}
int l, r, a[N], size[N], msize[N], vis[N], w[N], dis[N], szz;
void dfs(int u, int fa) {
	msize[u] = 0;
	a[++ r] = u; size[u] = 1;
	for(int i = p[u]; i + 1; i = e[i].nxt) {
		int v = e[i].v, c = e[i].c;
		if(vis[v] || v == fa) continue;
		dfs(v, u);
		size[u] += size[v];
		if(size[v] > msize[u]) msize[u] = size[v];
	}
}
void dfss(int u, int fa, ll sum) {
	dis[u] = sum; 
	for(int i = p[u]; i + 1; i = e[i].nxt) {
		int v = e[i].v, c = e[i].c;
		if(v == fa || vis[v]) continue;
		dfss(v, u, sum + c);
	}
}
struct AA {
	int u, v; ll c;
} ee[N << 3];
void solve(int u) { 
	l = 1, r = 0;
	dfs(u, u);
	int sz = size[u];
	for(int i = 1; i <= r; i ++) {
		int v = a[i];
		if(max(msize[v], sz - size[v]) < max(msize[u], sz - size[u])) u = v;
	}
	dis[u] = 0;
	vis[u] = 1;
	for(int i = p[u]; i + 1; i = e[i].nxt) {
		int v = e[i].v;
		if(vis[v]) continue;
		dfss(v, u, e[i].c);
	}
	int ma = u;
	for(int i = l; i <= r; i ++) {
		int v = a[i];
		if(dis[v] + w[v] < dis[ma] + w[ma]) ma = v;		
	}
	for(int i = l; i <= r; i ++) {
		int v = a[i];
		if(v == ma) continue;
		ee[++ szz] = {ma, v, w[ma] + w[v] + dis[v] + dis[ma]};
	}
	
	for(int i = p[u]; i + 1; i = e[i].nxt) {
		int v = e[i].v;
		if(vis[v]) continue;
		solve(v);
	}
}
int cmp(AA x, AA y) {
	return x.c < y.c;
}
int fa[N], n;
int get(int x) {
	return fa[x] == x ? x : fa[x] = get(fa[x]);
}
signed main() {
	init();
	scanf("%lld", &n);
	for(int i = 1; i <= n; i ++) scanf("%lld", &w[i]), fa[i] = i;
	for(int i = 2; i <= n; i ++) {
		int u, v, c;
		scanf("%lld%lld%lld", &u, &v, &c);
		insert(u, v, c);
		insert(v, u, c);
	}
	solve(1); 
	sort(ee + 1, ee + 1 + szz, cmp);
	ll ans = 0;
	for(int i = 1; i <= szz; i ++) {
		int u = ee[i].u, v = ee[i].v; ll c = ee[i].c;
		u = get(u), v = get(v);
		if(u == v) continue;
		fa[u] = v; ans += c;
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：5)

求完全图的最小生成树，立刻想到 Boruvka。

于是剩下的任务是，对于每个点 $x$，找到**当前和它不在同一连通块**的点 $y$ 的 $F(x, y) = w_y + dis_{x, y}$ 的最小值。

如果没有 $x, y$ 所在连通块不同的限制，可以很轻易地换根 dp 完成。先自下而上求出 $y$ 在子树内的 $F(x, y)$ 最小值，再自上而下求出 $y$ 在子树外 $F(x, y)$ 最小值。

加上了这个限制，我们除了求每个 $x$ 的 $F(x, y)$ 最小值和它对应的 $y$，还要求次小值和它对应的 $y$。需要注意我们强制规定最小值和次小值对应的 $y$ 当前所在连通块不同。这样如果 $x$ 跟最小值的 $y$ 在同一连通块，就可以让次小值递补。

时间复杂度 $O(n \log n)$。

[code](https://atcoder.jp/contests/cf17-final/submissions/44213307)

---

## 作者：Pengzt (赞：4)

**[cnblogs](https://www.cnblogs.com/Pengzt/p/17834730.html)**

**[洛谷](https://www.luogu.com.cn/problem/AT_cf17_final_j) [AT](https://atcoder.jp/contests/cf17-final/tasks/cf17_final_j)**

完全图的最小生成树是不好求的，但是发现 $\mathcal{O}(n^2)$ 级别的边中显然有很多都是没有用的，这种时候可以考虑分治。

显然如果对 $E'(E'\in E)$ 求 MST，没有选择的边一定也不在最后的 MST 的边集中。于是就让选出的边集的并等于原图，然后再求一遍 MST 即可，考虑点分治。

点分治时，记当前的重心为 $r'$，当前的分治树为 $T'$。若此时各个儿子的子树已经处理完，记为 $T_1,T_2,\dots,T_i$，再在这个基础上添加 $i - 1$ 条边就行了。考虑把这条 $i\to j$ 的路径拆成 $i\to p$ 和 $p\to j$ 这两段考虑，其中 $p$ 是 $i, j$ 在点分树上的 LCA。令 $val_i = d_i+ w_i$，$d_i$ 表示点 $i$ 到 $r'$ 的距离，按照 $val_i$ 排序即可。正确性是显然的，因为点分树上两点的 LCA 一定在原树中这两个点的路径上。

此时的边数是 $\mathcal{O}(n\log n)$ 的，故时间复杂度为 $\mathcal{O}(n\log^2n)$，瓶颈源于排序。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector < int >
#define eb emplace_back
#define pii pair < ll, int >
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
int Mbe;
mt19937_64 rng(35);
constexpr int N = 2e5 + 10;
int n, rt, cnt;
ll ans;
int a[N], mx[N], sz[N], vis[N], fa[N];
int head[N], cnt_e;
struct edge {
	int to, w, nxt;
} e[N << 1];
struct graph {
	int u, v;
	ll w;
} g[N << 5];
void adde(int u, int v, int w) {
	++cnt_e, e[cnt_e].to = v, e[cnt_e].w = w, e[cnt_e].nxt = head[u], head[u] = cnt_e;
}
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
void findroot(int u, int fath, int num) {
	sz[u] = 1, mx[u] = 0;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == fath || vis[v]) continue;
		findroot(v, u, num);
		sz[u] += sz[v];
		mx[u] = max(mx[u], sz[v]);
	}
	mx[u] = max(mx[u], num - sz[u]);
	if(mx[u] < mx[rt]) rt = u;
}
int tp;
pii stk[N];
void getdep(int u, int fath, ll val) {
	stk[++tp] = pii(a[u] + val, u);
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == fath || vis[v]) continue;
		getdep(v, u, val + e[i].w);
	}
}
void divide(int u) {
	vis[u] = 1;
	stk[++tp] = pii(a[u], u);
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(vis[v]) continue;
		getdep(v, u, e[i].w);
	}
	sort(stk + 1, stk + tp + 1);
	for(int i = 2; i <= tp; ++i)
		++cnt, g[cnt].u = stk[1].se, g[cnt].v = stk[i].se, g[cnt].w = stk[1].fi + stk[i].fi;
	tp = 0;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(vis[v]) continue;
		rt = 0;
		findroot(v, u, sz[v]);
		divide(rt);
	}
}
int Med;
int main() {
	fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
	ios :: sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	for(int i = 1; i < n; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		adde(u, v, w);
		adde(v, u, w);
	}
	mx[0] = N;
	findroot(1, 0, n);
	divide(rt);
	for(int i = 1; i <= n; ++i) fa[i] = i;
	sort(g + 1, g + cnt + 1, [](graph a, graph b){
		return a.w < b.w;
	});
	for(int i = 1; i <= cnt; ++i) {
		int u = find(g[i].u), v = find(g[i].v);
		if(u != v) fa[u] = v, ans += g[i].w;
	}
	cout << ans << "\n";
	cerr << TIME << "ms\n";
	return 0;
}
```

---

## 作者：BINYU (赞：4)

## 题意

给定一棵既有点权也有边权的树，构造一个完全图，图中两点间边的边权为树中两点点权之和加上两点间的距离，求该图的最小生成树。

## 思路

发现完全图总边数太大，考虑减少边数。

这里有一个性质：

如果在一个图中选取任意个联通的边集，使得它们的并为全集，则整个图的最小生成树中的边一定在 分割后的两个边集的最小生成树中出现。

证明：

假设有一条边 $(u,v)$ 在全图的最小生成树中却不在分割后的边集中，那么在包含 $(u,v)$ 的边集中一定存在一条连接 $(u,v)$ 的链，而这一定不比 $(u,v)$ 劣，否则 $(u,v)$ 一定可以替换这条链中的某一条边而成为最小生成树的一部分。

考虑优化建边：对于树上每个点，我们要让在新图中的包含这个点的边期望不超过 $O(\log n)$ 条，才能够求整个图的最小生成树。

记 $u$ 的点权为 $w_u$，$u$ 和 $v$ 在树上的距离为 $dis_{u,v}$

那么 $u$ 和 $v$ 在完全图中的边权就为 $w_u + w_v + dis_{u,v}$。

发现这个式子不是很对称，考虑把 $dis_{u,v}$ 拆了。

考虑从最近公共祖先处拆，此时这个式子可以写成 $w_u + dis_{u,lca} + w_v + dis_{v,lca}$，最小生成树显然是从 $w_u + dis_{u,lca}$ 最小的 $u$ 连向其他点，至于两个点在同一个子树内的情况，则会在该子树中算出更小的边权，不会影响答案。

但这样最坏复杂度还是 $O(n^2)$ 的，考虑换个位置差：点分树上最近公共祖先，这样复杂度就是 $O(n\log n)$ 的。

所以最终做法为：跑点分治，对于每个子树建完边后跑一边最小生成树即可。

---

## 作者：WESTRAIN (赞：2)

- [AT3611 Tree MST](https://www.luogu.com.cn/problem/AT3611)
  
  要求一棵树的最小生成树，可以把其分成两个边集，A 与 B，那么对于 A , B 分别求一遍 MST，再将选择的边合并做一次 MST ，显然即为原树的 MST。
  
  依据此结论，我们将本题的树进行点分治，设  $p[u]$ = $dis[u]+w[u]$  ,找出子树内 $ p[u] $ 最小的点，与剩余其他点连边，显然这便是当前树的最小生成树。
  
  那么将所有这样的边合并在一起，总边数为 $n \log n$ ，做一遍 kruskal，即为要求的最小生成树，时间复杂度为 $\mathcal O(n \log^2 n)$ 。
 


**Code**

&nbsp;
```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long h,t,k,fa[2000005],cnt,d[2000005],ans[2000001],q[2000005],b[2000005],mini,siz[2000005],max_siz[2000005],vis[2000005],w[2000005],p[2000005];
struct Edge{
	long long to,val;
}; 
vector<Edge> v[2000005];
struct MinE {
	long long u,v,val;
} e[5000005];
void dfs0(long long u) {
	q[++t]=u;
	vis[u]=1;
	siz[u]=max_siz[u]=1;
	for(long long i=0;i<v[u].size();i++) {
		long long to=v[u][i].to,val=v[u][i].val;
		if(vis[to]) continue;
		dfs0(to);
		siz[u]+=siz[to];
		max_siz[u]=max(max_siz[u],siz[to]);
	}
	vis[u]=0;
}
void dfs1(long long u) {
	q[++t]=u;
	vis[u]=1;	
	p[u]=d[u]+w[u]; 
	for(long long i=0;i<v[u].size();i++) {
		long long to=v[u][i].to,val=v[u][i].val;
		if(vis[to]) continue;
		d[to]=d[u]+val;
		dfs1(to);
	}
	if(mini>p[u]) {k=u,mini=p[u];}
	vis[u]=0;
}
void clear() {
	for(int i=1;i<=t;i++) d[q[i]]=p[q[i]]=0;
}
void solve(long long u) { 
	h=1,t=0;
	dfs0(u);
	mini=1000000000000000;long long s=siz[u];
	for(long long i=1;i<=t;i++) {
		long long v=q[i];
		long long g=max(max_siz[v],s-siz[v]);
		if(g<mini) {
			mini=g;
			u=v;
		}
	}
	
	vis[u]=1;
	h=1,t=0;
	d[u]=0;
	p[u]=w[u];
	mini=p[u],k=u;
	for(long long i=0;i<v[u].size();i++) {
		long long to=v[u][i].to,val=v[u][i].val;
		if(vis[to]) continue;
		d[to]=d[u]+val;
		dfs1(to);		
	}
	q[++t]=u;
	for(long long i=1;i<=t;i++) {
		if(k!=q[i]) e[++cnt].u=k,e[cnt].v=q[i],e[cnt].val=p[k]+p[q[i]];
	}
	clear();
	for(long long i=0;i<v[u].size();i++) {
		long long to=v[u][i].to;
		if(vis[to]) continue;
		solve(to);
	}
}
bool cmp(MinE a,MinE b) {
	return a.val<b.val;
}
long long find(long long x) {
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
int main() {
	ios::sync_with_stdio(false);
	cin>>n;
	for(long long i=1;i<=n;i++) cin>>w[i];
	for(long long i=1;i<n;i++) {
		long long a,b,c; cin>>a>>b>>c;
		v[a].push_back({b,c});
		v[b].push_back({a,c});
	}
	solve(1);
	
	long long ans=0;
	for(long long i=1;i<=n;i++) fa[i]=i;
	sort(e+1,e+1+cnt,cmp);
	for(long long i=1;i<=cnt;i++) { 
		long long u=e[i].u,v=e[i].v;
		long long f1=find(u),f2=find(v);
		if(f1==f2) continue;
		else {
			fa[f1]=f2,ans+=e[i].val;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Creeper_l (赞：1)

题意：给定一颗 $n$ 个点的树，点 $i$ 有权值 $a_{i}$，边有边权。现在有另外一个完全图，两点之间的边权为树上两点之间的距离加上树上两点的点权，求这张完全图的最小生成树。

首先有一个很显然的暴力，把完全图中每两点之间的边权算出来，然后跑一边最小生成树，时间复杂度 $O(n^{2} \log (n^{2}))$。

考虑如何优化。发现有很多路径是不必要的，因为它们一定劣于其它路径，这些路径我们就不用加到完全图中去了。那么可以用点分治来筛选路径。

假设当前重心为 $u$，我们可以把路径分为两种：

- 一个端点是 $u$ 的路径。

- 经过 $u$ 但是端点不在 $u$ 的路径。

对于第一种路径，我们可以直接将它加入边集，因为总边数不超过 $O(n \log n)$ 条。对于第二种，考虑如何选出最优的。假设两个点为 $x$ 和 $y$，那么可以把边权分为两个部分：$x \to u$，$u \to y$，即 $(a_{x}+dis(u,x))+(a_{y}+dis(u,y))$。发现这个式子的前一半和后一半的形式是一样的，所以要让边权最小，只需要选一个 $(a_{x}+dis(u,x))$ 最小的 $x$ 点，再连向其它所有的 $y$ 点即可。

总时间复杂度 $O(n \log^{2} n)$。

本题的 Trick：求最小生成树遇到边数很多时，可以先把边权小的边拿出来，删除一些没用的边，然后再做最小生成树。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f
#define inf_db 127
#define ls id << 1
#define rs id << 1 | 1
#define re register
#define endl '\n'
typedef pair <int,int> pii;
const int MAXN = 8e6 + 10;
int n,a[MAXN],head[MAXN],x,y,z,fa[MAXN],mn,id;
int pt,tot = 0,root,cnt,ans = 0;
bool vis[MAXN];
struct Node{int u,v,w,nxt;}e[MAXN << 1];
struct Edge{int u,v,w;}E[MAXN << 1];
struct F{int u,dis,idx;}p[MAXN << 1];
inline void Add(int u,int v,int w){e[++cnt] = {u,v,w,head[u]};head[u] = cnt;} 
inline int Get_size(int u,int father)
{
	if(vis[u] == true) return 0;
	int sum = 1;
	for(int i = head[u]; ~ i;i = e[i].nxt)
		if(e[i].v != father) sum += Get_size(e[i].v,u);
	return sum;
}
inline int Get_wc(int u,int father,int tot,int &wc)
{
	if(vis[u] == true) return 0;
	int sum = 1,mx = 0;
	for(int i = head[u]; ~ i;i = e[i].nxt)
	{
		int now = e[i].v;
		if(now == father) continue;
		int tmp = Get_wc(now,u,tot,wc);
		sum += tmp,mx = max(mx,tmp); 
	}
	if(max(mx,tot - sum) <= tot / 2) wc = u;
	return sum;
} 
inline void dfs(int u,int father,int dist,int r)
{
	if(vis[u] == true) return;
	int val = (a[u] + dist);
	p[++pt] = F{u,dist,r};
	if(val < mn) mn = val,id = u,root = r;
	for(int i = head[u]; ~ i;i = e[i].nxt)
	{
		int now = e[i].v;
		if(now == father) continue;
		dfs(now,u,dist + e[i].w,r);
	}
}
inline void solve(int u)
{
	if(vis[u] == true) return;
	Get_wc(u,0,Get_size(u,0),u),vis[u] = true;
	pt = 0,mn = 1e18,root = 0;
	for(int i = head[u]; ~ i;i = e[i].nxt)
	{
		int now = e[i].v;
		dfs(now,u,e[i].w,now);
	}
	for(int i = 1;i <= pt;i++)
		if(p[i].idx != root) E[++tot] = {id,p[i].u,mn + p[i].dis + a[p[i].u]};
	for(int i = 1;i <= pt;i++) E[++tot] = {u,p[i].u,p[i].dis + a[u] + a[p[i].u]};
	for(int i = head[u]; ~ i;i = e[i].nxt) solve(e[i].v); 
}
inline bool cmp(Edge x,Edge y){return x.w < y.w;}
inline int Find(int x)
{
	if(x == fa[x]) return x;
	return fa[x] = Find(fa[x]);
}
signed main()
{
	memset(head,-1,sizeof head);
	cin >> n;
	for(int i = 1;i <= n;i++) scanf("%lld",&a[i]);
	for(int i = 1;i < n;i++) scanf("%lld%lld%lld",&x,&y,&z),Add(x,y,z),Add(y,x,z);
	solve(1);
	sort(E + 1,E + tot + 1,cmp);
	for(int i = 1;i <= n;i++) fa[i] = i;
	for(int i = 1;i <= tot;i++)
		if(Find(E[i].u) != Find(E[i].v))
		{
			fa[Find(E[i].u)] = Find(E[i].v);
			ans += E[i].w;
		}
	cout << ans;
    return 0;
}



```


---

## 作者：541forever (赞：1)

首先我们发现在完全图上的边权若是在钦定经过一个点 $x$ 的情况下可以转换为 $dis_u + dis_v + w_u +
w_v$，$dis_i$ 是点 $x$ 到点 $i$ 的距离。这又可以转换为 $p_u + p_v$，$p_i$ 表示 $dis_i + w_i$，这就告诉我们这两个点的价值是可以分开算的。

而钦定一个点的过程就启示我们点分。考虑点分出一个分治重心后，首先我们知道只有在强制经过分治重心的情况下能成为最小生成树的边才有可能成为最终的最小生成树的边，接着，对于又因为每个点是独立的，所以强制经过分治重心情况下的最小生成树一定是选出一个最小
$p_i$，然后将其他与这个点不在一棵子树内的点与这个点连边，而子树内部经过分治重心一定不优，所以不连。

最后将所有侯选边提出来跑一遍 Kruskal 就做完了。考虑时间复杂度，首先我们点分了 $\log$ 层，每层连的边数又是 $O(n)$ 的，那么总的候选边数就是 $O
(n \log n)$，然后 Kruskal 的复杂度 $O (m \log n)$ 的，所以总复杂度是 $O (n \log^2 n)$ 的。

最后贴上丑陋的代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=200000,INF=0x3f3f3f3f;
int n,edgenum,ans,rt,head[MAXN+5],val[MAXN+5],si[MAXN+5],dist[MAXN+5],a[MAXN+5],num,b[MAXN+5],tot,fa[MAXN+5];
bool vis[MAXN+5];
inline int read(){
	int x=0,f=1;
	char ch;
	do{
		ch=getchar();
		if(ch=='-'){
			f=-1;
		}
	}while(!(ch>='0'&&ch<='9'));
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
struct Tree{
    int from,to,next,w;
}edge[2*MAXN+5];
struct Nedge{
    int from,to,w;
}nedge[20*MAXN+5];
void add_edge(int from,int to,int w){
    edge[++edgenum].next=head[from];
    edge[edgenum].from=from;
    edge[edgenum].to=to;
    edge[edgenum].w=w;
    head[from]=edgenum;
}
void get_root(int x,int f,int cnt){
    si[x]=1;
    int maxn=-INF;
    for(int i=head[x];i;i=edge[i].next){
        int v=edge[i].to;
        if(v==f||vis[v]){
            continue;
        }
        get_root(v,x,cnt);
        si[x]+=si[v];
        maxn=max(maxn,si[v]);
    }
    maxn=max(maxn,cnt-si[x]);
    if(maxn<ans){
        ans=maxn;
        rt=x;
    }
}//求重心
void dfs(int x,int f,int from){
    a[++num]=x;
    b[x]=from;
    si[x]=1;
    for(int i=head[x];i;i=edge[i].next){
        int v=edge[i].to;
        if(v==f||vis[v]){
            continue;
        }
        dist[v]=dist[x]+edge[i].w;
        dfs(v,x,from);
        si[x]+=si[v];
    }
}
void solve(){
    vis[rt]=1;
    dist[rt]=0;
    num=0;
    a[++num]=rt;
    b[rt]=rt;
    for(int i=head[rt];i;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]){
            continue;
        }
        dist[v]=edge[i].w;
        dfs(v,rt,v);
    }
    int pos=rt,minx=INF;
    for(int i=1;i<=num;++i){
        if(val[a[i]]+dist[a[i]]<minx){
            minx=val[a[i]]+dist[a[i]];
            pos=a[i];
        }
    }
    for(int i=1;i<=num;++i){
        if(b[a[i]]!=b[pos]){
            nedge[++tot].from=pos;
            nedge[tot].to=a[i];
            nedge[tot].w=dist[pos]+val[pos]+dist[a[i]]+val[a[i]];//将候选边存下来
        }
    }
    for(int i=head[rt];i;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]){
            continue;
        }
        ans=INF;
        get_root(v,v,si[v]);//继续点分下去
        solve();
    }
}//点分
bool cmp(Nedge x,Nedge y){
    return x.w<y.w;
}
int find(int x){
    if(fa[x]==x){
        return x;
    }
    return fa[x]=find(fa[x]);
}
signed main(){
    n=read();
    for(int i=1;i<=n;++i){
        val[i]=read();
    }
    for(int i=1;i<n;++i){
        int x=read();
        int y=read();
        int w=read();
        add_edge(x,y,w);
        add_edge(y,x,w);
    }
    ans=INF;
    get_root(1,1,n);
    solve();
    sort(nedge+1,nedge+tot+1,cmp);
    for(int i=1;i<=n;++i){
        fa[i]=i;
    }
    ans=0;
    for(int i=1;i<=tot;++i){
        int x=nedge[i].from;
        int y=nedge[i].to;
        x=find(x);
        y=find(y);
        if(x!=y){
            fa[x]=y;
            ans+=nedge[i].w;
        }
    }//Kruskal
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：Others (赞：1)

为什么我感觉我的淀粉质和大家的打法不一样，而且常数这么大......

# 前置知识

kruskal 最小生成树算法。

# Solution

**先普及淀粉质：**

在一类和树上路径有关的问题里，可以用点分治。

既然是分治，我们就先考虑原来的树。可以把路径分成两类：通过根的路径和没通过根的路径。第二类路径我们递归处理，只考虑通过根的路径。可以发现，任意两个不同子树上的点的距离就是他们到根的距离之和，为了不统计同一个子树上的路径，可以维护每个点属于根的哪一棵子树。预处理好后再处理问题。

我们每次选根选树的重心，这样可以做到 $O(\log n)$ 层的分治，剩下的合理处理就行了。

**做法：**

~~不会真的有人暴力吧......~~

观察到本题的输入结构是树，需要维护的东西是树上的路径且子树对应的最小生成树和上根节点肯定还是最小生成树，所以考虑点分治。

对于这题有一个很显然的**性质**：在合并时需要加入的路径只能是根到子树上的节点，有了这一点就很简单了。先把子树对应的最小生成树搞出来，然后把根节点到所有点的路径与子树对应的最小生成树的路径合并，然后就是板板。

个人感觉有点恶评。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define int long long
#define wr(x,ch) write(x),putchar(ch)
using namespace std;
namespace IO{
	
}
using IO::read;
using IO::write;
const int N=200005;
ll sum,head[N],nxt[N<<1],flag[N],cnt,to[N<<1],w[N<<1],fa[N],f[N],siz[N],Min,Minn,d[N],a[N],ans[N],n,u,v,ww,W[N],tto[N<<1];
struct edge {
	ll u,v,w;
	bool operator<(const edge &p) const {
		return w<p.w;
	}
};
vector<edge> vec[N],tmp;
void add(int u,int v,int ww) {
	nxt[++cnt]=head[u],to[head[u]=cnt]=v,w[cnt]=ww;
}
void init_0(int p) {
	sum++;
	for(int i=head[p];i;i=nxt[i]) 
		if(!flag[to[i]]&&to[i]!=fa[p]) fa[to[i]]=p,init_0(to[i]);
}
void init(int p) {
	siz[p]=1;
	ll tmp=0;
	for(int i=head[p];i;i=nxt[i]) 
		if(!flag[to[i]]&&to[i]!=fa[p]) init(to[i]),siz[p]+=siz[to[i]],tmp=max(tmp,siz[to[i]]);
	if(max(tmp,sum-tmp)<Min) Min=max(tmp,sum-tmp),Minn=p;
}
void dfs(int p,ll dis,int top) {
	d[p]=dis+W[p];
	if(top!=-1) a[++sum]=p;
	for(int i=head[p];i;i=nxt[i]) {
		if(to[i]!=fa[p]&&!flag[to[i]]) {
			fa[to[i]]=p;
			if(top==-1) dfs(to[i],dis+w[i],to[i]);
			else dfs(to[i],dis+w[i],top);
		}
	}
}
bool cmp(int x,int y) {
	return d[x]<d[y];
}
int get(int x) {
	return x==f[x]?x:f[x]=get(f[x]);
}
int fz(int p) {
	Min=0x7f7f7f7f,Minn=0,fa[p]=0,sum=0;
	init_0(p),init(p);
	p=Minn,flag[p]=1,fa[p]=0;
	for(int i=head[p];i;i=nxt[i]) if(!flag[to[i]]) tto[i]=fz(to[i]);
	sum=0;
	dfs(p,0,-1);
	sort(a+1,a+sum+1,cmp);
	tmp.clear();
	for(int i=head[p];i;i=nxt[i]) if(tto[i]&&!flag[tto[i]]) for(auto &lxl:vec[tto[i]]) tmp.push_back(lxl);
	for(int i=2;i<=sum;i++) tmp.push_back((edge){a[1],a[i],d[a[1]]+d[a[i]]});
	for(int i=1;i<=sum;i++) tmp.push_back((edge){p,a[i],d[a[i]]+d[p]}),f[a[i]]=a[i];
	sort(tmp.begin(),tmp.end());
	f[p]=p;int op1,op2,op3;
	for(auto &lxl:tmp) {
		op1=get(lxl.u),op2=get(lxl.v),op3=lxl.w;
		if(op1==op2) continue;
		f[op1]=op2;
		ans[p]+=op3;
		vec[p].push_back(lxl);
	}
	flag[p]=0;
	return p;
}
signed main() {
//	freopen("data.in","r",stdin);
	n=read();
	for(int i=1;i<=n;i++) W[i]=read();
	for(int i=1;i<n;i++) u=read(),v=read(),ww=read(),add(u,v,ww),add(v,u,ww);
	int ttmp=fz(1); 
//	for(auto &lxl:vec[ttmp]) printf("%d %d %d\n",lxl.u,lxl.v,lxl.w);
	wr(ans[ttmp],'\n');
	return 0;
}
```

---

## 作者：LinkyChristian (赞：1)

~~xpp杂题清除计划~~

这题和[P8207 [THUPC2022 初赛] 最小公倍树](https://www.luogu.com.cn/problem/P8207)有点像，都可以用优化选边的 kruskal 解决。

很显然，对于一张边数为 $n^2$ 级别的完全图，直接做 kruskal 的复杂度时 $O(n^2logn^2)$ 的，显然过不了。

但是也正是因为这是一张完全图，所以我们可以用一个定理来解决问题。

> 定理：对于任意一张完全图 $G=(V,E)$ ，选取数个边集 $(E_1,E_2,E_3,...,E_k)$ 使其完全覆盖边集 $E$ 。对每个集合 $E_i$ 求最小生成树，得到边集 $E_{MST_{i}}$ 。再对 $E_{MST_{1}},E_{MST_{2}},E_{MST_{3}},...,E_{MST_{k}}$ 求最小生成树，其最小生成树一定也是 $E$ 的最小生成树。

证明：考虑反证。假设最终图有一种比用 $E_{MST_{1}},E_{MST_{2}},E_{MST_{3}},...,E_{MST_{k}}$ 建出来的最小生成树更小的生成树，则该树一定有一条边 $(u,v)$ 不被包含在任何的 $E_{MST_i}$ 中。考虑这条边所属的一个或多个边集，在该边集中一定有一条连接 $(u,v)$ 的链，且此链一定不比 $(u,v)$ 更劣。因此在最终的最小生成树中用该链替代 $(u,v)$ 一定不会更劣。与该生成树比 $E_{MST_{1}},E_{MST_{2}},E_{MST_{3}},...,E_{MST_{k}}$ 建出来的最小生成树更小矛盾。

因此考虑淀粉质，假设我们以当前的分治中心 $rt$ 为根，设每个点的权值 $p_i$ 为 $dis_{rt,i} + w_i$ ，则对于不同子树的两个点，他们连边的权值为 $p_i+p_j$ 。考虑两两不同子树内的点之间连边组成的边集，设 $p_i$ 最小的 $i$ 为 $mn$ ，则这个边集的最小生成树一定为 $\sum_{i \in V} p_i+p_{mn}$ （这里的证明珂以参考一下 kruskal 算法正确性的证明），因此将淀粉质得到的所有边 $(i,mn)$ 加入边集，再做一次最小生成树就是 $G=(V,E)$ 的最小生成树了。

$Code$

```cpp
#include<bits/stdc++.h>
#define N 200010
using namespace std;
typedef long long ll;
int n,en;
ll w[N],INF=1e18;
int cnt,head[N],to[N<<1],nxt[N<<1];
ll val[N<<1];
int S,son[N],siz[N],vis[N],rt;
struct edge{
	int u,v;
	ll w;
	const bool operator < (const edge o) const {return w<o.w;}
}e[N<<4];
void insert(int u,int v,int w) {
	cnt++;
	to[cnt]=v;
	val[cnt]=w;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
int read() {
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)) f=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch)) res=res*10+ch-'0',ch=getchar();
	return f*res;
}
void gtrt(int now,int fa) {
    siz[now]=1,son[now]=0;
    for(int i=head[now]; i; i=nxt[i]) if(to[i]!=fa&&!vis[to[i]]) {
    	gtrt(to[i],now);
    	siz[now]+=siz[to[i]];
    	son[now]=max(son[now],siz[to[i]]);
    }
    son[now]=max(son[now],S-siz[now]);
    if(son[now]<son[rt]) rt=now;
}
ll sk[N];
int id[N],tp,mn;
void dfs(int now,int fa,ll dis) {
	sk[++tp]=w[now]+dis,id[tp]=now;
	if(sk[tp]<sk[mn]) mn=tp;
	for(int i=head[now]; i; i=nxt[i]) if(!vis[to[i]]&&to[i]!=fa) 
		dfs(to[i],now,dis+val[i]);
}
void solve(int now) {
	vis[now]=1;
    tp=mn=0,dfs(now,0,0);
	for(int i=1; i<=tp; i++) if(i!=mn) e[++en]=edge{id[i],id[mn],sk[i]+sk[mn]}; 
	int tmp=S;
	for(int i=head[now]; i; i=nxt[i]) if(!vis[to[i]]) {
	    S=siz[to[i]]<siz[now]?siz[to[i]]:tmp-siz[now];
	    rt=0,gtrt(to[i],now),solve(rt);
	}
}
int fa[N];
int find(int x) {
	while(fa[x]!=x) x=fa[x]=fa[fa[x]];
	return x;
}
int main()
{
	n=read();
	for(int i=1; i<=n; i++) w[i]=read();
	for(int i=1; i<n; i++) {
		int u=read(),v=read(),w=read();
		insert(u,v,w);
		insert(v,u,w);
	}
	S=son[0]=n,rt=0,gtrt(1,0),sk[0]=INF;
	solve(rt);
	for(int i=1; i<=n; i++) fa[i]=i;
	sort(e+1,e+en+1);int tot=0;ll sum=0;
	for(int i=1; i<=en; i++) {
		int u=find(e[i].u),v=find(e[i].v);
		if(u!=v) fa[u]=v,tot++,sum+=e[i].w;
		if(tot==n-1) {printf("%lld",sum);return 0;}
	}
	return 0;
}
```

~~我是不会说我开 nlogn 的数组只开了 n*4 导致错了好几发的~~


---

## 作者：asuldb (赞：1)

[题目](https://www.luogu.org/problemnew/show/AT3611)

这个题的输入首先就是一棵树，我们考虑一下点分

我们对于每一个分治重心考虑一下跨过这个分治重心的连边情况

就是把当前分治区域内所有的点向距离分治重心最近的点连边

考虑一下这个算法的正确性，如果我们已经对一个联通块内部形成了一个$mst$，我们需要把这个联通块和另外一个联通块合并

如果这个新的联通块出现会使得原来联通块的$mst$改变，那么**新出现的边也只会是原来联通块的点和新联通块到这个点距离最近的点之间的边**，而这些最近的点又都是一个，所以我们就可以大大简化连边数量了

所以这个点分的过程就相当于合并$mst$的过程

我们点分之后发现我们连了大概$nlogn$条边，于是再跑一个kruskal就好了，复杂度$O(nlog^2n)$

代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define re register
#define LL long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
inline int read() {
	char c=getchar();int x=0;while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
const int maxn=2e5+5;
struct E{int v,nxt,w;}e[maxn<<1];
struct Edge{int a,b;LL c;}E[maxn*55];
int sum[maxn],vis[maxn],head[maxn],mx[maxn],a[maxn],fa[maxn],sz[maxn];
int n,num,m,dx,S,rt;LL dw,ans,pre[maxn];
inline void add(int x,int y,int z) {
	e[++num].v=y;e[num].nxt=head[x];head[x]=num;e[num].w=z;
}
void getroot(int x,int fa) {
	sum[x]=1,mx[x]=0;
	for(re int i=head[x];i;i=e[i].nxt) {
		if(vis[e[i].v]||e[i].v==fa) continue;
		getroot(e[i].v,x);sum[x]+=sum[e[i].v];
		mx[x]=max(mx[x],sum[e[i].v]);
	}
	mx[x]=max(mx[x],S-sum[x]);
	if(mx[x]<mx[rt]) rt=x;
}
void getdis(int x,int fa) {
	E[++m]=(Edge){dx,x,pre[x]+a[x]+dw};
	for(re int i=head[x];i;i=e[i].nxt) {
		if(vis[e[i].v]||e[i].v==fa) continue;
		getdis(e[i].v,x);
	}
}
void chk(int x,int fa) {
	if(pre[x]+a[x]<dw) dw=pre[x]+a[x],dx=x;
	for(re int i=head[x];i;i=e[i].nxt) {
		if(vis[e[i].v]||e[i].v==fa) continue;
		pre[e[i].v]=pre[x]+e[i].w;chk(e[i].v,x);
	}
}
void dfs(int x) {
	dx=x,dw=a[x];vis[x]=1;pre[x]=0,chk(x,0),getdis(x,0);
	for(re int i=head[x];i;i=e[i].nxt) {
		if(vis[e[i].v]) continue;
		S=sum[e[i].v],rt=0,getroot(e[i].v,0),dfs(rt);
	}
}
inline int cmp(Edge A,Edge B) {return A.c<B.c;}
inline int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]);}
inline int merge(int x,int y) {
	int xx=find(x),yy=find(y);
	if(xx==yy) return 0;
	if(sz[xx]<sz[yy]) fa[xx]=yy,sz[yy]+=sz[xx];
		else fa[yy]=xx,sz[xx]+=sz[yy];
	return 1;
}
int main() {
	n=read();
	for(re int i=1;i<=n;i++) a[i]=read();
	for(re int x,y,z,i=1;i<n;i++) 
		x=read(),y=read(),z=read(),add(x,y,z),add(y,x,z); 
	mx[0]=n+1,S=n,rt=0,getroot(1,0),dfs(rt);
	std::sort(E+1,E+m+1,cmp);
	for(re int i=1;i<=n;i++) sz[i]=1,fa[i]=i;
	for(re int i=1;i<=m;i++) if(merge(E[i].a,E[i].b)) ans+=E[i].c;
	std::cout<<ans;
	return 0;
}
```


---

## 作者：happybob (赞：0)

一个有趣的结论是，一个图，选出若干个边集，满足他们的并为原图边集。则必有他们每个集合的 MST 的边的并，再求一次 MST 为原图的 MST。

考虑点分治，设当前重心为 $u$，设 $d_j = w_j + dist(u,j)$，则有对于两个点 $u,v$，其完全图上边权 $\leq d_u + d_v$。

每次分治时，把 $d$ 的最小值求出，将这个点和所有其他在分治树内的点连边，最后求 MST 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

constexpr int N = 2e5 + 5, M = N * 20;

int n;
vector<int> w;
vector<vector<pair<int, int>>> G;
vector<int> dis, sz;
bitset<N> del;

struct Edge
{
	int u, v, w;
	Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w){}
	Edge(){}
};

vector<Edge> eg;
set<pair<int, int> > cv;
int tot, wc;

auto get_sz(int u, int f) -> void
{
	sz[u] = 0;
	if (del[u]) return;
	sz[u] = 1;
	for (auto &j : G[u])
	{
		if (j.first != f)
		{
			get_sz(j.first, u);
			sz[u] += sz[j.first];
		}
	}
}

auto get_wc(int u, int f) -> void
{
	if (del[u]) return;
	int maxn = tot - sz[u];
	for (auto &j : G[u])
	{
		if (j.first ^ f)
		{
			get_wc(j.first, u);
			maxn = max(maxn, sz[j.first]);
		}
	}
	if (maxn <= (tot >> 1)) wc = u; 
}

vector<int> total;

auto get_dist(int u, int f, int w) -> void
{
	dis[u] = 0;
	if (del[u]) return;
	total.emplace_back(u);
	dis[u] = dis[f] + w;
	for (auto &j : G[u])
	{
		if (j.first != f)
		{
			get_dist(j.first, u, j.second);
		}
	}
}

auto solve(int u) -> void
{
	if (del[u]) return;
	cv.clear();
	get_sz(u, 0);
	tot = sz[u];
	wc = u;
	get_wc(u, 0);
	u = wc;
	del[u] = 1;
	dis[u] = 0;
	for (auto &j : G[u])
	{
		if (del[j.first]) continue;
		total.clear();
		total.shrink_to_fit();
		get_dist(j.first, u, j.second);
		vector<pair<int, int> > djb;
		for (auto &k : total)
		{
			dis[k] += w[k];
			djb.emplace_back(make_pair(dis[k], k));
		}
		for (auto &k : djb)
		{
			cv.insert(make_pair(k.first, k.second));
		}
	}
	for (auto it = cv.begin(); it != cv.end(); ++it)
	{
		if (it != cv.begin())
		{
			eg.emplace_back(Edge((*it).second, (*(cv.begin())).second, (*it).first + (*(cv.begin())).first));
		}
		eg.emplace_back(u, (*(it)).second, (*it).first + w[u]);
	}
	for (auto &j : G[u]) solve(j.first);
}

class Union_Find
{
public:
	vector<int> fa;
	auto Init() -> void
	{
		fa.resize(n + 1);
		for (int i = 0; i <= n; i++) fa[i] = i;
	}
	auto find(int u) -> int
	{
		return (fa[u] == u ? u : fa[u] = find(fa[u]));
	}
	auto merge(int u, int v) -> void
	{
		fa.at(find(u)) = find(v);
	}
}uf;

auto main() -> signed
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	del.reset();
	w.resize(n + 1);
	dis.resize(n + 1);
	sz.resize(n + 1);
	G.resize(n + 1);
	for (int i = 1; i <= n; i++) cin >> w[i];
	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		G[u].emplace_back(make_pair(v, w));
		G[v].emplace_back(make_pair(u, w)); 
	}
	solve(1);
	uf.Init();
	long long ans = 0LL;
	sort(eg.begin(), eg.end(), [&](const Edge& x, const Edge& y){return x.w < y.w;});
	for (int i = 0; i < eg.size(); i++)
	{
		auto p = eg.operator[](i);
		if (uf.find(p.u) ^ uf.find(p.v))
		{
			ans += p.w;
			uf.merge(p.u, p.v);
		}
	}
	cout << ans << "\n";
	return 0;
}
```


---

## 作者：wcyQwQ (赞：0)

关于 MST，有一个性质，就是把原图的边权拆成很多个部分，然后分别做 MST，新得到的边的集合的 MST 还是原图的 MST。

那么我们就可以尝试着拆边集了。我们考虑点分治，这样可以不漏掉树上任意路径构成的边集，考虑求出经过当前分支中心 $u$ 所有路径对应的 MST，我们记 $v$ 距离 $u$ 的距离为 $d_v$，那么两个点 $i, j$ 所对应的边权即为 $(w_i + d_i) + (w_j + d_j)$，所以我们求出 $w_i + d_i$ 最小的点 $i$，然后其他点向 $i$ 连边即可，但这样我们会把一些不合法的路径加进去，但是我们在继续对子树进行分治时会得到一些更优的边，所以不用管。

点分治选出来的边是 $O(n\log n)$ 的，所以总的时间复杂度为 $O(n\log^2n)$。[Code](https://atcoder.jp/contests/cf17-final/submissions/43750858)

---

## 作者：Lates (赞：0)

注意到点数比边数少很多，考虑使用 Borůvka 算法。

边权为 $s_x+s_y-2\times s_{lca(x,y)} + w_x+w_y$ ，其中 $s_x$ 表示 $x$ 到根的距离和。

那么考虑对于每个 $x$，找到祖先某个点，钦定这个点是他们的最近公共祖先。此时维护最近公共祖先为根子树内某点 $y$ 的 $s_y+w_y$ 的最小值。这个可以 dp 出来。

至于为什么钦定是对的，是因为如果实际上 最小的 $y$ 与 $x$ 的最近公共祖先不是这个点的话，那答案必然劣于真正最近公共祖先的答案。

Borůvka 算法，要找到属于不同联通块的一条最小的边，合并，并加入答案。

由于 $x,y$ 可能属于一个连通块。dp 的时候可以重载一个类，存最小值和次小值。并限定他们不同属于一个连通块。

有了 dp 值以后，第二次遍历求出 $x$ 答案（这里答案指 $x$ 到不同联通块的最短边），可以贪心地考虑，考虑 最小值和 $x$ 是否在一个连通块。不是就考虑次大值。 容易证明记录两个不同连通块的值，总能与任意 $x$ 形成不同属于一个连通块 这个效果。

然后取一个连通块里面每个点答案（与上文定义一样）的最小值，合并。


[评测记录1](https://atcoder.jp/contests/cf17-final/submissions/33407605)

[评测记录2](https://atcoder.jp/contests/cf17-final/submissions/33407678)


---

## 作者：FutaRimeWoawaSete (赞：0)

看着这个式子，挺简单的，拆一下：

$w_x + w_y + dis_{x,y}$

枚举 lca：

$= w_x + w_y + (dep_x + dep_y - 2 \times dep_{lca})$

直接合并下标相同的项：

$= (w_x + dep_x) + (w_y + dep_y) - 2 \times dep_{lca}$

以下将一个点 $x$ 的值称为 $(w_x + dep_x)$。

考虑对于每个点 $x$，考虑当它作为 lca 时的答案，维护子树内异色的最小的两个点的值并时刻更新答案，我们每次模仿 Kruskal 找边权最小的两个点并启发式合并改颜色，可以通过优秀的 DDP 做到 $O(n \log ^ 3 n)$ 的时间复杂度，显然过不了。

考虑边多，但边具有统一的计算格式。联想到另外一种求最小生成树的 Boruvka 算法：我们考虑对于每个点当作 $x$ 寻找使 $x$ 固定时使上述式子最小的一个 $y$，而这个东西我们显然可以先将 $x$ 子树内的点找一下最小值，然后做一遍换根 dp 得到每个点 $x$ 对应的 $y$。

接着就可以模拟 Boruvka 算法了，挺 ez 的。

注意我们应该同时维护子树内两种颜色的点的最小值。

代码实现的很烂，常数有亿点大，好像还跑不过点分树，挺尬的。

时间复杂度 $O(n \log n)$。

```cpp
/*
什么阴间。
我日，树边也带权，这么厉害的吗
根据一般原则我们拆拆拆
轻松写出一个 LCA 相关式子，盲猜是在 LCA 处统计答案
先把 (w_x - dep_x) 放在一起，找到子树内没有相连的两个点
感觉可以直接线段树模拟？好像有亿点难写
貌似是 O(n \log n a(n)) 的，就维护不在同一集合内的最小的两个点？
我日这得暴力改 LCA，问题大了，直接起飞 
貌似可以只在两个点的 LCA 处改一下？但是确实好像要并查集
DDP
After reading the solution
好，可以直接换根 dp，没看出来不谢 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5 , Inf = 2e9;
const long long Lnf = 1e17;
int n,m;
long long dep[Len],w[Len];
struct node
{
	int col,x;
	long long res;
	node(){col = x = Inf , res = Lnf;}
	node(int COL,int X,long long RES){col = COL , x = X , res = RES;}
	inline void clear(){col = x = Inf , res = Lnf;}
	bool operator < (const node &Ano) const
	{return res < Ano.res;}
};
struct Node
{
	node ts[2];
	Node(){ts[0].clear() , ts[1].clear();}
	Node(node x,node y){ts[0] = x , ts[1] = y;}
	inline void clear(){ts[0].clear() , ts[1].clear();}
	Node operator ^ (const Node &Ano) const//(Ans merge)
	{
		Node z;
		if(ts[0].res < Ano.ts[0].res) 
		{
			z.ts[0] = ts[0];
			if(Ano.ts[0].col == ts[0].col) z.ts[1] = min(ts[1] , Ano.ts[1]);
			else z.ts[1] = min(ts[1] , Ano.ts[0]);
		}
		else
		{
			z.ts[0] = Ano.ts[0];
			if(Ano.ts[0].col == ts[0].col) z.ts[1] = min(ts[1] , Ano.ts[1]);
			else z.ts[1] = min(ts[0] , Ano.ts[1]);
		}
		return z;
	}
}s[Len],pre[Len],suf[Len],p[Len];
int col[Len];
void makeSet(int x){for(int i = 1 ; i <= x ; i ++) col[i] = i;}
int findSet(int x){return col[x] == x ? col[x] : col[x] = findSet(col[x]);}
void unionSet(int x,int y)
{
	int u = findSet(x) , v = findSet(y);
	if(u == v) return;
	col[u] = v;
} 
struct edge
{
	int to;long long w;
	edge(){to = w = 0;}
	edge(int TO,long long W){to = TO , w = W;}
};
vector<edge> G[Len];void add(int from,int to,long long w){G[from].push_back(edge(to , w));}
vector<edge>::iterator it;
void dfs(int x,int f)
{
	int i = -1;
	for(it = G[x].begin() ; it != G[x].end() ; it ++)
	{
		i ++;
		int to = G[x][i].to;
		if(to == f)
		{
			G[x].erase(it);
			break;
		}
	}
	for(int i = 0 ; i < G[x].size() ; i ++)
	{
		int to = G[x][i].to;
		dep[to] = dep[x] + G[x][i].w;
		dfs(to , x);
	}
}
void dfs1(int x)//更新 w_x - dep_x 在子树内的最小的两个颜色 
{
	s[x] = Node(node(col[x] , x , w[x] + dep[x]) , node(Inf , Inf , Lnf));
	for(int i = 0 ; i < G[x].size() ; i ++)
	{
		int to = G[x][i].to;
		dfs1(to);
		s[x] = s[x] ^ s[to];
	}
}
void dfs2(int x)//更新每个点对应的 ans 
{
	for(int i = 0 ; i < G[x].size() ; i ++) 
	{
		int to = G[x][i].to;
		if(i) pre[to] = pre[G[x][i - 1].to];
		pre[to] = pre[to] ^ (Node(node(s[to].ts[0].col , s[to].ts[0].x , -dep[x] * 2 + s[to].ts[0].res) , node(s[to].ts[1].col , s[to].ts[1].x , -dep[x] * 2 + s[to].ts[1].res)));
	}
	for(int i = G[x].size() - 1 ; i >= 0 ; i --)
	{
		int to = G[x][i].to;
		if(i != G[x].size() - 1) suf[to] = suf[G[x][i + 1].to];
		suf[to] = suf[to] ^ (Node(node(s[to].ts[0].col , s[to].ts[0].x , -dep[x] * 2 + s[to].ts[0].res) , node(s[to].ts[1].col , s[to].ts[1].x , -dep[x] * 2 + s[to].ts[1].res)));
	}
	for(int i = 0 ; i < G[x].size() ; i ++)
	{
		int to = G[x][i].to;
		Node pz;
		if(i) pz = pz ^ pre[G[x][i - 1].to];
		if(i != G[x].size() - 1) pz = pz ^ suf[G[x][i + 1].to];
		p[to] = p[x] ^ pz ^ Node(node(col[x] , x , -dep[x] * 2 + w[x] + dep[x]) , node(Inf , Inf , Lnf));
		dfs2(to);
	}
}
node ms[Len];
void upd()
{
	for(int i = 1 ; i <= n ; i ++) 
	{
		s[i] = Node(node(s[i].ts[0].col , s[i].ts[0].x , -dep[i] * 2 + s[i].ts[0].res) , node(s[i].ts[1].col , s[i].ts[1].x , -dep[i] * 2 + s[i].ts[1].res));
		s[i] = s[i] ^ p[i];
		if(s[i].ts[0].col == col[i]) ms[col[i]] = min(ms[col[i]] , node(s[i].ts[1].col , s[i].ts[1].x , w[i] + dep[i] + s[i].ts[1].res));
		else ms[col[i]] = min(ms[col[i]] , node(s[i].ts[0].col , s[i].ts[0].x , w[i] + dep[i] + s[i].ts[0].res));
	}
}
int main()
{
	long long ans = 0;
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) scanf("%lld",&w[i]);
	for(int i = 1 ; i < n ; i ++)
	{
		int x,y,w;scanf("%d %d %d",&x,&y,&w);
		add(x , y , w);
		add(y , x , w);
	}	
	dfs(1 , 0);
	int Cnt = n;
	makeSet(n);
	while(Cnt > 1)
	{
		for(int i = 1 ; i <= n ; i ++)
		{
			s[i].clear();
			pre[i].clear();
			suf[i].clear();
			p[i].clear();
			ms[i].clear();
		}
		dfs1(1);
		dfs2(1);
		upd();
		for(int i = 1 ; i <= n ; i ++)
		{
			int x = findSet(col[i]);
			if(ms[x].x == Inf) continue;
			if(findSet(x) != findSet(ms[x].x)) 
			{
				Cnt --;
				ans += ms[x].res;
				unionSet(x , ms[x].x);
			}
		}
		for(int i = 1 ; i <= n ; i ++) col[i] = findSet(col[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

