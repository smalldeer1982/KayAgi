---
title: "Escape Through Leaf"
layout: "post"
diff: 省选/NOI-
pid: CF932F
tag: ['线段树', '树形 DP']
---

# Escape Through Leaf

## 题目描述

You are given a tree with $ n $ nodes (numbered from $ 1 $ to $ n $ ) rooted at node $ 1 $ . Also, each node has two values associated with it. The values for $ i $ -th node are $ a_{i} $ and $ b_{i} $ .

You can jump from a node to any node in its subtree. The cost of one jump from node $ x $ to node $ y $ is the product of $ a_{x} $ and $ b_{y} $ . The total cost of a path formed by one or more jumps is sum of costs of individual jumps. For every node, calculate the minimum total cost to reach any leaf from that node. Pay attention, that root can never be leaf, even if it has degree $ 1 $ .

Note that you cannot jump from a node to itself.

## 输入格式

The first line of input contains an integer $ n $ ( $ 2<=n<=10^{5} $ ) — the number of nodes in the tree.

The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n}(-10^{5}<=a_{i}<=10^{5}) $ .

The third line contains $ n $ space-separated integers $ b_{1},b_{2},...,b_{n}(-10^{5}<=b_{i}<=10^{5}) $ .

Next $ n-1 $ lines contains two space-separated integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) describing edge between nodes $ u_{i} $ and $ v_{i} $ in the tree.

## 输出格式

Output $ n $ space-separated integers, $ i $ -th of which denotes the minimum cost of a path from node $ i $ to reach any leaf.

## 说明/提示

In the first example, node $ 3 $ is already a leaf, so the cost is $ 0 $ . For node $ 2 $ , jump to node $ 3 $ with cost $ a_{2}×b_{3}=50 $ . For node $ 1 $ , jump directly to node $ 3 $ with cost $ a_{1}×b_{3}=10 $ .

In the second example, node $ 3 $ and node $ 4 $ are leaves, so the cost is $ 0 $ . For node $ 2 $ , jump to node $ 4 $ with cost $ a_{2}×b_{4}=100 $ . For node $ 1 $ , jump to node $ 2 $ with cost $ a_{1}×b_{2}=-400 $ followed by a jump from $ 2 $ to $ 4 $ with cost $ a_{2}×b_{4}=100 $ .

## 样例 #1

### 输入

```
3
2 10 -1
7 -7 5
2 3
2 1

```

### 输出

```
10 50 0 
```

## 样例 #2

### 输入

```
4
5 -10 5 7
-8 -80 -3 -10
2 1
2 4
1 3

```

### 输出

```
-300 100 0 0 
```

