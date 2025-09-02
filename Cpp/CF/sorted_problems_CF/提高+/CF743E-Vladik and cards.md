---
title: "Vladik and cards"
layout: "post"
diff: 提高+/省选-
pid: CF743E
tag: ['枚举', '剪枝', '状态合并', '向量']
---

# Vladik and cards

## 题目描述

Vladik was bored on his way home and decided to play the following game. He took $ n $ cards and put them in a row in front of himself. Every card has a positive integer number not exceeding $ 8 $ written on it. He decided to find the longest subsequence of cards which satisfies the following conditions:

- the number of occurrences of each number from $ 1 $ to $ 8 $ in the subsequence doesn't differ by more then $ 1 $ from the number of occurrences of any other number. Formally, if there are $ c_{k} $ cards with number $ k $ on them in the subsequence, than for all pairs of integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743E/0c6cc5f621659ae2ddf5ab0dac10dd28e326ec14.png) the condition $ |c_{i}-c_{j}|<=1 $ must hold.
- if there is at least one card with number $ x $ on it in the subsequence, then all cards with number $ x $ in this subsequence must form a continuous segment in it (but not necessarily a continuous segment in the original sequence). For example, the subsequence $ [1,1,2,2] $ satisfies this condition while the subsequence $ [1,2,2,1] $ doesn't. Note that $ [1,1,2,2] $ doesn't satisfy the first condition.

Please help Vladik to find the length of the longest subsequence that satisfies both conditions.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=1000 $ ) — the number of cards in Vladik's sequence.

The second line contains the sequence of $ n $ positive integers not exceeding $ 8 $ — the description of Vladik's sequence.

## 输出格式

Print single integer — the length of the longest subsequence of Vladik's sequence that satisfies both conditions.

## 说明/提示

In the first sample all the numbers written on the cards are equal, so you can't take more than one card, otherwise you'll violate the first condition.

## 样例 #1

### 输入

```
3
1 1 1

```

### 输出

```
1
```

## 样例 #2

### 输入

```
8
8 7 6 5 4 3 2 1

```

### 输出

```
8
```

## 样例 #3

### 输入

```
24
1 8 1 2 8 2 3 8 3 4 8 4 5 8 5 6 8 6 7 8 7 8 8 8

```

### 输出

```
17
```

