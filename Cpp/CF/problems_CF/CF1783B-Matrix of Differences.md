---
title: "Matrix of Differences"
layout: "post"
diff: 普及-
pid: CF1783B
tag: []
---

# Matrix of Differences

## 题目描述

For a square matrix of integers of size $ n \times n $ , let's define its beauty as follows: for each pair of side-adjacent elements $ x $ and $ y $ , write out the number $ |x-y| $ , and then find the number of different numbers among them.

For example, for the matrix $ \begin{pmatrix} 1 & 3\\ 4 & 2 \end{pmatrix} $ the numbers we consider are $ |1-3|=2 $ , $ |1-4|=3 $ , $ |3-2|=1 $ and $ |4-2|=2 $ ; there are $ 3 $ different numbers among them ( $ 2 $ , $ 3 $ and $ 1 $ ), which means that its beauty is equal to $ 3 $ .

You are given an integer $ n $ . You have to find a matrix of size $ n \times n $ , where each integer from $ 1 $ to $ n^2 $ occurs exactly once, such that its beauty is the maximum possible among all such matrices.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 49 $ ) – the number of test cases.

The first (and only) line of each test case contains a single integer $ n $ ( $ 2 \le n \le 50 $ ).

## 输出格式

For each test case, print $ n $ rows of $ n $ integers — a matrix of integers of size $ n \times n $ , where each number from $ 1 $ to $ n^2 $ occurs exactly once, such that its beauty is the maximum possible among all such matrices. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
2
2
3
```

### 输出

```
1 3
4 2
1 3 4
9 2 7
5 8 6
```

