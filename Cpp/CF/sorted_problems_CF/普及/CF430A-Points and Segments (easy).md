---
title: "Points and Segments (easy)"
layout: "post"
diff: 普及/提高-
pid: CF430A
tag: []
---

# Points and Segments (easy)

## 题目描述

Iahub isn't well prepared on geometry problems, but he heard that this year there will be a lot of geometry problems on the IOI selection camp. Scared, Iahub locked himself in the basement and started thinking of new problems of this kind. One of them is the following.

Iahub wants to draw $ n $ distinct points and $ m $ segments on the $ OX $ axis. He can draw each point with either red or blue. The drawing is good if and only if the following requirement is met: for each segment $ [l_{i},r_{i}] $ consider all the red points belong to it ( $ r_{i} $ points), and all the blue points belong to it ( $ b_{i} $ points); each segment $ i $ should satisfy the inequality $ |r_{i}-b_{i}|<=1 $ .

Iahub thinks that point $ x $ belongs to segment $ [l,r] $ , if inequality $ l<=x<=r $ holds.

Iahub gives to you all coordinates of points and segments. Please, help him to find any good drawing.

## 输入格式

The first line of input contains two integers: $ n $ ( $ 1<=n<=100 $ ) and $ m $ ( $ 1<=m<=100 $ ). The next line contains $ n $ space-separated integers $ x_{1},x_{2},...,x_{n} $ ( $ 0<=x_{i}<=100 $ ) — the coordinates of the points. The following $ m $ lines contain the descriptions of the $ m $ segments. Each line contains two integers $ l_{i} $ and $ r_{i} $ ( $ 0<=l_{i}<=r_{i}<=100 $ ) — the borders of the $ i $ -th segment.

It's guaranteed that all the points are distinct.

## 输出格式

If there is no good drawing for a given test, output a single integer -1. Otherwise output $ n $ integers, each integer must be 0 or 1. The $ i $ -th number denotes the color of the $ i $ -th point (0 is red, and 1 is blue).

If there are multiple good drawings you can output any of them.

## 样例 #1

### 输入

```
3 3
3 7 14
1 5
6 10
11 15

```

### 输出

```
0 0 0
```

## 样例 #2

### 输入

```
3 4
1 2 3
1 2
2 3
5 6
2 2

```

### 输出

```
1 0 1 
```

