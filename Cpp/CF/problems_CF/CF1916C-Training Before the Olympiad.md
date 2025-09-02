---
title: "Training Before the Olympiad"
layout: "post"
diff: 普及/提高-
pid: CF1916C
tag: ['博弈论']
---

# Training Before the Olympiad

## 题目描述

Masha and Olya have an important team olympiad coming up soon. In honor of this, Masha, for warm-up, suggested playing a game with Olya:

There is an array $ a $ of size $ n $ . Masha goes first, and the players take turns. Each move is described by the following sequence of actions:

 $ \bullet $ If the size of the array is $ 1 $ , the game ends.

 $ \bullet $ The player who is currently playing chooses two different indices $ i $ , $ j $ ( $ 1 \le i, j \le |a| $ ), and performs the following operation — removes $ a_i $ and $ a_j $ from the array and adds to the array a number equal to $ \lfloor \frac{a_i + a_j}{2} \rfloor \cdot 2 $ . In other words, first divides the sum of the numbers $ a_i $ , $ a_j $ by $ 2 $ rounding down, and then multiplies the result by $ 2 $ .

Masha aims to maximize the final number, while Olya aims to minimize it.

Masha and Olya decided to play on each non-empty prefix of the initial array $ a $ , and asked for your help.

For each $ k = 1, 2, \ldots, n $ , answer the following question. Let only the first $ k $ elements of the array $ a $ be present in the game, with indices $ 1, 2, \ldots, k $ respectively. What number will remain at the end with optimal play by both players?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the size of the array.

The second line contains $ n $ integers $ a_1,a_2, \ldots,a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the array on which Masha and Olya play.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ n $ integers. The $ k $ -th of these numbers should be equal to the number that will remain at the end with optimal play by both players, on the array consisting of the first $ k $ elements of the array $ a $ .

## 说明/提示

In the third test case, for a prefix of length $ 1 $ , the answer is $ 3 $ . For a prefix of length $ 2 $ , Masha has only one move, so the answer is $ 12 $ . For a prefix of length $ 3 $ , Masha has three possible moves: she chooses $ 3 $ and $ 10 $ , then the final number is $ 22 $ , $ 3 $ and $ 11 $ , then the final number is $ 24 $ , $ 10 $ and $ 11 $ , then the final number is $ 22 $ , so Masha will choose $ 3 $ and $ 11 $ and get $ 24 $ .

## 样例 #1

### 输入

```
4
1
31
6
6 3 7 2 5 4
3
3 10 11
5
7 13 11 19 1
```

### 输出

```
31 
6 8 16 18 22 26 
3 12 24 
7 20 30 48 50
```

