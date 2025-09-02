---
title: "DISQUERY - Distance Query"
layout: "post"
diff: 普及+/提高
pid: SP3978
tag: ['最近公共祖先 LCA', '树链剖分', '概率论']
---

# DISQUERY - Distance Query

## 题目描述

 [English](/problems/DISQUERY/en/) [Vietnamese](/problems/DISQUERY/vn/)The traffic network in a country consists of N cities (labeled with integers from 1 to N) and N-1 roads connecting the cities. There is a unique path between each pair of different cities, and we know the exact length of each road.

Write a program that will, for each of the K given pairs of cities, find the length of the shortest and the length of the longest road on the path between the two cities.

### Input

The first line of input contains an integer N, 2

The length of each road will be a positive integer less than or equal to 1 000 000.   
 The next line contains an integer K, 1

### Output

Each of the K lines of output should contain two integers – the lengths from the task description for the corresponding pair of the cities.


## 样例 #1

### 输入

```
5
2 3 100
4 3 200
1 5 150
1 3 50
3
2 4
3 5
1 2

```

### 输出

```
100 200
50 150
50 100

```

## 样例 #2

### 输入

```
7
3 6 4
1 7 1
1 3 2
1 2 6
2 5 4
2 4 4
5
6 4
7 6
1 2
1 3
3 5

```

### 输出

```
2 6
1 4
6 6
2 2
2 6

```

