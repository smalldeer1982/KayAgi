---
title: "Bit Game (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2027E2
tag: ['博弈论', '数位 DP', 'SG 函数']
---

# Bit Game (Hard Version)

## 题目描述

This is the hard version of this problem. The only difference is that you need to output the number of choices of games where Bob wins in this version, where the number of stones in each pile are not fixed. You must solve both versions to be able to hack.

Alice and Bob are playing a familiar game where they take turns removing stones from $ n $ piles. Initially, there are $ x_i $ stones in the $ i $ -th pile, and it has an associated value $ a_i $ . A player can take $ d $ stones away from the $ i $ -th pile if and only if both of the following conditions are met:

- $ 1 \le d \le a_i $ , and
- $ x \, \& \, d = d $ , where $ x $ is the current number of stones in the $ i $ -th pile and $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

The player who cannot make a move loses, and Alice goes first.

You're given the $ a_i $ values of each pile, but the number of stones in the $ i $ -th pile has not been determined yet. For the $ i $ -th pile, $ x_i $ can be any integer between $ 1 $ and $ b_i $ , inclusive. That is, you can choose an array $ x_1, x_2, \ldots, x_n $ such that the condition $ 1 \le x_i \le b_i $ is satisfied for all piles.

Your task is to count the number of games where Bob wins if both players play optimally. Two games are considered different if the number of stones in any pile is different, i.e., the arrays of $ x $ differ in at least one position.

Since the answer can be very large, please output the result modulo $ 10^9 + 7 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

The first line of each test case contains $ n $ ( $ 1 \le n \le 10^4 $ ) — the number of piles.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i < 2^{30} $ ).

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i < 2^{30} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^4 $ .

## 输出格式

Output a single integer, the number of games where Bob wins, modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case, no matter which values of $ x_2 $ and $ x_3 $ we choose, the second and third piles will always be chosen exactly once before no more stones can be taken from them. If $ x_1 = 2 $ , then no stones can be taken from it, so Bob will make the last move. If $ x_1 = 1 $ or $ x_1 = 3 $ , then exactly one move can be made on that pile, so Alice will make the last move. So Bob wins when $ x = [2, 1, 1] $ or $ x = [2, 1, 2] $ or $ x = [2, 2, 1] $ or $ x = [2, 2, 2] $ .

In the second test case, Bob wins when $ x_1 = 14 $ or $ x_1 = 30 $ by removing $ 14 - k $ stones, where $ k $ is the number of stones Alice removes on her turn. Bob also wins when $ x_1 = 16 $ or $ x_1 = 32 $ since Alice does not have any moves to begin with.

## 样例 #1

### 输入

```
7
3
1 2 3
3 2 2
1
13
45
5
5 4 7 8 6
4 4 5 5 5
4
6 4 8 8
12 13 14 12
3
92856133 46637598 12345678
29384774 73775896 87654321
2
65 12
110 31
4
677810235 275091182 428565855 720629731
74522416 889934149 3394714 230851724
```

### 输出

```
4
4
0
6552
722019507
541
665443265
```

