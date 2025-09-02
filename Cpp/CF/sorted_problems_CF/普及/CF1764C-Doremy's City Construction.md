---
title: "Doremy's City Construction"
layout: "post"
diff: 普及/提高-
pid: CF1764C
tag: ['贪心']
---

# Doremy's City Construction

## 题目描述

Doremy's new city is under construction! The city can be regarded as a simple undirected graph with $ n $ vertices. The $ i $ -th vertex has altitude $ a_i $ . Now Doremy is deciding which pairs of vertices should be connected with edges.

Due to economic reasons, there should be no self-loops or multiple edges in the graph.

Due to safety reasons, there should not be pairwise distinct vertices $ u $ , $ v $ , and $ w $ such that $ a_u \leq a_v \leq a_w $ and the edges $ (u,v) $ and $ (v,w) $ exist.

Under these constraints, Doremy would like to know the maximum possible number of edges in the graph. Can you help her?

Note that the constructed graph is allowed to be disconnected.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2\cdot 10^5 $ ) — the number of vertices.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1\le a_i\le 10^6 $ ) — the altitudes of each vertex.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum possible number of edges in the graph.

## 说明/提示

In the first test case, there can only be at most $ 3 $ edges in the graph. A possible construction is to connect $ (1,3) $ , $ (2,3) $ , $ (3,4) $ . In the picture below the red number above node $ i $ is $ a_i $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/664da7a7b39c78efe9a85191f05318cb0a9df4d9.png)

The following list shows all such $ u $ , $ v $ , $ w $ that the edges $ (u,v) $ and $ (v,w) $ exist.

- $ u=1 $ , $ v=3 $ , $ w=2 $ ;
- $ u=1 $ , $ v=3 $ , $ w=4 $ ;
- $ u=2 $ , $ v=3 $ , $ w=1 $ ;
- $ u=2 $ , $ v=3 $ , $ w=4 $ ;
- $ u=4 $ , $ v=3 $ , $ w=1 $ ;
- $ u=4 $ , $ v=3 $ , $ w=2 $ .

Another possible construction is to connect $ (1,4) $ , $ (2,4) $ , $ (3,4) $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/7d1fc03a74b1366633e41dc227acef23827c0f69.png)

An unacceptable construction is to connect $ (1,3) $ , $ (2,3) $ , $ (2,4) $ , $ (3,4) $ . Because when $ u=4 $ , $ v=2 $ , $ w=3 $ , $ a_u\le a_v \le a_w $ holds, and the respective edges exist.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/02cccee9e8ea3921ef7338c4d1dd72e83e933cbc.png)

## 样例 #1

### 输入

```
4
4
2 2 3 1
6
5 2 3 1 5 2
12
7 2 4 9 1 4 6 3 7 4 2 3
4
1000000 1000000 1000000 1000000
```

### 输出

```
3
9
35
2
```

