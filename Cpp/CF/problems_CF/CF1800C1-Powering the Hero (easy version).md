---
title: "Powering the Hero (easy version)"
layout: "post"
diff: 普及-
pid: CF1800C1
tag: []
---

# Powering the Hero (easy version)

## 题目描述

This is an easy version of the problem. It differs from the hard one only by constraints on $ n $ and $ t $ .

There is a deck of $ n $ cards, each of which is characterized by its power. There are two types of cards:

- a hero card, the power of such a card is always equal to $ 0 $ ;
- a bonus card, the power of such a card is always positive.

You can do the following with the deck:

- take a card from the top of the deck;
- if this card is a bonus card, you can put it on top of your bonus deck or discard;
- if this card is a hero card, then the power of the top card from your bonus deck is added to his power (if it is not empty), after that the hero is added to your army, and the used bonus discards.

Your task is to use such actions to gather an army with the maximum possible total power.

## 输入格式

The first line of input data contains single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases in the test.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 5000 $ ) — the number of cards in the deck.

The second line of each test case contains $ n $ integers $ s_1, s_2, \dots, s_n $ ( $ 0 \le s_i \le 10^9 $ ) — card powers in top-down order.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5000 $ .

## 输出格式

Output $ t $ numbers, each of which is the answer to the corresponding test case — the maximum possible total power of the army that can be achieved.

## 说明/提示

In the first sample, you can take bonuses $ 1 $ and $ 2 $ . Both hero cards will receive $ 3 $ power. If you take all the bonuses, one of them will remain unused.

In the second sample, the hero's card on top of the deck cannot be powered up, and the rest can be powered up with $ 2 $ and $ 3 $ bonuses and get $ 6 $ total power.

In the fourth sample, you can take bonuses $ 1 $ , $ 2 $ , $ 3 $ , $ 5 $ and skip the bonus $ 6 $ , then the hero $ 4 $ will be enhanced with a bonus $ 3 $ by $ 5 $ , and the hero $ 7 $ with a bonus $ 5 $ by $ 4 $ . $ 4+5=9 $ .

## 样例 #1

### 输入

```
5
5
3 3 3 0 0
6
0 3 3 0 0 3
7
1 2 3 0 4 5 0
7
1 2 5 0 4 3 0
5
3 1 0 0 4
```

### 输出

```
6
6
8
9
4
```

