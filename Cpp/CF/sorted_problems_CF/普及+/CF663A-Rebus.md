---
title: "Rebus"
layout: "post"
diff: 普及+/提高
pid: CF663A
tag: []
---

# Rebus

## 题目描述

You are given a rebus of form ? + ? - ? + ? = n, consisting of only question marks, separated by arithmetic operation '+' and '-', equality and positive integer $ n $ . The goal is to replace each question mark with some positive integer from $ 1 $ to $ n $ , such that equality holds.

## 输入格式

The only line of the input contains a rebus. It's guaranteed that it contains no more than $ 100 $ question marks, integer $ n $ is positive and doesn't exceed $ 1000000 $ , all letters and integers are separated by spaces, arithmetic operations are located only between question marks.

## 输出格式

The first line of the output should contain "Possible" (without quotes) if rebus has a solution and "Impossible" (without quotes) otherwise.

If the answer exists, the second line should contain any valid rebus with question marks replaced by integers from $ 1 $ to $ n $ . Follow the format given in the samples.

## 样例 #1

### 输入

```
? + ? - ? + ? + ? = 42

```

### 输出

```
Possible
9 + 13 - 39 + 28 + 31 = 42

```

## 样例 #2

### 输入

```
? - ? = 1

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
? = 1000000

```

### 输出

```
Possible
1000000 = 1000000

```

