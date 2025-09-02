---
title: "Anton and Danik"
layout: "post"
diff: 入门
pid: CF734A
tag: []
---

# Anton and Danik

## 题目描述

Anton likes to play chess, and so does his friend Danik.

Once they have played $ n $ games in a row. For each game it's known who was the winner — Anton or Danik. None of the games ended with a tie.

Now Anton wonders, who won more games, he or Danik? Help him determine this.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the number of games played.

The second line contains a string $ s $ , consisting of $ n $ uppercase English letters 'A' and 'D' — the outcome of each of the games. The $ i $ -th character of the string is equal to 'A' if the Anton won the $ i $ -th game and 'D' if Danik won the $ i $ -th game.

## 输出格式

If Anton won more games than Danik, print "Anton" (without quotes) in the only line of the output.

If Danik won more games than Anton, print "Danik" (without quotes) in the only line of the output.

If Anton and Danik won the same number of games, print "Friendship" (without quotes).

## 说明/提示

In the first sample, Anton won $ 6 $ games, while Danik — only $ 1 $ . Hence, the answer is "Anton".

In the second sample, Anton won $ 3 $ games and Danik won $ 4 $ games, so the answer is "Danik".

In the third sample, both Anton and Danik won $ 3 $ games and the answer is "Friendship".

## 样例 #1

### 输入

```
6
ADAAAA

```

### 输出

```
Anton

```

## 样例 #2

### 输入

```
7
DDDAADA

```

### 输出

```
Danik

```

## 样例 #3

### 输入

```
6
DADADA

```

### 输出

```
Friendship

```

