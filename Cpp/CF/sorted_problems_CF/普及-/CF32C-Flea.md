---
title: "Flea"
layout: "post"
diff: 普及-
pid: CF32C
tag: []
---

# Flea

## 题目描述

It is known that fleas in Berland can jump only vertically and horizontally, and the length of the jump is always equal to $ s $ centimeters. A flea has found herself at the center of some cell of the checked board of the size $ n×m $ centimeters (each cell is $ 1×1 $ centimeters). She can jump as she wishes for an arbitrary number of times, she can even visit a cell more than once. The only restriction is that she cannot jump out of the board.

The flea can count the amount of cells that she can reach from the starting position $ (x,y) $ . Let's denote this amount by $ d_{x,y} $ . Your task is to find the number of such starting positions $ (x,y) $ , which have the maximum possible value of $ d_{x,y} $ .

## 输入格式

The first line contains three integers $ n $ , $ m $ , $ s $ ( $ 1<=n,m,s<=10^{6} $ ) — length of the board, width of the board and length of the flea's jump.

## 输出格式

Output the only integer — the number of the required starting positions of the flea.

## 样例 #1

### 输入

```
2 3 1000000

```

### 输出

```
6

```

## 样例 #2

### 输入

```
3 3 2

```

### 输出

```
4

```

