---
title: "Find the Spruce"
layout: "post"
diff: 普及-
pid: CF1461B
tag: []
---

# Find the Spruce

## 题目描述

Holidays are coming up really soon. Rick realized that it's time to think about buying a traditional spruce tree. But Rick doesn't want real trees to get hurt so he decided to find some in an $ n \times m $ matrix consisting of "\*" and ".".

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461B/0f830498ab169a471030eeb85fc12c395e76f5ca.png)To find every spruce first let's define what a spruce in the matrix is. A set of matrix cells is called a spruce of height $ k $ with origin at point $ (x, y) $ if:

- All cells in the set contain an "\*".
- For each $ 1 \le i \le k $ all cells with the row number $ x+i-1 $ and columns in range $ [y - i + 1, y + i - 1] $ must be a part of the set. All other cells cannot belong to the set.

Examples of correct and incorrect spruce trees:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461B/2ce2df8e09c4fc74a3e149e5906821e41a5e552f.png)Now Rick wants to know how many spruces his $ n \times m $ matrix contains. Help Rick solve this problem.

## 输入格式

Each test contains one or more test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10 $ ).

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 500 $ ) — matrix size.

Next $ n $ lines of each test case contain $ m $ characters $ c_{i, j} $ — matrix contents. It is guaranteed that $ c_{i, j} $ is either a "." or an "\*".

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 500^2 $ ( $ \sum n \cdot m \le 500^2 $ ).

## 输出格式

For each test case, print single integer — the total number of spruces in the matrix.

## 说明/提示

In the first test case the first spruce of height $ 2 $ has its origin at point $ (1, 2) $ , the second spruce of height $ 1 $ has its origin at point $ (1, 2) $ , the third spruce of height $ 1 $ has its origin at point $ (2, 1) $ , the fourth spruce of height $ 1 $ has its origin at point $ (2, 2) $ , the fifth spruce of height $ 1 $ has its origin at point $ (2, 3) $ .

In the second test case the first spruce of height $ 1 $ has its origin at point $ (1, 2) $ , the second spruce of height $ 1 $ has its origin at point $ (2, 1) $ , the third spruce of height $ 1 $ has its origin at point $ (2, 2) $ .

## 样例 #1

### 输入

```
4
2 3
.*.
***
2 3
.*.
**.
4 5
.***.
*****
*****
*.*.*
5 7
..*.*..
.*****.
*******
.*****.
..*.*..
```

### 输出

```
5
3
23
34
```

