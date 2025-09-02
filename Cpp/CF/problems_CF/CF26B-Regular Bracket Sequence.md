---
title: "Regular Bracket Sequence"
layout: "post"
diff: 普及/提高-
pid: CF26B
tag: ['栈']
---

# Regular Bracket Sequence

## 题目描述

A bracket sequence is called regular if it is possible to obtain correct arithmetic expression by inserting characters «+» and «1» into this sequence. For example, sequences «(())()», «()» and «(()(()))» are regular, while «)(», «(()» and «(()))(» are not.

One day Johnny got bracket sequence. He decided to remove some of the brackets from it in order to obtain a regular bracket sequence. What is the maximum length of a regular bracket sequence which can be obtained?

## 输入格式

Input consists of a single line with non-empty string of «(» and «)» characters. Its length does not exceed $ 10^{6} $ .

## 输出格式

Output the maximum possible length of a regular bracket sequence.

## 样例 #1

### 输入

```
(()))(

```

### 输出

```
4

```

## 样例 #2

### 输入

```
((()())

```

### 输出

```
6

```

