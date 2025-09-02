---
title: "Many Perfect Squares"
layout: "post"
diff: 普及+/提高
pid: CF1781D
tag: []
---

# Many Perfect Squares

## 题目描述

You are given a set $ a_1, a_2, \ldots, a_n $ of distinct positive integers.

We define the squareness of an integer $ x $ as the number of perfect squares among the numbers $ a_1 + x, a_2 + x, \ldots, a_n + x $ .

Find the maximum squareness among all integers $ x $ between $ 0 $ and $ 10^{18} $ , inclusive.

Perfect squares are integers of the form $ t^2 $ , where $ t $ is a non-negative integer. The smallest perfect squares are $ 0, 1, 4, 9, 16, \ldots $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 50 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 50 $ ) — the size of the set.

The second line contains $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ in increasing order ( $ 1 \le a_1 < a_2 < \ldots < a_n \le 10^9 $ ) — the set itself.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 50 $ .

## 输出格式

For each test case, print a single integer — the largest possible number of perfect squares among $ a_1 + x, a_2 + x, \ldots, a_n + x $ , for some $ 0 \le x \le 10^{18} $ .

## 说明/提示

In the first test case, for $ x = 0 $ the set contains two perfect squares: $ 1 $ and $ 4 $ . It is impossible to obtain more than two perfect squares.

In the second test case, for $ x = 3 $ the set looks like $ 4, 9, 16, 25, 100 $ , that is, all its elements are perfect squares.

## 样例 #1

### 输入

```
4
5
1 2 3 4 5
5
1 6 13 22 97
1
100
5
2 5 10 17 26
```

### 输出

```
2
5
1
2
```

