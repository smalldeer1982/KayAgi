---
title: "Colour the Flag"
layout: "post"
diff: 普及-
pid: CF1534A
tag: []
---

# Colour the Flag

## 题目描述

Today we will be playing a red and white colouring game (no, this is not the Russian Civil War; these are just the colours of the Canadian flag).

You are given an $ n \times m $ grid of "R", "W", and "." characters. "R" is red, "W" is white and "." is blank. The neighbours of a cell are those that share an edge with it (those that only share a corner do not count).

Your job is to colour the blank cells red or white so that every red cell only has white neighbours (and no red ones) and every white cell only has red neighbours (and no white ones). You are not allowed to recolour already coloured cells.

## 输入格式

The first line contains $ t $ ( $ 1 \le t \le 100 $ ), the number of test cases.

In each test case, the first line will contain $ n $ ( $ 1 \le n \le 50 $ ) and $ m $ ( $ 1 \le m \le 50 $ ), the height and width of the grid respectively.

The next $ n $ lines will contain the grid. Each character of the grid is either 'R', 'W', or '.'.

## 输出格式

For each test case, output "YES" if there is a valid grid or "NO" if there is not.

If there is, output the grid on the next $ n $ lines. If there are multiple answers, print any.

In the output, the "YES"s and "NO"s are case-insensitive, meaning that outputs such as "yEs" and "nO" are valid. However, the grid is case-sensitive.

## 说明/提示

The answer for the first example case is given in the example output, and it can be proven that no grid exists that satisfies the requirements of the second example case. In the third example all cells are initially coloured, and the colouring is valid.

## 样例 #1

### 输入

```
3
4 6
.R....
......
......
.W....
4 4
.R.W
....
....
....
5 1
R
W
R
W
R
```

### 输出

```
YES
WRWRWR
RWRWRW
WRWRWR
RWRWRW
NO
YES
R
W
R
W
R
```

