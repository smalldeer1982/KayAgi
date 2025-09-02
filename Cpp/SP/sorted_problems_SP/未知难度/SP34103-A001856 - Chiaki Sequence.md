---
title: "A001856 - Chiaki Sequence"
layout: "post"
diff: 难度0
pid: SP34103
tag: []
---

# A001856 - Chiaki Sequence

## 题目描述

Chiaki is interested in an infinite sequence $ a_1, a_2, a_3, ... $ , which defined as follows: $$ a_n = \begin{cases} n, & n \le 2 \\ 2 \cdot a_{n-1}, & n \text{ is odd} \\ a_{n-1}+r_{n-1}, & n \text{ is even}\end{cases} $$ where $ r_n $ is the smallest positive integer not in the set $ S_n = \{a_j - a_i \mid 1 \le i  <  j \le n\} $ .

Chiaki would like to know the sum of the first $ n $ terms of the sequence, i.e. $ \sum\limits_{i=1}^{n} a_n $ . As this number may be very large, Chiaki is only interested in its remainder modulo ( $ 10^9 + 7 $ ).

## 输入格式

There are multiple test cases. The first line of input contains an integer $ T $ ( $ 1 \le T \le 1000 $ ), indicating the number of test cases. For each test case:

The first line contains an integer $ n $ ( $ 1 \le n < 10^{100} $ ) without leading zeros.

## 输出格式

For each test case, output an integer denoting the answer.

## 样例 #1

### 输入

```
11
1
2
3
4
5
6
7
8
9
10
1000000000
```

### 输出

```
1
3
7
15
31
52
94
145
247
359
834069170
```

