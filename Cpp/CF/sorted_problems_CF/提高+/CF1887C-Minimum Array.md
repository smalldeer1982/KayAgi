---
title: "Minimum Array"
layout: "post"
diff: 提高+/省选-
pid: CF1887C
tag: []
---

# Minimum Array

## 题目描述

Given an array $ a $ of length $ n $ consisting of integers. Then the following operation is sequentially applied to it $ q $ times:

- Choose indices $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ) and an integer $ x $ ;
- Add $ x $ to all elements of the array $ a $ in the segment $ [l, r] $ . More formally, assign $ a_i := a_i + x $ for all $ l \le i \le r $ .

Let $ b_j $ be the array $ a $ obtained after applying the first $ j $ operations ( $ 0 \le j \le q $ ). Note that $ b_0 $ is the array $ a $ before applying any operations.

You need to find the lexicographically minimum $ ^{\dagger} $ array among all arrays $ b_j $ .

 $ ^{\dagger} $ An array $ x $ is lexicographically smaller than array $ y $ if there is an index $ i $ such that $ x_i < y_i $ , and $ x_j = y_j $ for all $ j < i $ . In other words, for the first index $ i $ where the arrays differ, $ x_i < y_i $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 5 \cdot 10^5 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5 \cdot 10^5 $ ) — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — the elements of array $ a $ .

The third line of each test case contains a single integer $ q $ ( $ 0 \le q \le 5 \cdot 10^5 $ ) — the number of operations on the array.

In each of the next $ q $ lines, there are three integers $ l_j $ , $ r_j $ , and $ x_j $ $ (1 \le l_j \le r_j \le n, -10^9 \le x_j \le 10^9) $ — the description of each operation. The operations are given in the order they are applied.

It is guaranteed that the sum of $ n $ over all test cases and the sum of $ q $ over all test cases do not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, output the lexicographically minimum array among all arrays $ b_j $ .

## 说明/提示

In the first test case:

- $ b_0 = [1,2,3,4] $ ;
- $ b_1 = [1,2,3,4] $ ;
- $ b_2 = [-99,-98,-97,4] $ .

Thus, the lexicographically minimum array is $ b_2 $ .

In the second test case, the lexicographically minimum array is $ b_0 $ .

## 样例 #1

### 输入

```
2
4
1 2 3 4
2
1 4 0
1 3 -100
5
2 1 2 5 4
3
2 4 3
2 5 -2
1 3 1
```

### 输出

```
-99 -98 -97 4 
2 1 2 5 4
```

