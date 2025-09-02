---
title: "Almost Identity Permutations"
layout: "post"
diff: 普及+/提高
pid: CF888D
tag: []
---

# Almost Identity Permutations

## 题目描述

A permutation $ p $ of size $ n $ is an array such that every integer from $ 1 $ to $ n $ occurs exactly once in this array.

Let's call a permutation an almost identity permutation iff there exist at least $ n-k $ indices $ i $ ( $ 1<=i<=n $ ) such that $ p_{i}=i $ .

Your task is to count the number of almost identity permutations for given numbers $ n $ and $ k $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 4<=n<=1000 $ , $ 1<=k<=4 $ ).

## 输出格式

Print the number of almost identity permutations for given $ n $ and $ k $ .

## 样例 #1

### 输入

```
4 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4 2

```

### 输出

```
7

```

## 样例 #3

### 输入

```
5 3

```

### 输出

```
31

```

## 样例 #4

### 输入

```
5 4

```

### 输出

```
76

```

