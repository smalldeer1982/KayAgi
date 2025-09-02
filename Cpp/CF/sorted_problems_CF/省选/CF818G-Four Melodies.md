---
title: "Four Melodies"
layout: "post"
diff: 省选/NOI-
pid: CF818G
tag: []
---

# Four Melodies

## 题目描述

Author note: I think some of you might remember the problem "Two Melodies" from Eductational Codeforces Round 22. Now it's time to make it a bit more difficult!

Alice is a composer, and recently she had recorded two tracks that became very popular. Now she has got a lot of fans who are waiting for new tracks.

This time Alice wants to form four melodies for her tracks.

Alice has a sheet with $ n $ notes written on it. She wants to take four such non-empty non-intersecting subsequences that all of them form a melody and sum of their lengths is maximal.

Subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

Subsequence forms a melody when each two adjacent notes either differ by 1 or are congruent modulo 7.

You should write a program which will calculate maximum sum of lengths of such four non-empty non-intersecting subsequences that all of them form a melody.

## 输入格式

The first line contains one integer number $ n $ ( $ 4<=n<=3000 $ ).

The second line contains $ n $ integer numbers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{5} $ ) — notes written on a sheet.

## 输出格式

Print maximum sum of lengths of such four non-empty non-intersecting subsequences that all of them form a melody.

## 说明/提示

In the first example it is possible to compose $ 4 $ melodies by choosing any $ 4 $ notes (and each melody will consist of only one note).

In the second example it is possible to compose one melody with $ 2 $ notes — $ {1,2} $ . Remaining notes are used in other three melodies (one note per each melody).

## 样例 #1

### 输入

```
5
1 3 5 7 9

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5
1 3 5 7 2

```

### 输出

```
5

```

