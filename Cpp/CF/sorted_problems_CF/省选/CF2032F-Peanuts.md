---
title: "Peanuts"
layout: "post"
diff: 省选/NOI-
pid: CF2032F
tag: ['动态规划 DP', '博弈论']
---

# Peanuts

## 题目描述

Having the magical beanstalk, Jack has been gathering a lot of peanuts lately. Eventually, he has obtained $ n $ pockets of peanuts, conveniently numbered $ 1 $ to $ n $ from left to right. The $ i $ -th pocket has $ a_i $ peanuts.

Jack and his childhood friend Alice decide to play a game around the peanuts. First, Alice divides the pockets into some boxes; each box will have a non-zero number of consecutive pockets, and each pocket will, obviously, belong to exactly one box. At the same time, Alice does not change the order of the boxes, that is, the boxes are numbered in ascending order of the indices of the pockets in them.

After that, Alice and Jack will take turns alternately, with Alice going first.

At each turn, the current player will remove a positive number of peanuts from exactly one pocket which belongs to the leftmost non-empty box (i.e., the leftmost box containing at least one non-empty pocket). In other words, if we number the boxes from left to right, then each player can only pick peanuts from the pocket in the $ j $ -th box ( $ j \ge 2 $ ) only if the $ (j - 1) $ -th box has no peanuts left. The player who cannot make a valid move loses.

Alice is sure she will win since she has the advantage of dividing the pockets into boxes herself. Thus, she wanted to know how many ways there are for her to divide the peanuts into boxes at the start of the game so that she will win, assuming both players play optimally. Can you help her with the calculation?

As the result can be very large, output it modulo $ 998\,244\,353 $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 10^6 $ ) — the number of pockets.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the number of peanuts in each pocket.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a single integer — the number of ways for Alice to divide the pockets into boxes at the start of the game to guarantee her win, assuming both players play optimally, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the only way for Alice to win is to divide the pockets into two boxes as follows: $ ([1, 2], [3]) $ (the first box contains the first two pockets and the second box contains the third pocket). Alice wins by taking both peanuts from the second pocket, leaving Jack with $ ([1], [3]) $ . Jack is forced to take the only peanut left in the first box, which allows Alice to take the remaining ones in the second box.

In the second test case, the winning divisions for Alice are $ ([1], [2, 3, 1]) $ , $ ([1, 2, 3, 1]) $ , $ ([1, 2], [3], [1]) $ , and $ ([1, 2], [3, 1]) $ .

In the third test case, Alice always wins no matter how she divides the pockets into boxes.

In the fourth test case, Alice always loses no matter how she divides the pockets into boxes.

## 样例 #1

### 输入

```
5
3
1 2 3
4
1 2 3 1
5
1 1 1 1 1
2
1 1
10
1 2 3 4 5 6 7 8 9 10
```

### 输出

```
1
4
16
0
205
```

