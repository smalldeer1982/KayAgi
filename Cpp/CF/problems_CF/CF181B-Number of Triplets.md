---
title: "Number of Triplets"
layout: "post"
diff: 普及/提高-
pid: CF181B
tag: []
---

# Number of Triplets

## 题目描述

You are given $ n $ points on a plane. All points are different.

Find the number of different groups of three points $ (A,B,C) $ such that point $ B $ is the middle of segment $ AC $ .

The groups of three points are considered unordered, that is, if point $ B $ is the middle of segment $ AC $ , then groups $ (A,B,C) $ and $ (C,B,A) $ are considered the same.

## 输入格式

The first line contains a single integer $ n $ ( $ 3<=n<=3000 $ ) — the number of points.

Next $ n $ lines contain the points. The $ i $ -th line contains coordinates of the $ i $ -th point: two space-separated integers $ x_{i},y_{i} $ ( $ -1000<=x_{i},y_{i}<=1000 $ ).

It is guaranteed that all given points are different.

## 输出格式

Print the single number — the answer to the problem.

## 样例 #1

### 输入

```
3
1 1
2 2
3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
0 0
-1 0
0 1

```

### 输出

```
0

```

