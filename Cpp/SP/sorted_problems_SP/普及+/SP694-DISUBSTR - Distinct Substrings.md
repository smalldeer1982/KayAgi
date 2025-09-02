---
title: "DISUBSTR - Distinct Substrings"
layout: "post"
diff: 普及+/提高
pid: SP694
tag: ['容斥原理', '后缀数组 SA']
---

# DISUBSTR - Distinct Substrings

## 题目描述

Given a string, we need to find the total number of its distinct substrings.

## 输入格式

T- number of test cases. T<=20;  
 Each test case consists of one string, whose length is <= 1000

## 输出格式

For each test case output one number saying the number of distinct substrings.

## 说明/提示


Explanation for the testcase with string ABABA:

len=1 : A,B

len=2 : AB,BA

len=3 : ABA,BAB

len=4 : ABAB,BABA

len=5 : ABABA

Thus, total number of distinct substrings is 9.

## 样例 #1

### 输入

```
2
CCCCC
ABABA
```

### 输出

```
5
9

```

