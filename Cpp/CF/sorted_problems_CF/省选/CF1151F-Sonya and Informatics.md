---
title: "Sonya and Informatics"
layout: "post"
diff: 省选/NOI-
pid: CF1151F
tag: []
---

# Sonya and Informatics

## 题目描述

A girl named Sonya is studying in the scientific lyceum of the Kingdom of Kremland. The teacher of computer science (Sonya's favorite subject!) invented a task for her.

Given an array $ a $ of length $ n $ , consisting only of the numbers $ 0 $ and $ 1 $ , and the number $ k $ . Exactly $ k $ times the following happens:

- Two numbers $ i $ and $ j $ are chosen equiprobable such that ( $ 1 \leq i < j \leq n $ ).
- The numbers in the $ i $ and $ j $ positions are swapped.

Sonya's task is to find the probability that after all the operations are completed, the $ a $ array will be sorted in non-decreasing order. She turned to you for help. Help Sonya solve this problem.

It can be shown that the desired probability is either $ 0 $ or it can be represented as $ \dfrac{P}{Q} $ , where $ P $ and $ Q $ are coprime integers and $ Q \not\equiv 0~\pmod {10^9+7} $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2 \leq n \leq 100, 1 \leq k \leq 10^9 $ ) — the length of the array $ a $ and the number of operations.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 1 $ ) — the description of the array $ a $ .

## 输出格式

If the desired probability is $ 0 $ , print $ 0 $ , otherwise print the value $ P \cdot Q^{-1} $ $ \pmod {10^9+7} $ , where $ P $ and $ Q $ are defined above.

## 说明/提示

In the first example, all possible variants of the final array $ a $ , after applying exactly two operations: $ (0, 1, 0) $ , $ (0, 0, 1) $ , $ (1, 0, 0) $ , $ (1, 0, 0) $ , $ (0, 1, 0) $ , $ (0, 0, 1) $ , $ (0, 0, 1) $ , $ (1, 0, 0) $ , $ (0, 1, 0) $ . Therefore, the answer is $ \dfrac{3}{9}=\dfrac{1}{3} $ .

In the second example, the array will not be sorted in non-decreasing order after one operation, therefore the answer is $ 0 $ .

## 样例 #1

### 输入

```
3 2
0 1 0

```

### 输出

```
333333336
```

## 样例 #2

### 输入

```
5 1
1 1 1 0 0

```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 4
1 0 0 1 1 0

```

### 输出

```
968493834
```

