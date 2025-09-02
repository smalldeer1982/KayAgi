---
title: "Torus Path"
layout: "post"
diff: 普及+/提高
pid: CF1765K
tag: []
---

# Torus Path

## 题目描述

You are given a square grid with $ n $ rows and $ n $ columns, where each cell has a non-negative integer written in it. There is a chip initially placed at the top left cell (the cell with coordinates $ (1, 1) $ ). You need to move the chip to the bottom right cell (the cell with coordinates $ (n, n) $ ).

In one step, you can move the chip to the neighboring cell, but:

1. you can move only right or down. In other words, if the current cell is $ (x, y) $ , you can move either to $ (x, y + 1) $ or to $ (x + 1, y) $ . There are two special cases: 
  - if the chip is in the last column (cell $ (x, n) $ ) and you're moving right, you'll teleport to the first column (to the cell $ (x, 1) $ );
  - if the chip is in the last row (cell $ (n, y) $ ) and you're moving down, you'll teleport to the first row (to the cell $ (1, y) $ ).
2. you cannot visit the same cell twice. The starting cell is counted visited from the beginning (so you cannot enter it again), and you can't leave the finishing cell once you visit it.

Your total score is counted as the sum of numbers in all cells you have visited. What is the maximum possible score you can achieve?

## 输入格式

The first line contains the single integer $ n $ ( $ 2 \le n \le 200 $ ) — the number of rows and columns in the grid.

Next $ n $ lines contains the description of each row of the grid. The $ i $ -th line contains $ n $ integers $ a_{i, 1}, a_{i, 2}, \dots, a_{i, n} $ ( $ 0 \le a_{i, j} \le 10^9 $ ) where $ a_{i, j} $ is the number written in the cell $ (i, j) $ .

## 输出格式

Print one integer — the maximum possible score you can achieve.

## 样例 #1

### 输入

```
2
1 2
3 4
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3
10 10 10
10 0 10
10 10 10
```

### 输出

```
80
```

