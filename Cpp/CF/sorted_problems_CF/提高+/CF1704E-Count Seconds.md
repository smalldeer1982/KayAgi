---
title: "Count Seconds"
layout: "post"
diff: 提高+/省选-
pid: CF1704E
tag: ['拓扑排序']
---

# Count Seconds

## 题目描述

Cirno has a DAG (Directed Acyclic Graph) with $ n $ nodes and $ m $ edges. The graph has exactly one node that has no out edges. The $ i $ -th node has an integer $ a_i $ on it.

Every second the following happens:

- Let $ S $ be the set of nodes $ x $ that have $ a_x > 0 $ .
- For all $ x \in S $ , $ 1 $ is subtracted from $ a_x $ , and then for each node $ y $ , such that there is an edge from $ x $ to $ y $ , $ 1 $ is added to $ a_y $ .

Find the first moment of time when all $ a_i $ become $ 0 $ . Since the answer can be very large, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases. Description of test cases follows.

The first line of each test case contains two integers $ n, m $ ( $ 1 \leq n, m \leq 1000 $ ) — the number of vertices and edges in the graph.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq 10^9 $ ) — the integer on vertices.

Each line of the following $ m $ lines contains two integers $ x, y $ ( $ 1 \leq x, y \leq n $ ), represent a directed edge from $ x $ to $ y $ . It is guaranteed that the graph is a DAG with no multi-edges, and there is exactly one node that has no out edges.

It is guaranteed that both sum of $ n $ and sum of $ m $ over all test cases are less than or equal to $ 10\,000 $ .

## 输出格式

For each test case, print an integer in a separate line — the first moment of time when all $ a_i $ become $ 0 $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case:

- At time $ 0 $ , the values of the nodes are $ [1, 1, 1] $ .
- At time $ 1 $ , the values of the nodes are $ [0, 1, 1] $ .
- At time $ 2 $ , the values of the nodes are $ [0, 0, 1] $ .
- At time $ 3 $ , the values of the nodes are $ [0, 0, 0] $ .

So the answer is $ 3 $ .

 In the second test case: - At time $ 0 $ , the values of the nodes are $ [1, 0, 0, 0, 0] $ .
- At time $ 1 $ , the values of the nodes are $ [0, 1, 0, 0, 1] $ .
- At time $ 2 $ , the values of the nodes are $ [0, 0, 1, 0, 0] $ .
- At time $ 3 $ , the values of the nodes are $ [0, 0, 0, 1, 0] $ .
- At time $ 4 $ , the values of the nodes are $ [0, 0, 0, 0, 1] $ .
- At time $ 5 $ , the values of the nodes are $ [0, 0, 0, 0, 0] $ .

 So the answer is $ 5 $ .In the third test case:

The first moment of time when all $ a_i $ become $ 0 $ is $ 6\cdot 998244353 + 4 $ .

## 样例 #1

### 输入

```
5
3 2
1 1 1
1 2
2 3
5 5
1 0 0 0 0
1 2
2 3
3 4
4 5
1 5
10 11
998244353 0 0 0 998244353 0 0 0 0 0
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
1 3
7 9
5 6
1293 1145 9961 9961 1919
1 2
2 3
3 4
5 4
1 4
2 4
6 9
10 10 10 10 10 10
1 2
1 3
2 3
4 3
6 3
3 5
6 5
6 1
6 2
```

### 输出

```
3
5
4
28010
110
```

