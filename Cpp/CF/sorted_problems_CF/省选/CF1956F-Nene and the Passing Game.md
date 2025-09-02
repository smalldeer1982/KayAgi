---
title: "Nene and the Passing Game"
layout: "post"
diff: 省选/NOI-
pid: CF1956F
tag: ['图论', '并查集']
---

# Nene and the Passing Game

## 题目描述

Nene is training her team as a basketball coach. Nene's team consists of $ n $ players, numbered from $ 1 $ to $ n $ . The $ i $ -th player has an arm interval $ [l_i,r_i] $ . Two players $ i $ and $ j $ ( $ i \neq j $ ) can pass the ball to each other if and only if $ |i-j|\in[l_i+l_j,r_i+r_j] $ (here, $ |x| $ denotes the absolute value of $ x $ ).

Nene wants to test the cooperation ability of these players. In order to do this, she will hold several rounds of assessment.

- In each round, Nene will select a sequence of players $ p_1,p_2,\ldots,p_m $ such that players $ p_i $ and $ p_{i+1} $ can pass the ball to each other for all $ 1 \le i < m $ . The length of the sequence $ m $ can be chosen by Nene. Each player can appear in the sequence $ p_1,p_2,\ldots,p_m $ multiple times or not appear in it at all.
- Then, Nene will throw a ball to player $ p_1 $ , player $ p_1 $ will pass the ball to player $ p_2 $ and so on... Player $ p_m $ will throw a ball away from the basketball court so it can no longer be used.

As a coach, Nene wants each of $ n $ players to appear in at least one round of assessment. Since Nene has to go on a date after school, Nene wants you to calculate the minimum number of rounds of assessment needed to complete the task.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 2\cdot 10^5 $ ). The description of test cases follows.

The first line contains a single integer $ n $ ( $ 1 \le n \le 2\cdot 10^6 $ ) — the number of players.

The $ i $ -th of the next $ n $ lines contains two integers $ l_i $ and $ r_i $ ( $ 1\leq l_i\leq r_i\leq n $ ) — the arm interval of the $ i $ -th player.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^6 $ .

## 输出格式

For each test case, output one integer — the minimum number of rounds of assessment Nene needs to complete her work.

## 说明/提示

In the first two test cases, Nene can host two rounds of assessment: one with $ p=[1] $ and one with $ p=[2] $ . It can be shown that hosting one round of assessment is not enough, so the answer is $ 2 $ .

In the third test case, Nene can host two rounds of assessment: one with $ p=[1,3] $ and one with $ p=[2] $ . Player $ 1 $ can pass the ball to player $ 3 $ as $ |3-1|=2 \in [1+1,3+3] $ . It can be shown that hosting one round of assessment is not enough, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
5
2
1 1
1 1
2
1 1
2 2
3
1 3
1 3
1 3
5
1 1
2 2
1 5
2 2
1 1
6
1 2
5 5
2 3
2 3
2 2
1 2
```

### 输出

```
2
2
2
1
3
```

