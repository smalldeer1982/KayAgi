---
title: "BubbleReactor"
layout: "post"
diff: 省选/NOI-
pid: CF1218A
tag: []
---

# BubbleReactor

## 题目描述

你负责``BubbleReactor``。它由$n$根连接在$n$根电线上的``BubbleCore``组成。每个电线连接两个不同的``BubbleCore``。没有一条以上电线连接的``BubbleCore``。

你的任务是通过启动每一个``BubbleCore``来启动``BubbleReactor``。为了启动``BubbleCore``，它需要从已启动的直接连接的``BubbleCore``接收电源。但是，您可以手动启动一个``BubbleCore``而不需要电源。保证所有``BubbleCore``都能启动。

在每个``BubbleCore``启动之前，它的电位是根据它所能启动的``BubbleCore``数量计算的（直接连接到它的未启动的``BubbleCore``数量、间接连接它的未启动的``BubbleCore``数量和它自己）

启动``BubbleReactor``，使所有``BubbleCore``电位的总和达到最大。

## 输入格式

第一行包含一个整数$n$（$3\leq n\leq 15000$），即``BubbleCore``数。

下面的$n$行包含两个整数$u$，$v$（$0\leq u\neq v<n$），表示``Bubblecore`` $u$和$v$之间存在电线。

## 输出格式

一个整数，代表所有``BubbleCore``电位的总和的最大值。

## 说明/提示

如果我们先启动``BubbleCore`` $8$，然后打开``BubbleCore`` $7$，$2$，$1$，$3$，$0$，$9$，$4$，$5$，$6$，我们得到$10+9+8+7+6+5+1+3+1+1=51$的电位值。

## 样例 #1

### 输入

```
10
0 1
0 3
0 4
0 9
1 2
2 3
2 7
4 5
4 6
7 8

```

### 输出

```
51

```

