---
title: "RECTMAT - Rectangles in a Matrix"
layout: "post"
diff: 难度0
pid: SP8285
tag: []
---

# RECTMAT - Rectangles in a Matrix

## 题目描述

在一个 $n$ 行 $m$ 列的矩阵中，位置 $(i, j)$ 表示第 $i$ 行第 $j$ 列的单元格（$0 \le i < n$，$0 \le j < m$）。矩阵中的一个矩形可以用四个坐标 $(r_0, r_1, c_0, c_1)$ 来定义，它代表了所有行标在 $r_0 \le i < r_1$ 且列标在 $c_0 \le j < c_1$ 范围内的单元格集合（$0 \le r_0 < r_1 \le n$，$0 \le c_0 < c_1 \le m$）。如果两个矩形的单元格集合没有重叠，那么我们称这两个矩形是互相独立的。  

现在，给定三个正整数 $n$、$m$ 和 $k$，请计算从 $n \times m$ 的矩阵中选择 $k$ 个互相独立的矩形的方法数。注意，这些矩形的顺序无关紧要。请参照样例理解题目。

## 输入格式

输入只有一行，包含三个整数 $n, m, k$，满足 $1 \le n, m \le 1000$ 和 $1 \le k \le 6$。

## 输出格式

对于每个测试用例，输出符合条件的方法数对 $10^9 + 7$ 取模后的结果。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n2 2 4\n10 10 1\n
```

### 输出

```
\n1\n3025\nExplanation\nFirst case: You have to find the number of ways of choosing 4  independent rectangles from a 2x2 matrix.\nThe only way to do this is to  choose each cell as a separate rectangle.\n\n
```

