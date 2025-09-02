---
title: "Counting Shortcuts"
layout: "post"
diff: 普及+/提高
pid: CF1650G
tag: ['动态规划 DP', '图论']
---

# Counting Shortcuts

## 题目描述

Given an undirected connected graph with $ n $ vertices and $ m $ edges. The graph contains no loops (edges from a vertex to itself) and multiple edges (i.e. no more than one edge between each pair of vertices). The vertices of the graph are numbered from $ 1 $ to $ n $ .

Find the number of paths from a vertex $ s $ to $ t $ whose length differs from the shortest path from $ s $ to $ t $ by no more than $ 1 $ . It is necessary to consider all suitable paths, even if they pass through the same vertex or edge more than once (i.e. they are not simple).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650G/3360dade3a147f98c6dd4b25980520a2ae6123a6.png)Graph consisting of $ 6 $ of vertices and $ 8 $ of edgesFor example, let $ n = 6 $ , $ m = 8 $ , $ s = 6 $ and $ t = 1 $ , and let the graph look like the figure above. Then the length of the shortest path from $ s $ to $ t $ is $ 1 $ . Consider all paths whose length is at most $ 1 + 1 = 2 $ .

- $ 6 \rightarrow 1 $ . The length of the path is $ 1 $ .
- $ 6 \rightarrow 4 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 2 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 5 \rightarrow 1 $ . Path length is $ 2 $ .

There is a total of $ 4 $ of matching paths.

## 输入格式

The first line of test contains the number $ t $ ( $ 1 \le t \le 10^4 $ ) —the number of test cases in the test.

Before each test case, there is a blank line.

The first line of test case contains two numbers $ n, m $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le m \le 2 \cdot 10^5 $ ) —the number of vertices and edges in the graph.

The second line contains two numbers $ s $ and $ t $ ( $ 1 \le s, t \le n $ , $ s \neq t $ ) —the numbers of the start and end vertices of the path.

The following $ m $ lines contain descriptions of edges: the $ i $ th line contains two integers $ u_i $ , $ v_i $ ( $ 1 \le u_i,v_i \le n $ ) — the numbers of vertices that connect the $ i $ th edge. It is guaranteed that the graph is connected and does not contain loops and multiple edges.

It is guaranteed that the sum of values $ n $ on all test cases of input data does not exceed $ 2 \cdot 10^5 $ . Similarly, it is guaranteed that the sum of values $ m $ on all test cases of input data does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single number — the number of paths from $ s $ to $ t $ such that their length differs from the length of the shortest path by no more than $ 1 $ .

Since this number may be too large, output it modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
4

4 4
1 4
1 2
3 4
2 3
2 4

6 8
6 1
1 4
1 6
1 5
1 2
5 6
4 6
6 3
2 6

5 6
1 3
3 5
5 4
3 1
4 2
2 1
1 4

8 18
5 1
2 1
3 1
4 2
5 2
6 5
7 3
8 4
6 4
8 7
1 4
4 7
1 6
6 7
3 8
8 5
4 5
4 3
8 2
```

### 输出

```
2
4
1
11
```

