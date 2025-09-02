---
title: "Flood Fill"
layout: "post"
diff: 普及+/提高
pid: CF1114D
tag: []
---

# Flood Fill

## 题目描述

You are given a line of $ n $ colored squares in a row, numbered from $ 1 $ to $ n $ from left to right. The $ i $ -th square initially has the color $ c_i $ .

Let's say, that two squares $ i $ and $ j $ belong to the same connected component if $ c_i = c_j $ , and $ c_i = c_k $ for all $ k $ satisfying $ i < k < j $ . In other words, all squares on the segment from $ i $ to $ j $ should have the same color.

For example, the line $ [3, 3, 3] $ has $ 1 $ connected component, while the line $ [5, 2, 4, 4] $ has $ 3 $ connected components.

The game "flood fill" is played on the given line as follows:

- At the start of the game you pick any starting square (this is not counted as a turn).
- Then, in each game turn, change the color of the connected component containing the starting square to any other color.

Find the minimum number of turns needed for the entire line to be changed into a single color.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the number of squares.

The second line contains integers $ c_1, c_2, \ldots, c_n $ ( $ 1 \le c_i \le 5000 $ ) — the initial colors of the squares.

## 输出格式

Print a single integer — the minimum number of the turns needed.

## 说明/提示

In the first example, a possible way to achieve an optimal answer is to pick square with index $ 2 $ as the starting square and then play as follows:

- $ [5, 2, 2, 1] $
- $ [5, 5, 5, 1] $
- $ [1, 1, 1, 1] $

In the second example, a possible way to achieve an optimal answer is to pick square with index $ 5 $ as the starting square and then perform recoloring into colors $ 2, 3, 5, 4 $ in that order.

In the third example, the line already consists of one color only.

## 样例 #1

### 输入

```
4
5 2 2 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
8
4 5 2 2 1 3 5 5

```

### 输出

```
4

```

## 样例 #3

### 输入

```
1
4

```

### 输出

```
0

```

