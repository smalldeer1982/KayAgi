---
title: "Birthday"
layout: "post"
diff: 省选/NOI-
pid: CF623D
tag: []
---

# Birthday

## 题目描述

A MIPT student named Misha has a birthday today, and he decided to celebrate it in his country house in suburban Moscow. $ n $ friends came by, and after a typical party they decided to play blind man's buff.

The birthday boy gets blindfolded and the other players scatter around the house. The game is played in several rounds. In each round, Misha catches exactly one of his friends and has to guess who it is. The probability of catching the $ i $ -th friend does not change between rounds and is equal to $ p_{i} $ percent (as we know, it is directly proportional to the amount of alcohol consumed by the $ i $ -th friend) and $ p_{1}+p_{2}+...+p_{n}=100 $ holds. Misha has no information about who he caught. After Misha makes an attempt to guess the caught person, the round ends. Even then, Misha isn't told whether he guessed correctly, and a new round begins.

The game ends when Misha guesses every friend at least once, that is, there exists such set of rounds $ k_{1},k_{2},...,k_{n} $ , that during round number $ k_{i} $ Misha caught the $ i $ -th friend and guessed him. Misha wants to minimize the expectation of the number of rounds of the game. Despite the fact that at any point in the game Misha has no information about who he has already guessed, his friends are honest, and if they see that the condition for the end of the game is fulfilled, the game ends immediately. Find the expectation of the number of rounds in the game if Misha plays optimally.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=100 $ ) — the number of Misha's friends.

The second line contains $ n $ integers $ p_{i} $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF623D/fd6e5969e56f94c89cb7f2299474741ff2a9fe1c.png)), giving the probability to catch the $ i $ -th friend in one particular round in percent.

## 输出格式

Print a single real value — the expectation of the number of rounds provided that Misha plays optimally. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF623D/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 说明/提示

The optimal strategy in the first sample is to guess friends alternately.

## 样例 #1

### 输入

```
2
50 50

```

### 输出

```
5.0000000000

```

## 样例 #2

### 输入

```
4
50 20 20 10

```

### 输出

```
39.2846263444

```

