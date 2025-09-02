---
title: "MINIMAX - Minimizing maximizer"
layout: "post"
diff: 提高+/省选-
pid: SP90
tag: []
---

# MINIMAX - Minimizing maximizer

## 题目描述

 The company Chris Ltd. is preparing a new sorting hardware called Maximizer. Maximizer has n inputs numbered from 1 to n. Each input represents one integer. Maximizer has one output which represents the maximum value present on Maximizer's inputs.

 Maximizer is implemented as a pipeline of sorters Sorter(i $ _{1} $ , j $ _{1} $ ), ... , Sorter(i $ _{k} $ , j $ _{k} $ ). Each sorter has n inputs and n outputs. Sorter(i, j) sorts values on inputs i, i+1,... , j in non-decreasing order and lets the other inputs pass through unchanged. The n-th output of the last sorter is the output of the Maximizer.

 An intern (a former ACM contestant) observed that some sorters could be excluded from the pipeline and Maximizer would still produce the correct result. What is the length of the shortest subsequence of the given sequence of sorters in the pipeline still producing correct results for all possible combinations of input values?

   
### Task

Write a program that:

- reads a description of a Maximizer, i.e. the initial sequence of sorters in the pipeline,
- computes the length of the shortest subsequence of the initial sequence of sorters still producing correct results for all possible input data,
- writes the result.

## 输入格式

 The input begins with the integer t, the number of test cases. Then t test cases follow.

 For each test case the first line of the input contains two integers n and m (2 <= n <= 50000, 1 <= m <= 500000) separated by a single space. Integer n is the number of inputs and integer m is the number of sorters in the pipeline. The initial sequence of sorters is described in the next m lines. The k-th of these lines contains the parameters of the k-th sorter: two integers i $ _{k} $ and j $ _{k} $ (1 <= i $ _{k} $ < j $ _{k} $ <= n) separated by a single space.

## 输出格式

 For each test case the output consists of only one line containing an integer equal to the length of the shortest subsequence of the initial sequence of sorters still producing correct results for all possible data.

## 样例 #1

### 输入

```
1
40 6 
20 30 
1 10 
10 20 
20 30 
15 25 
30 40
```

### 输出

```
4
```

