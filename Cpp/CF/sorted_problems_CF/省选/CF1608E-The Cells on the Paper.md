---
title: "The Cells on the Paper"
layout: "post"
diff: 省选/NOI-
pid: CF1608E
tag: []
---

# The Cells on the Paper

## 题目描述

On an endless checkered sheet of paper, $ n $ cells are chosen and colored in three colors, where $ n $ is divisible by $ 3 $ . It turns out that there are exactly $ \frac{n}{3} $ marked cells of each of three colors!

Find the largest such $ k $ that it's possible to choose $ \frac{k}{3} $ cells of each color, remove all other marked cells, and then select three rectangles with sides parallel to the grid lines so that the following conditions hold:

- No two rectangles can intersect (but they can share a part of the boundary). In other words, the area of intersection of any two of these rectangles must be $ 0 $ .
- The $ i $ -th rectangle contains all the chosen cells of the $ i $ -th color and no chosen cells of other colors, for $ i = 1, 2, 3 $ .

## 输入格式

The first line of the input contains a single integer $ n $ — the number of the marked cells ( $ 3 \leq n \le 10^5 $ , $ n $ is divisible by 3).

The $ i $ -th of the following $ n $ lines contains three integers $ x_i $ , $ y_i $ , $ c_i $ ( $ |x_i|,|y_i| \leq 10^9 $ ; $ 1 \leq c_i \leq 3 $ ), where $ (x_i, y_i) $ are the coordinates of the $ i $ -th marked cell and $ c_i $ is its color.

It's guaranteed that all cells $ (x_i, y_i) $ in the input are distinct, and that there are exactly $ \frac{n}{3} $ cells of each color.

## 输出格式

Output a single integer $ k $ — the largest number of cells you can leave.

## 说明/提示

In the first sample, it's possible to leave $ 6 $ cells with indexes $ 1, 5, 6, 7, 8, 9 $ .

In the second sample, it's possible to leave $ 3 $ cells with indexes $ 1, 2, 3 $ .

## 样例 #1

### 输入

```
9
2 3 1
4 1 2
2 1 3
3 4 1
5 3 2
4 4 3
2 4 1
5 2 2
3 5 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3
1 1 1
2 2 2
3 3 3
```

### 输出

```
3
```

