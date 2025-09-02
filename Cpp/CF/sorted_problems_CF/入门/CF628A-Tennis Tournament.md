---
title: "Tennis Tournament"
layout: "post"
diff: 入门
pid: CF628A
tag: []
---

# Tennis Tournament

## 题目描述

A tennis tournament with $ n $ participants is running. The participants are playing by an olympic system, so the winners move on and the losers drop out.

The tournament takes place in the following way (below, $ m $ is the number of the participants of the current round):

- let $ k $ be the maximal power of the number $ 2 $ such that $ k<=m $ ,
- $ k $ participants compete in the current round and a half of them passes to the next round, the other $ m-k $ participants pass to the next round directly,
- when only one participant remains, the tournament finishes.

Each match requires $ b $ bottles of water for each participant and one bottle for the judge. Besides $ p $ towels are given to each participant for the whole tournament.

Find the number of bottles and towels needed for the tournament.

Note that it's a tennis tournament so in each match two participants compete (one of them will win and the other will lose).

## 输入格式

The only line contains three integers $ n,b,p $ ( $ 1<=n,b,p<=500 $ ) — the number of participants and the parameters described in the problem statement.

## 输出格式

Print two integers $ x $ and $ y $ — the number of bottles and towels need for the tournament.

## 说明/提示

In the first example will be three rounds:

1. in the first round will be two matches and for each match $ 5 $ bottles of water are needed (two for each of the participants and one for the judge),
2. in the second round will be only one match, so we need another $ 5 $ bottles of water,
3. in the third round will also be only one match, so we need another $ 5 $ bottles of water.

So in total we need $ 20 $ bottles of water.

In the second example no participant will move on to some round directly.

## 样例 #1

### 输入

```
5 2 3

```

### 输出

```
20 15

```

## 样例 #2

### 输入

```
8 2 4

```

### 输出

```
35 32

```

