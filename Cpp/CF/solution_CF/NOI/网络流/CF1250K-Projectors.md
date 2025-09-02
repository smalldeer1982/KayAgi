# Projectors

## 题目描述

今天，在“近似科学”学院将举办 $n$ 场讲座和 $m$ 场研讨会。第 $i$ 场讲座从 $a_i$ 开始，到 $b_i$ 结束（即讲座的时间区间为 $[a_i, b_i)$，右端点不包含在内）。第 $j$ 场研讨会从 $p_j$ 开始，到 $q_j$ 结束（同样，研讨会的时间区间为 $[p_j, q_j)$，右端点不包含在内）。

学院有 $x$ 台 HD 投影仪，编号为 $1$ 到 $x$，以及 $y$ 台普通投影仪，编号为 $x+1$ 到 $x+y$。投影仪的分配需满足以下要求：

- 每场讲座都必须使用一台 HD 投影仪；
- 每场研讨会都必须使用一台投影仪（可以是 HD 或普通投影仪）；
- 每台投影仪在同一时刻只能用于一场活动；
- 一旦某台投影仪被分配给某场活动，则在该活动的整个持续时间内都要使用这台投影仪；
- 如果某台投影仪分配给一场活动后，下一场活动的开始时间不早于当前活动的结束时间，则该投影仪可以被重复使用。

请判断是否存在一种投影仪的分配方案，使得所有要求都能满足。如果存在，请给出一种分配方案。

注意，活动时间区间的右端点是不包含的：如果一场活动的开始时间恰好等于另一场活动的结束时间，则投影仪可以被立即转移并复用。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
2 2 2 2
1 5
2 5
1 5
1 4
2 0 2 10
1 3
1 3
```

### 输出

```
YES
2 1 4 3 
YES
2 1 
```

## 样例 #2

### 输入

```
3
1 2 1 1
3 4
2 4
1 3
3 4 2 3
5 7
1 3
1 7
4 8
2 5
1 6
2 8
0 1 1 0
1 1000000
```

### 输出

```
YES
1 2 1 
NO
YES
1 
```

# 题解

## 作者：Jayun (赞：6)

# Projectors

## 题面

$n$ 个讲课，$m$ 个研讨会，$x$ 个高清投影仪和 $y$ 个普通投影仪。

每堂讲课必须使用一个高清投影仪，而研讨会可以使用普通或高清投影仪。

给定讲课和研讨会的时间区间，构造一个投影仪的分配方案。

$n,m,x,y \leq 300, a_i,b_i,p_i,q_i \leq 10^6$。

## 题解

厉害的建模题。

分配普通投影仪的分配时不需要考虑每个讲课的区间具体是什么，只需要知道每个时刻被多少讲课所包含。以此为启发考虑到网络流。

先离散化时间，以时间轴为基础建图。我们考虑的是普通投影仪，就把其**最多剩余量**作为流量：
- 经过 $i\rightarrow i+1$ 最多剩余 $\min(y,x+y-(\sigma_x+\sigma_y))$ 个普通投影仪，其中 $\sigma_x,\sigma_y$ 分别表示讲课数量和研讨会数量。那么就连一条 $(i,i+1)$ 流量为 $\min(y,x+y-(\sigma_x+\sigma_y))$ 的边。
- 对于一个研讨会 $(p_i,q_i)$，连一条 $(p_i,q_i)$ 流量为 $1$ 的边。

这样建图，假设到了时间 $p_x$，如果流走了研讨会的边，说明此研讨会消耗了一个普通投影仪，如果走的是 $(p_x,p_x+1)$ 的边就是高清投影仪。

对于不合法，建图连边的时候若投影仪符合式子就不合法、最终流量不为 $y$ 不合法。

对于构造合法方案，开两个栈贪心即可。

## 代码

### 小问题

奇怪的是，网络流用邻接表会有错误（可能只是我的问题，还望指出），这个是错误代码：

```cpp
const int N = 610 * 2;

inline ll Read() {
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

namespace Main {
	int n, m, x, y;
	int a[N], b[N];
	int sumX[N], sumY[N];
	int dtmp[N << 1], tot;

	int head[N << 1], cnt;
	struct Edge {
		int to; ll w; int op, nxt;
	} e[N * 5];
	void add_edge(int u, int v, ll w) {
		e[++cnt] = (Edge) {v, w, cnt ^ 1, head[u]}, head[u] = cnt;
		e[++cnt] = (Edge) {u, 0, cnt ^ 1, head[v]}, head[v] = cnt;
	}

	struct NetworkFlow {
		const int inf = 707406378;
		int S, T;
		int dis[N];
		queue <int> q;
		bool bfs() {
			while (!q.empty()) q.pop();
			memset (dis, 127 / 3, sizeof dis);
			dis[S] = 0;
			q.push(S);
			while (!q.empty()) {
				int u = q.front(); q.pop();
				for (int i = head[u]; i; i = e[i].nxt) {
					int v = e[i].to;
					if (dis[v] > dis[u] + 1 && e[i].w) {
						dis[v] = dis[u] + 1;
						if (v == T) return 1;
						q.push(v);
					}
				}
			}
			return 0;
		}
		ll dfs (int u, ll flow) {
			if (u == T) return flow;
			ll sum = 0;
			for (int i = head[u]; i; i = e[i].nxt) {
				int v = e[i].to;
				if (dis[v] == dis[u] + 1 && e[i].w) {
					ll f = dfs(v, min(e[i].w, flow - sum));
					if (!f) dis[v] = -1;
					e[i].w -= f;
					e[e[i].op].w += f;
					sum += f;
					if (sum == flow) break;
				}
			}
			return sum;
		}
		ll dinic () { ll ret = 0; for (; bfs(); ret += dfs(S, inf)); return ret; }
	} nf;

	vector <int> st[N], en[N];
	int id[N];
	int stX[N], stY[N];
	int Ans[N];

	void clr () {
		for (int i = 1; i <= tot; i++) {
			st[i].clear();
			en[i].clear();
		}
		tot = 0, cnt = 1;
		memset (Ans, 0, sizeof Ans);
		memset (head, 0, sizeof head);
		memset (sumX, 0, sizeof sumX);
		memset (sumY, 0, sizeof sumY);
	}

	int main () {
		for (int t = Read(); t--; clr()) {
			n = Read(), m = Read(), x = Read(), y = Read();
			for (int i = 1; i <= n; i++) a[i] = Read(), b[i] = Read(), dtmp[++tot] = a[i], dtmp[++tot] = b[i];
			for (int i = 1; i <= m; i++) a[i + n] = Read(), b[i + n] = Read(), dtmp[++tot] = a[i + n], dtmp[++tot] = b[i + n];
			sort (dtmp + 1, dtmp + 1 + tot);
			tot = unique (dtmp + 1, dtmp + 1 + tot) - dtmp - 1;
			for (int i = 1; i <= n + m; i++) {
				a[i] = lower_bound(dtmp + 1, dtmp + 1 + tot, a[i]) - dtmp;
				b[i] = lower_bound(dtmp + 1, dtmp + 1 + tot, b[i]) - dtmp;
				if (i <= n) sumX[a[i]]++, sumX[b[i]]--;
				else sumY[a[i]]++, sumY[b[i]]--;
				st[a[i]].emplace_back(i);
				en[b[i]].emplace_back(i);
			}
			for (int i = n + m; i >= n + 1; i--) {
				add_edge(a[i], b[i], 1);
				id[i] = cnt - 1;
			}
			bool flag = 1;
			for (int i = 1; i <= tot; i++) {
				sumX[i] += sumX[i - 1], sumY[i] += sumY[i - 1];
				if (i < tot)add_edge(i, i + 1, min(y, x + y - sumX[i] - sumY[i]));
				if (sumX[i] > x || x + y - (sumX[i] + sumY[i]) < 0) {
					puts("NO"); flag = 0; break;
				}
			}
			if (!flag) continue;
			nf.S = tot + 5, nf.T = nf.S + 1;
			add_edge(nf.S, 1, y);
			add_edge(tot, nf.T, nf.inf);
			if(nf.dinic() != y) { puts("NO"); continue; }
			puts("YES");
			int topX = 0, topY = 0;
			for (int i = 1; i <= x; i++) stX[++topX] = i;
			for (int i = x + 1; i <= x + y; i++) stY[++topY] = i;
			for (int i = 1; i <= tot; i++) {
				for (int j : en[i]) {
					if (Ans[j] <= x) stX[++topX] = Ans[j];
					else stY[++topY] = Ans[j];
				}
				for (int j : st[i]) {
					if (j <= n || e[id[j]].w) Ans[j] = stX[topX--];
					else Ans[j] = stY[topY--];
				}
			}
			for (int i = 1; i <= n + m; i++) printf ("%d ", Ans[i]); putchar(10);
		}
		return 0;
	}
}

int main () { 
//	freopen(".in", "r", stdin);
//	freopen("1.out", "w", stdout);
	Main::main();
	return 0;
}
```

### AC 代码

下面是 AC 代码：

```cpp
const int N = 2e4 + 5;

inline ll Read() {
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

namespace Main {
	int n, m, x, y;
	int a[N], b[N];
	int sumX[N], sumY[N];
	int dtmp[N], tot;

	struct Edge {
		int to; ll w; int op;
	};
	vector <Edge> G[N];
	void add_edge(int u, int v, ll w) {
		G[u].emplace_back((Edge) {v, w, G[v].size()});
		G[v].emplace_back((Edge) {u, 0, G[u].size() - 1});
	}

	struct NetworkFlow {
		const int inf = 707406378;
		int S, T;
		int dis[N];
		queue <int> q;
		bool bfs() {
			while (!q.empty()) q.pop();
			memset (dis, 127 / 3, sizeof dis);
			dis[S] = 0;
			q.push(S);
			while (!q.empty()) {
				int u = q.front(); q.pop();
				for (auto i : G[u]) {
					int v = i.to;
					if (dis[v] > dis[u] + 1 && i.w) {
						dis[v] = dis[u] + 1;
						if (v == T) return 1;
						q.push(v);
					}
				}
			}
			return 0;
		}
		ll dfs (int u, ll flow) {
			if (u == T) return flow;
			ll sum = 0;
			for (int i = 0; i < G[u].size(); i++) {
				int v = G[u][i].to;
				if (dis[v] == dis[u] + 1 && G[u][i].w) {
					ll f = dfs(v, min(G[u][i].w, flow - sum));
					if (!f) dis[v] = -1;
					G[u][i].w -= f;
					G[v][G[u][i].op].w += f;
					sum += f;
					if (sum == flow) break;
				}
			}
			return sum;
		}
		ll dinic () { ll ret = 0; for (; bfs(); ret += dfs(S, inf)); return ret; }
	} nf;

	vector <int> st[N], en[N];
	int id[N];
	int stX[N], stY[N];
	int Ans[N];

	void clr () {
		for (int i = 1; i <= tot; i++) {
			st[i].clear();
			en[i].clear();
		}
		for (int i = 1; i <= n + m + 5; i++) G[i].clear();
		tot = 0;
		memset (Ans, 0, sizeof Ans);
		memset (sumX, 0, sizeof sumX);
		memset (sumY, 0, sizeof sumY);
	}

	int main () {
		for (int t = Read(); t--; clr()) {
			n = Read(), m = Read(), x = Read(), y = Read();
			for (int i = 1; i <= n; i++) a[i] = Read(), b[i] = Read(), dtmp[++tot] = a[i], dtmp[++tot] = b[i];
			for (int i = 1; i <= m; i++) a[i + n] = Read(), b[i + n] = Read(), dtmp[++tot] = a[i + n], dtmp[++tot] = b[i + n];
			sort (dtmp + 1, dtmp + 1 + tot);
			tot = unique (dtmp + 1, dtmp + 1 + tot) - dtmp - 1;
			for (int i = 1; i <= n + m; i++) {
				a[i] = lower_bound(dtmp + 1, dtmp + 1 + tot, a[i]) - dtmp;
				b[i] = lower_bound(dtmp + 1, dtmp + 1 + tot, b[i]) - dtmp;
				if (i <= n) sumX[a[i]]++, sumX[b[i]]--;
				else sumY[a[i]]++, sumY[b[i]]--;
				st[a[i]].emplace_back(i);
				en[b[i]].emplace_back(i);
			}
			for (int i = n + m; i >= n + 1; i--) {
				add_edge(a[i], b[i], 1);
				id[i] = G[a[i]].size() - 1;
			}
			bool flag = 1;
			for (int i = 1; i <= tot; i++) {
				sumX[i] += sumX[i - 1], sumY[i] += sumY[i - 1];
				if (i < tot)add_edge(i, i + 1, min(y, x + y - sumX[i] - sumY[i]));
				if (sumX[i] > x || x + y - (sumX[i] + sumY[i]) < 0) {
					puts("NO"); flag = 0; break;
				}
			}
			if (!flag) continue;
			nf.S = tot + 2, nf.T = nf.S + 1;
			add_edge(nf.S, 1, y);
			add_edge(tot, nf.T, nf.inf);
			if(nf.dinic() != y) { puts("NO"); continue; }
			puts("YES");
			int topX = 0, topY = 0;
			for (int i = 1; i <= x; i++) stX[++topX] = i;
			for (int i = x + 1; i <= x + y; i++) stY[++topY] = i;
			for (int i = 1; i <= tot; i++) {
				for (int j : en[i]) {
					if (Ans[j] <= x) stX[++topX] = Ans[j];
					else stY[++topY] = Ans[j];
				}
				for (int j : st[i]) {
					if (j <= n || G[a[j]][id[j]].w) Ans[j] = stX[topX--];
					else Ans[j] = stY[topY--];
				}
			}
			for (int i = 1; i <= n + m; i++) printf ("%d ", Ans[i]); putchar(10);
		}
		return 0;
	}
}

int main () { 
//	freopen(".in", "r", stdin);
//	freopen("1.out", "w", stdout);
	Main::main();
	return 0;
}
```

---

## 作者：dsidsi (赞：5)

## Description

有$n$堂讲课，$m$次研讨会，$x$个高清投影仪和$y$个普通投影仪。

每堂讲课必须使用一个高清投影仪，而研讨会可以使用普通或高清投影仪。

第$i$堂讲课时间在$[a_i,b_i)$，第$i$次研讨会在时间在$[p_i,q_i)$，一个投影仪一次只能用在一个地方，且在使用完毕后才会归还。

构造为每节讲课/研讨会分配一个投影仪的方案。

$n,m,x,y \leq 300, a_i,b_i,p_i,q_i \leq 10^6$

## Solution

考虑已经知道了普通投影仪如何分配，那么存在分配高清投影仪的合法方案的充要条件是，对于任意整数$t$，时刻$t+0.5$满足需要用到的投影仪数量不超过$x+y$。

那么这意味着，我们只关心每个时刻到底要用多少投影仪，而不关心他们具体是什么。这启发我们想到网络流，$1$单位流量代表普通投影仪在每个时刻的状态。考虑每个时刻最多有多少普通投影仪是空闲的，显然是$min(x,x+y-sum)$，其中$sum$是这个时刻所需要的投影仪，即此时至少有$y-min(x,x+y-sum)$台投影仪被使用。

 - 建立一个时间轴，上面的节点依次表示时刻$0,1,...,i,...$。$i+0.5$向$i+1.5$连流量为$min(x,x+y-sum)$的边，其中$sum$是时刻$i+0.5$所需要的投影仪。时间轴上的流量表示空闲。
 - 对于研讨会$i$，连边$p_i\to q_i$，流量为$1$。表示这个投影仪此时被次研讨会使用。

存在合法解的方案当且仅当$0$到$Inf$的流量为$y$。

如何构造方案？考虑跑完最大流后，每次从$t$向$s$退$1$流量，如果一次研讨会使用当前的投影仪，当前仅当这个研讨会所代表的边被这个流量经过。

分配高清投影仪贪心即可。总时间复杂度$O(T(n+m)^2)$

**tips:** 需要把时间离散保证复杂度。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 605, Inf = 1 << 30;

inline int gi()
{
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int sum = 0;
	while ('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
	return sum;
}

int n, m, A, B, x[maxn], y[maxn], *q[maxn << 1], ti;
int vis[maxn], now[maxn], ans[maxn], sum[maxn << 1], Id[maxn];
vector<int> vec[maxn << 1];

struct edge
{
	int to, next, cap;
} e[maxn * 5];
int h[maxn << 1], cur[maxn << 1], dis[maxn << 1], tot;

inline void add(int u, int v, int w)
{
	//printf("%d %d %d\n", u, v, w);
	e[++tot] = (edge) {v, h[u], w}; h[u] = tot;
	e[++tot] = (edge) {u, h[v], 0}; h[v] = tot;
}

bool bfs(int s, int t, int E)
{
	static int u, l, r, q[maxn << 1];
	memset(dis + 1, 0, sizeof(int) * ti);
	l = 0; q[r = 1] = s; dis[s] = 1;
	while (l < r) {
		u = q[++l];
		for (int i = h[u], v; v = e[i].to, i; i = e[i].next)
			if ((i & 1) != E && !dis[v] && e[i].cap) dis[v] = dis[u] + 1, q[++r] = v;
	}
	return dis[t];
}

int dfs(int u, int t, int a, int E)
{
	if (u == t || !a) return a;
	int flow = 0, f;
	for (int &i = cur[u], v; v = e[i].to, i; i = e[i].next)
		if ((i & 1) != E && dis[v] == dis[u] + 1 && (f = dfs(v, t, min(a, e[i].cap), E))) {
			a -= f; flow += f;
			e[i].cap -= f; e[i ^ 1].cap += f;
			if (!a) break;
		}
	return flow;
}

int max_flow(int s, int t, int f, int E)
{
	int res = 0;
	while (bfs(s, t, E) && res < f) {
		memcpy(cur + 1, h + 1, sizeof(int) * ti);
		res += dfs(s, t, f, E);
	}
	return res;
}

int main()
{
	freopen("arrange20.in", "r", stdin);
	freopen("B.out", "w", stdout);

	int T = gi();
	while (T--) {
		n = gi(); m = gi(); A = gi(); B = gi();

		int Min = -1e9, Max = 1e9 + 1;
		q[tot = 1] = &Min; q[++tot] = &Max;
		for (int i = 1; i <= n; ++i) x[i] = gi(), y[i] = gi(), q[++tot] = x + i, q[++tot] = y + i;
		for (int i = 1; i <= m; ++i) x[n + i] = gi(), y[n + i] = gi(), q[++tot] = x + n + i, q[++tot] = y + n + i;
		sort(q + 1, q + tot + 1, [](int *a, int *b) {return *a < *b;});
		ti = 0;
		for (int lst = -1, i = 1; i <= tot; ++i) {
			if (*q[i] == lst) *q[i] = ti;
			else lst = *q[i], *q[i] = ++ti;
		}
		
		memset(sum + 1, 0, sizeof(int) * ti);
		for (int i = 1; i <= n + m; ++i)
			for (int j = x[i]; j < y[i]; ++j) ++sum[j];
		
		tot = 1; memset(h + 1, -1, sizeof(int) * ti);
		bool flg = 1;
		for (int i = 1; i < ti; ++i) {
			if (A + B < sum[i]) {flg = 0; break;}
			add(i, i + 1, min(B, A + B - sum[i]));
		}
		if (!flg) {puts("NO"); continue;}
		for (int i = n + 1; i <= n + m; ++i) add(x[i], y[i], 1), Id[i - n] = tot;

		if (max_flow(1, ti, Inf, -1) != B) puts("NO");
		else {
			puts("YES");
			memset(vis + 1, 0, sizeof(int) * m);
			memset(ans + 1, 0, sizeof(int) * (n + m));
			for (int i = 1; i <= m; ++i) vis[i] = !e[Id[i]].cap;
			for (int i = 1; i <= B; ++i) {
				max_flow(ti, 1, 1, 0);
				for (int j = 1; j <= m; ++j)
					if (!vis[j] && !e[Id[j]].cap) vis[j] = 1, ans[n + j] = A + i;
			}
			for (int i = 1; i <= ti; ++i) vec[i].clear();
			for (int i = 1; i <= n + m; ++i) if (!ans[i]) vec[x[i]].push_back(i);
			memset(now + 1, 0, sizeof(int) * A);
			for (int i = 1; i <= ti; ++i)
				for (int t : vec[i])
					for (int j = 1; j <= A; ++j)
						if (y[now[j]] <= x[t]) {now[j] = t; ans[t] = j; break;}
			for (int i = 1; i <= n; ++i) printf("%d ", ans[i]), assert(ans[i]);
			puts("");
			for (int i = 1; i <= m; ++i) printf("%d ", ans[n + i]), assert(ans[n + i]);
			puts("");
		}
	}
	
	return 0;
}
```

---

## 作者：123456xwd (赞：2)

首先，我们发现，若我们分配好了普通投影仪，然后我们自然而然的就可以分配出来高清投影仪，考虑如何分配普通投影仪。

先把时间离散化，这样子时间为数量 $\mathcal{O}(n)$ 的，不妨考虑一下网络流建模。

把每一个时间看作一个点，我们先连接 $(p_i,q_i,1)$，表示一个研讨会用普通投影仪，然后考虑如何表示普通投影仪空闲的情况。

乍一看可以直接连接 $(t,t+1,y)$，但你发现，这样子跑出来的一组解可能导致高清投影仪无法分配，考虑如何满足这个限制，其实就是让分配完普通投影仪后，**每个时刻需要用高清投影仪的数量 $\le x$**。

设 $needx_i,needy_i$ 表示在时刻 $i$，讲课和研讨会的数量，则要满足：$needx_i\le x \land  needx_i+needy_i\le x+y$。

对于第一个限制我们直接判断即可，第二个限制其实就是再说时刻 $i$，普通投影仪最多限制 $\min(y,x+y-needx_i-needy_i)$。

建模出来直接跑即可，通过流量是否等于 $y$ 来判断是否有解。

那么如何构造一组可行解呢？

我们用两个栈或者队列，维护一下当前可用的高清投影仪和普通投影仪。

然后根据流残量网络 $(p_i,q_i)$ 上的边权判断一下即可。

```c++
#include<bits/stdc++.h>
#define ull unsigned long long
//#define int long long
#define p_b push_back
#define m_p make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define gcd __gcd
#define lowbit(x) (x&(-x))
using namespace std;
int rd(){
    int x=0,f=1; char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar('0'+x%10);
}
const int N=1500+5,INF=0x3f3f3f3f;

struct edge{
	int to,nt,val;
}a[N<<2];
int head[N],at=1;
int now[N],deep[N],s,t;
void add(int u,int v,int w){
	a[++at].nt=head[u],head[u]=at,a[at].to=v,a[at].val=w;
}
void Add(int u,int v,int w){
	add(u,v,w);
	add(v,u,0);
}
bool bfs(){
	for(int i=1;i<=t;i++) deep[i]=0,now[i]=head[i];
	queue<int> q;int u,v,w;
	q.push(s),deep[s]=1;
	while(!q.empty()){
		u=q.front();q.pop();
		for(int i=head[u];i;i=a[i].nt){
			v=a[i].to,w=a[i].val;
			if(w&&!deep[v]){
				deep[v]=deep[u]+1;
				q.push(v);
			}
		}
	}
	return deep[t];
}
int dfs(int u,int flow){
	if(u==t||!flow) return flow;
	int v,w,tmp=0;
	for(int i=now[u];i;i=a[i].nt){
		v=a[i].to,w=a[i].val;
		now[u]=i;
		if(w&&deep[v]==deep[u]+1){
			int k=dfs(v,min(w,flow-tmp));
			if(!k) deep[v]=0;
			a[i].val-=k,a[i^1].val+=k,tmp+=k;
			if(tmp==flow) break;
		}
	}
	return tmp;
}

int Dinic(){
	int ans=0;
	while(bfs()) ans+=dfs(s,INF);
	return ans;
}

int n,m,x,y,tot;
int L[N],R[N],needx[N],needy[N];
vector<int> vec,st[N],ed[N];
stack<int> qx,qy;
int id[N],ans[N];
void solve(){
	n=rd(),m=rd(),x=rd(),y=rd();
	for(int i=1;i<=n+m;i++) L[i]=rd(),R[i]=rd(),vec.p_b(L[i]),vec.p_b(R[i]);
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	for(int i=1;i<=n+m;i++){
		L[i]=lower_bound(vec.begin(),vec.end(),L[i])-vec.begin()+1;
		R[i]=lower_bound(vec.begin(),vec.end(),R[i])-vec.begin()+1;
		if(i<=n) needx[L[i]]++,needx[R[i]]--; 
		else needy[L[i]]++,needy[R[i]]--;
		st[L[i]].p_b(i);ed[R[i]].p_b(i);
	}
	tot=vec.size();
	for(int i=1;i<=tot;i++){
		needx[i]+=needx[i-1],needy[i]+=needy[i-1];
		if(needx[i]>x||x+y-needy[i]-needx[i]<0){
			puts("NO");
			return;
		}
		if(i!=tot) Add(i,i+1,min(y,x+y-needy[i]-needx[i]));
	}
	s=tot+1,t=s+1;
	Add(s,1,y),Add(tot,t,y);
	for(int i=n+1;i<=n+m;i++) Add(L[i],R[i],1),id[i]=at-1;
	if(Dinic()!=y){
		puts("NO");
		return;
	}
	puts("YES");
	for(int i=1;i<=x;i++) qx.push(i);
	for(int i=1;i<=y;i++) qy.push(i+x);
	for(int i=1;i<=tot;i++){
		for(auto u : ed[i]){
			if(ans[u]>x) qy.push(ans[u]);
			else qx.push(ans[u]);
		}
		for(auto u : st[i]){
			if(u>n&&!a[id[u]].val)ans[u]=qy.top(),qy.pop();
			else ans[u]=qx.top(),qx.pop();
		}
	}
	for(int i=1;i<=n+m;i++) printf("%d ",ans[i]);
	puts("");
}


void clean(){
	vec.clear();at=1;
	for(int i=1;i<=tot;i++)	 st[i].clear(),ed[i].clear();
	memset(needx,0,sizeof(needx));
	memset(needy,0,sizeof(needy));
	memset(head,0,sizeof(head));
	memset(id,0,sizeof(id));
	while(!qx.empty()) qx.pop();
	while(!qy.empty()) qy.pop();
}

int main(){
	int T=rd();
	while(T--){
		solve();
		clean();
	}
    return 0;
}
```

---

## 作者：Others (赞：1)

很经典的最大流建模题，会建模基本上就结束了。

# 前言（废话）

- 这题好像贪心可以过（不清楚）。
- 有点小卡常。
- 为什么洛谷的 RemoteJudge 挂了。

# Solution

因为两种课都能用高清投影仪，所以对于高清投影仪，我们只需要判其是否足够供给每个时刻的课，然后就是普通投影仪够不够以及是否存在一种合法安排。

我们将时间轴上的流量设为剩余的普通投影仪的数量，然后对每个研讨课的起点终点连边，于是一个单位的流量就是一台普通投影仪，在时间轴上说明没有用，在研讨课的边上说明该研讨课用的普通投影仪。由于之前已经判断过普通投影仪和高清投影仪的数量足够，所以这里不用担心研讨课的边流不完的情况。

此处时间轴上的边权就是最大可能剩余的普通投影仪数。

但是注意：我们只判断过每个时间点上是否足够，但是这样的贪心显然是假的，反例就是在刚好分配完的情况下研讨会用的普通投影仪是无法与讲课交接的，而我们之前只判断了总数量，这就导致了这个网络的最大流不为普通投影仪数，这样也是没有合法安排的。

**Code**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=20005,inf=0x7f7f7f7f;
int tot,u,v,w,s,t,dis[N],cur[N],T,n,m,x,y,a[N],b[N],flag[N],top,stax[N],stay[N],topx,topy;
int sumx[N],sumy[N],idx[N],pos[N];
vector<int> vec1[N],vec2[N];
struct edge {
	int to,b,w;
};vector<edge> G[N];
void add(int u,int v,int w) {
	G[u].push_back((edge){v,G[v].size(),w});
	G[v].push_back((edge){u,G[u].size()-1,0});
}
bool bfs() {
	memset(dis,0,sizeof(dis));
	for(int i=1;i<=n;i++) cur[i]=0;
	dis[s]=1;
	queue<int> qu;
	qu.push(s);
	while(qu.size()) {
		int top=qu.front();qu.pop();
		for(const auto &lxl:G[top]) {
			if(dis[lxl.to]==0&&lxl.w>0) {
				dis[lxl.to]=dis[top]+1;
				if(lxl.to==t) return 1;
				qu.push(lxl.to);
			}
		}
	}
	return dis[t]!=0;
}
int dfs(int p,int Max) {
	if(p==t) return Max;
	int tot=0;
	for(int &i=cur[p];i!=G[p].size();i++) {
		if(dis[G[p][i].to]==dis[p]+1&&G[p][i].w>0) {
			int tmp=dfs(G[p][i].to,min(G[p][i].w,Max));
			if(tmp) {
				tot+=tmp;
				Max-=tmp;
				G[p][i].w-=tmp;
				G[G[p][i].to][G[p][i].b].w+=tmp;
				if(!Max) return tot;
			}else dis[G[p][i].to]=-1;
		}
	}
	return tot;
}
void DINIC() {
	while(bfs()) {
		memset(cur,0,sizeof(cur));
		tot+=dfs(s,inf);
	}
}
signed main() {
	cin >> T;
	while(T--) {
		cin >> n >> m >> x >> y;
		for(int i=1;i<=top;i++) vec1[i].clear(),vec2[i].clear();
		top=0;
		for(int i=1;i<=n+m+2;i++) G[i].clear();
		memset(sumx,0,sizeof(sumx));
		memset(sumy,0,sizeof(sumy));
		for(int i=1;i<=n;i++) {
			cin >> a[i] >> b[i];
			flag[++top]=a[i];
			flag[++top]=b[i];
		}
		for(int i=n+1;i<=n+m;i++) {
			cin >> a[i] >> b[i];
			flag[++top]=a[i];
			flag[++top]=b[i];
		}
		sort(flag+1,flag+top+1),top=unique(flag+1,flag+top+1)-flag-1;
		for(int i=1;i<=n+m;i++) {
			a[i]=lower_bound(flag+1,flag+top+1,a[i])-flag;
			b[i]=lower_bound(flag+1,flag+top+1,b[i])-flag;
			if(i<=n) sumx[a[i]]++,sumx[b[i]]--;
			else sumy[a[i]]++,sumy[b[i]]--;
			vec1[a[i]].push_back(i);
			vec2[b[i]].push_back(i);
		}
		bool fffflag=0;
		for(int i=1;i<=top;i++) {
			sumx[i]+=sumx[i-1],sumy[i]+=sumy[i-1];
			add(i,i+1,min(y,x+y-sumx[i]-sumy[i]));
			if(sumx[i]>x||sumx[i]+sumy[i]>x+y) {
				puts("NO");
				fffflag=1;
				break;
			}
		}
		if(fffflag) continue;
		s=top+1,t=s+1;
		add(s,1,y),add(top,t,y);
		for(int i=n+1;i<=n+m;i++) 
			add(a[i],b[i],1),idx[i]=G[a[i]].size()-1;
		tot=0;
		DINIC();
		if(tot!=y) {
			puts("NO");
			continue;
		}
		topx=topy=0;
		for(int i=1;i<=x;i++) stax[++topx]=i;
		for(int i=x+1;i<=x+y;i++) stay[++topy]=i;
		for(int i=1;i<=top;i++) {
			for(const auto &lxl:vec2[i]) {
				if(pos[lxl]<=x) stax[++topx]=pos[lxl];
				else stay[++topy]=pos[lxl];
			}
			for(const auto &lxl:vec1[i]) {
				if(lxl<=n||G[a[lxl]][idx[lxl]].w) pos[lxl]=stax[topx--];
				else pos[lxl]=stay[topy--];
			}
		}
		puts("YES");
		for(int i=1;i<=n+m;i++) printf("%d ",pos[i]);
		puts("");
	}
	return 0;
}

```

---

