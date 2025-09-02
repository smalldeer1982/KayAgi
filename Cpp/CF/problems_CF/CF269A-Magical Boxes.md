---
title: "Magical Boxes"
layout: "post"
diff: 普及/提高-
pid: CF269A
tag: []
---

# Magical Boxes

## 题目描述

Emuskald is a well-known illusionist. One of his trademark tricks involves a set of magical boxes. The essence of the trick is in packing the boxes inside other boxes.

From the top view each magical box looks like a square with side length equal to $ 2^{k} $ ( $ k $ is an integer, $ k>=0 $ ) units. A magical box $ v $ can be put inside a magical box $ u $ , if side length of $ v $ is strictly less than the side length of $ u $ . In particular, Emuskald can put 4 boxes of side length $ 2^{k-1} $ into one box of side length $ 2^{k} $ , or as in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269A/80c511ed150137d08b669bf5e500bfa82c8a8fe8.png)Emuskald is about to go on tour performing around the world, and needs to pack his magical boxes for the trip. He has decided that the best way to pack them would be inside another magical box, but magical boxes are quite expensive to make. Help him find the smallest magical box that can fit all his boxes.

## 输入格式

The first line of input contains an integer $ n $ ( $ 1<=n<=10^{5} $ ), the number of different sizes of boxes Emuskald has. Each of following $ n $ lines contains two integers $ k_{i} $ and $ a_{i} $ ( $ 0<=k_{i}<=10^{9} $ , $ 1<=a_{i}<=10^{9} $ ), which means that Emuskald has $ a_{i} $ boxes with side length $ 2^{k_{i}} $ . It is guaranteed that all of $ k_{i} $ are distinct.

## 输出格式

Output a single integer $ p $ , such that the smallest magical box that can contain all of Emuskald’s boxes has side length $ 2^{p} $ .

## 说明/提示

Picture explanation. If we have 3 boxes with side length 2 and 5 boxes with side length 1, then we can put all these boxes inside a box with side length 4, for example, as shown in the picture.

In the second test case, we can put all four small boxes into a box with side length 2.

## 样例 #1

### 输入

```
2
0 3
1 5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
1
0 4

```

### 输出

```
1

```

## 样例 #3

### 输入

```
2
1 10
2 2

```

### 输出

```
3

```

