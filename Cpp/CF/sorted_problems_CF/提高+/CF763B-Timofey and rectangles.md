---
title: "Timofey and rectangles"
layout: "post"
diff: 提高+/省选-
pid: CF763B
tag: []
---

# Timofey and rectangles

## 题目描述

One of Timofey's birthday presents is a colourbook in a shape of an infinite plane. On the plane $ n $ rectangles with sides parallel to coordinate axes are situated. All sides of the rectangles have odd length. Rectangles cannot intersect, but they can touch each other.

Help Timofey to color his rectangles in $ 4 $ different colors in such a way that every two rectangles touching each other by side would have different color, or determine that it is impossible.

Two rectangles intersect if their intersection has positive area. Two rectangles touch by sides if there is a pair of sides such that their intersection has non-zero length

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF763B/1e56315d730703e37fe416b7a434283dfefe0bca.png)The picture corresponds to the first example

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=5·10^{5} $ ) — the number of rectangles.

 $ n $ lines follow. The $ i $ -th of these lines contains four integers $ x_{1} $ , $ y_{1} $ , $ x_{2} $ and $ y_{2} $ ( $ -10^{9}<=x_{1}&lt;x_{2}<=10^{9} $ , $ -10^{9}<=y_{1}&lt;y_{2}<=10^{9} $ ), that means that points $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ are the coordinates of two opposite corners of the $ i $ -th rectangle.

It is guaranteed, that all sides of the rectangles have odd lengths and rectangles don't intersect each other.

## 输出格式

Print "NO" in the only line if it is impossible to color the rectangles in $ 4 $ different colors in such a way that every two rectangles touching each other by side would have different color.

Otherwise, print "YES" in the first line. Then print $ n $ lines, in the $ i $ -th of them print single integer $ c_{i} $ ( $ 1<=c_{i}<=4 $ ) — the color of $ i $ -th rectangle.

## 样例 #1

### 输入

```
8
0 0 5 3
2 -1 5 0
-3 -4 2 -1
-1 -1 2 0
-3 0 0 5
5 2 10 3
7 -3 10 2
4 -2 7 -1

```

### 输出

```
YES
1
2
2
3
2
2
4
1

```

