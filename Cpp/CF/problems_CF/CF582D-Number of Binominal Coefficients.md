---
title: "Number of Binominal Coefficients"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF582D
tag: []
---

# Number of Binominal Coefficients

## 题目描述

For a given prime integer $ p $ and integers $ α,A $ calculate the number of pairs of integers $ (n,k) $ , such that $ 0<=k<=n<=A $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF582D/d96ba5d6be086c3d0df101778af0c927c054edb9.png) is divisible by $ p^{α} $ .

As the answer can be rather large, print the remainder of the answer moduly $ 10^{9}+7 $ .

Let us remind you that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF582D/d96ba5d6be086c3d0df101778af0c927c054edb9.png) is the number of ways $ k $ objects can be chosen from the set of $ n $ objects.

## 输入格式

The first line contains two integers, $ p $ and $ α $ ( $ 1<=p,α<=10^{9} $ , $ p $ is prime).

The second line contains the decimal record of integer $ A $ ( $ 0<=A&lt;10^{1000} $ ) without leading zeroes.

## 输出格式

In the single line print the answer to the problem.

## 说明/提示

In the first sample three binominal coefficients divisible by 4 are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF582D/bed998b9151c636dcb106a9d59d333dcf36e51ee.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF582D/ea939f10119dfab9c0d926b557f9bc915ee93a82.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF582D/7af37d32634caf541e32a8e83877ecf38ed8d42f.png).

## 样例 #1

### 输入

```
2 2
7

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 1
9

```

### 输出

```
17

```

## 样例 #3

### 输入

```
3 3
9

```

### 输出

```
0

```

## 样例 #4

### 输入

```
2 4
5000

```

### 输出

```
8576851

```

