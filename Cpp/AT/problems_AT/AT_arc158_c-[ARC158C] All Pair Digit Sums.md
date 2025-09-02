---
title: "[ARC158C] All Pair Digit Sums"
layout: "post"
diff: 普及+/提高
pid: AT_arc158_c
tag: ['数学', '二分']
---

# [ARC158C] All Pair Digit Sums

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc158/tasks/arc158_c

正整数 $ x $ に対し，その各桁の和を $ f(x) $ と表すことにします．例えば $ f(158)\ =\ 1\ +\ 5\ +\ 8\ =\ 14 $，$ f(2023)\ =\ 2\ +\ 0\ +\ 2\ +\ 3\ =\ 7 $，$ f(1)\ =\ 1 $ です．

正整数列 $ A\ =\ (A_1,\ \ldots,\ A_N) $ が与えられます．$ \sum_{i=1}^N\sum_{j=1}^N\ f(A_i\ +\ A_j) $ を求めてください．

## 输入格式

入力は以下の形式で標準入力から与えられます．

> $ N $ $ A_1 $ $ \ldots $ $ A_N $

## 输出格式

$ \sum_{i=1}^N\sum_{j=1}^N\ f(A_i\ +\ A_j) $ を出力してください．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ <\ 10^{15} $
 
### Sample Explanation 1

$ \sum_{i=1}^N\sum_{j=1}^N\ f(A_i\ +\ A_j)\ =\ f(A_1+A_1)+f(A_1+A_2)+f(A_2+A_1)+f(A_2+A_2)=7+9+9+11=36 $ です．

### Sample Explanation 2

$ \sum_{i=1}^N\sum_{j=1}^N\ f(A_i\ +\ A_j)\ =\ f(A_1+A_1)\ =\ 135 $ です．

## 样例 #1

### 输入

```
2
53 28
```

### 输出

```
36
```

## 样例 #2

### 输入

```
1
999999999999999
```

### 输出

```
135
```

## 样例 #3

### 输入

```
5
123 456 789 101 112
```

### 输出

```
321
```

