# 题目信息

# Counting Shortcuts

## 题目描述

Given an undirected connected graph with $ n $ vertices and $ m $ edges. The graph contains no loops (edges from a vertex to itself) and multiple edges (i.e. no more than one edge between each pair of vertices). The vertices of the graph are numbered from $ 1 $ to $ n $ .

Find the number of paths from a vertex $ s $ to $ t $ whose length differs from the shortest path from $ s $ to $ t $ by no more than $ 1 $ . It is necessary to consider all suitable paths, even if they pass through the same vertex or edge more than once (i.e. they are not simple).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650G/3360dade3a147f98c6dd4b25980520a2ae6123a6.png)Graph consisting of $ 6 $ of vertices and $ 8 $ of edgesFor example, let $ n = 6 $ , $ m = 8 $ , $ s = 6 $ and $ t = 1 $ , and let the graph look like the figure above. Then the length of the shortest path from $ s $ to $ t $ is $ 1 $ . Consider all paths whose length is at most $ 1 + 1 = 2 $ .

- $ 6 \rightarrow 1 $ . The length of the path is $ 1 $ .
- $ 6 \rightarrow 4 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 2 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 5 \rightarrow 1 $ . Path length is $ 2 $ .

There is a total of $ 4 $ of matching paths.

## 样例 #1

### 输入

```
4

4 4
1 4
1 2
3 4
2 3
2 4

6 8
6 1
1 4
1 6
1 5
1 2
5 6
4 6
6 3
2 6

5 6
1 3
3 5
5 4
3 1
4 2
2 1
1 4

8 18
5 1
2 1
3 1
4 2
5 2
6 5
7 3
8 4
6 4
8 7
1 4
4 7
1 6
6 7
3 8
8 5
4 5
4 3
8 2```

### 输出

```
2
4
1
11```

# AI分析结果

### 题目内容重写

给定一个无向连通图，包含 $n$ 个顶点和 $m$ 条边。图中没有自环（即没有从顶点到自身的边）和重边（即每对顶点之间最多只有一条边）。图的顶点编号从 $1$ 到 $n$。

要求找到从顶点 $s$ 到顶点 $t$ 的路径数量，这些路径的长度与从 $s$ 到 $t$ 的最短路径长度的差值不超过 $1$。需要考虑所有符合条件的路径，即使它们经过相同的顶点或边多次（即路径不一定是简单的）。

例如，设 $n = 6$，$m = 8$，$s = 6$，$t = 1$，图的结构如上图所示。从 $s$ 到 $t$ 的最短路径长度为 $1$。考虑所有长度不超过 $1 + 1 = 2$ 的路径：

- $6 \rightarrow 1$，路径长度为 $1$。
- $6 \rightarrow 4 \rightarrow 1$，路径长度为 $2$。
- $6 \rightarrow 2 \rightarrow 1$，路径长度为 $2$。
- $6 \rightarrow 5 \rightarrow 1$，路径长度为 $2$。

总共有 $4$ 条符合条件的路径。

### 样例 #1

#### 输入

```
4

4 4
1 4
1 2
3 4
2 3
2 4

6 8
6 1
1 4
1 6
1 5
1 2
5 6
4 6
6 3
2 6

5 6
1 3
3 5
5 4
3 1
4 2
2 1
1 4

8 18
5 1
2 1
3 1
4 2
5 2
6 5
7 3
8 4
6 4
8 7
1 4
4 7
1 6
6 7
3 8
8 5
4 5
4 3
8 2
```

#### 输出

```
2
4
1
11
```

### 题解分析与结论

#### 综合分析与结论

本题的核心问题是在无向连通图中，计算从起点 $s$ 到终点 $t$ 的路径数量，这些路径的长度与最短路径长度的差值不超过 $1$。由于路径可以重复经过顶点和边，因此问题的难点在于如何高效地计算这些路径的数量。

各题解的思路主要集中在以下几个方面：

1. **分层图与BFS**：通过BFS对图进行分层，计算从 $s$ 到各点的最短路径长度，并利用层内边和层间边的性质来统计符合条件的路径数量。
2. **动态规划（DP）**：通过DP状态转移，记录从 $s$ 到各点的路径数量，并根据路径长度与最短路径的差值进行分类统计。
3. **Dijkstra算法**：利用Dijkstra算法计算最短路径，并在过程中统计次短路径的数量。

#### 所选高星题解

1. **作者：StudyingFather (赞：16)**  
   - **星级：5星**  
   - **关键亮点**：通过BFS对图进行分层，利用层内边和层间边的性质，巧妙地统计了符合条件的路径数量。代码简洁且高效，时间复杂度为 $O(n + m)$。  
   - **核心代码**：
     ```cpp
     void bfs(int s, int* dis, int* f) {
       queue<int> q;
       memset(dis, -1, sizeof(int) * (n + 1));
       memset(f, 0, sizeof(int) * (n + 1));
       dis[s] = 0, f[s] = 1;
       q.push(s);
       while (!q.empty()) {
         int u = q.front();
         q.pop();
         for (auto v : e[u])
           if (dis[v] == -1) {
             dis[v] = dis[u] + 1;
             f[v] = f[u];
             q.push(v);
           } else if (dis[v] == dis[u] + 1)
             f[v] = (f[v] + f[u]) % mod;
       }
     }
     ```

2. **作者：char_phi (赞：13)**  
   - **星级：4星**  
   - **关键亮点**：通过Dijkstra算法计算最短路径，并在过程中统计次短路径的数量。代码逻辑清晰，但时间复杂度较高，为 $O(n \log n)$。  
   - **核心代码**：
     ```cpp
     void Dijkstra() {
       int x = yd; for (re i = 1 ; i <= n ; ++ i) dis[i] = 0x3f3f3f3f, vis[i] = false;
       heap.push( (Node) {x, 0} ); dis[x] = 0;
       while (heap.empty() == false) {
         x = heap.top().x; heap.pop();
         if (vis[x] == true) continue;
         vis[x] = true;
         for (re i = head[x] ; i ; i = e[i].nxt) {
           int v = e[i].v;
           if (dis[v] > dis[x] + 1) {
             dis[v] = dis[x] + 1;
             if (vis[v] == false) heap.push( (Node) { v, dis[v] } );
           }
         }
       }
     }
     ```

3. **作者：AmamiyaYuuko (赞：4)**  
   - **星级：4星**  
   - **关键亮点**：通过记忆化搜索实现DP状态转移，避免了重复计算，代码简洁且易于理解。  
   - **核心代码**：
     ```cpp
     LL dp(int x, int k) {
       if (~f[x][k]) return f[x][k];
       LL s = 0;
       for (auto i : g[x]) {
         if (d[i] + 1 == d[x]) s += dp(i, k), s %= mod;
         else if (d[i] == d[x] && k == 1) s += dp(i, k - 1), s %= mod;
       }
       return f[x][k] = s;
     }
     ```

### 最优关键思路与技巧

1. **分层图与BFS**：通过BFS对图进行分层，利用层内边和层间边的性质，可以高效地统计符合条件的路径数量。这种方法的时间复杂度较低，适用于大规模图。
2. **动态规划（DP）**：通过DP状态转移，记录从 $s$ 到各点的路径数量，并根据路径长度与最短路径的差值进行分类统计。这种方法适用于需要统计路径数量的场景。
3. **Dijkstra算法**：利用Dijkstra算法计算最短路径，并在过程中统计次短路径的数量。这种方法适用于需要精确计算最短路径和次短路径的场景。

### 可拓展之处

1. **同类型题**：类似的问题可以扩展到计算路径长度与最短路径长度差值不超过 $k$ 的路径数量，或者计算路径长度等于某个特定值的路径数量。
2. **类似算法套路**：在统计路径数量时，可以结合BFS、DFS、Dijkstra等算法，利用分层图、DP等技巧进行优化。

### 推荐题目

1. **洛谷 P1144**：最短路计数
2. **洛谷 P1608**：路径统计
3. **洛谷 P4017**：最大流

### 个人心得摘录

1. **作者：char_phi**：在调试过程中发现，DFS的转移顺序会导致重复计算，因此需要清空DP值以避免重复转移。这提醒我们在设计算法时要注意转移顺序的影响。
2. **作者：daniEl_lElE**：在比赛中因为忘记取模而WA，提醒我们在处理大数运算时要注意取模操作，避免溢出。

---
处理用时：72.81秒