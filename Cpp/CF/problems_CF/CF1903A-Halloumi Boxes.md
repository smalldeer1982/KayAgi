---
title: "Halloumi Boxes"
layout: "post"
diff: 入门
pid: CF1903A
tag: []
---

# Halloumi Boxes

## 题目描述

Theofanis is busy after his [last contest](https://codeforces.com/contest/1594/problem/A), as now, he has to deliver many halloumis all over the world. He stored them inside $ n $ boxes and each of which has some number $ a_i $ written on it.

He wants to sort them in non-decreasing order based on their number, however, his machine works in a strange way. It can only reverse any subarray $ ^{\dagger} $ of boxes with length at most $ k $ .

Find if it's possible to sort the boxes using any number of reverses.

 $ ^{\dagger} $ Reversing a subarray means choosing two indices $ i $ and $ j $ (where $ 1 \le i \le j \le n $ ) and changing the array $ a_1, a_2, \ldots, a_n $ to $ a_1, a_2, \ldots, a_{i-1}, \; a_j, a_{j-1}, \ldots, a_i, \; a_{j+1}, \ldots, a_{n-1}, a_n $ . The length of the subarray is then $ j - i + 1 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

Each test case consists of two lines.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 100 $ ) — the number of boxes and the length of the maximum reverse that Theofanis can make.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^{9} $ ) — the number written on each box.

## 输出格式

For each test case, print YES (case-insensitive), if the array can be sorted in non-decreasing order, or NO (case-insensitive) otherwise.

## 说明/提示

In the first two test cases, the boxes are already sorted in non-decreasing order.

In the third test case, we can reverse the whole array.

In the fourth test case, we can reverse the first two boxes and the last two boxes.

In the fifth test case, it can be shown that it's impossible to sort the boxes.

## 样例 #1

### 输入

```
5
3 2
1 2 3
3 1
9 9 9
4 4
6 4 2 1
4 3
10 3 830 14
2 1
3 1
```

### 输出

```
YES
YES
YES
YES
NO
```

