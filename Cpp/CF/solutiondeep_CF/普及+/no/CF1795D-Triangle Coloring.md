# 题目信息

# Triangle Coloring

## 题目描述

You are given an undirected graph consisting of $ n $ vertices and $ n $ edges, where $ n $ is divisible by $ 6 $ . Each edge has a weight, which is a positive (greater than zero) integer.

The graph has the following structure: it is split into $ \frac{n}{3} $ triples of vertices, the first triple consisting of vertices $ 1, 2, 3 $ , the second triple consisting of vertices $ 4, 5, 6 $ , and so on. Every pair of vertices from the same triple is connected by an edge. There are no edges between vertices from different triples.

You have to paint the vertices of this graph into two colors, red and blue. Each vertex should have exactly one color, there should be exactly $ \frac{n}{2} $ red vertices and $ \frac{n}{2} $ blue vertices. The coloring is called valid if it meets these constraints.

The weight of the coloring is the sum of weights of edges connecting two vertices with different colors.

Let $ W $ be the maximum possible weight of a valid coloring. Calculate the number of valid colorings with weight $ W $ , and print it modulo $ 998244353 $ .

## 说明/提示

The following picture describes the graph from the first example test.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1795D/4ae4faa6e7106558b0f38fa8feb77e73227352e2.png)The maximum possible weight of a valid coloring of this graph is $ 31 $ .

## 样例 #1

### 输入

```
12
1 3 3 7 8 5 2 2 2 2 4 2```

### 输出

```
36```

## 样例 #2

### 输入

```
6
4 2 6 6 6 4```

### 输出

```
2```

# AI分析结果

### 题目内容重写

#### 三角形染色

**题目描述**

给定一个由 $n$ 个顶点和 $n$ 条边组成的无向图，其中 $n$ 能被 $6$ 整除。每条边都有一个权重，权重为正整数。

该图的结构如下：图被分成 $\frac{n}{3}$ 个三元组，第一个三元组由顶点 $1, 2, 3$ 组成，第二个三元组由顶点 $4, 5, 6$ 组成，依此类推。每个三元组中的每对顶点之间都有一条边连接。不同三元组之间的顶点没有边连接。

你需要将图中的顶点染成两种颜色，红色和蓝色。每个顶点必须被染成一种颜色，且恰好有 $\frac{n}{2}$ 个红色顶点和 $\frac{n}{2}$ 个蓝色顶点。如果染色满足这些约束条件，则称其为有效染色。

染色的权重是连接两个不同颜色顶点的边的权重之和。

设 $W$ 为有效染色的最大可能权重。计算权重为 $W$ 的有效染色的数量，并输出其对 $998244353$ 取模的结果。

**说明/提示**

下图描述了第一个样例测试的图。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1795D/4ae4faa6e7106558b0f38fa8feb77e73227352e2.png)

该图的有效染色的最大可能权重为 $31$。

**样例 #1**

**输入**

```
12
1 3 3 7 8 5 2 2 2 2 4 2
```

**输出**

```
36
```

**样例 #2**

**输入**

```
6
4 2 6 6 6 4
```

**输出**

```
2
```

### 算法分类
组合数学

### 题解分析与结论

题目要求在每个三元组中选择两条边，使得这些边的权重之和最大，并且计算满足条件的染色方案数。各题解的思路基本一致，主要分为以下几步：

1. **确定最优染色方案**：每个三元组必须选择两条边，且这两条边的权重之和最大。这意味着每个三元组的染色方案只能是“红红蓝”或“蓝蓝红”。
2. **计算染色方案数**：首先计算所有三元组中选择“红红蓝”或“蓝蓝红”的组合数，即 $\binom{n/3}{n/6}$。
3. **处理边权相同的特殊情况**：如果三元组中的三条边权相同，则有 $3$ 种选择方式；如果两条较小边权相同，则有 $2$ 种选择方式；否则只有 $1$ 种选择方式。
4. **乘法原理计算总方案数**：将所有三元组的选择方式数相乘，再乘以组合数，得到最终结果。

### 精选题解

#### 题解1：Hanx16Kira (5星)
**关键亮点**：
- 详细解释了每个三元组的选择方式，特别是边权相同的情况。
- 代码实现清晰，预处理阶乘和逆元，优化了组合数的计算。

**核心代码**：
```cpp
int ans = Binom(n / 3, n / 6); // 基础染色方案数
for (int i = 1, iend = n / 3; i <= iend; ++i) {
    int t[] = {w[i * 3 - 2], w[i * 3 - 1], w[i * 3]};
    sort(t, t + 3);
    if (t[1] == t[2] && t[0] == t[1]) ans = 3ll * ans % mod; // 三个边权相等
    else if (t[0] == t[1]) ans = 2ll * ans % mod; // 较小的两个边权相等
}
```

#### 题解2：ダ月 (4星)
**关键亮点**：
- 简洁明了地分析了每个三元组的染色方案，特别是边权相同的情况。
- 代码实现高效，直接计算组合数和边权相同的贡献。

**核心代码**：
```cpp
for (int i = 1; i <= n; i += 3) {
    sort(a + i, a + i + 3, cmp);
    if (a[i] == a[i + 1] && a[i + 1] == a[i + 2]) sum = sum * 3 % mod;
    else if (a[i + 1] == a[i + 2]) sum = sum * 2 % mod;
}
printf("%lld\n", sum * C(n / 3, n / 6) % mod);
```

#### 题解3：ztlh (4星)
**关键亮点**：
- 清晰地分析了每个三元组的染色方案，特别是边权相同的情况。
- 代码实现简洁，直接计算组合数和边权相同的贡献。

**核心代码**：
```cpp
for (int i = 1; i <= n; i += 3) {
    if (w[i] < w[i + 1]) swap(w[i], w[i + 1]);
    if (w[i] < w[i + 2]) swap(w[i], w[i + 2]);
    if (w[i + 1] < w[i + 2]) swap(w[i + 1], w[i + 2]);
    if (w[i] == w[i + 1] && w[i + 1] == w[i + 2]) ans = ans * 3 % Mod;
    else if (w[i + 1] == w[i + 2]) ans = ans * 2 % Mod;
}
printf("%lld\n", ans * C(n / 3, n / 6) % Mod);
```

### 最优关键思路
1. **组合数学**：使用组合数计算染色方案的总数，特别是 $\binom{n/3}{n/6}$。
2. **边权处理**：根据边权相同的情况，分别计算每个三元组的选择方式数，使用乘法原理得到最终结果。

### 可拓展之处
- 类似的问题可以扩展到其他图结构，如四元组、五元组等，需要根据图的结构调整染色方案和组合数的计算。
- 可以进一步优化组合数的计算，特别是在大模数下的快速计算。

### 推荐题目
1. [P1357 食物链](https://www.luogu.com.cn/problem/P1357)
2. [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)
3. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)

---
处理用时：56.07秒