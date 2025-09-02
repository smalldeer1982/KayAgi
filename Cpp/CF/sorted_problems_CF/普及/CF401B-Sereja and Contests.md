---
title: "Sereja and Contests"
layout: "post"
diff: 普及/提高-
pid: CF401B
tag: []
---

# Sereja and Contests

## 题目描述

Sereja is a coder and he likes to take part in Codesorfes rounds. However, Uzhland doesn't have good internet connection, so Sereja sometimes skips rounds.

Codesorfes has rounds of two types: $ Div1 $ (for advanced coders) and $ Div2 $ (for beginner coders). Two rounds, $ Div1 $ and $ Div2 $ , can go simultaneously, ( $ Div1 $ round cannot be held without $ Div2 $ ) in all other cases the rounds don't overlap in time. Each round has a unique identifier — a positive integer. The rounds are sequentially (without gaps) numbered with identifiers by the starting time of the round. The identifiers of rounds that are run simultaneously are different by one, also the identifier of the $ Div1 $ round is always greater.

Sereja is a beginner coder, so he can take part only in rounds of $ Div2 $ type. At the moment he is taking part in a $ Div2 $ round, its identifier equals to $ x $ . Sereja remembers very well that he has taken part in exactly $ k $ rounds before this round. Also, he remembers all identifiers of the rounds he has taken part in and all identifiers of the rounds that went simultaneously with them. Sereja doesn't remember anything about the rounds he missed.

Sereja is wondering: what minimum and what maximum number of $ Div2 $ rounds could he have missed? Help him find these two numbers.

## 输入格式

The first line contains two integers: $ x $ $ (1<=x<=4000) $ — the round Sereja is taking part in today, and $ k $ $ (0<=k&lt;4000) $ — the number of rounds he took part in.

Next $ k $ lines contain the descriptions of the rounds that Sereja took part in before. If Sereja took part in one of two simultaneous rounds, the corresponding line looks like: "1 $ num_{2} $ $ num_{1} $ " (where $ num_{2} $ is the identifier of this $ Div2 $ round, $ num_{1} $ is the identifier of the $ Div1 $ round). It is guaranteed that $ num_{1}-num_{2}=1 $ . If Sereja took part in a usual $ Div2 $ round, then the corresponding line looks like: "2 $ num $ " (where $ num $ is the identifier of this $ Div2 $ round). It is guaranteed that the identifiers of all given rounds are less than $ x $ .

## 输出格式

Print in a single line two integers — the minimum and the maximum number of rounds that Sereja could have missed.

## 说明/提示

In the second sample we have unused identifiers of rounds 1, 6, 7. The minimum number of rounds Sereja could have missed equals to 2. In this case, the round with the identifier 1 will be a usual $ Div2 $ round and the round with identifier $ 6 $ will be synchronous with the $ Div1 $ round.

The maximum number of rounds equals $ 3 $ . In this case all unused identifiers belong to usual $ Div2 $ rounds.

## 样例 #1

### 输入

```
3 2
2 1
2 2

```

### 输出

```
0 0
```

## 样例 #2

### 输入

```
9 3
1 2 3
2 8
1 4 5

```

### 输出

```
2 3
```

## 样例 #3

### 输入

```
10 0

```

### 输出

```
5 9
```

