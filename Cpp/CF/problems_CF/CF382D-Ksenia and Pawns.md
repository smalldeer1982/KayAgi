---
title: "Ksenia and Pawns"
layout: "post"
diff: 提高+/省选-
pid: CF382D
tag: []
---

# Ksenia and Pawns

## 题目描述

Ksenia has a chessboard of size $ n×m $ . Each cell of the chessboard contains one of the characters: "<", ">", "^", "v", "\#". The cells that contain character "\#" are blocked. We know that all chessboard cells that touch the border are blocked.

Ksenia is playing with two pawns on this chessboard. Initially, she puts the pawns on the chessboard. One cell of the chessboard can contain two pawns if and only if the cell is blocked. In other cases two pawns can not stand in one cell. The game begins when Ksenia put pawns on the board. In one move, Ksenia moves each pawn to a side adjacent cell in the direction of arrows painted on the cell on which the corresponding pawn sits (if the pawn sits on "\#", it does not move). Assume that Ksenia moves pawns simultaneously (see the second test case).

Of course, Ksenia plays for points. How can one calculate the points per game? Very simply! Let's count how many movements the first pawn made and how many movements the second pawn made, sum these two numbers — it will be the resulting score of the game.

Ksenia wonders: what is the maximum number of points she can earn (for that, she should place the pawns optimally well early in the game). Help her and find that number.

## 输入格式

The first line contains two integers, $ n $ and $ m $ $ (1<=n,m<=2000) $ — the sizes of the board. Each of the following $ n $ lines contains $ m $ characters – the board's description. Each character is one of the characters: "<", ">", "^", "v", "\#".

It is guaranteed that the border cells of the table are blocked cells (with character "\#").

## 输出格式

If Ksenia can get infinitely many points, print -1. Otherwise, print the maximum number of points she can get.

## 样例 #1

### 输入

```
1 1
#

```

### 输出

```
0

```

## 样例 #2

### 输入

```
3 4
####
#&gt;^{}#
####

```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 4
####
#&gt;&lt;#
####

```

### 输出

```
-1
```

## 样例 #4

### 输入

```
7 5
#####
##v##
##v##
#####
##^{}##
##^{}##
#####

```

### 输出

```
4
```

## 样例 #5

### 输入

```
7 5
#####
##v##
##v##
##&lt;##
##^{}##
##^{}##
#####
```

### 输出

```
5
```

