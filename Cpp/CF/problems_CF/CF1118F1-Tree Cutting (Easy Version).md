---
title: "Tree Cutting (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF1118F1
tag: []
---

# Tree Cutting (Easy Version)

## 题目描述

You are given an undirected tree of $ n $ vertices.

Some vertices are colored blue, some are colored red and some are uncolored. It is guaranteed that the tree contains at least one red vertex and at least one blue vertex.

You choose an edge and remove it from the tree. Tree falls apart into two connected components. Let's call an edge nice if neither of the resulting components contain vertices of both red and blue colors.

How many nice edges are there in the given tree?

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 3 \cdot 10^5 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 2 $ ) — the colors of the vertices. $ a_i = 1 $ means that vertex $ i $ is colored red, $ a_i = 2 $ means that vertex $ i $ is colored blue and $ a_i = 0 $ means that vertex $ i $ is uncolored.

The $ i $ -th of the next $ n - 1 $ lines contains two integers $ v_i $ and $ u_i $ ( $ 1 \le v_i, u_i \le n $ , $ v_i \ne u_i $ ) — the edges of the tree. It is guaranteed that the given edges form a tree. It is guaranteed that the tree contains at least one red vertex and at least one blue vertex.

## 输出格式

Print a single integer — the number of nice edges in the given tree.

## 说明/提示

Here is the tree from the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F1/ab0319e6d1b3fdf0a12318f77b159c6dc359f231.png)The only nice edge is edge $ (2, 4) $ . Removing it makes the tree fall apart into components $ \{4\} $ and $ \{1, 2, 3, 5\} $ . The first component only includes a red vertex and the second component includes blue vertices and uncolored vertices.

Here is the tree from the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F1/7f13f482fb950c8fef37bc2658aa383ebfb7bf5b.png)Every edge is nice in it.

Here is the tree from the third example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F1/f3485c6c57decb8200c34309a45ff67d9c4b5fd0.png)Edge $ (1, 3) $ splits the into components $ \{1\} $ and $ \{3, 2\} $ , the latter one includes both red and blue vertex, thus the edge isn't nice. Edge $ (2, 3) $ splits the into components $ \{1, 3\} $ and $ \{2\} $ , the former one includes both red and blue vertex, thus the edge also isn't nice. So the answer is 0.

## 样例 #1

### 输入

```
5
2 0 0 1 2
1 2
2 3
2 4
2 5

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
1 0 0 0 2
1 2
2 3
3 4
4 5

```

### 输出

```
4

```

## 样例 #3

### 输入

```
3
1 1 2
2 3
1 3

```

### 输出

```
0

```

