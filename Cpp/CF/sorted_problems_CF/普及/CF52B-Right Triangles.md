---
title: "Right Triangles"
layout: "post"
diff: 普及/提高-
pid: CF52B
tag: []
---

# Right Triangles

## 题目描述

You are given a $ n×m $ field consisting only of periods ('.') and asterisks ('\*'). Your task is to count all right triangles with two sides parallel to the square sides, whose vertices are in the centers of '\*'-cells. A right triangle is a triangle in which one angle is a right angle (that is, a 90 degree angle).

## 输入格式

The first line contains two positive integer numbers $ n $ and $ m $ ( $ 1<=n,m<=1000 $ ). The following $ n $ lines consist of $ m $ characters each, describing the field. Only '.' and '\*' are allowed.

## 输出格式

Output a single number — total number of square triangles in the field. Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cout (also you may use %I64d).

## 样例 #1

### 输入

```
2 2
**
*.

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 4
*..*
.**.
*.**

```

### 输出

```
9

```

