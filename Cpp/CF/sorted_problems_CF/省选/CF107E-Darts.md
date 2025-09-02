---
title: "Darts"
layout: "post"
diff: 省选/NOI-
pid: CF107E
tag: []
---

# Darts

## 题目描述

The night after the graduation ceremony graduate students of German University in Cairo (GUC) are playing darts. As there's no real dart board available, the photographs of members of the GUC upper management are being used.

So, $ n $ rectangular photos are placed on the wall. They can overlap arbitrary and even coincide. The photos are not necessarily placed horizontally or vertically, they could also be rotated before being pinned to the wall.

The score of one dart throw is simply the number of photos the dart went through.

Fatma has made a throw but her score was not recorded. She only remembers that she did make it into at least one photo.

Assuming that the probability distribution of the throw is equal across the whole wall, what would be the expectation of Fatma's score?

## 输入格式

The first line of input contains integer $ n $ ( $ 1<=n<=500 $ ) — the number of photos on the wall. Then follow $ n $ lines describing the photos, each containing $ 8 $ single-space-separated integers (coordinates of $ 4 $ vertices): $ x_{1} $ , $ y_{1} $ , $ x_{2} $ , $ y_{2} $ , $ x_{3} $ , $ y_{3} $ , $ x_{4} $ , $ y_{4} $ . Each photo is a rectangle with a nonzero area. The coordinates are integers, not exceeding $ 10^{4} $ by absolute value. The coordinates of the rectangle are given in either clockwise or counterclockwise order.

## 输出格式

Print the expected score of the throw. The answer will be accepted if it has absolute or relative error not exceeding $ 10^{-6} $ .

## 样例 #1

### 输入

```
1
0 0 0 2 2 2 2 0

```

### 输出

```
1.0000000000

```

## 样例 #2

### 输入

```
1
-1 0 0 1 1 0 0 -1

```

### 输出

```
1.0000000000

```

## 样例 #3

### 输入

```
4
0 0 0 1 3 1 3 0
0 0 0 3 1 3 1 0
3 3 2 3 2 0 3 0
3 3 3 2 0 2 0 3

```

### 输出

```
1.5000000000

```

## 样例 #4

### 输入

```
2
-1 0 0 1 1 0 0 -1
0 0 1 1 2 0 1 -1

```

### 输出

```
1.1428571429

```

