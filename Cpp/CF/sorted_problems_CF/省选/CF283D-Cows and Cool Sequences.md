---
title: "Cows and Cool Sequences"
layout: "post"
diff: 省选/NOI-
pid: CF283D
tag: []
---

# Cows and Cool Sequences

## 题目描述

Bessie and the cows have recently been playing with "cool" sequences and are trying to construct some. Unfortunately they are bad at arithmetic, so they need your help!

A pair $ (x,y) $ of positive integers is "cool" if $ x $ can be expressed as the sum of $ y $ consecutive integers (not necessarily positive). A sequence $ (a_{1},a_{2},...,a_{n}) $ is "cool" if the pairs $ (a_{1},a_{2}),(a_{2},a_{3}),...,(a_{n-1},a_{n}) $ are all cool.

The cows have a sequence of $ n $ positive integers, $ a_{1},a_{2},...,a_{n} $ . In one move, they may replace some $ a_{i} $ with any other positive integer (there are no other limits on the new value of $ a_{i} $ ). Determine the smallest number of moves needed to make the resulting sequence cool.

## 输入格式

The first line contains a single integer, $ n $ ( $ 2<=n<=5000 $ ). The next line contains $ n $ space-separated integers, $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{15} $ ).

Please do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 输出格式

A single integer, the minimum number of $ a_{i} $ that must be changed to make the sequence cool.

## 说明/提示

In the first sample, the sequence is already cool, so we don't need to change any elements. In the second sample, we can change $ a_{2} $ to 5 and $ a_{3} $ to 10 to make (20, 5, 10, 4) which is cool. This changes 2 elements.

## 样例 #1

### 输入

```
3
6 4 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
4
20 6 3 4

```

### 输出

```
2

```

