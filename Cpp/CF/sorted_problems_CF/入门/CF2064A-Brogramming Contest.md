---
title: "Brogramming Contest"
layout: "post"
diff: 入门
pid: CF2064A
tag: []
---

# Brogramming Contest

## 题目描述

One day after waking up, your friend challenged you to a brogramming contest. In a brogramming contest, you are given a binary string $ ^{\text{∗}} $ $ s $ of length $ n $ and an initially empty binary string $ t $ . During a brogramming contest, you can make either of the following moves any number of times:

- remove some suffix $ ^{\text{†}} $ from $ s $ and place it at the end of $ t $ , or
- remove some suffix from $ t $ and place it at the end of $ s $ .

 To win the brogramming contest, you must make the minimum number of moves required to make $ s $ contain only the character $ \texttt{0} $ and $ t $ contain only the character $ \texttt{1} $ . Find the minimum number of moves required. $ ^{\text{∗}} $ A binary string is a string consisting of characters $ \texttt{0} $ and $ \texttt{1} $ .

 $ ^{\text{†}} $ A string $ a $ is a suffix of a string $ b $ if $ a $ can be obtained from deletion of several (possibly, zero or all) elements from the beginning of $ b $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

The first line of each test case is an integer $ n $ ( $ 1 \le n \le 1000 $ ) — the length of the string $ s $ .

The second line of each test case contains the binary string $ s $ .

The sum of $ n $ across all test cases does not exceed $ 1000 $ .

## 输出格式

For each testcase, output the minimum number of moves required.

## 说明/提示

An optimal solution to the first test case is as follows:

- $ s = \texttt{00}\color{red}{\texttt{110}} $ , $ t = $ empty string.
- $ s = \texttt{00} $ , $ t = \texttt{11}\color{red}{\texttt{0}} $ .
- $ s = \texttt{000} $ , $ t = \texttt{11} $ .

It can be proven that there is no solution using less than $ 2 $ moves.

In the second test case, you have to move the whole string from $ s $ to $ t $ in one move.

In the fourth test case, you don't have to do any moves.

## 样例 #1

### 输入

```
5
5
00110
4
1111
3
001
5
00000
3
101
```

### 输出

```
2
1
1
0
3
```

