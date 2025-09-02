---
title: "Game on Tree (Hard)"
layout: "post"
diff: 提高+/省选-
pid: CF1970C3
tag: ['博弈论', '树形 DP']
---

# Game on Tree (Hard)

## 题目描述

This is the hard version of the problem. The only difference in this version is the constraint on $ t $ .

Ron and Hermione are playing a game on a tree of $ n $ nodes that are initially inactive. The game consists of $ t $ rounds, each of which starts with a stone on exactly one node, which is considered as activated. A move consists of picking an inactive neighbor of the node with a stone on it and moving the stone there (thus activating this neighbor). Ron makes the first move, after which he alternates with Hermione until no valid move is available. The player that cannot make a move loses the round. If both players play optimally, who wins each round of this game?

Note that all the rounds are played with the same tree; only the starting node changes. Moreover, after each round, all active nodes are considered inactive again.

## 输入格式

The first line contains integers $ n $ ( $ 2 \leq n \leq 2\times 10^5 $ ), $ t $ ( $ 1 \leq t \leq n $ ), the number of nodes in the tree and the number of rounds, respectively.

The next $ n-1 $ lines contain two integers $ 1 \leq u, v \leq n $ each, corresponding to an edge of the tree.

The next line contains $ t $ integers $ 1 \leq u_1 , \dots , u_t \leq n $ , corresponding to the node where the stone is initially put.

## 输出格式

The output consists of $ t $ lines, each line being either "Ron" or "Hermione".

## 样例 #1

### 输入

```
5 2
1 2
1 3
3 4
3 5
1 2
```

### 输出

```
Ron
Ron
```

## 样例 #2

### 输入

```
6 3
1 2
2 3
1 4
4 5
4 6
1 4 6
```

### 输出

```
Hermione
Ron
Hermione
```

