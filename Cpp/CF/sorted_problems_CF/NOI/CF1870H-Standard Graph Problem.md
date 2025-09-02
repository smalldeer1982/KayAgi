---
title: "Standard Graph Problem"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1870H
tag: []
---

# Standard Graph Problem

## 题目描述

You are given a weighted directed graph with $ n $ vertices and $ m $ edges. Each vertex in the graph can be either highlighted or normal. Initially, all vertices are normal. The cost of the graph is defined as the minimum sum of edge weights that need to be selected so that from each normal vertex one can reach at least one highlighted vertex using the selected edges only. If it is not possible to select the edges, the cost is $ -1 $ instead.

Your task is to compute the cost of the graph after each of the $ q $ queries. The queries can be of two types:

- $ +\;v_i $ makes vertex $ v_i $ highlighted; it is guaranteed that the vertex is normal before the query.
- $ -\;v_i $ makes vertex $ v_i $ normal; it is guaranteed that the vertex is highlighted before the query.

Output the cost of the graph after each of the $ q $ queries.

## 输入格式

The first line contains three integers $ n $ , $ m $ , and $ q $ ( $ 3 \le n \le 2 \cdot 10^5, 1 \le m, q \le 2 \cdot 10^5 $ ) — the number of vertices in the graph, the number of edges, and the number of queries.

The next $ m $ lines contain the edges of the graph, one edge per line. The $ i $ -th line contains three integers $ u_i $ , $ v_i $ , and $ c_i $ ( $ 1 \leq u_i, v_i \leq n, u_i \ne v_i, 1 \leq c_i \leq 10^6 $ ) — the endpoints of the $ i $ -th edge (from $ u_i $ to $ v_i $ ) and its weight ( $ c_i $ ).

The next $ q $ lines contain the queries, one query per line. The $ i $ -th line contains $ +\;v_i $ , if it is a query of the first type, and $ -\;v_i $ , if it is a query of the second type ( $ 1 \leq v_i \leq n $ ).

## 输出格式

Output $ q $ numbers. The $ i $ -th number is the cost of the graph after the first $ i $ queries.

## 说明/提示

In the first test:

- After the first query, it is most profitable to select the edges with numbers $ 3, 4, 5 $ , their total cost is $ 15 $ .
- After the second query, there are no highlighted vertices, which means that there are no suitable sets of edges, the cost of the graph is $ -1 $ .
- After the third query, it is most profitable to select the edges with numbers $ 1, 2, 5 $ , their total cost is $ 14 $ .
- After the fourth query, it is most profitable to select the edges with numbers $ 4 $ and $ 5 $ , their total cost is $ 12 $ .
- After the fifth query, it is most profitable to select only edge number $ 5 $ , its cost is $ 4 $ .
- After the sixth query, all vertices are highlighted and there is no need to select any edges, the cost of the graph is $ 0 $ .

## 样例 #1

### 输入

```
4 5 6
1 2 1
2 3 5
3 2 3
4 1 8
2 1 4
+ 1
- 1
+ 3
+ 1
+ 4
+ 2
```

### 输出

```
15
-1
14
12
4
0
```

## 样例 #2

### 输入

```
10 14 10
8 6 4
2 5 1
3 5 4
1 6 3
1 3 7
7 2 1
6 1 3
4 10 1
4 6 5
5 4 1
5 8 10
10 9 1
9 5 1
9 7 6
+ 7
+ 8
- 7
+ 10
+ 2
- 10
+ 5
- 2
- 5
+ 3
```

### 输出

```
28
24
29
19
18
24
18
19
29
20
```

