---
title: "Petya and Square"
layout: "post"
diff: 普及/提高-
pid: CF112B
tag: []
---

# Petya and Square

## 题目描述

Little Petya loves playing with squares. Mum bought him a square $ 2n×2n $ in size. Petya marked a cell inside the square and now he is solving the following task.

The task is to draw a broken line that would go along the grid lines and that would cut the square into two equal parts. The cutting line should not have any common points with the marked cell and the resulting two parts should be equal up to rotation.

Petya wants to determine whether it is possible to cut the square in the required manner given the sizes of the square side and the coordinates of the marked cell. Help him.

## 输入格式

The first line contains three space-separated integers $ 2n $ , $ x $ and $ y $ ( $ 2<=2n<=100,1<=x,y<=2n $ ), representing the length of a square's side and the coordinates of the marked cell. It is guaranteed that $ 2n $ is even.

The coordinates of the marked cell are represented by a pair of numbers $ x $ $ y $ , where $ x $ represents the number of the row and $ y $ represents the number of the column. The rows and columns are numbered by consecutive integers from $ 1 $ to $ 2n $ . The rows are numbered from top to bottom and the columns are numbered from the left to the right.

## 输出格式

If the square is possible to cut, print "YES", otherwise print "NO" (without the quotes).

## 说明/提示

A sample test from the statement and one of the possible ways of cutting the square are shown in the picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF112B/73a8bd680c4d33b060b29ddcf134c8221469d9f6.png)

## 样例 #1

### 输入

```
4 1 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
2 2 2

```

### 输出

```
NO

```

