---
title: "GCD of Polynomials"
layout: "post"
diff: 普及+/提高
pid: CF901B
tag: []
---

# GCD of Polynomials

## 题目描述

Suppose you have two polynomials ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/b88d8c9afbcdbe4c3db30f4f8047f16a3a48c8eb.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/e0c93f76951451d9aabeb4047e1f1124cfc2b66d.png). Then polynomial ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/1a8148c316d81cb0dcf0ac6a016f160db2da72c1.png) can be uniquely represented in the following way:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/c5e7dcb363dde0ba8872328b8e411c128512b38f.png)This can be done using [long division](https://en.wikipedia.org/wiki/Polynomial_long_division). Here, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/a1f26d7c8115e83b311bbacc16505e6f20f92b7d.png) denotes the degree of polynomial $ P(x) $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/026a0fc1a864c69852c699730e0a6f2d32f753be.png) is called the remainder of division of polynomial ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/1a8148c316d81cb0dcf0ac6a016f160db2da72c1.png) by polynomial ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/ebb5c58177e55fa198a7a231f3c0e4b1f18a6a49.png), it is also denoted as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/6e44041e1df78606fc571f5db249361dad8df62e.png).

Since there is a way to divide polynomials with remainder, we can define Euclid's algorithm of finding the greatest common divisor of two polynomials. The algorithm takes two polynomials ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/5a51ce4106123f55c64d5fbd31176d2fcf184db6.png). If the polynomial ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/ebb5c58177e55fa198a7a231f3c0e4b1f18a6a49.png) is zero, the result is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/1a8148c316d81cb0dcf0ac6a016f160db2da72c1.png), otherwise the result is the value the algorithm returns for pair ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/ad56ca03078389def1a802276b6af4c037ddb9af.png). On each step the degree of the second argument decreases, so the algorithm works in finite number of steps. But how large that number could be? You are to answer this question.

You are given an integer $ n $ . You have to build two polynomials with degrees not greater than $ n $ , such that their coefficients are integers not exceeding $ 1 $ by their absolute value, the leading coefficients (ones with the greatest power of $ x $ ) are equal to one, and the described Euclid's algorithm performs exactly $ n $ steps finding their greatest common divisor. Moreover, the degree of the first polynomial should be greater than the degree of the second. By a step of the algorithm we mean the transition from pair ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/5a51ce4106123f55c64d5fbd31176d2fcf184db6.png) to pair ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/ad56ca03078389def1a802276b6af4c037ddb9af.png).

## 输入格式

You are given a single integer $ n $ ( $ 1<=n<=150 $ ) — the number of steps of the algorithm you need to reach.

## 输出格式

```plain
Print two polynomials in the following format.
```
In the first line print a single integer $ m $ ( $ 0<=m<=n $ ) — the degree of the polynomial.
In the second line print $ m+1 $ integers between $ -1 $ and $ 1 $ — the coefficients of the polynomial, from constant to leading.
The degree of the first polynomial should be greater than the degree of the second polynomial, the leading coefficients should be equal to $ 1 $ . Euclid's algorithm should perform exactly $ n $ steps when called using these polynomials.
If there is no answer for the given $ n $ , print -1.
If there are multiple answer, print any of them.

## 说明/提示

In the second example you can print polynomials $ x^{2}-1 $ and $ x $ . The sequence of transitions is

 $ (x^{2}-1,x)→(x,-1)→(-1,0). $ There are two steps in it.

## 样例 #1

### 输入

```
1

```

### 输出

```
1
0 1
0
1

```

## 样例 #2

### 输入

```
2

```

### 输出

```
2
-1 0 1
1
0 1

```

