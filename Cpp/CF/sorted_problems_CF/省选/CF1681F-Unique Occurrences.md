---
title: "Unique Occurrences"
layout: "post"
diff: 省选/NOI-
pid: CF1681F
tag: ['树形 DP', '动态树 LCT']
---

# Unique Occurrences

## 题目描述

You are given a tree, consisting of $ n $ vertices. Each edge has an integer value written on it.

Let $ f(v, u) $ be the number of values that appear exactly once on the edges of a simple path between vertices $ v $ and $ u $ .

Calculate the sum of $ f(v, u) $ over all pairs of vertices $ v $ and $ u $ such that $ 1 \le v < u \le n $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 5 \cdot 10^5 $ ) — the number of vertices in the tree.

Each of the next $ n-1 $ lines contains three integers $ v, u $ and $ x $ ( $ 1 \le v, u, x \le n $ ) — the description of an edge: the vertices it connects and the value written on it.

The given edges form a tree.

## 输出格式

Print a single integer — the sum of $ f(v, u) $ over all pairs of vertices $ v $ and $ u $ such that $ v < u $ .

## 样例 #1

### 输入

```
3
1 2 1
1 3 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
1 2 2
1 3 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
1 4 4
1 2 3
3 4 4
4 5 5
```

### 输出

```
14
```

## 样例 #4

### 输入

```
2
2 1 1
```

### 输出

```
1
```

## 样例 #5

### 输入

```
10
10 2 3
3 8 8
4 8 9
5 8 5
3 10 7
7 8 2
5 6 6
9 3 4
1 6 3
```

### 输出

```
120
```

