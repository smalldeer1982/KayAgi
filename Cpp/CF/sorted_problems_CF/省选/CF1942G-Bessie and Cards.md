---
title: "Bessie and Cards"
layout: "post"
diff: 省选/NOI-
pid: CF1942G
tag: []
---

# Bessie and Cards

## 题目描述

[Second Dark Matter Battle - Pokemon Super Mystery Dungeon](https://soundcloud.com/decabat/second-dark-matter-battle?in=decabat/sets/best-of-pokemon-super-mystery)

⠀



Bessie has recently started playing a famous card game. In the game, there is only one deck of cards, consisting of $ a $ "draw $ 0 $ " cards, $ b $ "draw $ 1 $ " cards, $ c $ "draw $ 2 $ " cards, and $ 5 $ special cards. At the start of the game, all cards are in the randomly shuffled deck.

Bessie starts the game by drawing the top $ 5 $ cards of the deck. She may then play "draw $ x $ " cards from the hand to draw the next $ x $ cards from the top of the deck. Note that every card can only be played once, special cards cannot be played, and if Bessie uses a "draw $ 2 $ " card when there is only $ 1 $ card remaining in the deck, then she simply draws that remaining card. Bessie wins if she draws all $ 5 $ special cards.

Since Bessie is not very good at math problems, she wants you to find the probability that she wins, given that the deck is shuffled randomly over all $ (a + b + c + 5)! $ possible orderings. It can be shown that this answer can always be expressed as a fraction $ \frac{p}{q} $ where $ p $ and $ q $ are coprime integers. Output $ p \cdot q^{-1} $ modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case contains three integers $ a $ , $ b $ , and $ c $ ( $ 0 \le a, b, c \le 2 \cdot 10^5 $ ) – the number of draw $ 0 $ cards, draw $ 1 $ cards, and draw $ 2 $ cards, respectively.

It is guaranteed that the sum of $ a $ over all test cases does not exceed $ 2 \cdot 10^5 $ , the sum of $ b $ over all test cases does not exceed $ 2 \cdot 10^5 $ , and the sum of $ c $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the probability that Bessie wins, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first case, we have $ 1 $ of each type of "draw" card and $ 5 $ special cards. There are $ 30\,720 $ starting decks where Bessie will win by drawing the top $ 5 $ cards and $ 40\,320 $ starting decks in total. Thus, the probability of Bessie winning is $ \frac{30\,720}{40\,320} = \frac{16}{21} $ .

One example of a winning starting deck is, top to bottom,

1. "Special",
2. "Draw $ 1 $ ",
3. "Special",
4. "Special",
5. "Draw $ 0 $ ",
6. "Draw $ 2 $ ",
7. "Special",
8. "Special".

One example of a losing starting deck is:

1. "Special",
2. "Draw $ 1 $ ",
3. "Special",
4. "Special",
5. "Draw $ 0 $ ",
6. "Special",
7. "Special",
8. "Draw $ 2 $ ".

## 样例 #1

### 输入

```
4
1 1 1
0 0 0
5 3 7
3366 1434 1234
```

### 输出

```
903173463
1
35118742
398952013
```

