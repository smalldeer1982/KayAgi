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

该题目要求找到所有奶牛都能到达的牧场数量，本质上是图的遍历问题。大多数题解采用了DFS或BFS进行遍历，部分题解使用了反向建边、最短路算法（如Dijkstra、SPFA）等优化手段。整体来看，DFS和BFS是主流解法，反向建边和最短路的思路较为新颖，但实现复杂度较高。

### 所选高分题解

#### 1. 题解作者：xueyangkai (赞：133)
- **星级**：5星
- **关键亮点**：使用DFS遍历每个奶牛所在的牧场，通过计数数组`mk`记录每个牧场被访问的次数，最后统计`mk[i] == k`的牧场数量。思路清晰，代码简洁，且使用了`vector`存储图结构，适合无向图或有向图的遍历。
- **个人心得**：无
- **核心代码**：
  ```cpp
  void dfs(int x) {
      vis[x] = 1;  mk[x]++;
      for(int i = 0; i < b[x].size(); i++)
          if(!vis[b[x][i]])
              dfs(b[x][i]);
  }
  ```

#### 2. 题解作者：Khassar (赞：7)
- **星级**：4星
- **关键亮点**：使用BFS遍历每个奶牛所在的牧场，通过计数数组`cnt`记录每个牧场被访问的次数，最后统计`cnt[i] == k`的牧场数量。BFS适合处理大规模数据，且代码结构清晰。
- **个人心得**：无
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

#### 3. 题解作者：Lates (赞：14)
- **星级**：4星
- **关键亮点**：采用反向建边+DFS的思路，通过枚举每个牧场作为野餐地点，判断是否所有奶牛都能到达该牧场。反向建边的思路较为新颖，适合处理有向图的遍历问题。
- **个人心得**：作者提到第一次提交时忘记清空`vis`数组，导致WA，提醒了在DFS时要注意数组的初始化。
- **核心代码**：
  ```cpp
  void dfs(int now) {
      vis[now] = 1;
      for(register int i = head[now]; i; i = e[i].next) {
          if(!vis[e[i].e]) dfs(e[i].e);
      }
  }
  ```

### 最优关键思路与技巧
1. **DFS/BFS遍历**：DFS和BFS是解决图遍历问题的经典方法，适合处理大规模数据。
2. **反向建边**：通过反向建边，可以将问题转化为从目标点出发的遍历，简化了问题的复杂度。
3. **计数数组**：通过计数数组记录每个牧场被访问的次数，最后统计符合条件的牧场数量，是一种简单有效的统计方法。

### 可拓展之处
- **最短路算法**：虽然DFS/BFS是主流解法，但在某些情况下，最短路算法（如Dijkstra、SPFA）可以提供更优的解决方案，尤其是在边权不为1的情况下。
- **图的连通性**：该问题可以拓展为判断图的连通性，或者寻找图中的强连通分量。

### 推荐题目
1. **P3371 【模板】单源最短路径（弱化版）**（考察最短路算法）
2. **P3916 图的遍历**（考察图的遍历与连通性）
3. **P3388 【模板】割点（割顶）**（考察图的割点与连通性）

### 个人心得总结
- **调试经验**：部分作者提到在DFS时忘记清空`vis`数组，导致WA，提醒了在遍历时要注意数组的初始化。
- **优化思路**：反向建边和最短路的思路虽然复杂，但在某些情况下可以提供更优的解决方案，值得深入学习。

---
处理用时：38.76秒