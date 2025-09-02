---
title: "Games with Rectangle"
layout: "post"
diff: 普及+/提高
pid: CF128C
tag: []
---

# Games with Rectangle

## 题目描述

In this task Anna and Maria play the following game. Initially they have a checkered piece of paper with a painted $ n×m $ rectangle (only the border, no filling). Anna and Maria move in turns and Anna starts. During each move one should paint inside the last-painted rectangle a new lesser rectangle (along the grid lines). The new rectangle should have no common points with the previous one. Note that when we paint a rectangle, we always paint only the border, the rectangles aren't filled.

Nobody wins the game — Anna and Maria simply play until they have done $ k $ moves in total. Count the number of different ways to play this game.

## 输入格式

The first and only line contains three integers: $ n,m,k $ ( $ 1<=n,m,k<=1000 $ ).

## 输出格式

Print the single number — the number of the ways to play the game. As this number can be very big, print the value modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

Two ways to play the game are considered different if the final pictures are different. In other words, if one way contains a rectangle that is not contained in the other way.

In the first sample Anna, who performs her first and only move, has only one possible action plan — insert a $ 1×1 $ square inside the given $ 3×3 $ square.

In the second sample Anna has as much as 9 variants: 4 ways to paint a $ 1×1 $ square, 2 ways to insert a $ 1×2 $ rectangle vertically, 2 more ways to insert it horizontally and one more way is to insert a $ 2×2 $ square.

## 样例 #1

### 输入

```
3 3 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4 4 1

```

### 输出

```
9

```

## 样例 #3

### 输入

```
6 7 2

```

### 输出

```
75

```

