---
title: "Strictly Positive Matrix"
layout: "post"
diff: 提高+/省选-
pid: CF402E
tag: ['搜索', '强连通分量', '栈']
---

# Strictly Positive Matrix

## 题目描述

You have matrix $ a $ of size $ n×n $ . Let's number the rows of the matrix from $ 1 $ to $ n $ from top to bottom, let's number the columns from $ 1 $ to $ n $ from left to right. Let's use $ a_{ij} $ to represent the element on the intersection of the $ i $ -th row and the $ j $ -th column.

Matrix $ a $ meets the following two conditions:

- for any numbers $ i,j $ ( $ 1<=i,j<=n $ ) the following inequality holds: $ a_{ij}>=0 $ ;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF402E/5a3402d889c26bb1dab24aca748b24c9c6e8398d.png).

Matrix $ b $ is strictly positive, if for any numbers $ i,j $ ( $ 1<=i,j<=n $ ) the inequality $ b_{ij}&gt;0 $ holds. You task is to determine if there is such integer $ k>=1 $ , that matrix $ a^{k} $ is strictly positive.

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=2000 $ ) — the number of rows and columns in matrix $ a $ .

The next $ n $ lines contain the description of the rows of matrix $ a $ . The $ i $ -th line contains $ n $ non-negative integers $ a_{i1},a_{i2},...,a_{in} $ ( $ 0<=a_{ij}<=50 $ ). It is guaranteed that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF402E/5a3402d889c26bb1dab24aca748b24c9c6e8398d.png).

## 输出格式

If there is a positive integer $ k>=1 $ , such that matrix $ a^{k} $ is strictly positive, print "YES" (without the quotes). Otherwise, print "NO" (without the quotes).

## 样例 #1

### 输入

```
2
1 0
0 1

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
5
4 5 6 1 2
1 2 3 4 5
6 4 1 2 4
1 1 1 1 1
4 4 4 4 4

```

### 输出

```
YES

```

