---
title: "Memory and Casinos"
layout: "post"
diff: 省选/NOI-
pid: CF712E
tag: []
---

# Memory and Casinos

## 题目描述

There are $ n $ casinos lined in a row. If Memory plays at casino $ i $ , he has probability $ p_{i} $ to win and move to the casino on the right ( $ i+1 $ ) or exit the row (if $ i=n $ ), and a probability $ 1-p_{i} $ to lose and move to the casino on the left ( $ i-1 $ ) or also exit the row (if $ i=1 $ ).

We say that Memory dominates on the interval $ i...\ j $ if he completes a walk such that,

- He starts on casino $ i $ .
- He never looses in casino $ i $ .
- He finishes his walk by winning in casino $ j $ .

Note that Memory can still walk left of the $ 1 $ -st casino and right of the casino $ n $ and that always finishes the process.

Now Memory has some requests, in one of the following forms:

- $ 1 $ $ i $ $ a $ $ b $ : Set ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF712E/c42dd9c43ce106339882f9fe876940fd18941cce.png).
- $ 2 $ $ l $ $ r $ : Print the probability that Memory will dominate on the interval $ l...\ r $ , i.e. compute the probability that Memory will first leave the segment $ l...\ r $ after winning at casino $ r $ , if she starts in casino $ l $ .

It is guaranteed that at any moment of time $ p $ is a non-decreasing sequence, i.e. $ p_{i}<=p_{i+1} $ for all $ i $ from $ 1 $ to $ n-1 $ .

Please help Memory by answering all his requests!

## 输入格式

The first line of the input contains two integers $ n $ and $ q $ ( $ 1<=n,q<=100000 $ ), — number of casinos and number of requests respectively.

The next $ n $ lines each contain integers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i}&lt;b_{i}<=10^{9} $ ) — ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF712E/b2ea302f05f09d0a7bd195646f212cec2cdf90af.png) is the probability $ p_{i} $ of winning in casino $ i $ .

The next $ q $ lines each contain queries of one of the types specified above ( $ 1<=a&lt;b<=10^{9} $ , $ 1<=i<=n $ , $ 1<=l<=r<=n $ ).

It's guaranteed that there will be at least one query of type $ 2 $ , i.e. the output will be non-empty. Additionally, it is guaranteed that $ p $ forms a non-decreasing sequence at all times.

## 输出格式

Print a real number for every request of type $ 2 $ — the probability that boy will "dominate" on that interval. Your answer will be considered correct if its absolute error does not exceed $ 10^{-4} $ .

Namely: let's assume that one of your answers is $ a $ , and the corresponding answer of the jury is $ b $ . The checker program will consider your answer correct if $ |a-b|<=10^{-4} $ .

## 样例 #1

### 输入

```
3 13
1 3
1 2
2 3
2 1 1
2 1 2
2 1 3
2 2 2
2 2 3
2 3 3
1 2 2 3
2 1 1
2 1 2
2 1 3
2 2 2
2 2 3
2 3 3

```

### 输出

```
0.3333333333
0.2000000000
0.1666666667
0.5000000000
0.4000000000
0.6666666667
0.3333333333
0.2500000000
0.2222222222
0.6666666667
0.5714285714
0.6666666667

```

