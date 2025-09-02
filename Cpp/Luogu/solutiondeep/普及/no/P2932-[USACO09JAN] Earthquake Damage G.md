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



**算法分类**: 深度优先搜索 DFS

**综合分析**:
题目要求确定无法到达农庄的最小牧场数。各题解的核心思路是贪心地将已知无法到达农庄的牧场邻接点标记为损坏，再通过搜索统计可达点。这一策略确保计算的是最坏情况下的不可达点数，从而得到题目所求的最小值。

---

### 高分题解推荐

#### 1. [zhy137036] ⭐⭐⭐⭐
**关键亮点**:  
- 思路清晰，通过标记邻接点为损坏点实现贪心策略。
- 代码简洁，使用DFS遍历，变量命名明确。
- 后记部分解释了关键疑问，增强理解。

**核心代码**:
```cpp
void dfs(int x){
    ans++;
    broken[x] = true;
    for(int y : edge[x])
        if(!broken[y]) dfs(y);
}
// 预处理标记邻接点为损坏点后，DFS统计可达点
```

#### 2. [zhujiangyuan] ⭐⭐⭐⭐
**关键亮点**:  
- 正难则反的思路，直接求最多可达点。
- 代码简洁高效，变量命名规范，逻辑直观。
- 注释明确，适合快速理解算法。

**核心代码**:
```cpp
void dfs(int x) {
    v[x] = 1; ans++;
    for(int i : G[x])
        if(!v[i]) dfs(i);
}
// 标记损坏点邻接后，DFS统计可达点
```

#### 3. [SilverLi] ⭐⭐⭐⭐
**关键亮点**:  
- 使用BFS实现，适合大规模数据处理。
- 代码极简，利用`vis`数组同时标记损坏与访问状态。
- 预处理与搜索分离，结构清晰。

**核心代码**:
```cpp
queue<int> q;
q.push(1); vis[1] = 1;
while(!q.empty()) {
    int x = q.front(); q.pop();
    for(int i : G[x])
        if(!vis[i]) vis[i] = 1, q.push(i), ans++;
}
// BFS遍历未被标记的节点
```

---

**最优技巧总结**:  
- **贪心标记**：将报告点的所有邻接点标记为损坏，确保无法通过这些点到达农庄。
- **逆向思维**：计算可达点后取补集，避免直接统计损坏点的复杂度。
- **高效遍历**：采用DFS/BFS线性时间复杂度遍历，适合大规模图数据。

**拓展建议**:  
- 类似问题可参考图的连通块处理，如[P2863 The Cow Prom S](https://www.luogu.com.cn/problem/P2863)（强连通分量）。
- 推荐题目：[P3916 图的遍历](https://www.luogu.com.cn/problem/P3916)、[P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)、[P2863 [USACO06JAN] The Cow Prom S](https://www.luogu.com.cn/problem/P2863)。

**个人心得摘录**:  
> "标记邻接点为损坏点后，即使误判也不会影响最终结果，因为它们已被隔离。" —— [zhy137036]  
> "BFS更适合处理层序关系，但DFS代码更简洁，两者时间复杂度相同。" —— [SilverLi]

---
处理用时：79.92秒