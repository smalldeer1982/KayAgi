# Transitive Graph

## 题目描述

You are given a directed graph $ G $ with $ n $ vertices and $ m $ edges between them.

Initially, graph $ H $ is the same as graph $ G $ . Then you decided to perform the following actions:

- If there exists a triple of vertices $ a $ , $ b $ , $ c $ of $ H $ , such that there is an edge from $ a $ to $ b $ and an edge from $ b $ to $ c $ , but there is no edge from $ a $ to $ c $ , add an edge from $ a $ to $ c $ .
- Repeat the previous step as long as there are such triples.

Note that the number of edges in $ H $ can be up to $ n^2 $ after performing the actions.

You also wrote some values on vertices of graph $ H $ . More precisely, vertex $ i $ has the value of $ a_i $ written on it.

Consider a simple path consisting of $ k $ distinct vertices with indexes $ v_1, v_2, \ldots, v_k $ . The length of such a path is $ k $ . The value of that path is defined as $ \sum_{i = 1}^k a_{v_i} $ .

A simple path is considered the longest if there is no other simple path in the graph with greater length.

Among all the longest simple paths in $ H $ , find the one with the smallest value.

## 说明/提示

In the first test case, the longest path in both graphs is $ 1 \to 3 \to 4 \to 5 \to 2 $ . As the path includes all vertices, the minimal possible value of the longest path is the sum of values on all vertices, which is $ 12 $ .

In the second test case, the longest possible path is $ 1 \to 2 \to 3 \to 4 \to 6 \to 7 $ . As there are no longest paths with vertex $ 5 $ in them, this path has the minimal possible value of $ 5\,999\,999\,995 $ .

In the third test case, it can be proven that there is no path longer than $ 11 $ and that the value of the longest path cannot be less than $ 37 $ . Also, notice that the given graph has both self-loops and multiple edges.

## 样例 #1

### 输入

```
3
5 6
2 2 4 1 3
1 2
1 3
2 4
3 4
4 5
5 2
7 7
999999999 999999999 999999999 999999999 1000000000 999999999 1000000000
1 2
2 3
3 4
4 1
4 5
4 6
6 7
14 22
2 3 5 7 3 4 1 4 3 4 2 2 5 1
1 2
2 3
2 4
3 1
4 4
4 5
5 6
5 6
5 12
6 7
6 8
7 5
7 7
7 9
8 4
9 11
10 9
11 10
11 10
12 13
13 14
14 12```

### 输出

```
5 12
6 5999999995
11 37```

# 题解

## 作者：_Ink (赞：7)

其实这题简化过后就是一个很 typical 的题目了...

## 题解

这道题的思维量主要在于对题目所给信息的分析，即：

- 如果存在一条 $a$ 到 $b$ 的边，且存在一条 $b$ 到 $c$ 的边，那么你就可以建立一条 $a$ 到 $c$ 的边。

- 若新的图仍存在这种关系，便可以重复上述过程。

注意到第二条信息：**若新的图仍存在这种关系，便可以重复上述过程。** 不难想到，如果 $a$ 到 $b$ 有一条简单路径，那么 $a$ 就可以通过与路径上中间的点不断建边，最后与 $b$ 直接连接。

换句话说，如果 $a$ 可以到达 $b$，那么在建边操作后，$a$ 就可以直达 $b$。

由于题目要求我们走过的点数要尽量多，于是这里可以分两种情况讨论：

1. $a$ 可以到达 $b$，而 $b$ 无法到达 $a$。

显然，在建边后我们可以从 $a$ 直接到 $b$。但由于 $b$ 无法到达 $a$，那么 $a$ 到 $b$ 这条路径上的所有点肯定走不到了。

所以为了满足题意，在这种情况下，我们并不会走新加的边。

2. $a, b$ 可以互相到达。

$a,b$ 能互相到达，那么显然的是 $a$ 到 $b$ 路径上所有的点便组成了一个强连通分量。

而对于一个强连通分量中的所有点，其都是可以互相到达的。那么在建边操作后，强连通分量的点便都可以互相直达。**换言之，其内部组成为了一张完全图**。

组成为了完全图，我们便可以在该强连通分量中的任何一个点进入，遍历完内部的所有点后，再从任意一个点走出。

---

于是这就不难想到缩点了。

在缩完点后，图就变为了一张 DAG（有向无环图）。由讨论 1 可知，缩点后，我们实际上并不会走新加的边。所以实际在代码实现上我们也不需要真正地新加边。

那怎么走才能使得走过的点最多呢？我们显然要从入度为 0 的点开始走。

于是，剩下的求答案的部分就是一个很经典的 拓扑 + dp 的问题了。在具体的实现方法上，几乎可以说是和洛谷的模板题 [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387) 没有什么区别。而该题仅仅需要额外多处理一下“经过的点个数”这一个信息。这里就不再赘述了。

所以说...这道题可以说是缩点的模板练习题都不为过...

如果还有什么实现上的细节有问题，就看代码吧。

## $\text{Code:}$

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define maxn 200050
#define maxm 400050 
#define vi vector <int>
#define vvi vector <vi>
#define endl '\n'
#define ll long long
using namespace std;

struct Edge
{
	int head[maxn], nxt[maxm], to[maxm], cnt;
} e1, e2;

int n, m; 
int val[maxn];
int dfn[maxn], low[maxn], belong[maxn], tim, kn, valc[maxn];
ll valk[maxn];
bool vis[maxn];
int idg[maxn];
stack <int> s;

void clean()
{
	memset(e1.head, 0, sizeof(int)*(n + 5));
	memset(e2.head, 0, sizeof(int)*(n + 5));
	memset(dfn, 0, sizeof(int)*(n + 5));
	tim = 0, kn = 0;
	e1.cnt = e2.cnt = 0;
	memset(valc, 0, sizeof(int)*(n + 5));
	memset(valk, 0, sizeof(ll)*(n + 5));
	memset(idg, 0, sizeof(int)*(n + 5));
}

void add_edge(Edge &e, int u, int v)
{
	e.nxt[++ e.cnt] = e.head[u];
	e.head[u] = e.cnt;
	e.to[e.cnt] = v;
}

void tarjan(int x)
{
	dfn[x] = low[x] = ++ tim;
	vis[x] = true;
	s.push(x);
	for(int i = e1.head[x]; i; i = e1.nxt[i]){
		int y = e1.to[i];
		if(!dfn[y]){
			tarjan(y);
			low[x] = min(low[x], low[y]);
		}
		if(vis[y]) low[x] = min(low[x], dfn[y]);
	}
	if(dfn[x] == low[x]){
		++ kn;
		while(s.size()){
			int y = s.top(); s.pop();
			vis[y] = false;
			belong[y] = kn;
			valk[kn] += val[y];
			valc[kn] ++;
			if(x == y) break;
		}
	}
}

void solve()
{
	cin >> n >> m;
	clean();
	for(int i = 1; i <= n; i ++) cin >> val[i];
	for(int i = 1; i <= m; i ++){
		int u, v; cin >> u >> v;
		if(u == v) continue;
		add_edge(e1, u, v);
	}
	for(int i = 1; i <= n; i ++){
		if(!dfn[i]) tarjan(i);
	}
	
	for(int k = 1; k <= n; k ++){
		int u = belong[k];
		for(int i = e1.head[k]; i; i = e1.nxt[i]){
			int v = belong[e1.to[i]];
			if(u == v) continue;
			add_edge(e2, u, v);
			idg[v] ++;
		}
	}
	
	queue <int> q;
	vi dpc(kn + 1, 0);
	vector <ll> dp(kn + 1, 0);
	int mx = 0;
	for(int i = 1; i <= kn; i ++){
		if(!idg[i]) q.push(i), dp[i] = valk[i], dpc[i] = valc[i], mx = max(mx, dpc[i]);
	}
	ll ans = 1ll << 60;
	while(q.size()){
		int x = q.front(); q.pop();
		for(int i = e2.head[x]; i; i = e2.nxt[i]){
			int y = e2.to[i];
			idg[y] --;
			if(!idg[y]) q.push(y);
			if(dpc[y] < dpc[x] + valc[y]){
				dpc[y] = dpc[x] + valc[y];
				dp[y] = dp[x] + valk[y];
				mx = max(mx, dpc[y]);
			}
			else if(dpc[y] == dpc[x] + valc[y]){
				dp[y] = min(dp[y], dp[x] + valk[y]);
			}
		}
	}
	for(int i = 1; i <= kn; i ++){
		if(dpc[i] == mx) ans = min(dp[i], ans);
	}
	
	cout << mx << ' ' << ans << endl;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); //cout.tie(0);
	
	int t = 1;
	cin >> t; 
	while(t --) solve();
	
	return 0;
}
```

---

## 作者：Engulf (赞：3)

简单题，本人觉得比 D 简单。

首先我们没有必要按照题目的要求构建新图，因为我们要求的是最长的路径，既然我们能从 $a$ 到 $b$ 再到 $c$，肯定不可能走 $a$ 到 $c$ 而略过 $b$，这会使答案变小。

这是一个有向图，我们直接考虑 tarjan 求出强连通分量之后缩点，显然在一个强连通分量内的所有点都可以出现在我们的路径上，问题就变成了在一个 DAG 上面的最长路径问题，直接拓扑排序 dp 即可，更新长度的同时更新和的最小值，典。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e5 + 5;

int n, m;

int a[N];

vector<int> g[N], G[N];

int in[N], siz[N];

ll w[N];

int len[N];
ll cost[N];

stack<int> stk;
int scc[N], tot;
int dfn[N], low[N], tim;
bool ins[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    stk.push(u), ins[u] = 1;
    for (auto v: g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        int v;
        ++tot;
        do {
            v = stk.top();
            siz[tot]++;
            ins[v] = 0;
            w[tot] += a[v];
            scc[v] = tot;
            stk.pop();
        } while (v != u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1, x, y; i <= m; i++) {
            cin >> x >> y;
            g[x].emplace_back(y);
        }

        for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);

        for (int i = 1; i <= n; i++)
            for (auto j: g[i])
                if (scc[i] != scc[j]) {
                    G[scc[i]].emplace_back(scc[j]);
                    in[scc[j]]++;
                }

        queue<int> q;
        for (int i = 1; i <= tot; i++)
            if (!in[i]) {
                q.push(i);
                len[i] = siz[i];
                cost[i] = w[i];
            }

        int maxlen = 0;
        ll mincost = 1e18;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (len[u] > maxlen) {
                maxlen = len[u];
                mincost = cost[u];
            } else if (len[u] == maxlen)
                mincost = min(mincost, cost[u]);
            for (auto v: G[u]) {
                if (len[u] + siz[v] > len[v]) {
                    len[v] = len[u] + siz[v];
                    cost[v] = cost[u] + w[v];
                } else if (len[u] + siz[v] == len[v])
                    cost[v] = min(cost[v], cost[u] + w[v]);
                if (!--in[v])
                    q.push(v);
            }
        }

        cout << maxlen << " " << mincost << "\n";

        for (int i = 1; i <= tot; i++) {
            in[i] = len[i] = w[i] = siz[i] = 0;
            cost[i] = 1e18;
        }
        for (int i = 1; i <= n; i++) {
            dfn[i] = low[i] = 0;
            g[i].clear();
            G[i].clear();
        }
        tim = tot = 0;
    }
    return 0;
}
```

---

## 作者：BINYU (赞：2)

## 题意

给你一张有向图，点有点权，现进行以下操作直到无法进行：

选择两条首尾相连的边 $(a,b)$ 和 $(b,c)$ 且 $a$ 与 $c$ 间没边，添加边 $(a,c)$。

求操作完后图中最长的 **不经过重复点的路径**，并求这种路径中经过的点的点权和最小值。

## 思路

先考虑 DAG 上的问题，发现这个操作是无用的：走一条边肯定不如走两条边更优。所以这个操作的作用只有：

1. 让一个 SCC 变成完全图。

2. 若 $u$ 和 $v$ 不在同一 SCC 中且有边，则 $u$ 所在 SCC 所有点均向 $v$ 所在 SCC 所有点连边。

换句话说，我们每进入一个 SCC，都可以实现遍历完整个 SCC 并去往其连向的任意 SCC，于是一个 SCC 内的点就不重要了，整个问题就被转化在 DAG 上了，缩点之后遍历一次整个图，每个点从其后继处更新答案就完了。

---

## 作者：ran_qwq (赞：1)

对于一个强连通分量，它可以连成一个完全图。只要经过它的某一个点就可以经过全部点，所以考虑缩点。

缩点后，图变成 DAG。容易发现新建边后不会对答案产生贡献，所以在 DAG 上跑 dp 即可。

设 $f_u$ 为到达第 $u$ 个强连通分量的最大点数，$g_u$ 为最大点权和，$siz_u$ 为第 $u$ 个强连通分量的大小，$sum_u$ 为第 $u$ 个强连通分量的点权和。

- 如果 $f_u+siz_u>f_v$ 的话，$f_v\leftarrow f_u+siz_v,g_v\leftarrow g_u+siz_v$。

- 如果 $f_u+siz_u=f_v$ 的话，$g_v\leftarrow \min(g_v,g_u+siz_v)$。

---

## 作者：happybob (赞：1)

考虑原图如果存在一条从 $a$ 到 $b$ 的路径，那么新图中 $a$ 会向路径上每一个点连边，证明显然。

进一步的，一个强连通分量内部在新图上必然是完全图。

考虑缩点，然后直接朴素 DP 即可，每个 SCC 内每个点都可以走，SCC 之间只能按照 DAG 的走法走。$f_u$ 和 $g_u$ 分别表示从这个 SCC 出发的最长路径长度以及在满足长度最长的情况下的最小权值。容易转移。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

const int N = 2e5 + 5;

int scc_idx;
int t, n, m;
vector<int> G[N], RG[N], NG[N];
bool vis[N];
int a[N];
long long f[N], f2[N];
int cnt[N];
long long sum[N];
vector<int> ver;
int bel[N];

void dfs(int u)
{
	vis[u] = 1;
	for (auto& j : G[u])
	{
		if (!vis[j]) dfs(j);
	}
	ver.emplace_back(u);
}

void rdfs(int u)
{
	cnt[scc_idx]++;
	vis[u] = 1;
	sum[scc_idx] += a[u];
	bel[u] = scc_idx;
	for (auto& j : RG[u])
	{
		if (!vis[j]) rdfs(j);
	}
}

void kosaraju()
{
	for (int i = 1; i <= n; i++)
	{
		if (!vis[i]) dfs(i);
	}
	for (int i = 1; i <= n; i++) vis[i] = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		if (!vis[ver[i]])
		{
			scc_idx++;
			rdfs(ver[i]);
		}
	}
}

void dfs_dag(int u)
{
	if (f[u]) return;
	f[u] = cnt[u];
	if (!NG[u].size())
	{
		f2[u] = sum[u];
		return;
	}
	for (auto& j : NG[u])
	{
		dfs_dag(j);
		if (f[j] + cnt[u] > f[u])
		{
			f[u] = f[j] + cnt[u];
			f2[u] = f2[j] + sum[u];
		}
		else if (f[j] + cnt[u] == f[u])
		{
			if (f2[j] + sum[u] < f2[u]) f2[u] = f2[j] + sum[u];
		}
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		ver.clear();
		cin >> n >> m;
		for (int i = 1; i <= n; i++) G[i].clear(), RG[i].clear(), vis[i] = 0;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= scc_idx; i++) NG[i].clear(), f[i] = 0, f2[i] = (long long)4e18, cnt[i] = sum[i] = 0;
		scc_idx = 0;
		vector<pair<int, int>> egs;
		for (int i = 1; i <= m; i++)
		{
			int u, v;
			cin >> u >> v;
			egs.emplace_back(make_pair(u, v));
			G[u].emplace_back(v);
			RG[v].emplace_back(u);
		}
		kosaraju();
		for (auto& [u, v] : egs)
		{
			if (bel[u] ^ bel[v]) NG[bel[u]].emplace_back(bel[v]);
		}
		for (int i = 1; i <= scc_idx; i++)
		{
			if (!f[i])
			{
				dfs_dag(i);
			}
		}
		int maxd = 0;
		long long minn = (long long)4e18;
		for (int i = 1; i <= scc_idx; i++)
		{
			if (f[i] > maxd)
			{
				maxd = f[i];
				minn = f2[i];
			}
			else if (f[i] == maxd && f2[i] < minn) minn = f2[i];
		}
		cout << maxd << " " << minn << "\n";
	}
	return 0;
}
```


---

## 作者：Trafford1894 (赞：1)

考虑一次加边操作：

- 若存在三元组 $a, b, c$，使得 $a$ 到 $b$ 有一条边，$b$ 到 $c$ 有一条边，但是 $a$ 到 $c$ 没边，则连一条 $a$ 到 $c$ 的边。

我们可以对 $a$ 和 $c$ 在原图中的连通性做分类讨论。

- $a$ 可到达 $c$，$c$ 也可到达 $a$。即它们在同一个强连通分量中。这种情况下，根据加边操作的定义，将会加一条 $a$ 到 $c$ 的边，一条 $c$ 到 $a$ 的边。推而广之，一个强连通分量内的点两两之间都将有边相连，这个强连通分量会变成有向完全图。

- $a$ 可到达 $c$，而 $c$ 不可到达 $a$。这样的话，会加一条 $a$ 到 $c$ 的边。因为 $a$ 本就可到达 $c$，加一条 $a$ 到 $c$ 的边并不对它们的连通性构成影响。

- $a$ 和 $c$ 相互不可到达。不会加任何边。

由此，我们可以得出一些结论：

- 原图的连通性并不改变，因此并不需要真正地加边。

- 原图的强连通分量变成了有向完全图，可以从任意一个点进入，从任意一个点走出。

我们可以直接在原图上缩点，缩点后就成了 DAG，在上面跑一遍 DP 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+9;
int dfn[N], low[N], col[N], dfst, scc;
long long val[N];
int ind[N];
long long g[N];
int in[N], f[N], n, m;
vector<int> old[N], neo[N];
stack<int> s; queue<int> q;
void init() {
	dfst = scc = 0;
	memset(dfn, 0, sizeof(int)*(n+9));	
	memset(low, 0, sizeof(int)*(n+9));
	memset(col, 0, sizeof(int)*(n+9));
	memset(val, 0, sizeof(int)*(n+9));
	memset(f, 0, sizeof(int)*(n+9));
	memset(g, 0, sizeof(int)*(n+9));
	memset(in, 0, sizeof(int)*(n+9));
	memset(ind, 0, sizeof(int)*(n+9));
	for (int i = 0; i <= n; i++) old[i].clear(), neo[i].clear();	
	while (s.size()) s.pop();
	while (q.size()) q.pop();
}

void tarjan(int c) {
	dfn[c] = low[c] = ++dfst; s.push(c);
	for (int to : old[c]) {
		if (!dfn[to]) {tarjan(to); low[c] = min(low[c], low[to]);}
		else if (!col[to]) {low[c] = min(low[c], dfn[to]);}
	} if (low[c] != dfn[c]) return;
	while (1) {
		int tp = s.top(); s.pop(); col[tp] = c;
		if (tp == c) break; 
		val[c] += val[tp]; ind[c]++;
	}
}

void solve() {
	init();
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {cin >> val[i]; ind[i] = 1;}
	for (int i = 1, u, v; i <= m; i++) {cin >> u >> v; old[u].push_back(v); old[v].push_back(v);}
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++) {for (int to : old[i]) {if (col[i] != col[to]) {in[col[to]]++, neo[col[i]].push_back(col[to]);}}}
	for (int i = 1; i <= n; i++) {if (col[i] == i && in[i] == 0) {q.push(i); f[i] = ind[i]; g[i] = val[i];}}
	while (q.size()) {
		int c = q.front(); q.pop(); 
		for (int to : neo[c]) {
			if (f[to] < f[c] + ind[to]) {
				f[to] = f[c] + ind[to], g[to] = g[c] + val[to];	
			} else if (f[to] == f[c] + ind[to]) g[to] = min(g[to], g[c] + val[to]);
			if (--in[to] == 0) q.push(to);
		}
	}
	
	long long a = 0, b = LLONG_MAX;
	for (int i = 1; i <= n; i++) {
		if (col[i] != i) continue;
		a = max(a, 1ll * f[i]);
	}
	
	for (int i = 1; i <= n; i++) {
		if (col[i] != i) continue;
		if (f[i] == a) b = min(b, g[i]);	
	}
	
	cout << a << " " << b << "\n";
}

int main() {
	//freopen("E.in", "r", stdin);
	ios::sync_with_stdio(false); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
    return 0;	
}
```



---

## 作者：Phartial (赞：1)

注意到 $G$ 中的一条路径（不要求不经过重复点）总是可以通过在 $H$ 中调整为不经过重复点的路径，于是题目变为：在 $G$ 中所有经过的不同的点最多的路径中经过的不同的点的权值和的最小值。

因为 $G$ 中的强连通分量如果经过则必然全部经过，因此我们可以先把 $G$ 中所有的强连通分量缩成一个点，到这个点就相当于遍历了一遍该强连通分量中的所有点。缩点后图变成了一张 DAG，直接在 DAG 上 dp 出最长路径和最长路径的最小权值和即可。

```cpp
#include <iostream>
#include <vector>

using namespace std;
using LL = long long;

const int kN = 2e5 + 1;

int tt, n, m, a[kN];
vector<int> e[kN];
int dc, dn[kN][2], b[kN], bc, stk[kN], st;
LL s[kN];
vector<int> l[kN], ne[kN];
int df[kN];
LL f[kN], ans;

void D(int x) {
  dn[x][0] = dn[x][1] = ++dc;
  stk[++st] = x, b[x] = -1;
  for (int i : e[x]) {
    if (!b[i]) {
      D(i);
      dn[x][1] = min(dn[x][1], dn[i][1]);
    } else if (b[i] == -1) {
      dn[x][1] = min(dn[x][1], dn[i][0]);
    }
  }
  if (dn[x][0] == dn[x][1]) {
    ++bc;
    l[bc].clear();
    for (; stk[st] != x; --st) {
      l[bc].push_back(stk[st]), b[stk[st]] = bc;
      s[bc] += a[stk[st]];
    }
    l[bc].push_back(stk[st]), b[stk[st]] = bc;
    s[bc] += a[stk[st]];
    --st;
  }
}
int C(int x) {
  if (~df[x]) {
    return df[x];
  }
  df[x] = l[x].size();
  for (int i : ne[x]) {
    df[x] = max(df[x], (int)l[x].size() + C(i));
  }
  return df[x];
}
LL S(int x) {
  if (~f[x]) {
    return f[x];
  }
  if (ne[x].empty()) {
    return f[x] = s[x];
  }
  f[x] = 1e18;
  for (int i : ne[x]) {
    if (df[x] == df[i] + l[x].size()) {
      f[x] = min(f[x], s[x] + S(i));
    }
  }
  return f[x];
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> tt; tt--;) {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      e[i].clear(), ne[i].clear();
      b[i] = s[i] = 0;
    }
    for (int i = 1, x, y; i <= m; ++i) {
      cin >> x >> y;
      e[x].push_back(y);
    }
    dc = bc = st = 0;
    for (int i = 1; i <= n; ++i) {
      if (!b[i]) {
        D(i);
      }
    }
    for (int i = 1; i <= n; ++i) {
      for (int j : e[i]) {
        if (b[i] != b[j]) {
          ne[b[i]].push_back(b[j]);
        }
      }
    }
    for (int i = 1; i <= bc; ++i) {
      df[i] = f[i] = -1;
    }
    int md = 0;
    for (int i = 1; i <= bc; ++i) {
      md = max(md, C(i));
    }
    ans = 1e18;
    for (int i = 1; i <= bc; ++i) {
      if (C(i) == md) {
        ans = min(ans, S(i));
      }
    }
    cout << md << ' ' << ans << '\n';
  }
  return 0;
}
```

---

## 作者：CQWDX (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1900E)

前置芝士：[缩点](https://www.luogu.com.cn/blog/dzz-best-programmer/tarjan)、[拓扑排序](https://www.luogu.com.cn/blog/80049/topo-sort)。

### 题目描述

有向图 $G$ 有 $N$ 个点，$M$ 条边，点 $u$ 的点权为 $A_u$。

若存在三元组 $a,b,c$ 使得 $a$ 至 $b$ 有一条边，$b$ 至 $c$ 有一条边，则连一条 $a$ 至 $c$ 的边。重复执行以上操作，直到不存在这样的三元组为止。

求其最长链长度及最长链上的最小点权和。

### 分析

不难发现，只要 $a,c$ 连通，则能连一条 $a$ 至 $c$ 的边。

若 $a,c$ 在一个强连通分量内：

> 因为强连通分量内部任意两点连通，一个强连通分量在上述操作后可变为完全子图。
>
> 显然可以从任意一点进入子图遍历所有点后从任意一点离开子图。即一个完全子图的最长链长度为子图的点数。
>
> 点权和为完全子图内部的点权之和。
>
> 即对于强连通分量 $G(V,E)$，最长链长度为 $|V|$，点权和为 $\sum\limits_{u\in V}a_u$。

若 $a,c$ 不在一个强连通分量内：

> 显然 $a\to b,b\to c$ 的长度大于 $a\to c$。所以最优决策不是走 $a\to c$ 这条新连的边。这里可视为不连接 $a,c$。

以每个点的强连通分量编号进行建图。

显然缩点后组成的图是 DAG。否则这个大图可以构成一个新的强连通分量。

接下来便可以拓扑排序后跑 DAG 上最长链板子。

设 $f_u$ 为以 $u$ 为起点的最长链长度，$g_u$ 为以 $u$ 为起点的最长链的最小点权和。

则有转移方程 $f_u=\max\{f_u,f_v+w_v\},(u,v)\in E$。

显然当 $f_u<f_v+w_v$ 时，$g_u=g_v+w'_v$。

而当 $f_u=f_v+w_v$ 时，$g_u=\min\{g_u,g_v+w'_v\}$。

### 代码

~~请欣赏工程码风。~~

```cpp
#include <bits/stdc++.h>
#include <algorithm>
#define int long long
const int maxn = 2e5 + 20;
const int inf = 2e18;
int n, m;
int a[maxn];
int dfn[maxn], low[maxn], dfncnt;
int scc[maxn], sz[maxn], val[maxn], sccidx;
int stack[maxn], top;
int inDeg[maxn];
int f[maxn], fval[maxn];
std::vector <int> topo;
struct graph {
	struct edge {
		int u, v, w, next;
	};
	int head[maxn], cnt;
	edge e[maxn];
	void add(int x, int y) {
		e[++cnt].u = x, e[cnt].v = y, e[cnt].next = head[x], head[x] = cnt;
	}
} g, p;
void tarjan(int u, graph &g) {
	low[u] = dfn[u] = ++dfncnt;
	stack[++top] = u;
	for(int i = g.head[u]; i; i = g.e[i].next) {
		int v = g.e[i].v;
		if(!dfn[v]) tarjan(v, g), low[u] = std::min(low[u], low[v]);
		else if(!scc[v]) low[u]	= std::min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]) {
		sccidx++;
		while(stack[top] != u) scc[stack[top--]] = sccidx, sz[sccidx]++;
		scc[stack[top--]] = sccidx, sz[sccidx]++;
	}
}
void getSCC(int n, graph &g) {
	for(int i = 1; i <= n; i++)
		if(!dfn[i]) tarjan(i, g);
}
std::vector <int> topoSort(graph &g) {
	std::queue <int> q;
	std::vector <int> res;
	for(int i = 1; i <= sccidx; i++)
		if(inDeg[i] == 0) q.push(i);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		res.push_back(u);
		for(int i = g.head[u]; i; i = g.e[i].next) {
			int v = g.e[i].v, w = g.e[i].w;
			if(--inDeg[v] == 0) q.push(v);
		}
	}
	return res;
}
void solve() {
	int ans = 0, ansp;
	sccidx = 0, dfncnt = 0, g.cnt = 0, p.cnt = 0, top = 0;
	scanf("%lld %lld", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]), g.head[i] = p.head[i] = val[i] = sz[i] = dfn[i] = scc[i] = 0;
	for(int i = 1; i <= m; i++) {
		int x, y;
		scanf("%lld %lld", &x, &y);
		g.add(x, y);
	}
	getSCC(n, g);
	for(int i = 1; i <= n; i++) {
		for(int j = g.head[i]; j; j = g.e[j].next) {
			int v = g.e[j].v;
			if(scc[i] == scc[v]) continue;
			p.add(scc[i], scc[v]);
			inDeg[scc[v]]++;
		}
	}
	for(int i = 1; i <= n; i++)
		val[scc[i]] += a[i];
	topo = topoSort(p);
	for(int i = 1; i <= sccidx; i++) {
		if(inDeg[i] == 0) fval[i] = val[i], f[i] = sz[i];
		else fval[i] = inf;
	}
	for(auto u : topo) {
		for(int i = p.head[u]; i; i = p.e[i].next) {
			int v = p.e[i].v, w = sz[v];
			if(f[v] < f[u] + w) f[v] = f[u] + w, fval[v] = fval[u] + val[v];
			else if(f[v] == f[u] + w) fval[v] = std::min(fval[v], fval[u] + val[v]);
		}
	}
	for(int i = 1; i <= n; i++)
		if(ans < f[i]) ans = f[i], ansp = fval[i];
		else if(ans == f[i]) ansp = std::min(ansp, fval[i]);
	printf("%lld %lld\n", ans, ansp);
}
signed main() {
	int t;
	scanf("%lld", &t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：0)

这个 $H$ 我们很难处理出来。考虑发掘它的性质。注意到 $(u,v)$ 的加边操作不影响两点间的连通性，这启发我们从连通性下手。

考虑一个强连通分量，在 $G$ 中两两之间互相可达。于是我们可以在若干次建边操作后让强连通性变成两两之间必有有向边连接。于是，我们发现在 $G$ 中的一个 SCC，会在 $H$ 中构成一个团。

再回去考虑要求的问题，不难发现要想最大化经过的点的数量，就需要把 $G$ 中的一个 SCC 走遍，也就是经过 SCC 的所有点。考虑在缩点后的 DAG 直接 dp 即可。记录第一关键字为点数，第二关键字为权值即可。

时间复杂度 $O(n+m)$。[提交记录](https://codeforces.com/contest/1900/submission/234489862)

---

## 作者：233L (赞：0)

一开始看到加边不知道有啥用，先丢一边。要求[有向图的最长路径](https://zh.wikipedia.org/wiki/%E6%9C%80%E9%95%BF%E8%B7%AF%E5%BE%84%E9%97%AE%E9%A2%98#%E5%85%B3%E9%94%AE%E8%B7%AF%E5%BE%84)，但这是 NP 困难的。

先考虑有向无环图，显然可以直接 dp，点权和最小也是好求的。回到有环的情况，考虑缩点变成 DAG，但是在一个强连通分量中未必存在一条理想的路径：指定起点终点，把强连通分量所有点都访问一次，即哈密顿路径（这是 NP 困难的）。

回过头来看加边的条件：只要间接可达，就加一条边。强连通分量就变成团，想走哪走哪，自然存在上文所说的理想路径。

缩点后，记 $siz_i$ 表示强连通分量的点的个数，$val_i$ 表示强连通分量的权值和。在最大化 $siz_i$ 的前提下最小化 $val_i$，直接 dp 即可。我写的记忆化搜索，感觉挺好写，但是记得多测清空。时间复杂度 $O(n)$。[submission](https://codeforces.com/contest/1900/submission/234478608)

---

## 作者：Sampson_YW (赞：0)

相当于 $x$ 向原图上的所有通过 $x$ 能到达的点连边。

对于一个强连通分量，它在操作后会变成一个完全图。

对于不在同一个强连通分量里的点对 $(x,y)$，它们连边后不会影响最长路，因为在操作前就有一条更长的 $x\to y$ 的路径。

一个完全图可以从某一个点进入后，经过所有点后在任意一个点结束。所以完全图对最长路的贡献就是这个图的大小，权值就是所有点权之和。

缩点后跑拓扑排序 DP 即可。

---

