---
title: "Fire in the City"
layout: "post"
diff: 提高+/省选-
pid: CF845E
tag: []
---

# Fire in the City

## 题目描述

The capital of Berland looks like a rectangle of size $ n×m $ of the square blocks of same size.

Fire!

It is known that $ k+1 $ blocks got caught on fire ( $ k+1<=n·m $ ). Those blocks are centers of ignition. Moreover positions of $ k $ of these centers are known and one of these stays unknown. All $ k+1 $ positions are distinct.

The fire goes the following way: during the zero minute of fire only these $ k+1 $ centers of ignition are burning. Every next minute the fire goes to all neighbouring blocks to the one which is burning. You can consider blocks to burn for so long that this time exceeds the time taken in the problem. The neighbouring blocks are those that touch the current block by a side or by a corner.

Berland Fire Deparment wants to estimate the minimal time it takes the fire to lighten up the whole city. Remember that the positions of $ k $ blocks (centers of ignition) are known and ( $ k+1 $ )-th can be positioned in any other block.

Help Berland Fire Department to estimate the minimal time it takes the fire to lighten up the whole city.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ k $ ( $ 1<=n,m<=10^{9} $ , $ 1<=k<=500 $ ).

Each of the next $ k $ lines contain two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i}<=n $ , $ 1<=y_{i}<=m $ ) — coordinates of the $ i $ -th center of ignition. It is guaranteed that the locations of all centers of ignition are distinct.

## 输出格式

Print the minimal time it takes the fire to lighten up the whole city (in minutes).

## 说明/提示

In the first example the last block can have coordinates $ (4,4) $ .

In the second example the last block can have coordinates $ (8,3) $ .

## 样例 #1

### 输入

```
7 7 3
1 2
2 1
5 5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
10 5 1
3 3

```

### 输出

```
2

```

