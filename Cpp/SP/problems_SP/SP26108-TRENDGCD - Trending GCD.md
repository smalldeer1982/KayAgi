---
title: "TRENDGCD - Trending GCD"
layout: "post"
diff: 省选/NOI-
pid: SP26108
tag: []
---

# TRENDGCD - Trending GCD

## 题目描述

Problem statement is simple. Given **A** and **B** you need to calculate **S(A,B) .**

![sigma(a=1 to A)sigma(b=1 to B) (a*b*f(gcd(a,b)))](http://s29.postimg.org/qnxglb8mf/pic.png "TRENDGCD problem statement")

Here, **f(n)=n, if n is square free otherwise 0**. Also **f(1)=1**.

## 输入格式

The first line contains one integer **T** - denoting the number of test cases.

**T** lines follow each containing two integers **A,B**.

## 输出格式

For each testcase output the value of S(A,B) mod 1000000007 in a single line.

## 样例 #1

### 输入

```
3
42 18
35 1
20 25
```

### 输出

```
306395
630
128819
```

