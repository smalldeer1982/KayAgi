---
title: "Turtle"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1239E
tag: []
---

# Turtle

## 题目描述

Kolya has a turtle and a field of size $ 2 \times n $ . The field rows are numbered from $ 1 $ to $ 2 $ from top to bottom, while the columns are numbered from $ 1 $ to $ n $ from left to right.

Suppose in each cell of the field there is a lettuce leaf. The energy value of lettuce leaf in row $ i $ and column $ j $ is equal to $ a_{i,j} $ . The turtle is initially in the top left cell and wants to reach the bottom right cell. The turtle can only move right and down and among all possible ways it will choose a way, maximizing the total energy value of lettuce leaves (in case there are several such paths, it will choose any of them).

Kolya is afraid, that if turtle will eat too much lettuce, it can be bad for its health. So he wants to reorder lettuce leaves in the field, so that the energetic cost of leaves eaten by turtle will be minimized.

## 输入格式

The first line contains an integer $ n $ ( $ 2 \le n \le 25 $ ) — the length of the field.

The second line contains $ n $ integers $ a_{1, i} $ ( $ 0 \le a_{1, i} \le 50\,000 $ ), the energetic cost of lettuce leaves in the first row of the field.

The third line contains $ n $ integers $ a_{2, i} $ ( $ 0 \le a_{2, i} \le 50\,000 $ ), the energetic cost of lettuce leaves in the second row of the field.

## 输出格式

Print two lines with $ n $ integers in each — the optimal reordering of lettuce from the input data.

In case there are several optimal ways to reorder lettuce, print any of them.

## 说明/提示

In the first example, after reordering, the turtle will eat lettuce with total energetic cost $ 1+4+2 = 7 $ .

In the second example, the turtle will eat lettuce with energetic cost equal $ 0 $ .

In the third example, after reordering, the turtle will eat lettuce with total energetic cost equal $ 1 $ .

## 样例 #1

### 输入

```
2
1 4
2 3

```

### 输出

```
1 3 
4 2 

```

## 样例 #2

### 输入

```
3
0 0 0
0 0 0

```

### 输出

```
0 0 0 
0 0 0 

```

## 样例 #3

### 输入

```
3
1 0 1
0 0 0

```

### 输出

```
0 0 1
0 1 0

```

