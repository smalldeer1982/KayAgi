# 题目信息

# The Classic Problem

## 题目描述

You are given a weighted undirected graph on $ n $ vertices and $ m $ edges. Find the shortest path from vertex $ s $ to vertex $ t $ or else state that such path doesn't exist.

## 说明/提示

A path from vertex $ s $ to vertex $ t $ is a sequence $ v_{0} $ , ..., $ v_{k} $ , such that $ v_{0}=s $ , $ v_{k}=t $ , and for any $ i $ from 0 to $ k-1 $ vertices $ v_{i} $ and $ v_{i+1} $ are connected by an edge.

The length of the path is the sum of weights of edges between $ v_{i} $ and $ v_{i+1} $ for all $ i $ from 0 to $ k-1 $ .

The shortest path from $ s $ to $ t $ is the path which length is minimum among all possible paths from $ s $ to $ t $ .

## 样例 #1

### 输入

```
4 4
1 4 2
1 2 0
2 3 0
3 4 0
1 4
```

### 输出

```
3
4
1 2 3 4 
```

## 样例 #2

### 输入

```
4 3
1 2 4
2 3 5
3 4 6
1 4
```

### 输出

```
112
4
1 2 3 4 
```

## 样例 #3

### 输入

```
4 2
1 2 0
3 4 1
1 4
```

### 输出

```
-1
```

# AI分析结果



---
处理用时：182.28秒