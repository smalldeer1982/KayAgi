---
title: "Rectangles and Square"
layout: "post"
diff: 省选/NOI-
pid: CF335D
tag: []
---

# Rectangles and Square

## 题目描述

You are given $ n $ rectangles, labeled 1 through $ n $ . The corners of rectangles have integer coordinates and their edges are parallel to the $ Ox $ and $ Oy $ axes. The rectangles may touch each other, but they do not overlap (that is, there are no points that belong to the interior of more than one rectangle).

Your task is to determine if there's a non-empty subset of the rectangles that forms a square. That is, determine if there exists a subset of the rectangles and some square for which every point that belongs to the interior or the border of that square belongs to the interior or the border of at least one of the rectangles in the subset, and every point that belongs to the interior or the border of at least one rectangle in the subset belongs to the interior or the border of that square.

## 输入格式

First line contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of rectangles. Each of the next $ n $ lines contains a description of a rectangle, with the $ i $ -th such line describing the rectangle labeled $ i $ . Each rectangle description consists of four integers: $ x_{1} $ , $ y_{1} $ , $ x_{2} $ , $ y_{2} $ — coordinates of the bottom left and the top right corners ( $ 0<=x_{1}&lt;x_{2}<=3000 $ , $ 0<=y_{1}&lt;y_{2}<=3000 $ ).

No two rectangles overlap (that is, there are no points that belong to the interior of more than one rectangle).

## 输出格式

If such a subset exists, print "YES" (without quotes) on the first line of the output file, followed by $ k $ , the number of rectangles in the subset. On the second line print $ k $ numbers — the labels of rectangles in the subset in any order. If more than one such subset exists, print any one. If no such subset exists, print "NO" (without quotes).

## 说明/提示

The first test case looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF335D/b555a1b2f0fa9850a908273e7c5806edefd08e25.png)Note that rectangles 6, 8, and 9 form a square as well, and would be an acceptable answer.

The second test case looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF335D/50fe7d9330ec3e3fa026a900ee9c84c7d3b58755.png)

## 样例 #1

### 输入

```
9
0 0 1 9
1 0 9 1
1 8 9 9
8 1 9 8
2 2 3 6
3 2 7 3
2 6 7 7
5 3 7 6
3 3 5 6

```

### 输出

```
YES 5
5 6 7 8 9

```

## 样例 #2

### 输入

```
4
0 0 1 9
1 0 9 1
1 8 9 9
8 1 9 8

```

### 输出

```
NO

```

