---
title: "Masha and Cactus"
layout: "post"
diff: 省选/NOI-
pid: CF856D
tag: []
---

# Masha and Cactus

## 题目描述

Masha is fond of cacti. When she was a little girl, she decided to plant a tree. Now Masha wants to make a nice cactus out of her tree.

Recall that tree is a connected undirected graph that has no cycles. Cactus is a connected undirected graph such that each vertex belongs to at most one cycle.

Masha has some additional edges that she can add to a tree. For each edge she knows which vertices it would connect and the beauty of this edge. Masha can add some of these edges to the graph if the resulting graph is a cactus. Beauty of the resulting cactus is sum of beauties of all added edges.

Help Masha find out what maximum beauty of the resulting cactus she can achieve.

## 输入格式

The first line of the input data contains two integers $ n $ and $ m $ — the number of vertices in a tree, and the number of additional edges available ( $ 3<=n<=2·10^{5} $ ; $ 0<=m<=2·10^{5} $ ).

Let us describe Masha's tree. It has a root at vertex 1. The second line contains $ n-1 $ integers: $ p_{2},p_{3},...,p_{n} $ , here $ p_{i} $ — is the parent of a vertex $ i $ — the first vertex on a path from the vertex $ i $ to the root of the tree ( $ 1<=p_{i}&lt;i $ ).

The following $ m $ lines contain three integers $ u_{i} $ , $ v_{i} $ and $ c_{i} $ — pairs of vertices to be connected by the additional edges that Masha can add to the tree and beauty of edge ( $ 1<=u_{i},v_{i}<=n $ ; $ u_{i}≠v_{i} $ ; $ 1<=c_{i}<=10^{4} $ ).

It is guaranteed that no additional edge coincides with the edge of the tree.

## 输出格式

Output one integer — the maximum beauty of a cactus Masha can achieve.

## 样例 #1

### 输入

```
7 3
1 1 2 2 3 3
4 5 1
6 7 1
2 3 1

```

### 输出

```
2

```

