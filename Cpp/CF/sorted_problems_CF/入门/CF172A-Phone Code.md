---
title: "Phone Code"
layout: "post"
diff: 入门
pid: CF172A
tag: []
---

# Phone Code

## 题目描述

Polycarpus has $ n $ friends in Tarasov city. Polycarpus knows phone numbers of all his friends: they are strings $ s_{1},s_{2},...,s_{n} $ . All these strings consist only of digits and have the same length.

Once Polycarpus needed to figure out Tarasov city phone code. He assumed that the phone code of the city is the longest common prefix of all phone numbers of his friends. In other words, it is the longest string $ c $ which is a prefix (the beginning) of each $ s_{i} $ for all $ i $ ( $ 1<=i<=n $ ). Help Polycarpus determine the length of the city phone code.

## 输入格式

The first line of the input contains an integer $ n $ ( $ 2<=n<=3·10^{4} $ ) — the number of Polycarpus's friends. The following $ n $ lines contain strings $ s_{1},s_{2},...,s_{n} $ — the phone numbers of Polycarpus's friends. It is guaranteed that all strings consist only of digits and have the same length from $ 1 $ to $ 20 $ , inclusive. It is also guaranteed that all strings are different.

## 输出格式

Print the number of digits in the city phone code.

## 说明/提示

A prefix of string $ t $ is a string that is obtained by deleting zero or more digits from the end of string $ t $ . For example, string "00209" has 6 prefixes: "" (an empty prefix), "0", "00", "002", "0020", "00209".

In the first sample the city phone code is string "00".

In the second sample the city phone code is an empty string.

In the third sample the city phone code is string "770123456789".

## 样例 #1

### 输入

```
4
00209
00219
00999
00909

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2
1
2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3
77012345678999999999
77012345678901234567
77012345678998765432

```

### 输出

```
12

```

