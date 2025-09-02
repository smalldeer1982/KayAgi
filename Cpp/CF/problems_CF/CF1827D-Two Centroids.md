---
title: "Two Centroids"
layout: "post"
diff: 省选/NOI-
pid: CF1827D
tag: []
---

# Two Centroids

## 题目描述

You are given a tree (an undirected connected acyclic graph) which initially only contains vertex $ 1 $ . There will be several queries to the given tree. In the $ i $ -th query, vertex $ i + 1 $ will appear and be connected to vertex $ p_i $ ( $ 1 \le p_i \le i $ ).

After each query, please find out the least number of operations required to make the current tree has two centroids. In one operation, you can add one vertex and one edge to the tree such that it remains a tree.

A vertex is called a centroid if its removal splits the tree into subtrees with at most $ \lfloor \frac{n}{2} \rfloor $ vertices each, with $ n $ as the number of vertices of the tree. For example, the centroid of the following tree is $ 3 $ because the biggest subtree after removing the centroid has $ 2 $ vertices.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827D/ecc06e1bfbfa2b50ddf426bffbad51ace4e5a023.png)In the next tree, vertex $ 1 $ and $ 2 $ are both centroids.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827D/42a5367fe4666594cdbcb007a8104c576dad78f0.png)

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 5 \cdot 10^{5} $ ) — the number of nodes of the final tree.

The second line of each test case contains $ n - 1 $ integers $ p_1, p_2, \ldots, p_{n - 1} $ ( $ 1 \le p_i \le i $ ) — the index of the vertex that is connected to vertex $ i + 1 $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^{5} $ .

## 输出格式

For each test case, output $ n - 1 $ integers. The $ i $ -th integer is the answer to the $ i $ -th query — the least number of operations required to make the current tree have two centroids.

We can show that an answer always exists.

## 说明/提示

The illustrations below are of the fourth example test case.

After the third query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827D/15c7a987e93f4191ff93989ce5a5d836a3f65c54.png)  The tree already has vertices $ 2 $ and $ 3 $ as centroids, so no operations are needed.After the fourth query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827D/510bc6f02a1aac0ae1f0e8ae57461166a9b6fabc.png)  Adding vertex $ x $ to the tree makes vertices $ 2 $ and $ 3 $ centroids. Only one operation is needed.After the fifth query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827D/29421eb0f8c94af01daaf309b6ffbeb3c5c65c23.png)  Adding vertex $ x $ and $ y $ to the tree makes vertices $ 5 $ and $ 2 $ centroids. Two operations are needed.After the sixth query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827D/276326fe18921ee503ac095502b55c698850d8c6.png)  Adding vertex $ x $ , $ y $ , and $ z $ to the tree makes vertices $ 5 $ and $ 2 $ centroids. Three operations are needed.

## 样例 #1

### 输入

```
5
2
1
3
1 1
4
1 2 3
7
1 2 3 2 5 2
10
1 2 2 4 5 5 7 8 9
```

### 输出

```
0
0 1
0 1 0
0 1 0 1 2 3
0 1 2 1 0 1 0 1 2
```

