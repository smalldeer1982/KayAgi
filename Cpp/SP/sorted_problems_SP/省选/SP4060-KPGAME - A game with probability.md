---
title: "KPGAME - A game with probability"
layout: "post"
diff: 省选/NOI-
pid: SP4060
tag: []
---

# KPGAME - A game with probability

## 题目描述

### 描述
Alice 和 Bob 在玩一个游戏。有 $n$ 个石子在这里，Alice 和 Bob 轮流投掷硬币，如果正面朝上，则从 $n$ 个石子中取出一个石子，否则不做任何事。取到最后一颗石子的人胜利。Alice 在投掷硬币时有 $p$ 的概率投掷出他想投的一面，同样，Bob 有 $q$ 的概率投掷出他相投的一面。

现在 Alice 先手投掷硬币，假设他们都想赢得游戏，问你 Alice 胜利的概率为多少。

## 输入格式

第一行一个正整数 $t$，表示数据组数。
对于每组数据，一行三个数 $n,p,q$。

## 输出格式

对于每组数据输出一行一个实数，表示 Alice 胜利的概率，保留 $6$ 位小数。

### 样例输入

1
1 0.5 0.5

### 样例输出

0.666667

## 说明/提示

$1\leqslant t\leqslant 50$；

$0.5\leqslant p,q\leqslant 0.99999999$；

对于 $100\%$ 的数据 $1\leqslant n\leqslant 99999999$。

翻译 by @[Dying_Light](/user/51477) @[aiyougege](/user/39067)

## 样例 #1

### 输入

```
1
1 0.5 0.5
```

### 输出

```
0.666666667
```

