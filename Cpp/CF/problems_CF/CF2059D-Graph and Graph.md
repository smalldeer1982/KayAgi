---
title: "Graph and Graph"
layout: "post"
diff: 难度0
pid: CF2059D
tag: []
---

# Graph and Graph

## 题目描述

You are given two connected undirected graphs with the same number of vertices. In both graphs, there is a token located at some vertex. In the first graph, the token is initially at vertex $ s_1 $ , and in the second graph, the token is initially at vertex $ s_2 $ . The following operation is repeated an infinite number of times:

- Let the token currently be at vertex $ v_1 $ in the first graph and at vertex $ v_2 $ in the second graph.
- A vertex $ u_1 $ , adjacent to $ v_1 $ , is chosen in the first graph.
- A vertex $ u_2 $ , adjacent to $ v_2 $ , is chosen in the second graph.
- The tokens are moved to the chosen vertices: in the first graph, the token moves from $ v_1 $ to $ u_1 $ , and in the second graph, from $ v_2 $ to $ u_2 $ .
- The cost of such an operation is equal to $ |u_1 - u_2| $ .

Determine the minimum possible total cost of all operations or report that this value will be infinitely large.

## 输入格式

Each test consists of multiple test cases. The first line contains one integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains three integers $ n $ , $ s_1 $ , and $ s_2 $ ( $ 2 \le n \le 1000 $ , $ 1 \le s_1, s_2 \le n $ ) — the number of vertices in each graph, the number of the vertex in the first graph where the token is initially located, and the number of the vertex in the second graph where the token is initially located.

The second line of each test case contains one integer $ m_1 $ ( $ 1 \le m_1 \le 1000 $ ) — the number of edges in the first graph.

The $ i $ -th of the following $ m_1 $ lines contains two integers $ a_i $ and $ b_i $ ( $ 1 \le a_i, b_i \le n $ , $ a_i \ne b_i $ ) — the numbers of the endpoints of the $ i $ -th edge in the first graph.

The next line of each test case contains one integer $ m_2 $ ( $ 1 \le m_2 \le 1000 $ ) — the number of edges in the second graph.

The $ j $ -th of the following $ m_2 $ lines contains two integers $ c_j $ and $ d_j $ ( $ 1 \le c_j, d_j \le n $ , $ c_j \ne d_j $ ) — the numbers of the endpoints of the $ j $ -th edge in the second graph.

It is guaranteed that the sum of $ n $ , the sum of $ m_1 $ , and the sum of $ m_2 $ over all test cases do not exceed $ 1000 $ .

It is guaranteed that both graphs are connected.

## 输出格式

For each test case, output one integer — the minimum total cost of all operations or $ -1 $ , if this value will be infinitely large.

## 说明/提示

In the first test case, an infinite sequence of transitions can be constructed to the vertices $ 2, 3, 4, 1, 2, 3, 4, 1, \ldots $ , along which the token can move in both the first and the second graphs.

In the second test case, it can be proven that the cost of any operation will be greater than $ 0 $ ; therefore, the total cost of all operations will be infinitely large.

## 样例 #1

### 输入

```
3
4 1 1
4
1 2
2 3
3 4
4 1
4
1 2
2 3
3 4
4 1
4 1 2
4
1 2
2 3
3 4
4 1
4
1 2
2 3
3 4
4 1
7 7 2
7
1 6
2 1
3 2
3 4
5 1
7 3
7 5
6
5 1
5 6
5 7
6 3
7 2
7 4
```

### 输出

```
0
-1
7
```

