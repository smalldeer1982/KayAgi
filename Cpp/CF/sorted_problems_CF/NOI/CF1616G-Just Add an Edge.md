---
title: "Just Add an Edge"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1616G
tag: []
---

# Just Add an Edge

## 题目描述

You are given a directed acyclic graph with $ n $ vertices and $ m $ edges. For all edges $ a \to b $ in the graph, $ a < b $ holds.

You need to find the number of pairs of vertices $ x $ , $ y $ , such that $ x > y $ and after adding the edge $ x \to y $ to the graph, it has a Hamiltonian path.

## 输入格式

The first line of input contains one integer $ t $ ( $ 1 \leq t \leq 5 $ ): the number of test cases.

The next lines contains the descriptions of the test cases.

In the first line you are given two integers $ n $ and $ m $ ( $ 1 \leq n \leq 150\,000 $ , $ 0 \leq m \leq \min(150\,000, \frac{n(n-1)}{2}) $ ): the number of vertices and edges in the graph.

Each of the next $ m $ lines contains two integers $ a $ , $ b $ ( $ 1 \leq a < b \leq n $ ), specifying an edge $ a \to b $ in the graph. No edge $ a \to b $ appears more than once.

## 输出格式

For each test case, print one integer: the number of pairs of vertices $ x $ , $ y $ , $ x > y $ , such that after adding the edge $ x \to y $ to the graph, it has a Hamiltonian path.

## 说明/提示

In the first example, any edge $ x \to y $ such that $ x > y $ is valid, because there already is a path $ 1 \to 2 \to 3 $ .

In the second example only the edge $ 4 \to 1 $ is valid. There is a path $ 3 \to 4 \to 1 \to 2 $ if this edge is added.

In the third example you can add edges $ 2 \to 1 $ , $ 3 \to 1 $ , $ 4 \to 1 $ , $ 4 \to 2 $ .

## 样例 #1

### 输入

```
3
3 2
1 2
2 3
4 3
1 2
3 4
1 4
4 4
1 3
1 4
2 3
3 4
```

### 输出

```
3
1
4
```

