---
title: "Distanced Coloring"
layout: "post"
diff: 普及-
pid: CF2002A
tag: ['数学']
---

# Distanced Coloring

## 题目描述

You received an $ n\times m $ grid from a mysterious source. The source also gave you a magic positive integer constant $ k $ .

The source told you to color the grid with some colors, satisfying the following condition:

- If $ (x_1,y_1) $ , $ (x_2,y_2) $ are two distinct cells with the same color, then $ \max(|x_1-x_2|,|y_1-y_2|)\ge k $ .

You don't like using too many colors. Please find the minimum number of colors needed to color the grid.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\le t\le1000 $ ). The description of the test cases follows.

The only line of each test case consists of three positive integers $ n $ , $ m $ , $ k $ ( $ 1\le n,m,k\le10^4 $ ) — the dimensions of the grid and the magic constant.

## 输出格式

For each test case, print a single integer — the minimum number of colors needed to color the grid.

## 说明/提示

In the first test case, one of the optimal constructions is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2002A/9ce95b69207ca02098572c656648bb834e503b1e.png)In the second test case, the color of all cells must be pairwise different, so the answer is $ 5 $ .

## 样例 #1

### 输入

```
6
3 3 2
5 1 10000
7 3 4
3 2 7
8 9 6
2 5 4
```

### 输出

```
4
5
12
6
36
8
```

