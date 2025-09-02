---
title: "Tournament"
layout: "post"
diff: 普及+/提高
pid: CF27B
tag: []
---

# Tournament

## 题目描述

The tournament «Sleepyhead-2010» in the rapid falling asleep has just finished in Berland. $ n $ best participants from the country have participated in it. The tournament consists of games, each of them is a match between two participants. $ n·(n-1)/2 $ games were played during the tournament, and each participant had a match with each other participant.

The rules of the game are quite simple — the participant who falls asleep first wins. The secretary made a record of each game in the form « $ x_{i} $ $ y_{i} $ », where $ x_{i} $ and $ y_{i} $ are the numbers of participants. The first number in each pair is a winner (i.e. $ x_{i} $ is a winner and $ y_{i} $ is a loser). There is no draws.

Recently researches form the «Institute Of Sleep» have found that every person is characterized by a value $ p_{j} $ — the speed of falling asleep. The person who has lower speed wins. Every person has its own value $ p_{j} $ , constant during the life.

It is known that all participants of the tournament have distinct speeds of falling asleep. Also it was found that the secretary made records about all the games except one. You are to find the result of the missing game.

## 输入格式

The first line contains one integer $ n $ ( $ 3<=n<=50 $ ) — the number of participants. The following $ n·(n-1)/2-1 $ lines contain the results of the games. Each game is described in a single line by two integers $ x_{i},y_{i} $ ( $ 1<=x_{i},y_{i}<=n,x_{i}≠y_{i} $ ), where $ x_{i} $ и $ y_{i} $ are the numbers of the opponents in this game. It is known that during the tournament each of the $ n $ participants played $ n-1 $ games, one game with each other participant.

## 输出格式

Output two integers $ x $ and $ y $ — the missing record. If there are several solutions, output any of them.

## 样例 #1

### 输入

```
4
4 2
4 1
2 3
2 1
3 1

```

### 输出

```
4 3

```

