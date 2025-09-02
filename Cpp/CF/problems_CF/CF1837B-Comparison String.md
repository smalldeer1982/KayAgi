---
title: "Comparison String"
layout: "post"
diff: 普及-
pid: CF1837B
tag: []
---

# Comparison String

## 题目描述

You are given a string $ s $ of length $ n $ , where each character is either &lt; or &gt;.

An array $ a $ consisting of $ n+1 $ elements is compatible with the string $ s $ if, for every $ i $ from $ 1 $ to $ n $ , the character $ s_i $ represents the result of comparing $ a_i $ and $ a_{i+1} $ , i. e.:

- $ s_i $ is &lt; if and only if $ a_i < a_{i+1} $ ;
- $ s_i $ is &gt; if and only if $ a_i > a_{i+1} $ .

For example, the array $ [1, 2, 5, 4, 2] $ is compatible with the string &lt;&lt;&gt;&gt;. There are other arrays with are compatible with that string, for example, $ [13, 37, 42, 37, 13] $ .

The cost of the array is the number of different elements in it. For example, the cost of $ [1, 2, 5, 4, 2] $ is $ 4 $ ; the cost of $ [13, 37, 42, 37, 13] $ is $ 3 $ .

You have to calculate the minimum cost among all arrays which are compatible with the given string $ s $ .

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases.

Each test case consists of two lines:

- the first line contains one integer $ n $ ( $ 1 \le n \le 100 $ );
- the second line contains the string $ s $ , consisting of $ n $ characters. Each character of $ s $ is either &lt; or &gt;.

## 输出格式

For each test case, print one integer — the minimum cost among all arrays which are compatible with the given string $ s $ .

## 说明/提示

In the first test case of the example, the array can be $ [13, 37, 42, 37, 13] $ .

In the second test case of the example, the array can be $ [42, 37, 13, 37, 42] $ .

## 样例 #1

### 输入

```
4
4
<<>>
4
>><<
5
>>>>>
7
<><><><

```

### 输出

```
3
3
6
2
```

