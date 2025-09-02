---
title: "Buy One, Get One Free"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF335F
tag: []
---

# Buy One, Get One Free

## 题目描述

A nearby pie shop is having a special sale. For each pie you pay full price for, you may select one pie of a strictly lesser value to get for free. Given the prices of all the pies you wish to acquire, determine the minimum total amount you must pay for all of the pies.

## 输入格式

Input will begin with an integer $ n $ ( $ 1<=n<=500000 $ ), the number of pies you wish to acquire. Following this is a line with $ n $ integers, each indicating the cost of a pie. All costs are positive integers not exceeding $ 10^{9} $ .

## 输出格式

Print the minimum cost to acquire all the pies.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first test case you can pay for a pie with cost 5 and get a pie with cost 4 for free, then pay for a pie with cost 5 and get a pie with cost 3 for free, then pay for a pie with cost 4 and get a pie with cost 3 for free.

In the second test case you have to pay full price for every pie.

## 样例 #1

### 输入

```
6
3 4 5 3 4 5

```

### 输出

```
14

```

## 样例 #2

### 输入

```
5
5 5 5 5 5

```

### 输出

```
25

```

## 样例 #3

### 输入

```
4
309999 6000 2080 2080

```

### 输出

```
314159

```

