---
title: "Sagheer and Crossroads"
layout: "post"
diff: 普及-
pid: CF812A
tag: []
---

# Sagheer and Crossroads

## 题目描述

Sagheer is walking in the street when he comes to an intersection of two roads. Each road can be represented as two parts where each part has $ 3 $ lanes getting into the intersection (one for each direction) and $ 3 $ lanes getting out of the intersection, so we have $ 4 $ parts in total. Each part has $ 4 $ lights, one for each lane getting into the intersection ( $ l $ — left, $ s $ — straight, $ r $ — right) and a light $ p $ for a pedestrian crossing.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF812A/a08cde5c54e404c978bae7b092917e8befa50c5b.png)An accident is possible if a car can hit a pedestrian. This can happen if the light of a pedestrian crossing of some part and the light of a lane that can get to or from that same part are green at the same time.

Now, Sagheer is monitoring the configuration of the traffic lights. Your task is to help him detect whether an accident is possible.

## 输入格式

The input consists of four lines with each line describing a road part given in a counter-clockwise order.

Each line contains four integers $ l $ , $ s $ , $ r $ , $ p $ — for the left, straight, right and pedestrian lights, respectively. The possible values are $ 0 $ for red light and $ 1 $ for green light.

## 输出格式

On a single line, print "YES" if an accident is possible, and "NO" otherwise.

## 说明/提示

In the first example, some accidents are possible because cars of part $ 1 $ can hit pedestrians of parts $ 1 $ and $ 4 $ . Also, cars of parts $ 2 $ and $ 3 $ can hit pedestrians of part $ 4 $ .

In the second example, no car can pass the pedestrian crossing of part $ 4 $ which is the only green pedestrian light. So, no accident can occur.

## 样例 #1

### 输入

```
1 0 0 1
0 1 0 0
0 0 1 0
0 0 0 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
0 1 1 0
1 0 1 0
1 1 0 0
0 0 0 1

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
1 0 0 0
0 0 0 1
0 0 0 0
1 0 1 0

```

### 输出

```
NO

```

