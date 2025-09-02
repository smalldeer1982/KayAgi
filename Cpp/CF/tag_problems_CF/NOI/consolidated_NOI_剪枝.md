---
title: "Dynamic Shortest Path"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF843D
tag: ['广度优先搜索 BFS', '剪枝', '最短路']
---

# Dynamic Shortest Path

## 题目描述

You are given a weighted directed graph, consisting of $ n $ vertices and $ m $ edges. You should answer $ q $ queries of two types:

- 1 v — find the length of shortest path from vertex $ 1 $ to vertex $ v $ .
- 2 c $ l_{1}\ l_{2}\ ...\ l_{c} $  — add $ 1 $ to weights of edges with indices $ l_{1},l_{2},...,l_{c} $ .

## 输入格式

The first line of input data contains integers $ n $ , $ m $ , $ q $ ( $ 1<=n,m<=10^{5} $ , $ 1<=q<=2000 $ ) — the number of vertices and edges in the graph, and the number of requests correspondingly.

Next $ m $ lines of input data contain the descriptions of edges: $ i $ -th of them contains description of edge with index $ i $ — three integers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ 0<=c_{i}<=10^{9} $ ) — the beginning and the end of edge, and its initial weight correspondingly.

Next $ q $ lines of input data contain the description of edges in the format described above ( $ 1<=v<=n $ , $ 1<=l_{j}<=m $ ). It's guaranteed that inside single query all $ l_{j} $ are distinct. Also, it's guaranteed that a total number of edges in all requests of the second type does not exceed $ 10^{6} $ .

## 输出格式

For each query of first type print the length of the shortest path from $ 1 $ to $ v $ in a separate line. Print -1, if such path does not exists.

## 说明/提示

The description of changes of the graph in the first sample case:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF843D/24bd98e5125f858d47fdfa77b158c3a581ad248b.png)

The description of changes of the graph in the second sample case:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF843D/d325c1b90420a99987b13a59d8addca767eb6927.png)

## 样例 #1

### 输入

```
3 2 9
1 2 0
2 3 0
2 1 2
1 3
1 2
2 1 1
1 3
1 2
2 2 1 2
1 3
1 2

```

### 输出

```
1
0
2
1
4
2

```

## 样例 #2

### 输入

```
5 4 9
2 3 1
2 4 1
3 4 1
1 2 0
1 5
1 4
2 1 2
2 1 2
1 4
2 2 1 3
1 4
2 1 4
1 4

```

### 输出

```
-1
1
2
3
4

```



---

