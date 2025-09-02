---
title: "Making It Bipartite"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1630F
tag: []
---

# Making It Bipartite

## 题目描述

You are given an undirected graph of $ n $ vertices indexed from $ 1 $ to $ n $ , where vertex $ i $ has a value $ a_i $ assigned to it and all values $ a_i $ are different. There is an edge between two vertices $ u $ and $ v $ if either $ a_u $ divides $ a_v $ or $ a_v $ divides $ a_u $ .

Find the minimum number of vertices to remove such that the remaining graph is bipartite, when you remove a vertex you remove all the edges incident to it.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5\cdot10^4 $ ) — the number of vertices in the graph.

The second line of each test case contains $ n $ integers, the $ i $ -th of them is the value $ a_i $ ( $ 1 \le a_i \le 5\cdot10^4 $ ) assigned to the $ i $ -th vertex, all values $ a_i $ are different.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5\cdot10^4 $ .

## 输出格式

For each test case print a single integer — the minimum number of vertices to remove such that the remaining graph is bipartite.

## 说明/提示

In the first test case if we remove the vertices with values $ 1 $ and $ 2 $ we will obtain a bipartite graph, so the answer is $ 2 $ , it is impossible to remove less than $ 2 $ vertices and still obtain a bipartite graph.

 BeforeAfter![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1630F/942c26248b7d172f5cdc09acd9d7537a30e3800a.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1630F/bc5251b7b4c65e753205357055524fdabbab189f.png)test case #1In the second test case we do not have to remove any vertex because the graph is already bipartite, so the answer is $ 0 $ .

 BeforeAfter![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1630F/e14c807620a684d1c42eae27e1634f3f79d2b591.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1630F/e14c807620a684d1c42eae27e1634f3f79d2b591.png)test case #2In the third test case we only have to remove the vertex with value $ 12 $ , so the answer is $ 1 $ .

 BeforeAfter![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1630F/0e274acd7bb55f89f89b1e0e170ad88f96e25ebb.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1630F/58073552a235882d99e254b667a8c605aab677e0.png)test case #3In the fourth test case we remove the vertices with values $ 2 $ and $ 195 $ , so the answer is $ 2 $ .

 BeforeAfter![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1630F/e6ab60dbaacd357dd6018ee973b8769b11114587.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1630F/e741a3508bfca233ca2a287cefbb0585172278f0.png)test case #4

## 样例 #1

### 输入

```
4
4
8 4 2 1
4
30 2 3 5
5
12 4 6 2 3
10
85 195 5 39 3 13 266 154 14 2
```

### 输出

```
2
0
1
2
```

