---
title: "Long number"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF756F
tag: []
---

# Long number

## 题目描述

Consider the following grammar:

- <expression> ::= <term> | <expression> '+' <term>
- <term> ::= <number> | <number> '-' <number> | <number> '(' <expression> ')'
- <number> ::= <pos\_digit> | <number> <digit>
- <digit> ::= '0' | <pos\_digit>
- <pos\_digit> ::= '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'

This grammar describes a number in decimal system using the following rules:

- <number> describes itself,
- <number>-<number> (l-r, $ l<=r $ ) describes integer which is concatenation of all integers from $ l $ to $ r $ , written without leading zeros. For example, 8-11 describes 891011,
- <number>(<expression>) describes integer which is concatenation of <number> copies of integer described by <expression>,
- <expression>+<term> describes integer which is concatenation of integers described by <expression> and <term>.

For example, 2(2-4+1)+2(2(17)) describes the integer 2341234117171717.

You are given an expression in the given grammar. Print the integer described by it modulo $ 10^{9}+7 $ .

## 输入格式

The only line contains a non-empty string at most $ 10^{5} $ characters long which is valid according to the given grammar. In particular, it means that in terms l-r $ l<=r $ holds.

## 输出格式

Print single integer — the number described by the expression modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
8-11

```

### 输出

```
891011

```

## 样例 #2

### 输入

```
2(2-4+1)+2(2(17))

```

### 输出

```
100783079

```

## 样例 #3

### 输入

```
1234-5678

```

### 输出

```
745428774

```

## 样例 #4

### 输入

```
1+2+3+4-5+6+7-9

```

### 输出

```
123456789

```

