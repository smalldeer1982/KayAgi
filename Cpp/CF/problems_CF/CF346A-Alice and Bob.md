---
title: "Alice and Bob"
layout: "post"
diff: 普及/提高-
pid: CF346A
tag: []
---

# Alice and Bob

## 题目描述

It is so boring in the summer holiday, isn't it? So Alice and Bob have invented a new game to play. The rules are as follows. First, they get a set of $ n $ distinct integers. And then they take turns to make the following moves. During each move, either Alice or Bob (the player whose turn is the current) can choose two distinct integers $ x $ and $ y $ from the set, such that the set doesn't contain their absolute difference $ |x-y| $ . Then this player adds integer $ |x-y| $ to the set (so, the size of the set increases by one).

If the current player has no valid move, he (or she) loses the game. The question is who will finally win the game if both players play optimally. Remember that Alice always moves first.

## 输入格式

The first line contains an integer $ n $ ( $ 2<=n<=100 $ ) — the initial number of elements in the set. The second line contains $ n $ distinct space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the elements of the set.

## 输出格式

Print a single line with the winner's name. If Alice wins print "Alice", otherwise print "Bob" (without quotes).

## 说明/提示

Consider the first test sample. Alice moves first, and the only move she can do is to choose 2 and 3, then to add 1 to the set. Next Bob moves, there is no valid move anymore, so the winner is Alice.

## 样例 #1

### 输入

```
2
2 3

```

### 输出

```
Alice

```

## 样例 #2

### 输入

```
2
5 3

```

### 输出

```
Alice

```

## 样例 #3

### 输入

```
3
5 6 7

```

### 输出

```
Bob

```

