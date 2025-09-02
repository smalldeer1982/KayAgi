---
title: "Point on Spiral"
layout: "post"
diff: 普及-
pid: CF279A
tag: []
---

# Point on Spiral

## 题目描述

Valera the horse lives on a plane. The Cartesian coordinate system is defined on this plane. Also an infinite spiral is painted on the plane. The spiral consists of segments:  $ [(0,0),(1,0)] $ , $ [(1,0),(1,1)] $ , $ [(1,1),(-1,1)] $ , $ [(-1,1),(-1,-1)] $ , $ [(-1,-1),(2,-1)] $ , $ [(2,-1),(2,2)] $  and so on. Thus, this infinite spiral passes through each integer point of the plane.

Valera the horse lives on the plane at coordinates $ (0,0) $ . He wants to walk along the spiral to point $ (x,y) $ . Valera the horse has four legs, so he finds turning very difficult. Count how many times he will have to turn if he goes along a spiral from point $ (0,0) $ to point $ (x,y) $ .

## 输入格式

The first line contains two space-separated integers $ x $ and $ y $ $ (|x|,|y|<=100) $ .

## 输出格式

Print a single integer, showing how many times Valera has to turn.

## 样例 #1

### 输入

```
0 0

```

### 输出

```
0

```

## 样例 #2

### 输入

```
1 0

```

### 输出

```
0

```

## 样例 #3

### 输入

```
0 1

```

### 输出

```
2

```

## 样例 #4

### 输入

```
-1 -1

```

### 输出

```
3

```

