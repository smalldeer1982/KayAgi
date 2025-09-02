---
title: "Torn Lucky Ticket"
layout: "post"
diff: 普及/提高-
pid: CF1895C
tag: []
---

# Torn Lucky Ticket

## 题目描述

A ticket is a non-empty string of digits from $ 1 $ to $ 9 $ .

A lucky ticket is such a ticket that:

- it has an even length;
- the sum of digits in the first half is equal to the sum of digits in the second half.

You are given $ n $ ticket pieces $ s_1, s_2, \dots, s_n $ . How many pairs $ (i, j) $ (for $ 1 \le i, j \le n $ ) are there such that $ s_i + s_j $ is a lucky ticket? Note that it's possible that $ i=j $ .

Here, the + operator denotes the concatenation of the two strings. For example, if $ s_i $ is 13, and $ s_j $ is 37, then $ s_i + s_j $ is 1337.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of ticket pieces.

The second line contains $ n $ non-empty strings $ s_1, s_2, \dots, s_n $ , each of length at most $ 5 $ and consisting only of digits from $ 1 $ to $ 9 $ .

## 输出格式

Print a single integer — the number of pairs $ (i, j) $ (for $ 1 \le i, j \le n $ ) such that $ s_i + s_j $ is a lucky ticket.

## 样例 #1

### 输入

```
10
5 93746 59 3746 593 746 5937 46 59374 6
```

### 输出

```
20
```

## 样例 #2

### 输入

```
5
2 22 222 2222 22222
```

### 输出

```
13
```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
9
```

