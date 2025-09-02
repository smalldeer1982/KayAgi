---
title: "Computer Game"
layout: "post"
diff: 普及/提高-
pid: CF1183C
tag: []
---

# Computer Game

## 题目描述

Vova is playing a computer game. There are in total $ n $ turns in the game and Vova really wants to play all of them. The initial charge of his laptop battery (i.e. the charge before the start of the game) is $ k $ .

During each turn Vova can choose what to do:

- If the current charge of his laptop battery is strictly greater than $ a $ , Vova can just play, and then the charge of his laptop battery will decrease by $ a $ ;
- if the current charge of his laptop battery is strictly greater than $ b $ ( $ b<a $ ), Vova can play and charge his laptop, and then the charge of his laptop battery will decrease by $ b $ ;
- if the current charge of his laptop battery is less than or equal to $ a $ and $ b $ at the same time then Vova cannot do anything and loses the game.

Vova wants to complete the game (Vova can complete the game if after each of $ n $ turns the charge of the laptop battery is strictly greater than $ 0 $ ). Among all possible ways to complete the game, Vova wants to choose the one where the number of turns when he just plays is the maximum possible. It is possible that Vova cannot complete the game at all.

Your task is to find out the maximum possible number of turns Vova can just play or report that Vova cannot complete the game.

You have to answer $ q $ independent queries.

## 输入格式

The first line of the input contains one integer $ q $ ( $ 1 \le q \le 10^5 $ ) — the number of queries. Each query is presented by a single line.

The only line of the query contains four integers $ k, n, a $ and $ b $ ( $ 1 \le k, n \le 10^9, 1 \le b < a \le 10^9 $ ) — the initial charge of Vova's laptop battery, the number of turns in the game and values $ a $ and $ b $ , correspondingly.

## 输出格式

For each query print one integer: -1 if Vova cannot complete the game or the maximum number of turns Vova can just play otherwise.

## 说明/提示

In the first example query Vova can just play $ 4 $ turns and spend $ 12 $ units of charge and then one turn play and charge and spend $ 2 $ more units. So the remaining charge of the battery will be $ 1 $ .

In the second example query Vova cannot complete the game because even if he will play and charge the battery during each turn then the charge of the notebook battery will be $ 0 $ after the last turn.

## 样例 #1

### 输入

```
6
15 5 3 2
15 5 4 3
15 5 2 1
15 5 5 1
16 7 5 2
20 5 7 3

```

### 输出

```
4
-1
5
2
0
1

```

