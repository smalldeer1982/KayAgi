---
title: "Lattice Optimizing"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2002G
tag: ['折半搜索 meet in the middle']
---

# Lattice Optimizing

## 题目描述

考虑一个具有 
$n$ 行和 
$n$ 列的网格图。

对于所有 $x < n$ 的位置有一个权值  $d_{x,y}$

对于所有 $y < n$ 的位置有一个权值 
$r_{x,y}$

从 $(1,1)$ 开始走，每次往下或往右走，最终到 $(n,n)$。

初始有一个空集合 $S$。若从 $(x,y)$ 走到 $(x+1,y)$，将 $d_{x,y}$ 加入 $S$；走到 $(x,y+1)$ 就加入 $r_{x,y}$。

需要最大化走到终点时的 $mex(S)$

其中，$mex(x)$ 定义为 $x$ 中最小未出现的 **非负整数**。

## 输入格式

第一行一个数 $T$，表示测试组数。

每组测试第一行一个整数 $n$，接下来 $n-1$ 行每行 $n$ 个数表示 $d$。

接下来 $n$ 行每行 $n-1$ 个数表示 $r$。

保证 $n$ 不超过 $20$，且所有 $n^3$ 的和不超过 $8000$，且 $d_{i,j}$ 和 $r_{i,j}$ 都不超过 $2n-2$。

## 输出格式

输出 $T$ 行表示每组测试数据的答案。

## 样例 #1

### 输入

```
2
3
1 0 2
0 1 3
2 1
0 3
3 0
3
1 2 0
0 1 2
2 0
1 2
0 1
```

### 输出

```
3
2
```

## 样例 #2

### 输入

```
1
10
16 7 3 15 9 17 1 15 9 0
4 3 1 12 13 10 10 14 6 12
3 1 3 9 5 16 0 12 7 12
11 4 8 7 13 7 15 13 9 2
2 3 9 9 4 12 17 7 10 15
10 6 15 17 13 6 15 9 4 9
13 3 3 14 1 2 10 10 12 16
8 2 9 13 18 7 1 6 2 6
15 12 2 6 0 0 13 3 7 17
7 3 17 17 10 15 12 14 15
4 3 3 17 3 13 11 16 6
16 17 7 7 12 5 2 4 10
18 9 9 3 5 9 1 16 7
1 0 4 2 10 10 12 2 1
4 14 15 16 15 5 8 4 18
7 18 10 11 2 0 14 8 18
2 17 6 0 9 6 13 5 11
5 15 7 11 6 3 17 14 5
1 3 16 16 13 1 0 13 11
```

### 输出

```
14
```



---

---
title: "Summer Dichotomy"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF538H
tag: ['深度优先搜索 DFS', '二分图', '构造']
---

# Summer Dichotomy

## 题目描述

 $ T $ students applied into the ZPP class of Summer Irrelevant School. The organizing committee of the school may enroll any number of them, but at least $ t $ students must be enrolled. The enrolled students should be divided into two groups in any manner (it is possible that one of the groups will be empty!)

During a shift the students from the ZPP grade are tutored by $ n $ teachers. Due to the nature of the educational process, each of the teachers should be assigned to exactly one of two groups (it is possible that no teacher will be assigned to some of the groups!). The $ i $ -th teacher is willing to work in a group as long as the group will have at least $ l_{i} $ and at most $ r_{i} $ students (otherwise it would be either too boring or too hard). Besides, some pairs of the teachers don't like each other other and therefore can not work in the same group; in total there are $ m $ pairs of conflicting teachers.

You, as the head teacher of Summer Irrelevant School, have got a difficult task: to determine how many students to enroll in each of the groups and in which group each teacher will teach.

## 输入格式

The first line contains two space-separated integers, $ t $ and $ T $ ( $ 1<=t<=T<=10^{9} $ ).

The second line contains two space-separated integers $ n $ and $ m $ ( $ 1<=n<=10^{5} $ , $ 0<=m<=10^{5} $ ).

The $ i $ -th of the next $ n $ lines contain integers $ l_{i} $ and $ r_{i} $ ( $ 0<=l_{i}<=r_{i}<=10^{9} $ ).

The next $ m $ lines describe the pairs of conflicting teachers. Each of these lines contain two space-separated integers — the indices of teachers in the pair. The teachers are indexed starting from one. It is guaranteed that no teacher has a conflict with himself and no pair of conflicting teachers occurs in the list more than once.

## 输出格式

If the distribution is possible, print in the first line a single word 'POSSIBLE' (without the quotes). In the second line print two space-separated integers $ n_{1} $ and $ n_{2} $ — the number of students in the first and second group, correspondingly, the contstraint $ t<=n_{1}+n_{2}<=T $ should be met. In the third line print $ n $ characters, the $ i $ -th of which should be 1 or 2, if the $ i $ -th teacher should be assigned to the first or second group, correspondingly. If there are multiple possible distributions of students and teachers in groups, you can print any of them.

If the sought distribution doesn't exist, print a single word 'IMPOSSIBLE' (without the quotes).

## 样例 #1

### 输入

```
10 20
3 0
3 6
4 9
16 25

```

### 输出

```
POSSIBLE
4 16
112

```

## 样例 #2

### 输入

```
1 10
3 3
0 10
0 10
0 10
1 2
1 3
2 3

```

### 输出

```
IMPOSSIBLE

```



---

---
title: "Tourist Guide"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF589H
tag: ['搜索', '生成树', '最近公共祖先 LCA']
---

# Tourist Guide

## 题目描述

It is not that easy to create a tourist guide as one might expect. A good tourist guide should properly distribute flow of tourists across the country and maximize the revenue stream from the tourism. This is why there is a number of conditions to be met before a guide may be declared as an official tourist guide and approved by Ministry of Tourism.

Ministry of Tourism has created a list of $ k $ remarkable cities out of $ n $ cities in the country. Basically, it means that in order to conform to strict regulations and to be approved by the ministry a tourist guide should be represented as a set of routes between remarkable cities so that the following conditions are met:

- the first and the last city of every route are distinct remarkable cities,
- each remarkable city can be an endpoint of at most one route,
- there is no pair of routes which share a road.

Please note that a route may pass through a remarkable city. Revenue stream from the tourism highly depends on a number of routes included in a tourist guide so the task is to find out a set of routes conforming the rules of a tourist guide with a maximum number of routes included.

## 输入格式

The first line contains three integer numbers $ n,m,k $ $ (1<=n<=50000,0<=m<=50000,1<=k<=n) $ — the number of cities in the country, the number of roads in the country and the number of remarkable cities correspondingly.

Each of the following $ m $ lines contains two integer numbers $ a_{i} $ and $ b_{i} $ $ (1<=a_{i},b_{i}<=n) $ — meaning that cities $ a_{i} $ and $ b_{i} $ are connected by a bidirectional road. It is guaranteed that $ a_{i} $ and $ b_{i} $ are distinct numbers and there is no more than one road between a pair of cities.

The last line contains $ k $ distinct integer numbers — a list of remarkable cities. All cities are numbered from 1 to $ n $ .

## 输出格式

The first line of the output should contain $ c $ — the number of routes in a tourist guide. The following $ c $ lines should contain one tourist route each. Every route should be printed in a form of " $ t $ $ v_{1} $ $ v_{2} $ ... $ v_{t+1} $ ", where $ t $ is a number of roads in a route and $ v_{1},v_{2},...,v_{t+1} $ — cities listed in the order they are visited on the route.

If there are multiple answers print any of them.

## 样例 #1

### 输入

```
6 4 4
1 2
2 3
4 5
5 6
1 3 4 6

```

### 输出

```
2
2 1 2 3
2 4 5 6

```

## 样例 #2

### 输入

```
4 3 4
1 2
1 3
1 4
1 2 3 4

```

### 输出

```
2
1 1 2
2 3 1 4

```



---

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

