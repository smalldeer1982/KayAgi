---
title: "Two Arrays"
layout: "post"
diff: 省选/NOI-
pid: CF1641D
tag: []
---

# Two Arrays

## 题目描述

Sam changed his school and on the first biology lesson he got a very interesting task about genes.

You are given $ n $ arrays, the $ i $ -th of them contains $ m $ different integers — $ a_{i,1}, a_{i,2},\ldots,a_{i,m} $ . Also you are given an array of integers $ w $ of length $ n $ .

Find the minimum value of $ w_i + w_j $ among all pairs of integers $ (i, j) $ ( $ 1 \le i, j \le n $ ), such that the numbers $ a_{i,1}, a_{i,2},\ldots,a_{i,m}, a_{j,1}, a_{j,2},\ldots,a_{j,m} $ are distinct.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 2 \leq n \leq 10^5 $ , $ 1 \le m \le 5 $ ).

The $ i $ -th of the next $ n $ lines starts with $ m $ distinct integers $ a_{i,1}, a_{i,2}, \ldots, a_{i,m} $ and then $ w_i $ follows ( $ 1\leq a_{i,j} \leq 10^9 $ , $ 1 \leq w_{i} \leq 10^9 $ ).

## 输出格式

Print a single number — the answer to the problem.

If there are no suitable pairs $ (i, j) $ , print $ -1 $ .

## 说明/提示

In the first test the minimum value is $ 5 = w_3 + w_4 $ , because numbers $ \{2, 3, 4, 5\} $ are distinct.

In the second test case, there are no suitable pair $ (i, j) $ .

## 样例 #1

### 输入

```
4 2
1 2 5
4 3 1
2 3 2
4 5 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4 3
1 2 3 5
2 3 4 2
3 4 5 3
1 3 10 10
```

### 输出

```
-1
```

