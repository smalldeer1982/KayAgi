---
title: "COUNTPAS - Counting Pascal"
layout: "post"
diff: 难度0
pid: SP7186
tag: []
---

# COUNTPAS - Counting Pascal

## 题目描述

Pascal’s triangle is a common figure in combinatorics. It is a triangle formed by rows of integers.  
The top row contains a single 1. Each new row has one element more than the previous one  
and is formed as follows: the leftmost and rightmost values are 1, while each of the other values  
is the sum of the two values above it. Here we depict the first 7 rows of the triangle.

             1                       1   1                   1   2   1               1   3   3   1           1   4   6   4   1       1   5   10   10   5   1   1   6   15   20   15   6   1Pascal’s triangle is infinite, of course, and contains the value 1 an unbounded number of times.  
However, any other value appears a finite number of times in the triangle. In this problem you  
are given an integer K >= 2. Your task is to calculate the number of values in the triangle that  
are different from 1 and less than or equal to K.

## 输入格式

The input contains several test cases. Each test case is described in a single line that contains  
an integer K (2 processed as a test case.

## 输出格式

For each test case output a single line with an integer indicating the number of values in Pascal’s  
triangle that are different from 1 and less than or equal to K.

## 样例 #1

### 输入

```
2\n6\n-1\n\n
```

### 输出

```
\n1\n10
```

