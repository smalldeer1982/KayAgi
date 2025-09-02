---
title: "Ivan and Powers of Two"
layout: "post"
diff: 普及/提高-
pid: CF305C
tag: []
---

# Ivan and Powers of Two

## 题目描述

Ivan has got an array of $ n $ non-negative integers $ a_{1},a_{2},...,a_{n} $ . Ivan knows that the array is sorted in the non-decreasing order.

Ivan wrote out integers $ 2^{a_{1}},2^{a_{2}},...,2^{a_{n}} $ on a piece of paper. Now he wonders, what minimum number of integers of form $ 2^{b} $ $ (b>=0) $ need to be added to the piece of paper so that the sum of all integers written on the paper equalled $ 2^{v}-1 $ for some integer $ v $ $ (v>=0) $ .

Help Ivan, find the required quantity of numbers.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ). The second input line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (0<=a_{i}<=2·10^{9}) $ . It is guaranteed that $ a_{1}<=a_{2}<=...<=a_{n} $ .

## 输出格式

Print a single integer — the answer to the problem.

## 说明/提示

In the first sample you do not need to add anything, the sum of numbers already equals $ 2^{3}-1=7 $ .

In the second sample you need to add numbers $ 2^{0},2^{1},2^{2} $ .

## 样例 #1

### 输入

```
4
0 1 1 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
1
3

```

### 输出

```
3

```

