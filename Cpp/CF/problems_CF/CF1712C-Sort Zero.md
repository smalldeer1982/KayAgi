---
title: "Sort Zero"
layout: "post"
diff: 普及/提高-
pid: CF1712C
tag: ['贪心']
---

# Sort Zero

## 题目描述

An array is sorted if it has no inversions

A Young Boy



You are given an array of $ n $ positive integers $ a_1,a_2,\ldots,a_n $ .

In one operation you do the following:

1. Choose any integer $ x $ .
2. For all $ i $ such that $ a_i = x $ , do $ a_i := 0 $ (assign $ 0 $ to $ a_i $ ).

Find the minimum number of operations required to sort the array in non-decreasing order.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ).

The second line of each test case contains $ n $ positive integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le n $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case print one integer — the minimum number of operations required to sort the array in non-decreasing order.

## 说明/提示

In the first test case, you can choose $ x = 3 $ for the operation, the resulting array is $ [0, 0, 2] $ .

In the second test case, you can choose $ x = 1 $ for the first operation and $ x = 3 $ for the second operation, the resulting array is $ [0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
5
3
3 3 2
4
1 3 1 3
5
4 1 5 3 2
4
2 4 1 2
1
1
```

### 输出

```
1
2
4
3
0
```

