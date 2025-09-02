# Don&#39;t Detect Cycle

## 题目描述

有一个图 $G$，由 $N$ 个顶点组成，顶点编号为 $1, 2, \ldots, N$。起初，图中没有任何边。

接下来，我们将向图中添加 $M$ 条无向边。图中最终的边是预先确定的：第 $i$ 条边 $(1 \le i \le M)$ 连接顶点 $u_i$ 和 $v_i$。我们称其为边 $i$。添加后的图确保是简单图。

现在，你要判断是否存在一种排列 $(P_1, P_2, \ldots, P_M)$ 满足以下条件，并如满足条件则给出这样的一个实例。

**条件**：
- 按照索引顺序为 $i = 1, 2, \ldots, M$，依次执行以下操作：
  1. 如果当前图中包含 $u_{P_i}$ 或 $v_{P_i}$ 的环存在，则立即停止操作，此时条件不成立。
  2. 在图中添加边 $P_i$（即连接顶点 $u_{P_i}$ 和 $v_{P_i}$ 的无向边）。

共给出 $T$ 个测试用例，请分别解决每个测试用例。

**环的定义**：图 $G$ 中的环是指满足以下条件的顶点序列 $(v_0, \dots, v_{L-1})$ 和边序列 $(e_0, \dots, e_{L-1})$：
- $L \ge 1$
- 若 $i \neq j$，则 $v_i \neq v_j$ 且 $e_i \neq e_j$
- 对于 $0 \le i \le L-2$，边 $e_i$ 连接顶点 $v_i$ 和 $v_{i+1}$
- 边 $e_{L-1}$ 连接顶点 $v_{L-1}$ 和 $v_0$

**简单图的定义**：图 $G$ 被称作简单图，是因为没有自环和多重边。

## 说明/提示

- 输入中所有的数值均为整数。
- $1 \le T \le 2000$
- 每个测试用例满足：
  - $2 \le N \le 4000$
  - $1 \le M \le 4000$
  - $1 \le u_i, v_i \le N$ （$1 \le i \le M$）
  - 添加所有给定的边后，图为简单图。
- 每份输入文件中，所有测试用例 $N, M$ 总和不超过 $4000$。

**部分评分**

若仅回答满足以下条件的数据集，可获得 $30$ 分：

- $T \le 50$
- 每个测试用例满足：
  - $N \le 100$
  - $M \le 100$
- 每份输入文件中，所有测试用例 $N, M$ 总和不超过 $100$

### 示例说明 1

给定图如下图所示：  
![图示](https://img.atcoder.jp/ttpc2024_1/efcd772696bd0c92c27611b554a4d94b.png)

按顺序 $P = (1, 2, 3, 4)$ 添加边后，图为如下图、符合条件：  
![图示](https://img.atcoder.jp/ttpc2024_1/f639f61a8c21e023b412bb9d1f8c4cca.png)  
![图示](https://img.atcoder.jp/ttpc2024_1/d6307590977040bdaea3733c0df34398.png)

因此，`1 2 3 4` 是一个正确的输出方案。若按顺序 $P = (2, 3, 4, 1)$ 添加边，则在添加边 $1$ 时会形成包含顶点 $2$ 的环，故不满足条件：  
![图示](https://img.atcoder.jp/ttpc2024_1/d7e2277adb8c0aace5f07f25a6cf2569.png)  
![图示](https://img.atcoder.jp/ttpc2024_1/11d01a954d01e5ea030492db5eefd3f8.png)

另外，像 $P = (1, 4, 3, 2)$ 或 $P = (2, 4, 1, 3)$ 的排列也符合条件。

### 示例说明 2

如果不存在满足条件的排列 $P$，则请输出 `-1`。注意，图不一定连通。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1
4 4
1 2
2 3
3 4
4 2```

### 输出

```
2 4 1 3```

## 样例 #2

### 输入

```
4
4 5
1 2
2 3
3 4
3 1
1 4
5 3
1 2
2 3
3 4
9 10
3 5
1 8
5 8
4 9
6 7
7 9
1 2
1 4
2 4
4 6
8 10
1 4
3 8
2 5
3 4
1 5
5 8
2 8
5 7
4 5
3 7```

### 输出

```
-1
3 2 1
4 10 2 8 7 9 6 5 3 1
-1```

# 题解

## 作者：Register_int (赞：2)

可以将加边倒过来变成删边。将能删的边直接删掉必然是不劣的，而复杂度允许我们每次暴力枚举删哪条边，所以问题就转换为什么边可以删。可以发现：

- 如果这条边是割边，此时它虽然删不动，但直接放在最前面去加并不影响后面的结果。可以扔前面去不考虑。
- 否则边的两个端点仅被一个环包含。

求割边复杂度已经对了，求每个点被多少个环包含也可以用 dfs 树 + 树上差分做掉，可以通过。不过不够优美，我们有这么一个引理：

> 若一个边双满足：对于任意一条边，都有其两端点的度数的最大值 $>2$，则不存在合法的加边方案。

证明是简单的：考察最后加的边 $(u,v)$，那么 $v$ 除了 $u$ 还有至少两个邻居，取其中的两个为 $x,y$。由边双的性质可得 $v,x$ 会在一个环内，而加边前 $v$ 不在任何一个环里，故这个环只能是 $v\to a\rightsquigarrow u\to v$，同理还有一个环是 $v\to b\rightsquigarrow u\to v$。你会发现两个一合并出现了 $v\to a\rightsquigarrow b\to v$ 这个环，寄了！因此这种情况无解。

所以我们有这么一个贪心：每次找出所有两端度数均 $\le 2$ 的边，将他们扔到操作序列尾，再将所有割边扔到操作序列头，不断重复即可。时间复杂度 $O(m(n+m))$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e3 + 10;

vector<pair<int, int>> g[MAXN];

int dfn[MAXN], low[MAXN], id; bool ban[MAXN];

vector<int> a, b; bool flag;

void tarjan(int u, int pre) {
	dfn[u] = low[u] = ++id;
	for (pair<int, int> p : g[u]) {
		int v = p.first, w = p.second;
		if (w == pre || ban[w]) continue;
		if (!dfn[v]) {
			tarjan(v, w), low[u] = min(low[u], low[v]);
			if (dfn[u] < low[v]) ban[w] = flag = 1, a.emplace_back(w);
		} else if (w != pre) low[u] = min(low[u], dfn[v]);
	}
}

int T, n, m, d[MAXN], u[MAXN], v[MAXN];

int main() {
	for (scanf("%d", &T); T--; ) {
		scanf("%d%d", &n, &m), a.clear(), b.clear();
		for (int i = 1; i <= n; i++) g[i].clear();
		for (int i = 1; i <= m; i++) {
			scanf("%d%d", &u[i], &v[i]), ban[i] = 0;
			g[u[i]].emplace_back(v[i], i), g[v[i]].emplace_back(u[i], i);
		}
		for (flag = 1; flag; ) {
			for (int i = 1; i <= n; i++) dfn[i] = low[i] = 0;
			for (int i = 1; i <= n; i++) d[i] = 0; id = flag = 0;
			for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i, 0);
			for (int i = 1; i <= m; i++) if (!ban[i]) d[u[i]]++, d[v[i]]++;
			for (int i = 1; i <= m; i++) {
				if (ban[i] || d[u[i]] > 2 || d[v[i]] > 2) continue;
				b.emplace_back(i), ban[i] = flag = 1;
			}
		}
		reverse(b.begin(), b.end());
		if (a.size() + b.size() < m) { puts("-1"); continue; }
		for (int i : a) printf("%d ", i); for (int i : b) printf("%d ", i); puts("");
	}
}
```

---

