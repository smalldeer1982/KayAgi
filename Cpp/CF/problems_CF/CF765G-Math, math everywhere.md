---
title: "Math, math everywhere"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF765G
tag: []
---

# Math, math everywhere

## 题目描述

If you have gone that far, you'll probably skip unnecessary legends anyway...

You are given a binary string ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF765G/6f5e6f7df69128977b79b7463c73fb36b053692e.png) and an integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF765G/751b745076fc47afb357605550109735f432dc0d.png). Find the number of integers $ k $ , $ 0<=k&lt;N $ , such that for all $ i=0 $ , $ 1 $ , ..., $ m-1 $

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF765G/c12a5d894fc1147c0baa00e3bc64f9ecad04c6da.png) Print the answer modulo $ 10^{9}+7 $ .

## 输入格式

In the first line of input there is a string $ s $ consisting of $ 0 $ 's and $ 1 $ 's ( $ 1<=|s|<=40 $ ).

In the next line of input there is an integer $ n $ ( $ 1<=n<=5·10^{5} $ ).

Each of the next $ n $ lines contains two space-separated integers $ p_{i} $ , $ α_{i} $ ( $ 1<=p_{i},α_{i}<=10^{9} $ , $ p_{i} $ is prime). All $ p_{i} $ are distinct.

## 输出格式

A single integer — the answer to the problem.

## 样例 #1

### 输入

```
1
2
2 1
3 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
01
2
3 2
5 1

```

### 输出

```
15

```

## 样例 #3

### 输入

```
1011
1
3 1000000000

```

### 输出

```
411979884

```

