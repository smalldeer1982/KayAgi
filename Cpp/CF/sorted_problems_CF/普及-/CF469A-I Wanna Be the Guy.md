---
title: "I Wanna Be the Guy"
layout: "post"
diff: 普及-
pid: CF469A
tag: []
---

# I Wanna Be the Guy

## 题目描述

There is a game called "I Wanna Be the Guy", consisting of $ n $ levels. Little X and his friend Little Y are addicted to the game. Each of them wants to pass the whole game.

Little X can pass only $ p $ levels of the game. And Little Y can pass only $ q $ levels of the game. You are given the indices of levels Little X can pass and the indices of levels Little Y can pass. Will Little X and Little Y pass the whole game, if they cooperate each other?

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=100 $ ).

The next line contains an integer $ p $ $ (0<=p<=n) $ at first, then follows $ p $ distinct integers $ a_{1},a_{2},...,a_{p} $ $ (1<=a_{i}<=n) $ . These integers denote the indices of levels Little X can pass. The next line contains the levels Little Y can pass in the same format. It's assumed that levels are numbered from 1 to $ n $ .

## 输出格式

If they can pass all the levels, print "I become the guy.". If it's impossible, print "Oh, my keyboard!" (without the quotes).

## 说明/提示

In the first sample, Little X can pass levels \[1 2 3\], and Little Y can pass level \[2 4\], so they can pass all the levels both.

In the second sample, no one can pass level 4.

## 样例 #1

### 输入

```
4
3 1 2 3
2 2 4

```

### 输出

```
I become the guy.

```

## 样例 #2

### 输入

```
4
3 1 2 3
2 2 3

```

### 输出

```
Oh, my keyboard!

```

