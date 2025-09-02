---
title: "Xor-sequences"
layout: "post"
diff: 提高+/省选-
pid: CF691E
tag: ['模拟', '进制', '位运算']
---

# Xor-sequences

## 题目描述

You are given $ n $ integers $ a_{1},a_{2},...,a_{n} $ .

A sequence of integers $ x_{1},x_{2},...,x_{k} $ is called a "xor-sequence" if for every $ 1<=i<=k-1 $ the number of ones in the binary representation of the number $ x_{i} $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF691E/081f686069870b762728923799c454e27369af9a.png) $ x_{i+1} $ 's is a multiple of $ 3 $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF691E/187abd20483c4318d7cd71518f323b9990bcdd61.png) for all $ 1<=i<=k $ . The symbol ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF691E/081f686069870b762728923799c454e27369af9a.png) is used for the binary exclusive or operation.

How many "xor-sequences" of length $ k $ exist? Output the answer modulo $ 10^{9}+7 $ .

Note if $ a=[1,1] $ and $ k=1 $ then the answer is $ 2 $ , because you should consider the ones from $ a $ as different.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=100 $ , $ 1<=k<=10^{18} $ ) — the number of given integers and the length of the "xor-sequences".

The second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=10^{18} $ ).

## 输出格式

Print the only integer $ c $ — the number of "xor-sequences" of length $ k $ modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
5 2
15 1 2 4 8

```

### 输出

```
13

```

## 样例 #2

### 输入

```
5 1
15 1 2 4 8

```

### 输出

```
5

```

