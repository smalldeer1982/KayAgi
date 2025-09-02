---
title: "Field Should Not Be Empty"
layout: "post"
diff: 省选/NOI-
pid: CF1905F
tag: ['枚举']
---

# Field Should Not Be Empty

## 题目描述

You are given a permutation $ ^{\dagger} $ $ p $ of length $ n $ .

We call index $ x $ good if for all $ y < x $ it holds that $ p_y < p_x $ and for all $ y > x $ it holds that $ p_y > p_x $ . We call $ f(p) $ the number of good indices in $ p $ .

You can perform the following operation: pick $ 2 $ distinct indices $ i $ and $ j $ and swap elements $ p_i $ and $ p_j $ .

Find the maximum value of $ f(p) $ after applying the aforementioned operation exactly once.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test consists of multiple test cases. The first line of contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the length of the permutation $ p $ .

The second line of each test case contain $ n $ distinct integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ) — the elements of the permutation $ p $ .

It is guaranteed that sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum value of $ f(p) $ after performing the operation exactly once.

## 说明/提示

In the first test case, $ p = [1,2,3,4,5] $ and $ f(p)=5 $ which is already maximum possible. But must perform the operation anyway. We can get $ f(p)=3 $ by choosing $ i=1 $ and $ j=2 $ which makes $ p = [2,1,3,4,5] $ .

In the second test case, we can transform $ p $ into $ [1,2,3,4,5] $ by choosing $ i=1 $ and $ j=2 $ . Thus $ f(p)=5 $ .

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
5
2 1 3 4 5
7
2 1 5 3 7 6 4
6
2 3 5 4 1 6
7
7 6 5 4 3 2 1
```

### 输出

```
3
5
2
3
2
```

