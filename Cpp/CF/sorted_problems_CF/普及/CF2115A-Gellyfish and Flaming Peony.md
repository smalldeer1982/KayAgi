---
title: "Gellyfish and Flaming Peony"
layout: "post"
diff: 普及/提高-
pid: CF2115A
tag: ['动态规划 DP', '广度优先搜索 BFS']
---

# Gellyfish and Flaming Peony

## 题目描述

Gellyfish hates math problems, but she has to finish her math homework:

Gellyfish is given an array of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ .

She needs to do the following two-step operation until all elements of $ a $ are equal:

1. Select two indexes $ i $ , $ j $ satisfying $ 1 \leq i, j \leq n $ and $ i \neq j $ .
2. Replace $ a_i $ with $ \gcd(a_i, a_j) $ .

Now, Gellyfish asks you for the minimum number of operations to achieve her goal.

It can be proven that Gellyfish can always achieve her goal.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5000 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 5000 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \leq a_i \leq 5000 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5000 $ .

## 输出格式

For each test case, output a single integer — the minimum number of operations to achieve her goal.

## 说明/提示

In the first test case, the following is a way that minimizes the number of operations:

1. Choose $ i = 3 $ and $ j=2 $ and replace $ a_3 $ with $ \gcd(a_3,a_2) = \gcd(30, 20) = 10 $ , then $ a $ becomes $ [12, 20, 10] $ .
2. Choose $ i=1 $ and $ j=3 $ and replace $ a_1 $ with $ \gcd(a_1,a_3) = \gcd(12, 10) = 2 $ , then $ a $ becomes $ [2, 20, 10] $ .
3. Choose $ i=2 $ and $ j=1 $ and replace $ a_2 $ with $ \gcd(a_2,a_1) = \gcd(20, 2) = 2 $ , then $ a $ becomes $ [2, 2, 10] $ .
4. Choose $ i=3 $ and $ j=1 $ and replace $ a_3 $ with $ \gcd(a_3,a_1) = \gcd(10, 2) = 2 $ , then $ a $ becomes $ [2, 2, 2] $ .

## 样例 #1

### 输入

```
3
3
12 20 30
6
1 9 1 9 8 1
3
6 14 15
```

### 输出

```
4
3
3
```

