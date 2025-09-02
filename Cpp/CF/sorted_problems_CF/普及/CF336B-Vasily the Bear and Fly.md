---
title: "Vasily the Bear and Fly"
layout: "post"
diff: 普及/提高-
pid: CF336B
tag: []
---

# Vasily the Bear and Fly

## 题目描述

One beautiful day Vasily the bear painted $ 2m $ circles of the same radius $ R $ on a coordinate plane. Circles with numbers from $ 1 $ to $ m $ had centers at points $ (2R-R,0) $ , $ (4R-R,0) $ , $ ... $ , $ (2Rm-R,0) $ , respectively. Circles with numbers from $ m+1 $ to $ 2m $ had centers at points $ (2R-R,2R) $ , $ (4R-R,2R) $ , $ ... $ , $ (2Rm-R,2R) $ , respectively.

Naturally, the bear painted the circles for a simple experiment with a fly. The experiment continued for $ m^{2} $ days. Each day of the experiment got its own unique number from $ 0 $ to $ m^{2}-1 $ , inclusive.

On the day number $ i $ the following things happened:

1. The fly arrived at the coordinate plane at the center of the circle with number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336B/1b364c80eefc9bb591cfee14c9b688961a93a8ea.png) (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336B/2e19bbae9bd88a29fe3fe77f1d030d713103ddf9.png) is the result of dividing number $ x $ by number $ y $ , rounded down to an integer).
2. The fly went along the coordinate plane to the center of the circle number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336B/c14650a911b9c897e385d07e41f4fe67d4bab52b.png) (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336B/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) is the remainder after dividing number $ x $ by number $ y $ ). The bear noticed that the fly went from the center of circle $ v $ to the center of circle $ u $ along the shortest path with all points lying on the border or inside at least one of the $ 2m $ circles. After the fly reached the center of circle $ u $ , it flew away in an unknown direction.

Help Vasily, count the average distance the fly went along the coordinate plane during each of these $ m^{2} $ days.

## 输入格式

The first line contains two integers $ m,R $ ( $ 1<=m<=10^{5} $ , $ 1<=R<=10 $ ).

## 输出格式

In a single line print a single real number — the answer to the problem. The answer will be considered correct if its absolute or relative error doesn't exceed $ 10^{-6} $ .

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336B/6102118b4e5d6ba27b3c37cb86bca9d322e9441e.png)

Figure to the second sample

## 样例 #1

### 输入

```
1 1

```

### 输出

```
2.0000000000

```

## 样例 #2

### 输入

```
2 2

```

### 输出

```
5.4142135624

```

