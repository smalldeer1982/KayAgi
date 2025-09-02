---
title: "Segments"
layout: "post"
diff: 普及/提高-
pid: CF909B
tag: []
---

# Segments

## 题目描述

You are given an integer $ N $ . Consider all possible segments on the coordinate axis with endpoints at integer points with coordinates between 0 and $ N $ , inclusive; there will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF909B/150441d31156a32e0b2da63844d600138a543898.png) of them.

You want to draw these segments in several layers so that in each layer the segments don't overlap (they might touch at the endpoints though). You can not move the segments to a different location on the coordinate axis.

Find the minimal number of layers you have to use for the given $ N $ .

## 输入格式

The only input line contains a single integer $ N $ ( $ 1<=N<=100 $ ).

## 输出格式

Output a single integer - the minimal number of layers required to draw the segments for the given $ N $ .

## 说明/提示

As an example, here are the segments and their optimal arrangement into layers for $ N=4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF909B/d28bd213a6c0995aff826b2bebd914bef9ec9fa5.png)

## 样例 #1

### 输入

```
2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3

```

### 输出

```
4

```

## 样例 #3

### 输入

```
4

```

### 输出

```
6

```

