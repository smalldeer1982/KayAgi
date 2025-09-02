---
title: "The Minimum Number of Variables"
layout: "post"
diff: 提高+/省选-
pid: CF279D
tag: []
---

# The Minimum Number of Variables

## 题目描述

You've got a positive integer sequence $ a_{1},a_{2},...,a_{n} $ . All numbers in the sequence are distinct. Let's fix the set of variables $ b_{1},b_{2},...,b_{m} $ . Initially each variable $ b_{i} $ $ (1<=i<=m) $ contains the value of zero. Consider the following sequence, consisting of $ n $ operations.

The first operation is assigning the value of $ a_{1} $ to some variable $ b_{x} $ $ (1<=x<=m) $ . Each of the following $ n-1 $ operations is assigning to some variable $ b_{y} $ the value that is equal to the sum of values that are stored in the variables $ b_{i} $ and $ b_{j} $ $ (1<=i,j,y<=m) $ . At that, the value that is assigned on the $ t $ -th operation, must equal $ a_{t} $ . For each operation numbers $ y,i,j $ are chosen anew.

Your task is to find the minimum number of variables $ m $ , such that those variables can help you perform the described sequence of operations.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=23) $ . The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{k}<=10^{9}) $ .

It is guaranteed that all numbers in the sequence are distinct.

## 输出格式

In a single line print a single number — the minimum number of variables $ m $ , such that those variables can help you perform the described sequence of operations.

If you cannot perform the sequence of operations at any $ m $ , print -1.

## 说明/提示

In the first sample, you can use two variables $ b_{1} $ and $ b_{2} $ to perform the following sequence of operations.

1. $ b_{1} $ := $ 1 $ ;
2. $ b_{2} $ := $ b_{1}+b_{1} $ ;
3. $ b_{1} $ := $ b_{1}+b_{2} $ ;
4. $ b_{1} $ := $ b_{1}+b_{1} $ ;
5. $ b_{1} $ := $ b_{1}+b_{2} $ .

## 样例 #1

### 输入

```
5
1 2 3 6 8

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
3 6 5

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
6
2 4 8 6 10 18

```

### 输出

```
3

```

