---
title: "Congruence Equation"
layout: "post"
diff: 提高+/省选-
pid: CF919E
tag: ['素数判断,质数,筛法', '概率论', '逆元']
---

# Congruence Equation

## 题目描述

Given an integer $ x $ . Your task is to find out how many positive integers $ n $ ( $ 1<=n<=x $ ) satisfy

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF919E/02717f82c41ef4ed609db5d967f659c9784212e1.png) where $ a,b,p $ are all known constants.

## 输入格式

The only line contains four integers $ a,b,p,x $ ( $ 2<=p<=10^{6}+3 $ , $ 1<=a,b<p $ , $ 1<=x<=10^{12} $ ). It is guaranteed that $ p $ is a prime.

## 输出格式

Print a single integer: the number of possible answers $ n $ .

## 说明/提示

In the first sample, we can see that $ n=2 $ and $ n=8 $ are possible answers.

## 样例 #1

### 输入

```
2 3 5 8

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 6 7 13

```

### 输出

```
1

```

## 样例 #3

### 输入

```
233 233 10007 1

```

### 输出

```
1

```

