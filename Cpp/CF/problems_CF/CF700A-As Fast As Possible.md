---
title: "As Fast As Possible"
layout: "post"
diff: 提高+/省选-
pid: CF700A
tag: []
---

# As Fast As Possible

## 题目描述

On vacations $ n $ pupils decided to go on excursion and gather all together. They need to overcome the path with the length $ l $ meters. Each of the pupils will go with the speed equal to $ v_{1} $ . To get to the excursion quickly, it was decided to rent a bus, which has seats for $ k $ people (it means that it can't fit more than $ k $ people at the same time) and the speed equal to $ v_{2} $ . In order to avoid seasick, each of the pupils want to get into the bus no more than once.

Determine the minimum time required for all $ n $ pupils to reach the place of excursion. Consider that the embarkation and disembarkation of passengers, as well as the reversal of the bus, take place immediately and this time can be neglected.

## 输入格式

The first line of the input contains five positive integers $ n $ , $ l $ , $ v_{1} $ , $ v_{2} $ and $ k $ ( $ 1<=n<=10000 $ , $ 1<=l<=10^{9} $ , $ 1<=v_{1}&lt;v_{2}<=10^{9} $ , $ 1<=k<=n $ ) — the number of pupils, the distance from meeting to the place of excursion, the speed of each pupil, the speed of bus and the number of seats in the bus.

## 输出格式

Print the real number — the minimum time in which all pupils can reach the place of excursion. Your answer will be considered correct if its absolute or relative error won't exceed $ 10^{-6} $ .

## 说明/提示

In the first sample we should immediately put all five pupils to the bus. The speed of the bus equals $ 2 $ and the distance is equal to $ 10 $ , so the pupils will reach the place of excursion in time $ 10/2=5 $ .

## 样例 #1

### 输入

```
5 10 1 2 5

```

### 输出

```
5.0000000000

```

## 样例 #2

### 输入

```
3 6 1 2 1

```

### 输出

```
4.7142857143

```

