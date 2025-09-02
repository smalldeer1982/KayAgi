---
title: "Brick Wall"
layout: "post"
diff: 入门
pid: CF1918A
tag: []
---

# Brick Wall

## 题目描述

A brick is a strip of size $ 1 \times k $ , placed horizontally or vertically, where $ k $ can be an arbitrary number that is at least $ 2 $ ( $ k \ge 2 $ ).

A brick wall of size $ n \times m $ is such a way to place several bricks inside a rectangle $ n \times m $ , that all bricks lie either horizontally or vertically in the cells, do not cross the border of the rectangle, and that each cell of the $ n \times m $ rectangle belongs to exactly one brick. Here $ n $ is the height of the rectangle $ n \times m $ and $ m $ is the width. Note that there can be bricks with different values of k in the same brick wall.

The wall stability is the difference between the number of horizontal bricks and the number of vertical bricks. Note that if you used $ 0 $ horizontal bricks and $ 2 $ vertical ones, then the stability will be  $ -2 $ , not $ 2 $ .

What is the maximal possible stability of a wall of size $ n \times m $ ?

It is guaranteed that under restrictions in the statement at least one $ n \times m $ wall exists.

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1 \le t \le 10\,000 $ ), the number of test cases.

The only line of each test case contains two integers $ n $ and $ m $ ( $ 2 \le n,\,m \le 10^4 $ ).

## 输出格式

For each test case, print one integer, the maximum stability of a wall of size $ n \times m $ .

## 说明/提示

In the 1st test case, the maximum stability of $ 2 $ is obtained by placing two horizontal bricks $ 1 \times 2 $ one on top of the other.

In the 2nd test case, one can get the maximum stability of $ 28 $ by placing $ 4 $ horizontal bricks $ 1 \times 2 $ in each of the $ 7 $ rows.

## 样例 #1

### 输入

```
5
2 2
7 8
16 9
3 5
10000 10000
```

### 输出

```
2
28
64
6
50000000
```

