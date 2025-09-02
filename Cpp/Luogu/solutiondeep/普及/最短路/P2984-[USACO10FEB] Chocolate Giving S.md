# 题目信息

# [USACO10FEB] Chocolate Giving S

## 题目描述

FJ 有 $B$ 头奶牛 $(1\le B\le 25000)$，有 $N(2\times B\le N\le 50000)$ 个农场，编号 $1$ 到 $N$，有 $M(N-1\le M\le 100000)$ 条双向边，第 $i$ 条边连接农场 $R_i$ 和 $S_i(1\le R_i\le N, 1\le S_i\le N)$，该边的长度是 $L_i(1\le L_i\le 2000)$。居住在农场 $P_i$ 的奶牛 A $(1\le P_i\le N)$，想送一份新年礼物给居住在农场 $Q_i(1\le Q_i\le N)$ 的奶牛 B，但是奶牛 A 必须先到 FJ（居住在编号 $1$ 的农场）那里取礼物，然后再送给奶牛 B。你的任务是：奶牛 A 至少需要走多远的路程？

## 样例 #1

### 输入

```
6 7 3 
1 2 3 
5 4 3 
3 1 1 
6 1 9 
3 4 2 
1 4 4 
3 2 2 
2 4 
5 1 
3 6 
```

### 输出

```
6 
6 
10 
```

# AI分析结果

### 综合分析与结论

本题的核心是求解从农场1到其他农场的最短路径，然后根据查询输出两个农场到农场1的最短路径之和。由于是无向图，从农场A到农场1的最短路径等于从农场1到农场A的最短路径，因此只需从农场1出发跑一次最短路即可。大多数题解都采用了Dijkstra或SPFA算法，部分题解通过堆优化或配对堆进一步提升了效率。

### 所选高星题解

#### 1. **封禁用户 (5星)**
- **关键亮点**：使用Dijkstra算法，并通过堆优化提升效率。代码简洁清晰，注释详细，逻辑严谨。
- **个人心得**：作者提到“这世界上不缺少什么水题，而是缺少发现水题的眼睛”，强调了理解题意的重要性。
- **核心代码**：
  ```cpp
  void dijkstra(int s) {
      priority_queue<P, vector<P>, greater<P>> q;
      for (int i = 1; i <= n; i++) d[i] = 1e9;
      d[s] = 0;
      q.push(P{0, s});
      while (!q.empty()) {
          P p = q.top(); q.pop();
          int v = p.second;
          if (d[v] < p.first) continue;
          for (int i = 0; i < G[v].size(); i++) {
              edge e = G[v][i];
              if (d[e.to] > d[v] + e.cost) {
                  d[e.to] = d[v] + e.cost;
                  q.push(P{d[e.to], e.to});
              }
          }
      }
  }
  ```
  **实现思想**：使用优先队列优化的Dijkstra算法，每次从队列中取出距离最小的点进行松弛操作。

#### 2. **小糯米 (4星)**
- **关键亮点**：通过配对堆优化Dijkstra算法，进一步提升了效率。代码结构清晰，注释详细。
- **个人心得**：作者提到“Dijkstra这道题不太行得通”，并尝试了配对堆优化，最终AC。
- **核心代码**：
  ```cpp
  void dijkstra() {
      PairingHeap<State> ph;
      for (long long i = 1; i <= n; ++i) d[i] = 2147483647;
      d[s] = 0;
      for (long long i = 1; i <= n; ++i) nps[i] = ph.insert(State{d[i], i});
      while (!ph.isEmpty()) {
          State ts; ph.deleteMin(ts);
          long long u = ts.nid;
          d[u] = ts.dis;
          nps[u] = nullptr;
          for (long long i = 0; i < g[u].size(); ++i) {
              long long v = g[u][i].v, w = g[u][i].w;
              if (d[v] > d[u] + w && nps[v] != nullptr) {
                  d[v] = d[u] + w;
                  ph.decreaseKey(nps[v], State{d[v], v});
              }
          }
      }
  }
  ```
  **实现思想**：使用配对堆优化的Dijkstra算法，通过减少堆操作的时间复杂度来提升整体效率。

#### 3. **L_Y_T (4星)**
- **关键亮点**：通过多次尝试优化SPFA算法，最终通过扩大数组范围解决了RE问题。代码结构清晰，注释详细。
- **个人心得**：作者提到“交了九九八十一遍，最后终于过了”，强调了调试和优化的重要性。
- **核心代码**：
  ```cpp
  void spfa(ll s) {
      queue<ll>q;
      for(ll i = 1 ; i <= n ; i ++) dis[i] = inf;
      memset(vis , false , sizeof(vis)) ;
      q.push(s) ;
      dis[s] = 0 ;
      while(!q.empty()) {
          ll u = q.front() ;
          q.pop() ;
          vis[u] = 0 ;
          for(ll i = head[u] ; i != -1 ; i = a[i].next ) {
              ll v = a[i].y ;
              if(dis[v] > dis[u] + a[i].z) {
                  dis[v] = dis[u] + a[i].z ;
                  if(!vis[v]) {
                      vis[v] = true ;
                      q.push(v) ;
                  }
              }
          }
      }
  }
  ```
  **实现思想**：使用SPFA算法，通过队列进行松弛操作，最终通过扩大数组范围解决了RE问题。

### 最优关键思路与技巧

1. **Dijkstra算法**：适用于无负权边的图，通过优先队列优化可以提升效率。
2. **SPFA算法**：适用于存在负权边的图，但时间复杂度不稳定，容易被卡。
3. **配对堆优化**：通过减少堆操作的时间复杂度，进一步提升Dijkstra算法的效率。

### 可拓展之处

- **同类型题**：类似的最短路问题可以通过Dijkstra或SPFA算法解决，如[P4779](https://www.luogu.org/problem/P4779)。
- **算法套路**：在无负权边的图中，优先使用Dijkstra算法；在存在负权边的图中，使用SPFA算法。

### 推荐题目

1. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.org/problem/P4779)
2. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.org/problem/P3371)
3. [P2984 【USACO10FEB】Chocolate Giving S](https://www.luogu.org/problem/P2984)

### 个人心得总结

- **调试与优化**：多次调试和优化是解决问题的关键，如L_Y_T通过扩大数组范围解决了RE问题。
- **理解题意**：理解题意并找到最优解法是解决问题的第一步，如封禁用户通过一次Dijkstra算法解决了问题。

---
处理用时：50.06秒