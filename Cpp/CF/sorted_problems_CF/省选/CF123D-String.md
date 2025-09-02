---
title: "String"
layout: "post"
diff: 省选/NOI-
pid: CF123D
tag: ['线段树', '排序', '后缀数组 SA']
---

# String

## 题目描述

You are given a string $ s $ . Each pair of numbers $ l $ and $ r $ that fulfill the condition $ 1<=l<=r<=|s| $ , correspond to a substring of the string $ s $ , starting in the position $ l $ and ending in the position $ r $ (inclusive).

Let's define the function of two strings $ F(x,y) $ like this. We'll find a list of such pairs of numbers for which the corresponding substrings of string $ x $ are equal to string $ y $ . Let's sort this list of pairs according to the pair's first number's increasing. The value of function $ F(x,y) $ equals the number of non-empty continuous sequences in the list.

For example: $ F(babbabbababbab,babb)=6 $ . The list of pairs is as follows:

 $ (1,4),(4,7),(9,12) $

Its continuous sequences are:

- $ (1,4) $
- $ (4,7) $
- $ (9,12) $
- $ (1,4),(4,7) $
- $ (4,7),(9,12) $
- $ (1,4),(4,7),(9,12) $

Your task is to calculate for the given string $ s $ the sum $ F(s,x) $ for all $ x $ , that $ x $ belongs to the set of all substrings of a string $ s $ .

## 输入格式

The only line contains the given string $ s $ , consisting only of small Latin letters ( $ 1<=|s|<=10^{5} $ ).

## 输出格式

Print the single number — the sought sum.

Please do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specificator.

## 说明/提示

In the first sample the function values at $ x $ equal to "a", "aa", "aaa" and "aaaa" equal 10, 6, 3 and 1 correspondingly.

In the second sample for any satisfying $ x $ the function value is 1.

## 样例 #1

### 输入

```
aaaa

```

### 输出

```
20

```

## 样例 #2

### 输入

```
abcdef

```

### 输出

```
21

```

## 样例 #3

### 输入

```
abacabadabacaba

```

### 输出

```
188

```

