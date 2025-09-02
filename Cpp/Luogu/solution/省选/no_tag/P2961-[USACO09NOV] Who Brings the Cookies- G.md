# [USACO09NOV] Who Brings the Cookies? G

## 题目描述

农夫约翰的 $N (1 \leq N \leq 1,000)$ 头奶牛，方便地编号为 $1$ 到 $N$，决定组成 $M (1 \leq M \leq 100)$ 个学习小组。每个学习小组 $G_i$ 中有 $S_i (1 \leq S_i \leq 19)$ 头奶牛参与学习（即奶牛 $G_i1, G_i2, \dots$）。一头奶牛可能参加多个学习小组。

对于每个学习小组，必须选择其中一头奶牛带饼干来参加会议。饼干很贵且需要时间来获取，因此奶牛们希望尽可能公平地分配带饼干的工作。

她们决定，如果一头奶牛参加了大小为 $c_1, c_2, \dots, c_K$ 的会议，她最多只愿意为 $ceil(1/c_1 + 1/c_2 + \dots + 1/c_K$) 个会议带饼干。

找出哪头奶牛为每次会议带饼干。如果无法做到，只需输出 '$-1$'。如果有多个解决方案，任选其一。

## 说明/提示

奶牛 $1$ 最多可以为 $2$ 次会议带饼干，奶牛 $2$ 可以带 $2$ 次，奶牛 $3$ 可以带 $2$ 次，奶牛 $4$ 可以带 $1$ 次，奶牛 $5$ 可以带 $1$ 次。
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5 6 
3 2 4 5 
2 1 3 
3 1 2 3 
1 1 
2 2 5 
3 2 3 4 
```

### 输出

```
5 
1 
3 
1 
2 
4 
```

# 题解

## 作者：Usada_Pekora (赞：3)

题外话：写了 SPJ 过了两个月终于有管理员回了（虽然没被采纳但是对了），这道题总算能交了。

题意：有 $n$ 个人与 $m$ 个小组，对于每个小组，给出小组的大小 $k$ 和组内人员。若第 $i$ 个人参加了 $j$ 个小组，这 $j$ 个小组的大小分别为 $k_{p_1},k_{p_2}...k_{p_j}$，则他可以匹配这 $j$ 个小组中的 $\lceil\sum^j_{l=1}\frac{1}{k_{p_l}}\rceil$ 个。问使每个小组都被匹配的方案。

匹配！不难想出二分图匹配这个做法：用每个人去匹配组，然后检验最大匹配数，最后输出方案。然而本题一个点可以同时匹配好多点，直接这么做显然是不可以的，不过可以考虑拆点做。

当一个点可以向 $f$ 个点连出边，我们可以将其拆成 $f$ 个点，每个新点在图中的连边关系与原点一样。如此一来，这 $f$ 个点每个点匹配一个点，就等同于这个点匹配了 $f$ 个点。

拆完点后，我们在新图上跑二分图匹配即可，需要注意处理拆完的点与原先点的关系，用右部的小组点来匹配会少一些细节问题。

代码如下（复杂度会比寻常的二分图匹配大一些，因为我们拆点增加了点数）：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005, M = 105;
int n, m, tot;
double c[N];
int matx[N], maty[N], id[N * M];
bool vis[N], g[M][N];
inline bool dfs(int u) {//匈牙利算法
	for(int i = 1; i <= tot; i++) {
		if(!g[u][id[i]] || vis[i]) continue;
		vis[i] = 1;
		if(!maty[i] || dfs(maty[i])) {
			matx[u] = i;
			maty[i] = u;
			return 1;
		}
	}
	return 0;
}
int main() {
	cin >> n >> m;
	for(int i = 1, x; i <= m; i++) {
		cin >> x;
		for(int j = 1, y; j <= x; j++) {
			cin >> y;
			c[y] += 1.0 / x;
			g[i][y] = 1;
		}
	}
	for(int i = 1; i <= n; i++) {
		int f = ceil(c[i]);
		while(f--) id[++tot] = i;//将 i 拆成 f 个点
	}
	for(int i = 1; i <= m; i++) {
		memset(vis, 0, sizeof vis);
		if(!dfs(i)) {
			cout << -1 << '\n';
			return 0;
		}
	}
	for(int i = 1; i <= m; i++)
		cout << id[matx[i]] << '\n';
	return 0;
}
```

本题还存在一种不需要拆点，且理论复杂度更优的做法，复杂度上界约为 $O((n+m)\sqrt{n+m})$。

将其转化为多源汇最大流模型，每个人最多匹配 $f$ 个小组，则从源点向他连流量为 $f$ 的边；一个小组只能被一个人匹配一次，则每个人向他所在的小组连一条流量为 $1$ 的边；一个小组仅能被匹配一次，则向汇点连流量为 $1$ 的边。

然后直接 Dinic 跑一次，因为是二分图，所以复杂度为 $O(E\sqrt V)$，一共有 $n+m$ 个点，第一个步骤连了 $2n$ 条边，第二个步骤最多连 $38m$ 条边，第三个步骤连了 $2m$ 条边，约去常数后大概是上面的复杂度。

对于方案输出，我们判断一条从人流向小组的正向边流量是否为 $0$，为 $0$ 则明这个人匹配了这个小组。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005, M = 105, E = 19 * M + N + M;
double c[N];
int dep[N], n, m, s, t, fir[N + M], nxt[E << 1], to[E << 1], flow[E << 1], cnt = 1, mat[M];
inline void add(int u, int v, int f) {
	to[++cnt] = v;
	flow[cnt] = f;
	nxt[cnt] = fir[u];
	fir[u] = cnt;
}
inline bool bfs() {
	memset(dep, 0, sizeof dep);
	dep[s] = 1;
	queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = fir[u]; i; i = nxt[i]) {
			if(flow[i] && !dep[to[i]]) {
				q.push(to[i]);
				dep[to[i]] = dep[u] + 1;
			}
		}
	}
	return dep[t] > 0;
}
inline int min(int x, int y) {
	return x < y ? x : y;
}
inline int dfs(int u, int in) {
	if(u == t) return in;
	int out = 0, res;
	for(int i = fir[u]; i && in; i = nxt[i]) {
		if(dep[to[i]] == dep[u] + 1 && flow[i]) {
			res = dfs(to[i], min(in, flow[i]));
			flow[i] -= res, flow[i ^ 1] += res, in -= res, out += res;
		}
	}
	if(out == 0) dep[u] = 0;
	return out;
}
inline int dinic() {
	int res = 0;
	while(bfs()) res += dfs(s, 1e9);
	return res;
}
int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	s = 0, t = n + m + 1;
	for(int i = 1, x; i <= m; i++) {
		cin >> x;
		for(int j = 1, y; j <= x; j++) {
			cin >> y;
			c[y] += 1.0 / x;
			add(y, i + n, 1);
			add(i + n, y, 0);
		}
	}
	for(int i = 1; i <= n; i++) {
		int f = ceil(c[i]);
		add(s, i, f);
		add(i, s, 0);
	}
	for(int i = 1; i <= m; i++) {
		add(i + n, t, 1);
		add(t, i + n, 0);
	}
	int maxf = dinic();
	if(maxf == m) {
		for(int i = 1; i <= n; i++) {
			for(int j = fir[i]; j; j = nxt[j]) 
				if(to[j] != s && flow[j] == 0) mat[to[j] - n] = i;
		}
		for(int i = 1; i <= m; i++) printf("%d\n", mat[i]);
	} else puts("-1");
	return 0;
}
```


---

