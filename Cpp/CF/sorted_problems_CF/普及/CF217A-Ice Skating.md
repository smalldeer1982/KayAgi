---
title: "Ice Skating"
layout: "post"
diff: 普及/提高-
pid: CF217A
tag: []
---

# Ice Skating

## 题目描述

Bajtek is learning to skate on ice. He's a beginner, so his only mode of transportation is pushing off from a snow drift to the north, east, south or west and sliding until he lands in another snow drift. He has noticed that in this way it's impossible to get from some snow drifts to some other by any sequence of moves. He now wants to heap up some additional snow drifts, so that he can get from any snow drift to any other one. He asked you to find the minimal number of snow drifts that need to be created.

We assume that Bajtek can only heap up snow drifts at integer coordinates.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1<=n<=100 $ ) — the number of snow drifts. Each of the following $ n $ lines contains two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i},y_{i}<=1000 $ ) — the coordinates of the $ i $ -th snow drift.

Note that the north direction coinсides with the direction of $ Oy $ axis, so the east direction coinсides with the direction of the $ Ox $ axis. All snow drift's locations are distinct.

## 输出格式

Output the minimal number of snow drifts that need to be created in order for Bajtek to be able to reach any snow drift from any other one.

## 样例 #1

### 输入

```
2
2 1
1 2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
2 1
4 1

```

### 输出

```
0

```

