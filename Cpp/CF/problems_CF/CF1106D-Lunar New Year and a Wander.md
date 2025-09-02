---
title: "Lunar New Year and a Wander"
layout: "post"
diff: 普及+/提高
pid: CF1106D
tag: ['堆']
---

# Lunar New Year and a Wander

## 题目描述

Lunar New Year is approaching, and Bob decides to take a wander in a nearby park.

The park can be represented as a connected graph with $ n $ nodes and $ m $ bidirectional edges. Initially Bob is at the node $ 1 $ and he records $ 1 $ on his notebook. He can wander from one node to another through those bidirectional edges. Whenever he visits a node not recorded on his notebook, he records it. After he visits all nodes at least once, he stops wandering, thus finally a permutation of nodes $ a_1, a_2, \ldots, a_n $ is recorded.

Wandering is a boring thing, but solving problems is fascinating. Bob wants to know the lexicographically smallest sequence of nodes he can record while wandering. Bob thinks this problem is trivial, and he wants you to solve it.

A sequence $ x $ is lexicographically smaller than a sequence $ y $ if and only if one of the following holds:

- $ x $ is a prefix of $ y $ , but $ x \ne y $ (this is impossible in this problem as all considered sequences have the same length);
- in the first position where $ x $ and $ y $ differ, the sequence $ x $ has a smaller element than the corresponding element in $ y $ .

## 输入格式

The first line contains two positive integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 10^5 $ ), denoting the number of nodes and edges, respectively.

The following $ m $ lines describe the bidirectional edges in the graph. The $ i $ -th of these lines contains two integers $ u_i $ and $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ ), representing the nodes the $ i $ -th edge connects.

Note that the graph can have multiple edges connecting the same two nodes and self-loops. It is guaranteed that the graph is connected.

## 输出格式

Output a line containing the lexicographically smallest sequence $ a_1, a_2, \ldots, a_n $ Bob can record.

## 说明/提示

In the first sample, Bob's optimal wandering path could be $ 1 \rightarrow 2 \rightarrow 1 \rightarrow 3 $ . Therefore, Bob will obtain the sequence $ \{1, 2, 3\} $ , which is the lexicographically smallest one.

In the second sample, Bob's optimal wandering path could be $ 1 \rightarrow 4 \rightarrow 3 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 1 \rightarrow 5 $ . Therefore, Bob will obtain the sequence $ \{1, 4, 3, 2, 5\} $ , which is the lexicographically smallest one.

## 样例 #1

### 输入

```
3 2
1 2
1 3

```

### 输出

```
1 2 3 

```

## 样例 #2

### 输入

```
5 5
1 4
3 4
5 4
3 2
1 5

```

### 输出

```
1 4 3 2 5 

```

## 样例 #3

### 输入

```
10 10
1 4
6 8
2 5
3 7
9 4
5 6
3 4
8 10
8 9
1 10

```

### 输出

```
1 4 3 7 9 8 6 5 2 10 

```

