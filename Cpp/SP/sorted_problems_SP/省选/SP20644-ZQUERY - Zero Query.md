---
title: "ZQUERY - Zero Query"
layout: "post"
diff: 省选/NOI-
pid: SP20644
tag: []
---

# ZQUERY - Zero Query

## 题目描述

[English](/problems/ZQUERY/en) [Vietnamese](/problems/ZQUERY/vn)Given an array having **N** elements, each element is either **-1** or **1**.

You have **M** queries, each query has two numbers **L** and **R**, you have to answer the length of the longest subarray in range **L** to **R** (inclusive) that its sum is equal to 0.

## 输入格式

The first line contains two numbers **N** and **M** (**1** <= **N**, **M** <= **50000**) - the number of elements and the number of queries.

The second line contains **N** numbers - the elements of the array, each element is either **-1** or **1**.

In the next **M** lines, each line contains two numbers **L** and **R** (**1** <= **L** <= **R** <= **N**).

## 输出格式

For each query, print the length of the longest subarray that satisfies the query in one line. If there isn't any such subarray, print 0.

## 样例 #1

### 输入

```
6 4
1 1 1 -1 -1 -1
1 3
1 4
1 5
1 6
```

### 输出

```
0
2
4
6
```

