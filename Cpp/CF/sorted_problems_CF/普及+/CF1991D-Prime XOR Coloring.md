---
title: "Prime XOR Coloring"
layout: "post"
diff: 普及+/提高
pid: CF1991D
tag: ['数论', '位运算', 'Ad-hoc']
---

# Prime XOR Coloring

## 题目描述

You are given an undirected graph with $ n $ vertices, numbered from $ 1 $ to $ n $ . There is an edge between vertices $ u $ and $ v $ if and only if $ u \oplus v $ is a [prime number](https://en.wikipedia.org/wiki/Prime_number), where $ \oplus $ denotes the [bitwise XOR operator](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Color all vertices of the graph using the minimum number of colors, such that no two vertices directly connected by an edge have the same color.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ). The description of test cases follows.

The only line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the graph.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output two lines.

The first line should contain a single integer $ k $ ( $ 1 \le k \le n $ ) — the minimum number of colors required.

The second line should contain $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 1 \le c_i \le k $ ) — the color of each vertex.

If there are multiple solutions, output any of them.

## 说明/提示

In the first test case, the minimum number of colors is $ 1 $ , because there is only one vertex.

In the second test case, the minimum number of colors is $ 2 $ , because there is an edge connecting $ 1 $ and $ 2 $ ( $ 1 \oplus 2 = 3 $ , which is a prime number).

In the third test case, the minimum number of colors is still $ 2 $ , because $ 2 $ and $ 3 $ can be colored the same since there is no edge between $ 2 $ and $ 3 $ ( $ 2 \oplus 3 = 1 $ , which is not a prime number).

In the fourth test case, it can be shown that the minimum number of colors is $ 3 $ .

In the fifth test case, it can be shown that the minimum number of colors is $ 3 $ .

In the sixth test case, it can be shown that the minimum number of colors is $ 4 $ .

## 样例 #1

### 输入

```
6
1
2
3
4
5
6
```

### 输出

```
1
1
2
1 2
2
1 2 2
3
1 2 2 3
3
1 2 2 3 3
4
1 2 2 3 3 4
```

