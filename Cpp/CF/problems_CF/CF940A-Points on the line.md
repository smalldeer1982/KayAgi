---
title: "Points on the line"
layout: "post"
diff: 普及-
pid: CF940A
tag: ['枚举']
---

# Points on the line

## 题目描述

We've got no test cases. A big olympiad is coming up. But the problemsetters' number one priority should be adding another problem to the round.

The diameter of a multiset of points on the line is the largest distance between two points from this set. For example, the diameter of the multiset $ {1,3,2,1} $ is 2.

Diameter of multiset consisting of one point is 0.

You are given $ n $ points on the line. What is the minimum number of points you have to remove, so that the diameter of the multiset of the remaining points will not exceed $ d $ ?

## 输入格式

The first line contains two integers $ n $ and $ d $ ( $ 1<=n<=100,0<=d<=100 $ ) — the amount of points and the maximum allowed diameter respectively.

The second line contains $ n $ space separated integers ( $ 1<=x_{i}<=100 $ ) — the coordinates of the points.

## 输出格式

Output a single integer — the minimum number of points you have to remove.

## 说明/提示

In the first test case the optimal strategy is to remove the point with coordinate $ 4 $ . The remaining points will have coordinates $ 1 $ and $ 2 $ , so the diameter will be equal to $ 2-1=1 $ .

In the second test case the diameter is equal to $ 0 $ , so its is unnecessary to remove any points.

In the third test case the optimal strategy is to remove points with coordinates $ 1 $ , $ 9 $ and $ 10 $ . The remaining points will have coordinates $ 3 $ , $ 4 $ and $ 6 $ , so the diameter will be equal to $ 6-3=3 $ .

## 样例 #1

### 输入

```
3 1
2 1 4

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 0
7 7 7

```

### 输出

```
0

```

## 样例 #3

### 输入

```
6 3
1 3 4 6 9 10

```

### 输出

```
3

```

