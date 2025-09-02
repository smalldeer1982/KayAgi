---
title: "Lust"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF891E
tag: []
---

# Lust

## 题目描述

A false witness that speaketh lies!

You are given a sequence containing $ n $ integers. There is a variable $ res $ that is equal to $ 0 $ initially. The following process repeats $ k $ times.

Choose an index from $ 1 $ to $ n $ uniformly at random. Name it $ x $ . Add to $ res $ the multiply of all $ a_{i} $ 's such that $ 1<=i<=n $ , but $ i≠x $ . Then, subtract $ a_{x} $ by $ 1 $ .

You have to find expected value of $ res $ at the end of the process. It can be proved that the expected value of $ res $ can be represented as an irreducible fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF891E/2c40be71c60fe708ee9e4e80e2cd7a26163f3bd6.png). You have to find ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF891E/9a9fda8924087f2c7a7148a751aac9511d3b1e3c.png).

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=5000 $ , $ 1<=k<=10^{9} $ ) — the number of elements and parameter $ k $ that is specified in the statement.

The second line contains $ n $ space separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=10^{9} $ ).

## 输出格式

Output a single integer — the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF891E/9a9fda8924087f2c7a7148a751aac9511d3b1e3c.png).

## 样例 #1

### 输入

```
2 1
5 5

```

### 输出

```
5
```

## 样例 #2

### 输入

```
1 10
80

```

### 输出

```
10
```

## 样例 #3

### 输入

```
2 2
0 0

```

### 输出

```
500000003
```

## 样例 #4

### 输入

```
9 4
0 11 12 9 20 7 8 18 2

```

### 输出

```
169316356
```

