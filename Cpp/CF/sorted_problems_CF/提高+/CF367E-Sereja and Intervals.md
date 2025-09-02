---
title: "Sereja and Intervals"
layout: "post"
diff: 提高+/省选-
pid: CF367E
tag: ['动态规划 DP']
---

# Sereja and Intervals

## 题目描述

Sereja is interested in intervals of numbers, so he has prepared a problem about intervals for you. An interval of numbers is a pair of integers $ [l,r] $ $ (1<=l<=r<=m) $ . Interval $ [l_{1},r_{1}] $ belongs to interval $ [l_{2},r_{2}] $ if the following condition is met: $ l_{2}<=l_{1}<=r_{1}<=r_{2} $ .

Sereja wants to write out a sequence of $ n $ intervals $ [l_{1},r_{1}] $ , $ [l_{2},r_{2}] $ , $ ... $ , $ [l_{n},r_{n}] $ on a piece of paper. At that, no interval in the sequence can belong to some other interval of the sequence. Also, Sereja loves number $ x $ very much and he wants some (at least one) interval in the sequence to have $ l_{i}=x $ . Sereja wonders, how many distinct ways to write such intervals are there?

Help Sereja and find the required number of ways modulo $ 1000000007 $ $ (10^{9}+7) $ .

Two ways are considered distinct if there is such $ j $ $ (1<=j<=n) $ , that the $ j $ -th intervals in two corresponding sequences are not equal.

## 输入格式

The first line contains integers $ n $ , $ m $ , $ x $ $ (1<=n·m<=100000,1<=x<=m) $ — the number of segments in the sequence, the constraints on the numbers in segments and Sereja's favourite number.

## 输出格式

In a single line print the answer modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In third example next sequences will be correct: $ {[1,1],[3,3]} $ , $ {[1,2],[3,3]} $ , $ {[2,2],[3,3]} $ , $ {[3,3],[1,1]} $ , $ {[3,3],[2,2]} $ , $ {[3,3],[1,2]} $ .

## 样例 #1

### 输入

```
1 1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 5 1

```

### 输出

```
240

```

## 样例 #3

### 输入

```
2 3 3

```

### 输出

```
6

```

