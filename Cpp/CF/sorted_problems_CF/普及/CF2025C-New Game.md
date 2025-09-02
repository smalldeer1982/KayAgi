---
title: "New Game"
layout: "post"
diff: 普及/提高-
pid: CF2025C
tag: ['双指针 two-pointer']
---

# New Game

## 题目描述

There's a new game Monocarp wants to play. The game uses a deck of $ n $ cards, where the $ i $ -th card has exactly one integer $ a_i $ written on it.

At the beginning of the game, on the first turn, Monocarp can take any card from the deck. During each subsequent turn, Monocarp can take exactly one card that has either the same number as on the card taken on the previous turn or a number that is one greater than the number on the card taken on the previous turn.

In other words, if on the previous turn Monocarp took a card with the number $ x $ , then on the current turn he can take either a card with the number $ x $ or a card with the number $ x + 1 $ . Monocarp can take any card which meets that condition, regardless of its position in the deck.

After Monocarp takes a card on the current turn, it is removed from the deck.

According to the rules of the game, the number of distinct numbers written on the cards that Monocarp has taken must not exceed $ k $ .

If, after a turn, Monocarp cannot take a card without violating the described rules, the game ends.

Your task is to determine the maximum number of cards that Monocarp can take from the deck during the game, given that on the first turn he can take any card from the deck.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 200\,000 $ ) — the number of cards in the deck and the maximum number of distinct numbers that can be written on the cards that Monocarp takes.

The second line contains a sequence of integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^{9} $ ), where $ a_i $ is the number written on the $ i $ -th card.

Additional constraint of the input: the sum of $ n $ over all test cases doesn't exceed $ 200\,000 $ .

## 输出格式

For each test case, print the maximum number of cards that Monocarp can take from the deck during the game, given that on the first turn he can take any card from the deck.

## 说明/提示

In the first example, Monocarp needs to take any of the cards with the number $ 3 $ . On the next two turns, he needs to take the two remaining cards with the number $ 3 $ . On the next three turns, he needs to take three cards with the number $ 4 $ . After that, Monocarp will not be able to take any more cards from the deck, and he will have $ 6 $ cards.

## 样例 #1

### 输入

```
4
10 2
5 2 4 3 4 3 4 5 3 2
5 1
10 11 10 11 10
9 3
4 5 4 4 6 5 4 4 6
3 2
1 3 1
```

### 输出

```
6
3
9
2
```

