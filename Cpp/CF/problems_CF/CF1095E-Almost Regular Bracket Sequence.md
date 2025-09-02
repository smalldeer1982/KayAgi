---
title: "Almost Regular Bracket Sequence"
layout: "post"
diff: 普及+/提高
pid: CF1095E
tag: []
---

# Almost Regular Bracket Sequence

## 题目描述

You are given a bracket sequence $ s $ consisting of $ n $ opening '(' and closing ')' brackets.

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters '1' and '+' between the original characters of the sequence. For example, bracket sequences "()()", "(())" are regular (the resulting expressions are: "(1)+(1)", "((1+1)+1)"), and ")(" and "(" are not.

You can change the type of some bracket $ s_i $ . It means that if $ s_i =  $ ')' then you can change it to '(' and vice versa.

Your task is to calculate the number of positions $ i $ such that if you change the type of the $ i $ -th bracket, then the resulting bracket sequence becomes regular.

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the length of the bracket sequence.

The second line of the input contains the string $ s $ consisting of $ n $ opening '(' and closing ')' brackets.

## 输出格式

Print one integer — the number of positions $ i $ such that if you change the type of the $ i $ -th bracket, then the resulting bracket sequence becomes regular.

## 样例 #1

### 输入

```
6
(((())

```

### 输出

```
3

```

## 样例 #2

### 输入

```
6
()()()

```

### 输出

```
0

```

## 样例 #3

### 输入

```
1
)

```

### 输出

```
0

```

## 样例 #4

### 输入

```
8
)))(((((

```

### 输出

```
0

```

