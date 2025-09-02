---
title: "Shuffle"
layout: "post"
diff: 提高+/省选-
pid: CF1622D
tag: ['组合数学', '差分']
---

# Shuffle

## 题目描述

You are given a binary string (i. e. a string consisting of characters 0 and/or 1) $ s $ of length $ n $ . You can perform the following operation with the string $ s $ at most once: choose a substring (a contiguous subsequence) of $ s $ having exactly $ k $ characters 1 in it, and shuffle it (reorder the characters in the substring as you wish).

Calculate the number of different strings which can be obtained from $ s $ by performing this operation at most once.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2 \le n \le 5000 $ ; $ 0 \le k \le n $ ).

The second line contains the string $ s $ of length $ n $ , consisting of characters 0 and/or 1.

## 输出格式

Print one integer — the number of different strings which can be obtained from $ s $ by performing the described operation at most once. Since the answer can be large, output it modulo $ 998244353 $ .

## 说明/提示

Some strings you can obtain in the first example:

- to obtain 0110110, you can take the substring from the $ 1 $ -st character to the $ 4 $ -th character, which is 1100, and reorder its characters to get 0110;
- to obtain 1111000, you can take the substring from the $ 3 $ -rd character to the $ 7 $ -th character, which is 00110, and reorder its characters to get 11000;
- to obtain 1100101, you can take the substring from the $ 5 $ -th character to the $ 7 $ -th character, which is 110, and reorder its characters to get 101.

In the second example, $ k = 0 $ so you can only choose the substrings consisting only of 0 characters. Reordering them doesn't change the string at all, so the only string you can obtain is 10010.

## 样例 #1

### 输入

```
7 2
1100110
```

### 输出

```
16
```

## 样例 #2

### 输入

```
5 0
10010
```

### 输出

```
1
```

## 样例 #3

### 输入

```
8 1
10001000
```

### 输出

```
10
```

## 样例 #4

### 输入

```
10 8
0010011000
```

### 输出

```
1
```

