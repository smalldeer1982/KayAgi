# 题目信息

# [USACO09JAN] Best Spot S

## 题目描述

Bessie, always wishing to optimize her life, has realized that she really enjoys visiting F (1 <= F <= P) favorite pastures F\_i of the P (1 <= P <= 500; 1 <= F\_i <= P) total pastures (conveniently

numbered 1..P) that compose Farmer John's holdings.

Bessie knows that she can navigate the C (1 <= C <= 8,000) bidirectional cowpaths (conveniently numbered 1..C) that connect various pastures to travel to any pasture on the entire farm. Associated with each path P\_i is a time T\_i (1 <= T\_i <= 892) to traverse that path (in either direction) and two path endpoints a\_i and b\_i (1 <= a\_i <= P; 1 <= b\_i <= P).

Bessie wants to find the number of the best pasture to sleep in so that when she awakes, the average time to travel to any of her F favorite pastures is minimized.

By way of example, consider a farm laid out as the map below shows, where \*'d pasture numbers are favorites. The bracketed numbers are times to traverse the cowpaths.

```cpp

            1*--[4]--2--[2]--3
                     |       |
                    [3]     [4]
                     |       |
                     4--[3]--5--[1]---6---[6]---7--[7]--8*
                     |       |        |         |
                    [3]     [2]      [1]       [3]
                     |       |        |         |
                    13*      9--[3]--10*--[1]--11*--[3]--12*
```
The following table shows distances for potential 'best place' of pastures 4, 5, 6, 7, 9, 10, 11, and 12:

```cpp
      * * * * * * Favorites * * * * * *
 Potential      Pasture Pasture Pasture Pasture Pasture Pasture     Average
Best Pasture       1       8      10      11      12      13        Distance
------------      --      --      --      --      --      --      -----------
    4              7      16       5       6       9       3      46/6 = 7.67
    5             10      13       2       3       6       6      40/6 = 6.67
    6             11      12       1       2       5       7      38/6 = 6.33
    7             16       7       4       3       6      12      48/6 = 8.00
    9             12      14       3       4       7       8      48/6 = 8.00
   10             12      11       0       1       4       8      36/6 = 6.00 ** BEST
   11             13      10       1       0       3       9      36/6 = 6.00
   12             16      13       4       3       0      12      48/6 = 8.00

```
Thus, presuming these choices were the best ones (a program would have to check all of them somehow), the best place to sleep is pasture 10.

约翰拥有 $P(1 \leq P \leq 500)$ 个牧场，贝茜特别喜欢其中的 $F$ 个。所有的牧场由 $C(1 < C \leq 8000)$条双向路连接，第 $i$ 条路连接着 $a_i,b_i$，需要 $T_i(1 \leq T_i < 892)$ 个单位时间来通过。

作为一只总想优化自己生活方式的奶牛，贝茜喜欢自己某一天醒来，到达所有那 $F$ 个她喜欢的牧场的平均需时最小。那她前一天应该睡在哪个牧场呢？请帮助贝茜找到这个最佳牧场。

由样例解释可见，在样例环境下，牧场 $10$ 到所有贝茜喜欢的牧场的平均距离最小，为最佳牧场。


## 说明/提示

As the problem statement


As the problem statement.


## 样例 #1

### 输入

```
13 6 15 
11 
13 
10 
12 
8 
1 
2 4 3 
7 11 3 
10 11 1 
4 13 3 
9 10 3 
2 3 2 
3 5 4 
5 9 2 
6 7 6 
5 6 1 
1 2 4 
4 5 3 
11 12 3 
6 10 1 
7 8 7 
```

### 输出

```
10 
```

# AI分析结果

### 综合分析与结论

本题的核心是求解每个牧场到所有贝茜喜欢的牧场的最短路径的平均值，并找到使该平均值最小的牧场。大多数题解采用了Floyd算法，少数使用了Dijkstra或SPFA算法。Floyd算法由于其简单性和适用于多源最短路的特性，成为了主流选择。虽然Dijkstra和SPFA在某些情况下可能更快，但Floyd的代码实现更为简洁，且在小规模数据下（P≤500）性能足够。

### 所选高星题解

#### 题解1：Cxs3 (4星)
**关键亮点**：
- 使用Floyd算法，代码简洁明了。
- 详细解释了Floyd算法的动态规划思想。
- 代码中初始化部分清晰，避免了常见的错误。

**个人心得**：
- 强调了Floyd算法的时间复杂度为O(n^3)，虽然较慢但足够应对本题。

**核心代码**：
```cpp
for(k=1;k<=n;k++)
  for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
      f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
```

#### 题解2：zhaoyp (4星)
**关键亮点**：
- 详细解释了Floyd算法的动态规划思想和状态转移方程。
- 代码结构清晰，注释详细，适合初学者理解。

**核心代码**：
```cpp
for(int k = 1;k <= p;++k)
    for(int i = 1;i <= p;++i)
        for(int j = 1;j <= p;++j)
            floyd[i][j] = min(floyd[i][j],floyd[i][k]+floyd[k][j]);
```

#### 题解3：Caicz (4星)
**关键亮点**：
- 代码简洁，直接应用Floyd算法。
- 强调了无向图的处理方式，代码中双向存储距离。

**核心代码**：
```cpp
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
```

### 最优关键思路与技巧

1. **Floyd算法**：适用于多源最短路问题，代码实现简单，时间复杂度为O(n^3)，适合小规模数据。
2. **初始化**：在Floyd算法中，初始化距离矩阵时，对角线元素应设为0，其他元素设为无穷大。
3. **无向图处理**：在存储路径时，双向存储距离，确保图的连通性。

### 可拓展之处

1. **Dijkstra算法**：适用于单源最短路问题，时间复杂度为O(n^2)或O(n log n)，适合大规模数据。
2. **SPFA算法**：适用于稀疏图，时间复杂度为O(kE)，k为常数，适合边数较少的情况。

### 推荐相似题目

1. **P1144 最短路计数**：考察Dijkstra算法的应用，适合理解最短路径的计数问题。
2. **P3371 【模板】单源最短路径（弱化版）**：适合练习Dijkstra算法的实现。
3. **P4779 【模板】单源最短路径（标准版）**：适合练习Dijkstra算法的优化版本。

### 个人心得总结

- **调试经历**：在初始化距离矩阵时，容易忘记将对角线元素设为0，导致算法无法正确运行。
- **踩坑教训**：在无向图中，双向存储距离是必要的，否则会导致图不连通，影响最短路径的计算。
- **顿悟感想**：Floyd算法虽然时间复杂度较高，但在小规模数据下，其简洁性和易实现性使其成为首选。

---
处理用时：29.35秒