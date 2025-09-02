---
title: "Tourists"
layout: "post"
diff: 省选/NOI-
pid: CF286D
tag: []
---

# Tourists

## 题目描述

A double tourist path, located at a park in Ultima Thule, is working by the following principle:

- We introduce the Cartesian coordinate system.
- At some points of time there are two tourists going (for a walk) from points $ (-1,0) $ and $ (1,0) $ simultaneously. The first one is walking from $ (-1,0) $ , the second one is walking from $ (1,0) $ .
- Both tourists in a pair move at the same speed $ 1 $ (distance unit per second), the first one moves along line $ x=-1 $ , the second one moves along line $ x=1 $ , both of them are moving in the positive direction of the $ Oy $ axis.
- At some points of time walls appear. Wall $ (l_{i},r_{i}) $ is a segment between points $ (0,l_{i}) $ and $ (0,r_{i}) $ . Each wall appears immediately.

The Ultima Thule government wants to learn this for each pair of tourists that walk simultaneously: for how long (in seconds) will they not see each other? Two tourists don't see each other if the segment that connects their positions on the plane intersects at least one wall. Two segments intersect if they share at least one point. We assume that the segments' ends belong to the segments.

Help the government count the required time. Note that the walls can intersect (in any way) or coincide.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ( $ 1<=n,m<=10^{5} $ ) — the number of pairs of tourists and the number of built walls. The next $ m $ lines contain three space-separated integers $ l_{i} $ , $ r_{i} $ and $ t_{i} $ each ( $ 0<=l_{i}<r_{i}<=10^{9} $ , $ 0<=t_{i}<=10^{9} $ ) — the wall ends and the time it appeared. The last line contains $ n $ distinct space-separated strictly increasing integers $ q_{1},q_{2},...,q_{n} $ ( $ 0<=q_{i}<=10^{9} $ ) — the points of time when pairs of tourists walk.

All points of time are given in seconds.

## 输出格式

For each pair of tourists print on a single line a single integer — the time in seconds when the two tourists from the corresponding pair won't see each other. Print the numbers in the order in which the they go in the input.

## 样例 #1

### 输入

```
2 2
1 4 3
3 6 5
0 1

```

### 输出

```
2
4

```

## 样例 #2

### 输入

```
3 3
0 3 4
0 1 2
2 4 0
1 3 4

```

### 输出

```
2
4
4

```

