---
title: "Gellyfish and Forget-Me-Not"
layout: "post"
diff: 省选/NOI-
pid: CF2115D
tag: ['贪心', '线性基']
---

# Gellyfish and Forget-Me-Not

## 题目描述

Gellyfish and Flower are playing a game.

The game consists of two arrays of $ n $ integers $ a_1,a_2,\ldots,a_n $ and $ b_1,b_2,\ldots,b_n $ , along with a binary string $ c_1c_2\ldots c_n $ of length $ n $ .

There is also an integer $ x $ which is initialized to $ 0 $ .

The game consists of $ n $ rounds. For $ i = 1,2,\ldots,n $ , the round proceeds as follows:

1. If $ c_i = \mathtt{0} $ , Gellyfish will be the active player. Otherwise, if $ c_i = \mathtt{1} $ , Flower will be the active player.
2. The active player will perform exactly one of the following operations: 
  - Set $ x:=x \oplus a_i $ .
  - Set $ x:=x \oplus b_i $ .

Here, $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Gellyfish wants to minimize the final value of $  x  $ after $  n  $ rounds, while Flower wants to maximize it.

Find the final value of $  x  $ after all $  n  $ rounds if both players play optimally.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the number of rounds of the game.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < 2^{60} $ ).

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 0 \leq b_i < 2^{60} $ ).

The fourth line of each test case contains a binary string $ c $ of length $ n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer — the final value of $  x  $ after all $  n  $ rounds.

## 说明/提示

In the first test case, there's only one round and Gellyfish is the active player of that round. Therefore, she will choose $ a_1 $ , and the final value of $ x $ is $ 0 $ .

In the second test case, Flower will be the active player in both rounds. She will choose $ a_1 $ and $ b_2 $ , and the final value of $ x $ is $ a_1 \oplus b_2 = 15 $ . Flower may also choose $ b_1 $ and $ a_2 $ instead for the same result of $ x=a_2 \oplus b_1 = 15 $ .

In the third test case, $ a_1 = b_1 $ so it doesn't matter what decision Gellyfish makes in the first round. In the second round:

- If Flower chooses $ a_2 $ , then $ x $ will become $ 7 $ . Gellyfish will choose $ b_3 $ in the third round, so the final value of $ x $ will be $ 4 $ .
- Otherwise, Flower chooses $ b_2 $ , then $ x $ will become $ 4 $ . Gellyfish will choose $ a_3 $ in the third round, so the final value of $ x $ will be $ 6 $ .

Flower wants to maximize the final value of $ x $ , so Flower will choose $ b_2 $ in the second round. Therefore, the final value of $ x $ will be $ 6 $ .

## 样例 #1

### 输入

```
5
1
0
2
0
2
12 2
13 3
11
3
6 1 2
6 2 3
010
4
1 12 7 2
4 14 4 2
0111
9
0 5 10 6 6 2 6 2 11
7 3 15 3 6 7 6 7 8
110010010
```

### 输出

```
0
15
6
11
5
```

