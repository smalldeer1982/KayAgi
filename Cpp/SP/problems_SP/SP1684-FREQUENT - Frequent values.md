---
title: "FREQUENT - Frequent values"
layout: "post"
diff: 普及+/提高
pid: SP1684
tag: ['搜索', '未知标签231']
---

# FREQUENT - Frequent values

## 题目描述

You are given a sequence of **n** integers **a $ _{1} $ , a $ _{2} $ , ... , a $ _{n} $**  in non-decreasing order. In addition to that, you are given several queries consisting of indices **i** and **j** (_1 ≤ i ≤ j ≤ n_). For each query, determine the most frequent value among the integers **a $ _{i} $ , ... , a $ _{j} $** .

   
#### Input Specification

 The input consists of several test cases. Each test case starts with a line containing two integers **n** and **q** (_1 ≤ n, q ≤ 100000_). The next line contains **n** integers **a $ _{1} $ , ... , a $ _{n} $**  (_-100000 ≤ a $ _{i} $ ≤ 100000_, for each _i ∈ {1, ..., n}_) separated by spaces. You can assume that for each _i ∈ {1, ..., n-1}: a $ _{i} $ ≤ a $ _{i+1} $_ . The following **q** lines contain one query each, consisting of two integers **i** and **j** (_1 ≤ i ≤ j ≤ n_), which indicate the boundary indices for the query.

 The last test case is followed by a line containing a single 0.

   
#### Output Specification

 For each query, print one line with one integer: The number of occurrences of the most frequent value within the given range.

   
#### Sample Input

 ```
10 3
-1 -1 1 1 1 1 3 10 10 10
2 3
1 10
5 10
0
```
   
#### Sample Output

 ```
1
4
3
```
- - - - - -

_A naive algorithm may not run in time!_

