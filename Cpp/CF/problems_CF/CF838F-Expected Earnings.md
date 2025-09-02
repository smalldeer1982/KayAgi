---
title: "Expected Earnings"
layout: "post"
diff: 省选/NOI-
pid: CF838F
tag: []
---

# Expected Earnings

## 题目描述

You are playing a game with a bag of red and black balls. Initially, you are told that the bag has $ n $ balls total. In addition, you are also told that the bag has probability $ p_{i}/10^{6} $ of containing exactly $ i $ red balls.

You now would like to buy balls from this bag. You really like the color red, so red balls are worth a unit of $ 1 $ , while black balls are worth nothing. To buy a ball, if there are still balls in the bag, you pay a cost $ c $ with $ 0<=c<=1 $ , and draw a ball randomly from the bag. You can choose to stop buying at any point (and you can even choose to not buy anything at all).

Given that you buy optimally to maximize the expected profit (i.e. # red balls - cost needed to obtain them), print the maximum expected profit.

## 输入格式

The first line of input will contain two integers $ n,X $ ( $ 1<=n<=10000 $ , $ 0<=X<=10^{6} $ ).

The next line of input will contain $ n+1 $ integers $ p_{0},p_{1},...\ p_{n} $ ( $ 0<=p_{i}<=10^{6} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF838F/7db6b8342276851a78020e225114985f8bcff7e6.png))

The value of $ c $ can be computed as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF838F/6efe404963af6b3d99ee39cb1c0a64c063c32bf4.png).

## 输出格式

Print a single floating point number representing the optimal expected value.

Your answer will be accepted if it has absolute or relative error at most $ 10^{-9} $ . More specifically, if your answer is $ a $ and the jury answer is $ b $ , your answer will be accepted if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF838F/d8d110e69d298146d951837cc2710d1c4cc74a7d.png).

## 说明/提示

Here, there is equal probability for the bag to contain 0,1,2,3 red balls. Also, it costs 0.2 to draw a ball from the bag.

## 样例 #1

### 输入

```
3 200000
250000 250000 250000 250000

```

### 输出

```
0.9000000000

```

