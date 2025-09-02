---
title: "Gerald and Giant Chess"
layout: "post"
diff: 提高+/省选-
pid: CF559C
tag: ['动态规划 DP', '组合数学']
---

# Gerald and Giant Chess

## 题目描述

Giant chess is quite common in Geraldion. We will not delve into the rules of the game, we'll just say that the game takes place on an $ h×w $ field, and it is painted in two colors, but not like in chess. Almost all cells of the field are white and only some of them are black. Currently Gerald is finishing a game of giant chess against his friend Pollard. Gerald has almost won, and the only thing he needs to win is to bring the pawn from the upper left corner of the board, where it is now standing, to the lower right corner. Gerald is so confident of victory that he became interested, in how many ways can he win?

The pawn, which Gerald has got left can go in two ways: one cell down or one cell to the right. In addition, it can not go to the black cells, otherwise the Gerald still loses. There are no other pawns or pieces left on the field, so that, according to the rules of giant chess Gerald moves his pawn until the game is over, and Pollard is just watching this process.

## 输入格式

The first line of the input contains three integers: $ h,w,n $ — the sides of the board and the number of black cells ( $ 1<=h,w<=10^{5},1<=n<=2000 $ ).

Next $ n $ lines contain the description of black cells. The $ i $ -th of these lines contains numbers $ r_{i},c_{i} $ ( $ 1<=r_{i}<=h,1<=c_{i}<=w $ ) — the number of the row and column of the $ i $ -th cell.

It is guaranteed that the upper left and lower right cell are white and all cells in the description are distinct.

## 输出格式

Print a single line — the remainder of the number of ways to move Gerald's pawn from the upper left to the lower right corner modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
3 4 2
2 2
2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
100 100 3
15 16
16 15
99 88

```

### 输出

```
545732279

```

