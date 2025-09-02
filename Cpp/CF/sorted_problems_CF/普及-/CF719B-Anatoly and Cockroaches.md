---
title: "Anatoly and Cockroaches"
layout: "post"
diff: 普及-
pid: CF719B
tag: []
---

# Anatoly and Cockroaches

## 题目描述

Anatoly lives in the university dorm as many other students do. As you know, cockroaches are also living there together with students. Cockroaches might be of two colors: black and red. There are $ n $ cockroaches living in Anatoly's room.

Anatoly just made all his cockroaches to form a single line. As he is a perfectionist, he would like the colors of cockroaches in the line to alternate. He has a can of black paint and a can of red paint. In one turn he can either swap any two cockroaches, or take any single cockroach and change it's color.

Help Anatoly find out the minimum number of turns he needs to make the colors of cockroaches in the line alternate.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the number of cockroaches.

The second line contains a string of length $ n $ , consisting of characters 'b' and 'r' that denote black cockroach and red cockroach respectively.

## 输出格式

Print one integer — the minimum number of moves Anatoly has to perform in order to make the colors of cockroaches in the line to alternate.

## 说明/提示

In the first sample, Anatoly has to swap third and fourth cockroaches. He needs $ 1 $ turn to do this.

In the second sample, the optimum answer is to paint the second and the fourth cockroaches red. This requires $ 2 $ turns.

In the third sample, the colors of cockroaches in the line are alternating already, thus the answer is $ 0 $ .

## 样例 #1

### 输入

```
5
rbbrr

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
bbbbb

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3
rbr

```

### 输出

```
0

```

