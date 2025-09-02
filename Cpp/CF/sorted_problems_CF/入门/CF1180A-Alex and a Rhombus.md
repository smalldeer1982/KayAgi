---
title: "Alex and a Rhombus"
layout: "post"
diff: 入门
pid: CF1180A
tag: []
---

# Alex and a Rhombus

## 题目描述

While playing with geometric figures Alex has accidentally invented a concept of a  $ n $ -th order rhombus in a cell grid.

A $ 1 $ -st order rhombus is just a square $ 1 \times 1 $ (i.e just a cell).

A $ n $ -th order rhombus for all $ n \geq 2 $ one obtains from a  $ n-1 $ -th order rhombus adding all cells which have a common side with it to it (look at the picture to understand it better).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1180A/ccf29660dcd8bd16597fff06e6153caa2bd347a9.png)Alex asks you to compute the number of cells in a  $ n $ -th order rhombus.

## 输入格式

The first and only input line contains integer $ n $ ( $ 1 \leq n \leq 100 $ ) — order of a rhombus whose numbers of cells should be computed.

## 输出格式

Print exactly one integer — the number of cells in a  $ n $ -th order rhombus.

## 说明/提示

Images of rhombus corresponding to the examples are given in the statement.

## 样例 #1

### 输入

```
1

```

### 输出

```
1
```

## 样例 #2

### 输入

```
2

```

### 输出

```
5
```

## 样例 #3

### 输入

```
3

```

### 输出

```
13
```

