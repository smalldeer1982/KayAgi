---
title: "Vanya and Triangles"
layout: "post"
diff: 普及+/提高
pid: CF552D
tag: []
---

# Vanya and Triangles

## 题目描述

Vanya got bored and he painted $ n $ distinct points on the plane. After that he connected all the points pairwise and saw that as a result many triangles were formed with vertices in the painted points. He asks you to count the number of the formed triangles with the non-zero area.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=2000 $ ) — the number of the points painted on the plane.

Next $ n $ lines contain two integers each $ x_{i},y_{i} $ ( $ -100<=x_{i},y_{i}<=100 $ ) — the coordinates of the $ i $ -th point. It is guaranteed that no two given points coincide.

## 输出格式

In the first line print an integer — the number of triangles with the non-zero area among the painted points.

## 说明/提示

Note to the first sample test. There are $ 3 $ triangles formed: $ (0,0)-(1,1)-(2,0) $ ; $ (0,0)-(2,2)-(2,0) $ ; $ (1,1)-(2,2)-(2,0) $ .

Note to the second sample test. There is $ 1 $ triangle formed: $ (0,0)-(1,1)-(2,0) $ .

Note to the third sample test. A single point doesn't form a single triangle.

## 样例 #1

### 输入

```
4
0 0
1 1
2 0
2 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
0 0
1 1
2 0

```

### 输出

```
1

```

## 样例 #3

### 输入

```
1
1 1

```

### 输出

```
0

```

