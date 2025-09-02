# 题目信息

# Jamie and Interesting Graph

## 题目描述

Jamie has recently found undirected weighted graphs with the following properties very interesting:

- The graph is connected and contains exactly $ n $ vertices and $ m $ edges.
- All edge weights are integers and are in range $ [1,10^{9}] $ inclusive.
- The length of shortest path from $ 1 $ to $ n $ is a prime number.
- The sum of edges' weights in the minimum spanning tree (MST) of the graph is a prime number.
- The graph contains no loops or multi-edges.

If you are not familiar with some terms from the statement you can find definitions of them in notes section.

Help Jamie construct any graph with given number of vertices and edges that is interesting!



## 说明/提示

The graph of sample 1: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/03021596e10dc8211f3fe958e7629dc3a97d37e7.png) Shortest path sequence: $ {1,2,3,4} $ . MST edges are marked with an asterisk (\*).

Definition of terms used in the problem statement:

A shortest path in an undirected graph is a sequence of vertices $ (v_{1},v_{2},...\ ,v_{k}) $ such that $ v_{i} $ is adjacent to $ v_{i+1} $ $ 1<=i<k $ and the sum of weight ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/df0334815830e4f0c8788e37a58a6247ba52744b.png) is minimized where $ w(i,j) $ is the edge weight between $ i $ and $ j $ . ([https://en.wikipedia.org/wiki/Shortest\_path\_problem](https://en.wikipedia.org/wiki/Shortest_path_problem))

A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself. ([https://en.wikipedia.org/wiki/Prime\_number](https://en.wikipedia.org/wiki/Prime_number))

A minimum spanning tree (MST) is a subset of the edges of a connected, edge-weighted undirected graph that connects all the vertices together, without any cycles and with the minimum possible total edge weight. ([https://en.wikipedia.org/wiki/Minimum\_spanning\_tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree))

[https://en.wikipedia.org/wiki/Multiple\_edges](https://en.wikipedia.org/wiki/Multiple_edges)

## 样例 #1

### 输入

```
4 4
```

### 输出

```
7 7
1 2 3
2 3 2
3 4 2
2 4 4
```

## 样例 #2

### 输入

```
5 4
```

### 输出

```
7 13
1 2 2
1 3 4
1 4 3
4 5 4
```

# AI分析结果



## 算法分类
**构造型算法**

---

## 题解思路与核心难点

### 核心思路
所有题解的核心思路为：
1. **构造一条链式结构**：将 1 到 n 的顶点连接成一条链，使得这条链既是唯一的最短路径，也是唯一的最小生成树（MST）。
2. **边权设计**：
   - 链上的边权总和设置为一个较大的质数（如 1e5+3）。
   - 链的前 n-2 条边权设为 1，最后一条边权调整至总和为质数。
   - 其余边的权值设为极大值（如 1e9），确保不影响最短路径和 MST。
3. **灵活补边**：剩余边随意连接未直接相邻的顶点，权值取极大值。

### 解决难点
1. **统一最短路径与 MST 的边集**：通过链式结构，确保两者的路径重合，避免双重质数条件的冲突。
2. **质数生成与调整**：固定选择大质数或动态生成，调整首条边权使得总和为质数。
3. **高效构造**：代码需简洁处理链的生成与多余边的填充。

---

## 题解评分 (≥4星)

1. **Fuko_Ibuki（5星）**  
   - **亮点**：代码极简，直接固定大质数 1e5+3，首边动态调整权值，剩余边高效生成。
   - **代码**：仅需 15 行，逻辑清晰。

2. **0xFF（4.5星）**  
   - **亮点**：思路与 Fuko_Ibuki 完全一致，但代码稍显冗长，变量命名更规范。

3. **feiji_code（4星）**  
   - **亮点**：思路清晰，代码简洁，但质数选择注释稍显随意。

---

## 最优思路提炼

### 关键步骤
1. **链式结构**：连接 1→2→…→n，前 n-2 条边权为 1，最后一条边权为 `p - (n-2)`（p 为大质数）。
2. **质数选择**：固定大质数（如 1e5+3）或动态生成，确保总和为质数。
3. **补边策略**：任意填充非链边，权值设为 1e9，避免影响最短路径和 MST。

### 代码片段
```cpp
// 核心构造逻辑（Fuko_Ibuki 题解）
int p = 1e5 + 3; // 固定大质数
printf("%d %d\n1 2 %d\n", p, p, p - n + 2);
for (int i = 2; i < n; i++) 
    printf("%d %d 1\n", i, i+1);
m -= n - 1;
for (int k = 0, j = n; m--;) {
    if (++j > n) j = ++k + 2;
    printf("%d %d 1000000000\n", k, j);
}
```

---

## 相似题目推荐
1. **P1265（公路修建）**：构造最小生成树的条件验证。
2. **P1967（货车运输）**：最大生成树与路径查询的结合。
3. **P1119（灾后重建）**：动态最短路径的构造与维护。

---

## 可视化设计

### 动画方案
1. **链式构造**：  
   - **步骤**：逐个高亮链边，显示边权调整过程，实时计算当前总权和是否为质数。
   - **颜色**：链边为绿色，其他边为红色。
2. **补边填充**：  
   - **效果**：随机连接非链顶点，边权以灰色虚线表示，权值显示为 1e9。
3. **质数验证**：  
   - **提示**：总权和变为质数时，播放上扬音效，背景闪烁绿色。

### 复古像素风格
- **节点**：8-bit 方块，编号居中显示。
- **边权**：链边显示为像素箭头，其他边为虚线。
- **音效**：  
  - 添加链边：8-bit “哔”声。
  - 完成构造：经典 FC 过关音效。

---

## 总结
通过链式结构的巧妙设计，将最短路径与 MST 的质数条件统一，剩余边填充极大权值。代码实现简洁高效，核心在于质数选择与边权调整。此思路可推广至需同时满足多重图论条件的构造问题。

---
处理用时：75.47秒