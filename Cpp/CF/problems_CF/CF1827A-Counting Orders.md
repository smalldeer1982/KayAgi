---
title: "Counting Orders"
layout: "post"
diff: 普及/提高-
pid: CF1827A
tag: []
---

# Counting Orders

## 题目描述

You are given two arrays $ a $ and $ b $ each consisting of $ n $ integers. All elements of $ a $ are pairwise distinct.

Find the number of ways to reorder $ a $ such that $ a_i > b_i $ for all $ 1 \le i \le n $ , modulo $ 10^9 + 7 $ .

Two ways of reordering are considered different if the resulting arrays are different.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^{5} $ ) — the length of the array $ a $ and $ b $ .

The second line of each test case contains $ n $ distinct integers $ a_1 $ , $ a_2 $ , $ \ldots $ , $ a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the array $ a $ . It is guaranteed that all elements of $ a $ are pairwise distinct.

The second line of each test case contains $ n $ integers $ b_1 $ , $ b_2 $ , $ \ldots $ , $ b_n $ ( $ 1 \le b_i \le 10^9 $ ) — the array $ b $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^{5} $ .

## 输出格式

For each test case, output the number of ways to reorder array $ a $ such that $ a_i > b_i $ for all $ 1 \le i \le n $ , modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
5
6
9 6 8 4 5 2
4 1 5 6 3 1
3
4 3 2
3 4 9
1
2
1
3
2 3 4
1 3 3
12
2 3 7 10 23 28 29 50 69 135 420 1000
1 1 2 3 5 8 13 21 34 55 89 144
```

### 输出

```
32
0
1
0
13824
```

