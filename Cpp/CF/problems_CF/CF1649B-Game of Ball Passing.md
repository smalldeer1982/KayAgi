---
title: "Game of Ball Passing"
layout: "post"
diff: 普及-
pid: CF1649B
tag: []
---

# Game of Ball Passing

## 题目描述

Daniel is watching a football team playing a game during their training session. They want to improve their passing skills during that session.

The game involves $ n $ players, making multiple passes towards each other. Unfortunately, since the balls were moving too fast, after the session Daniel is unable to know how many balls were involved during the game. The only thing he knows is the number of passes delivered by each player during all the session.

Find the minimum possible amount of balls that were involved in the game.

## 输入格式

There are several test cases in the input data. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 5 \cdot 10^4 $ ) — the number of test cases. This is followed by the test cases description.

The first line of each test case contains one integer $ n $ ( $ 2 \leq n \leq 10^5 $ ) — the number of players.

The second line of the test case contains a sequence of integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq 10^9 $ ), where $ a_i $ is the number of passes delivered by the $ i $ -th player.

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 10^5 $ .

## 输出格式

For each test case print a single integer — the answer to the problem.

## 说明/提示

In the first test case, with the only ball, the game can go like this:

 $ 2 \rightarrow 1 \rightarrow 3 \rightarrow 4 \rightarrow 1 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 2 \rightarrow 3 \rightarrow 2 $ .

In the second test case, there is no possible way to play the game with only one ball. One possible way to play with two balls:

 $ 2 \rightarrow 1 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 1 $ .

 $ 2 \rightarrow 3 \rightarrow 2 \rightarrow 1 $

In the third example, there were no passes, so $ 0 $ balls are possible.

## 样例 #1

### 输入

```
4
4
2 3 3 2
3
1 5 2
2
0 0
4
1000000000 1000000000 1000000000 1000000000
```

### 输出

```
1
2
0
1
```

