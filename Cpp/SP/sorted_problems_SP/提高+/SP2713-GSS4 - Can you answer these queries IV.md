---
title: "GSS4 - Can you answer these queries IV"
layout: "post"
diff: 提高+/省选-
pid: SP2713
tag: ['线段树']
---

# GSS4 - Can you answer these queries IV

## 题目描述

You are given a sequence A of N(N <= 100,000) positive integers. There sum will be less than 10 $ ^{18} $ . On this sequence you have to apply M (M <= 100,000) operations:

(A) For given x,y, for each elements between the x-th and the y-th ones (inclusively, counting from 1), modify it to its positive square root (rounded down to the nearest integer).

(B) For given x,y, query the sum of all the elements between the x-th and the y-th ones (inclusively, counting from 1) in the sequence.

## 输入格式

Multiple test cases, please proceed them one by one. Input terminates by EOF.

For each test case:

The first line contains an integer N. The following line contains N integers, representing the sequence A $ _{1} $ ..A $ _{N} $ .   
 The third line contains an integer M. The next M lines contain the operations in the form "i x y".i=0 denotes the modify operation, i=1 denotes the query operation.

## 输出格式

For each test case:

Output the case number (counting from 1) in the first line of output. Then for each query, print an integer as the problem required.

Print an blank line after each test case.

See the sample output for more details.

## 样例 #1

### 输入

```
5
1 2 3 4 5
5
1 2 4
0 2 4
1 2 4
0 4 5
1 1 5
4
10 10 10 10
3
1 1 4
0 2 3
1 1 4
```

### 输出

```
Case #1:
9
4
6

Case #2:
40
26
```

