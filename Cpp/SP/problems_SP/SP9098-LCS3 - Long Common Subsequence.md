---
title: "LCS3 - Long Common Subsequence"
layout: "post"
diff: 普及+/提高
pid: SP9098
tag: []
---

# LCS3 - Long Common Subsequence

## 题目描述

Given a sequence of N(1<=N<=1000000) numbers range from 0 to 10000 and several other sequence of M(0<=M<=5) numbers, you have to compute the Longest Common Subsequence of this sequences with the main sequence.

## 输入格式

First line of the input will be N the number of elements of the main sequence. After that line there will be N numbers in one or more lines. Each of this number will be between 0 to 10000(inclusive). Then there will be Q(1<=Q<=5000) the number of query. Then following Q lines will be queries. In each query, start with a number M(0<=M<=5), followed by M numbers also between 0 to 10000(inclusive).

## 输出格式

For each query first print the number of elements in the longest common subsequence of the main and query sequences. Then print the subsequence. If there is more then one then print the lexicographically smallest.

## 样例 #1

### 输入

```
10
5 1 4 3 2 6 5 5 0 7
5
1 5
1 10
4 5 0 4 7
5 4 1 2 3 5
5 2 6 5 0 7
 
```

### 输出

```
1 5
0
3 5 0 7
3 1 2 5
5 2 6 5 0 7
```

