---
title: "Limit"
layout: "post"
diff: 普及/提高-
pid: CF197B
tag: []
---

# Limit

## 题目描述

You are given two polynomials:

- $ P(x)=a_{0}·x^{n}+a_{1}·x^{n-1}+...+a_{n-1}·x+a_{n} $ and
- $ Q(x)=b_{0}·x^{m}+b_{1}·x^{m-1}+...+b_{m-1}·x+b_{m} $ .

Calculate limit ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/c4175ff9e67dcea784338cdf48751a5246b376e3.png).

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ( $ 0<=n,m<=100 $ ) — degrees of polynomials $ P(x) $ and $ Q(x) $ correspondingly.

The second line contains $ n+1 $ space-separated integers — the factors of polynomial $ P(x) $ : $ a_{0} $ , $ a_{1} $ , ..., $ a_{n-1} $ , $ a_{n} $ $ (-100<=a_{i}<=100,a_{0}≠0) $ .

The third line contains $ m+1 $ space-separated integers — the factors of polynomial $ Q(x) $ : $ b_{0} $ , $ b_{1} $ , ..., $ b_{m-1} $ , $ b_{m} $ $ (-100<=b_{i}<=100,b_{0}≠0) $ .

## 输出格式

If the limit equals $ +∞ $ , print "Infinity" (without quotes). If the limit equals $ -∞ $ , print "-Infinity" (without the quotes).

If the value of the limit equals zero, print "0/1" (without the quotes).

Otherwise, print an irreducible fraction — the value of limit ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/c4175ff9e67dcea784338cdf48751a5246b376e3.png), in the format "p/q" (without the quotes), where $ p $ is the — numerator, $ q $ $ (q&gt;0) $ is the denominator of the fraction.

## 说明/提示

Let's consider all samples:

1. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/fa0398edff13cf2c92e5c43221f39e276c660081.png)
2. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/c67cf94a1cc8bcaea0f1fad4d1517e71a16c059c.png)
3. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/10f72864aeb3074d34f0800e3222dff4f843160b.png)
4. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/40209670dcba21fdfb878390c6903f068a0dc416.png)
5. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/9292f5d3f957b00c90b246f44689b5ebc7f89abc.png)

You can learn more about the definition and properties of limits if you follow the link: http://en.wikipedia.org/wiki/Limit\_of\_a\_function

## 样例 #1

### 输入

```
2 1
1 1 1
2 5

```

### 输出

```
Infinity

```

## 样例 #2

### 输入

```
1 0
-1 3
2

```

### 输出

```
-Infinity

```

## 样例 #3

### 输入

```
0 1
1
1 0

```

### 输出

```
0/1

```

## 样例 #4

### 输入

```
2 2
2 1 6
4 5 -7

```

### 输出

```
1/2

```

## 样例 #5

### 输入

```
1 1
9 0
-5 2

```

### 输出

```
-9/5

```

