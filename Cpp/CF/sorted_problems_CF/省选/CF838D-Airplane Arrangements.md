---
title: "Airplane Arrangements"
layout: "post"
diff: 省选/NOI-
pid: CF838D
tag: []
---

# Airplane Arrangements

## 题目描述

There is an airplane which has $ n $ rows from front to back. There will be $ m $ people boarding this airplane.

This airplane has an entrance at the very front and very back of the plane.

Each person has some assigned seat. It is possible for multiple people to have the same assigned seat. The people will then board the plane one by one starting with person $ 1 $ . Each person can independently choose either the front entrance or back entrance to enter the plane.

When a person walks into the plane, they will walk directly to their assigned seat. Then, while the seat they’re looking at is occupied, they will keep moving one space in the same direction. A passenger will get angry if they reach the end of the row without finding their assigned seat.

Find the number of ways to assign tickets to the passengers and board the plane without anyone getting angry. Two ways are different if there exists a passenger who chose a different entrance in both ways, or the assigned seat is different. Print this count modulo $ 10^{9}+7 $ .

## 输入格式

The first line of input will contain two integers $ n,m $ ( $ 1<=m<=n<=1000000 $ ), the number of seats, and the number of passengers, respectively.

## 输出格式

Print a single number, the number of ways, modulo $ 10^{9}+7 $ .

## 说明/提示

Here, we will denote a passenger by which seat they were assigned, and which side they came from (either "F" or "B" for front or back, respectively).

For example, one valid way is 3B, 3B, 3B (i.e. all passengers were assigned seat 3 and came from the back entrance). Another valid way would be 2F, 1B, 3F.

One invalid way would be 2B, 2B, 2B, since the third passenger would get to the front without finding a seat.

## 样例 #1

### 输入

```
3 3

```

### 输出

```
128

```

