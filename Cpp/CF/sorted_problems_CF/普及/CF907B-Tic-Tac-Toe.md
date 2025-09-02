---
title: "Tic-Tac-Toe"
layout: "post"
diff: 普及/提高-
pid: CF907B
tag: []
---

# Tic-Tac-Toe

## 题目背景

两头熊在玩一个游戏。

这个游戏的棋盘是由9个大方格排成$3\*3$的形式，每个大方格中有9个小方格，也是排成$3\*3$的形式。一个熊执x棋，一个执o棋。第一步由执x棋的熊下，可以下在任意一个小方格中，然后从第二步开始，上一个熊把棋下在的小方格在它所属的$3\*3$小方格中的对应位置，这头熊需要下在3\*3的大方格的对应位置大方格中的9个小方格中的一个。比如上一头熊下到了(6,4)(6,4)位置,(6,4)(6,4)位属于中间的那个大方格，在中间那个大方格的9个小方格中属于左下位，下一步就必须下到9个大方格的左下位的那个大方格中的9个小方格中的一个(样例1)。但是如果这9个小方格已经都被下过棋子了，那么就可以从其他地方任选一个小格子下棋(样例2)。

给定一个棋盘，上面有当前已经下完的棋子，再给出最后一步的坐标，要求在棋盘上下一步可以下的位置上打出"!"(无引号)

## 题目描述

Two bears are playing tic-tac-toe via mail. It's boring for them to play usual tic-tac-toe game, so they are a playing modified version of this game. Here are its rules.

The game is played on the following field.

 ![](http://espresso.codeforces.com/9f2cb44894dfaba91b9e381419482b55cfe9ff63.png)Players are making moves by turns. At first move a player can put his chip in any cell of any small field. For following moves, there are some restrictions: if during last move the opposite player put his chip to cell with coordinates $ (x_{l},y_{l}) $ in some small field, the next move should be done in one of the cells of the small field with coordinates $ (x_{l},y_{l}) $ . For example, if in the first move a player puts his chip to lower left cell of central field, then the second player on his next move should put his chip into some cell of lower left field (pay attention to the first test case). If there are no free cells in the required field, the player can put his chip to any empty cell on any field.

You are given current state of the game and coordinates of cell in which the last move was done. You should find all cells in which the current player can put his chip.

A hare works as a postman in the forest, he likes to foul bears. Sometimes he changes the game field a bit, so the current state of the game could be unreachable. However, after his changes the cell where the last move was done is not empty. You don't need to find if the state is unreachable or not, just output possible next moves according to the rules.

## 输入格式

First 11 lines contains descriptions of table with 9 rows and 9 columns which are divided into 9 small fields by spaces and empty lines. Each small field is described by 9 characters without spaces and empty lines. character "x" (ASCII-code 120) means that the cell is occupied with chip of the first player, character "o" (ASCII-code 111) denotes a field occupied with chip of the second player, character "." (ASCII-code 46) describes empty cell.

The line after the table contains two integers $ x $ and $ y $ ( $ 1<=x,y<=9 $ ). They describe coordinates of the cell in table where the last move was done. Rows in the table are numbered from up to down and columns are numbered from left to right.

It's guaranteed that cell where the last move was done is filled with "x" or "o". Also, it's guaranteed that there is at least one empty cell. It's not guaranteed that current state of game is reachable.

## 输出格式

Output the field in same format with characters "!" (ASCII-code 33) on positions where the current player can put his chip. All other cells should not be modified.

## 说明/提示

In the first test case the first player made a move to lower left cell of central field, so the second player can put a chip only to cells of lower left field.

In the second test case the last move was done to upper left cell of lower central field, however all cells in upper left field are occupied, so the second player can put his chip to any empty cell.

In the third test case the last move was done to central cell of central field, so current player can put his chip to any cell of central field, which is already occupied, so he can move anywhere. Pay attention that this state of the game is unreachable.

## 样例 #1

### 输入

```
... ... ...
... ... ...
... ... ...

... ... ...
... ... ...
... x.. ...

... ... ...
... ... ...
... ... ...
6 4

```

### 输出

```
... ... ... 
... ... ... 
... ... ... 

... ... ... 
... ... ... 
... x.. ... 

!!! ... ... 
!!! ... ... 
!!! ... ... 


```

## 样例 #2

### 输入

```
xoo x.. x..
ooo ... ...
ooo ... ...

x.. x.. x..
... ... ...
... ... ...

x.. x.. x..
... ... ...
... ... ...
7 4

```

### 输出

```
xoo x!! x!! 
ooo !!! !!! 
ooo !!! !!! 

x!! x!! x!! 
!!! !!! !!! 
!!! !!! !!! 

x!! x!! x!! 
!!! !!! !!! 
!!! !!! !!! 


```

## 样例 #3

### 输入

```
o.. ... ...
... ... ...
... ... ...

... xxx ...
... xox ...
... ooo ...

... ... ...
... ... ...
... ... ...
5 5

```

### 输出

```
o!! !!! !!! 
!!! !!! !!! 
!!! !!! !!! 

!!! xxx !!! 
!!! xox !!! 
!!! ooo !!! 

!!! !!! !!! 
!!! !!! !!! 
!!! !!! !!! 


```

