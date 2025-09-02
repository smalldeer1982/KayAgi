---
title: "Gellyfish and Tricolor Pansy"
layout: "post"
diff: 入门
pid: CF2116A
tag: ['贪心']
---

# Gellyfish and Tricolor Pansy

## 题目描述

Gellyfish and Flower are playing a game called "Duel".

Gellyfish has $ a $ HP, while Flower has $ b $ HP.

Each of them has a knight. Gellyfish's knight has $ c $ HP, while Flower's knight has $ d $ HP.

They will play a game in rounds until one of the players wins. For $ k = 1, 2, \ldots $ in this order, they will perform the following actions:

- If $ k $ is odd and Gellyfish's knight is alive:
  - Gellyfish's knight can attack Flower and reduce $ b $ by $ 1 $ . If $ b \leq 0 $ , Gellyfish wins. Or,
  - Gellyfish's knight can attack Flower's knight and reduce $ d $ by $ 1 $ . If $ d \leq 0 $ , Flower's knight dies.
- If $ k $ is even and Flower's knight is alive:
  - Flower's knight can attack Gellyfish and reduce $ a $ by $ 1 $ . If $ a \leq 0 $ , Flower wins. Or,
  - Flower's knight can attack Gellyfish's knight and reduce $ c $ by $ 1 $ . If $ c \leq 0 $ , Gellyfish's knight dies.

As one of the smartest people in the world, you want to tell them who will win before the game. Assume both players play optimally.

It can be proven that the game will never end in a draw. That is, one player has a strategy to end the game in a finite number of moves.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first and only line of each test case contains four integers $ a $ , $ b $ , $ c $ , $ d $ ( $ 1 \leq a, b, c, d \leq 10^9 $ ) — the HP of Gellyfish, the HP of Flower, the HP of Gellyfish's knight, and the HP of Flower's knight, respectively.

## 输出格式

For each test case, if Flower will win, output "Flower", otherwise output "Gellyfish".

## 说明/提示

In the first test case, Gellyfish has only $ 1 $ HP. Therefore, no matter what Gellyfish does in the first round, Flower's knight will attack Gellyfish in the second round, allowing Flower to win.

In the second test case, Flower's knight has only $ 1 $ HP. Gellyfish will attack Flower's knight in the first round. Then Flower's knight will no longer be able to attack, allowing Gellyfish to win.

## 样例 #1

### 输入

```
5
1 2 3 4
100 999 1 1
10 20 10 30
12 14 13 11
998 244 353 107
```

### 输出

```
Flower
Gellyfish
Flower
Gellyfish
Gellyfish
```

