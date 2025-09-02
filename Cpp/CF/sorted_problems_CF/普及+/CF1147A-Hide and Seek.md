---
title: "Hide and Seek"
layout: "post"
diff: 普及+/提高
pid: CF1147A
tag: []
---

# Hide and Seek

## 题目描述

Alice and Bob are playing a game on a line with $ n $ cells. There are $ n $ cells labeled from $ 1 $ through $ n $ . For each $ i $ from $ 1 $ to $ n-1 $ , cells $ i $ and $ i+1 $ are adjacent.

Alice initially has a token on some cell on the line, and Bob tries to guess where it is.

Bob guesses a sequence of line cell numbers $ x_1, x_2, \ldots, x_k $ in order. In the $ i $ -th question, Bob asks Alice if her token is currently on cell $ x_i $ . That is, Alice can answer either "YES" or "NO" to each Bob's question.

At most one time in this process, before or after answering a question, Alice is allowed to move her token from her current cell to some adjacent cell. Alice acted in such a way that she was able to answer "NO" to all of Bob's questions.

Note that Alice can even move her token before answering the first question or after answering the last question. Alice can also choose to not move at all.

You are given $ n $ and Bob's questions $ x_1, \ldots, x_k $ . You would like to count the number of scenarios that let Alice answer "NO" to all of Bob's questions.

Let $ (a,b) $ denote a scenario where Alice starts at cell $ a $ and ends at cell $ b $ . Two scenarios $ (a_i, b_i) $ and $ (a_j, b_j) $ are different if $ a_i \neq a_j $ or $ b_i \neq b_j $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \leq n,k \leq 10^5 $ ) — the number of cells and the number of questions Bob asked.

The second line contains $ k $ integers $ x_1, x_2, \ldots, x_k $ ( $ 1 \leq x_i \leq n $ ) — Bob's questions.

## 输出格式

Print a single integer, the number of scenarios that let Alice answer "NO" to all of Bob's questions.

## 说明/提示

The notation $ (i,j) $ denotes a scenario where Alice starts at cell $ i $ and ends at cell $ j $ .

In the first example, the valid scenarios are $ (1, 2), (2, 1), (2, 2), (2, 3), (3, 2), (3, 3), (3, 4), (4, 3), (4, 5) $ . For example, $ (3,4) $ is valid since Alice can start at cell $ 3 $ , stay there for the first three questions, then move to cell $ 4 $ after the last question.

 $ (4,5) $ is valid since Alice can start at cell $ 4 $ , stay there for the first question, the move to cell $ 5 $ for the next two questions. Note that $ (4,5) $ is only counted once, even though there are different questions that Alice can choose to do the move, but remember, we only count each pair of starting and ending positions once.

In the second example, Alice has no valid scenarios.

In the last example, all $ (i,j) $ where $ |i-j| \leq 1 $ except for $ (42, 42) $ are valid scenarios.

## 样例 #1

### 输入

```
5 3
5 1 4

```

### 输出

```
9

```

## 样例 #2

### 输入

```
4 8
1 2 3 4 4 3 2 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
100000 1
42

```

### 输出

```
299997

```

