---
title: "Dominoes"
layout: "post"
diff: 提高+/省选-
pid: CF1608D
tag: []
---

# Dominoes

## 题目描述

You are given $ n $ dominoes. Each domino has a left and a right cell. Each cell can be colored either black or white. Some cells are already colored, while some aren't yet.

The coloring is said to be valid if and only if it is possible to rearrange the dominoes in some order such that for each $ 1 \le i \le n $ the color of the right cell of the $ i $ -th domino is different from the color of the left cell of the $ ((i \bmod n)+1) $ -st domino.

Note that you can't rotate the dominoes, so the left cell always remains the left cell, and the right cell always remains the right cell.

Count the number of valid ways to color the yet uncolored cells of dominoes. Two ways are considered different if there is a cell that is colored white in one way and black in the other. In particular, colorings BW WB and WB BW different (and both invalid).

As this number can be very big, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of dominoes.

The next $ n $ lines describe dominoes. Each line contains two characters which represent the left and the right cell. Character B means that the corresponding cell is black, character W means that the corresponding cell is white, and ? means that the cell is yet to be colored.

## 输出格式

Print a single integer — the answer to the problem.

## 说明/提示

In the first test case, there is only one domino, and we need the color of its right cell to be different from the color of its left cell. There is only one way to achieve this.

In the second test case, there are only $ 2 $ such colorings:

BB WW and WB WB.

## 样例 #1

### 输入

```
1
?W
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
??
W?
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
BB
??
W?
??
```

### 输出

```
10
```

