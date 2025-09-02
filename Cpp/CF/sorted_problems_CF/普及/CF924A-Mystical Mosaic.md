---
title: "Mystical Mosaic"
layout: "post"
diff: 普及/提高-
pid: CF924A
tag: []
---

# Mystical Mosaic

## 题目描述

There is a rectangular grid of $ n $ rows of $ m $ initially-white cells each.

Arkady performed a certain number (possibly zero) of operations on it. In the $ i $ -th operation, a non-empty subset of rows $ R_{i} $ and a non-empty subset of columns $ C_{i} $ are chosen. For each row $ r $ in $ R_{i} $ and each column $ c $ in $ C_{i} $ , the intersection of row $ r $ and column $ c $ is coloured black.

There's another constraint: a row or a column can only be chosen at most once among all operations. In other words, it means that no pair of $ (i,j) $ ( $ i<j $ ) exists such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924A/970bfdc984412d650a4edcfe5e0a8df4329d1b0b.png) or ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924A/74963b959d98ef5a1623c0fa6c3ddc72e6be47dd.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924A/f53ec93ace7ac116d42268fc65398baf94289b39.png) denotes intersection of sets, and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924A/a8551b5381914bb6ecc9b38259329c2377122e54.png) denotes the empty set.

You are to determine whether a valid sequence of operations exists that produces a given final grid.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ $ (1<=n,m<=50 $ ) — the number of rows and columns of the grid, respectively.

Each of the following $ n $ lines contains a string of $ m $ characters, each being either '.' (denoting a white cell) or '\#' (denoting a black cell), representing the desired setup.

## 输出格式

If the given grid can be achieved by any valid sequence of operations, output "Yes"; otherwise output "No" (both without quotes).

You can print each character in any case (upper or lower).

## 说明/提示

For the first example, the desired setup can be produced by $ 3 $ operations, as is shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924A/74e6b77ab65d49c640ecfae7cdd0e283eea435f7.png)For the second example, the desired setup cannot be produced, since in order to colour the center row, the third row and all columns must be selected in one operation, but after that no column can be selected again, hence it won't be possible to colour the other cells in the center column.

## 样例 #1

### 输入

```
5 8
.#.#..#.
.....#..
.#.#..#.
#.#....#
.....#..

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
5 5
..#..
..#..
#####
..#..
..#..

```

### 输出

```
No

```

## 样例 #3

### 输入

```
5 9
........#
#........
..##.#...
.......#.
....#.#.#

```

### 输出

```
No

```

