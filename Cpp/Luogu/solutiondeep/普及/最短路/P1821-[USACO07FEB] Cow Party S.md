# 题目信息

# [USACO07FEB] Cow Party S

## 题目描述

寒假到了，$n$ 头牛都要去参加一场在编号为 $x$ 的牛的农场举行的派对，农场之间有 $m$ 条有向路，每条路都有一定的长度。

每头牛参加完派对后都必须回家，无论是去参加派对还是回家，每头牛都会选择最短路径，求这 $n$ 头牛的最短路径（一个来回）中最长的一条路径长度。


## 说明/提示

### 样例 1 解释
![](https://cdn.luogu.com.cn/upload/image_hosting/rl3com2y.png)

### 数据规模与约定

对于全部的测试点，保证 $1 \leq x \leq n \leq 10^3$，$1 \leq m \leq 10^5$，$1 \leq u,v \leq n$，$1 \leq w \leq 10^2$，保证从任何一个结点出发都能到达 $x$ 号结点，且从 $x$ 出发可以到达其他所有节点。

## 样例 #1

### 输入

```
4 8 2
1 2 4
1 3 2
1 4 7
2 1 1
2 3 5
3 1 2
3 4 4
4 2 3
```

### 输出

```
10```

# AI分析结果

### 综合分析与结论

该题目要求计算每头牛从各自农场到派对农场的最短路径，以及从派对农场返回的最短路径，最终求所有牛中最长的往返路径。题解中主要使用了**Dijkstra**和**SPFA**两种最短路算法，并通过**反向建图**来简化单终点最短路径的计算。大多数题解思路相似，核心在于通过两次最短路计算（一次正向，一次反向）来解决问题。

### 高星题解推荐

#### 1. **My_666 (5星)**
- **关键亮点**：思路清晰，代码结构良好，使用了Dijkstra算法，并通过反向建图优化了单终点最短路径的计算。代码中详细注释了每一步的操作，适合初学者理解。
- **个人心得**：强调了使用Dijkstra而非SPFA的重要性，避免在竞赛中被卡数据。
- **核心代码**：
  ```cpp
  void dijkstra(int s) {
      memset(dis, 0x3f3f3f3f, sizeof(dis));
      priority_queue< pair<int, int> > q;
      q.push(make_pair(0, s));
      dis[s] = 0;
      while (q.size()) {
          int u = q.top().second;
          q.pop();
          if (vis[u]) continue;
          vis[u] = 1;
          for (int i = head[u]; i; i = e[i].nxt) {
              int v = e[i].to;
              if (dis[v] > dis[u] + e[i].w) {
                  dis[v] = dis[u] + e[i].w;
                  q.push(make_pair(-dis[v], v));
              }
          }
      }
  }
  ```

#### 2. **C_Cong (4星)**
- **关键亮点**：使用了SPFA算法，并通过反向建图简化了单终点最短路径的计算。代码结构清晰，适合对SPFA熟悉的读者。
- **核心代码**：
  ```cpp
  void spfa(int k) {
      memset(vis, 0, sizeof(vis));
      vis[l] = true;
      f[k][l] = 0;
      Q.push(l);
      while (!Q.empty()) {
          int news = Q.front();
          Q.pop();
          vis[news] = false;
          for (int i = 0; i < G[k][news].size(); i++) {
              int v = G[k][news][i].v, u = G[k][news][i].u;
              if (f[k][v] > f[k][news] + u) {
                  f[k][v] = f[k][news] + u;
                  if (!vis[v]) {
                      vis[v] = true;
                      Q.push(v);
                  }
              }
          }
      }
  }
  ```

#### 3. **King丨帝御威 (4星)**
- **关键亮点**：使用了堆优化的Dijkstra算法，代码结构清晰，适合对堆优化Dijkstra熟悉的读者。强调了堆优化Dijkstra的实用性。
- **核心代码**：
  ```cpp
  void dijkstra() {
      memset(dis, 0x3f, sizeof(dis));
      priority_queue<node> q;
      q.push((node){s, 0});
      dis[s] = 0;
      while (!q.empty()) {
          node q = q.top(); q.pop();
          int u = q.pnt;
          if (len > d[u]) continue;
          for (int i = head[u]; i; i = edge[i].nxt) {
              int v = edge[i].to;
              if (d[v] > d[u] + edge[i].val) {
                  d[v] = d[u] + edge[i].val;
                  q.push((node){v, d[v]});
              }
          }
      }
  }
  ```

### 最优关键思路与技巧

1. **反向建图**：通过反向建图，将单终点最短路径问题转化为单源最短路径问题，简化了计算。
2. **堆优化Dijkstra**：堆优化的Dijkstra算法在稀疏图中效率较高，适合处理大规模数据。
3. **SPFA与Dijkstra的选择**：在竞赛中，Dijkstra通常比SPFA更稳定，避免被卡数据。

### 可拓展之处

1. **多源最短路径**：类似问题可以扩展到多源最短路径，使用Floyd算法或多次Dijkstra。
2. **动态图最短路径**：如果图中边权动态变化，可以考虑使用动态最短路径算法。

### 推荐题目

1. **P3371 【模板】单源最短路径（弱化版）**：练习Dijkstra和SPFA的基础题目。
2. **P4779 【模板】单源最短路径（标准版）**：练习堆优化Dijkstra的题目。
3. **P1144 最短路计数**：在最短路径的基础上，统计最短路径的数量。

### 个人心得总结

- **调试经历**：部分题解提到在调试过程中发现反向建图的重要性，避免重复计算。
- **踩坑教训**：强调了SPFA的不稳定性，建议在竞赛中使用Dijkstra。
- **顿悟感想**：通过反向建图，简化了单终点最短路径的计算，提升了代码效率。

---
处理用时：42.59秒