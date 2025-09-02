---
title: "The Meeting Place Cannot Be Changed"
layout: "post"
diff: 普及/提高-
pid: CF780B
tag: []
---

# The Meeting Place Cannot Be Changed

## 题目描述

The main road in Bytecity is a straight line from south to north. Conveniently, there are coordinates measured in meters from the southernmost building in north direction.

At some points on the road there are $ n $ friends, and $ i $ -th of them is standing at the point $ x_{i} $ meters and can move with any speed no greater than $ v_{i} $ meters per second in any of the two directions along the road: south or north.

You are to compute the minimum time needed to gather all the $ n $ friends at some point on the road. Note that the point they meet at doesn't need to have integer coordinate.

## 输入格式

The first line contains single integer $ n $ ( $ 2<=n<=60000 $ ) — the number of friends.

The second line contains $ n $ integers $ x_{1},x_{2},...,x_{n} $ ( $ 1<=x_{i}<=10^{9} $ ) — the current coordinates of the friends, in meters.

The third line contains $ n $ integers $ v_{1},v_{2},...,v_{n} $ ( $ 1<=v_{i}<=10^{9} $ ) — the maximum speeds of the friends, in meters per second.

## 输出格式

Print the minimum time (in seconds) needed for all the $ n $ friends to meet at some point on the road.

Your answer will be considered correct, if its absolute or relative error isn't greater than $ 10^{-6} $ . Formally, let your answer be $ a $ , while jury's answer be $ b $ . Your answer will be considered correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF780B/ae5849bac53685f0bc780c0a433a39d53ab83a23.png) holds.

## 说明/提示

In the first sample, all friends can gather at the point $ 5 $ within $ 2 $ seconds. In order to achieve this, the first friend should go south all the time at his maximum speed, while the second and the third friends should go north at their maximum speeds.

## 样例 #1

### 输入

```
3
7 1 3
1 2 1

```

### 输出

```
2.000000000000

```

## 样例 #2

### 输入

```
4
5 10 3 2
2 3 2 4

```

### 输出

```
1.400000000000

```

