---
title: "Closing ceremony"
layout: "post"
diff: 普及+/提高
pid: CF720A
tag: ['排序', '队列']
---

# Closing ceremony

## 题目描述

The closing ceremony of Squanch Code Cup is held in the big hall with $ n×m $ seats, arranged in $ n $ rows, $ m $ seats in a row. Each seat has two coordinates $ (x,y) $ ( $ 1<=x<=n $ , $ 1<=y<=m $ ).

There are two queues of people waiting to enter the hall: $ k $ people are standing at $ (0,0) $ and $ n·m-k $ people are standing at $ (0,m+1) $ . Each person should have a ticket for a specific seat. If person $ p $ at $ (x,y) $ has ticket for seat $ (x_{p},y_{p}) $ then he should walk $ |x-x_{p}|+|y-y_{p}| $ to get to his seat.

Each person has a stamina — the maximum distance, that the person agrees to walk. You should find out if this is possible to distribute all $ n·m $ tickets in such a way that each person has enough stamina to get to their seat.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 1<=n·m<=10^{4} $ ) — the size of the hall.

The second line contains several integers. The first integer $ k $ ( $ 0<=k<=n·m $ ) — the number of people at $ (0,0) $ . The following $ k $ integers indicate stamina of each person there.

The third line also contains several integers. The first integer $ l $ ( $ l=n·m-k $ ) — the number of people at $ (0,m+1) $ . The following $ l $ integers indicate stamina of each person there.

The stamina of the person is a positive integer less that or equal to $ n+m $ .

## 输出格式

If it is possible to distribute tickets between people in the described manner print "YES", otherwise print "NO".

## 样例 #1

### 输入

```
2 2
3 3 3 2
1 3

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
2 2
3 2 3 3
1 2

```

### 输出

```
NO

```

