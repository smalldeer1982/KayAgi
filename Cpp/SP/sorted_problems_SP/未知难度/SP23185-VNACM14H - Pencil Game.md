---
title: "VNACM14H - Pencil Game"
layout: "post"
diff: 难度0
pid: SP23185
tag: []
---

# VNACM14H - Pencil Game

## 题目描述

Â Â Minh has a box of pencils. The box is a rectangle of size M Ă&#151;N, where position (i, j) has a pencil Â with a length of exactly i Ă&#151; N + j (0 â&#137;¤ i â&#137;¤ M-1, 0 â&#137;¤ j â&#137;¤ N-1). Note that position (0, 0) does not have any pencil hence having a length of 0.

Â Â He wonders if he could select a sub-rectangle of the box and join all the pencils within that sub-rectangle together, to get a new long pencil that has a specific length L that he wants.

Â Â Your task is to find a sub-rectangle of the box in which the total length of the contained pencils is L and return the area of that the sub-rectangle. If there are multiple solutions, return the smallest Â possible area. If thereâ&#128;&#153;s no such sub-rectangle, return -1.

Minh has a box of pencils. The box is a rectangle of size M Ă&#151;N, where position (i, j) has a pencilÂ

## 输入格式

The input file consists of several datasets. The first line of the input file contains the number of

datasets which is a positive integer and is not greater than 150. The following lines describe theÂ

datasets.

Â Â Each dataset contains three space-separated numbers M, N and L (1 â&#137;¤ M, N â&#137;¤ 10^6,Â 1 â&#137;¤ L â&#137;¤ 10^12) written in one line.

## 输出格式

Â Â For each dataset, write in one line the smallest possible area of the sub-rectangle in which the total sum of pencil lengths is L. Write in one line -1 if there is no such sub-rectangle.

## 样例 #1

### 输入

```
2
2 3 8
2 2 7
```

### 输出

```
4
-1
```

