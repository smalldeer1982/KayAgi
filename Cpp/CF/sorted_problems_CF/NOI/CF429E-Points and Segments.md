---
title: "Points and Segments"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF429E
tag: ['图论', '离散化', '二分图']
---

# Points and Segments

## 题目描述

Iahub isn't well prepared on geometry problems, but he heard that this year there will be a lot of geometry problems on the IOI selection camp. Scared, Iahub locked himself in the basement and started thinking of new problems of this kind. One of them is the following.

Iahub wants to draw $ n $ distinct segments $ [l_{i},r_{i}] $ on the $ OX $ axis. He can draw each segment with either red or blue. The drawing is good if and only if the following requirement is met: for each point $ x $ of the $ OX $ axis consider all the segments that contains point $ x $ ; suppose, that $ r_{x} $ red segments and $ b_{x} $ blue segments contain point $ x $ ; for each point $ x $ inequality $ |r_{x}-b_{x}|<=1 $ must be satisfied.

A segment $ [l,r] $ contains a point $ x $ if and only if $ l<=x<=r $ .

Iahub gives you the starting and ending points of all the segments. You have to find any good drawing for him.

## 输入格式

The first line of input contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of segments. The $ i $ -th of the next $ n $ lines contains two integers $ l_{i} $ and $ r_{i} $ ( $ 0<=l_{i}<=r_{i}<=10^{9} $ ) — the borders of the $ i $ -th segment.

It's guaranteed that all the segments are distinct.

## 输出格式

If there is no good drawing for a given test, output a single integer -1. Otherwise output $ n $ integers; each integer must be 0 or 1. The $ i $ -th number denotes the color of the $ i $ -th segment (0 is red and 1 is blue).

If there are multiple good drawings you can output any of them.

## 样例 #1

### 输入

```
2
0 2
2 3

```

### 输出

```
0 1

```

## 样例 #2

### 输入

```
6
1 5
1 3
3 5
2 10
11 11
12 12

```

### 输出

```
0 1 0 1 0 0

```

