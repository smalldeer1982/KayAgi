---
title: "The Great Mixing"
layout: "post"
diff: 提高+/省选-
pid: CF788C
tag: []
---

# The Great Mixing

## 题目描述

Sasha and Kolya decided to get drunk with Coke, again. This time they have $ k $ types of Coke. $ i $ -th type is characterised by its carbon dioxide concentration ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788C/e1c7e5030c197d01ff231112151d3da349759c26.png). Today, on the party in honour of Sergiy of Vancouver they decided to prepare a glass of Coke with carbon dioxide concentration ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788C/cf824d7bd7455690f355c377fa2d0f87b9cfce24.png). The drink should also be tasty, so the glass can contain only integer number of liters of each Coke type (some types can be not presented in the glass). Also, they want to minimize the total volume of Coke in the glass.

Carbon dioxide concentration is defined as the volume of carbone dioxide in the Coke divided by the total volume of Coke. When you mix two Cokes, the volume of carbon dioxide sums up, and the total volume of Coke sums up as well.

Help them, find the minimal natural number of liters needed to create a glass with carbon dioxide concentration ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788C/cf824d7bd7455690f355c377fa2d0f87b9cfce24.png). Assume that the friends have unlimited amount of each Coke type.

## 输入格式

The first line contains two integers $ n $ , $ k $ ( $ 0<=n<=1000 $ , $ 1<=k<=10^{6} $ ) — carbon dioxide concentration the friends want and the number of Coke types.

The second line contains $ k $ integers $ a_{1},a_{2},...,a_{k} $ ( $ 0<=a_{i}<=1000 $ ) — carbon dioxide concentration of each type of Coke. Some Coke types can have same concentration.

## 输出格式

Print the minimal natural number of liter needed to prepare a glass with carbon dioxide concentration ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788C/cf824d7bd7455690f355c377fa2d0f87b9cfce24.png), or -1 if it is impossible.

## 说明/提示

In the first sample case, we can achieve concentration ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788C/53c0c0e0841a7863e5e41d3ae6109fc13a9793f0.png) using one liter of Coke of types ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788C/da8eb2670aa7e9cd04451ad3d364dcfa7808ce21.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788C/58f5368f174695d4a9676aa063eb233c189ffbac.png): ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788C/9c80a149431da6c85f5bf624aec9db77964b8cd4.png).

In the second case, we can achieve concentration ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788C/963e89a320201d0d065c93114d2e7ec46c38edca.png) using two liters of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788C/37018a685b28e11b8bb14963b061142acb08a0ad.png) type and one liter of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788C/651b259754ff1d1b6742b5c61d5d87e9e1ce4261.png) type: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF788C/527baa6d1f1947adca91a049754dca2254588380.png).

## 样例 #1

### 输入

```
400 4
100 300 450 500

```

### 输出

```
2

```

## 样例 #2

### 输入

```
50 2
100 25

```

### 输出

```
3

```

