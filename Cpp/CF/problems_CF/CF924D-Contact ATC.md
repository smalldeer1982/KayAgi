---
title: "Contact ATC"
layout: "post"
diff: 省选/NOI-
pid: CF924D
tag: []
---

# Contact ATC

## 题目描述

Arkady the air traffic controller is now working with $ n $ planes in the air. All planes move along a straight coordinate axis with Arkady's station being at point $ 0 $ on it. The $ i $ -th plane, small enough to be represented by a point, currently has a coordinate of $ x_{i} $ and is moving with speed $ v_{i} $ . It's guaranteed that $ x_{i}·v_{i}<0 $ , i.e., all planes are moving towards the station.

Occasionally, the planes are affected by winds. With a wind of speed $ v_{wind} $ (not necessarily positive or integral), the speed of the $ i $ -th plane becomes $ v_{i}+v_{wind} $ .

According to weather report, the current wind has a steady speed falling inside the range $ [-w,w] $ (inclusive), but the exact value cannot be measured accurately since this value is rather small — smaller than the absolute value of speed of any plane.

Each plane should contact Arkady at the exact moment it passes above his station. And you are to help Arkady count the number of pairs of planes $ (i,j) $ ( $ i<j $ ) there are such that there is a possible value of wind speed, under which planes $ i $ and $ j $ contact Arkady at the same moment. This value needn't be the same across different pairs.

The wind speed is the same for all planes. You may assume that the wind has a steady speed and lasts arbitrarily long.

## 输入格式

The first line contains two integers $ n $ and $ w $ ( $ 1<=n<=100000 $ , $ 0<=w<10^{5} $ ) — the number of planes and the maximum wind speed.

The $ i $ -th of the next $ n $ lines contains two integers $ x_{i} $ and $ v_{i} $ ( $ 1<=|x_{i}|<=10^{5} $ , $ w+1<=|v_{i}|<=10^{5} $ , $ x_{i}·v_{i}<0 $ ) — the initial position and speed of the $ i $ -th plane.

Planes are pairwise distinct, that is, no pair of $ (i,j) $ ( $ i<j $ ) exists such that both $ x_{i}=x_{j} $ and $ v_{i}=v_{j} $ .

## 输出格式

Output a single integer — the number of unordered pairs of planes that can contact Arkady at the same moment.

## 说明/提示

In the first example, the following $ 3 $ pairs of planes satisfy the requirements:

- $ (2,5) $  passes the station at time $ 3/4 $ with $ v_{wind}=1 $ ;
- $ (3,4) $  passes the station at time $ 2/5 $ with $ v_{wind}=1/2 $ ;
- $ (3,5) $  passes the station at time $ 4/7 $ with $ v_{wind}=-1/4 $ .

In the second example, each of the $ 3 $ planes with negative coordinates can form a valid pair with each of the other $ 3 $ , totaling $ 9 $ pairs.

## 样例 #1

### 输入

```
5 1
-3 2
-3 3
-1 2
1 -3
3 -5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
6 1
-3 2
-2 2
-1 2
1 -2
2 -2
3 -2

```

### 输出

```
9

```

