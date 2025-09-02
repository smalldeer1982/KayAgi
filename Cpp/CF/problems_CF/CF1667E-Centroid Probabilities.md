---
title: "Centroid Probabilities"
layout: "post"
diff: 省选/NOI-
pid: CF1667E
tag: ['动态规划 DP', '快速傅里叶变换 FFT']
---

# Centroid Probabilities

## 题目描述

Consider every tree (connected undirected acyclic graph) with $ n $ vertices ( $ n $ is odd, vertices numbered from $ 1 $ to $ n $ ), and for each $ 2 \le i \le n $ the $ i $ -th vertex is adjacent to exactly one vertex with a smaller index.

For each $ i $ ( $ 1 \le i \le n $ ) calculate the number of trees for which the $ i $ -th vertex will be the centroid. The answer can be huge, output it modulo $ 998\,244\,353 $ .

A vertex is called a centroid if its removal splits the tree into subtrees with at most $ (n-1)/2 $ vertices each.

## 输入格式

The first line contains an odd integer $ n $ ( $ 3 \le n < 2 \cdot 10^5 $ , $ n $ is odd) — the number of the vertices in the tree.

## 输出格式

Print $ n $ integers in a single line, the $ i $ -th integer is the answer for the $ i $ -th vertex (modulo $ 998\,244\,353 $ ).

## 说明/提示

Example $ 1 $ : there are two possible trees: with edges $ (1-2) $ , and $ (1-3) $ — here the centroid is $ 1 $ ; and with edges $ (1-2) $ , and $ (2-3) $ — here the centroid is $ 2 $ . So the answer is $ 1, 1, 0 $ .

Example $ 2 $ : there are $ 24 $ possible trees, for example with edges $ (1-2) $ , $ (2-3) $ , $ (3-4) $ , and $ (4-5) $ . Here the centroid is $ 3 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
1 1 0
```

## 样例 #2

### 输入

```
5
```

### 输出

```
10 10 4 0 0
```

## 样例 #3

### 输入

```
7
```

### 输出

```
276 276 132 36 0 0 0
```

