---
title: "Graph Coloring (hard version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1792F2
tag: ['动态规划 DP', '图论', '组合数学', '快速数论变换 NTT']
---

# Graph Coloring (hard version)

## 题目描述

The only difference between the easy and the hard version is the constraint on $ n $ .

You are given an undirected complete graph on $ n $ vertices. A complete graph is a graph where each pair of vertices is connected by an edge. You have to paint the edges of the graph into two colors, red and blue (each edge will have one color).

A set of vertices $ S $ is red-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through red edges and vertices from $ S $ . Similarly, a set of vertices $ S $ is blue-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through blue edges and vertices from $ S $ .

You have to paint the graph in such a way that:

- there is at least one red edge;
- there is at least one blue edge;
- for each set of vertices $ S $ such that $ |S| \ge 2 $ , $ S $ is either red-connected or blue-connected, but not both.

Calculate the number of ways to paint the graph, and print it modulo $ 998244353 $ .

## 输入格式

The first (and only) line contains one integer $ n $ ( $ 3 \le n \le 5 \cdot 10^4 $ ).

## 输出格式

Print one integer — the number of ways to paint the graph, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
```

### 输出

```
50
```

## 样例 #3

### 输入

```
100
```

### 输出

```
878752271
```

## 样例 #4

### 输入

```
1337
```

### 输出

```
520628749
```

## 样例 #5

### 输入

```
42013
```

### 输出

```
906821221
```



---

---
title: "Points and Segments"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF429E
tag: ['图论', '离散化', '二分图']
---

# Points and Segments

## 题目描述

Iahub isn't well prepared on geometry problems, but he heard that this year there will be a lot of geometry problems on the IOI selection camp. Scared, Iahub locked himself in the basement and started thinking of new problems of this kind. One of them is the following.

Iahub wants to draw $ n $ distinct segments $ [l_{i},r_{i}] $ on the $ OX $ axis. He can draw each segment with either red or blue. The drawing is good if and only if the following requirement is met: for each point $ x $ of the $ OX $ axis consider all the segments that contains point $ x $ ; suppose, that $ r_{x} $ red segments and $ b_{x} $ blue segments contain point $ x $ ; for each point $ x $ inequality $ |r_{x}-b_{x}|<=1 $ must be satisfied.

A segment $ [l,r] $ contains a point $ x $ if and only if $ l<=x<=r $ .

Iahub gives you the starting and ending points of all the segments. You have to find any good drawing for him.

## 输入格式

The first line of input contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of segments. The $ i $ -th of the next $ n $ lines contains two integers $ l_{i} $ and $ r_{i} $ ( $ 0<=l_{i}<=r_{i}<=10^{9} $ ) — the borders of the $ i $ -th segment.

It's guaranteed that all the segments are distinct.

## 输出格式

If there is no good drawing for a given test, output a single integer -1. Otherwise output $ n $ integers; each integer must be 0 or 1. The $ i $ -th number denotes the color of the $ i $ -th segment (0 is red and 1 is blue).

If there are multiple good drawings you can output any of them.

## 样例 #1

### 输入

```
2
0 2
2 3

```

### 输出

```
0 1

```

## 样例 #2

### 输入

```
6
1 5
1 3
3 5
2 10
11 11
12 12

```

### 输出

```
0 1 0 1 0 0

```



---

