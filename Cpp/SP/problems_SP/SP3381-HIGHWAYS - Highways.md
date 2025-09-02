---
title: "HIGHWAYS - Highways"
layout: "post"
diff: 普及/提高-
pid: SP3381
tag: []
---

# HIGHWAYS - Highways

## 题目描述

A number of cities are connected by a network of highways. Each highway is bidirectional and connects two cities, with a given travel time. What is the shortest time to get from a given city to another given city?

## 输入格式

The first line of input contains the number of test cases.  
  
 Each test case starts with a line containing the number of cities n (2   
 Then m lines follow, each describing one highway. The description consists of the two distinct city numbers and the time in minutes to travel along the highway. The time will be between 1 and 1000.
 
 首先输入一行一个整数，表示测试数据的组数。接着对于每一组测试数据，第一行四个整数，分别代表图中点的个数、边的条数、起点、终点。接下来 $m$ 行每行三个整数 $u$，$v$，$w$，代表从第 $u$ 个点到第 $v$ 个点间有一条长度为 $w$ 的无向道路连接。

## 输出格式

For each test case output a single line containing the minimum time it takes to get from the start to the destination. If no connection exists, output NONE.

数据范围：$2 \le n \le 10^5$，$1 \le m \le 10^5$，$1 \le w \le 10^3$。

## 样例 #1

### 输入

```
2
4 2 1 4
1 2 5
3 4 5
4 4 1 4
1 2 5
2 3 5
3 4 5
4 2 6
```

### 输出

```
NONE
11
```

