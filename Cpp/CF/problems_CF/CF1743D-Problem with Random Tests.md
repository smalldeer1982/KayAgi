---
title: "Problem with Random Tests"
layout: "post"
diff: 普及+/提高
pid: CF1743D
tag: []
---

# Problem with Random Tests

## 题目描述

You are given a string $ s $ consisting of $ n $ characters. Each character of $ s $ is either 0 or 1.

A substring of $ s $ is a contiguous subsequence of its characters.

You have to choose two substrings of $ s $ (possibly intersecting, possibly the same, possibly non-intersecting — just any two substrings). After choosing them, you calculate the value of the chosen pair of substrings as follows:

- let $ s_1 $ be the first substring, $ s_2 $ be the second chosen substring, and $ f(s_i) $ be the integer such that $ s_i $ is its binary representation (for example, if $ s_i $ is 11010, $ f(s_i) = 26 $ );
- the value is the bitwise OR of $ f(s_1) $ and $ f(s_2) $ .

Calculate the maximum possible value you can get, and print it in binary representation without leading zeroes.

## 输入格式

The first line contains one integer $ n $ — the number of characters in $ s $ .

The second line contains $ s $ itself, consisting of exactly $ n $ characters 0 and/or 1.

All non-example tests in this problem are generated randomly: every character of $ s $ is chosen independently of other characters; for each character, the probability of it being 1 is exactly $ \frac{1}{2} $ .

This problem has exactly $ 40 $ tests. Tests from $ 1 $ to $ 3 $ are the examples; tests from $ 4 $ to $ 40 $ are generated randomly. In tests from $ 4 $ to $ 10 $ , $ n = 5 $ ; in tests from $ 11 $ to $ 20 $ , $ n = 1000 $ ; in tests from $ 21 $ to $ 40 $ , $ n = 10^6 $ .

Hacks are forbidden in this problem.

## 输出格式

Print the maximum possible value you can get in binary representation without leading zeroes.

## 说明/提示

In the first example, you can choose the substrings 11010 and 101. $ f(s_1) = 26 $ , $ f(s_2) = 5 $ , their bitwise OR is $ 31 $ , and the binary representation of $ 31 $ is 11111.

In the second example, you can choose the substrings 1110010 and 11100.

## 样例 #1

### 输入

```
5
11010
```

### 输出

```
11111
```

## 样例 #2

### 输入

```
7
1110010
```

### 输出

```
1111110
```

## 样例 #3

### 输入

```
4
0000
```

### 输出

```
0
```

