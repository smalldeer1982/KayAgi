---
title: "Five-In-a-Row"
layout: "post"
diff: 普及-
pid: CF825B
tag: []
---

# Five-In-a-Row

## 题目描述

Alice and Bob play 5-in-a-row game. They have a playing field of size $ 10×10 $ . In turns they put either crosses or noughts, one at a time. Alice puts crosses and Bob puts noughts.

In current match they have made some turns and now it's Alice's turn. She wonders if she can put cross in such empty cell that she wins immediately.

Alice wins if some crosses in the field form line of length not smaller than 5. This line can be horizontal, vertical and diagonal.

## 输入格式

You are given matrix $ 10×10 $ (10 lines of 10 characters each) with capital Latin letters 'X' being a cross, letters 'O' being a nought and '.' being an empty cell. The number of 'X' cells is equal to the number of 'O' cells and there is at least one of each type. There is at least one empty cell.

It is guaranteed that in the current arrangement nobody has still won.

## 输出格式

Print 'YES' if it's possible for Alice to win in one turn by putting cross in some empty cell. Otherwise print 'NO'.

## 样例 #1

### 输入

```
XX.XX.....
.....OOOO.
..........
..........
..........
..........
..........
..........
..........
..........

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
XXOXX.....
OO.O......
..........
..........
..........
..........
..........
..........
..........
..........

```

### 输出

```
NO

```

