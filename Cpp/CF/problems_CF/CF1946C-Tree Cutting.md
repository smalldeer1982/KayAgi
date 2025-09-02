---
title: "Tree Cutting"
layout: "post"
diff: 普及/提高-
pid: CF1946C
tag: ['图论', '二分']
---

# Tree Cutting

## 题目描述

You are given a tree with $ n $ vertices.

Your task is to find the maximum number $ x $ such that it is possible to remove exactly $ k $ edges from this tree in such a way that the size of each remaining connected component $ ^{\dagger} $ is at least $ x $ .

 $ ^{\dagger} $ Two vertices $ v $ and $ u $ are in the same connected component if there exists a sequence of numbers $ t_1, t_2, \ldots, t_k $ of arbitrary length $ k $ , such that $ t_1 = v $ , $ t_k = u $ , and for each $ i $ from $ 1 $ to $ k - 1 $ , vertices $ t_i $ and $ t_{i+1} $ are connected by an edge.

## 输入格式

Each test consists of several sets of input data. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of sets of input data. This is followed by a description of the sets of input data.

The first line of each set of input data contains two integers $ n $ and $ k $ ( $ 1 \le k < n \le 10^5 $ ) — the number of vertices in the tree and the number of edges to be removed.

Each of the next $ n - 1 $ lines of each set of input data contains two integers $ v $ and $ u $ ( $ 1 \le v, u \le n $ ) — the next edge of the tree.

It is guaranteed that the sum of the values of $ n $ for all sets of input data does not exceed $ 10^5 $ .

## 输出格式

For each set of input data, output a single line containing the maximum number $ x $ such that it is possible to remove exactly $ k $ edges from the tree in such a way that the size of each remaining connected component is at least $ x $ .

## 说明/提示

The tree in the first set of input data:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/832ffb4f88c37ab14f5b7a9eaac2d6382d506053.png)After removing the edge $ 1 $ — $ 3 $ , the tree will look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/fbcdbb17592694a687d8cacf2d552a9f2e19b5fc.png)The tree has split into two connected components. The first component consists of two vertices: $ 1 $ and $ 2 $ . The second connected component consists of three vertices: $ 3, 4 $ and $ 5 $ . In both connected components, there are at least two vertices. It can be shown that the answer $ 3 $ is not achievable, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
6
5 1
1 2
1 3
3 4
3 5
2 1
1 2
6 1
1 2
2 3
3 4
4 5
5 6
3 1
1 2
1 3
8 2
1 2
1 3
2 4
2 5
3 6
3 7
3 8
6 2
1 2
2 3
1 4
4 5
5 6
```

### 输出

```
2
1
3
1
1
2
```

