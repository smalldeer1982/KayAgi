---
title: "Random Teams"
layout: "post"
diff: 普及/提高-
pid: CF478B
tag: []
---

# Random Teams

## 题目描述

 $ n $ participants of the competition were split into $ m $ teams in some manner so that each team has at least one participant. After the competition each pair of participants from the same team became friends.

Your task is to write a program that will find the minimum and the maximum number of pairs of friends that could have formed by the end of the competition.

## 输入格式

The only line of input contains two integers $ n $ and $ m $ , separated by a single space ( $ 1<=m<=n<=10^{9} $ ) — the number of participants and the number of teams respectively.

## 输出格式

 $ n $ participants of the competition were split into $ m $ teams in some manner so that each team has at least one participant. After the competition each pair of participants from the same team became friends.

Your task is to write a program that will find the minimum and the maximum number of pairs of friends that could have formed by the end of the competition.

## 说明/提示

In the first sample all the participants get into one team, so there will be exactly ten pairs of friends.

In the second sample at any possible arrangement one team will always have two participants and the other team will always have one participant. Thus, the number of pairs of friends will always be equal to one.

In the third sample minimum number of newly formed friendships can be achieved if participants were split on teams consisting of $ 2 $ people, maximum number can be achieved if participants were split on teams of $ 1 $ , $ 1 $ and $ 4 $ people.

## 样例 #1

### 输入

```
5 1

```

### 输出

```
10 10

```

## 样例 #2

### 输入

```
3 2

```

### 输出

```
1 1

```

## 样例 #3

### 输入

```
6 3

```

### 输出

```
3 6

```

