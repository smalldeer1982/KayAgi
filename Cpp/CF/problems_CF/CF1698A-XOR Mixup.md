---
title: "XOR Mixup"
layout: "post"
diff: 入门
pid: CF1698A
tag: []
---

# XOR Mixup

## 题目描述

There is an array $ a $ with $ n-1 $ integers. Let $ x $ be the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all elements of the array. The number $ x $ is added to the end of the array $ a $ (now it has length $ n $ ), and then the elements are shuffled.

You are given the newly formed array $ a $ . What is $ x $ ? If there are multiple possible values of $ x $ , you can output any of them.

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 2 \leq n \leq 100 $ ) — the number of integers in the resulting array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 127 $ ) — the elements of the newly formed array $ a $ .

Additional constraint on the input: the array $ a $ is made by the process described in the statement; that is, some value of $ x $ exists.

## 输出格式

For each test case, output a single integer — the value of $ x $ , as described in the statement. If there are multiple possible values of $ x $ , output any of them.

## 说明/提示

In the first test case, one possible array $ a $ is $ a=[2, 5, 4] $ . Then $ x = 2 \oplus 5 \oplus 4 = 3 $ ( $ \oplus $ denotes the bitwise XOR), so the new array is $ [2, 5, 4, 3] $ . Afterwards, the array is shuffled to form $ [4, 3, 2, 5] $ .

In the second test case, one possible array $ a $ is $ a=[1, 10, 6, 10] $ . Then $ x = 1 \oplus 10 \oplus 6 \oplus 10 = 7 $ , so the new array is $ [1, 10, 6, 10, 7] $ . Afterwards, the array is shuffled to form $ [6, 1, 10, 7, 10] $ .

In the third test case, all elements of the array are equal to $ 6 $ , so $ x=6 $ .

In the fourth test case, one possible array $ a $ is $ a=[100, 100] $ . Then $ x = 100 \oplus 100 = 0 $ , so the new array is $ [100, 100, 0] $ . Afterwards, the array is shuffled to form $ [100, 100, 0] $ . (Note that after the shuffle, the array can remain the same.)

## 样例 #1

### 输入

```
4
4
4 3 2 5
5
6 1 10 7 10
6
6 6 6 6 6 6
3
100 100 0
```

### 输出

```
3
7
6
0
```

