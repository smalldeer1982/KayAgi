---
title: "Maximum Control (easy)"
layout: "post"
diff: 普及-
pid: CF958B1
tag: []
---

# Maximum Control (easy)

## 题目描述

The Resistance is trying to take control over all planets in a particular solar system. This solar system is shaped like a tree. More precisely, some planets are connected by bidirectional hyperspace tunnels in such a way that there is a path between every pair of the planets, but removing any tunnel would disconnect some of them.

The Resistance already has measures in place that will, when the time is right, enable them to control every planet that is not remote. A planet is considered to be remote if it is connected to the rest of the planets only via a single hyperspace tunnel.

How much work is there left to be done: that is, how many remote planets are there?

## 输入格式

The first line of the input contains an integer $ N $ ( $ 2<=N<=1000 $ ) – the number of planets in the galaxy.

The next $ N-1 $ lines describe the hyperspace tunnels between the planets. Each of the $ N-1 $ lines contains two space-separated integers $ u $ and $ v $ ( $ 1<=u,v<=N $ ) indicating that there is a bidirectional hyperspace tunnel between the planets $ u $ and $ v $ . It is guaranteed that every two planets are connected by a path of tunnels, and that each tunnel connects a different pair of planets.

## 输出格式

A single integer denoting the number of remote planets.

## 说明/提示

In the first example, only planets $ 2 $ , $ 3 $ and $ 5 $ are connected by a single tunnel.

In the second example, the remote planets are $ 2 $ and $ 3 $ .

Note that this problem has only two versions – easy and medium.

## 样例 #1

### 输入

```
5
4 1
4 2
1 3
1 5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
1 2
4 3
1 4

```

### 输出

```
2

```

