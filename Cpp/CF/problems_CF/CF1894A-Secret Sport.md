---
title: "Secret Sport"
layout: "post"
diff: 入门
pid: CF1894A
tag: []
---

# Secret Sport

## 题目描述

Let's consider a game in which two players, A and B, participate. This game is characterized by two positive integers, $ X $ and $ Y $ .

The game consists of sets, and each set consists of plays. In each play, exactly one of the players, either A or B, wins. A set ends exactly when one of the players reaches $ X $ wins in the plays of that set. This player is declared the winner of the set. The players play sets until one of them reaches $ Y $ wins in the sets. After that, the game ends, and this player is declared the winner of the entire game.

You have just watched a game but didn't notice who was declared the winner. You remember that during the game, $ n $ plays were played, and you know which player won each play. However, you do not know the values of $ X $ and $ Y $ . Based on the available information, determine who won the entire game — A or B. If there is not enough information to determine the winner, you should also report it.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ $ (1 \leq t \leq 10^4) $ - the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $ n $ $ (1 \leq n \leq 20) $ - the number of plays played during the game.

The second line of each test case contains a string $ s $ of length $ n $ , consisting of characters $ \texttt{A} $ and $ \texttt{B} $ . If $ s_i = \texttt{A} $ , it means that player A won the $ i $ -th play. If $ s_i = \texttt{B} $ , it means that player B won the $ i $ -th play.

It is guaranteed that the given sequence of plays corresponds to at least one valid game scenario, for some values of $ X $ and $ Y $ .

## 输出格式

For each test case, output:

- $ \texttt{A} $ — if player A is guaranteed to be the winner of the game.
- $ \texttt{B} $ — if player B is guaranteed to be the winner of the game.
- $ \texttt{?} $ — if it is impossible to determine the winner of the game.

## 说明/提示

In the first test case, the game could have been played with parameters $ X = 3 $ , $ Y = 1 $ . The game consisted of $ 1 $ set, in which player A won, as they won the first $ 3 $ plays. In this scenario, player A is the winner. The game could also have been played with parameters $ X = 1 $ , $ Y = 3 $ . It can be shown that there are no such $ X $ and $ Y $ values for which player B would be the winner.

In the second test case, player B won all the plays. It can be easily shown that in this case, player B is guaranteed to be the winner of the game.

In the fourth test case, the game could have been played with parameters $ X = 3 $ , $ Y = 3 $ :

- In the first set, $ 3 $ plays were played: AAA. Player A is declared the winner of the set.
- In the second set, $ 3 $ plays were played: AAA. Player A is declared the winner of the set.
- In the third set, $ 5 $ plays were played: AABBB. Player B is declared the winner of the set.
- In the fourth set, $ 5 $ plays were played: AABBB. Player B is declared the winner of the set.
- In the fifth set, $ 4 $ plays were played: BBAB. Player B is declared the winner of the set.

In total, player B was the first player to win $ 3 $ sets. They are declared the winner of the game.

## 样例 #1

### 输入

```
7
5
ABBAA
3
BBB
7
BBAAABA
20
AAAAAAAABBBAABBBBBAB
1
A
13
AAAABABBABBAB
7
BBBAAAA
```

### 输出

```
A
B
A
B
A
B
A
```

