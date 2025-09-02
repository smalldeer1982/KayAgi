---
title: "Cards Partition"
layout: "post"
diff: 普及+/提高
pid: CF2018A
tag: ['数学', '贪心']
---

# Cards Partition

## 题目描述

[DJ Genki vs Gram - Einherjar Joker](https://soundcloud.com/leon-hwang-368077289/einherjar-joker-dj-genki-vs-gram)

⠀



You have some cards. An integer between $ 1 $ and $ n $ is written on each card: specifically, for each $ i $ from $ 1 $ to $ n $ , you have $ a_i $ cards which have the number $ i $ written on them.

There is also a shop which contains unlimited cards of each type. You have $ k $ coins, so you can buy at most $ k $ new cards in total, and the cards you buy can contain any integer between $ \mathbf{1} $ and $ \mathbf{n} $ , inclusive.

After buying the new cards, you must partition all your cards into decks, according to the following rules:

- all the decks must have the same size;
- there are no pairs of cards with the same value in the same deck.

Find the maximum possible size of a deck after buying cards and partitioning them optimally.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ k $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ , $ 0 \leq k \leq 10^{16} $ ) — the number of distinct types of cards and the number of coins.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq 10^{10} $ , $ \sum a_i \geq 1 $ ) — the number of cards of type $ i $ you have at the beginning, for each $ 1 \leq i \leq n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the maximum possible size of a deck if you operate optimally.

## 说明/提示

In the first test case, you can buy one card with the number $ 1 $ , and your cards become $ [1, 1, 1, 1, 2, 2, 3, 3] $ . You can partition them into the decks $ [1, 2], [1, 2], [1, 3], [1, 3] $ : they all have size $ 2 $ , and they all contain distinct values. You can show that you cannot get a partition with decks of size greater than $ 2 $ , so the answer is $ 2 $ .

In the second test case, you can buy two cards with the number $ 1 $ and one card with the number $ 3 $ , and your cards become $ [1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 5, 5, 5, 5] $ , which can be partitioned into $ [1, 2, 3], [1, 2, 4], [1, 2, 5], [1, 2, 5], [2, 3, 5], [2, 4, 5] $ . You can show that you cannot get a partition with decks of size greater than $ 3 $ , so the answer is $ 3 $ .

## 样例 #1

### 输入

```
9
3 1
3 2 2
5 4
2 6 1 2 4
2 100
1410065408 10000000000
10 8
7 4 6 6 9 3 10 2 8 7
2 12
2 2
2 70
0 1
1 0
1
3 0
2 1 2
3 1
0 3 3
```

### 输出

```
2
3
1
7
2
2
1
1
2
```

