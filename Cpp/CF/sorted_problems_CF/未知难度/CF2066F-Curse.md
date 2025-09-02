---
title: "Curse"
layout: "post"
diff: 难度0
pid: CF2066F
tag: []
---

# Curse

## 题目描述

You are given two arrays of integers: $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_m $ .

You need to determine if it is possible to transform array $ a $ into array $ b $ using the following operation several (possibly, zero) times.

- Among all non-empty subarrays $ ^{\text{∗}} $ of $ a $ , choose any with the maximum sum, and replace this subarray with an arbitrary non-empty integer array.

If it is possible, you need to construct any possible sequence of operations. Constraint: in your answer, the sum of the lengths of the arrays used as replacements must not exceed $ n + m $ across all operations. The numbers must not exceed $ 10^9 $ in absolute value.

 $ ^{\text{∗}} $ An array $ a $ is a subarray of an array $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 200 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n, m $ ( $ 1 \le n, m \le 500 $ ) — the lengths of arrays $ a $ and $ b $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^6 \le a_i \le 10^6 $ ) — the elements of array $ a $ .

The third line of each test case contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ -10^6 \le b_i \le 10^6 $ ) — the elements of array $ b $ .

It is guaranteed that the sum of the values of $ n $ across all test cases does not exceed $ 500 $ .

It is guaranteed that the sum of the values of $ m $ across all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, output $ -1 $ if it is impossible to transform array $ a $ into array $ b $ .

Otherwise, in the first line, output the number of operations $ 0 \leq q \leq n + m $ . Then output the operations in the following format in the order they are performed.

In the first line of each operation, print three numbers $ l, r, k $ ( $ 1 \leq l \leq r \leq |a| $ ). In the second line, print $ k $ integers $ c_1 \ldots c_k $ , which means replacing the segment $ a_l, \ldots, a_r $ with the array $ c_1, \ldots, c_k $ .

The sum of $ k $ across all $ q $ operations must not exceed $ n + m $ . Additionally, it must hold that $ -10^9 \leq c_i \leq 10^9 $ .

You do not need to minimize the number of operations.

## 说明/提示

In the first test, the initial array is modified as follows:

 $$ [2, -3, 2, 0] \to [2, -3, -3] \to [-3, -3, -3] \to [-3, -7, -3] \to [-3, -7, 0]  $$

You may choose to output empty lines or not. Empty lines in the example are added for convenience.

## 样例 #1

### 输入

```
3
4 3
2 -3 2 0
-3 -7 0
2 1
-2 -2
2
5 4
-5 9 -3 5 -9
-6 6 -1 -9
```

### 输出

```
4
3 4 1
-3 

1 1 1
-3 

2 2 1
-7 

3 3 1
0
 
-1

3
2 4 1
-5 

1 1 1
-6 

2 2 2
6 -1
```

