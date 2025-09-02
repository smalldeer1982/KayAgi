---
title: "Tiling Challenge"
layout: "post"
diff: 普及/提高-
pid: CF1150B
tag: []
---

# Tiling Challenge

## 题目描述

One day Alice was cleaning up her basement when she noticed something very curious: an infinite set of wooden pieces! Each piece was made of five square tiles, with four tiles adjacent to the fifth center tile:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1150B/ad6ce0df252a3db4eebc7f2ae8f0d041a8339ee0.png) By the pieces lay a large square wooden board. The board is divided into $ n^2 $ cells arranged into $ n $ rows and $ n $ columns. Some of the cells are already occupied by single tiles stuck to it. The remaining cells are free.Alice started wondering whether she could fill the board completely using the pieces she had found. Of course, each piece has to cover exactly five distinct cells of the board, no two pieces can overlap and every piece should fit in the board entirely, without some parts laying outside the board borders. The board however was too large for Alice to do the tiling by hand. Can you help determine if it's possible to fully tile the board?

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 3 \leq n \leq 50 $ ) — the size of the board.

The following $ n $ lines describe the board. The $ i $ -th line ( $ 1 \leq i \leq n $ ) contains a single string of length $ n $ . Its $ j $ -th character ( $ 1 \leq j \leq n $ ) is equal to "." if the cell in the $ i $ -th row and the $ j $ -th column is free; it is equal to "\#" if it's occupied.

You can assume that the board contains at least one free cell.

## 输出格式

Output YES if the board can be tiled by Alice's pieces, or NO otherwise. You can print each letter in any case (upper or lower).

## 说明/提示

The following sketches show the example boards and their tilings if such tilings exist:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1150B/4aa3066acea41ad93dd59954e4030c273a6b97d8.png)

## 样例 #1

### 输入

```
3
#.#
...
#.#

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4
##.#
#...
####
##.#

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5
#.###
....#
#....
###.#
#####

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
5
#.###
....#
#....
....#
#..##

```

### 输出

```
NO

```

