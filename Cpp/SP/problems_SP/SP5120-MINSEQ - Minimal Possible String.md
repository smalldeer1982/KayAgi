---
title: "MINSEQ - Minimal Possible String"
layout: "post"
diff: 难度0
pid: SP5120
tag: []
---

# MINSEQ - Minimal Possible String

## 题目描述

Given two strings A and B, your are to find the lexicographically smallest string after inserting B into A.

For example, string A is "369", and string B is "4799". There are 4 ways that I can insert B into A, and I’ll get 4 different results: 4799369, 3479969, 3647999, 3694799. Thus, 3479969 is the lexicographically smallest one.

## 输入格式

Input contains several cases. Each case has 2 strings A and B with length no longer than 100000 in 2 lines. Process the input until EOF. The strings consist of only digit 1-9.

## 输出格式

For each case, output the minimal possible result.

## 样例 #1

### 输入

```
\n369\n4799\n666\n12345\n\n
```

### 输出

```
\n3479969\n12345666
```

