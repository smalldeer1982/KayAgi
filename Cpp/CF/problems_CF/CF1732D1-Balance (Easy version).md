---
title: "Balance (Easy version)"
layout: "post"
diff: 普及/提高-
pid: CF1732D1
tag: []
---

# Balance (Easy version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version there are no "remove" queries.

Initially you have a set containing one element — $ 0 $ . You need to handle $ q $ queries of the following types:

- + $ x $ — add the integer $ x $ to the set. It is guaranteed that this integer is not contained in the set;
- ? $ k $ — find the $ k\text{-mex} $ of the set.

In our problem, we define the $ k\text{-mex} $ of a set of integers as the smallest non-negative integer $ x $ that is divisible by $ k $ and which is not contained in the set.

## 输入格式

The first line contains an integer $ q $ ( $ 1 \leq q \leq 2 \cdot 10^5 $ ) — the number of queries.

The following $ q $ lines describe the queries.

An addition query of integer $ x $ is given in the format + $ x $ ( $ 1 \leq x \leq 10^{18} $ ). It is guaranteed that $ x $ was not contained in the set.

A search query of $ k\text{-mex} $ is given in the format ? $ k $ ( $ 1 \leq k \leq 10^{18} $ ).

It is guaranteed that there will be at least one query of type ?.

## 输出格式

For each query of type ? output a single integer — the $ k\text{-mex} $ of the set.

## 说明/提示

In the first example:

After the first and second queries, the set will contain elements $ \{0, 1, 2\} $ . The smallest non-negative number that is divisible by $ 1 $ and is not contained in the set is $ 3 $ .

After the fourth query, the set will contain the elements $ \{0, 1, 2, 4\} $ . The smallest non-negative number that is divisible by $ 2 $ and is not contained in the set is $ 6 $ .

In the second example:

- Initially, the set contains only the element $ \{0\} $ .
- After adding an integer $ 100 $ the set contains elements $ \{0, 100\} $ .
- $ 100\text{-mex} $ of the set is $ 200 $ .
- After adding an integer $ 200 $ the set contains elements $ \{0, 100, 200\} $ .
- $ 100\text{-mex} $ of the set is $ 300 $ .
- After adding an integer $ 50 $ the set contains elements $ \{0, 50, 100, 200\} $ .
- $ 50\text{-mex} $ of the set is $ 150 $ .

## 样例 #1

### 输入

```
15
+ 1
+ 2
? 1
+ 4
? 2
+ 6
? 3
+ 7
+ 8
? 1
? 2
+ 5
? 1
+ 1000000000000000000
? 1000000000000000000
```

### 输出

```
3
6
3
3
10
3
2000000000000000000
```

## 样例 #2

### 输入

```
6
+ 100
? 100
+ 200
? 100
+ 50
? 50
```

### 输出

```
200
300
150
```

