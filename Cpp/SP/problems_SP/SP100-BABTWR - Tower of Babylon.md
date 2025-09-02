---
title: "BABTWR - Tower of Babylon"
layout: "post"
diff: 普及/提高-
pid: SP100
tag: []
---

# BABTWR - Tower of Babylon

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP100/7a939db1eae2f77be9ce3ec4d462683703792d71.png)Apart from the Hanging Gardens the Babylonians (around 3000-539 b.c.) built the Tower of Babylon as well. The tower was meant to reach the sky, but the project failed because of a confusion of language imposed from much higher above.

For the 2638th anniversary a model of the tower will be rebuilt. _n_ different types of blocks are available. Each one of them may be duplicated as many times as you like. Each type has a height _y_, a width _x_ and a depth _z_. The blocks are to be stacked one upon eachother so that the resulting tower is as high as possible. Of course the blocks can be rotated as desired before stacking. However for reasons of stability a block can only be stacked upon another if _both_ of its baselines are shorter.

## 输入格式

The number of types of blocks _n_ is located in the first line of each test case. On the subsequent _n_ lines the height _y $ _{i} $_ , the width _x $ _{i} $_  and the depth _z $ _{i} $_  of each type of blocks are given. There are never more than 30 different types available.

There are many test cases, which come one by one. Input terminates with n = 0.

**Edited:** You can assume that max(_x $ _{i} $_ , _y $ _{i} $_ , _z $ _{i} $_ ) <= 2500.

## 输出格式

For each test case your program should output one line with the height of the highest possible tower.

## 样例 #1

### 输入

```
5
31 41 59
26 53 58
97 93 23
84 62 64
33 83 27
1
1 1 1
0
```

### 输出

```
342
1
```

