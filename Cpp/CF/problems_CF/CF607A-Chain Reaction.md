---
title: "Chain Reaction"
layout: "post"
diff: 普及/提高-
pid: CF607A
tag: []
---

# Chain Reaction

## 题目描述

There are $ n $ beacons located at distinct positions on a number line. The $ i $ -th beacon has position $ a_{i} $ and power level $ b_{i} $ . When the $ i $ -th beacon is activated, it destroys all beacons to its left (direction of decreasing coordinates) within distance $ b_{i} $ inclusive. The beacon itself is not destroyed however. Saitama will activate the beacons one at a time from right to left. If a beacon is destroyed, it cannot be activated.

Saitama wants Genos to add a beacon strictly to the right of all the existing beacons, with any position and any power level, such that the least possible number of beacons are destroyed. Note that Genos's placement of the beacon means it will be the first beacon activated. Help Genos by finding the minimum number of beacons that could be destroyed.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the initial number of beacons.

The $ i $ -th of next $ n $ lines contains two integers $ a_{i} $ and $ b_{i} $ ( $ 0<=a_{i}<=1000000 $ , $ 1<=b_{i}<=1000000 $ ) — the position and power level of the $ i $ -th beacon respectively. No two beacons will have the same position, so $ a_{i}≠a_{j} $ if $ i≠j $ .

## 输出格式

Print a single integer — the minimum number of beacons that could be destroyed if exactly one beacon is added.

## 说明/提示

For the first sample case, the minimum number of beacons destroyed is $ 1 $ . One way to achieve this is to place a beacon at position $ 9 $ with power level $ 2 $ .

For the second sample case, the minimum number of beacons destroyed is $ 3 $ . One way to achieve this is to place a beacon at position $ 1337 $ with power level $ 42 $ .

## 样例 #1

### 输入

```
4
1 9
3 1
6 1
7 4

```

### 输出

```
1

```

## 样例 #2

### 输入

```
7
1 1
2 1
3 1
4 1
5 1
6 1
7 1

```

### 输出

```
3

```

