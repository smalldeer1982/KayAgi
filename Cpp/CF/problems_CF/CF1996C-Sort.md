---
title: "Sort"
layout: "post"
diff: 普及-
pid: CF1996C
tag: ['贪心', '前缀和']
---

# Sort

## 题目描述

You are given two strings $ a $ and $ b $ of length $ n $ . Then, you are (forced against your will) to answer $ q $ queries.

For each query, you are given a range bounded by $ l $ and $ r $ . In one operation, you can choose an integer $ i $ ( $ l \leq i \leq r $ ) and set $ a_i = x $ where $ x $ is any character you desire. Output the minimum number of operations you must perform such that $ \texttt{sorted(a[l..r])} = \texttt{sorted(b[l..r])} $ . The operations you perform on one query does not affect other queries.

For an arbitrary string $ c $ , $ \texttt{sorted(c[l..r])} $ denotes the substring consisting of characters $ c_l, c_{l+1}, ... , c_r $ sorted in lexicographical order.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 1000 $ ) – the number of test cases.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \leq n, q \leq 2 \cdot 10^5 $ ) – the length of both strings and the number of queries.

The following line contains $ a $ of length $ n $ . It is guaranteed $ a $ only contains lowercase latin letters.

The following line contains $ b $ of length $ n $ . It is guaranteed $ b $ only contains lowercase latin letters.

The following $ q $ lines contain two integers $ l $ and $ r $ ( $ 1 \leq l \leq r \leq n $ ) – the range of the query.

It is guaranteed the sum of $ n $ and $ q $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query, output an integer, the minimum number of operations you need to perform in a new line.

## 说明/提示

For the first query, $ \texttt{sorted(a[1..5])} = $ abcde and $ \texttt{sorted(b[1..5])} = $ abcde, so no operations are necessary.

For the second query, you need to set $ a_1 =  $ e. Then, $ \texttt{sorted(a[1..4])} = \texttt{sorted(b[1..4])} =  $ bcde.

## 样例 #1

### 输入

```
3
5 3
abcde
edcba
1 5
1 4
3 3
4 2
zzde
azbe
1 3
1 4
6 3
uwuwuw
wuwuwu
2 4
1 3
1 6
```

### 输出

```
0
1
0
2
2
1
1
0
```

