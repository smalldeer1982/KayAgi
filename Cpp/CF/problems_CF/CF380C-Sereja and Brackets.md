---
title: "Sereja and Brackets"
layout: "post"
diff: 普及+/提高
pid: CF380C
tag: []
---

# Sereja and Brackets

## 题目描述

Sereja has a bracket sequence $ s_{1},s_{2},...,s_{n} $ , or, in other words, a string $ s $ of length $ n $ , consisting of characters "(" and ")".

Sereja needs to answer $ m $ queries, each of them is described by two integers $ l_{i},r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ . The answer to the $ i $ -th query is the length of the maximum correct bracket subsequence of sequence $ s_{li},s_{li}+1,...,s_{ri} $ . Help Sereja answer all queries.

You can find the definitions for a subsequence and a correct bracket sequence in the notes.

## 输入格式

The first line contains a sequence of characters $ s_{1},s_{2},...,s_{n} $ $ (1<=n<=10^{6}) $ without any spaces. Each character is either a "(" or a ")". The second line contains integer $ m $ $ (1<=m<=10^{5}) $ — the number of queries. Each of the next $ m $ lines contains a pair of integers. The $ i $ -th line contains integers $ l_{i},r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ — the description of the $ i $ -th query.

## 输出格式

Print the answer to each question on a single line. Print the answers in the order they go in the input.

## 说明/提示

A subsequence of length $ |x| $ of string $ s=s_{1}s_{2}...\ s_{|s|} $ (where $ |s| $ is the length of string $ s $ ) is string $ x=s_{k1}s_{k2}...\ s_{k|x|} $ $ (1<=k_{1}<k_{2}<...<k_{|x|}<=|s|) $ .

A correct bracket sequence is a bracket sequence that can be transformed into a correct aryphmetic expression by inserting characters "1" and "+" between the characters of the string. For example, bracket sequences "()()", "(())" are correct (the resulting expressions "(1)+(1)", "((1+1)+1)"), and ")(" and "(" are not.

For the third query required sequence will be «()».

For the fourth query required sequence will be «()(())(())».

## 样例 #1

### 输入

```
())(())(())(
7
1 1
2 3
1 2
1 12
8 12
5 11
2 10

```

### 输出

```
0
0
2
10
4
6
6

```

