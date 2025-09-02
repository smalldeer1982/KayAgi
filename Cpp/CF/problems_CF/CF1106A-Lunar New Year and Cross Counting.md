---
title: "Lunar New Year and Cross Counting"
layout: "post"
diff: 普及-
pid: CF1106A
tag: []
---

# Lunar New Year and Cross Counting

## 题目描述

在一个 $n \times n$ 的地图中寻找有几个图案，满足

$M(i,j)=M(i-1,j-1)=M(i-1,j+1)=M(i+1,j-1)=M(i+1,j+1)=X$

形似下图。
```
X.X
.X.
X.X
```
如果图案中心所在位置不同即视作不同。

## 输入格式

第一行正整数 $n (1 \le n \le 500)$，表示地图的大小。
接下来 $n$ 行每行 $n$ 个字符，只包含 **'X' 或 '.'**。

## 输出格式

一行一个整数 $k$ 表示图案个数。

## 样例 #1

### 输入

```
5
.....
.XXX.
.XXX.
.XXX.
.....

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
XX
XX

```

### 输出

```
0

```

## 样例 #3

### 输入

```
6
......
X.X.X.
.X.X.X
X.X.X.
.X.X.X
......

```

### 输出

```
4

```

