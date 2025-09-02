---
title: "Coloring a Tree"
layout: "post"
diff: 普及/提高-
pid: CF902B
tag: []
---

# Coloring a Tree

## 题目描述

You are given a rooted tree with $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ , the root is the vertex number $ 1 $ .

Each vertex has a color, let's denote the color of vertex $ v $ by $ c_{v} $ . Initially $ c_{v}=0 $ .

You have to color the tree into the given colors using the smallest possible number of steps. On each step you can choose a vertex $ v $ and a color $ x $ , and then color all vectices in the subtree of $ v $ (including $ v $ itself) in color $ x $ . In other words, for every vertex $ u $ , such that the path from root to $ u $ passes through $ v $ , set $ c_{u}=x $ .

It is guaranteed that you have to color each vertex in a color different from $ 0 $ .

You can learn what a rooted tree is using the link: <a>https://en.wikipedia.org/wiki/Tree\_(graph\_theory)</a>.

## 输入格式

The first line contains a single integer $ n $ ( $ 2<=n<=10^{4} $ ) — the number of vertices in the tree.

The second line contains $ n-1 $ integers $ p_{2},p_{3},...,p_{n} $ ( $ 1<=p_{i}<i $ ), where $ p_{i} $ means that there is an edge between vertices $ i $ and $ p_{i} $ .

The third line contains $ n $ integers $ c_{1},c_{2},...,c_{n} $ ( $ 1<=c_{i}<=n $ ), where $ c_{i} $ is the color you should color the $ i $ -th vertex into.

It is guaranteed that the given graph is a tree.

## 输出格式

Print a single integer — the minimum number of steps you have to perform to color the tree into given colors.

## 说明/提示

The tree from the first sample is shown on the picture (numbers are vetices' indices):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/9fd1d55fa8fc46341a8b892f02c91e5845a9cee1.png)

On first step we color all vertices in the subtree of vertex $ 1 $ into color $ 2 $ (numbers are colors):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/e11b694106163670fb12fdde15a9f65a4e1cb530.png)

On seond step we color all vertices in the subtree of vertex $ 5 $ into color $ 1 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/e36a2cbd1ae067ab6fd537cd6badf9d7433ee5c6.png)

On third step we color all vertices in the subtree of vertex $ 2 $ into color $ 1 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/e700d0bc8664e90658b34cd2376df32d0611fede.png)

The tree from the second sample is shown on the picture (numbers are vetices' indices):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/67ba592a2c43f57a4f90fbf32ea9b4099ae3ce16.png)

On first step we color all vertices in the subtree of vertex $ 1 $ into color $ 3 $ (numbers are colors):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/a70897e485cd2f798f1fbdf16aad3be9100baa22.png)

On second step we color all vertices in the subtree of vertex $ 3 $ into color $ 1 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/00b2012fb6c63cf50c8cbb62275892a14d90331b.png)

On third step we color all vertices in the subtree of vertex $ 6 $ into color $ 2 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/cbb680be6f7f4a3785c9124a3b69bfeceadc9ad8.png)

On fourth step we color all vertices in the subtree of vertex $ 4 $ into color $ 1 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/2dab5297c24ff5c2f70dfec33f37cb0e4b4866c7.png)

On fith step we color all vertices in the subtree of vertex $ 7 $ into color $ 3 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/8a33180d0bd5c28d2385265618229c6952307c3c.png)

## 样例 #1

### 输入

```
6
1 2 2 1 5
2 1 1 1 1 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
7
1 1 2 3 1 4
3 3 1 1 1 2 3

```

### 输出

```
5

```

