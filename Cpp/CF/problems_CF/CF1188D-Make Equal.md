---
title: "Make Equal"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1188D
tag: []
---

# Make Equal

## 题目描述

You are given $ n $ numbers $ a_1, a_2, \dots, a_n $ . In one operation we can add to any one of those numbers a nonnegative integer power of $ 2 $ .

What is the smallest number of operations we need to perform to make all $ n $ numbers equal? It can be proved that under given constraints it doesn't exceed $ 10^{18} $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^{17} $ ).

## 输出格式

Output exactly one integer — the smallest number of operations we need to perform to make all $ n $ numbers equal.

## 说明/提示

In the first example, all numbers are already equal. So the needed number of operation is $ 0 $ .

In the second example, we can apply the operation $ 3 $ times: add $ 8 $ to first $ 2 $ , add $ 8 $ to second $ 2 $ , add $ 2 $ to $ 8 $ , making all numbers equal to $ 10 $ . It can be proved that we can't make all numbers equal in less than $ 3 $ operations.

## 样例 #1

### 输入

```
4
228 228 228 228

```

### 输出

```
0
```

## 样例 #2

### 输入

```
3
2 2 8

```

### 输出

```
3
```

