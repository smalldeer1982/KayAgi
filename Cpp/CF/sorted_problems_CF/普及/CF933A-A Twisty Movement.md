---
title: "A Twisty Movement"
layout: "post"
diff: 普及/提高-
pid: CF933A
tag: ['动态规划 DP', '线段树', '枚举', '前缀和']
---

# A Twisty Movement

## 题目描述

A dragon symbolizes wisdom, power and wealth. On Lunar New Year's Day, people model a dragon with bamboo strips and clothes, raise them with rods, and hold the rods high and low to resemble a flying dragon.

A performer holding the rod low is represented by a $ 1 $ , while one holding it high is represented by a $ 2 $ . Thus, the line of performers can be represented by a sequence $ a_{1},a_{2},...,a_{n} $ .

Little Tommy is among them. He would like to choose an interval $ [l,r] $ ( $ 1<=l<=r<=n $ ), then reverse $ a_{l},a_{l+1},...,a_{r} $ so that the length of the longest non-decreasing subsequence of the new sequence is maximum.

A non-decreasing subsequence is a sequence of indices $ p_{1},p_{2},...,p_{k} $ , such that $ p_{1}<p_{2}<...<p_{k} $ and $ a_{p1}<=a_{p2}<=...<=a_{pk} $ . The length of the subsequence is $ k $ .

## 输入格式

The first line contains an integer $ n $ $ (1<=n<=2000) $ , denoting the length of the original sequence.

The second line contains $ n $ space-separated integers, describing the original sequence $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=2,i=1,2,...,n) $ .

## 输出格式

Print a single integer, which means the maximum possible length of the longest non-decreasing subsequence of the new sequence.

## 说明/提示

In the first example, after reversing $ [2,3] $ , the array will become $ [1,1,2,2] $ , where the length of the longest non-decreasing subsequence is $ 4 $ .

In the second example, after reversing $ [3,7] $ , the array will become $ [1,1,1,1,2,2,2,2,2,1] $ , where the length of the longest non-decreasing subsequence is $ 9 $ .

## 样例 #1

### 输入

```
4
1 2 1 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
10
1 1 2 2 2 1 1 2 2 1

```

### 输出

```
9

```

