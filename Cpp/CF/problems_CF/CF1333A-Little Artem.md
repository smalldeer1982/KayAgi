---
title: "Little Artem"
layout: "post"
diff: 普及-
pid: CF1333A
tag: []
---

# Little Artem

## 题目描述

Young boy Artem tries to paint a picture, and he asks his mother Medina to help him. Medina is very busy, that's why she asked for your help.

Artem wants to paint an $ n \times m $ board. Each cell of the board should be colored in white or black.

Lets $ B $ be the number of black cells that have at least one white neighbor adjacent by the side. Let $ W $ be the number of white cells that have at least one black neighbor adjacent by the side. A coloring is called good if $ B = W + 1 $ .

The first coloring shown below has $ B=5 $ and $ W=4 $ (all cells have at least one neighbor with the opposite color). However, the second coloring is not good as it has $ B=4 $ , $ W=4 $ (only the bottom right cell doesn't have a neighbor with the opposite color).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1333A/34674661541310c7b0f570cbf7d03ed451c5851a.png)Please, help Medina to find any good coloring. It's guaranteed that under given constraints the solution always exists. If there are several solutions, output any of them.

## 输入格式

Each test contains multiple test cases.

The first line contains the number of test cases $ t $ ( $ 1 \le t \le 20 $ ). Each of the next $ t $ lines contains two integers $ n, m $ ( $ 2 \le n,m \le 100 $ ) — the number of rows and the number of columns in the grid.

## 输出格式

For each test case print $ n $ lines, each of length $ m $ , where $ i $ -th line is the $ i $ -th row of your colored matrix (cell labeled with 'B' means that the cell is black, and 'W' means white). Do not use quotes.

It's guaranteed that under given constraints the solution always exists.

## 说明/提示

In the first testcase, $ B=3 $ , $ W=2 $ .

In the second testcase, $ B=5 $ , $ W=4 $ . You can see the coloring in the statement.

## 样例 #1

### 输入

```
2
3 2
3 3
```

### 输出

```
BW
WB
BB
BWB
BWW
BWB
```

