---
title: "Remove Extra One"
layout: "post"
diff: 普及+/提高
pid: CF900C
tag: ['数学', '树状数组']
---

# Remove Extra One

## 题目描述

You are given a permutation $ p $ of length $ n $ . Remove one element from permutation to make the number of records the maximum possible.

We remind that in a sequence of numbers $ a_{1},a_{2},...,a_{k} $ the element $ a_{i} $ is a record if for every integer $ j $ ( $ 1<=j&lt;i $ ) the following holds: $ a_{j}&lt;a_{i} $ .

## 输入格式

The first line contains the only integer $ n $ ( $ 1<=n<=10^{5} $ ) — the length of the permutation.

The second line contains $ n $ integers $ p_{1},p_{2},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — the permutation. All the integers are distinct.

## 输出格式

Print the only integer — the element that should be removed to make the number of records the maximum possible. If there are multiple such elements, print the smallest one.

## 说明/提示

In the first example the only element can be removed.

## 样例 #1

### 输入

```
1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
5 1 2 3 4

```

### 输出

```
5

```

