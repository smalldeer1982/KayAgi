---
title: "Infected Tree"
layout: "post"
diff: 普及+/提高
pid: CF1689C
tag: []
---

# Infected Tree

## 题目描述

Byteland is a beautiful land known because of its beautiful trees.

Misha has found a binary tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . A binary tree is an acyclic connected bidirectional graph containing $ n $ vertices and $ n - 1 $ edges. Each vertex has a degree at most $ 3 $ , whereas the root is the vertex with the number $ 1 $ and it has a degree at most $ 2 $ .

Unfortunately, the root got infected.

The following process happens $ n $ times:

- Misha either chooses a non-infected (and not deleted) vertex and deletes it with all edges which have an end in this vertex or just does nothing.
- Then, the infection spreads to each vertex that is connected by an edge to an already infected vertex (all already infected vertices remain infected).

As Misha does not have much time to think, please tell him what is the maximum number of vertices he can save from the infection (note that deleted vertices are not counted as saved).

## 输入格式

There are several test cases in the input data. The first line contains a single integer $ t $ ( $ 1\leq t\leq 5000 $ ) — the number of test cases. This is followed by the test cases description.

The first line of each test case contains one integer $ n $ ( $ 2\leq n\leq 3\cdot 10^5 $ ) — the number of vertices of the tree.

The $ i $ -th of the following $ n-1 $ lines in the test case contains two positive integers $ u_i $ and $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ ), meaning that there exists an edge between them in the graph.

It is guaranteed that the graph is a binary tree rooted at $ 1 $ . It is also guaranteed that the sum of $ n $ over all test cases won't exceed $ 3\cdot 10^5 $ .

## 输出格式

For each test case, output the maximum number of vertices Misha can save.

## 说明/提示

In the first test case, the only possible action is to delete vertex $ 2 $ , after which we save $ 0 $ vertices in total.

In the second test case, if we delete vertex $ 2 $ , we can save vertices $ 3 $ and $ 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1689C/1f479df0f6df9637a1dfee43da055c650bdae647.png)

## 样例 #1

### 输入

```
4
2
1 2
4
1 2
2 3
2 4
7
1 2
1 5
2 3
2 4
5 6
5 7
15
1 2
2 3
3 4
4 5
4 6
3 7
2 8
1 9
9 10
9 11
10 12
10 13
11 14
11 15
```

### 输出

```
0
2
2
10
```

