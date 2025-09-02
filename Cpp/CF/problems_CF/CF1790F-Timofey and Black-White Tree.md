---
title: "Timofey and Black-White Tree"
layout: "post"
diff: 提高+/省选-
pid: CF1790F
tag: []
---

# Timofey and Black-White Tree

## 题目描述

Timofey came to a famous summer school and found a tree on $ n $ vertices. A tree is a connected undirected graph without cycles.

Every vertex of this tree, except $ c_0 $ , is colored white. The vertex $ c_0 $ is colored black.

Timofey wants to color all the vertices of this tree in black. To do this, he performs $ n - 1 $ operations. During the $ i $ -th operation, he selects the vertex $ c_i $ , which is currently white, and paints it black.

Let's call the positivity of tree the minimum distance between all pairs of different black vertices in it. The distance between the vertices $ v $ and $ u $ is the number of edges on the path from $ v $ to $ u $ .

After each operation, Timofey wants to know the positivity of the current tree.

## 输入格式

The first line contains the integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains the integers $ n, c_0 $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le c_0 \le n $ ) — the number of vertices in the tree and index of the initial black vertex.

The second line of each testcase contains $ n - 1 $ unique integers $ c_1, c_2, \dots, c_{n-1} $ ( $ 1 \le c_i \le n $ , $ c_i \ne c_0 $ ), where $ c_i $ is the vertex which is colored black during the $ i $ -th operation.

Each of the next $ n - 1 $ row of each testcase contains the integers $ v_i, u_i $ ( $ 1 \le v_i, u_i \le n $ ) — edges in the tree.

It is guaranteed that the sum of $ n $ for all testcases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, print $ n - 1 $ integer on a separate line.

The integer with index $ i $ must be equal to positivity of the tree obtained by the first $ i $ operations.

## 说明/提示

In the first testcase, after the second operation, the tree looks like this: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1790F/a32165e192e2b6f9339d786991ed5f6c93b66d14.png)

The distance between vertices $ 1 $ and $ 6 $ is $ 3 $ , the distance between vertices $ 4 $ and $ 6 $ is $ 3 $ , the distance between vertices $ 1 $ and $ 4 $ is $ 2 $ . The positivity of this tree is equal to the minimum of these distances. It equals $ 2 $ .

In the third testcase, after the fourth operation, the tree looks like this: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1790F/fd53da75cc7d2ed2c5c7b22e26af36d60231a33d.png)

The positivity of this tree is $ 2 $ .

## 样例 #1

### 输入

```
6
6 6
4 1 3 5 2
2 4
6 5
5 3
3 4
1 3
4 2
4 1 3
3 1
2 3
1 4
10 3
10 7 6 5 2 9 8 1 4
1 2
1 3
4 5
4 3
6 4
8 7
9 8
10 8
1 8
7 3
7 5 1 2 4 6
1 2
3 2
4 5
3 4
6 5
7 6
9 7
9 3 1 4 2 6 8 5
4 1
8 9
4 8
2 6
7 3
2 4
3 5
5 4
10 2
1 8 5 10 6 9 4 3 7
10 7
7 8
3 6
9 7
7 6
4 2
1 6
7 5
9 2
```

### 输出

```
3 2 1 1 1 
3 1 1 
3 2 2 2 2 2 1 1 1 
4 2 2 1 1 1 
5 1 1 1 1 1 1 1 
4 3 2 2 1 1 1 1 1
```

