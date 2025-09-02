---
title: "Cyclic Coloring"
layout: "post"
diff: 省选/NOI-
pid: CF183C
tag: []
---

# Cyclic Coloring

## 题目描述

You are given a directed graph $ G $ with $ n $ vertices and $ m $ arcs (multiple arcs and self-loops are allowed). You have to paint each vertex of the graph into one of the $ k $ $ (k<=n) $ colors in such way that for all arcs of the graph leading from a vertex $ u $ to vertex $ v $ , vertex $ v $ is painted with the next color of the color used to paint vertex $ u $ .

The colors are numbered cyclically $ 1 $ through $ k $ . This means that for each color $ i $ $ (i&lt;k) $ its next color is color $ i+1 $ . In addition, the next color of color $ k $ is color $ 1 $ . Note, that if $ k=1 $ , then the next color for color $ 1 $ is again color $ 1 $ .

Your task is to find and print the largest possible value of $ k $ $ (k<=n) $ such that it's possible to color $ G $ as described above with $ k $ colors. Note that you don't necessarily use all the $ k $ colors (that is, for each color $ i $ there does not necessarily exist a vertex that is colored with color $ i $ ).

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ( $ 1<=n,m<=10^{5} $ ), denoting the number of vertices and the number of arcs of the given digraph, respectively.

Then $ m $ lines follow, each line will contain two space-separated integers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n $ ), which means that the $ i $ -th arc goes from vertex $ a_{i} $ to vertex $ b_{i} $ .

Multiple arcs and self-loops are allowed.

## 输出格式

Print a single integer — the maximum possible number of the colors that can be used to paint the digraph (i.e. $ k $ , as described in the problem statement). Note that the desired value of $ k $ must satisfy the inequality $ 1<=k<=n $ .

## 说明/提示

For the first example, with $ k=2 $ , this picture depicts the two colors (arrows denote the next color of that color).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183C/5fc25b3e1baecb0cc286fd1a3b08fbd0e1f5c4eb.png)With $ k=2 $ a possible way to paint the graph is as follows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183C/8c36834819409d82c5c1224a04a2fcf860f0bd11.png)It can be proven that no larger value for $ k $ exists for this test case.

For the second example, here's the picture of the $ k=5 $ colors.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183C/6fb597ece64567e61db8b5ed6d1b98f36788eb3f.png)A possible coloring of the graph is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183C/ddb3d14ab97f674110eb33ef458d1f97e9ea4ac4.png)For the third example, here's the picture of the $ k=3 $ colors.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183C/a77c6758c9d6428611a620004da04ba72186df31.png)A possible coloring of the graph is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183C/5dc5850b22b6955a11cc6496cce3c42d93bc37c7.png)

## 样例 #1

### 输入

```
4 4
1 2
2 1
3 4
4 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 2
1 4
2 5

```

### 输出

```
5

```

## 样例 #3

### 输入

```
4 5
1 2
2 3
3 1
2 4
4 1

```

### 输出

```
3

```

## 样例 #4

### 输入

```
4 4
1 1
1 2
2 1
1 2

```

### 输出

```
1

```

