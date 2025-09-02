---
title: "Serega and Fun"
layout: "post"
diff: 省选/NOI-
pid: CF455D
tag: []
---

# Serega and Fun

## 题目描述

Serega loves fun. However, everyone has fun in the unique manner. Serega has fun by solving query problems. One day Fedor came up with such a problem.

You are given an array $ a $ consisting of $ n $ positive integers and queries to it. The queries can be of two types:

1. Make a unit cyclic shift to the right on the segment from $ l $ to $ r $ (both borders inclusive). That is rearrange elements of the array in the following manner: $ a[l],a[l+1],...,a[r-1],a[r]→a[r],a[l],a[l+1],...,a[r-1]. $
2. Count how many numbers equal to $ k $ are on the segment from $ l $ to $ r $ (both borders inclusive).

Fedor hurried to see Serega enjoy the problem and Serega solved it really quickly. Let's see, can you solve it?

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of elements of the array. The second line contains $ n $ integers $ a[1],a[2],...,a[n] $ ( $ 1<=a[i]<=n $ ).

The third line contains a single integer $ q $ ( $ 1<=q<=10^{5} $ ) — the number of queries. The next $ q $ lines contain the queries.

As you need to respond to the queries online, the queries will be encoded. A query of the first type will be given in format: $ 1 $ $ l'_{i} $ $ r'_{i} $ . A query of the second type will be given in format: $ 2 $ $ l'_{i} $ $ r'_{i} $ $ k'_{i} $ . All the number in input are integer. They satisfy the constraints: $ 1<=l'_{i},r'_{i},k'_{i}<=n $ .

To decode the queries from the data given in input, you need to perform the following transformations:

 $ l_{i}=((l'_{i}+lastans-1) mod n)+1; r_{i}=((r'_{i}+lastans-1) mod n)+1; k_{i}=((k'_{i}+lastans-1) mod n)+1. $ Where $ lastans $ is the last reply to the query of the 2-nd type (initially, $ lastans=0 $ ). If after transformation $ l_{i} $ is greater than $ r_{i} $ , you must swap these values.

## 输出格式

For each query of the 2-nd type print the answer on a single line.

## 样例 #1

### 输入

```
7
6 6 2 7 4 2 5
7
1 3 6
2 2 4 2
2 2 4 7
2 2 2 5
1 2 6
1 1 4
2 1 7 3

```

### 输出

```
2
1
0
0

```

## 样例 #2

### 输入

```
8
8 4 2 2 7 7 8 8
8
1 8 8
2 8 1 7
1 8 1
1 7 3
2 8 8 3
1 1 4
1 2 7
1 4 5

```

### 输出

```
2
0

```

