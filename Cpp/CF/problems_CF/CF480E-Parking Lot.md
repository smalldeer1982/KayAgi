---
title: "Parking Lot"
layout: "post"
diff: 提高+/省选-
pid: CF480E
tag: []
---

# Parking Lot

## 题目描述

Petya's been bored at work and he is killing the time by watching the parking lot at the office. The parking lot looks from above like an $ n×m $ table (a cell of the table corresponds to a single parking spot). Some spots in the parking lot are taken, others are empty.

Petya watches cars riding into the parking lot one by one. After a car settles down at the parking spot, Petya amuzes himself by counting what maximum square of empty spots (i.e. a square subtable) can be seen on the parking lot if we look at it from above. Also, he takes notes of the square's size (side length) in his notebook.

You task is: given the state of the parking lot at the initial moment of time and the information about where the arriving cars park, restore what Petya wrote in his notebook. It is midday, so nobody leaves the lot.

## 输入格式

Petya's been bored at work and he is killing the time by watching the parking lot at the office. The parking lot looks from above like an $ n×m $ table (a cell of the table corresponds to a single parking spot). Some spots in the parking lot are taken, others are empty.

Petya watches cars riding into the parking lot one by one. After a car settles down at the parking spot, Petya amuzes himself by counting what maximum square of empty spots (i.e. a square subtable) can be seen on the parking lot if we look at it from above. Also, he takes notes of the square's size (side length) in his notebook.

You task is: given the state of the parking lot at the initial moment of time and the information about where the arriving cars park, restore what Petya wrote in his notebook. It is midday, so nobody leaves the lot.

## 输出格式

Print $ k $ integers — the length of the side of the maximum square of empty spots after the corresponding car has entered the parking lot.

## 样例 #1

### 输入

```
7 8 4
........
X.....X.
........
........
.X......
........
........
1 5
6 4
3 5
4 6

```

### 输出

```
5
4
4
3

```

