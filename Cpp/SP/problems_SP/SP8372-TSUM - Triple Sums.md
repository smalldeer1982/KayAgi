---
title: "TSUM - Triple Sums"
layout: "post"
diff: 省选/NOI-
pid: SP8372
tag: []
---

# TSUM - Triple Sums

## 题目描述

You're given a sequence **s** of **N** distinct integers.  
Consider all the possible sums of three integers from the sequence at three different indicies.  
For each obtainable sum output the number of different triples of indicies that generate it.  
 **Constraints:**  
N <= 40000, |s $ _{i} $ | <= 20000

## 输入格式

The first line of input contains a single integer N.  
Each of the next N lines contain an element of s.

## 输出格式

Print the solution for each possible sum in the following format:  
sum\_value : number\_of\_triples  
  
Smaller sum values should be printed first.

## 样例 #1

### 输入

```
5
-1
2
3
0
5
```

### 输出

```

1 : 1
2 : 1
4 : 2
5 : 1
6 : 1
7 : 2
8 : 1
10 : 1
```

