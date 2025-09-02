---
title: "Black Square"
layout: "post"
diff: 普及/提高-
pid: CF828B
tag: []
---

# Black Square

## 题目描述

Polycarp has a checkered sheet of paper of size $ n×m $ . Polycarp painted some of cells with black, the others remained white. Inspired by Malevich's "Black Square", Polycarp wants to paint minimum possible number of white cells with black so that all black cells form a square.

You are to determine the minimum possible number of cells needed to be painted black so that the black cells form a black square with sides parallel to the painting's sides. All the cells that do not belong to the square should be white. The square's side should have positive length.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=100 $ ) — the sizes of the sheet.

The next $ n $ lines contain $ m $ letters 'B' or 'W' each — the description of initial cells' colors. If a letter is 'B', then the corresponding cell is painted black, otherwise it is painted white.

## 输出格式

Print the minimum number of cells needed to be painted black so that the black cells form a black square with sides parallel to the painting's sides. All the cells that do not belong to the square should be white. If it is impossible, print -1.

## 说明/提示

In the first example it is needed to paint $ 5 $ cells — $ (2,2) $ , $ (2,3) $ , $ (3,2) $ , $ (3,3) $ and $ (4,2) $ . Then there will be a square with side equal to three, and the upper left corner in $ (2,2) $ .

In the second example all the cells are painted black and form a rectangle, so it's impossible to get a square.

In the third example all cells are colored white, so it's sufficient to color any cell black.

## 样例 #1

### 输入

```
5 4
WWWW
WWWB
WWWB
WWBB
WWWW

```

### 输出

```
5

```

## 样例 #2

### 输入

```
1 2
BB

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
3 3
WWW
WWW
WWW

```

### 输出

```
1

```

