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
这些题解均围绕 Johnson 全源最短路算法展开，旨在解决带负权边的有向图中所有点对间的最短路径问题。各题解思路基本一致，先通过添加虚拟节点和 Bellman - Ford（或 SPFA）算法判断负环并计算各点势能，再利用势能将边权转换为非负，最后用 Dijkstra 算法计算最短路。

### 所选题解
- **作者：StudyingFather（5星）**
    - **关键亮点**：思路清晰，对 Johnson 算法的原理和正确性证明详细且易懂，代码经过格式化，可读性高。
    - **个人心得**：无

### 重点代码
```cpp
// 加边函数
void addedge(int u, int v, int w) {
  e[++cnt].v = v;
  e[cnt].w = w;
  e[cnt].next = head[u];
  head[u] = cnt;
}

// SPFA 算法判断负环并计算势能
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

// Dijkstra 算法计算最短路
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

// 主函数
int main() {
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    addedge(u, v, w);
  }
  for (int i = 1; i <= n; i++) addedge(0, i, 0);
  if (!spfa(0)) {
    cout << -1 << endl;
    return 0;
  }
  for (int u = 1; u <= n; u++)
    for (int i = head[u]; i; i = e[i].next) e[i].w += h[u] - h[e[i].v];
  for (int i = 1; i <= n; i++) {
    dijkstra(i);
    long long ans = 0;
    for (int j = 1; j <= n; j++) {
      if (dis[j] == INF)
        ans += j * INF;
      else
        ans += j * (dis[j] + h[j] - h[i]);
    }
    cout << ans << endl;
  }
  return 0;
}
```
**核心实现思想**：
1. **加边函数**：使用链式前向星存储图的边信息。
2. **SPFA 算法**：从虚拟节点开始，通过不断更新各点的最短距离（势能），并判断是否存在负环。
3. **Dijkstra 算法**：以每个点为起点，使用优先队列优化，计算最短路。
4. **主函数**：读取输入，添加虚拟节点和边，调用 SPFA 判断负环，更新边权，再调用 Dijkstra 计算最短路并输出结果。

### 最优关键思路或技巧
- **虚拟节点的引入**：通过添加一个虚拟节点并向所有节点连边权为 0 的边，方便使用 Bellman - Ford（或 SPFA）算法计算各点的势能。
- **势能的运用**：利用势能将负权边转换为非负权边，使得可以使用 Dijkstra 算法，同时保证最短路的正确性。

### 可拓展之处
同类型题或类似算法套路：
- 最小费用最大流问题：Johnson 算法的思想可用于将负权边转换为非负权边，从而使用 Dijkstra 算法求解最短增广路。
- 带负权边的单源最短路问题：可使用 Johnson 算法的预处理步骤，将负权边转换为非负权边后再用 Dijkstra 算法求解。

### 推荐题目
1. [P3385 【模板】负环](https://www.luogu.com.cn/problem/P3385)
2. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
3. [P2047 [NOI2007] 社交网络](https://www.luogu.com.cn/problem/P2047)

### 个人心得摘录与总结
- **ACMlearning**：刚开始准备用 spfa 直接判断负环，发现不能处理非连通图的负环，后来建虚拟点解决了该问题。总结：在处理负环判断时，对于非连通图要考虑添加虚拟点。
- **king_xbz**：认为 SPFA 虽容易被卡，但通过堆优化 SPFA 可以与堆优化 Dij 分庭抗礼。总结：对于容易被卡的算法，可以尝试进行优化来提高性能。

---
处理用时：38.61秒