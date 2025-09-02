---
title: "Manhattan Triangle"
layout: "post"
diff: 提高+/省选-
pid: CF1979E
tag: []
---

# Manhattan Triangle

## 题目描述

The Manhattan distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is defined as: $ $$$|x_1 - x_2| + |y_1 - y_2|. $ $ </p><p>We call a <span class="tex-font-style-it">Manhattan triangle</span> three points on the plane, the Manhattan distances between each pair of which are equal.</p><p>You are given a set of pairwise distinct points and an <span class="tex-font-style-bf">even</span> integer  $ d $ . Your task is to find any Manhattan triangle, composed of three distinct points from the given set, where the Manhattan distance between any pair of vertices is equal to  $ d$$$.

## 输入格式

Each test consists of multiple test cases. The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ d $ ( $ 3 \le n \le 2 \cdot 10^5 $ , $ 2 \le d \le 4 \cdot 10^5 $ , $ d $ is even) — the number of points and the required Manhattan distance between the vertices of the triangle.

The $ (i + 1) $ -th line of each test case contains two integers $ x_i $ and $ y_i $ ( $ -10^5 \le x_i, y_i \le 10^5 $ ) — the coordinates of the $ i $ -th point. It is guaranteed that all points are pairwise distinct.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output three distinct integers $ i $ , $ j $ , and $ k $ ( $ 1 \le i,j,k \le n $ ) — the indices of the points forming the Manhattan triangle. If there is no solution, output " $ 0\ 0\ 0 $ " (without quotes).

If there are multiple solutions, output any of them.

## 说明/提示

In the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1979E/bbfd233820492f977fbef974993b9a69a436fb4a.png) Points $ A $ , $ B $ , and $ F $ form a Manhattan triangle, the Manhattan distance between each pair of vertices is $ 4 $ . Points $ D $ , $ E $ , and $ F $ can also be the answer.In the third test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1979E/0f533955337f14b26cd93892ca00000567fdf3e5.png) Points $ A $ , $ C $ , and $ E $ form a Manhattan triangle, the Manhattan distance between each pair of vertices is $ 6 $ .In the fourth test case, there are no two points with a Manhattan distance of $ 4 $ , and therefore there is no suitable Manhattan triangle.

## 样例 #1

### 输入

```
6
6 4
3 1
0 0
0 -2
5 -3
3 -5
2 -2
5 4
0 0
0 -2
5 -3
3 -5
2 -2
6 6
3 1
0 0
0 -2
5 -3
3 -5
2 -2
4 4
3 0
0 3
-3 0
0 -3
10 8
2 1
-5 -1
-4 -1
-5 -3
0 1
-2 5
-4 4
-4 2
0 0
-4 1
4 400000
100000 100000
-100000 100000
100000 -100000
-100000 -100000
```

### 输出

```
2 6 1
4 3 5
3 5 1
0 0 0
6 1 3
0 0 0
```

