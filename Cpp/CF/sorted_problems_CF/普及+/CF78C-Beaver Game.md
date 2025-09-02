---
title: "Beaver Game"
layout: "post"
diff: 普及+/提高
pid: CF78C
tag: []
---

# Beaver Game

## 题目描述

Two beavers, Timur and Marsel, play the following game.

There are $ n $ logs, each of exactly $ m $ meters in length. The beavers move in turns. For each move a beaver chooses a log and gnaws it into some number (more than one) of equal parts, the length of each one is expressed by an integer and is no less than $ k $ meters. Each resulting part is also a log which can be gnawed in future by any beaver. The beaver that can't make a move loses. Thus, the other beaver wins.

Timur makes the first move. The players play in the optimal way. Determine the winner.

## 输入格式

The first line contains three integers $ n $ , $ m $ , $ k $ ( $ 1<=n,m,k<=10^{9} $ ).

## 输出格式

Print "Timur", if Timur wins, or "Marsel", if Marsel wins. You should print everything without the quotes.

## 说明/提示

In the first sample the beavers only have one log, of $ 15 $ meters in length. Timur moves first. The only move he can do is to split the log into $ 3 $ parts each $ 5 $ meters in length. Then Marsel moves but he can't split any of the resulting logs, as $ k=4 $ . Thus, the winner is Timur.

In the second example the beavers have $ 4 $ logs $ 9 $ meters in length. Timur can't split any of them, so that the resulting parts possessed the length of not less than $ 5 $ meters, that's why he loses instantly.

## 样例 #1

### 输入

```
1 15 4

```

### 输出

```
Timur
```

## 样例 #2

### 输入

```
4 9 5

```

### 输出

```
Marsel
```

