---
title: "GCD Guessing Game"
layout: "post"
diff: 提高+/省选-
pid: UVA1521
tag: ['贪心', '素数判断,质数,筛法', '最大公约数 gcd']
---

# GCD Guessing Game

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4267

[PDF](https://uva.onlinejudge.org/external/15/p1521.pdf)


## 输入格式

**本题在单测试点内有多组测试数据，请读入到 EOF。**

给定 $n (2 \leq n \leq 10^4)$，玩一个猜数游戏。目标为 $p (p \in [1, n])$。

每一次可以猜一个数 $x$，会告诉你 $\gcd(x, p)$。

求在 **最坏** 情况下，至少需要猜几次 **保证** 猜出 $p$。

## 输出格式

对于每一组数据，输出答案并换行。

## 说明/提示

Translated by @[longgod](/user/39675), retranslated by @[Carroty_cat](/user/912750).

## 样例 #1

### 输入

```
6
```

### 输出

```
2
```

