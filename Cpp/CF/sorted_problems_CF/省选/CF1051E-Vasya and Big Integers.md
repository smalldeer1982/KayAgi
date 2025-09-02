---
title: "Vasya and Big Integers"
layout: "post"
diff: 省选/NOI-
pid: CF1051E
tag: []
---

# Vasya and Big Integers

## 题目描述

Vasya owns three big integers — $ a, l, r $ . Let's define a partition of $ x $ such a sequence of strings $ s_1, s_2, \dots, s_k $ that $ s_1 + s_2 + \dots + s_k = x $ , where $ + $ is a concatanation of strings. $ s_i $ is the $ i $ -th element of the partition. For example, number $ 12345 $ has the following partitions: \["1", "2", "3", "4", "5"\], \["123", "4", "5"\], \["1", "2345"\], \["12345"\] and lots of others.

Let's call some partition of $ a $ beautiful if each of its elements contains no leading zeros.

Vasya want to know the number of beautiful partitions of number $ a $ , which has each of $ s_i $ satisfy the condition $ l \le s_i \le r $ . Note that the comparison is the integer comparison, not the string one.

Help Vasya to count the amount of partitions of number $ a $ such that they match all the given requirements. The result can be rather big, so print it modulo $ 998244353 $ .

## 输入格式

The first line contains a single integer $ a~(1 \le a \le 10^{1000000}) $ .

The second line contains a single integer $ l~(0 \le l \le 10^{1000000}) $ .

The third line contains a single integer $ r~(0 \le r \le 10^{1000000}) $ .

It is guaranteed that $ l \le r $ .

It is also guaranteed that numbers $ a, l, r $ contain no leading zeros.

## 输出格式

Print a single integer — the amount of partitions of number $ a $ such that they match all the given requirements modulo $ 998244353 $ .

## 说明/提示

In the first test case, there are two good partitions $ 13+5 $ and $ 1+3+5 $ .

In the second test case, there is one good partition $ 1+0+0+0+0 $ .

## 样例 #1

### 输入

```
135
1
15

```

### 输出

```
2

```

## 样例 #2

### 输入

```
10000
0
9

```

### 输出

```
1

```

