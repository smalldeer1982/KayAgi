---
title: "Maxim and Calculator"
layout: "post"
diff: 省选/NOI-
pid: CF261E
tag: []
---

# Maxim and Calculator

## 题目描述

Maxim has got a calculator. The calculator has two integer cells. Initially, the first cell contains number $ 1 $ , and the second cell contains number $ 0 $ . In one move you can perform one of the following operations:

1. Let's assume that at the current time the first cell contains number $ a $ , and the second cell contains number $ b $ . Write to the second cell number $ b+1 $ ;
2. Let's assume that at the current time the first cell contains number $ a $ , and the second cell contains number $ b $ . Write to the first cell number $ a·b $ .

Maxim is wondering, how many integers $ x $ $ (l<=x<=r) $ are there, such that we can write the number $ x $ to the first cell of the calculator, having performed at most $ p $ moves.

## 输入格式

The first line contains three integers: $ l $ , $ r $ , $ p $ $ (2<=l<=r<=10^{9},1<=p<=100) $ .

The numbers in the line are separated by single spaces.

## 输出格式

In a single line print a single integer — the answer to the problem.

## 样例 #1

### 输入

```
2 10 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2 111 100

```

### 输出

```
106

```

## 样例 #3

### 输入

```
2 111 11

```

### 输出

```
47

```

