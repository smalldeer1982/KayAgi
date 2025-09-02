---
title: "Rook"
layout: "post"
diff: 入门
pid: CF1907A
tag: []
---

# Rook

## 题目描述

As you probably know, chess is a game that is played on a board with 64 squares arranged in an $ 8\times 8 $ grid. Columns of this board are labeled with letters from a to h, and rows are labeled with digits from 1 to 8. Each square is described by the row and column it belongs to.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1907A/5226e0bd856554fc042684f72134386d96e93c43.png)The rook is a piece in the game of chess. During its turn, it may move any non-zero number of squares horizontally or vertically. Your task is to find all possible moves for a rook on an empty chessboard.

## 输入格式

The first line of input contains single integer $ t $ ( $ 1 \le t \le 64 $ ) — the number of test cases. The descriptions of test cases follow.

Each test case contains one string of two characters, description of the square where rook is positioned. The first character is a letter from a to h, the label of column, and the second character is a digit from 1 to 8, the label of row.

The same position may occur in more than one test case.

## 输出格式

For each test case, output descriptions of all squares where the rook can move, in the same format as in the input.

You can output squares in any order per test case.

## 样例 #1

### 输入

```
1
d5
```

### 输出

```
d1
d2
b5
g5
h5
d3
e5
f5
d8
a5
d6
d7
c5
d4
```

