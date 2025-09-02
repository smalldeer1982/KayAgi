---
title: "Longest Regular Bracket Sequence"
layout: "post"
diff: 普及/提高-
pid: CF5C
tag: ['字符串', '动态规划 DP', '栈']
---

# Longest Regular Bracket Sequence

## 题目描述

This is yet another problem dealing with regular bracket sequences.

We should remind you that a bracket sequence is called regular, if by inserting «+» and «1» into it we can get a correct mathematical expression. For example, sequences «(())()», «()» and «(()(()))» are regular, while «)(», «(()» and «(()))(» are not.

You are given a string of «(» and «)» characters. You are to find its longest substring that is a regular bracket sequence. You are to find the number of such substrings as well.

## 输入格式

The first line of the input file contains a non-empty string, consisting of «(» and «)» characters. Its length does not exceed $ 10^{6} $ .

## 输出格式

Print the length of the longest substring that is a regular bracket sequence, and the number of such substrings. If there are no such substrings, write the only line containing "0 1".

## 样例 #1

### 输入

```
)((())))(()())

```

### 输出

```
6 2

```

## 样例 #2

### 输入

```
))(

```

### 输出

```
0 1

```

