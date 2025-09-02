---
title: "Team"
layout: "post"
diff: 普及/提高-
pid: CF401C
tag: []
---

# Team

## 题目描述

Now it's time of Olympiads. Vanya and Egor decided to make his own team to take part in a programming Olympiad. They've been best friends ever since primary school and hopefully, that can somehow help them in teamwork.

For each team Olympiad, Vanya takes his play cards with numbers. He takes only the cards containing numbers 1 and 0. The boys are very superstitious. They think that they can do well at the Olympiad if they begin with laying all the cards in a row so that:

- there wouldn't be a pair of any side-adjacent cards with zeroes in a row;
- there wouldn't be a group of three consecutive cards containing numbers one.

Today Vanya brought $ n $ cards with zeroes and $ m $ cards with numbers one. The number of cards was so much that the friends do not know how to put all those cards in the described way. Help them find the required arrangement of the cards or else tell the guys that it is impossible to arrange cards in such a way.

## 输入格式

The first line contains two integers: $ n $ ( $ 1<=n<=10^{6} $ ) — the number of cards containing number 0; $ m $ ( $ 1<=m<=10^{6} $ ) — the number of cards containing number 1.

## 输出格式

In a single line print the required sequence of zeroes and ones without any spaces. If such sequence is impossible to obtain, print -1.

## 样例 #1

### 输入

```
1 2

```

### 输出

```
101

```

## 样例 #2

### 输入

```
4 8

```

### 输出

```
110110110101

```

## 样例 #3

### 输入

```
4 10

```

### 输出

```
11011011011011

```

## 样例 #4

### 输入

```
1 5

```

### 输出

```
-1

```

