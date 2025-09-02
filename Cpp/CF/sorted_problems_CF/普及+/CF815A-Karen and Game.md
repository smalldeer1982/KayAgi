---
title: "Karen and Game"
layout: "post"
diff: 普及+/提高
pid: CF815A
tag: []
---

# Karen and Game

## 题目描述

On the way to school, Karen became fixated on the puzzle game on her phone!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815A/69d9eed46962e3cdadeae01ef67d1e4bd4bac050.png)The game is played as follows. In each level, you have a grid with $ n $ rows and $ m $ columns. Each cell originally contains the number $ 0 $ .

One move consists of choosing one row or column, and adding $ 1 $ to all of the cells in that row or column.

To win the level, after all the moves, the number in the cell at the $ i $ -th row and $ j $ -th column should be equal to $ g_{i,j} $ .

Karen is stuck on one level, and wants to know a way to beat this level using the minimum number of moves. Please, help her with this task!

## 输入格式

The first line of input contains two integers, $ n $ and $ m $ ( $ 1<=n,m<=100 $ ), the number of rows and the number of columns in the grid, respectively.

The next $ n $ lines each contain $ m $ integers. In particular, the $ j $ -th integer in the $ i $ -th of these rows contains $ g_{i,j} $ ( $ 0<=g_{i,j}<=500 $ ).

## 输出格式

If there is an error and it is actually not possible to beat the level, output a single integer -1.

Otherwise, on the first line, output a single integer $ k $ , the minimum number of moves necessary to beat the level.

The next $ k $ lines should each contain one of the following, describing the moves in the order they must be done:

- row $ x $ , ( $ 1<=x<=n $ ) describing a move of the form "choose the $ x $ -th row".
- col $ x $ , ( $ 1<=x<=m $ ) describing a move of the form "choose the $ x $ -th column".

If there are multiple optimal solutions, output any one of them.

## 说明/提示

In the first test case, Karen has a grid with $ 3 $ rows and $ 5 $ columns. She can perform the following $ 4 $ moves to beat the level:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815A/2c8fcc04f5be718b03f1b0d9aafd9c48834c67b9.png)In the second test case, Karen has a grid with $ 3 $ rows and $ 3 $ columns. It is clear that it is impossible to beat the level; performing any move will create three $ 1 $ s on the grid, but it is required to only have one $ 1 $ in the center.

In the third test case, Karen has a grid with $ 3 $ rows and $ 3 $ columns. She can perform the following $ 3 $ moves to beat the level:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815A/b5d0f3212dd0b57527e9775bb29c6dbecaf28d27.png)Note that this is not the only solution; another solution, among others, is col 1, col 2, col 3.

## 样例 #1

### 输入

```
3 5
2 2 2 3 2
0 0 0 1 0
1 1 1 2 1

```

### 输出

```
4
row 1
row 1
col 4
row 3

```

## 样例 #2

### 输入

```
3 3
0 0 0
0 1 0
0 0 0

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
3 3
1 1 1
1 1 1
1 1 1

```

### 输出

```
3
row 1
row 2
row 3

```

