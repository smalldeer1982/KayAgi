---
title: "Construct Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1917F
tag: ['动态规划 DP']
---

# Construct Tree

## 题目描述

You are given an array of integers $ l_1, l_2, \dots, l_n $ and an integer $ d $ . Is it possible to construct a tree satisfying the following three conditions?

- The tree contains $ n + 1 $ nodes.
- The length of the $ i $ -th edge is equal to $ l_i $ .
- The (weighted) diameter of the tree is equal to $ d $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 250 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ d $ ( $ 2 \leq n \leq 2000, 1 \leq d \leq 2000 $ ).

The second line of each test case contains $ n $ integers $ l_1, l_2, \dots, l_n $ ( $ 1 \leq l_i \leq d $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, output $ \texttt{Yes} $ if it is possible to construct a tree that satisfies all the conditions, and $ \texttt{No} $ otherwise.

You can print the letters in any case (upper or lower).

## 说明/提示

Below, you are given the illustrations of trees for the first and third test cases. One of the diameters is highlighted by coloring its edges in red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1917F/b0da55c56a8230f64464b5410b99445c4424c394.png)

## 样例 #1

### 输入

```
3
4 10
1 2 3 4
4 7
1 4 3 4
6 18
2 4 3 7 6 7
```

### 输出

```
Yes
No
Yes
```

