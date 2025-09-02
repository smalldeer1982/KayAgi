---
title: "Planting Trees"
layout: "post"
diff: 普及/提高-
pid: CF45J
tag: []
---

# Planting Trees

## 题目描述

Vasya is a Greencode wildlife preservation society proponent. One day he found an empty field nobody owned, divided it into $ n×m $ squares and decided to plant a forest there. Vasya will plant $ nm $ trees of all different heights from $ 1 $ to $ nm $ . For his forest to look more natural he wants any two trees growing in the side neighbouring squares to have the absolute value of difference in heights to be strictly more than 1. Help Vasya: make the plan of the forest planting for which this condition is fulfilled.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ( $ 1<=n,m<=100 $ ) — the number of rows and columns on Vasya's field

## 输出格式

If there's no solution, print -1. Otherwise, print $ n $ lines containing $ m $ numbers each — the trees' planting plan. In every square of the plan the height of a tree that should be planted on this square should be written. If there are several solutions to that problem, print any of them.

## 样例 #1

### 输入

```
2 3

```

### 输出

```
3 6 2
5 1 4

```

## 样例 #2

### 输入

```
2 1

```

### 输出

```
-1

```

