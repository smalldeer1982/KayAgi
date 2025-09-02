---
title: "Binary String Battle"
layout: "post"
diff: 难度0
pid: CF2123D
tag: []
---

# Binary String Battle

## 题目描述

Alice and Bob are given a binary string $ s $ of length $ n $ , and an integer $ k $ ( $ 1\leq k < n $ ).

Alice wins if she is able to transform all characters of $ s $ into zeroes. If Alice is unable to win in a finite number of moves, then Bob wins.

Alice and Bob take turns, with Alice going first.

- On Alice's turn, she may choose any subsequence $ ^{\text{∗}} $ of length $ k $ in $ s $ , then set all characters in that subsequence to zero.
- On Bob's turn, he may choose any substring $ ^{\text{†}} $ of length $ k $ in $ s $ , then set all characters in that substring to one.

Note that Alice wins if the string consists of all zeros at any point during the game, including in between Alice's and Bob's turns.

Determine who wins with optimal play.

 $ ^{\text{∗}} $ A subsequence of a string $ s $ is a set of characters in $ s $ . Note that these characters do not have to be adjacent.

 $ ^{\text{†}} $ A substring of a string $ s $ is a contiguous group of characters in $ s $ . Note that these characters must be adjacent.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 2\leq n \leq 2\cdot 10^5 $ , $ 1\leq k < n $ ).

The second line of each test case contains a binary string $ s $ of length $ n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output on a single line "Alice" if Alice wins with optimal play, and "Bob" if Bob wins with optimal play.

You can output the answer in any case (upper or lower). For example, the strings "aLiCe", "alice", "ALICE", and "alICE" will be recognized as "Alice".

## 说明/提示

In the third sample, Alice can choose the subsequence consisting of $ s_2 $ , turning $ s $ into $ 000000 $ . Then she wins immediately.

In the fourth sample, it can be shown that there is no way for Alice to guarantee that she can turn $ s $ into $ 0000 $ within a finite number of moves.

## 样例 #1

### 输入

```
6
5 2
11011
7 4
1011011
6 1
010000
4 1
1111
8 3
10110110
6 4
111111
```

### 输出

```
Bob
Alice
Alice
Bob
Bob
Alice
```

