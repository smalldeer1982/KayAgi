---
title: "Sky Full of Stars"
layout: "post"
diff: 省选/NOI-
pid: CF997C
tag: []
---

# Sky Full of Stars

## 题目描述

On one of the planets of Solar system, in Atmosphere University, many students are fans of bingo game.

It is well known that one month on this planet consists of $ n^2 $ days, so calendars, represented as square matrix $ n $ by $ n $ are extremely popular.

Weather conditions are even more unusual. Due to the unique composition of the atmosphere, when interacting with sunlight, every day sky takes one of three colors: blue, green or red.

To play the bingo, you need to observe the sky for one month — after each day, its cell is painted with the color of the sky in that day, that is, blue, green or red.

At the end of the month, students examine the calendar. If at least one row or column contains only cells of one color, that month is called lucky.

Let's call two colorings of calendar different, if at least one cell has different colors in them. It is easy to see that there are $ 3^{n \cdot n} $ different colorings. How much of them are lucky? Since this number can be quite large, print it modulo $ 998244353 $ .

## 输入格式

The first and only line of input contains a single integer $ n $ ( $ 1 \le n \le 1000\,000 $ ) — the number of rows and columns in the calendar.

## 输出格式

Print one number — number of lucky colorings of the calendar modulo $ 998244353 $

## 说明/提示

In the first sample any coloring is lucky, since the only column contains cells of only one color.

In the second sample, there are a lot of lucky colorings, in particular, the following colorings are lucky:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF997C/ac5b00cad39330de8487d369f95c472d2789d588.png)While these colorings are not lucky:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF997C/d7e778adcf49c4573cc1d5ca5e208443325ff00a.png)

## 样例 #1

### 输入

```
1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2

```

### 输出

```
63

```

## 样例 #3

### 输入

```
3

```

### 输出

```
9933

```

