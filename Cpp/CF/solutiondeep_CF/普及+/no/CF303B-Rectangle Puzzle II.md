# 题目信息

# Rectangle Puzzle II

## 题目描述

You are given a rectangle grid. That grid's size is $ n×m $ . Let's denote the coordinate system on the grid. So, each point on the grid will have coordinates — a pair of integers $ (x,y) $ $ (0<=x<=n,0<=y<=m) $ .

Your task is to find a maximum sub-rectangle on the grid $ (x_{1},y_{1},x_{2},y_{2}) $ so that it contains the given point $ (x,y) $ , and its length-width ratio is exactly $ (a,b) $ . In other words the following conditions must hold: $ 0<=x_{1}<=x<=x_{2}<=n $ , $ 0<=y_{1}<=y<=y_{2}<=m $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303B/d25d5fd31cdc2b2671d5f1dca98aadab16b15a21.png).

The sides of this sub-rectangle should be parallel to the axes. And values $ x_{1},y_{1},x_{2},y_{2} $ should be integers.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303B/4f1aa1906686be0387a09dbeae2bf3128e4fc307.png)If there are multiple solutions, find the rectangle which is closest to $ (x,y) $ . Here "closest" means the Euclid distance between $ (x,y) $ and the center of the rectangle is as small as possible. If there are still multiple solutions, find the lexicographically minimum one. Here "lexicographically minimum" means that we should consider the sub-rectangle as sequence of integers $ (x_{1},y_{1},x_{2},y_{2}) $ , so we can choose the lexicographically minimum one.

## 样例 #1

### 输入

```
9 9 5 5 2 1
```

### 输出

```
1 3 9 7
```

## 样例 #2

### 输入

```
100 100 52 50 46 56
```

### 输出

```
17 8 86 92
```

# AI分析结果

### 题目内容
# 矩形谜题 II

## 题目描述
给定一个矩形网格，其大小为 $n×m$ 。我们在网格上定义一个坐标系，因此网格上的每个点都有坐标，即一对整数 $(x,y)$ ，其中 $(0<=x<=n,0<=y<=m)$ 。

你的任务是在网格上找到一个最大的子矩形 $(x_{1},y_{1},x_{2},y_{2})$ ，该子矩形要包含给定的点 $(x,y)$ ，并且其长宽比恰好为 $(a,b)$ 。换句话说，必须满足以下条件：$0<=x_{1}<=x<=x_{2}<=n$ ，$0<=y_{1}<=y<=y_{2}<=m$ ，$\frac{x_{2}-x_{1}}{y_{2}-y_{1}}=\frac{a}{b}$ 。

这个子矩形的边应与坐标轴平行，并且 $x_{1},y_{1},x_{2},y_{2}$ 的值应为整数。

如果有多个解，找到离 $(x,y)$ 最近的矩形。这里的“最近”是指 $(x,y)$ 与矩形中心之间的欧几里得距离尽可能小。如果仍然有多个解，则找到字典序最小的那个。这里的“字典序最小”意味着我们将子矩形视为整数序列 $(x_{1},y_{1},x_{2},y_{2})$ ，所以我们可以选择字典序最小的那个。

## 样例 #1
### 输入
```
9 9 5 5 2 1
```
### 输出
```
1 3 9 7
```

## 样例 #2
### 输入
```
100 100 52 50 46 56
```
### 输出
```
17 8 86 92
```

### 算法分类
搜索

### 综合分析与结论
由于暂无题解，以下给出通用建议与扩展思路。本题核心是在给定矩形网格中，搜索满足特定长宽比且包含指定点的最大子矩形，并在多解时按特定规则选择。解决本题的关键在于如何高效地遍历所有可能的子矩形，同时满足长宽比条件以及距离和字典序要求。可先根据长宽比关系，确定子矩形可能的边长组合，再结合包含指定点的条件进行筛选。对于距离和字典序的判断，可在遍历过程中实时计算和比较。

### 扩展思路
同类型题可考虑在二维平面上进行特定形状搜索并满足一定约束条件的题目。类似算法套路如在搜索过程中利用剪枝策略减少不必要的计算，或者利用数学关系提前确定搜索范围。

### 推荐洛谷题目
1. P1162 填涂颜色，涉及二维数组的搜索遍历，与本题在二维空间操作有相似性。
2. P1339 热浪，可通过搜索算法解决最短路问题，在搜索策略上有借鉴之处。
3. P1443 马的遍历，同样是二维平面上的搜索问题，可加深对搜索算法的理解。 

---
处理用时：25.98秒