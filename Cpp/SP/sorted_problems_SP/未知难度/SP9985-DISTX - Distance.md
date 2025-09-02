---
title: "DISTX - Distance"
layout: "post"
diff: 难度0
pid: SP9985
tag: []
---

# DISTX - Distance

## 题目描述

In this task let's consider distance between two positive integers defined as below.

Single operation is : multiplying some number by prime number or dividing some number by prime number ( we can divide only when remainder is equal to 0 )

Distance d between two numbers a,b is minimum number operations to convert one number to another.

For example d(69,42)=3

This distance is very similiar to well-known term "distance" in real human life:

d(a,a)=0 , distance number to itself is 0

d(a,b)=d(b,a) distance from a->b is equal to b->a

d(a,b)+d(b,c)>=d(a,c) triangle equation is true too

With given n number you have to determine for each i-th of those numbers closest number aj from set that

i!=j and if there is many numbers with equal, smallest distance, you have to pick number with smallest index

## 输入格式

In first line - number n <=10^5.

In next n lines - i-th number. Every number is not greater than 10^6

## 输出格式

You have to output n lines.

I-th line should contain index of closest number ( if there is many answers, please output smallest index )

## 样例 #1

### 输入

```
6\n1\n2\n3\n4\n5\n6\n
```

### 输出

```
2\n1\n1\n2\n1\n2 \n
```

