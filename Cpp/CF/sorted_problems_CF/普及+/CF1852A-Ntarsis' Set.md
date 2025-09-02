---
title: "Ntarsis' Set"
layout: "post"
diff: 普及+/提高
pid: CF1852A
tag: []
---

# Ntarsis' Set

## 题目描述

Ntarsis has been given a set $ S $ , initially containing integers $ 1, 2, 3, \ldots, 10^{1000} $ in sorted order. Every day, he will remove the $ a_1 $ -th, $ a_2 $ -th, $ \ldots $ , $ a_n $ -th smallest numbers in $ S $ simultaneously.

What is the smallest element in $ S $ after $ k $ days?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case consists of two integers $ n $ and $ k $ ( $ 1 \leq n,k \leq 2 \cdot 10^5 $ ) — the length of $ a $ and the number of days.

The following line of each test case consists of $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the elements of array $ a $ .

It is guaranteed that:

- The sum of $ n $ over all test cases won't exceed $ 2 \cdot 10^5 $ ;
- The sum of $ k $ over all test cases won't exceed $ 2 \cdot 10^5 $ ;
- $ a_1 < a_2 < \cdots < a_n $ for all test cases.

## 输出格式

For each test case, print an integer that is the smallest element in $ S $ after $ k $ days.

## 说明/提示

For the first test case, each day the $ 1 $ -st, $ 2 $ -nd, $ 4 $ -th, $ 5 $ -th, and $ 6 $ -th smallest elements need to be removed from $ S $ . So after the first day, $ S $ will become $ \require{cancel} $ $ \{\cancel 1, \cancel 2, 3, \cancel 4, \cancel 5, \cancel 6, 7, 8, 9, \ldots\} = \{3, 7, 8, 9, \ldots\} $ . The smallest element is $ 3 $ .

For the second case, each day the $ 1 $ -st, $ 3 $ -rd, $ 5 $ -th, $ 6 $ -th and $ 7 $ -th smallest elements need to be removed from $ S $ . $ S $ will be changed as follows:

 Day $ S $ before $ S $ after1 $ \{\cancel 1, 2, \cancel 3, 4, \cancel 5, \cancel 6, \cancel 7, 8, 9, 10, \ldots \} $  $ \to $  $ \{2, 4, 8, 9, 10, \ldots\} $ 2 $ \{\cancel 2, 4, \cancel 8, 9, \cancel{10}, \cancel{11}, \cancel{12}, 13, 14, 15, \ldots\} $  $ \to $  $ \{4, 9, 13, 14, 15, \ldots\} $ 3 $ \{\cancel 4, 9, \cancel{13}, 14, \cancel{15}, \cancel{16}, \cancel{17}, 18, 19, 20, \ldots\} $  $ \to $  $ \{9, 14, 18, 19, 20, \ldots\} $ The smallest element left after $ k = 3 $ days is $ 9 $ .

## 样例 #1

### 输入

```
7
5 1
1 2 4 5 6
5 3
1 3 5 6 7
4 1000
2 3 4 5
9 1434
1 4 7 9 12 15 17 18 20
10 4
1 3 5 7 9 11 13 15 17 19
10 6
1 4 7 10 13 16 19 22 25 28
10 150000
1 3 4 5 10 11 12 13 14 15
```

### 输出

```
3
9
1
12874
16
18
1499986
```

