---
title: "Chladni Figure"
layout: "post"
diff: 普及+/提高
pid: CF1147B
tag: []
---

# Chladni Figure

## 题目描述

Inaka has a disc, the circumference of which is $ n $ units. The circumference is equally divided by $ n $ points numbered clockwise from $ 1 $ to $ n $ , such that points $ i $ and $ i + 1 $ ( $ 1 \leq i < n $ ) are adjacent, and so are points $ n $ and $ 1 $ .

There are $ m $ straight segments on the disc, the endpoints of which are all among the aforementioned $ n $ points.

Inaka wants to know if her image is rotationally symmetrical, i.e. if there is an integer $ k $ ( $ 1 \leq k < n $ ), such that if all segments are rotated clockwise around the center of the circle by $ k $ units, the new image will be the same as the original one.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ( $ 2 \leq n \leq 100\,000 $ , $ 1 \leq m \leq 200\,000 $ ) — the number of points and the number of segments, respectively.

The $ i $ -th of the following $ m $ lines contains two space-separated integers $ a_i $ and $ b_i $ ( $ 1 \leq a_i, b_i \leq n $ , $ a_i \neq b_i $ ) that describe a segment connecting points $ a_i $ and $ b_i $ .

It is guaranteed that no segments coincide.

## 输出格式

Output one line — "Yes" if the image is rotationally symmetrical, and "No" otherwise (both excluding quotation marks).

You can output each letter in any case (upper or lower).

## 说明/提示

The first two examples are illustrated below. Both images become the same as their respective original ones after a clockwise rotation of $ 120 $ degrees around the center.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1147B/e97ded58f64e835700251efbf078bd03afdc1691.png)

## 样例 #1

### 输入

```
12 6
1 3
3 7
5 7
7 11
9 11
11 3

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
9 6
4 5
5 6
7 8
8 9
1 2
2 3

```

### 输出

```
Yes

```

## 样例 #3

### 输入

```
10 3
1 2
3 2
7 2

```

### 输出

```
No

```

## 样例 #4

### 输入

```
10 2
1 6
2 7

```

### 输出

```
Yes

```

