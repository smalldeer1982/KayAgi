---
title: "Rectangular Polyline"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1444D
tag: []
---

# Rectangular Polyline

## 题目描述

One drew a closed polyline on a plane, that consisted only of vertical and horizontal segments (parallel to the coordinate axes). The segments alternated between horizontal and vertical ones (a horizontal segment was always followed by a vertical one, and vice versa). The polyline did not contain strict self-intersections, which means that in case any two segments shared a common point, that point was an endpoint for both of them (please consult the examples in the notes section).

Unfortunately, the polyline was erased, and you only know the lengths of the horizonal and vertical segments. Please construct any polyline matching the description with such segments, or determine that it does not exist.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 200 $ ) —the number of test cases.

The first line of each test case contains one integer $ h $ ( $ 1 \leq h \leq 1000 $ ) — the number of horizontal segments. The following line contains $ h $ integers $ l_1, l_2, \dots, l_h $ ( $ 1 \leq l_i \leq 1000 $ ) — lengths of the horizontal segments of the polyline, in arbitrary order.

The following line contains an integer $ v $ ( $ 1 \leq v \leq 1000 $ ) — the number of vertical segments, which is followed by a line containing $ v $ integers $ p_1, p_2, \dots, p_v $ ( $ 1 \leq p_i \leq 1000 $ ) — lengths of the vertical segments of the polyline, in arbitrary order.

Test cases are separated by a blank line, and the sum of values $ h + v $ over all test cases does not exceed $ 1000 $ .

## 输出格式

For each test case output Yes, if there exists at least one polyline satisfying the requirements, or No otherwise. If it does exist, in the following $ n $ lines print the coordinates of the polyline vertices, in order of the polyline traversal: the $ i $ -th line should contain two integers $ x_i $ and $ y_i $ — coordinates of the $ i $ -th vertex.

Note that, each polyline segment must be either horizontal or vertical, and the segments should alternate between horizontal and vertical. The coordinates should not exceed $ 10^9 $ by their absolute value.

## 说明/提示

In the first test case of the first example, the answer is Yes — for example, the following picture illustrates a square that satisfies the requirements:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1444D/511e3cc6ecd7cbf8bef9022e593d85929ba09d17.png)In the first test case of the second example, the desired polyline also exists. Note that, the polyline contains self-intersections, but only in the endpoints:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1444D/0fcb4ab165879349d64b5ec435afdbdfe4bad9ed.png)In the second test case of the second example, the desired polyline could be like the one below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1444D/8889270100914e11d3c483d0ff3b94b9e989e1a1.png)Note that the following polyline is not a valid one, since it contains self-intersections that are not endpoints for some of the segments:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1444D/0176b8a3571481194d4ceebd3813157b1aae2d53.png)

## 样例 #1

### 输入

```
2
2
1 1
2
1 1

2
1 2
2
3 3
```

### 输出

```
Yes
1 0
1 1
0 1
0 0
No
```

## 样例 #2

### 输入

```
2
4
1 1 1 1
4
1 1 1 1

3
2 1 1
3
2 1 1
```

### 输出

```
Yes
1 0
1 1
2 1
2 2
1 2
1 1
0 1
0 0
Yes
0 -2
2 -2
2 -1
1 -1
1 0
0 0
```

## 样例 #3

### 输入

```
2
4
1 4 1 2
4
3 4 5 12

4
1 2 3 6
2
1 3
```

### 输出

```
Yes
2 0
2 3
3 3
3 7
4 7
4 12
0 12
0 0
No
```

