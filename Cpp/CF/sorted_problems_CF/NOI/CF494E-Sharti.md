---
title: "Sharti"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF494E
tag: []
---

# Sharti

## 题目描述

During the last 24 hours Hamed and Malek spent all their time playing "Sharti". Now they are too exhausted to finish the last round. So they asked you for help to determine the winner of this round.

"Sharti" is played on a $ n×n $ board with some of cells colored white and others colored black. The rows of the board are numbered from top to bottom using number $ 1 $ to $ n $ . Also the columns of the board are numbered from left to right using numbers $ 1 $ to $ n $ . The cell located at the intersection of $ i $ -th row and $ j $ -th column is denoted by $ (i,j) $ .

The players alternatively take turns. In each turn the player must choose a square with side-length at most $ k $ with its lower-right cell painted white. Then the colors of all the cells in this square are inversed (white cells become black and vice-versa). The player who cannot perform a move in his turn loses.

You know Hamed and Malek are very clever and they would have played their best moves at each turn. Knowing this and the fact that Hamed takes the first turn, given the initial board as described in the input, you must determine which one of them will be the winner.

## 输入格式

In this problem the initial board is specified as a set of  $m$ rectangles. All cells that lie inside at least one of these rectangles are colored white and the rest are colored black.

In the first line of input three space-spereated integers  $n,m,k(1\le k\le n\le 10^9,1\le m\le 5\times 10^4)$ follow, denoting size of the board, number of rectangles and maximum size of the turn square during the game, respectively.

In  $i$ - th line of the next  $m$ lines four space-seperated integers  $a_i,b_i,c_i,d_i(1≤a_i≤c_i≤n, 1≤b_i≤d_i≤n)$ are given meaning that  $i$ - th rectangle determining the initial board is a rectangle with upper-left cell at  $(a_i,b_i)$ and lower-right cell at  $(c_i,d_i)$.

## 输出格式

If Hamed wins, print "Hamed", otherwise print "Malek" (without the quotes).

## 样例 #1

### 输入

```
5 2 1
1 1 3 3
2 2 4 4

```

### 输出

```
Malek

```

## 样例 #2

### 输入

```
12 5 7
3 4 5 6
1 2 1 2
4 5 9 9
8 6 12 10
12 4 12 4

```

### 输出

```
Hamed

```

