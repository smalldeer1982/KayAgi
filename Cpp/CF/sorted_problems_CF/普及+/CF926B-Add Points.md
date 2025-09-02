---
title: "Add Points"
layout: "post"
diff: 普及+/提高
pid: CF926B
tag: []
---

# Add Points

## 题目描述

There are $ n $ points on a straight line, and the $ i $ -th point among them is located at $ x_{i} $ . All these coordinates are distinct.

Determine the number $ m $ — the smallest number of points you should add on the line to make the distances between all neighboring points equal.

## 输入格式

The first line contains a single integer $ n $ ( $ 3<=n<=100000 $ ) — the number of points.

The second line contains a sequence of integers $ x_{1},x_{2},...,x_{n} $ ( $ -10^{9}<=x_{i}<=10^{9} $ ) — the coordinates of the points. All these coordinates are distinct. The points can be given in an arbitrary order.

## 输出格式

Print a single integer $ m $ — the smallest number of points you should add on the line to make the distances between all neighboring points equal.

## 说明/提示

In the first example you can add one point with coordinate $ 0 $ .

In the second example the distances between all neighboring points are already equal, so you shouldn't add anything.

## 样例 #1

### 输入

```
3
-5 10 5

```

### 输出

```
1

```

## 样例 #2

### 输入

```
6
100 200 400 300 600 500

```

### 输出

```
0

```

## 样例 #3

### 输入

```
4
10 9 0 -1

```

### 输出

```
8

```

