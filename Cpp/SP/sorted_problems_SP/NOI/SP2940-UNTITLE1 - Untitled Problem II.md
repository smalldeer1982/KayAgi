---
title: "UNTITLE1 - Untitled Problem II"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP2940
tag: ['前缀和', '分块', '凸包']
---

# UNTITLE1 - Untitled Problem II

## 题目描述

You are given a sequence of N integers A $ _{1} $ , A $ _{2} $ .. A $ _{N} $ . (-10000 <= A $ _{i} $ <= 10000, N <= 50000)

Let S $ _{i} $ denote the sum of A $ _{1} $ ..A $ _{i} $ . You need to apply M (M <= 50000) operations:

- 0 x y k: increase all integers from A $ _{x} $ to A $ _{y} $ by k(1 <= x <= y <= N, -10000 <= k <= 10000).
- 1 x y: ask for max{ S $ _{i} $ | x <= i <= y }.(1 <= x <= y <= N)

## 输入格式

- In the first line there is an integer N.
- The following line contains N integers that represent the sequence.
- The third line contains an integer M denotes the number of operations.
- In the next M lines, each line contains an operation "0 x y k" or "1 x y".

## 输出格式

For each "1 x y" operation, print one integer representing its result.

## 样例 #1

### 输入

```
5
238 -9622 5181 202 -6943
5
1 3 4
0 5 5 4846
1 3 5
0 3 5 -7471
1 3 3
```

### 输出

```
-4001
-4001
-11674
```

