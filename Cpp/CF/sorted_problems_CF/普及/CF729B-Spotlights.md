---
title: "Spotlights"
layout: "post"
diff: 普及/提高-
pid: CF729B
tag: []
---

# Spotlights

## 题目描述

Theater stage is a rectangular field of size $ n×m $ . The director gave you the stage's plan which actors will follow. For each cell it is stated in the plan if there would be an actor in this cell or not.

You are to place a spotlight on the stage in some good position. The spotlight will project light in one of the four directions (if you look at the stage from above) — left, right, up or down. Thus, the spotlight's position is a cell it is placed to and a direction it shines.

A position is good if two conditions hold:

- there is no actor in the cell the spotlight is placed to;
- there is at least one actor in the direction the spotlight projects.

Count the number of good positions for placing the spotlight. Two positions of spotlight are considered to be different if the location cells or projection direction differ.

## 输入格式

The first line contains two positive integers $ n $ and $ m $ ( $ 1<=n,m<=1000 $ ) — the number of rows and the number of columns in the plan.

The next $ n $ lines contain $ m $ integers, $ 0 $ or $ 1 $ each — the description of the plan. Integer $ 1 $ , means there will be an actor in the corresponding cell, while $ 0 $ means the cell will remain empty. It is guaranteed that there is at least one actor in the plan.

## 输出格式

Print one integer — the number of good positions for placing the spotlight.

## 说明/提示

In the first example the following positions are good:

1. the (1, 1) cell and right direction;
2. the (1, 1) cell and down direction;
3. the (1, 3) cell and left direction;
4. the (1, 3) cell and down direction;
5. the (1, 4) cell and left direction;
6. the (2, 2) cell and left direction;
7. the (2, 2) cell and up direction;
8. the (2, 2) and right direction;
9. the (2, 4) cell and left direction.

Therefore, there are $ 9 $ good positions in this example.

## 样例 #1

### 输入

```
2 4
0 1 0 0
1 0 1 0

```

### 输出

```
9

```

## 样例 #2

### 输入

```
4 4
0 0 0 0
1 0 0 1
0 1 1 0
0 1 0 0

```

### 输出

```
20

```

