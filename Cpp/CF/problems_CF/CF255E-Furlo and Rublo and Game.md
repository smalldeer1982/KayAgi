---
title: "Furlo and Rublo and Game"
layout: "post"
diff: 提高+/省选-
pid: CF255E
tag: []
---

# Furlo and Rublo and Game

## 题目描述

Furlo and Rublo play a game. The table has $ n $ piles of coins lying on it, the $ i $ -th pile has $ a_{i} $ coins. Furlo and Rublo move in turns, Furlo moves first. In one move you are allowed to:

- choose some pile, let's denote the current number of coins in it as $ x $ ;
- choose some integer $ y $ $ (0<=y&lt;x; x^{1/4}<=y<=x^{1/2}) $ and decrease the number of coins in this pile to $ y $ . In other words, after the described move the pile will have $ y $ coins left.

The player who can't make a move, loses.

Your task is to find out, who wins in the given game if both Furlo and Rublo play optimally well.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=77777) $ — the number of piles. The next line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=777777777777) $ — the sizes of piles. The numbers are separated by single spaces.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 输出格式

If both players play optimally well and Furlo wins, print "Furlo", otherwise print "Rublo". Print the answers without the quotes.

## 样例 #1

### 输入

```
1
1

```

### 输出

```
Rublo

```

## 样例 #2

### 输入

```
2
1 2

```

### 输出

```
Rublo

```

## 样例 #3

### 输入

```
10
1 2 3 4 5 6 7 8 9 10

```

### 输出

```
Furlo

```

