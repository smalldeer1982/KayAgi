---
title: "Sorting Permutations"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF398E
tag: []
---

# Sorting Permutations

## 题目描述

We are given a permutation sequence $ a_{1},a_{2},...,a_{n} $ of numbers from $ 1 $ to $ n $ . Let's assume that in one second, we can choose some disjoint pairs $ (u_{1},v_{1}),(u_{2},v_{2}),...,(u_{k},v_{k}) $ and swap all $ a_{ui} $ and $ a_{vi} $ for every $ i $ at the same time ( $ 1<=u_{i}&lt;v_{i}<=n $ ). The pairs are disjoint if every $ u_{i} $ and $ v_{j} $ are different from each other.

We want to sort the sequence completely in increasing order as fast as possible. Given the initial permutation, calculate the number of ways to achieve this. Two ways are different if and only if there is a time $ t $ , such that the set of pairs used for swapping at that time are different as sets (so ordering of pairs doesn't matter). If the given permutation is already sorted, it takes no time to sort, so the number of ways to sort it is $ 1 $ .

To make the problem more interesting, we have $ k $ holes inside the permutation. So exactly $ k $ numbers of $ a_{1},a_{2},...,a_{n} $ are not yet determined. For every possibility of filling the holes, calculate the number of ways, and print the total sum of these values modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains two integers $ n $ $ (1<=n<=10^{5}) $ and $ k $ $ (0<=k<=12) $ . The second line contains the permutation sequence $ a_{1},...,a_{n} $ $ (0<=a_{i}<=n) $ . If a number is not yet determined, it is denoted as $ 0 $ . There are exactly $ k $ zeroes. All the numbers $ a_{i} $ that aren't equal to zero are distinct.

## 输出格式

Print the total sum of the number of ways modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
5 0
1 5 2 4 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5 2
1 0 2 4 0

```

### 输出

```
7

```

