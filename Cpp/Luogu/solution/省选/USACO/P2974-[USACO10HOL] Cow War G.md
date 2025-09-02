# [USACO10HOL] Cow War G

## 题目描述

给定 $V$ 个点，$E$ 条边的无向图。
一开始每个点上有 `T` 牛，`J` 牛，或者没有（`E`）。
`J` 牛可以 `MOVE` 到一个相邻的点，也可以 `ATTACK` 相邻点上的一个 `T` 牛。不过操作有限制，只能按照 `MOVE`,`ATTACK` 或者 `MOVE` 然后 `ATTACK` 三种方式操作。
一个 `T` 牛仅能被 `ATTACK` 一次，被 `ATTACK` 后它会留在原地。
需要保证任意时刻，每个点上有且仅有一头牛。
求所有 `T` 牛被 `ATTACK` 的最大次数，并给出一个可行的操作方案。

## 说明/提示

对于测试点 $1\sim5$，$1\leq V\leq 30,1\leq E\leq 50$。
对于测试点 $6\sim 10$，$1\leq V\leq 500,1\leq E\leq 2\times 10^3$。
对于测试点 $11\sim 15$，$1\leq V\leq 10^3,1\leq E\leq 5\times 10^3$。
注意：一个操作需要描述现在的位置，例如：点 $3$ 上的牛先 `MOVE` 到点 $2$，再 `ATTACK` 点 $4$，应该写为：

\```
MOVE 3 2
ATTACK 2 4
\```

## 样例 #1

### 输入

```
5 4 
TEJTJ 
1 2 
2 3 
3 4 
4 5 
```

### 输出

```
2 
MOVE 3 2 
ATTACK 2 1 
ATTACK 5 4 
```

# 题解

## 作者：Usada_Pekora (赞：8)

题意：

给定 $n$ 个点，$m$ 条边的无向图。

每个点上有 `T` 牛，`J` 牛，或者没有（`E`）。

`J` 牛可以 `MOVE` 到一个相邻的点，也可以 `ATTACK` 相邻点上的一个 `T` 牛。不过操作有限制，只能按照 `MOVE`,`ATTACK` 或者 `MOVE` 然后 `ATTACK` 三种方式操作。

一个 `T` 牛仅能被 `ATTACK` 一次。

需要保证任意时刻，每个点上有且仅有一头牛。

求所有 `T` 牛被 `ATTACK` 的最大次数，并给出一个可行的操作方案。

题解：

注意到这个东西很像最大流的常见套路：每个点有容量限制，多个源点，问多个汇点最多接收到多少流量？

按点种类建模。

对于 `J` 牛，它需要从超级源接收一个流量（攻击一次），然后可以 `MOVE` 到一个其他点或者不动，最后 `ATTACK`，需要三层图。

对于 `T` 牛，它只能被一个点 `ATTACK` 一次，需要一层图。

对于 `E`，它可以被 `MOVE`，但是同时只能有一头牛在这个位置，所以需要两层用来限制流量。

梳理一下：第一层给 `J` 牛接收流量，第二层是被 `MOVE` 到或者不动的点，第三层用于限制每个点至多被一头牛占据，第四层被 `ATTACK`。

然后就可以愉快 Dinic 了。

至于方案输出，我们像匈牙利算法一样去处理 `MOVE` 并且模拟就好了，不同的一点是每个点最多 `MOVE` 一次。`ATTACK` 在处理完前面以后就是常规的最大流输出了。 

Dinic 可以过倒不是因为网络流跑不满，而是因为流量都是 $1$，复杂度 $O(E\min\{V^{\frac{2}{3}},E^{\frac{1}{2}}\})$，其中 $V$ 是点数，$E$ 是边数。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005, M = 5005;
int fir[N << 2], nxt[(N + M) << 2], to[(N + M) << 2], flow[(N + M) << 2], cnt = 1;
int n, m, s, t, dep[N << 2];
char str[N];
bool vis[N << 2];
inline void add(int u, int v, int f) {
	to[++cnt] = v;
	flow[cnt] = f;
	nxt[cnt] = fir[u];
	fir[u] = cnt;
}
inline void addedge(int u, int v, int f) {
	add(u, v, f);
	add(v, u, 0);
}
#define v to[i]
inline bool bfs() {
	memset(dep, 0, sizeof dep);
	dep[s] = 1;
	queue<int> q;
	q.push(s);

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int i = fir[u]; i; i = nxt[i]) {
			if (flow[i] && !dep[v]) {
				q.push(v);
				dep[v] = dep[u] + 1;
			}
		}
	}

	return dep[t] > 0;
}
inline int min(int x, int y) {
	return x < y ? x : y;
}
inline int dfs(int u, int in) {
	if (u == t)
		return in;

	int out = 0, res;

	for (int i = fir[u]; i && in; i = nxt[i]) {
		if (dep[v] == dep[u] + 1 && flow[i]) {
			res = dfs(v, min(in, flow[i]));
			flow[i] -= res, flow[i ^ 1] += res, in -= res, out += res;
		}
	}

	if (out == 0)
		dep[u] = 0;

	return out;
}
inline int dinic() {
	int res = 0;

	while (bfs())
		res += dfs(s, 1e9);

	return res;
}
inline bool print_move(int u) {
	if (vis[u] || str[u] != 'J')
		return 0;

	vis[u] = 1;

	for (int i = fir[u]; i; i = nxt[i]) {

		if (v == u + n || v <= u || flow[i])
			continue;

		if (str[v - n] == 'J') {
			if (print_move(v - n)) {
				printf("MOVE %d %d\n", u, v - n);
				swap(str[u], str[v - n]);
				return 1;
			}
		} else if (str[v - n] == 'E') {
			printf("MOVE %d %d\n", u, v - n);
			swap(str[u], str[v - n]);
			return 1;
		}
	}

	return 0;
}
#undef v
signed main() {
	scanf("%d%d", &n, &m);
	scanf("%s", str + 1);
	s = 0, t = 4 * n + 1;

	for (int i = 1; i <= n; i++) {
		if (str[i] == 'J') {
			addedge(s, i, 1);
			addedge(i, n + i, 1);//REMAIN
			addedge(n + i, 2 * n + i, 1);
		} else if (str[i] == 'T')
			addedge(3 * n + i, t, 1);
		else if (str[i] == 'E')
			addedge(n + i, 2 * n + i, 1);
	}

	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);

		if (str[u] != 'T' && str[v] != 'T') { //MOVE u v / MOVE v u
			addedge(u, n + v, 1);
			addedge(v, n + u, 1);
		} else if (str[u] != 'T' && str[v] == 'T') // ATTACK u v
			addedge(2 * n + u, 3 * n + v, 1);
		else if (str[v] != 'T' && str[u] == 'T') //ATTACK v u
			addedge(2 * n + v, 3 * n + u, 1);
	}

	int maxf = dinic();
	printf("%d\n", maxf);

	for (int i = 1; i <= n; i++)
		print_move(i);

	for (int i = 2 * n + 1; i <= 3 * n; i++) {
		if (str[i - 2 * n] != 'J')
			continue;

		for (int j = fir[i]; j; j = nxt[j]) {
			int v = to[j];

			if (v <= i)
				continue;

			if (flow[j] == 0 && str[v - 3 * n] == 'T') {
				printf("ATTACK %d %d\n", i - 2 * n, v - 3 * n);
				break;
			}
		}
	}

	return 0;
}
```


---

