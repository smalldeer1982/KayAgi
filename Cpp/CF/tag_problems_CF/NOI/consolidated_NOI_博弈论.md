---
title: "Two Arrays"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1710E
tag: ['博弈论', '二分图']
---

# Two Arrays

## 题目描述

You are given two arrays of integers $ a_1,a_2,\dots,a_n $ and $ b_1,b_2,\dots,b_m $ .

Alice and Bob are going to play a game. Alice moves first and they take turns making a move.

They play on a grid of size $ n \times m $ (a grid with $ n $ rows and $ m $ columns). Initially, there is a rook positioned on the first row and first column of the grid.

During her/his move, a player can do one of the following two operations:

1. Move the rook to a different cell on the same row or the same column of the current cell. A player cannot move the rook to a cell that has been visited $ 1000 $ times before (i.e., the rook can stay in a certain cell at most $ 1000 $ times during the entire game). Note that the starting cell is considered to be visited once at the beginning of the game.
2. End the game immediately with a score of $ a_r+b_c $ , where $ (r, c) $ is the current cell (i.e., the rook is on the $ r $ -th row and $ c $ -th column).

Bob wants to maximize the score while Alice wants to minimize it. If they both play this game optimally, what is the final score of the game?

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \leq n,m \leq 2 \cdot 10^5 $ ) — the length of the arrays $ a $ and $ b $ (which coincide with the number of rows and columns of the grid).

The second line contains the $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq 5 \cdot 10^8 $ ).

The third line contains the $ m $ integers $ b_1, b_2,\dots, b_n $ ( $ 1 \leq b_i \leq 5 \cdot 10^8 $ ).

## 输出格式

Print a single line containing the final score of the game.

## 说明/提示

In the first test case, Alice moves the rook to $ (2, 1) $ and Bob moves the rook to $ (1, 1) $ . This process will repeat for $ 999 $ times until finally, after Alice moves the rook, Bob cannot move it back to $ (1, 1) $ because it has been visited $ 1000 $ times before. So the final score of the game is $ a_2+b_1=4 $ .

In the second test case, the final score of the game is $ a_3+b_5 $ .

## 样例 #1

### 输入

```
2 1
3 2
2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 5
235499701 451218171 355604420 132973458
365049318 264083156 491406845 62875547 175951751
```

### 输出

```
531556171
```



---

---
title: "Prime Split Game"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1991H
tag: ['博弈论', '数论']
---

# Prime Split Game

## 题目描述

Alice and Bob are playing a game with $ n $ piles of stones, where the $ i $ -th pile has $ a_i $ stones. Players take turns making moves, with Alice going first.

On each move, the player does the following three-step process:

1. Choose an integer $ k $ ( $ 1 \leq k \leq \frac n 2 $ ). Note that the value of $ k $ can be different for different moves.
2. Remove $ k $ piles of stones.
3. Choose another $ k $ piles of stones and split each pile into two piles. The number of stones in each new pile must be a prime number.

The player who is unable to make a move loses.

Determine who will win if both players play optimally.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of piles of stones.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 2 \cdot 10^5 $ ) — the number of stones in the piles.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output "Alice" (without quotes) if Alice wins and "Bob" (without quotes) otherwise.

You can output each letter in any case (upper or lower). For example, the strings "alIcE", "Alice", and "alice" will all be considered identical.

## 说明/提示

In the first test case, there are $ 2 $ piles of stones with $ 2 $ and $ 1 $ stones respectively. Since neither $ 1 $ nor $ 2 $ can be split into two prime numbers, Alice cannot make a move, so Bob wins.

In the second test case, there are $ 3 $ piles of stones with $ 3 $ , $ 5 $ , and $ 7 $ stones respectively. Alice can choose $ k = 1 $ , remove the pile of $ 7 $ stones, and then split the pile of $ 5 $ stones into two piles of prime numbers of stones, $ 2 $ and $ 3 $ . Then, the piles consist of $ 3 $ piles of stones with $ 3 $ , $ 2 $ , and $ 3 $ stones respectively, leaving Bob with no valid moves, so Alice wins.

In the third test case, there are $ 4 $ piles of stones with $ 4 $ , $ 6 $ , $ 8 $ , and $ 10 $ stones respectively. Alice can choose $ k = 2 $ , removing two piles of $ 8 $ and $ 10 $ stones. She splits the pile of $ 4 $ stones into two piles of prime numbers of stones, $ 2 $ and $ 2 $ , and the pile of $ 6 $ stones into two piles of $ 3 $ and $ 3 $ stones. Then, Bob has no valid moves, so Alice wins.

In the fourth test case, there are $ 5 $ piles of stones, each containing $ 8 $ stones. It can be shown that if both players play optimally, Bob will win.

## 样例 #1

### 输入

```
4
2
2 1
3
3 5 7
4
4 6 8 10
5
8 8 8 8 8
```

### 输出

```
Bob
Alice
Alice
Bob
```



---

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



---

---
title: "Grid Game 3-angle"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2045F
tag: ['博弈论', '数论']
---

# Grid Game 3-angle

## 题目描述

Anda 和 Kamu 决定玩一个叫作「网格游戏」的游戏，并请你来做裁判。作为裁判，你需要设置一个大小为 $N$ 的三角形网格。这个网格共有 $N$ 行（从 $1$ 到 $N$ 编号）。第 $r$ 行有 $r$ 个格子，第 $r$ 行的第 $c$ 个格子记作 $(r, c)$。

![示例图1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045F/d40475d9abd66fd4b8b1753d7ed7b9ab45f87e16.png)

在开始游戏前，有 $M$ 个不同的格子被选中（编号从 $1$ 到 $M$），并在格子 $(R_i, C_i)$ 上放置 $A_i$ 颗石子。随后，你给 Anda 和 Kamu 一个整数 $K$，游戏随即开始。

玩家 Anda 和 Kamu 轮流进行游戏，由 Anda 先手。每个玩家在他的回合中必须：

- 选择一个至少包含一颗石子的格子 $(r, c)$；
- 从该格子中移除至少一颗但不超过 $K$ 颗石子；
- 对于每个满足 $r + 1 \leq x \leq \min(N, r + K)$ 且 $c \leq y \leq c + x - r$ 的格子 $(x, y)$，可以向其中添加零颗或多颗，但不超过 $K$ 颗的石子。

下图显示了当 $K = 3$ 时，可以添加石子的所有可能格子。左图选择了 $(2, 1)$，右图选择了 $(4, 3)$。

![示例图2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045F/b2d9c6a56735a1903fa39837671da9d8b4751eac.png)

无法进行有效回合（即因为没有足够的石子）的一方将输掉比赛，而对方将获胜。请判断，如果双方都采取最佳策略，谁将赢得比赛。

## 输入格式

本题包含多组测试数据。第一行是一个整数 $T$（$1 \leq T \leq 100$），表示测试数据的组数。

每组测试数据的第一行包含三个整数 $N$、$M$ 和 $K$（$1 \leq N \leq 10^9; 1 \leq M, K \leq 200\,000$）。接下来的 $M$ 行中，每行包含三个整数 $R_i$、$C_i$ 和 $A_i$（$1 \leq C_i \leq R_i \leq N; 1 \leq A_i \leq 10^9$）。每对 $(R_i, C_i)$ 都是独特的。

所有测试数据中 $M$ 的总和不超过 $200\,000$。

## 输出格式

对于每组测试数据，输出一行字符串，表示如果双方都采取最佳策略，哪位玩家将赢得比赛。如果 Anda 获胜，输出“Anda”；否则，输出“Kamu”。

## 示例说明

对于第一个例子，Anda 在第一回合将从格子 $(1, 1)$ 移除所有石子，然后在 $(2, 1)$ 添加三颗石子。此时，唯一剩余的有石子的格子是 $(2, 1)$，其中有五颗石子，因此 Kamu 必须在该回合中从中移除石子。无论 Kamu 移除多少，Anda 都能在随后一回合中移除剩下的所有石子，从而赢得比赛。

对于第二个例子，Kamu 可以通过模仿 Anda 的所有操作，即使 Anda 无法完成回合，使得自己成为胜利者。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
2 2 4
1 1 3
2 1 2
100 2 1
4 1 10
4 4 10
10 5 2
1 1 4
3 1 2
4 2 5
2 2 1
5 3 4
```

### 输出

```
Anda
Kamu
Anda
```



---

