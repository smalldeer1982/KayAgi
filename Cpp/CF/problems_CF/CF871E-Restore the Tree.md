---
title: "Restore the Tree"
layout: "post"
diff: 省选/NOI-
pid: CF871E
tag: ['构造']
---

# Restore the Tree

## 题目描述

Petya had a tree consisting of $ n $ vertices numbered with integers from $ 1 $ to $ n $ . Accidentally he lost his tree.

Petya remembers information about $ k $ vertices: distances from each of them to each of the $ n $ tree vertices.

Your task is to restore any tree that satisfies the information that Petya remembers or report that such tree doesn't exist.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2<=n<=30000 $ , $ 1<=k<=min(200,n) $ ) — the number of vertices in the tree and the number of vertices about which Petya remembers distance information.

The following $ k $ lines contain remembered information. The $ i $ -th line contains $ n $ integers $ d_{i,1},d_{i,2},...,d_{i,n} $ ( $ 0<=d_{i,j}<=n-1 $ ), where $ d_{i,j} $ — the distance to $ j $ -th vertex from the $ i $ -th vertex that Petya remembers.

## 输出格式

If there are no suitable trees, print -1.

In the other case, print $ n-1 $ lines: each line should contain two vertices connected by edge in the required tree. You can print edges and vertices in an edge in any order. The tree vertices are enumerated from $ 1 $ to $ n $ .

If there are many solutions print any of them.

## 说明/提示

Picture for the first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF871E/6f212029526e4d77c3a6bc5fe4ad25b3afc1824a.png)

## 样例 #1

### 输入

```
5 2
0 1 2 3 2
2 1 0 1 2

```

### 输出

```
2 1
3 2
4 3
5 2

```

## 样例 #2

### 输入

```
3 1
1 2 1

```

### 输出

```
-1

```

