---
title: "The Child and Polygon"
layout: "post"
diff: 省选/NOI-
pid: CF437E
tag: []
---

# The Child and Polygon

## 题目描述

This time our child has a simple polygon. He has to find the number of ways to split the polygon into non-degenerate triangles, each way must satisfy the following requirements:

- each vertex of each triangle is one of the polygon vertex;
- each side of the polygon must be the side of exactly one triangle;
- the area of intersection of every two triangles equals to zero, and the sum of all areas of triangles equals to the area of the polygon;
- each triangle must be completely inside the polygon;
- each side of each triangle must contain exactly two vertices of the polygon.

The picture below depicts an example of a correct splitting.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437E/a8e2701cc66365983a77c546adbf6d2315ebb4eb.png)Please, help the child. Calculate the described number of ways modulo $ 1000000007 $ $ (10^{9}+7) $ for him.

## 输入格式

The first line contains one integer $ n $ $ (3<=n<=200) $ — the number of vertices of the polygon. Then follow $ n $ lines, each line containing two integers. The $ i $ -th line contains $ x_{i},y_{i} $ $ (|x_{i}|,|y_{i}|<=10^{7}) $ — the $ i $ -th vertex of the polygon in clockwise or counterclockwise order.

It's guaranteed that the polygon is simple.

## 输出格式

Output the number of ways modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample, there are two possible splittings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437E/02e2009a70acb17a1ce2cf1ec7df448a4afdd92f.png)In the second sample, there are only one possible splitting:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437E/2a38e13bdc3c393812a8729aaf5a7d6b365647bf.png)

## 样例 #1

### 输入

```
4
0 0
0 1
1 1
1 0

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4
0 0
1 0
0 1
-1 0

```

### 输出

```
1

```

## 样例 #3

### 输入

```
5
0 0
1 0
1 1
0 1
-2 -1

```

### 输出

```
3

```

