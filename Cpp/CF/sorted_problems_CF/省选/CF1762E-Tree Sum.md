---
title: "Tree Sum"
layout: "post"
diff: 省选/NOI-
pid: CF1762E
tag: []
---

# Tree Sum

## 题目描述

Let us call an edge-weighted tree with $ n $ vertices numbered from $ 1 $ to $ n $ good if the weight of each edge is either $ 1 $ or $ -1 $ and for each vertex $ i $ , the product of the edge weights of all edges having $ i $ as one endpoint is $ -1 $ .

You are given a positive integer $ n $ . There are $ n^{n-2} \cdot 2^{n-1} $ distinct $ ^\dagger $ edge-weighted trees with $ n $ vertices numbered from $ 1 $ to $ n $ such that each edge is either $ 1 $ or $ -1 $ . Your task is to find the sum of $ d(1,n)^\ddagger $ of all such trees that are good. Since the answer can be quite large, you only need to find it modulo $ 998\,244\,353 $ .

 $ ^\dagger $ Two trees are considered to be distinct if either:

- there exists two vertices such that there is an edge between them in one of the trees, and not in the other.
- there exists two vertices such that there is an edge between them in both trees but the weight of the edge between them in one tree is different from the one in the other tree.

Note that by [Cayley's formula](https://rb.gy/hho7vu), the number of trees on $ n $ labeled vertices is $ n^{n-2} $ . Since we have $ n-1 $ edges, there are $ 2^{n-1} $ possible assignment of weights(weight can either be $ 1 $ or $ -1 $ ). That is why total number of distinct edge-weighted tree is $ n^{n-2} \cdot 2^{n-1} $ .

 $ ^\ddagger $ $ d(u,v) $ denotes the sum of the weight of all edges on the unique simple path from $ u $ to $ v $ .

## 输入格式

The first and only line of input contains a single integer $ n $ ( $ 1 \leq n \leq 5 \cdot 10^5 $ ).

## 输出格式

The only line of output should contain a single integer, the required answer, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, there is only $ 1 $ distinct good tree. The value of $ d(1,2) $ for that tree is $ -1 $ , which is $ 998\,244\,352 $ under modulo $ 998\,244\,353 $ .

In the second test case, the value of $ d(1,1) $ for any tree is $ 0 $ , so the answer is $ 0 $ .

In the third test case, there are $ 16 $ distinct good trees. The value of $ d(1,4) $ is:

- $ -2 $ for $ 2 $ trees;
- $ -1 $ for $ 8 $ trees;
- $ 0 $ for $ 4 $ trees;
- $ 1 $ for $ 2 $ trees.

The sum of $ d(1,4) $ over all trees is $ 2 \cdot (-2) + 8 \cdot (-1) + 4 \cdot (0) + 2 \cdot (1) = -10 $ , which is $ 998\,244\,343 $ under modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
2
```

### 输出

```
998244352
```

## 样例 #2

### 输入

```
1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
```

### 输出

```
998244343
```

## 样例 #4

### 输入

```
10
```

### 输出

```
948359297
```

## 样例 #5

### 输入

```
43434
```

### 输出

```
86232114
```

