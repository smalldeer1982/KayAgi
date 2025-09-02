---
title: "Generating Sets"
layout: "post"
diff: 普及+/提高
pid: CF722D
tag: []
---

# Generating Sets

## 题目描述

You are given a set $ Y $ of $ n $ distinct positive integers $ y_{1},y_{2},...,y_{n} $ .

Set $ X $ of $ n $ distinct positive integers $ x_{1},x_{2},...,x_{n} $ is said to generate set $ Y $ if one can transform $ X $ to $ Y $ by applying some number of the following two operation to integers in $ X $ :

1. Take any integer $ x_{i} $ and multiply it by two, i.e. replace $ x_{i} $ with $ 2·x_{i} $ .
2. Take any integer $ x_{i} $ , multiply it by two and add one, i.e. replace $ x_{i} $ with $ 2·x_{i}+1 $ .

Note that integers in $ X $ are not required to be distinct after each operation.

Two sets of distinct integers $ X $ and $ Y $ are equal if they are equal as sets. In other words, if we write elements of the sets in the array in the increasing order, these arrays would be equal.

Note, that any set of integers (or its permutation) generates itself.

You are given a set $ Y $ and have to find a set $ X $ that generates $ Y $ and the maximum element of $ X $ is mininum possible.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=50000 $ ) — the number of elements in $ Y $ .

The second line contains $ n $ integers $ y_{1},...,y_{n} $ ( $ 1<=y_{i}<=10^{9} $ ), that are guaranteed to be distinct.

## 输出格式

Print $ n $ integers — set of distinct integers that generate $ Y $ and the maximum element of which is minimum possible. If there are several such sets, print any of them.

## 样例 #1

### 输入

```
5
1 2 3 4 5

```

### 输出

```
4 5 2 3 1 

```

## 样例 #2

### 输入

```
6
15 14 3 13 1 12

```

### 输出

```
12 13 14 7 3 1 

```

## 样例 #3

### 输入

```
6
9 7 13 17 5 11

```

### 输出

```
4 5 2 6 3 1 

```

