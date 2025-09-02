---
title: "Tavas in Kansas"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF536D
tag: []
---

# Tavas in Kansas

## 题目描述

Tavas lives in Kansas. Kansas has $ n $ cities numbered from 1 to $ n $ connected with $ m $ bidirectional roads. We can travel from any city to any other city via these roads. Kansas is as strange as Tavas. So there may be a road between a city and itself or more than one road between two cities.

Tavas invented a game and called it "Dashti". He wants to play Dashti with his girlfriends, Nafas.

In this game, they assign an arbitrary integer value to each city of Kansas. The value of $ i $ -th city equals to $ p_{i} $ .

During the game, Tavas is in city $ s $ and Nafas is in city $ t $ . They play in turn and Tavas goes first. A player in his/her turn, must choose a non-negative integer $ x $ and his/her score increases by the sum of values of all cities with (shortest) distance no more than $ x $ from his/her city. Each city may be used once, or in the other words, after first time a player gets score from a city, city score becomes zero.

There is an additional rule: the player must choose $ x $ such that he/she gets the point of at least one city that was not used before. Note that city may initially have value 0, such city isn't considered as been used at the beginning of the game, i. e. each player may use it to fullfill this rule.

The game ends when nobody can make a move.

A player's score is the sum of the points he/she earned during the game. The winner is the player with greater score, or there is a draw if players score the same value. Both players start game with zero points.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF536D/9654f3510f1e9019608228c20f14073d277d65a9.png)If Tavas wins, he'll break his girlfriend's heart, and if Nafas wins, Tavas will cry. But if their scores are equal, they'll be happy and Tavas will give Nafas flowers.

They're not too emotional after all, so they'll play optimally. Your task is to tell Tavas what's going to happen after the game ends.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 2<=n<=2000 $ , $ n-1<=m<=10^{5} $ ).

The second line of input contains two integers $ s $ and $ t $ ( $ 1<=s,t<=n $ , $ s≠t $ ).

The next line contains $ n $ integers $ p_{1},p_{2},...,p_{n} $ separated by spaces ( $ |p_{i}|<=10^{9} $ ).

The next $ m $ lines contain the roads. Each line contains three integers $ v,u,w $ and it means that there's an road with length $ w $ between cities $ v $ and $ u $ ( $ 1<=u,v<=n $ and $ 0<=w<=10^{9} $ ). The road may lead from the city to itself, there may be several roads between each pair of cities.

## 输出格式

If Tavas wins, print "Break a heart". If Nafas wins print "Cry" and if nobody wins (i. e. the game ended with draw) print "Flowers".

## 样例 #1

### 输入

```
4 4
1 2
3 2 5 -11
1 4 2
3 4 2
3 1 5
3 2 1

```

### 输出

```
Cry

```

## 样例 #2

### 输入

```
5 4
1 2
2 2 -5 -4 6
1 2 4
2 3 5
2 4 2
4 5 2

```

### 输出

```
Break a heart

```

## 样例 #3

### 输入

```
2 1
1 2
-5 -5
1 2 10

```

### 输出

```
Flowers

```

