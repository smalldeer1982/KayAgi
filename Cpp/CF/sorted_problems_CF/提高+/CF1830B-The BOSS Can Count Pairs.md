---
title: "The BOSS Can Count Pairs"
layout: "post"
diff: 提高+/省选-
pid: CF1830B
tag: []
---

# The BOSS Can Count Pairs

## 题目描述

You are given two arrays $ a $ and $ b $ , both of length $ n $ .

Your task is to count the number of pairs of integers $ (i,j) $ such that $ 1 \leq i < j \leq n $ and $ a_i \cdot a_j = b_i+b_j $ .

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the length of the arrays.

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le n $ ) — the elements of array $ a $ .

The third line of each test case contains $ n $ integers $ b_1,b_2,\ldots,b_n $ ( $ 1 \le b_i \le n $ ) — the elements of array $ b $ .

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the number of good pairs.

## 说明/提示

In the first sample, there are $ 2 $ good pairs:

- $ (1,2) $ ,
- $ (1,3) $ .

In the second sample, there are $ 7 $ good pairs:

- $ (1,2) $ ,
- $ (1,5) $ ,
- $ (2,8) $ ,
- $ (3,4) $ ,
- $ (4,7) $ ,
- $ (5,6) $ ,
- $ (5,7) $ .

## 样例 #1

### 输入

```
3
3
2 3 2
3 3 1
8
4 2 8 2 1 2 7 5
3 5 8 8 1 1 6 5
8
4 4 8 8 8 8 8 8
8 8 8 8 8 8 8 8
```

### 输出

```
2
7
1
```

