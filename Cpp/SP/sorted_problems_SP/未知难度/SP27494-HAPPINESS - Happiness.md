---
title: "HAPPINESS - Happiness"
layout: "post"
diff: 难度0
pid: SP27494
tag: []
---

# HAPPINESS - Happiness

## 题目描述

You are given an array on N elements a\[1\], a\[2\], a\[3\], …. , a\[N\].

Now you will have to answer some queries.

In every query, you will be given an interval, \[l, r\]. For this interval you have to print the total summation of happiness of all the elements of the given array between the interval \[l, r\].

The happiness of an element a\[i\] between interval \[l, r\] is: the number of sub-array \[lj , rj\] where the minimum value between \[lj, rj\] is equal to a\[i\]. Here, _l <= lj <= i & i <= rj <= r._

Now, you have to print the total summation of happiness of all the elements between \[l,r\].

## 输入格式

The first line of the input contains the number of test cases T. The first line of each test case contains two numbers, N & M. N is the number of elements in array a and M is the number of queries you need to perform.

The next line contains N integers, the array a : a\[1\], a\[2\], a\[3\], … a\[N\].

Next M lines contains two integers, l & r.

## 输出格式

For each test case, you need to print the case number on the first line in this format: Case X: where X is the case number.

In the next M lines, you need to print the total summation of happiness of all the elements between \[l, r\] of the given array.

## 样例 #1

### 输入

```
2\n5 2\n1 3 2 4 3\n1 3\n2 4\n5 2\n5 3 7 6 8\n1 4\n2 5&nbsp;
```

### 输出

```
Case 1:\n6\n6\nCase 2:\n10\n10
```

