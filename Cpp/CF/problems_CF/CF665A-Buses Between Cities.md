---
title: "Buses Between Cities"
layout: "post"
diff: 普及/提高-
pid: CF665A
tag: []
---

# Buses Between Cities

## 题目描述

A 市和 B 市之间有公交车行驶，第一班是早上 $\text{5:00}$ ，最后一班不迟于 $\text{23:59}$ 开出。

从 A 市出发的公共汽车每隔 $a$ 分钟发车，到 B 市需 $t_a$ 分钟，从 B 市出发的公共汽车每隔 $b$ 分钟发一辆车，到 A 市需 $t_b$ 分钟。

司机 Simon 为了增加工作的乐趣，数了数在他的行程途中向他驶来的公交车，但 Simon 没有计算他在起点和终点遇到的公共汽车。

给定 Simon 从 A 城到 B 城的时间，计算 Simon 将会见到的公共汽车的数量。

## 输入格式

第一行两个整数 $a,t_a\left(1\leqslant a,t_a\leqslant 120\right)$。

第二行两个整数 $b,t_b\left(1\leqslant b,t_b\leqslant 120\right)$。

第三行一个字符串，表示 Simon 从 A 市出发的时间，格式为 $\text{hh:mm}$（$\text{hh}$ 为小时，$\text{mm}$ 为分钟，且两者均用两位数表示）。

保证 Simon 从 A 市出发时一定有一辆公交车从 A 市开出，$a,t_a,b,t_b$ 的单位均为分钟。

## 输出格式

一行一个整数，表示 Simon 在路上遇到的公交车的数量。

## 样例 #1

### 输入

```
10 30
10 35
05:20

```

### 输出

```
5

```

## 样例 #2

### 输入

```
60 120
24 100
13:00

```

### 输出

```
9

```

