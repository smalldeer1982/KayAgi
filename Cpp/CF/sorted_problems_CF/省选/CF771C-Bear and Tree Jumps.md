---
title: "Bear and Tree Jumps"
layout: "post"
diff: 省选/NOI-
pid: CF771C
tag: []
---

# Bear and Tree Jumps

## 题目描述

A tree is an undirected connected graph without cycles. The distance between two vertices is the number of edges in a simple path between them.

Limak is a little polar bear. He lives in a tree that consists of $ n $ vertices, numbered $ 1 $ through $ n $ .

Limak recently learned how to jump. He can jump from a vertex to any vertex within distance at most $ k $ .

For a pair of vertices $ (s,t) $ we define $ f(s,t) $ as the minimum number of jumps Limak needs to get from $ s $ to $ t $ . Your task is to find the sum of $ f(s,t) $ over all pairs of vertices $ (s,t) $ such that $ s&lt;t $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 2<=n<=200000 $ , $ 1<=k<=5 $ ) — the number of vertices in the tree and the maximum allowed jump distance respectively.

The next $ n-1 $ lines describe edges in the tree. The $ i $ -th of those lines contains two integers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n $ ) — the indices on vertices connected with $ i $ -th edge.

It's guaranteed that the given edges form a tree.

## 输出格式

Print one integer, denoting the sum of $ f(s,t) $ over all pairs of vertices $ (s,t) $ such that $ s&lt;t $ .

## 说明/提示

In the first sample, the given tree has $ 6 $ vertices and it's displayed on the drawing below. Limak can jump to any vertex within distance at most $ 2 $ . For example, from the vertex $ 5 $ he can jump to any of vertices: $ 1 $ , $ 2 $ and $ 4 $ (well, he can also jump to the vertex $ 5 $ itself).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF771C/8994ac77b38d70eaef5cd0952cd4c3fda510d514.png)There are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF771C/cde4e5f0e6e4654d394ac6cfffb62423a3518573.png) pairs of vertices $ (s,t) $ such that $ s&lt;t $ . For $ 5 $ of those pairs Limak would need two jumps: $ (1,6),(3,4),(3,5),(3,6),(5,6) $ . For other $ 10 $ pairs one jump is enough. So, the answer is $ 5·2+10·1=20 $ .

In the third sample, Limak can jump between every two vertices directly. There are $ 3 $ pairs of vertices $ (s&lt;t) $ , so the answer is $ 3·1=3 $ .

## 样例 #1

### 输入

```
6 2
1 2
1 3
2 4
2 5
4 6

```

### 输出

```
20

```

## 样例 #2

### 输入

```
13 3
1 2
3 2
4 2
5 2
3 6
10 6
6 7
6 13
5 8
5 9
9 11
11 12

```

### 输出

```
114

```

## 样例 #3

### 输入

```
3 5
2 1
3 1

```

### 输出

```
3

```

