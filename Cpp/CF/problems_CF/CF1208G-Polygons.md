---
title: "Polygons"
layout: "post"
diff: 省选/NOI-
pid: CF1208G
tag: []
---

# Polygons

## 题目描述

You are given two integers $ n $ and $ k $ .

You need to construct $ k $ regular polygons having same [circumcircle](https://en.wikipedia.org/wiki/Circumscribed_circle), with distinct number of sides $ l $ between $ 3 $ and $ n $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1208G/95991da251ccd37f8f076c85876463789e724ae5.png)Illustration for the first example.You can rotate them to minimize the total number of distinct points on the circle. Find the minimum number of such points.

## 输入格式

The only line of input contains two integers $ n $ and $ k $ ( $ 3 \le n \le 10^{6} $ , $ 1 \le k \le n-2 $ ), the maximum number of sides of a polygon and the number of polygons to construct, respectively.

## 输出格式

Print a single integer — the minimum number of points required for $ k $ polygons.

## 说明/提示

In the first example, we have $ n = 6 $ and $ k = 2 $ . So, we have $ 4 $ polygons with number of sides $ 3 $ , $ 4 $ , $ 5 $ and $ 6 $ to choose from and if we choose the triangle and the hexagon, then we can arrange them as shown in the picture in the statement.

Hence, the minimum number of points required on the circle is $ 6 $ , which is also the minimum overall possible sets.

## 样例 #1

### 输入

```
6 2

```

### 输出

```
6

```

## 样例 #2

### 输入

```
200 50

```

### 输出

```
708

```

