# 题目信息

# [USACO09JAN] Earthquake Damage G

## 题目描述

Wisconsin has had an earthquake that has struck Farmer John's farm! The earthquake has damaged some of the pastures so that they are unpassable. Remarkably, none of the cowpaths was damaged.

As usual, the farm is modeled as a set of $P(1 \le P \le 30,000)$ pastures conveniently numbered $1\ldots P$ which are connected by a set of $C (1 \le C \le 100,000)$ non-directional cowpaths conveniently numbered $1\ldots C$. Cowpath $i$ connects pastures $a_i$ and $b_i (1 \le a_i \le P; 1 \le b_i \le P)$. Cowpaths might connect $a_i$ to itself or perhaps might connect two pastures more than once.  The barn is located in pasture $1$.

A total of $N (1 \le N \le P)$ cows (in different pastures) sequentially contact Farmer John via moobile phone with an integer message $report_j (2 \le report_j \le P)$ that indicates that pasture $report_j$ is undamaged but that the calling cow is unable to return to the barn from pasture $report_j$ because she could not find a path that does not go through damaged pastures.

After all the cows report in, determine the minimum number of pastures (including ones that are uncrossable) from which it is not possible to return to the barn.

Note: Feedback on some of the test data will be provided on the first $50$ submissions.

## 说明/提示

Pasture $2$ is damaged, resulting in cows in pastures $2, 3, 4$ not being able to return to the barn.

## 样例 #1

### 输入

```
4 3 1 
1 2 
2 3 
3 4 
3 
```

### 输出

```
3 
```

# AI分析结果



### 综合分析与结论
题目要求确定无法到达1号点的最少牧场数目。各题解的核心思路是：将报告点的邻居标记为损坏，确保这些报告点无法到达1号点，然后通过DFS/BFS统计可到达的点数，总点数减去可到达数即为答案。关键点在于贪心策略的正确性——标记报告点的邻居为损坏，从而阻断其与1号点的连通。

### 高星题解推荐
#### 1. 作者：zhy137036（4星）
- **关键亮点**：思路清晰，代码简洁，正确标记报告点的邻居而非报告点自身，确保符合题意。解释详细，包含后记讨论潜在问题。
- **核心代码**：
  ```cpp
  void dfs(int x) {
      ans++;
      broken[x] = true;
      for (auto y : edge[x]) {
          if (!broken[y]) dfs(y);
      }
  }
  ```
  标记邻居为损坏后，从1号点DFS统计可到达的点。

#### 2. 作者：zhujiangyuan（4星）
- **关键亮点**：代码简洁，正确使用贪心策略，标记邻居为损坏，逻辑清晰。
- **核心代码**：
  ```cpp
  void dfs(int x) {
      vis[x] = 1; ans++;
      for (auto i : G[x]) if (!vis[i]) dfs(i);
  }
  ```
  通过DFS遍历未被标记的节点，直接统计可到达的点数。

#### 3. 作者：SilverLi（4星）
- **关键亮点**：代码简洁，正确标记邻居为损坏，并采用BFS实现，适合处理大规模图。
- **核心代码**：
  ```cpp
  void DeepFirstSerch(int ch) {
      ++ans, vis[ch] = 1;
      for (int i : g[ch]) if (!vis[i]) DFS(i);
  }
  ```
  使用BFS遍历未被标记的节点，逻辑与DFS等效但更高效。

### 最优思路总结
- **贪心标记**：将每个报告点的所有邻居标记为损坏，确保报告点无法通过任何路径到达1号点。
- **图遍历**：从1号点进行DFS/BFS，统计未被标记的可到达点，总点数减去该数即为答案。
- **正确性保障**：题目保证报告点无法到达1号点，因此其路径必经过损坏点，标记邻居后阻断所有可能路径。

### 拓展与同类题目
- **同类题目**：
  1. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)：图遍历与路径计数。
  2. [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：图的覆盖与贪心策略。
  3. [P3388 割点](https://www.luogu.com.cn/problem/P3388)：连通性与关键节点分析。

### 个人心得摘录
- **调试关键**：部分题解错误标记报告点自身为损坏，导致结果错误。正确做法应仅标记邻居，确保报告点未被损坏但无法到达。
- **贪心验证**：通过反向分析，若存在未被处理的路径到达报告点，则与题意矛盾，证明贪心策略的正确性。

---
处理用时：291.65秒