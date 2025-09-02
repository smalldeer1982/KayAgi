---
title: "A Determined Cleanup"
layout: "post"
diff: 提高+/省选-
pid: CF933B
tag: []
---

# A Determined Cleanup

## 题目描述

In order to put away old things and welcome a fresh new year, a thorough cleaning of the house is a must.

Little Tommy finds an old polynomial and cleaned it up by taking it modulo another. But now he regrets doing this...

Given two integers $ p $ and $ k $ , find a polynomial $ f(x) $ with non-negative integer coefficients strictly less than $ k $ , whose remainder is $ p $ when divided by $ (x+k) $ . That is, $ f(x)=q(x)·(x+k)+p $ , where $ q(x) $ is a polynomial (not necessarily with integer coefficients).

## 输入格式

The only line of input contains two space-separated integers $ p $ and $ k $ ( $ 1<=p<=10^{18} $ , $ 2<=k<=2000 $ ).

## 输出格式

If the polynomial does not exist, print a single integer -1, or output two lines otherwise.

In the first line print a non-negative integer $ d $ — the number of coefficients in the polynomial.

In the second line print $ d $ space-separated integers $ a_{0},a_{1},...,a_{d-1} $ , describing a polynomial ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF933B/381061dc6f6f1bcc54e8d3bbd2305bd07d410ac3.png) fulfilling the given requirements. Your output should satisfy $ 0<=a_{i}<k $ for all $ 0<=i<=d-1 $ , and $ a_{d-1}≠0 $ .

If there are many possible solutions, print any of them.

## 说明/提示

In the first example, $ f(x)=x^{6}+x^{5}+x^{4}+x=(x^{5}-x^{4}+3x^{3}-6x^{2}+12x-23)·(x+2)+46 $ .

In the second example, $ f(x)=x^{2}+205x+92=(x-9)·(x+214)+2018 $ .

## 样例 #1

### 输入

```
46 2

```

### 输出

```
7
0 1 0 0 1 1 1

```

## 样例 #2

### 输入

```
2018 214

```

### 输出

```
3
92 205 1

```

