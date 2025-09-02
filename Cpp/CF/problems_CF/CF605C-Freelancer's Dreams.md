---
title: "Freelancer's Dreams"
layout: "post"
diff: 省选/NOI-
pid: CF605C
tag: ['向量', '凸包']
---

# Freelancer's Dreams

## 题目描述

Mikhail the Freelancer dreams of two things: to become a cool programmer and to buy a flat in Moscow. To become a cool programmer, he needs at least $ p $ experience points, and a desired flat in Moscow costs $ q $ dollars. Mikhail is determined to follow his dreams and registered at a freelance site.

He has suggestions to work on $ n $ distinct projects. Mikhail has already evaluated that the participation in the $ i $ -th project will increase his experience by $ a_{i} $ per day and bring $ b_{i} $ dollars per day. As freelance work implies flexible working hours, Mikhail is free to stop working on one project at any time and start working on another project. Doing so, he receives the respective share of experience and money. Mikhail is only trying to become a cool programmer, so he is able to work only on one project at any moment of time.

Find the real value, equal to the minimum number of days Mikhail needs to make his dream come true.

For example, suppose Mikhail is suggested to work on three projects and $ a_{1}=6 $ , $ b_{1}=2 $ , $ a_{2}=1 $ , $ b_{2}=3 $ , $ a_{3}=2 $ , $ b_{3}=6 $ . Also, $ p=20 $ and $ q=20 $ . In order to achieve his aims Mikhail has to work for $ 2.5 $ days on both first and third projects. Indeed, $ a_{1}·2.5+a_{2}·0+a_{3}·2.5=6·2.5+1·0+2·2.5=20 $ and $ b_{1}·2.5+b_{2}·0+b_{3}·2.5=2·2.5+3·0+6·2.5=20 $ .

## 输入格式

The first line of the input contains three integers $ n $ , $ p $ and $ q $ ( $ 1<=n<=100000,1<=p,q<=1000000 $ ) — the number of projects and the required number of experience and money.

Each of the next $ n $ lines contains two integers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=1000000 $ ) — the daily increase in experience and daily income for working on the $ i $ -th project.

## 输出格式

Print a real value — the minimum number of days Mikhail needs to get the required amount of experience and money. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF605C/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 说明/提示

First sample corresponds to the example in the problem statement.

## 样例 #1

### 输入

```
3 20 20
6 2
1 3
2 6

```

### 输出

```
5.000000000000000

```

## 样例 #2

### 输入

```
4 1 1
2 3
3 2
2 3
3 2

```

### 输出

```
0.400000000000000

```

