---
title: "Good Subarrays (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1736C2
tag: []
---

# Good Subarrays (Hard Version)

## 题目描述

This is the hard version of this problem. In this version, we have queries. Note that we do not have multiple test cases in this version. You can make hacks only if both versions of the problem are solved.

An array $ b $ of length $ m $ is good if for all $ i $ the $ i $ -th element is greater than or equal to $ i $ . In other words, $ b $ is good if and only if $ b_i \geq i $ for all $ i $ ( $ 1 \leq i \leq m $ ).

You are given an array $ a $ consisting of $ n $ positive integers, and you are asked $ q $ queries.

In each query, you are given two integers $ p $ and $ x $ ( $ 1 \leq p,x \leq n $ ). You have to do $ a_p := x $ (assign $ x $ to $ a_p $ ). In the updated array, find the number of pairs of indices $ (l, r) $ , where $ 1 \le l \le r \le n $ , such that the array $ [a_l, a_{l+1}, \ldots, a_r] $ is good.

Note that all queries are independent, which means after each query, the initial array $ a $ is restored.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ).

The third line contains an integer $ q $ ( $ 1 \leq q \leq 2 \cdot 10^5 $ ) — the number of queries.

Each of the next $ q $ lines contains two integers $ p_j $ and $ x_j $ ( $ 1 \leq p_j, x_j \leq n $ ) – the description of the $ j $ -th query.

## 输出格式

For each query, print the number of suitable pairs of indices after making the change.

## 说明/提示

Here are notes for first example.

In first query, after update $ a=[2,4,1,4] $ . Now $ (1,1) $ , $ (2,2) $ , $ (3,3) $ , $ (4,4) $ , $ (1,2) $ , and $ (3,4) $ are suitable pairs.

In second query, after update $ a=[2,4,3,4] $ . Now all subarrays of $ a $ are good.

In third query, after update $ a=[2,1,1,4] $ . Now $ (1,1) $ , $ (2,2) $ , $ (3,3) $ , $ (4,4) $ , and $ (3,4) $ are suitable.

## 样例 #1

### 输入

```
4
2 4 1 4
3
2 4
3 3
2 1
```

### 输出

```
6
10
5
```

## 样例 #2

### 输入

```
5
1 1 3 2 1
3
1 3
2 5
4 5
```

### 输出

```
7
9
8
```

