---
title: "Exponential notation"
layout: "post"
diff: 普及-
pid: CF691C
tag: ['模拟', '数学']
---

# Exponential notation

## 题目描述

You are given a positive decimal number $ x $ .

Your task is to convert it to the "simple exponential notation".

Let $ x=a·10^{b} $ , where $ 1<=a&lt;10 $ , then in general case the "simple exponential notation" looks like "aEb". If $ b $ equals to zero, the part "Eb" should be skipped. If $ a $ is an integer, it should be written without decimal point. Also there should not be extra zeroes in $ a $ and $ b $ .

## 输入格式

The only line contains the positive decimal number $ x $ . The length of the line will not exceed $ 10^{6} $ . Note that you are given too large number, so you can't use standard built-in data types "float", "double" and other.

## 输出格式

Print the only line — the "simple exponential notation" of the given number $ x $ .

## 样例 #1

### 输入

```
16

```

### 输出

```
1.6E1

```

## 样例 #2

### 输入

```
01.23400

```

### 输出

```
1.234

```

## 样例 #3

### 输入

```
.100

```

### 输出

```
1E-1

```

## 样例 #4

### 输入

```
100.

```

### 输出

```
1E2

```

