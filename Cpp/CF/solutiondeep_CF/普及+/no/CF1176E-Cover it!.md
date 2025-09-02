# 题目信息

# Cover it!

## 题目描述

You are given an undirected unweighted connected graph consisting of $ n $ vertices and $ m $ edges. It is guaranteed that there are no self-loops or multiple edges in the given graph.

Your task is to choose at most $ \lfloor\frac{n}{2}\rfloor $ vertices in this graph so each unchosen vertex is adjacent (in other words, connected by an edge) to at least one of chosen vertices.

It is guaranteed that the answer exists. If there are multiple answers, you can print any.

You will be given multiple independent queries to answer.

## 说明/提示

In the first query any vertex or any pair of vertices will suffice.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1176E/425f889a93c1cbf45927e909f714357cbb29729c.png)Note that you don't have to minimize the number of chosen vertices. In the second query two vertices can be enough (vertices $ 2 $ and $ 4 $ ) but three is also ok.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1176E/95acc958b4ac046071fd74b6c58c6e3e5d349deb.png)

## 样例 #1

### 输入

```
2
4 6
1 2
1 3
1 4
2 3
2 4
3 4
6 8
2 5
5 4
4 3
4 1
1 3
2 3
2 6
5 6
```

### 输出

```
2
1 3
3
4 3 6
```

# AI分析结果

### 题目内容（中文重写）
# 覆盖它！

## 题目描述
给定一个由 $n$ 个顶点和 $m$ 条边组成的无向、无权且连通的图。保证给定的图中没有自环或重边。

你的任务是在这个图中选择至多 $\lfloor\frac{n}{2}\rfloor$ 个顶点，使得每个未被选择的顶点都与至少一个被选择的顶点相邻（换句话说，通过一条边相连）。

保证存在答案。如果有多个答案，你可以输出任意一个。

你将得到多个独立的查询并需要进行回答。

## 说明/提示
在第一个查询中，任何一个顶点或任意一对顶点都可以满足条件。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1176E/425f889a93c1cbf45927e909f714357cbb29729c.png)
请注意，你不必使选择的顶点数量最小化。在第二个查询中，两个顶点就足够了（顶点 $2$ 和 $4$），但选择三个顶点也是可以的。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1176E/95acc958b4ac046071fd74b6c58c6e3e5d349deb.png)

## 样例 #1
### 输入
```
2
4 6
1 2
1 3
1 4
2 3
2 4
3 4
6 8
2 5
5 4
4 3
4 1
1 3
2 3
2 6
5 6
```

### 输出
```
2
1 3
3
4 3 6
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路大多是将图中的点按某种规则划分成两个集合，然后选择元素数量较少的那个集合作为答案，以此保证所选顶点数不超过 $\lfloor\frac{n}{2}\rfloor$。

- **思路对比**：大部分题解通过深度优先搜索（DFS）或广度优先搜索（BFS）遍历图，依据点的深度奇偶性、染色情况等进行划分。而 `registerGen` 的题解采用贪心策略，直接枚举结点进行集合划分。
- **算法要点**：多数题解利用 DFS 或 BFS 构建生成树，进而按深度奇偶性划分点集；贪心解法则是直接枚举结点，根据相邻关系划分集合。
- **解决难点**：关键在于证明划分出的两个集合中必有一个大小不超过 $\lfloor\frac{n}{2}\rfloor$，以及确保未被选择的点都与至少一个被选择的点相邻。

### 所选题解
- **hzjnsy（4星）**
    - **关键亮点**：思路简洁清晰，直接点明利用 DFS 找搜索树，按深度奇偶性划分点集，必有一个点集大小不超过 $\lfloor\frac{n}{2}\rfloor$，时间和空间复杂度分析明确。
- **registerGen（4星）**
    - **关键亮点**：采用贪心策略，不依赖生成树，直接枚举结点进行集合划分，代码实现详细且逻辑清晰。
- **Ryo_Yamada（4星）**
    - **关键亮点**：同样基于生成树的 DFS 方法，思路清晰，代码简洁，对生成树的处理方式有一定参考价值。

### 重点代码
#### hzjnsy
核心思路：先 DFS 找出搜索树，按深度奇偶性划分点集，选择较小的点集。
```cpp
// 伪代码，具体实现可参考原链接
// dfs 找出搜索树并划分点集
// 选择较小的点集作为答案
```

#### registerGen
核心思路：贪心枚举结点，将未访问的结点 $u$ 加入集合 $S$，其相邻未访问结点 $v$ 加入集合 $T$，最后输出较小的集合。
```cpp
#include <algorithm>
#include <cstdio>

const int N = 2e5;

struct Edge {
  int to, nxt;
} e[N * 2 + 10];
int head[N + 10], tote;
void addEdge(int u, int v) {
  e[++tote] = {v, head[u]};
  head[u] = tote;
}

int n, m, col[N + 10];
bool vis[N + 10];

void mian() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v; scanf("%d%d", &u, &v);
    addEdge(u, v), addEdge(v, u);
  }
  for (int u = 1; u <= n; u++)
    if (!vis[u]) {
      vis[u] = 1;
      col[u] = 1; // 加入集合 S
      for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (!vis[v]) {
          vis[v] = 1;
          col[v] = 2; // 加入集合 T
        }
      }
    }
  int cnt = 0;
  for (int i = 1; i <= n; i++)
    if (col[i] == 1) cnt++;
  if (cnt <= n / 2) {
    printf("%d\n", cnt);
    for (int i = 1; i <= n; i++)
      if (col[i] == 1) printf("%d ", i);
  } else {
    printf("%d\n", n - cnt);
    for (int i = 1; i <= n; i++)
      if (col[i] == 2) printf("%d ", i);
  }
  puts("");
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    for (int i = 1; i <= n; i++)
      head[i] = vis[i] = col[i] = 0;
    tote = 0;
    mian();
  }
  return 0;
}
```

#### Ryo_Yamada
核心思路：对每个连通块的生成树进行 DFS，按深度奇偶性划分点集，选择较小的点集加入答案。
```cpp
def(N, int, 2e5 + 5)

int n, m;
int c[2];
vector<int> e[N];
bool vis[N];
int dep[N];
vector<int> ans, d[2];

void dfs(int u, int Fa) {
	vis[u] = 1;
	dep[u] = dep[Fa] + 1;
	++c[dep[u] & 1];
	d[dep[u] & 1].pb(u);
	for(int v : e[u]) if(!vis[v]) dfs(v, u);
}

int main() {
	int t; qread(t);
	W(t) {
		ans.clear();
		qread(n, m);
		rep(i, 1, n) vis[i] = 0, e[i].clear();
		rep(i, 1, m) {
			int u, v;
			qread(u, v);
			e[u].pb(v), e[v].pb(u);
		}
		rep(i, 1, n) if(!vis[i]) {
			d[0].clear(), d[1].clear();
			c[0] = c[1] = 0;
			dfs(i, 0);
			if(c[0] > c[1]) for(int v : d[1]) ans.pb(v);
			else for(int v : d[0]) ans.pb(v);
		}
		cout << ans.size() << endl;
		for(int u : ans) printf("%d ", u);
		puts("");
	}
	return 0;
}
```

### 最优关键思路或技巧
- **划分点集**：利用 DFS 或 BFS 遍历图，按深度奇偶性、染色情况等将点划分为两个集合，选择较小的集合作为答案，保证所选顶点数不超过 $\lfloor\frac{n}{2}\rfloor$。
- **贪心策略**：直接枚举结点，根据相邻关系划分集合，避免生成树的构建。

### 拓展思路
同类型题目可能会改变图的性质（如有权图、有向图）或增加其他限制条件（如最小化选择的顶点数），但核心思路仍可围绕图的遍历和点集划分展开。类似算法套路包括二分图染色、树的遍历等。

### 推荐题目
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)
- [P2814 家谱](https://www.luogu.com.cn/problem/P2814)
- [P3366 最小生成树](https://www.luogu.com.cn/problem/P3366)

### 个人心得摘录与总结
部分作者认为题目难度被高估，实际难度较低。在解题时，要注意多组数据的清空操作，避免数据残留导致错误。

---
处理用时：61.19秒