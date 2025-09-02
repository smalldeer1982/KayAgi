---
title: "Shaass and Lights"
layout: "post"
diff: 提高+/省选-
pid: CF294C
tag: ['数学', '组合数学', '逆元']
---

# Shaass and Lights

## 题目描述

There are $ n $ lights aligned in a row. These lights are numbered $ 1 $ to $ n $ from left to right. Initially some of the lights are switched on. Shaass wants to switch all the lights on. At each step he can switch a light on (this light should be switched off at that moment) if there's at least one adjacent light which is already switched on.

He knows the initial state of lights and he's wondering how many different ways there exist to switch all the lights on. Please find the required number of ways modulo $ 1000000007 (10^{9}+7) $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ where $ n $ is the number of lights in the sequence and $ m $ is the number of lights which are initially switched on, $ (1<=n<=1000,1<=m<=n) $ . The second line contains $ m $ distinct integers, each between $ 1 $ to $ n $ inclusive, denoting the indices of lights which are initially switched on.

## 输出格式

In the only line of the output print the number of different possible ways to switch on all the lights modulo $ 1000000007 (10^{9}+7) $ .

## 样例 #1

### 输入

```
3 1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4 2
1 4

```

### 输出

```
2

```

## 样例 #3

### 输入

```
11 2
4 8

```

### 输出

```
6720

```

