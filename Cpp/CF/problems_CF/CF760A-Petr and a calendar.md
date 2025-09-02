---
title: "Petr and a calendar"
layout: "post"
diff: 入门
pid: CF760A
tag: []
---

# Petr and a calendar

## 题目描述

Petr wants to make a calendar for current month. For this purpose he draws a table in which columns correspond to weeks (a week is seven consequent days from Monday to Sunday), rows correspond to weekdays, and cells contain dates. For example, a calendar for January 2017 should look like on the picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF760A/70f7bb298739f0018d24699e43e0bdba58d6965c.png)Petr wants to know how many columns his table should have given the month and the weekday of the first date of that month? Assume that the year is non-leap.

## 输入格式

The only line contain two integers $ m $ and $ d $ ( $ 1<=m<=12 $ , $ 1<=d<=7 $ ) — the number of month (January is the first month, December is the twelfth) and the weekday of the first date of this month ( $ 1 $ is Monday, $ 7 $ is Sunday).

## 输出格式

Print single integer: the number of columns the table should have.

## 说明/提示

The first example corresponds to the January 2017 shown on the picture in the statements.

In the second example $ 1 $ -st January is Monday, so the whole month fits into $ 5 $ columns.

In the third example $ 1 $ -st November is Saturday and $ 5 $ columns is enough.

## 样例 #1

### 输入

```
1 7

```

### 输出

```
6

```

## 样例 #2

### 输入

```
1 1

```

### 输出

```
5

```

## 样例 #3

### 输入

```
11 6

```

### 输出

```
5

```

