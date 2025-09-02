---
title: "Fillomino 2"
layout: "post"
diff: 普及/提高-
pid: CF1517C
tag: []
---

# Fillomino 2

## 题目描述

Fillomino is a classic logic puzzle. (You do not need to know Fillomino in order to solve this problem.) In one classroom in Yunqi town, some volunteers are playing a board game variant of it:

Consider an $ n $ by $ n $ chessboard. Its rows are numbered from $ 1 $ to $ n $ from the top to the bottom. Its columns are numbered from $ 1 $ to $ n $ from the left to the right. A cell on an intersection of $ x $ -th row and $ y $ -th column is denoted $ (x, y) $ . The main diagonal of the chessboard is cells $ (x, x) $ for all $ 1 \le x \le n $ .

A permutation of $ \{1, 2, 3, \dots, n\} $ is written on the main diagonal of the chessboard. There is exactly one number written on each of the cells. The problem is to partition the cells under and on the main diagonal (there are exactly $ 1+2+ \ldots +n $ such cells) into $ n $ connected regions satisfying the following constraints:

1. Every region should be connected. That means that we can move from any cell of a region to any other cell of the same region visiting only cells of the same region and moving from a cell to an adjacent cell.
2. The $ x $ -th region should contain cell on the main diagonal with number $ x $ for all $ 1\le x\le n $ .
3. The number of cells that belong to the $ x $ -th region should be equal to $ x $ for all $ 1\le x\le n $ .
4. Each cell under and on the main diagonal should belong to exactly one region.

## 输入格式

The first line contains a single integer $ n $ ( $ 1\le n \le 500 $ ) denoting the size of the chessboard.

The second line contains $ n $ integers $ p_1 $ , $ p_2 $ , ..., $ p_n $ . $ p_i $ is the number written on cell $ (i, i) $ . It is guaranteed that each integer from $ \{1, \ldots, n\} $ appears exactly once in $ p_1 $ , ..., $ p_n $ .

## 输出格式

If no solution exists, output $ -1 $ .

Otherwise, output $ n $ lines. The $ i $ -th line should contain $ i $ numbers. The $ j $ -th number on the $ i $ -th line should be $ x $ if cell $ (i, j) $ belongs to the the region with $ x $ cells.

## 说明/提示

The solutions to the examples are illustrated in the following pictures: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1517C/9c1f0c1849ccf4ce0e7b23176bd91c953e348595.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1517C/9e88a2fdc4b038adc182da7d0d66d5d0dcc6a27e.png)

## 样例 #1

### 输入

```
3
2 3 1
```

### 输出

```
2
2 3
3 3 1
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
1
2 2
3 3 3
4 4 4 4
5 5 5 5 5
```

