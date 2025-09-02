---
title: "Triangle"
layout: "post"
diff: 普及+/提高
pid: CF407A
tag: []
---

# Triangle

## 题目描述

There is a right triangle with legs of length $ a $ and $ b $ . Your task is to determine whether it is possible to locate the triangle on the plane in such a way that none of its sides is parallel to the coordinate axes. All the vertices must have integer coordinates. If there exists such a location, you have to output the appropriate coordinates of vertices.

## 输入格式

The first line contains two integers $ a,b $ ( $ 1<=a,b<=1000 $ ), separated by a single space.

## 输出格式

In the first line print either "YES" or "NO" (without the quotes) depending on whether the required location exists. If it does, print in the next three lines three pairs of integers — the coordinates of the triangle vertices, one pair per line. The coordinates must be integers, not exceeding $ 10^{9} $ in their absolute value.

## 样例 #1

### 输入

```
1 1

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
5 5

```

### 输出

```
YES
2 1
5 5
-2 4

```

## 样例 #3

### 输入

```
5 10

```

### 输出

```
YES
-10 4
-2 -2
1 2

```

