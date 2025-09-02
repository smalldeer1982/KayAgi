---
title: "Short LIS"
layout: "post"
diff: 难度0
pid: AT_jag2018summer_day2_k
tag: []
---

# Short LIS

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2018summer-day2/tasks/jag2018summer_day2_k

You are given three integers $ N $, $ A $, and $ B $.

Let $ P=(P_0,P_1,...,P_{N-1}) $ be a permutation of $ (0,1,...,N-1) $. $ P $ is said **good** if and only if it satisfies all of the following conditions:

- The length of a longest increasing subsequence of $ P $ is at most $ 2 $.
- $ P_A\ =\ B $

Count the number of good permutations modulo $ 10^9+7 $.

## 输入格式

Input is given from Standard Input in the following format:

> $ N $ $ A $ $ B $

## 输出格式

Print the number of good permutations modulo $ 10^9+7 $.

## 说明/提示

### Constraints

- $ 1\ \leq\ N\ \leq\ 10^6 $
- $ 0\ \leq\ A\ \leq\ N-1 $
- $ 0\ \leq\ B\ \leq\ N-1 $

### Sample Explanation 1

The only good permutation is $ (0,2,1) $.

## 样例 #1

### 输入

```
3 0 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
12 2 3
```

### 输出

```
5390
```

## 样例 #3

### 输入

```
10000 9875 5431
```

### 输出

```
135608808
```

