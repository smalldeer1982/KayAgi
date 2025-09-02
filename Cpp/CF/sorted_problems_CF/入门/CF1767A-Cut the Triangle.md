---
title: "Cut the Triangle"
layout: "post"
diff: 入门
pid: CF1767A
tag: ['数学']
---

# Cut the Triangle

## 题目描述

You are given a non-degenerate triangle (a non-degenerate triangle is a triangle with positive area). The vertices of the triangle have coordinates $ (x_1, y_1) $ , $ (x_2, y_2) $ and $ (x_3, y_3) $ .

You want to draw a straight line to cut the triangle into two non-degenerate triangles. Furthermore, the line you draw should be either horizontal or vertical.

Can you draw the line to meet all the constraints?

Here are some suitable ways to draw the line:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1767A/eae3d7282c3158bdbed223cdc7230dcfb540b234.png)However, these ways to draw the line are not suitable (the first line cuts the triangle into a triangle and a quadrangle; the second line doesn't cut the triangle at all; the third line is neither horizontal nor vertical):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1767A/bffea37399e8b2b37904bb00d4f9d390b630614c.png)

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of four lines. The first of them is empty. The $ i $ -th of the next three lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le 10^8 $ ) — the coordinates of the $ i $ -th vertex of the triangle.

Additional constraint on the input: in each test case, the triangle formed by three vertices has positive area (i. e. it is non-degenerate).

## 输出格式

For each test case, print YES if it is possible to cut the triangle according to the statement, or NO otherwise. You may print each letter in any case (YES, yes, Yes will all be recognized as positive answer, NO, no and nO will all be recognized as negative answer).

## 样例 #1

### 输入

```
4


4 7
6 8
3 5


4 5
4 7
6 8


5 8
1 8
2 5


3 6
6 6
6 3
```

### 输出

```
YES
YES
YES
NO
```

