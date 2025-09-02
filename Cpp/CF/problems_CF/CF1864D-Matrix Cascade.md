---
title: "Matrix Cascade"
layout: "post"
diff: 普及/提高-
pid: CF1864D
tag: []
---

# Matrix Cascade

## 题目描述

There is a matrix of size $ n \times n $ which consists of 0s and 1s. The rows are numbered from $ 1 $ to $ n $ from top to bottom, the columns are numbered from $ 1 $ to $ n $ from left to right. The cell at the intersection of the $ x $ -th row and the $ y $ -th column is denoted as $ (x, y) $ .

AquaMoon wants to turn all elements of the matrix to 0s. In one step she can perform the following operation:

- Select an arbitrary cell, let it be $ (i, j) $ , then invert the element in $ (i, j) $ and also invert all elements in cells $ (x, y) $ for $ x > i $ and $ x - i \ge \left|y - j\right| $ . To invert a value means to change it to the opposite: 0 changes to 1, 1 changes to 0.

Help AquaMoon determine the minimum number of steps she need to perform to turn all elements of the matrix to 0s. We can show that an answer always exists.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 2 \le n \le 3000 $ ).

The $ i $ -th of the following $ n $ lines contains a binary string only of characters 0 and 1, of length $ n $ .

It is guaranteed that the sum of $ n^2 $ over all test cases does not exceed $ 9\,000\,000 $ .

## 输出格式

For each test case, print the minimum number of steps.

## 说明/提示

In the first test case, we can use the following scheme:

1. perform the operation on the cell $ (1, 3) $ .

Clearly, the elements of the initial matrix are not all 0, so at least one operation is required. Thus, $ 1 $ is the answer.

In the second test case, we use the following scheme:

1. perform the operation on the cell $ (3, 3) $ ;
2. perform the operation on the cell $ (1, 1) $ .

It can be shown that there is no way to convert all elements to 0s in $ 0 $ or $ 1 $ steps, so the answer is exactly $ 2 $ .

## 样例 #1

### 输入

```
3
5
00100
01110
11111
11111
11111
3
100
110
110
6
010101
111101
011110
000000
111010
001110
```

### 输出

```
1
2
15
```

