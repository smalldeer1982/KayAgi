---
title: "POLISH - Polish Language"
layout: "post"
diff: 省选/NOI-
pid: SP10419
tag: ['后缀数组 SA']
---

# POLISH - Polish Language

## 题目描述

Russell can't wait to know Poland. As he waits he decided to learn a little of the Polish Language. To do this in a funny way he intends to use an old Polish dictionary and play a game he learned from the old Carl.

Given a word s in the dictionary, Russell is interested in sequences of suffixes of s. But not just any one! Russell considers amusing sequences of suffixes with the following properties:

- The suffixes appear in increasing sizes.
- The suffixes appear in lexicographic order.

As an example, if s = ABACA then the sequences (ABACA), (A, CA) and (A, ACA, BACA) please Russell but (ABACA, ACA) or (CA, ACA) doesn't.

Help Russell find the number of amusing sequences of suffixes of a given word s modulo 1000000007 (10^9 + 7).

## 输入格式

The input consists of several test cases. Each test case consists of only one line containing a string **S** with 1 to 100000 (10^5) uppercase latin letters (A - Z).

## 输出格式

For each test case output a single line containing the number of amusing sequences of suffixes of **S** modulo 1000000007 (10^9 + 7).

## 样例 #1

### 输入

```
ABACA\nNIE\nPIJ\nWODY\nCAMPINAS
```

### 输出

```
11\n7\n5\n8\n20
```

