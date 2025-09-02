---
title: "Table Tennis Game 2"
layout: "post"
diff: 普及/提高-
pid: CF765C
tag: []
---

# Table Tennis Game 2

## 题目描述

Misha and Vanya have played several table tennis sets. Each set consists of several serves, each serve is won by one of the players, he receives one point and the loser receives nothing. Once one of the players scores exactly $ k $ points, the score is reset and a new set begins.

Across all the sets Misha scored $ a $ points in total, and Vanya scored $ b $ points. Given this information, determine the maximum number of sets they could have played, or that the situation is impossible.

Note that the game consisted of several complete sets.

## 输入格式

The first line contains three space-separated integers $ k $ , $ a $ and $ b $ ( $ 1<=k<=10^{9} $ , $ 0<=a,b<=10^{9} $ , $ a+b&gt;0 $ ).

## 输出格式

If the situation is impossible, print a single number -1. Otherwise, print the maximum possible number of sets.

## 说明/提示

Note that the rules of the game in this problem differ from the real table tennis game, for example, the rule of "balance" (the winning player has to be at least two points ahead to win a set) has no power within the present problem.

## 样例 #1

### 输入

```
11 11 5

```

### 输出

```
1

```

## 样例 #2

### 输入

```
11 2 3

```

### 输出

```
-1

```

