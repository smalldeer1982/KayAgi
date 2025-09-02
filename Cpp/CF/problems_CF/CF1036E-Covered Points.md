---
title: "Covered Points"
layout: "post"
diff: 省选/NOI-
pid: CF1036E
tag: ['概率论']
---

# Covered Points

## 题目描述

You are given $ n $ segments on a Cartesian plane. Each segment's endpoints have integer coordinates. Segments can intersect with each other. No two segments lie on the same line.

Count the number of distinct points with integer coordinates, which are covered by at least one segment.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 1000 $ ) — the number of segments.

Each of the next $ n $ lines contains four integers $ Ax_i, Ay_i, Bx_i, By_i $ ( $ -10^6 \le Ax_i, Ay_i, Bx_i, By_i \le 10^6 $ ) — the coordinates of the endpoints $ A $ , $ B $ ( $ A \ne B $ ) of the $ i $ -th segment.

It is guaranteed that no two segments lie on the same line.

## 输出格式

Print a single integer — the number of distinct points with integer coordinates, which are covered by at least one segment.

## 说明/提示

The image for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1036E/328bc786470ca0c6c881c66bf4ab063a98d10f53.png)Several key points are marked blue, the answer contains some non-marked points as well.

The image for the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1036E/eec87126bd479256c1ebc7932fb835380371e1c1.png)

## 样例 #1

### 输入

```
9
0 0 4 4
-1 5 4 0
4 0 4 4
5 2 11 2
6 1 6 7
5 6 11 6
10 1 10 7
7 0 9 8
10 -1 11 -1

```

### 输出

```
42

```

## 样例 #2

### 输入

```
4
-1 2 1 2
-1 0 1 0
-1 0 0 3
0 3 1 0

```

### 输出

```
7

```

