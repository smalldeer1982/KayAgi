---
title: "Rectangle Painting 1"
layout: "post"
diff: 提高+/省选-
pid: CF1198D
tag: []
---

# Rectangle Painting 1

## 题目描述

There is a square grid of size $ n \times n $ . Some cells are colored in black, all others are colored in white. In one operation you can select some rectangle and color all its cells in white. It costs $ \max(h, w) $ to color a rectangle of size $ h \times w $ . You are to make all cells white for minimum total cost.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 50 $ ) — the size of the square grid.

Each of the next $ n $ lines contains a string of length $ n $ , consisting of characters '.' and '\#'. The $ j $ -th character of the $ i $ -th line is '\#' if the cell with coordinates $ (i, j) $ is black, otherwise it is white.

## 输出格式

Print a single integer — the minimum total cost to paint all cells in white.

## 说明/提示

The examples and some of optimal solutions are shown on the pictures below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1198D/cb07e2ee21adbb1a45d78db7b060446e335ba3ff.png)

## 样例 #1

### 输入

```
3
###
#.#
###

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
...
...
...

```

### 输出

```
0

```

## 样例 #3

### 输入

```
4
#...
....
....
#...

```

### 输出

```
2

```

## 样例 #4

### 输入

```
5
#...#
.#.#.
.....
.#...
#....

```

### 输出

```
5

```

