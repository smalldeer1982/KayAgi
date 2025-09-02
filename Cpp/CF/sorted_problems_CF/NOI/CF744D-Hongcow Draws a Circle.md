---
title: "Hongcow Draws a Circle"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF744D
tag: []
---

# Hongcow Draws a Circle

## 题目描述

Hongcow really likes the color red. Hongcow doesn't like the color blue.

Hongcow is standing in an infinite field where there are $ n $ red points and $ m $ blue points.

Hongcow wants to draw a circle in the field such that this circle contains at least one red point, and no blue points. Points that line exactly on the boundary of the circle can be counted as either inside or outside.

Compute the radius of the largest circle that satisfies this condition. If this circle can have arbitrarily large size, print $ -1 $ . Otherwise, your answer will be accepted if it has relative or absolute error at most $ 10^{-4} $ .

## 输入格式

The first line of the input will contain two integers $ n,m $ ( $ 1<=n,m<=1,000 $ ).

The next $ n $ lines will contain two integers $ x_{i},y_{i} $ ( $ 1<=x_{i},y_{i}<=10^{4} $ ). This denotes the coordinates of a red point.

The next $ m $ lines will contain two integers $ x_{i},y_{i} $ ( $ 1<=x_{i},y_{i}<=10^{4} $ ). This denotes the coordinates of a blue point.

No two points will have the same coordinates.

## 输出格式

Print $ -1 $ if the circle can have arbitrary size. Otherwise, print a floating point number representing the largest radius circle that satisfies the conditions. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-4} $ .

Namely, let's assume that your answer is $ a $ and the answer of the jury is $ b $ . The checker program will consider your answer correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF744D/52c84cb27b50fce8b08f35fa39c1f083ebd1a014.png).

## 说明/提示

This is a picture of the first sample

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF744D/50e8da306fe47947cfeb784650b3d6b2ea876ead.png)This is a picture of the second sample

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF744D/a1b03125c876722297007ba9fc107d7fb9df9570.png)

## 样例 #1

### 输入

```
2 5
2 3
3 4
1 1
1 4
4 2
4 7
2 5

```

### 输出

```
3.5355338827

```

## 样例 #2

### 输入

```
1 6
3 3
1 5
5 4
2 1
3 4
4 2
1 3

```

### 输出

```
1.5811388195

```

## 样例 #3

### 输入

```
2 2
2 2
3 3
1 1
4 4

```

### 输出

```
-1

```

