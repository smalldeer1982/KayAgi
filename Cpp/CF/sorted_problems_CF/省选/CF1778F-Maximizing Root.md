---
title: "Maximizing Root"
layout: "post"
diff: 省选/NOI-
pid: CF1778F
tag: []
---

# Maximizing Root

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . Vertex $ 1 $ is the root of the tree. Each vertex has an integer value. The value of $ i $ -th vertex is $ a_i $ . You can do the following operation at most $ k $ times.

- Choose a vertex $ v $ that has not been chosen before and an integer $ x $ such that $ x $ is a common divisor of the values of all vertices of the subtree of $ v $ . Multiply by $ x $ the value of each vertex in the subtree of $ v $ .

What is the maximum possible value of the root node $ 1 $ after at most $ k $ operations? Formally, you have to maximize the value of $ a_1 $ .

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root. The subtree of a node $ u $ is the set of all nodes $ y $ such that the simple path from $ y $ to the root passes through $ u $ . Note that $ u $ is in the subtree of $ u $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 50\,000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 2 \leq n \leq 10^5 $ , $ 0 \leq k \leq n $ ) — the number of vertices in the tree and the number of operations.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 1000 $ ), where $ a_i $ denotes the value of vertex $ i $ .

Each of the next $ n - 1 $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ , $ u_i \neq v_i $ ), denoting the edge of the tree between vertices $ u_i $ and $ v_i $ . It is guaranteed that the given edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum value of the root after performing at most $ k $ operations.

## 说明/提示

Both examples have the same tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778F/6a70ae0aa91307af0a5148283774844759a80b11.png)For the first test case, you can do two operations as follows:

- Choose the subtree of vertex $ 4 $ and $ x = 2 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778F/efd9ed3fe3fe146d2c3ad22bdc3a0d5094263862.png)  After this operation, the node values become $ \{24, 12, 24, 12, 12\}. $
- Choose the subtree of vertex $ 1 $ and $ x = 12 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778F/448b3697478f6bf92a71b275bb4b714ad3a39227.png)  After this operation, the node values become $ \{288, 144, 288, 144, 144\}. $

 The value of the root is $ 288 $ and it is the maximum.For the second test case, you can do three operations as follows:

- Choose the subtree of vertex $ 4 $ and $ x = 2 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778F/efd9ed3fe3fe146d2c3ad22bdc3a0d5094263862.png)  After this operation, the node values become $ \{24, 12, 24, 12, 12\}. $
- Choose the subtree of vertex $ 2 $ and $ x = 4 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778F/7004889d13c9800ff61e810a176c843b3201729c.png)  After this operation, the node values become $ \{24, 48, 24, 48, 48\}. $
- Choose the subtree of vertex $ 1 $ and $ x = 24 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778F/33e11b130545753fb9dc63bbfb2deaf72c859447.png)  After this operation, the node values become $ \{576, 1152, 576, 1152, 1152\}. $

 The value of the root is $ 576 $ and it is the maximum.

## 样例 #1

### 输入

```
2
5 2
24 12 24 6 12
1 2
1 3
2 4
2 5
5 3
24 12 24 6 12
1 2
1 3
2 4
2 5
```

### 输出

```
288
576
```

