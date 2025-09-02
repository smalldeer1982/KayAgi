---
title: "Moodular Arithmetic"
layout: "post"
diff: 普及+/提高
pid: CF603B
tag: []
---

# Moodular Arithmetic

## 题目描述

As behooves any intelligent schoolboy, Kevin Sun is studying psycowlogy, cowculus, and cryptcowgraphy at the Bovinia State University (BGU) under Farmer Ivan. During his Mathematics of Olympiads (MoO) class, Kevin was confronted with a weird functional equation and needs your help. For two fixed integers $ k $ and $ p $ , where $ p $ is an odd prime number, the functional equation states that

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF603B/ed6bc974175d6ded86ca0d36ce0ca4605575bbb9.png)for some function ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF603B/3d499b5681b890bdb5d1b1234e5b8d6e9d7e27b1.png). (This equation should hold for any integer $ x $ in the range $ 0 $ to $ p-1 $ , inclusive.)

It turns out that $ f $ can actually be many different functions. Instead of finding a solution, Kevin wants you to count the number of distinct functions $ f $ that satisfy this equation. Since the answer may be very large, you should print your result modulo $ 10^{9}+7 $ .

## 输入格式

The input consists of two space-separated integers $ p $ and $ k $ ( $ 3<=p<=1000000 $ , $ 0<=k<=p-1 $ ) on a single line. It is guaranteed that $ p $ is an odd prime number.

## 输出格式

Print a single integer, the number of distinct functions $ f $ modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, $ p=3 $ and $ k=2 $ . The following functions work:

1. $ f(0)=0 $ , $ f(1)=1 $ , $ f(2)=2 $ .
2. $ f(0)=0 $ , $ f(1)=2 $ , $ f(2)=1 $ .
3. $ f(0)=f(1)=f(2)=0 $ .

## 样例 #1

### 输入

```
3 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 4

```

### 输出

```
25

```

