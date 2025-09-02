# 题目信息

# Matching Reduction

## 题目描述

You are given a bipartite graph with $ n_1 $ vertices in the first part, $ n_2 $ vertices in the second part, and $ m $ edges. The maximum matching in this graph is the maximum possible (by size) subset of edges of this graph such that no vertex is incident to more than one chosen edge.

You have to process two types of queries to this graph:

- $ 1 $ — remove the minimum possible number of vertices from this graph so that the size of the maximum matching gets reduced exactly by $ 1 $ , and print the vertices that you have removed. Then, find any maximum matching in this graph and print the sum of indices of edges belonging to this matching;
- $ 2 $ — query of this type will be asked only after a query of type $ 1 $ . As the answer to this query, you have to print the edges forming the maximum matching you have chosen in the previous query.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query. Use functions fflush in C++ and BufferedWriter.flush in Java languages after each writing in your program.

## 说明/提示

In this problem, you may receive the verdict "Idleness Limit Exceeded" since it is in online mode. If it happens, it means that either the output format is wrong, or you don't meet some constraint of the problem. You may treat this verdict as "Wrong Answer".

For your convenience, the output for queries in the example is separated by the line ===. Don't print this line in your program, it is done only to make sure that it's easy to distinguish between answers for different queries in the statement.

## 样例 #1

### 输入

```
3 4 4 4
2 2
1 3
2 1
3 4
1
2
1
2```

### 输出

```
1
-4
3
===
2
1 2
===
1
2
2
===
1
2```

# AI分析结果



## 算法分类
**无算法分类**

---

## 综合分析与结论

### 核心思路与难点
- **核心思路**：基于 König 定理，最大匹配等于最小点覆盖大小。每次删除一个最小点覆盖中的顶点，使得最大匹配减少 1。
- **关键步骤**：
  1. **构建最大流模型**：将二分图转换为网络流模型，左右部分分别连接源点和汇点。
  2. **残量网络标记**：通过最大流后的残量网络，标记可达顶点。左部不可达顶点和右部可达顶点构成最小点覆盖。
  3. **顶点删除策略**：每次从最小点覆盖中删除一个顶点，维护当前最大匹配。
- **解决难点**：
  - 正确判断顶点是否属于最小点覆盖。
  - 高效维护删除后的匹配边和总和。

### 题解对比
- **Alex_Wei 题解**：通过残量网络分离最大独立集和非独立集顶点，直接删除非独立集顶点。
- **Leasier 题解**：显式构造最小点覆盖，维护删除后的匹配边。
- **do_while_true 题解**：利用 König 定理构造最小点覆盖，动态维护顶点集合。

---

## 题解评分（≥4星）

1. **Alex_Wei 题解（★★★★★）**  
   - **亮点**：利用最大独立集性质，代码简洁高效，预处理非独立集顶点。
2. **Leasier 题解（★★★★☆）**  
   - **亮点**：显式构造最小点覆盖，维护匹配边的总和和集合。
3. **do_while_true 题解（★★★★☆）**  
   - **亮点**：动态维护顶点集合，直接处理最小点覆盖。

---

## 最优思路提炼

### 关键思路
1. **König 定理应用**：最大匹配大小等于最小点覆盖大小。
2. **顶点删除策略**：每次删除一个最小点覆盖中的顶点，确保最大匹配减少 1。
3. **残量网络标记**：通过最大流后的残量网络 DFS，标记左部不可达顶点和右部可达顶点为最小点覆盖。

### 代码实现要点
- **最大流构建**：左右部分分别连接源点和汇点，边权为 1。
- **残量网络处理**：DFS 标记可达顶点，分离最小点覆盖。
- **动态维护**：记录匹配边总和和集合，每次删除后更新。

```cpp
// Alex_Wei 题解核心代码片段
void dfs2(int u) {
    vis[u] = true;
    for (int i = head[u]; i; i = edge[i].nxt)
        if (edge[i].dis && !vis[edge[i].to])
            dfs2(edge[i].to);
}
// 标记残量网络中可达顶点
```

---

## 同类型题与算法套路

### 类似算法
- **最大流求二分图匹配**：通过 Dinic 算法高效求解。
- **König 定理应用**：最小点覆盖与最大匹配的关系。
- **残量网络分析**：标记顶点属性（如是否在最小点覆盖中）。

### 推荐题目
1. **P3386**：二分图最大匹配（模板题）。
2. **P2764**：最小路径覆盖（König 定理应用）。
3. **UVA1201**：最小点覆盖（需构造二分图模型）。

---

## 可视化与算法演示

### 二分过程演示（不适用）
由于本题不涉及二分算法，核心为网络流与顶点标记。

### 复古像素化动画设计
1. **Canvas 网格绘制**：
   - 左右部分顶点用不同颜色区分。
   - 匹配边高亮为绿色，删除顶点标记为红色。
2. **音效触发**：
   - 删除顶点时播放“爆炸”音效。
   - 更新匹配边时播放“点击”音效。
3. **自动演示模式**：
   - 按步骤展示最大流构建、残量网络标记、顶点删除过程。

---

## 个人心得摘录
- **Alex_Wei**：强调最大独立集与顶点数的关系，通过预处理简化动态维护。
- **do_while_true**：注意残量网络 DFS 的方向（右部失配点开始），确保标记正确性。

---

**总结**：通过 König 定理将问题转化为最小点覆盖删除，结合最大流和残量网络标记，实现高效动态维护。

---
处理用时：71.84秒