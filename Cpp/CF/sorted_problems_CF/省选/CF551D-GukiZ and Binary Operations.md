---
title: "GukiZ and Binary Operations"
layout: "post"
diff: 省选/NOI-
pid: CF551D
tag: []
---

# GukiZ and Binary Operations

## 题目描述

We all know that GukiZ often plays with arrays.

Now he is thinking about this problem: how many arrays $ a $ , of length $ n $ , with non-negative elements strictly less then $ 2^{l} $ meet the following condition: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF551D/a6e7bc576316f94114c2b7ddad7b1f99dc329174.png)? Here operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF551D/620e07dca4a112648a0a9f81b5fb9f226c4bb233.png) means bitwise AND (in Pascal it is equivalent to and, in C/C++/Java/Python it is equivalent to &), operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF551D/6bfd82b83489db5433e1a03d2bc0f44671a33056.png) means bitwise OR (in Pascal it is equivalent to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF551D/6bfd82b83489db5433e1a03d2bc0f44671a33056.png), in C/C++/Java/Python it is equivalent to |).

Because the answer can be quite large, calculate it modulo $ m $ . This time GukiZ hasn't come up with solution, and needs you to help him!

## 输入格式

First and the only line of input contains four integers $ n $ , $ k $ , $ l $ , $ m $ ( $ 2<=n<=10^{18} $ , $ 0<=k<=10^{18} $ , $ 0<=l<=64 $ , $ 1<=m<=10^{9}+7 $ ).

## 输出格式

In the single line print the number of arrays satisfying the condition above modulo $ m $ .

## 说明/提示

In the first sample, satisfying arrays are $ {1,1},{3,1},{1,3} $ .

In the second sample, only satisfying array is $ {1,1} $ .

In the third sample, satisfying arrays are $ {0,3,3},{1,3,2},{1,3,3},{2,3,1},{2,3,3},{3,3,0},{3,3,1},{3,3,2},{3,3,3} $ .

## 样例 #1

### 输入

```
2 1 2 10

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2 1 1 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 3 2 10

```

### 输出

```
9

```

