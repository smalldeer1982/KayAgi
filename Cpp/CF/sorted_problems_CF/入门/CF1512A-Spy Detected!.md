---
title: "Spy Detected!"
layout: "post"
diff: 入门
pid: CF1512A
tag: []
---

# Spy Detected!

## 题目描述

You are given an array $ a $ consisting of $ n $ ( $ n \ge 3 $ ) positive integers. It is known that in this array, all the numbers except one are the same (for example, in the array $ [4, 11, 4, 4] $ all numbers except one are equal to $ 4 $ ).

Print the index of the element that does not equal others. The numbers in the array are numbered from one.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ). Then $ t $ test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 3 \le n \le 100 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 100 $ ).

It is guaranteed that all the numbers except one in the $ a $ array are the same.

## 输出格式

For each test case, output a single integer — the index of the element that is not equal to others.

## 样例 #1

### 输入

```
4
4
11 13 11 11
5
1 4 4 4 4
10
3 3 3 3 10 3 3 3 3 3
3
20 20 10
```

### 输出

```
2
1
5
3
```

