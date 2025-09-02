---
title: "Bash Plays with Functions"
layout: "post"
diff: 省选/NOI-
pid: CF757E
tag: []
---

# Bash Plays with Functions

## 题目描述

Bash got tired on his journey to become the greatest Pokemon master. So he decides to take a break and play with functions.

Bash defines a function $ f_{0}(n) $ , which denotes the number of ways of factoring $ n $ into two factors $ p $ and $ q $ such that $ gcd(p,q)=1 $ . In other words, $ f_{0}(n) $ is the number of ordered pairs of positive integers $ (p,q) $ such that $ p·q=n $ and $ gcd(p,q)=1 $ .

But Bash felt that it was too easy to calculate this function. So he defined a series of functions, where $ f_{r+1} $ is defined as:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF757E/ba3f455e23406140b1481185211a534c2e0f9d49.png)Where $ (u,v) $ is any ordered pair of positive integers, they need not to be co-prime.

Now Bash wants to know the value of $ f_{r}(n) $ for different $ r $ and $ n $ . Since the value could be huge, he would like to know the value modulo $ 10^{9}+7 $ . Help him!

## 输入格式

The first line contains an integer $ q $ ( $ 1<=q<=10^{6} $ ) — the number of values Bash wants to know.

Each of the next $ q $ lines contain two integers $ r $ and $ n $ ( $ 0<=r<=10^{6} $ , $ 1<=n<=10^{6} $ ), which denote Bash wants to know the value $ f_{r}(n) $ .

## 输出格式

Print $ q $ integers. For each pair of $ r $ and $ n $ given, print $ f_{r}(n) $ modulo $ 10^{9}+7 $ on a separate line.

## 样例 #1

### 输入

```
5
0 30
1 25
3 65
2 5
4 48

```

### 输出

```
8
5
25
4
630

```

