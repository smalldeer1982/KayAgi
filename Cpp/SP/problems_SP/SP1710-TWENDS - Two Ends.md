---
title: "TWENDS - Two Ends"
layout: "post"
diff: 难度0
pid: SP1710
tag: []
---

# TWENDS - Two Ends

## 题目描述

在双人游戏“Two Ends”中，牌的数目是一个偶数。每张卡片上有一个正整数。每轮游戏中，玩家轮流从任意一端取出一张牌，并将其放在自己的牌堆中。牌上整数之和高的玩家获胜。现在有一个策略——每次都选择一张牌上点数最大的牌，我们称之为贪婪策略。但是，这有时候也会使你输掉游戏，如下面的例子所示：（如果第一个玩家选择$3$而不是$4$，那么她会赢。）

$3$ $2$ $10$ $4$

现在后手玩家使用贪婪策略，先手玩家可以自由使用任何策略。您需要确定先手玩家的分数和后手玩家的分数之间的最大差值。

## 输入格式

将有多组测试用例。每组测试用例占一行，表示一次游戏。每行将以一个偶数$n$开头，后跟$n$个正整数。$n=0$表示输入结束。假设$n$不超过$1000$，且列表中的数字之和不超过$1000000$。

## 输出格式

````In game m, the greedy strategy might lose by as many as p points.````

其中，$m$是游戏次数（从$1$开始），$p$是当后手玩家使用贪婪策略时，先手玩家的分数和后手玩家的分数之间的最大差值。当采用贪婪策略时，每轮游戏中玩家总是在牌的两端中取点数较大的一张牌。当两端牌的点数相同时，取左端的牌。

## 样例 #1

### 输入

```
4 3 2 10 4
8 1 2 3 4 5 6 7 8
8 2 2 1 5 3 8 7 3
0
```

### 输出

```
In game 1, the greedy strategy might lose by as many as 7 points.
In game 2, the greedy strategy might lose by as many as 4 points.
In game 3, the greedy strategy might lose by as many as 5 points.
```

