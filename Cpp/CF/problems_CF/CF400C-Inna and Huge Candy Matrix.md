---
title: "Inna and Huge Candy Matrix"
layout: "post"
diff: 普及-
pid: CF400C
tag: []
---

# Inna and Huge Candy Matrix

## 题目描述

Inna and Dima decided to surprise Sereja. They brought a really huge candy matrix, it's big even for Sereja! Let's number the rows of the giant matrix from $ 1 $ to $ n $ from top to bottom and the columns — from $ 1 $ to $ m $ , from left to right. We'll represent the cell on the intersection of the $ i $ -th row and $ j $ -th column as $ (i,j) $ . Just as is expected, some cells of the giant candy matrix contain candies. Overall the matrix has $ p $ candies: the $ k $ -th candy is at cell $ (x_{k},y_{k}) $ .

The time moved closer to dinner and Inna was already going to eat $ p $ of her favourite sweets from the matrix, when suddenly Sereja (for the reason he didn't share with anyone) rotated the matrix $ x $ times clockwise by 90 degrees. Then he performed the horizontal rotate of the matrix $ y $ times. And then he rotated the matrix $ z $ times counterclockwise by 90 degrees. The figure below shows how the rotates of the matrix looks like.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF400C/168ff7db18e226cd45113b10da5f3c7fbd5680f5.png)Inna got really upset, but Duma suddenly understood two things: the candies didn't get damaged and he remembered which cells contained Inna's favourite sweets before Sereja's strange actions. Help guys to find the new coordinates in the candy matrix after the transformation Sereja made!

## 输入格式

The first line of the input contains fix integers $ n $ , $ m $ , $ x $ , $ y $ , $ z $ , $ p $ $ (1<=n,m<=10^{9}; 0<=x,y,z<=10^{9}; 1<=p<=10^{5}) $ .

Each of the following $ p $ lines contains two integers $ x_{k} $ , $ y_{k} $ $ (1<=x_{k}<=n; 1<=y_{k}<=m) $ — the initial coordinates of the $ k $ -th candy. Two candies can lie on the same cell.

## 输出格式

For each of the $ p $ candies, print on a single line its space-separated new coordinates.

## 说明/提示

Just for clarity. Horizontal rotating is like a mirroring of the matrix. For matrix:

`<br></br>QWER      REWQ <br></br>ASDF  ->  FDSA<br></br>ZXCV      VCXZ<br></br>`

## 样例 #1

### 输入

```
3 3 3 1 1 9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3

```

### 输出

```
1 3
1 2
1 1
2 3
2 2
2 1
3 3
3 2
3 1

```

