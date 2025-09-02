---
title: "Building Permutation"
layout: "post"
diff: 普及-
pid: CF285C
tag: []
---

# Building Permutation

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

You have a sequence of integers $ a_{1},a_{2},...,a_{n} $ . In one move, you are allowed to decrease or increase any number by one. Count the minimum number of moves, needed to build a permutation from this sequence.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=3·10^{5} $ ) — the size of the sought permutation. The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ -10^{9}<=a_{i}<=10^{9} $ ).

## 输出格式

Print a single number — the minimum number of moves.

Please, do not use the %lld specifier to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first sample you should decrease the first number by one and then increase the second number by one. The resulting permutation is $ (2,1) $ .

In the second sample you need 6 moves to build permutation $ (1,3,2) $ .

## 样例 #1

### 输入

```
2
3 0

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
-1 -1 2

```

### 输出

```
6

```

