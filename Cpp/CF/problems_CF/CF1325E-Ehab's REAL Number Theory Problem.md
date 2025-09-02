---
title: "Ehab's REAL Number Theory Problem"
layout: "post"
diff: 省选/NOI-
pid: CF1325E
tag: []
---

# Ehab's REAL Number Theory Problem

## 题目描述

You are given an array $ a $ of length $ n $ that has a special condition: every element in this array has at most 7 divisors. Find the length of the shortest non-empty subsequence of this array product of whose elements is a perfect square.

A sequence $ a $ is a subsequence of an array $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements.

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of $ a $ .

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , $ \ldots $ , $ a_{n} $ ( $ 1 \le a_i \le 10^6 $ ) — the elements of the array $ a $ .

## 输出格式

Output the length of the shortest non-empty subsequence of $ a $ product of whose elements is a perfect square. If there are several shortest subsequences, you can find any of them. If there's no such subsequence, print "-1".

## 说明/提示

In the first sample, you can choose a subsequence $ [1] $ .

In the second sample, you can choose a subsequence $ [6, 6] $ .

In the third sample, you can choose a subsequence $ [6, 15, 10] $ .

In the fourth sample, there is no such subsequence.

## 样例 #1

### 输入

```
3
1 4 6
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
2 3 6 6
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
6 15 10
```

### 输出

```
3
```

## 样例 #4

### 输入

```
4
2 3 5 7
```

### 输出

```
-1
```

