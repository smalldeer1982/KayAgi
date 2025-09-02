---
title: "Fibonacci String Subsequences"
layout: "post"
diff: 省选/NOI-
pid: CF946F
tag: []
---

# Fibonacci String Subsequences

## 题目描述

You are given a binary string $ s $ (each character of this string is either 0 or 1).

Let's denote the cost of string $ t $ as the number of occurences of $ s $ in $ t $ . For example, if $ s $ is 11 and $ t $ is 111011, then the cost of $ t $ is $ 3 $ .

Let's also denote the Fibonacci strings sequence as follows:

- $ F(0) $ is 0;
- $ F(1) $ is 1;
- $ F(i)=F(i-1)+F(i-2) $ if $ i&gt;1 $ , where $ + $ means the concatenation of two strings.

Your task is to calculate the sum of costs of all subsequences of the string $ F(x) $ . Since answer may be large, calculate it modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains two integers $ n $ and $ x $ ( $ 1<=n<=100 $ , $ 0<=x<=100 $ ) — the length of $ s $ and the index of a Fibonacci string you are interested in, respectively.

The second line contains $ s $ — a string consisting of $ n $ characters. Each of these characters is either 0 or 1.

## 输出格式

Print the only integer — the sum of costs of all subsequences of the string $ F(x) $ , taken modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
2 4
11

```

### 输出

```
14

```

## 样例 #2

### 输入

```
10 100
1010101010

```

### 输出

```
553403224

```

