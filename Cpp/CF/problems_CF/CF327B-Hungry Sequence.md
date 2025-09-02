---
title: "Hungry Sequence"
layout: "post"
diff: 普及/提高-
pid: CF327B
tag: []
---

# Hungry Sequence

## 题目描述

Iahub and Iahubina went to a date at a luxury restaurant. Everything went fine until paying for the food. Instead of money, the waiter wants Iahub to write a Hungry sequence consisting of $ n $ integers.

A sequence $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ , consisting of $ n $ integers, is Hungry if and only if:

- Its elements are in increasing order. That is an inequality $ a_{i}&lt;a_{j} $ holds for any two indices $ i,j $ $ (i&lt;j) $ .
- For any two indices $ i $ and $ j $ $ (i&lt;j) $ , $ a_{j} $ must not be divisible by $ a_{i} $ .

Iahub is in trouble, so he asks you for help. Find a Hungry sequence with $ n $ elements.

## 输入格式

The input contains a single integer: $ n $ ( $ 1<=n<=10^{5} $ ).

## 输出格式

Output a line that contains $ n $ space-separated integers $ a_{1} $ $ a_{2} $ , ..., $ a_{n} $ $ (1<=a_{i}<=10^{7}) $ , representing a possible Hungry sequence. Note, that each $ a_{i} $ must not be greater than $ 10000000 $ ( $ 10^{7} $ ) and less than $ 1 $ .

If there are multiple solutions you can output any one.

## 样例 #1

### 输入

```
3

```

### 输出

```
2 9 15

```

## 样例 #2

### 输入

```
5

```

### 输出

```
11 14 20 27 31

```

