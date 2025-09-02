---
title: "Distributed Join"
layout: "post"
diff: 普及/提高-
pid: CF457B
tag: []
---

# Distributed Join

## 题目描述

Piegirl was asked to implement two table join operation for distributed database system, minimizing the network traffic.

Suppose she wants to join two tables, $ A $ and $ B $ . Each of them has certain number of rows which are distributed on different number of partitions. Table $ A $ is distributed on the first cluster consisting of $ m $ partitions. Partition with index $ i $ has $ a_{i} $ rows from $ A $ . Similarly, second cluster containing table $ B $ has $ n $ partitions, $ i $ -th one having $ b_{i} $ rows from $ B $ .

In one network operation she can copy one row from any partition to any other partition. At the end, for each row from $ A $ and each row from $ B $ there should be a partition that has both rows. Determine the minimal number of network operations to achieve this.

## 输入格式

First line contains two integer numbers, $ m $ and $ n $ ( $ 1<=m,n<=10^{5} $ ). Second line contains description of the first cluster with $ m $ space separated integers, $ a_{i} $ $ (1<=a_{i}<=10^{9}) $ . Similarly, third line describes second cluster with $ n $ space separated integers, $ b_{i} $ $ (1<=b_{i}<=10^{9}) $ .

## 输出格式

Print one integer — minimal number of copy operations.

## 说明/提示

In the first example it makes sense to move all the rows to the second partition of the second cluster which is achieved in $ 2+6+3=11 $ operations

In the second example Piegirl can copy each row from $ B $ to the both partitions of the first cluster which needs $ 2·3=6 $ copy operations.

## 样例 #1

### 输入

```
2 2
2 6
3 100

```

### 输出

```
11

```

## 样例 #2

### 输入

```
2 3
10 10
1 1 1

```

### 输出

```
6

```

