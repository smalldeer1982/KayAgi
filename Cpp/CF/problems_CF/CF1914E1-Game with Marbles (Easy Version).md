---
title: "Game with Marbles (Easy Version)"
layout: "post"
diff: 普及/提高-
pid: CF1914E1
tag: ['贪心', '博弈论']
---

# Game with Marbles (Easy Version)

## 题目描述

The easy and hard versions of this problem differ only in the constraints on the number of test cases and $ n $ . In the easy version, the number of test cases does not exceed $ 10^3 $ , and $ n $ does not exceed $ 6 $ .

Recently, Alice and Bob were given marbles of $ n $ different colors by their parents. Alice has received $ a_1 $ marbles of color $ 1 $ , $ a_2 $ marbles of color $ 2 $ ,..., $ a_n $ marbles of color $ n $ . Bob has received $ b_1 $ marbles of color $ 1 $ , $ b_2 $ marbles of color $ 2 $ , ..., $ b_n $ marbles of color $ n $ . All $ a_i $ and $ b_i $ are between $ 1 $ and $ 10^9 $ .

After some discussion, Alice and Bob came up with the following game: players take turns, starting with Alice. On their turn, a player chooses a color $ i $ such that both players have at least one marble of that color. The player then discards one marble of color $ i $ , and their opponent discards all marbles of color $ i $ . The game ends when there is no color $ i $ such that both players have at least one marble of that color.

The score in the game is the difference between the number of remaining marbles that Alice has and the number of remaining marbles that Bob has at the end of the game. In other words, the score in the game is equal to $ (A-B) $ , where $ A $ is the number of marbles Alice has and $ B $ is the number of marbles Bob has at the end of the game. Alice wants to maximize the score, while Bob wants to minimize it.

Calculate the score at the end of the game if both players play optimally.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^3 $ ) — the number of test cases.

Each test case consists of three lines:

- the first line contains a single integer $ n $ ( $ 2 \le n \le 6 $ ) — the number of colors;
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ), where $ a_i $ is the number of marbles of the $ i $ -th color that Alice has;
- the third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le 10^9 $ ), where $ b_i $ is the number of marbles of the $ i $ -th color that Bob has.

## 输出格式

For each test case, output a single integer — the score at the end of the game if both Alice and Bob act optimally.

## 说明/提示

In the first example, one way to achieve a score of $ 1 $ is as follows:

1. Alice chooses color $ 1 $ , discards $ 1 $ marble. Bob also discards $ 1 $ marble;
2. Bob chooses color $ 3 $ , discards $ 1 $ marble. Alice also discards $ 1 $ marble;
3. Alice chooses color $ 2 $ , discards $ 1 $ marble, and Bob discards $ 2 $ marble.

As a result, Alice has $ a = [3, 1, 0] $ remaining, and Bob has $ b = [0, 0, 3] $ remaining. The score is $ 3 + 1 - 3 = 1 $ .

It can be shown that neither Alice nor Bob can achieve a better score if both play optimally.

In the second example, Alice can first choose color $ 1 $ , then Bob will choose color $ 4 $ , after which Alice will choose color $ 2 $ , and Bob will choose color $ 3 $ . It can be shown that this is the optimal game.

## 样例 #1

### 输入

```
5
3
4 2 1
1 2 4
4
1 20 1 20
100 15 10 20
5
1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1
3
5 6 5
2 1 7
6
3 2 4 2 5 5
9 4 7 9 2 5
```

### 输出

```
1
-9
2999999997
8
-6
```

