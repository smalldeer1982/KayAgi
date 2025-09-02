# 题目信息

# [USACO06DEC] Cow Picnic S

## 题目描述

The cows are having a picnic! Each of Farmer John's K (1 ≤ K ≤ 100) cows is grazing in one of N (1 ≤ N ≤ 1,000) pastures, conveniently numbered 1...N. The pastures are connected by M (1 ≤ M ≤ 10,000) one-way paths (no path connects a pasture to itself).

The cows want to gather in the same pasture for their picnic, but (because of the one-way paths) some cows may only be able to get to some pastures. Help the cows out by figuring out how many pastures are reachable by all cows, and hence are possible picnic locations.

$K(1 \le K \le 100)$ 只奶牛分散在 $N(1 \le N \le 1000)$ 个牧场．现在她们要集中起来进餐。牧场之间有 $M(1 \le M \le 10000)$ 条有向路连接，而且不存在起点和终点相同的有向路．她们进餐的地点必须是所有奶牛都可到达的地方。那么，有多少这样的牧场可供进食呢？

## 说明/提示

The cows can meet in pastures 3 or 4.


## 样例 #1

### 输入

```
2 4 4
2
3
1 2
1 4
2 3
3 4```

### 输出

```
2```

# AI分析结果

### 综合分析与结论

本题的核心问题是如何找到所有奶牛都能到达的牧场。题解中主要采用了DFS、BFS、以及最短路算法（如Dijkstra、SPFA）来解决。大多数题解通过遍历每个奶牛所在的牧场，记录每个牧场被访问的次数，最终统计被所有奶牛访问过的牧场数量。部分题解通过反向建图优化了搜索效率。

### 所选高星题解

#### 1. 作者：xueyangkai (赞：133)
- **星级**：5星
- **关键亮点**：
  - 使用DFS遍历每个奶牛所在的牧场，记录每个牧场被访问的次数。
  - 代码简洁，思路清晰，易于理解。
  - 通过`mk`数组记录每个牧场被访问的次数，最终统计`mk[i] == k`的牧场数量。
- **核心代码**：
  ```cpp
  void dfs(int x) {
      vis[x] = 1;  mk[x]++;
      for(int i = 0; i < b[x].size(); i++)
          if(!vis[b[x][i]])
              dfs(b[x][i]);
  }
  ```
- **个人心得**：无

#### 2. 作者：Lates (赞：14)
- **星级**：4星
- **关键亮点**：
  - 使用反向建图，从每个牧场出发，判断是否能到达所有奶牛所在的牧场。
  - 通过`vis`数组记录每个牧场是否被访问，最终统计满足条件的牧场数量。
  - 代码结构清晰，优化了搜索效率。
- **核心代码**：
  ```cpp
  void dfs(int now) {
      vis[now] = 1;
      for(register int i = head[now]; i; i = e[i].next) {
          if(!vis[e[i].e]) dfs(e[i].e);
      }
  }
  ```
- **个人心得**：作者提到第一次提交时忘记清空`vis`数组，导致WA，提醒了在DFS中清空标记数组的重要性。

#### 3. 作者：Khassar (赞：7)
- **星级**：4星
- **关键亮点**：
  - 使用BFS遍历每个奶牛所在的牧场，记录每个牧场被访问的次数。
  - 通过`cnt`数组记录每个牧场被访问的次数，最终统计`cnt[i] == k`的牧场数量。
  - 代码结构清晰，易于理解。
- **核心代码**：
  ```cpp
  void bfs(int x) {
      queue<int> q;
      q.push(x);
      vis[x] = 1;
      while(!q.empty()) {
          int u = q.front();
          q.pop();
          for(int i = head[u]; i; i = e[i].next) {
              int v = e[i].to;
              if(!vis[v]) {
                  vis[v] = 1;
                  s[v]++;
                  q.push(v);
              }
          }
      }
  }
  ```
- **个人心得**：无

### 最优关键思路与技巧
1. **DFS/BFS遍历**：通过DFS或BFS遍历每个奶牛所在的牧场，记录每个牧场被访问的次数，最终统计被所有奶牛访问过的牧场数量。
2. **反向建图**：通过反向建图，从每个牧场出发，判断是否能到达所有奶牛所在的牧场，优化了搜索效率。
3. **标记数组清空**：在每次DFS/BFS遍历前，清空标记数组，确保每次遍历的独立性。

### 可拓展之处
- **同类型题**：类似的问题可以扩展到其他图论问题，如寻找所有节点都能到达的节点、判断图的连通性等。
- **算法套路**：DFS/BFS遍历、反向建图、标记数组清空等技巧在其他图论问题中也经常使用。

### 推荐题目
1. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
2. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)
3. [P3916 图的遍历](https://www.luogu.com.cn/problem/P3916)

---
处理用时：36.23秒