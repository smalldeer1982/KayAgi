---
title: "Colored Balls"
layout: "post"
diff: 省选/NOI-
pid: CF792E
tag: []
---

# Colored Balls

## 题目描述

There are $ n $ boxes with colored balls on the table. Colors are numbered from $ 1 $ to $ n $ . $ i $ -th box contains $ a_{i} $ balls, all of which have color $ i $ . You have to write a program that will divide all balls into sets such that:

- each ball belongs to exactly one of the sets,
- there are no empty sets,
- there is no set containing two (or more) balls of different colors (each set contains only balls of one color),
- there are no two sets such that the difference between their sizes is greater than $ 1 $ .

Print the minimum possible number of sets.

## 输入格式

The first line contains one integer number $ n $ ( $ 1<=n<=500 $ ).

The second line contains $ n $ integer numbers $ a_{1},a_{2},...\ ,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print one integer number — the minimum possible number of sets.

## 说明/提示

In the first example the balls can be divided into sets like that: one set with $ 4 $ balls of the first color, two sets with $ 3 $ and $ 4 $ balls, respectively, of the second color, and two sets with $ 4 $ balls of the third color.

## 样例 #1

### 输入

```
3
4 7 8

```

### 输出

```
5

```

## 样例 #2

### 输入

```
2
2 7

```

### 输出

```
4

```

