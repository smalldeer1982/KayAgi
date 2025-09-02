---
title: "The Classic Problem"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF464E
tag: ['最短路', '可持久化线段树', '哈希 hashing']
---

# The Classic Problem

## 题目描述

You are given a weighted undirected graph on $ n $ vertices and $ m $ edges. Find the shortest path from vertex $ s $ to vertex $ t $ or else state that such path doesn't exist.

## 输入格式

The first line of the input contains two space-separated integers — $ n $ and $ m $ ( $ 1<=n<=10^{5} $ ; $ 0<=m<=10^{5} $ ).

Next $ m $ lines contain the description of the graph edges. The $ i $ -th line contains three space-separated integers — $ u_{i} $ , $ v_{i} $ , $ x_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ; $ 0<=x_{i}<=10^{5} $ ). That means that vertices with numbers $ u_{i} $ and $ v_{i} $ are connected by edge of length $ 2^{x_{i}} $ (2 to the power of $ x_{i} $ ).

The last line contains two space-separated integers — the numbers of vertices $ s $ and $ t $ .

The vertices are numbered from $ 1 $ to $ n $ . The graph contains no multiple edges and self-loops.

## 输出格式

In the first line print the remainder after dividing the length of the shortest path by $ 1000000007 (10^{9}+7) $ if the path exists, and -1 if the path doesn't exist.

If the path exists print in the second line integer $ k $ — the number of vertices in the shortest path from vertex $ s $ to vertex $ t $ ; in the third line print $ k $ space-separated integers — the vertices of the shortest path in the visiting order. The first vertex should be vertex $ s $ , the last vertex should be vertex $ t $ . If there are multiple shortest paths, print any of them.

## 说明/提示

A path from vertex $ s $ to vertex $ t $ is a sequence $ v_{0} $ , ..., $ v_{k} $ , such that $ v_{0}=s $ , $ v_{k}=t $ , and for any $ i $ from 0 to $ k-1 $ vertices $ v_{i} $ and $ v_{i+1} $ are connected by an edge.

The length of the path is the sum of weights of edges between $ v_{i} $ and $ v_{i+1} $ for all $ i $ from 0 to $ k-1 $ .

The shortest path from $ s $ to $ t $ is the path which length is minimum among all possible paths from $ s $ to $ t $ .

## 样例 #1

### 输入

```
4 4
1 4 2
1 2 0
2 3 0
3 4 0
1 4

```

### 输出

```
3
4
1 2 3 4 

```

## 样例 #2

### 输入

```
4 3
1 2 4
2 3 5
3 4 6
1 4

```

### 输出

```
112
4
1 2 3 4 

```

## 样例 #3

### 输入

```
4 2
1 2 0
3 4 1
1 4

```

### 输出

```
-1

```



---

---
title: "Matvey's Birthday"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF718E
tag: ['枚举', '最短路', '进制']
---

# Matvey's Birthday

## 题目描述

Today is Matvey's birthday. He never knows what to ask as a present so friends gave him a string $ s $ of length $ n $ . This string consists of only first eight English letters: 'a', 'b', $ ... $ , 'h'.

First question that comes to mind is: who might ever need some string? Matvey is a special boy so he instantly found what to do with this string. He used it to build an undirected graph where vertices correspond to position in the string and there is an edge between distinct positions $ a $ and $ b $ ( $ 1<=a,b<=n $ ) if at least one of the following conditions hold:

1. $ a $ and $ b $ are neighbouring, i.e. $ |a-b|=1 $ .
2. Positions $ a $ and $ b $ contain equal characters, i.e. $ s_{a}=s_{b} $ .

Then Matvey decided to find the diameter of this graph. Diameter is a maximum distance (length of the shortest path) among all pairs of vertices. Also, Matvey wants to find the number of pairs of vertices such that the distance between them is equal to the diameter of the graph. As he is very cool and experienced programmer he managed to solve this problem very fast. Will you do the same?

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=100000 $ ) — the length of the string.

The second line contains the string $ s $ itself. It's guaranteed that $ s $ consists of only first eight letters of English alphabet.

## 输出格式

Print two integers — the diameter of the graph and the number of pairs of positions with the distance equal to the diameter.

## 说明/提示

Consider the second sample.

The maximum distance is $ 2 $ . It's obtained for pairs $ (1,4) $ , $ (2,4) $ , $ (4,6) $ and $ (4,7) $ .

## 样例 #1

### 输入

```
3
abc

```

### 输出

```
2 1

```

## 样例 #2

### 输入

```
7
aaabaaa

```

### 输出

```
2 4

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

