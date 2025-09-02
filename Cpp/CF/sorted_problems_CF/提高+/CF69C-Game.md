---
title: "Game"
layout: "post"
diff: 提高+/省选-
pid: CF69C
tag: []
---

# Game

## 题目描述

Kostya 在玩一个游戏，他在游戏内成立了公会，包括他在内，工会有 $k$ 名成员。

## 输入格式

作为工会会长，Kostya 知道每一位成员购买基础神器的记录。他想知道目前每位成员拥有的神器情况。
第 $1$ 行，$4$ 个整数 $k,n,m,q$，表示成员数量，基础神器种类，高级神器种类，购买神器的记录数量。

第 $2 \sim n+1$ 行，每行 $1$ 个字符串，表示每种基础神器的名字。

第 $n+2 \sim n+m+1$ 行，第 $i(1 \le i \le m)$ 行表示一种高级神器的名字和合成规则，如下：
1. $name_i$。这是一个字符串，表示高级神器的名字。
2. $art_{i,j}(1 \le j \le p_i)$。这是一个字符串，表示合成需要的第 $j$ 种基础神器的名字。
3. $num_{i,j}(1 \le j \le p_i)$。这是一个正整数，表示合成需要的第 $j$ 种基础神器的数量。

第 $(n+m+2) \sim (n+m+q+1)$ 行，每行表示一条购买记录，包含 $1$ 个正整数 $x$ 和 $1$ 个字符串 $name$，表示第 $x$ 名成员购买了 $1$ 个名字为 $s$ 的基础神器。

## 输出格式

输出 $k$ 个区域，第 $i(1 \le i \le k)$ 个区域表示第 $i$ 名成员拥有的神器：

首先用 $1$ 行输出成员拥有的神器种类数 $b_i$；
再按名字的字典序输出第 $i$ 名成员拥有的神器。每个神器单独用 $1$ 行输出，先输出神器的名字，再输出神器的数量，中间用空格分隔。

## 说明/提示

对于 $100\%$ 的数据，保证
$1 \le k \le 100$；
$1 \le n \le 50$；
$0 \le m \le 50$；
$1 \le q \le 500$。

## 样例 #1

### 输入

```
2 3 2 5
desolator
refresher
perseverance
vanguard: desolator 1, refresher 1
maelstorm: perseverance 2
1 desolator
2 perseverance
1 refresher
2 desolator
2 perseverance

```

### 输出

```
1
vanguard 1
2
desolator 1
maelstorm 1

```

