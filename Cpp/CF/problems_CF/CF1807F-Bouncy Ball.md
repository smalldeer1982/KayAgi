---
title: "Bouncy Ball"
layout: "post"
diff: 普及+/提高
pid: CF1807F
tag: []
---

# Bouncy Ball

## 题目描述

You are given a room that can be represented by a $ n \times m $ grid. There is a ball at position $ (i_1, j_1) $ (the intersection of row $ i_1 $ and column $ j_1 $ ), and it starts going diagonally in one of the four directions:

- The ball is going down and right, denoted by $ \texttt{DR} $ ; it means that after a step, the ball's location goes from $ (i, j) $ to $ (i+1, j+1) $ .
- The ball is going down and left, denoted by $ \texttt{DL} $ ; it means that after a step, the ball's location goes from $ (i, j) $ to $ (i+1, j-1) $ .
- The ball is going up and right, denoted by $ \texttt{UR} $ ; it means that after a step, the ball's location goes from $ (i, j) $ to $ (i-1, j+1) $ .
- The ball is going up and left, denoted by $ \texttt{UL} $ ; it means that after a step, the ball's location goes from $ (i, j) $ to $ (i-1, j-1) $ .

After each step, the ball maintains its direction unless it hits a wall (that is, the direction takes it out of the room's bounds in the next step). In this case, the ball's direction gets flipped along the axis of the wall; if the ball hits a corner, both directions get flipped. Any instance of this is called a bounce. The ball never stops moving.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1807F/b981cd1b02284413957fa53dbf389556ca82be95.png)In the above example, the ball starts at $ (1, 7) $ and goes $ \texttt{DL} $ until it reaches the bottom wall, then it bounces and continues in the direction $ \texttt{UL} $ . After reaching the left wall, the ball bounces and continues to go in the direction $ \texttt{UR} $ . When the ball reaches the upper wall, it bounces and continues in the direction $ \texttt{DR} $ . After reaching the bottom-right corner, it bounces once and continues in direction $ \texttt{UL} $ , and so on.

Your task is to find how many bounces the ball will go through until it reaches cell $ (i_2, j_2) $ in the room, or report that it never reaches cell $ (i_2, j_2) $ by printing $ -1 $ .

Note that the ball first goes in a cell and only after that bounces if it needs to.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains six integers and a string $ n, m, i_1, j_1, i_2, j_2, d $ ( $ 2 \leq n, m \leq 25000 $ ; $ 1 \leq i_1, i_2 \leq n $ ; $ 1 \leq j_1, j_2 \leq m $ ; $ d \in\{ \texttt{DR}, \texttt{DL}, \texttt{UR}, \texttt{UL}\} $ ) — the dimensions of the grid, the starting coordinates of the ball, the coordinates of the final cell and the starting direction of the ball.

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 5 \cdot 10^4 $ .

## 输出格式

For each test case, output a single integer — the number of bounces the ball does until it reaches cell $ (i_2, j_2) $ for the first time, or $ -1 $ if the ball never reaches the final cell.

## 样例 #1

### 输入

```
6
5 7 1 7 2 4 DL
5 7 1 7 3 2 DL
3 3 1 3 2 2 UR
2 4 2 1 2 2 DR
4 3 1 1 1 3 UL
6 4 1 2 3 4 DR
```

### 输出

```
3
-1
1
-1
4
0
```

