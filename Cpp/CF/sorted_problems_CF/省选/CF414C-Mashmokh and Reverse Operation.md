---
title: "Mashmokh and Reverse Operation"
layout: "post"
diff: 省选/NOI-
pid: CF414C
tag: []
---

# Mashmokh and Reverse Operation

## 题目描述

Mashmokh's boss, Bimokh, didn't like Mashmokh. So he fired him. Mashmokh decided to go to university and participate in ACM instead of finding a new job. He wants to become a member of Bamokh's team. In order to join he was given some programming tasks and one week to solve them. Mashmokh is not a very experienced programmer. Actually he is not a programmer at all. So he wasn't able to solve them. That's why he asked you to help him with these tasks. One of these tasks is the following.

You have an array $ a $ of length $ 2^{n} $ and $ m $ queries on it. The $ i $ -th query is described by an integer $ q_{i} $ . In order to perform the $ i $ -th query you must:

- split the array into $ 2^{n-q_{i}} $ parts, where each part is a subarray consisting of $ 2^{q_{i}} $ numbers; the $ j $ -th subarray $ (1<=j<=2^{n-q_{i}}) $ should contain the elements $ a[(j-1)·2^{q_{i}}+1],a[(j-1)·2^{q_{i}}+2],...,a[(j-1)·2^{q_{i}}+2^{q_{i}}] $ ;
- reverse each of the subarrays;
- join them into a single array in the same order (this array becomes new array $ a $ );
- output the number of inversions in the new $ a $ .

Given initial array $ a $ and all the queries. Answer all the queries. Please, note that the changes from some query is saved for further queries.

## 输入格式

The first line of input contains a single integer $ n (0<=n<=20) $ .

The second line of input contains $ 2^{n} $ space-separated integers $ a[1],a[2],...,a[2^{n}] (1<=a[i]<=10^{9}) $ , the initial array.

The third line of input contains a single integer $ m (1<=m<=10^{6}) $ .

The fourth line of input contains $ m $ space-separated integers $ q_{1},q_{2},...,q_{m} (0<=q_{i}<=n) $ , the queries.

Note: since the size of the input and output could be very large, don't use slow output techniques in your language. For example, do not use input and output streams (cin, cout) in C++.

## 输出格式

Output $ m $ lines. In the $ i $ -th line print the answer (the number of inversions) for the $ i $ -th query.

## 说明/提示

If we reverse an array $ x[1],x[2],...,x[n] $ it becomes new array $ y[1],y[2],...,y[n] $ , where $ y[i]=x[n-i+1] $ for each $ i $ .

The number of inversions of an array $ x[1],x[2],...,x[n] $ is the number of pairs of indices $ i,j $ such that: $ i&lt;j $ and $ x[i]&gt;x[j] $ .

## 样例 #1

### 输入

```
2
2 1 4 3
4
1 2 0 2

```

### 输出

```
0
6
6
0

```

## 样例 #2

### 输入

```
1
1 2
3
0 1 1

```

### 输出

```
0
1
0

```

