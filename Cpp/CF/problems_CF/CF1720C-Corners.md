---
title: "Corners"
layout: "post"
diff: 普及/提高-
pid: CF1720C
tag: []
---

# Corners

## 题目描述

You are given a matrix consisting of $ n $ rows and $ m $ columns. Each cell of this matrix contains $ 0 $ or $ 1 $ .

Let's call a square of size $ 2 \times 2 $ without one corner cell an L-shape figure. In one operation you can take one L-shape figure, with at least one cell containing $ 1 $ and replace all numbers in it with zeroes.

Find the maximum number of operations that you can do with the given matrix.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 500 $ ) — the number of test cases. Then follow the descriptions of each test case.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \leq n, m \leq 500 $ ) — the size of the matrix.

Each of the following $ n $ lines contains a binary string of length $ m $ — the description of the matrix.

It is guaranteed that the sum of $ n $ and the sum of $ m $ over all test cases does not exceed $ 1000 $ .

## 输出格式

For each test case output the maximum number of operations you can do with the given matrix.

## 说明/提示

In the first testcase one of the optimal sequences of operations is the following (bold font shows l-shape figure on which operation was performed):

- Matrix before any operation was performed:  101111011110
- Matrix after $ 1 $ operation was performed:  100101011110
- Matrix after $ 2 $ operations were performed:  100100011110
- Matrix after $ 3 $ operations were performed:  100100010110
- Matrix after $ 4 $ operations were performed:  100000010110
- Matrix after $ 5 $ operations were performed:  100000010100
- Matrix after $ 6 $ operations were performed:  100000000100
- Matrix after $ 7 $ operations were performed:  000000000100
- Matrix after $ 8 $ operations were performed:  000000000000

In the third testcase from the sample we can not perform any operation because the matrix doesn't contain any ones.

In the fourth testcase it does not matter which L-shape figure we pick in our first operation. We will always be left with single one. So we will perform $ 2 $ operations.

## 样例 #1

### 输入

```
4
4 3
101
111
011
110
3 4
1110
0111
0111
2 2
00
00
2 2
11
11
```

### 输出

```
8
9
0
2
```

