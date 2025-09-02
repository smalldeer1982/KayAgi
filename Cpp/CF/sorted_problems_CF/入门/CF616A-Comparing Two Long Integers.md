---
title: "Comparing Two Long Integers"
layout: "post"
diff: 入门
pid: CF616A
tag: []
---

# Comparing Two Long Integers

## 题目描述

You are given two very long integers $ a,b $ (leading zeroes are allowed). You should check what number $ a $ or $ b $ is greater or determine that they are equal.

The input size is very large so don't use the reading of symbols one by one. Instead of that use the reading of a whole line or token.

As input/output can reach huge size it is recommended to use fast input/output methods: for example, prefer to use scanf/printf instead of cin/cout in C++, prefer to use BufferedReader/PrintWriter instead of Scanner/System.out in Java. Don't use the function input() in Python2 instead of it use the function raw\_input().

## 输入格式

The first line contains a non-negative integer $ a $ .

The second line contains a non-negative integer $ b $ .

The numbers $ a,b $ may contain leading zeroes. Each of them contains no more than $ 10^{6} $ digits.

## 输出格式

Print the symbol "<" if $ a<b $ and the symbol ">" if $ a>b $ . If the numbers are equal print the symbol "=".

## 样例 #1

### 输入

```
9
10

```

### 输出

```
<

```

## 样例 #2

### 输入

```
11
10

```

### 输出

```
>

```

## 样例 #3

### 输入

```
00012345
12345

```

### 输出

```
=

```

## 样例 #4

### 输入

```
0123
9

```

### 输出

```
>

```

## 样例 #5

### 输入

```
0123
111

```

### 输出

```
>

```

