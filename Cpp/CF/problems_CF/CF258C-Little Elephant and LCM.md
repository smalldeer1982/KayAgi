---
title: "Little Elephant and LCM"
layout: "post"
diff: 省选/NOI-
pid: CF258C
tag: []
---

# Little Elephant and LCM

## 题目描述

The Little Elephant loves the LCM (least common multiple) operation of a non-empty set of positive integers. The result of the LCM operation of $ k $ positive integers $ x_{1},x_{2},...,x_{k} $ is the minimum positive integer that is divisible by each of numbers $ x_{i} $ .

Let's assume that there is a sequence of integers $ b_{1},b_{2},...,b_{n} $ . Let's denote their LCMs as $ lcm(b_{1},b_{2},...,b_{n}) $ and the maximum of them as $ max(b_{1},b_{2},...,b_{n}) $ . The Little Elephant considers a sequence $ b $ good, if $ lcm(b_{1},b_{2},...,b_{n})=max(b_{1},b_{2},...,b_{n}) $ .

The Little Elephant has a sequence of integers $ a_{1},a_{2},...,a_{n} $ . Help him find the number of good sequences of integers $ b_{1},b_{2},...,b_{n} $ , such that for all $ i $ $ (1<=i<=n) $ the following condition fulfills: $ 1<=b_{i}<=a_{i} $ . As the answer can be rather large, print the remainder from dividing it by $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains a single positive integer $ n $ $ (1<=n<=10^{5}) $ — the number of integers in the sequence $ a $ . The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{5}) $ — sequence $ a $ .

## 输出格式

In the single line print a single integer — the answer to the problem modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
4
1 4 3 2

```

### 输出

```
15

```

## 样例 #2

### 输入

```
2
6 3

```

### 输出

```
13

```

