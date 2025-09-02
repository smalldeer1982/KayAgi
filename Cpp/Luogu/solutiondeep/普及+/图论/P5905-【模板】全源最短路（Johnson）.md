# 题目信息

# 【模板】全源最短路（Johnson）

## 题目描述

给定一个包含 $n$ 个结点和 $m$ 条带权边的有向图，求所有点对间的最短路径长度，一条路径的长度定义为这条路径上所有边的权值和。

注意：

1. 边权**可能**为负，且图中**可能**存在重边和自环；

2. 部分数据卡 $n$ 轮 SPFA 算法。



## 说明/提示

【样例解释】

左图为样例 $1$ 给出的有向图，最短路构成的答案矩阵为：

```
0 4 11 8 11 
1000000000 0 7 4 7 
1000000000 -5 0 -3 0 
1000000000 -2 5 0 3 
1000000000 -1 4 1 0 
```

右图为样例 $2$ 给出的有向图，红色标注的边构成了负环，注意给出的图不一定连通。

![](https://cdn.luogu.com.cn/upload/image_hosting/7lb35u4u.png)

【数据范围】

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^3,\ \ 1\leq m\leq 6\times 10^3,\ \ 1\leq u,v\leq n,\ \ -3\times 10^5\leq w\leq 3\times 10^5$。

对于 $20\%$ 的数据，$1\leq n\leq 100$，不存在负环（可用于验证 Floyd 正确性）

对于另外 $20\%$ 的数据，$w\ge 0$（可用于验证 Dijkstra 正确性）

upd. 添加一组 Hack 数据：针对 SPFA 的 SLF 优化

## 样例 #1

### 输入

```
5 7
1 2 4
1 4 10
2 3 7
4 5 3
4 2 -2
3 4 -3
5 3 4```

### 输出

```
128
1000000072
999999978
1000000026
1000000014
```

## 样例 #2

### 输入

```
5 5
1 2 4
3 4 9
3 4 -3
4 5 3
5 3 -2```

### 输出

```
-1```

# AI分析结果

### 综合分析与结论
这些题解主要围绕 Johnson 全源最短路算法展开，用于解决含负权边的有向图的全源最短路问题。核心思路是通过添加虚拟节点，利用 Bellman - Ford 或 SPFA 算法计算势能，将边权重新标注为非负，再用 Dijkstra 算法求最短路。各题解在思路阐述、代码实现和复杂度分析上各有特点，但整体思路一致。

### 所选题解
- StudyingFather（5星）
    - 关键亮点：思路清晰，对 Johnson 算法的原理、正确性证明和复杂度分析详细，代码规范且有注释。
    - 个人心得：提到被各位 D 惨了，所以把代码扔到 clang - format 里格式化了下，体现了对代码规范性的重视。
- ix35（4星）
    - 关键亮点：思路简洁明了，对几种常见最短路算法的复杂度和适用场景进行了对比，代码有详细注释。
- Mine_King（4星）
    - 关键亮点：对 Johnson 算法的实现方法和正确性证明详细，通过具体例子说明边权调整的过程，代码实现中注意了处理精度问题。

### 重点代码及核心实现思想
#### StudyingFather 的题解
```cpp
// 添加边
void addedge(int u, int v, int w) {
  e[++cnt].v = v;
  e[cnt].w = w;
  e[cnt].next = head[u];
  head[u] = cnt;
}
// SPFA 算法求势能并判负环
bool spfa(int s) {
  queue<int> q;
  memset(h, 63, sizeof(h));
  h[s] = 0, vis[s] = 1;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = 0;
    for (int i = head[u]; i; i = e[i].next) {
      int v = e[i].v;
      if (h[v] > h[u] + e[i].w) {
        h[v] = h[u] + e[i].w;
        if (!vis[v]) {
          vis[v] = 1;
          q.push(v);
          t[v]++;
          if (t[v] == n + 1) return false;
        }
      }
    }
  }
  return true;
}
// Dijkstra 算法求单源最短路
void dijkstra(int s) {
  priority_queue<node> q;
  for (int i = 1; i <= n; i++) dis[i] = INF;
  memset(vis, 0, sizeof(vis));
  dis[s] = 0;
  q.push(node(0, s));
  while (!q.empty()) {
    int u = q.top().id;
    q.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next) {
      int v = e[i].v;
      if (dis[v] > dis[u] + e[i].w) {
        dis[v] = dis[u] + e[i].w;
        if (!vis[v]) q.push(node(dis[v], v));
      }
    }
  }
  return;
}
```
核心实现思想：先使用 SPFA 算法从虚拟节点出发求势能并判断负环，若存在负环则直接返回 - 1；若不存在负环，将边权重新标注为非负，再以每个点为起点，使用 Dijkstra 算法求单源最短路，最后根据势能调整结果得到最终的最短路。

### 最优关键思路或技巧
- **势能调整边权**：通过添加虚拟节点，利用 Bellman - Ford 或 SPFA 算法计算势能，将边权重新标注为非负，使得可以使用 Dijkstra 算法求最短路。
- **负环判断**：在计算势能的过程中，通过记录节点入队次数判断是否存在负环。

### 可拓展之处
同类型题或类似算法套路：
- **网络流中的应用**：在最小费用最大流问题中，由于走反向边费用要取负，无法使用 Dijkstra 增广，可使用 Johnson 算法的思想将边权转为非负，然后用 Dijkstra 算法增广。
- **其他图算法的结合**：可以结合其他图算法，如拓扑排序、强连通分量等，解决更复杂的图问题。

### 推荐题目
- [P3385 【模板】负环](https://www.luogu.com.cn/problem/P3385)
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

### 个人心得总结
- StudyingFather：重视代码规范性，通过格式化代码提高代码可读性。
- ACMlearning：在学习 Johnson 算法的过程中，从 Bellman - Ford 算法开始学习，通过具体例子理解 Johnson 算法的正确性，体现了学习算法的过程和方法。
- king_xbz：为 SPFA 算法正名，提出堆优化 SPFA 算法与堆优化 Dij 分庭抗礼，展示了对算法的深入研究和创新思维。

---
处理用时：35.04秒