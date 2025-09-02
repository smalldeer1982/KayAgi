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
题目要求找出所有奶牛都能到达的牧场数目。各题解主要采用以下思路：
1. **正向遍历法**：对每头牛进行DFS/BFS，统计每个牧场的访问次数，最后筛选次数等于K的牧场。
2. **反向建边法**：反向构建图后，枚举每个牧场作为聚集点，检查是否能到达所有奶牛的位置。
3. **最短路法**：通过SPFA/Dijkstra计算可达性，但效率较低。

最优思路为**正向遍历法**，时间复杂度为O(K*(N+M))，在题目数据范围内可行且代码简洁。反向建边法在K较大时效率较低，最短路法不推荐。

---

### 精选题解与评分

#### 题解1：作者 xueyangkai（★★★★★）
**关键亮点**：  
- 代码简洁，使用DFS+邻接表，逻辑清晰。  
- 用全局计数器`mk[]`记录每个牧场的访问次数，最后直接统计结果。  
**核心代码**：
```cpp
void dfs(int x) {
    vis[x] = 1;  mk[x]++;
    for (int i = 0; i < b[x].size(); i++)
        if (!vis[b[x][i]]) dfs(b[x][i]);
}
// 调用方式：对每头牛重置vis后调用dfs
```

#### 题解2：作者 Khassar（★★★★☆）
**关键亮点**：  
- 使用BFS替代DFS，避免递归栈溢出风险。  
- 队列实现清晰，适合大规模数据。  
**核心代码**：
```cpp
void bfs(int now) {
    queue<int> q;
    q.push(now);
    vis[now] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].to;
            if (!vis[v]) {
                vis[v] = 1; s[v]++;
                q.push(v);
            }
        }
    }
}
```

#### 题解3：作者 灵光一闪（★★★★☆）
**关键亮点**：  
- 邻接矩阵实现，代码直观。  
- 动态重置访问数组，避免状态污染。  
**核心代码**：
```cpp
void dfs(int x) {
    vis[x] = true; cnt[x]++;
    for (int y : edges[x])
        if (!vis[y]) dfs(y);
}
```

---

### 关键技巧总结
1. **遍历方向选择**：优先从奶牛位置出发遍历图，而非反向枚举聚集点。
2. **邻接表优化**：使用`vector`或链式前向星存储稀疏图，避免邻接矩阵空间浪费。
3. **状态重置**：每次DFS/BFS前必须重置访问数组，防止状态残留。
4. **计数器复用**：用全局数组记录访问次数，减少重复计算。

---

### 拓展与举一反三
1. **类似题目**：  
   - P2863 [USACO06JAN] The Prom-强连通分量（可达性统计）。  
   - P3916 图的遍历（反向建边优化）。  
   - P4017 最大食物链计数（拓扑排序+路径计数）。  
2. **算法套路**：  
   - **多源可达性统计**：通过多次遍历累加结果，适用于路径覆盖问题。  
   - **反向思维**：当正向遍历复杂时，考虑反向建边或逆向逻辑。  

---

### 个人心得摘录
- **梦里调音**：初始思路错误（牧场找奶牛），效率低下，转换思路后AC。  
- **Khassar**：强调BFS在拓展可达点时的优势，避免DFS递归深度问题。  
- **说好不哭**：使用BFS时需注意队列的初始化与状态管理，避免漏判。  

（总结：问题转化和数据结构选择对效率至关重要，调试时需重点关注状态重置和边界条件。）

---
处理用时：65.56秒