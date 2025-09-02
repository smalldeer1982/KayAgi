---
title: "Tram"
layout: "post"
diff: 普及/提高-
pid: CF746C
tag: []
---

# Tram

## 题目描述

The tram in Berland goes along a straight line from the point $ 0 $ to the point $ s $ and back, passing $ 1 $ meter per $ t_{1} $ seconds in both directions. It means that the tram is always in the state of uniform rectilinear motion, instantly turning around at points $ x=0 $ and $ x=s $ .

Igor is at the point $ x_{1} $ . He should reach the point $ x_{2} $ . Igor passes $ 1 $ meter per $ t_{2} $ seconds.

Your task is to determine the minimum time Igor needs to get from the point $ x_{1} $ to the point $ x_{2} $ , if it is known where the tram is and in what direction it goes at the moment Igor comes to the point $ x_{1} $ .

Igor can enter the tram unlimited number of times at any moment when his and the tram's positions coincide. It is not obligatory that points in which Igor enter and exit the tram are integers. Assume that any boarding and unboarding happens instantly. Igor can move arbitrary along the line (but not faster than $ 1 $ meter per $ t_{2} $ seconds). He can also stand at some point for some time.

## 输入格式

The first line contains three integers $ s $ , $ x_{1} $ and $ x_{2} $ ( $ 2<=s<=1000 $ , $ 0<=x_{1},x_{2}<=s $ , $ x_{1}≠x_{2} $ ) — the maximum coordinate of the point to which the tram goes, the point Igor is at, and the point he should come to.

The second line contains two integers $ t_{1} $ and $ t_{2} $ ( $ 1<=t_{1},t_{2}<=1000 $ ) — the time in seconds in which the tram passes $ 1 $ meter and the time in seconds in which Igor passes $ 1 $ meter.

The third line contains two integers $ p $ and $ d $ ( $ 1<=p<=s-1 $ , $ d $ is either $ 1 $ or ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF746C/ee7dae0e2931e541c875d1cf78343bbce2c7035a.png)) — the position of the tram in the moment Igor came to the point $ x_{1} $ and the direction of the tram at this moment. If ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF746C/74be8e06b8041e97f872d8432e27947747c25c8a.png), the tram goes in the direction from the point $ s $ to the point $ 0 $ . If $ d=1 $ , the tram goes in the direction from the point $ 0 $ to the point $ s $ .

## 输出格式

Print the minimum time in seconds which Igor needs to get from the point $ x_{1} $ to the point $ x_{2} $ .

## 说明/提示

In the first example it is profitable for Igor to go by foot and not to wait the tram. Thus, he has to pass $ 2 $ meters and it takes $ 8 $ seconds in total, because he passes $ 1 $ meter per $ 4 $ seconds.

In the second example Igor can, for example, go towards the point $ x_{2} $ and get to the point $ 1 $ in $ 6 $ seconds (because he has to pass $ 3 $ meters, but he passes $ 1 $ meters per $ 2 $ seconds). At that moment the tram will be at the point $ 1 $ , so Igor can enter the tram and pass $ 1 $ meter in $ 1 $ second. Thus, Igor will reach the point $ x_{2} $ in $ 7 $ seconds in total.

## 样例 #1

### 输入

```
4 2 4
3 4
1 1

```

### 输出

```
8

```

## 样例 #2

### 输入

```
5 4 0
1 2
3 1

```

### 输出

```
7

```

