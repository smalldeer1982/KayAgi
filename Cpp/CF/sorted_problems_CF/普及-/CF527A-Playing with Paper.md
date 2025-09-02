---
title: "Playing with Paper"
layout: "post"
diff: 普及-
pid: CF527A
tag: []
---

# Playing with Paper

## 题目描述

One day Vasya was sitting on a not so interesting Maths lesson and making an origami from a rectangular $ a $ mm $ × $ $ b $ mm sheet of paper ( $ a>b $ ). Usually the first step in making an origami is making a square piece of paper from the rectangular sheet by folding the sheet along the bisector of the right angle, and cutting the excess part.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527A/919759a22ff5597b60d204c65faf22c2233113ef.png)After making a paper ship from the square piece, Vasya looked on the remaining $ (a-b) $ mm $ × $ $ b $ mm strip of paper. He got the idea to use this strip of paper in the same way to make an origami, and then use the remainder (if it exists) and so on. At the moment when he is left with a square piece of paper, he will make the last ship from it and stop.

Can you determine how many ships Vasya will make during the lesson?

## 输入格式

The first line of the input contains two integers $ a $ , $ b $ ( $ 1<=b<a<=10^{12} $ ) — the sizes of the original sheet of paper.

## 输出格式

Print a single integer — the number of ships that Vasya will make.

## 说明/提示

Pictures to the first and second sample test.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527A/8a10deb3e516fda81e76aae552290cb4cf3649c8.png)

## 样例 #1

### 输入

```
2 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
10 7

```

### 输出

```
6

```

## 样例 #3

### 输入

```
1000000000000 1

```

### 输出

```
1000000000000

```

