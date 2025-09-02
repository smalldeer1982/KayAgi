---
title: "Alice, Bob, Two Teams"
layout: "post"
diff: 普及/提高-
pid: CF632B
tag: []
---

# Alice, Bob, Two Teams

## 题目描述

Alice and Bob are playing a game. The game involves splitting up game pieces into two teams. There are $ n $ pieces, and the $ i $ -th piece has a strength $ p_{i} $ .

The way to split up game pieces is split into several steps:

1. First, Alice will split the pieces into two different groups $ A $ and $ B $ . This can be seen as writing the assignment of teams of a piece in an $ n $ character string, where each character is $ A $ or $ B $ .
2. Bob will then choose an arbitrary prefix or suffix of the string, and flip each character in that suffix (i.e. change $ A $ to $ B $ and $ B $ to $ A $ ). He can do this step at most once.
3. Alice will get all the pieces marked $ A $ and Bob will get all the pieces marked $ B $ .

The strength of a player is then the sum of strengths of the pieces in the group.

Given Alice's initial split into two teams, help Bob determine an optimal strategy. Return the maximum strength he can achieve.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=5·10^{5} $ ) — the number of game pieces.

The second line contains $ n $ integers $ p_{i} $ ( $ 1<=p_{i}<=10^{9} $ ) — the strength of the $ i $ -th piece.

The third line contains $ n $ characters $ A $ or $ B $ — the assignment of teams after the first step (after Alice's step).

## 输出格式

Print the only integer $ a $ — the maximum strength Bob can achieve.

## 说明/提示

In the first sample Bob should flip the suffix of length one.

In the second sample Bob should flip the prefix or the suffix (here it is the same) of length $ 5 $ .

In the third sample Bob should do nothing.

## 样例 #1

### 输入

```
5
1 2 3 4 5
ABABA

```

### 输出

```
11

```

## 样例 #2

### 输入

```
5
1 2 3 4 5
AAAAA

```

### 输出

```
15

```

## 样例 #3

### 输入

```
1
1
B

```

### 输出

```
1

```

