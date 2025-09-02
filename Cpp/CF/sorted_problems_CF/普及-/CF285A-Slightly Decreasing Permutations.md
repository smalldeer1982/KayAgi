---
title: "Slightly Decreasing Permutations"
layout: "post"
diff: 普及-
pid: CF285A
tag: []
---

# Slightly Decreasing Permutations

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

The decreasing coefficient of permutation $ p_{1},p_{2},...,p_{n} $ is the number of such $ i\ (1<=i&lt;n) $ , that $ p_{i}&gt;p_{i+1} $ .

You have numbers $ n $ and $ k $ . Your task is to print the permutation of length $ n $ with decreasing coefficient $ k $ .

## 输入格式

The single line contains two space-separated integers: $ n,k\ (1<=n<=10^{5},0<=k&lt;n) $ — the permutation length and the decreasing coefficient.

## 输出格式

In a single line print $ n $ space-separated integers: $ p_{1},p_{2},...,p_{n} $ — the permutation of length $ n $ with decreasing coefficient $ k $ .

If there are several permutations that meet this condition, print any of them. It is guaranteed that the permutation with the sought parameters exists.

## 样例 #1

### 输入

```
5 2

```

### 输出

```
1 5 2 4 3

```

## 样例 #2

### 输入

```
3 0

```

### 输出

```
1 2 3

```

## 样例 #3

### 输入

```
3 2

```

### 输出

```
3 2 1

```

