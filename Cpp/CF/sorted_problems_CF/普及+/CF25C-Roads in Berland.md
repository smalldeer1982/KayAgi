---
title: "Roads in Berland"
layout: "post"
diff: 普及+/提高
pid: CF25C
tag: ['最短路']
---

# Roads in Berland

## 题目描述

There are $ n $ cities numbered from 1 to $ n $ in Berland. Some of them are connected by two-way roads. Each road has its own length — an integer number from 1 to 1000. It is known that from each city it is possible to get to any other city by existing roads. Also for each pair of cities it is known the shortest distance between them. Berland Government plans to build $ k $ new roads. For each of the planned road it is known its length, and what cities it will connect. To control the correctness of the construction of new roads, after the opening of another road Berland government wants to check the sum of the shortest distances between all pairs of cities. Help them — for a given matrix of shortest distances on the old roads and plans of all new roads, find out how the sum of the shortest distances between all pairs of cities changes after construction of each road.

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=300 $ ) — amount of cities in Berland. Then there follow $ n $ lines with $ n $ integer numbers each — the matrix of shortest distances. $ j $ -th integer in the $ i $ -th row — $ d_{i,j} $ , the shortest distance between cities $ i $ and $ j $ . It is guaranteed that $ d_{i,i}=0,d_{i,j}=d_{j,i} $ , and a given matrix is a matrix of shortest distances for some set of two-way roads with integer lengths from 1 to 1000, such that from each city it is possible to get to any other city using these roads.

Next line contains integer $ k $ ( $ 1<=k<=300 $ ) — amount of planned roads. Following $ k $ lines contain the description of the planned roads. Each road is described by three space-separated integers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ ( $ 1<=a_{i},b_{i}<=n,a_{i}≠b_{i},1<=c_{i}<=1000 $ ) — $ a_{i} $ and $ b_{i} $ — pair of cities, which the road connects, $ c_{i} $ — the length of the road. It can be several roads between a pair of cities, but no road connects the city with itself.

## 输出格式

Output $ k $ space-separated integers $ q_{i} $ ( $ 1<=i<=k $ ). $ q_{i} $ should be equal to the sum of shortest distances between all pairs of cities after the construction of roads with indexes from 1 to $ i $ . Roads are numbered from 1 in the input order. Each pair of cities should be taken into account in the sum exactly once, i. e. we count unordered pairs.

## 样例 #1

### 输入

```
2
0 5
5 0
1
1 2 3

```

### 输出

```
3 
```

## 样例 #2

### 输入

```
3
0 4 5
4 0 9
5 9 0
2
2 3 8
1 2 1

```

### 输出

```
17 12 
```

