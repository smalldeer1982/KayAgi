---
title: "Sorting By Multiplication"
layout: "post"
diff: 普及+/提高
pid: CF1861D
tag: ['动态规划 DP']
---

# Sorting By Multiplication

## 题目描述

You are given an array $ a $ of length $ n $ , consisting of positive integers.

You can perform the following operation on this array any number of times (possibly zero):

- choose three integers $ l $ , $ r $ and $ x $ such that $ 1 \le l \le r \le n $ , and multiply every $ a_i $ such that $ l \le i \le r $ by $ x $ .

Note that you can choose any integer as $ x $ , it doesn't have to be positive.

You have to calculate the minimum number of operations to make the array $ a $ sorted in strictly ascending order (i. e. the condition $ a_1 < a_2 < \dots < a_n $ must be satisfied).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the array $ a $ .

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print one integer — the minimum number of operations required to make $ a $ sorted in strictly ascending order.

## 说明/提示

In the first test case, we can perform the operations as follows:

- $ l = 2 $ , $ r = 4 $ , $ x = 3 $ ;
- $ l = 4 $ , $ r = 4 $ , $ x = 2 $ ;
- $ l = 5 $ , $ r = 5 $ , $ x = 10 $ .

 After these operations, the array $ a $ becomes $ [1, 3, 6, 12, 20] $ .In the second test case, we can perform one operation as follows:

- $ l = 1 $ , $ r = 4 $ , $ x = -2 $ ;
- $ l = 6 $ , $ r = 6 $ , $ x = 1337 $ .

 After these operations, the array $ a $ becomes $ [-10, -8, -6, -4, 5, 1337] $ .In the third test case, the array $ a $ is already sorted.

## 样例 #1

### 输入

```
3
5
1 1 2 2 2
6
5 4 3 2 5 1
3
1 2 3
```

### 输出

```
3
2
0
```

