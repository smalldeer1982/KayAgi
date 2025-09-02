---
title: "Blank Space"
layout: "post"
diff: 入门
pid: CF1829B
tag: []
---

# Blank Space

## 题目描述

You are given a binary array $ a $ of $ n $ elements, a binary array is an array consisting only of $ 0 $ s and $ 1 $ s.

A blank space is a segment of consecutive elements consisting of only $ 0 $ s.

Your task is to find the length of the longest blank space.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 100 $ ) — the length of the array.

The second line of each test case contains $ n $ space-separated integers $ a_i $ ( $ 0 \leq a_i \leq 1 $ ) — the elements of the array.

## 输出格式

For each test case, output a single integer — the length of the longest blank space.

## 样例 #1

### 输入

```
5
5
1 0 0 1 0
4
0 1 1 1
1
0
3
1 1 1
9
1 0 0 0 1 0 0 0 1
```

### 输出

```
2
1
1
0
3
```

