---
title: "Grid Game 2"
layout: "post"
diff: 省选/NOI-
pid: CF1906G
tag: ['博弈论', '最大公约数 gcd']
---

# Grid Game 2

## 题目描述

You are playing "Grid Game 2" with your friend. There is a grid with $ 10^9 $ rows (numbered from $ 1 $ to $ 10^9 $ ) and $ 10^9 $ columns (numbered from $ 1 $ to $ 10^9 $ ). The cell at row $ r $ and column $ c $ is denoted as $ (r, c) $ .

Each cell can have a colour of either black or white. Initially, there are exactly $ N $ black cells (numbered from $ 1 $ to $ N $ ). Black cell $ i $ is located at $ (R_i, C_i) $ . The rest of the cells are white.

You and your friend will alternately take turn playing on this grid, and you are playing in the first turn. In one turn, a player will choose a black cell $ (r, c) $ , then toggle cells $ (r - x, c - y) $ for all $ 0 \leq x, y < \min(r, c) $ . If a cell is toggled, then the cell becomes black if it was a white cell, and the cell becomes white if it was a black cell.

For example, the following illustration shows how the grid changes after a player chooses a black cell $ (5, 4) $ in their turn.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906G/e2fd54c73d9615e1033b8dd1a01d70086e6fa600.png)A player who is unable to play on their turn, i.e. no remaining black cells, loses the game, and the opposing player wins the game. If you and your friend are playing optimally, determine who will win the game.

## 输入格式

The first line consists of an integer $ N $ ( $ 1 \le N \le 200\,000 $ ).

Each of the next $ N $ lines consists of two integers $ R_i $ $ C_i $ ( $ 1 \leq R_i, C_i \leq 10^9) $ . For $ 1 \leq i < j \leq N $ , $ (R_i, C_i) \neq (R_j, C_j) $ .

## 输出格式

Output FIRST if you will win the game, or SECOND otherwise.

## 说明/提示

Explanation for the sample input/output #1

You can start your move by choosing $ (2, 4) $ , whose effect was demonstrated in the following illustration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906G/2b04f438065762fd04c672bc2aeca49fdf0ed64a.png)The remaining black cells are $ (1, 3) $ and $ (1, 4) $ , each of which will only toggle itself when chosen. Whichever your friend chooses on the next move, the you can choose the remaining black cell.

Explanation for the sample input/output #2

You have only one cell to choose, and will toggle cells $ (1, 1) $ , $ (1, 2) $ , $ (2, 1) $ , and $ (2, 2) $ . Your friend and you will alternately choose the remaining black cells with your friend choosing the last black cell.

## 样例 #1

### 输入

```
2
2 3
2 4
```

### 输出

```
FIRST
```

## 样例 #2

### 输入

```
1
2 2
```

### 输出

```
SECOND
```

## 样例 #3

### 输入

```
13
1 1
1 4
1 5
2 1
2 4
2 5
4 1
4 2
4 4
5 1
5 2
5 4
5 5
```

### 输出

```
SECOND
```



---

