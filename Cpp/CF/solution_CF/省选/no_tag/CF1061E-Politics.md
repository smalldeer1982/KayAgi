# Politics

## 题目描述

有 $n$ 个城市。

两位候选人正在竞争总统职位。选举将在未来举行，两位候选人都已经规划好了如何用道路连接这些城市。每份规划都只使用 $n-1$ 条道路连接所有城市。也就是说，每份规划都可以看作是一棵树。两位候选人还分别指定了他们心目中的首都（第一位候选人选择第 $x$ 个城市，第二位候选人选择第 $y$ 个城市），这两个城市可以相同也可以不同。

每个城市都有建设港口的潜力（每个城市最多只能建一个港口）。在第 $i$ 个城市建设港口可以获得 $a_i$ 的收益。然而，每位候选人都有自己的具体要求。要求的形式如下：

- $k$ $x$，表示候选人希望在他所选树（以他选择的首都为根）的第 $k$ 个城市的子树内，恰好建设 $x$ 个港口。

请你计算，在满足两位候选人所有要求的前提下，最多可以获得多少收益。如果无法满足所有要求，则输出 $-1$。

另外保证，每位候选人都对自己选择的首都提出了港口建设要求。

## 说明/提示

在第一个样例中，最优方案是在城市 $2$、$3$ 和 $4$ 建设港口，满足了两位候选人的所有要求，收益为 $2 + 3 + 4 = 9$。

在第二个样例中，最优方案是在城市 $2$ 和 $3$ 建设港口，满足了两位候选人的所有要求，收益为 $99 + 99 = 198$。

在第三个样例中，无法在满足两位候选人所有要求的前提下建设港口，因此答案为 $-1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 1 2
1 2 3 4
1 2
1 3
3 4
1 2
2 3
1 4
2
1 3
4 1
1
2 3
```

### 输出

```
9```

## 样例 #2

### 输入

```
5 1 1
3 99 99 100 2
1 2
1 3
3 4
3 5
1 3
1 2
2 4
2 5
2
1 2
3 1
2
1 2
2 1
```

### 输出

```
198```

## 样例 #3

### 输入

```
4 1 2
1 2 3 4
1 2
1 3
3 4
2 1
2 4
4 3
1
1 4
2
4 1
2 4
```

### 输出

```
-1```

# 题解

## 作者：Durant_Lee (赞：2)

[欢迎来我的博客逛逛](https://blog.csdn.net/Dream_Lolita/article/details/86185723)

这题的实质上就是将点分成若干个集合，每个集合必须激活一定数量的点，使得权最大，一看就是费用流啊。


令$x_i$为第$i$个节点的需求（子树中至少需要多少个），我们考虑这样连边


- 对于树$1$中每个有需求节点$i$，我们从$S$向$i$连费用为$0$，容量为$x_i-\sum x_j$，其中$j\neq i,j$在$i$子树内。

- 对于树$2$中每个有需求节点$i$，我们从$i$向$T$连费用为$0$，容量为$x_i-\sum x_j$，其中$j\neq i,j$在$i$子树内。


- 对于$i$在两棵树中的向上走到最近有限制的点（包括自己）$fa_1,fa_2$，从$fa_1$向$fa_2$连费用为$a_i$，容量为$1$的边。

跑最大费用流即可。

若$S$连出去的流量不等于连向$T$的流量或不满流则一定不能满足所有要求。

考虑这样连边的意义？我们在子树内的选择不会往根的父亲贡献，同时限制了子树的需求。


【参考代码】
```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;

const int N=1010,M=2e6+10;
const int INF=0x3f3f3f3f;
int n,ans,in,out,Q,a[N];

int read()
{
	int ret=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) ret=ret*10+(c^48),c=getchar();
	return ret;
}
void failed(){puts("-1");exit(0);}

namespace Flow
{
	int S=0,T=N-5,tot=1,mxflow;
	int head[N],fr[N],dis[N],inq[N],ins[N];
	queue<int>q;
	struct Tway
	{
		int u,v,nex,w,c;
		Tway(int _u=0,int _v=0,int _nex=0,int _w=0,int _c=0):u(_u),v(_v),nex(_nex),w(_w),c(_c){}
	}e[M];
	void addedege(int u,int v,int w,int c)
	{
		e[++tot]=Tway(u,v,head[u],w,c);head[u]=tot;
		e[++tot]=Tway(v,u,head[v],0,-c);head[v]=tot;
		//printf("%d %d %d %d\n",u,v,w,c);
	}
	bool spfa()
	{
		memset(dis,-0x3f,(T+2)<<2);memset(inq,0,(T+2)<<2);
		dis[S]=0;q.push(S);inq[S]=1;fr[T]=-1;
		while(!q.empty())
		{
			int u=q.front();q.pop();inq[u]=0;
			for(int i=head[u];i;i=e[i].nex)
			{
				int v=e[i].v;
				if(e[i].w && dis[u]+e[i].c>dis[v])
				{
					dis[v]=dis[u]+e[i].c;fr[v]=i;
					if(!inq[v]) q.push(v),inq[v]=1;
				}
			}
		}
		return ~fr[T];
	}
	void mcfx()
	{
		while(spfa()) 
		{
			int mi=INF;
			for(int i=fr[T];i;i=fr[e[i].u]) mi=min(mi,e[i].w); 
			for(int i=fr[T];i;i=fr[e[i].u]) ans+=e[i].c*mi,e[i].w-=mi,e[i^1].w+=mi;
			mxflow+=mi;
		}
	}
}

namespace Tree
{
	struct Tway{int v,nex;};
	struct Tree
	{
		int rt,tot,b[N],bl[N],head[N];
		Tway e[N<<1];
		vector<int>vec[N];
		void add(int u,int v)
		{
			e[++tot]=(Tway){v,head[u]};head[u]=tot;
			e[++tot]=(Tway){u,head[v]};head[v]=tot;
		}
		int dfs(int x,int fa,bool f)
		{
			int sum=0;vec[x].pb(x);
			for(int i=head[x];i;i=e[i].nex)
			{
				int v=e[i].v;
				if(v==fa) continue;
				sum+=dfs(v,x,f);
				for(int i=0;i<(int)vec[v].size();++i)vec[x].pb(vec[v][i]);
			}
			if(b[x])
			{
				if(b[x]<sum) failed();
				if(!f) Flow::addedege(Flow::S,x,b[x]-sum,0),in+=b[x]-sum;
				else Flow::addedege(x+n,Flow::T,b[x]-sum,0),out+=b[x]-sum;
				for(int i=0;i<(int)vec[x].size();++i) bl[vec[x][i]]=x;
				vec[x].clear();return b[x];
			}
			return sum;
		}
	}T[2];
}
using namespace Tree;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("CF1061E.in","r",stdin);
	freopen("CF1061E.out","w",stdout);
#endif
	n=read();T[0].rt=read();T[1].rt=read();
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<n;++i) T[0].add(read(),read());
	for(int i=1;i<n;++i) T[1].add(read(),read());
	Q=read();for(int i=1,x;i<=Q;++i)x=read(),T[0].b[x]=read();
	Q=read();for(int i=1,x;i<=Q;++i)x=read(),T[1].b[x]=read();
	T[0].dfs(T[0].rt,0,0);T[1].dfs(T[1].rt,0,1);
	for(int i=1;i<=n;++i) Flow::addedege(T[0].bl[i],T[1].bl[i]+n,1,a[i]);
	if(in^out) failed();
	Flow::mcfx(); if(Flow::mxflow^in) failed();
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Arghariza (赞：1)

感觉有些题解的建图方式过于抽象，提供一个正常人能想出来的做法。

先把两棵树的限制分开。假如现在只有一棵树，由于限制是关于子树的，也就是只有包含和无交两种关系，于是我们可以把所有对子树的限制，转化为对若干个不交连通块的限制，且这些连通块的并集为 $\{1,2,\cdots,n\}$。

转化后的第 $i$ 条限制形如 $(lim_i,U_i)$，其中 $U_i$ 表示被限制的点集，并且必须从这个点集内选恰好 $lim_i$ 个点。所有限制的 $U_i$ 的并集为 $\{1,2,\cdots,n\}$。

把所有限制转化后，再把两棵树放在一起。考虑如下建图（$(u,v,x,y)$ 表示 $u$ 向 $v$ 连一条容量为 $x$，费用为 $y$ 的边）：

- 建立超级源点 $S$ 以及超级汇点 $T$。
- 对第一棵树的每条限制 $(lim_i,U_i)$ 新建点 $q_i$。
- 对第二棵树的每条限制 $(lim'_i,U'_i)$ 新建点 $q'_i$。
- 对每个点 $u$ 分别建两个点 $X_u,Y_u$ 表示分别在两棵树中。
- 对第一棵树的每条限制 $(lim_i,U_i)$，连边 $(S,q_i,lim_i,0)$；对 $\forall u\in U_i$，连边 $(q_i,X_u,1,0)$。
- 对每个点 $u$，连边 $(X_u,Y_u,1,a_u)$。
- 对第二棵树的每条限制 $(lim'_i,U'_i)$，连边 $(q'_i,T,lim'_i,0)$；对 $\forall u\in U'_i$，连边 $(Y_u,q'_i,1,0)$。

直接求 $S$ 到 $T$ 的最大费用最大流，如果最大流没有达到所有限制的点数之和则无解；否则答案就是最大费用。

不难理解连边方式正确。

```cpp
// Problem: E. Politics
// Contest: Codeforces - Codeforces Round 523 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1061/E
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define R(i, x, y) for (int i = (x); i >= (y); i--)
#define FIO(FILE) freopen(FILE".in", "r", stdin), freopen(FILE".out", "w", stdout)

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
bool Mbe;

struct Flow {
	const int inf = 0x3f3f3f3f;
	int n, s, t, tot;
	struct edge { int to, nxt, w, c; };
	vector<int> hd, cr, d, vs;
	vector<edge> e;
	Flow () { }
	Flow (int _n) : n(_n), tot(-1) { hd.resize(n + 5, -1), d.resize(n + 5), vs.resize(n + 5), e.clear(); }
	void add_edge(int u, int v, int w, int c) { e.eb((edge) { v, hd[u], w, c }), hd[u] = ++tot; }
	void add_flow(int u, int v, int w, int c) { add_edge(u, v, w, c), add_edge(v, u, 0, -c); }
	bool spfa() {
		fill(d.begin(), d.end(), -inf);
		queue<int> q; q.push(s), d[s] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop(), vs[u] = 0;
			for (int i = hd[u]; ~i; i = e[i].nxt) {
				int v = e[i].to;
				if (!e[i].w) continue;
				if (d[v] < d[u] + e[i].c) {
					d[v] = d[u] + e[i].c;
					if (!vs[v]) q.push(v), vs[v] = 1;
				}
			}
		}
		return d[t] != -inf;
	}
	int dfs(int u, int in) {
		if (u == t) return in;
		vs[u] = 1;
		int out = 0;
		for (int &i = cr[u]; ~i; i = e[i].nxt) {
			int v = e[i].to;
			if (e[i].w && !vs[v] && d[v] == d[u] + e[i].c) {
				int res = dfs(v, min(in, e[i].w));
				e[i].w -= res, e[i ^ 1].w += res;
				in -= res, out += res;
			}
			if (!in) break;
		}
		vs[u] = 0;
		return out;
	}
	pi dinic() {
		int mc = 0, mf = 0;
		while (spfa()) {
			cr = hd;
			int res = dfs(s, inf);
			mc += res * d[t], mf += res;
		}
		return mp(mf, mc);
	}
};

const int N = 505;
const int M = 2e3 + 5;

int n, q1, q2;
int a[N];

struct Tree {
	int rt, res, lim[N];
	vector<int> G[N], p;
	vector<pair<int, vector<int>>> q;
	void add(int u, int v) { G[u].eb(v), G[v].eb(u); }
	void gt(int u, int f) {
		p.eb(u);
		for (int v : G[u]) {
			if (v == f) continue;
			if (!lim[v]) gt(v, u);
			else res -= lim[v];
		}
	}
	void dfs(int u, int f) {
		if (lim[u]) {
			p.clear(), res = lim[u], gt(u, f);
			if (res < 0) cout << -1 << '\n', exit(0);
			q.eb(mp(res, p));
		}
		for (int v : G[u]) 
			if (v != f) dfs(v, u);
	}
} T1, T2;

void solve() {
	cin >> n >> T1.rt >> T2.rt;
	F (i, 1, n) cin >> a[i];
	F (i, 1, n - 1) { int u, v; cin >> u >> v, T1.add(u, v); }
	F (i, 1, n - 1) { int u, v; cin >> u >> v, T2.add(u, v); }
	cin >> q1; F (i, 1, q1) { int x, y; cin >> x >> y, T1.lim[x] = y; }
	cin >> q2; F (i, 1, q2) { int x, y; cin >> x >> y, T2.lim[x] = y; }
	int _ = T1.lim[T1.rt];
	if (T2.lim[T2.rt] != _) return cout << -1 << '\n', void();
	T1.dfs(T1.rt, 0), T2.dfs(T2.rt, 0);
	Flow G(2 * n + q1 + q2 + 2); G.s = 2 * n + q1 + q2 + 1, G.t = 2 * n + q1 + q2 + 2;
	int cur = 2 * n;
	for (auto p : T1.q) {
		int lim = p.fi;
		vector<int> nd = p.se;
		cur++, G.add_flow(G.s, cur, lim, 0);
		for (int u : nd) G.add_flow(cur, u, 1, 0);
	}
	for (auto p : T2.q) {
		int lim = p.fi;
		vector<int> nd = p.se;
		cur++, G.add_flow(cur, G.t, lim, 0);
		for (int u : nd) G.add_flow(u + n, cur, 1, 0);
	}
	F (i, 1, n) G.add_flow(i, i + n, 1, a[i]);
	pi res = G.dinic();
	if (res.fi != _) cout << -1 << '\n';
	else cout << res.se << '\n';
}


bool Med;
int main() {
	// FIO("");
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：1)

对于每个节点，我们可以找到其祖先中深度最高且被限制的节点。这样我们就可以把一棵树划分为若干节点集合，同时有对于每个集合需要选择指定数量的节点的限制。

考虑如何处理这两组限制，考虑建出网络，若网络的流量可以流满那么就代表着存在方案。

对于第一棵树的每个限制 $\left(x_i, k_i\right)$，设其代表 $x_i$ 所代表的集合要恰好存在 $k_i$ 个节点被选择，那么我们可以建一条边 $S \rightarrow x_{i, 1}$，容量为 $k_i$。对于第二棵树的每个限制 $\left(x_i, k_i\right)$，我们可以建一条边 $x_{i, 2} \rightarrow T$，容量为 $k_i$。

接下来处理节点的对应关系，对于每个节点 $i$，我们设其在第一棵树上属于点 $l_i$，在第二棵树上属于点 $r_i$，那么我们可以建边 $l_i \rightarrow r_i$，容量为 $1$。

接下来考虑如何最大化收益，我们可以使用最大费用最大流，对于节点所属集合之间的连边加上其对应的收益即可。

---

## 作者：Nuisdete (赞：1)

考虑一个 naive 的建图方式。

对于第一棵树，我们从上向下建图，对于第二棵树，我们从下往上建图，边的容量就是当前点的子树限制条件。

然后第一棵树中的点向第二课树对应的点连边，容量为 $1$，价值为当前点对应的的价值，源点连向第一棵树的根，第二棵树的根连向汇点。

跑最大费用最大流即可，无解只需要判每条有子树限制的边是否满流即可。

但是交上去发现假了，因为它可能不往有限制的边流。

但是无所谓，加个下界就真了。

btw：题目翻译里没写根节点一定有限制，这个条件如果没有的话其它做法可能会挂，但是这个不会。/kx /kx /kx

```cpp
# include <cstdio>
# include <vector>
# include <algorithm>
# include <functional>

constexpr int N = 1e4 + 5;

int numE = 1;
std::vector<int> head(N), cur(N);

struct Edge {
  int nxt, to, cap, val;

  Edge() {}
  Edge(int N, int T, int C, int V) {
    nxt = N, to = T, cap = C, val = V;
  }
}; std::vector<Edge> edge(N);

void addE2(int x, int y, int cap, int val) {
  edge[++numE] = Edge(head[x], y, cap, val), head[x] = numE;
  edge[++numE] = Edge(head[y], x, 0, -val), head[y] = numE;
}

int s, t;

std::vector<int> dis(N);
std::vector<bool> vis(N);

bool spfa() {
  std::fill(dis.begin(), dis.end(), -1e9);
  std::fill(vis.begin(), vis.end(), false);

  std::vector<int> que(N + 5);
  auto hd = que.begin(), tl = que.begin();

  *tl ++ = s, dis[s] = 0, vis[s] = true;

  while (hd != tl) {
    int u = *hd ++; vis[u] = false;
    if (hd - que.begin() > N) hd = que.begin();
    cur[u] = head[u];

    for (int i = head[u]; i; i = edge[i].nxt) {
      int k = edge[i].to;
      if (dis[k] < dis[u] + edge[i].val && edge[i].cap) {
        dis[k] = dis[u] + edge[i].val;
        if (!vis[k]) {
          *tl ++ = k, vis[k] = true;
          if (tl - que.begin() > N) tl = que.begin();
        }
      }
    } 
  }

  return dis[t] != -1e9;
}

int cst;

int dfs(int u, int flw) {
  if (u == t) return flw;
  int tot = 0; vis[u] = true;
  
  for (int& i = cur[u]; i; i = edge[i].nxt) {
    int k = edge[i].to;
    if (edge[i].cap && dis[k] == dis[u] + edge[i].val && !vis[k]) {
      int add = dfs(k, std::min(flw, edge[i].cap));
      if (!add) dis[k] = -1e9;
      edge[i].cap -= add, edge[i ^ 1].cap += add;
      tot += add, flw -= add, cst += add * edge[i].val;
      if (!flw) break;
    }
  }

  return vis[u] = false, tot;
}

int dinic() {
  int res = 0;

  while (spfa()) {
    int tmp;
    std::fill(vis.begin(), vis.end(), false);
    while ((tmp = dfs(s, 1e9))) res += tmp;
  }
  
  return res;
}

void solve() {

  int n, x, y;
  scanf("%d %d %d", &n, &x, &y);

  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

  std::vector<std::vector<int> > G1(n + 1), G2(n + 1);

  for (int i = 1; i < n; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    G1[x].push_back(y), G1[y].push_back(x);
  }

  for (int i = 1; i < n; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    G2[x].push_back(y), G2[y].push_back(x);
  }

  int m;
  scanf("%d", &m);

  std::vector<int> lim1(n + 1);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    lim1[x] = y;
  }

  scanf("%d", &m);
  
  std::vector<int> lim2(n + 1);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    lim2[x] = y;
  }

  std::vector<int> deg(n + 23 << 1 | 1);

  std::function<void(int, int)> dfs1 = [&](int u, int father) {
    for (int k : G1[u]) if (k != father) {
      dfs1(k, u);
      if (!lim1[k]) addE2(u, k, 1e9, 0);
      else deg[k] += lim1[k], deg[u] -= lim1[k];
    }
  };
  dfs1(x, 0);

  std::function<void(int, int)> dfs2 = [&](int u, int father) {
    for (int k : G2[u]) if (k != father) {
      dfs2(k, u);
      if (!lim2[k]) addE2(k + n, u + n, 1e9, 0);
      else deg[u + n] += lim2[k], deg[k + n] -= lim2[k];
    }
  };
  dfs2(y, 0);

  for (int i = 1; i <= n; ++i) {
    addE2(i, i + n, 1, a[i]);
  }

  s = 0, t = 2 * n + 1;
  deg[s] -= lim1[x], deg[x] += lim1[x];
  deg[y + n] -= lim2[y], deg[t] += lim2[y];

  int S = 2 * n + 2, T = 2 * n + 3;

  int tot = 0;
  for (int i = 0; i < n + 1 << 1; ++i) {
    if (deg[i] < 0) addE2(i, T, -deg[i], 0);
    if (deg[i] > 0) addE2(S, i, deg[i], 0), tot += deg[i];
  }

  addE2(t, s, 1e9, 0);

  s = S, t = T;

  if (dinic() < tot) 
    return puts("-1"), void();

  printf("%d\n", cst);
}

int main() {

  int T = 1;
  while (T --) solve();

  return 0;
}
```

---

## 作者：day_dream (赞：1)

我们发现，这些条件就是要在一些集合里面选一些数使选出来的权值和最大。

这就是一个最大费用流。

建模时，把点拆开，表示两棵树，每对点间连一条流量为1，费用为其权值的边。我们只需要对每棵树，每一个条件建一个点，向集合中的点连一条流量为1，费用为0的边然后把建出来的点连到源点/汇点就好了。

是否合法只要在跑完费用流后判一下满流即可。

(注意一开始要把存限制的数组初始化为-1，因为他可以限制为0)

```cpp
#include<algorithm>
#include<cstdio>
#include<deque>
#define mxn 510
using namespace std;
const int inf=1e9;
int n,m,N,S,T,sl,fh,rtx,rty;
int rd()
{
    sl=0;fh=1;
    char ch=getchar();
    while(ch<'0'||'9'<ch) {if(ch=='-') fh=-1; ch=getchar();}
    while('0'<=ch&&ch<='9') sl=sl*10+ch-'0',ch=getchar();
    return sl*fh;
}
namespace WLL
{
    #define inf 0x7fffffff
    #define pb push_back
    #define pf push_front
    #define ppf pop_front
    int ans,vis[mxn*10],dis[mxn*10];
    int t,h[mxn*10],cur[mxn*10];
    struct edge
    {
        int to,val,cap,nxt;
    }e[mxn*mxn];
    void init() {S=++N; T=++N; t=1;}
    void add(int u,int v,int c,int w)
    {
        if(c<0) return ;
        e[++t]=(edge){v,w,c,h[u]};h[u]=t;
        e[++t]=(edge){u,-w,0,h[v]};h[v]=t;
    }
    bool spfa()
    {
        fill(dis+1,dis+N+1,-inf);
        fill(vis+1,vis+N+1,0);
        deque<int> q;int u,v;
        q.pb(S);dis[S]=0;
        while(!q.empty())
        {
            u=q.front();q.ppf();
            for(int i=h[u];i;i=e[i].nxt)
                if(e[i].cap&&dis[v=e[i].to]<dis[u]+e[i].val)
                {
                    dis[v]=dis[u]+e[i].val;
                    if(vis[v]) continue;vis[v]=1;
                    if(!q.empty()&&dis[v]>=dis[q.front()]) q.pf(v);
                    else q.pb(v);
                }
            vis[u]=0;
        }
        return dis[T]>-inf;
    }
    int dfs(int u,int f)
    {
        vis[u]=1;if(u==T) return f;
        int v,q=0,tmp;
        for(int &i=cur[u];i;i=e[i].nxt)
            if(!vis[v=e[i].to]&&e[i].cap&&dis[v]==dis[u]+e[i].val)
            {
                tmp=dfs(v,min(f,e[i].cap));
                f-=tmp;q+=tmp;
                ans+=tmp*e[i].val;
                e[i].cap-=tmp;e[i^1].cap+=tmp;
                if(!f) return q;
            }
        return q;
    }
    void main()
    {
        while(spfa())
        {
            for(int i=1;i<=N;++i) cur[i]=h[i];vis[T]=1;
            while(vis[T]) fill(vis+1,vis+N+1,0),dfs(S,inf);
        }
        for(int i=h[S];i;i=e[i].nxt)
            if(e[i].cap)
            {
                puts("-1");
                return ;
            }
        for(int i=h[T];i;i=e[i].nxt)
            if(e[i^1].cap)
            {
                puts("-1");
                return ;
            }
        printf("%d\n",ans);
    }
}
struct Tre
{
    int id,flg,flow,a[mxn];
    int t,h[mxn];
    struct edge
    {
        int to,nxt;
    }e[mxn<<1];
    void init() {fill(a+1,a+n+1,-1);}
    void add(int u,int v)
    {
        e[++t]=(edge){v,h[u]};h[u]=t;
        e[++t]=(edge){u,h[v]};h[v]=t;
    }
    void dfs2(int u,int f)
    {
        if(a[u]>=0) {flow-=a[u]; return ;}
        if(flg) WLL::add(2*u,id,1,0);
        else WLL::add(id,2*u-1,1,0);
        for(int v,i=h[u];i;i=e[i].nxt)
            if((v=e[i].to)!=f)
                dfs2(v,u);
    }
    void dfs1(int u,int f)
    {
        for(int v,i=h[u];i;i=e[i].nxt)
            if((v=e[i].to)!=f)
                dfs1(v,u);
        if(a[u]>=0)
        {
            flow=a[u];id=++N;
            for(int v,i=h[u];i;i=e[i].nxt)
                if((v=e[i].to)!=f)
                    dfs2(v,u);
            if(flg) WLL::add(id,T,flow,0),WLL::add(u*2,id,1,0);
            else WLL::add(S,id,flow,0),WLL::add(id,u*2-1,1,0);
        }
    }
}Tx,Ty;
int main()
{
    n=rd();rtx=rd();rty=rd();int x,y;
    Ty.flg=1;N=n<<1;WLL::init();
    Tx.init();Ty.init();
    for(int i=1;i<=n;++i) x=rd(),WLL::add(i*2-1,i*2,1,x);
    for(int i=1;i<n;++i) x=rd(),y=rd(),Tx.add(x,y);
    for(int i=1;i<n;++i) x=rd(),y=rd(),Ty.add(x,y);
    m=rd();for(int i=1;i<=m;++i) x=rd(),Tx.a[x]=rd();
    m=rd();for(int i=1;i<=m;++i) x=rd(),Ty.a[x]=rd();
    Tx.dfs1(rtx,0);Ty.dfs1(rty,0);
    WLL::main();
    return 0;
}
```

---

## 作者：Miracle_1024 (赞：0)

### 思路：

考虑流量表示选的点个数，费用表示选点的收益，跑最大费用最大流。

那么我用一个点x表示某树中的询问点 $x$，刨去它子孙询问点的子树后的子树。

对于树 $1$，连边 $S\to x$，流量为 $x$ 的限定数-孩子询问的限定数，费用为 $0$。

对于树 $2$，连边 $x\to T$，流量为 $x$ 的限定数-孩子询问的限定数，费用为 $0$。

以限制数量。

之后对于每个点，给它在树 $1$ 中最近的询问祖先到树 $2$ 中最近的询问祖先 连边，流量为 $1$，费用为点权。

表示选这个点。

如果S的出流量和不等于 $T$ 的入流量和，或者最后没跑满，则说明无解。

### 代码:
```
#include<bits/stdc++.h>
#define CLR(a,x) memset(a,x,sizeof(a))
#define MP make_pair
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pa;
const int maxn=505;

inline ll rd(){
    ll x=0;char c=getchar();int neg=1;
    while(c<'0'||c>'9'){if(c=='-') neg=-1;c=getchar();}
    while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x*neg;
}

int teg[2][maxn*2][2],tegh[2][maxn],tect[2];
int dem[2][maxn],cfa[2][maxn],rt[2];
inline void adteg(int o,int a,int b){
    teg[o][++tect[o]][0]=b,teg[o][tect[o]][1]=tegh[o][a],tegh[o][a]=tect[o];
    teg[o][++tect[o]][0]=a,teg[o][tect[o]][1]=tegh[o][b],tegh[o][b]=tect[o];
}
struct Edge{
    int b,l,c,ne;
}eg[maxn*6];
int N,egh[maxn*2],ect=1,S=1004,T=1005;
int val[maxn],inl,outl;

inline void ext(){
    printf("-1\n");
    exit(0);
}

inline void adeg(int a,int b,int l,int c){
    if(a==S) inl+=l;
    if(b==T) outl+=l;
    eg[++ect]=(Edge){b,l,c,egh[a]},egh[a]=ect;
    eg[++ect]=(Edge){a,0,-c,egh[b]},egh[b]=ect;
}
inline int dfs(int o,int x,int f,int cl){
    if(dem[o][x]) cl=x;
    cfa[o][x]=cl;
    int n=0;
    for(int i=tegh[o][x];i;i=teg[o][i][1]){
        int b=teg[o][i][0];if(b==f) continue;
        n+=dfs(o,b,x,cl);
    }
    if(dem[o][x]){
        if(dem[o][x]<n) ext();
        if(o==0) adeg(S,x,dem[o][x]-n,0);
        else adeg(x+N,T,dem[o][x]-n,0);
        return dem[o][x];
    }return n;
}

queue<int> q;
int dis[maxn*2],ine[maxn*2];
bool flag[maxn*2];

inline bool spfa(){
    CLR(dis,-127);dis[S]=0;
    CLR(ine,0);q.push(S);
    while(!q.empty()){
        int p=q.front();q.pop();
        flag[p]=0;
        for(int i=egh[p];i;i=eg[i].ne){
            int b=eg[i].b;if(!eg[i].l) continue;
            if(dis[b]<dis[p]+eg[i].c){
                dis[b]=dis[p]+eg[i].c,ine[b]=i;
                if(!flag[b]) q.push(b),flag[b]=1;
            }
        }
    }return dis[T]>=-1e9;
}

int main(){
    int i,j,k;
    N=rd(),rt[0]=rd(),rt[1]=rd();
    for(i=1;i<=N;i++)
        val[i]=rd();
    for(i=1;i<N;i++) adteg(0,rd(),rd());
    for(i=1;i<N;i++) adteg(1,rd(),rd());
    for(i=rd();i;i--){
        int x=rd(),y=rd();
        dem[0][x]=y;
    }for(i=rd();i;i--){
        int x=rd(),y=rd();
        dem[1][x]=y;
    }
    dfs(0,rt[0],0,0);dfs(1,rt[1],0,0);
    for(i=1;i<=N;i++){
        adeg(cfa[0][i],cfa[1][i]+N,1,val[i]);
    }
    if(inl!=outl) ext();
    int ans=0;
    while(spfa()){
        int mi=1e9;
        for(i=T;i!=S;i=eg[ine[i]^1].b){
            mi=min(mi,eg[ine[i]].l);
        }ans+=mi*dis[T];
        inl-=mi;
        for(i=T;i!=S;i=eg[ine[i]^1].b){
            eg[ine[i]].l-=mi,eg[ine[i]^1].l+=mi;
        }
    }
    if(inl) ext();
    printf("%d\n",ans);
    return 0;
}
```


---

