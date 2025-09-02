---
title: "AROPE3 - Alphabetic Rope3"
layout: "post"
diff: 提高+/省选-
pid: SP29461
tag: ['平衡树']
---

# AROPE3 - Alphabetic Rope3

## 题目描述

The Alphabetic Rope is now available in the market. The Alphabetic Rope consists of alphabetic  

characters in each stripe which looks like string.  

You are given an Alphabetic rope consists of lowercase alphabetic characters only,you have to perform  

some operations on rope and answers some queries on it. 

Queries are of 3 types:

- 1 X Y : Cut the rope segment from X to Y and Reverse it then join at the front of the rope.
- 2 X Y : Cut the rope segment from X to Y and Reverse it then join at the back of the rope.
- 3 Y: Print on a new line an Alphabet on Yth position of the current rope.

## 输入格式

There is only one input. Input begins with single line giving Alphabetic Rope as a string S.  

Next line containg Q, follows Q lines giving Queries as mentioned above. (Index used are 0-based)

## 输出格式

For each query of type 3, Print a single character in a new line.

$1\le |S|\le 100000$. (Length of string)

$1\le Q \le 100000$. (Total Queries)

## 样例 #1

### 输入

```
gautambishal
5
1 3 5
3 0
3 3
2 2 4
3 9

```

### 输出

```
m
g
a
```

