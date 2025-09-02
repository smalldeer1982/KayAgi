---
title: "Monocarp and the Set"
layout: "post"
diff: 普及+/提高
pid: CF1886D
tag: []
---

# Monocarp and the Set

## 题目描述

Monocarp has $ n $ numbers $ 1, 2, \dots, n $ and a set (initially empty). He adds his numbers to this set $ n $ times in some order. During each step, he adds a new number (which has not been present in the set before). In other words, the sequence of added numbers is a permutation of length $ n $ .

Every time Monocarp adds an element into the set except for the first time, he writes out a character:

- if the element Monocarp is trying to insert becomes the maximum element in the set, Monocarp writes out the character &gt;;
- if the element Monocarp is trying to insert becomes the minimum element in the set, Monocarp writes out the character &lt;;
- if none of the above, Monocarp writes out the character ?.

You are given a string $ s $ of $ n-1 $ characters, which represents the characters written out by Monocarp (in the order he wrote them out). You have to process $ m $ queries to the string. Each query has the following format:

- $ i $ $ c $ — replace $ s_i $ with the character $ c $ .

Both before processing the queries and after each query, you have to calculate the number of different ways to order the integers $ 1, 2, 3, \dots, n $ such that, if Monocarp inserts the integers into the set in that order, he gets the string $ s $ . Since the answers might be large, print them modulo $ 998244353 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2 \le n \le 3 \cdot 10^5 $ ; $ 1 \le m \le 3 \cdot 10^5 $ ).

The second line contains the string $ s $ , consisting of exactly $ n-1 $ characters &lt;, &gt; and/or ?.

Then $ m $ lines follow. Each of them represents a query. Each line contains an integer $ i $ and a character $ c $ ( $ 1 \le i \le n-1 $ ; $ c $ is either &lt;, &gt;, or ?).

## 输出格式

Both before processing the queries and after each query, print one integer — the number of ways to order the integers $ 1, 2, 3, \dots, n $ such that, if Monocarp inserts the integers into the set in that order, he gets the string $ s $ . Since the answers might be large, print them modulo $ 998244353 $ .

## 说明/提示

In the first example, there are three possible orderings before all queries:

- $ 3, 1, 2, 5, 4, 6 $ ;
- $ 4, 1, 2, 5, 3, 6 $ ;
- $ 4, 1, 3, 5, 2, 6 $ .

After the last query, there is only one possible ordering:

- $ 3, 5, 4, 6, 2, 1 $ .

## 样例 #1

### 输入

```
6 4
<?>?>
1 ?
4 <
5 <
1 >

```

### 输出

```
3
0
0
0
1
```

## 样例 #2

### 输入

```
2 2
>
1 ?
1 <

```

### 输出

```
1
0
1
```

