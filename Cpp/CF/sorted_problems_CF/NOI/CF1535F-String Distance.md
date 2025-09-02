---
title: "String Distance"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1535F
tag: []
---

# String Distance

## 题目描述

Suppose you are given two strings $ a $ and $ b $ . You can apply the following operation any number of times: choose any contiguous substring of $ a $ or $ b $ , and sort the characters in it in non-descending order. Let $ f(a, b) $ the minimum number of operations you have to apply in order to make them equal (or $ f(a, b) = 1337 $ if it is impossible to make $ a $ and $ b $ equal using these operations).

For example:

- $ f(\text{ab}, \text{ab}) = 0 $ ;
- $ f(\text{ba}, \text{ab}) = 1 $ (in one operation, we can sort the whole first string);
- $ f(\text{ebcda}, \text{ecdba}) = 1 $ (in one operation, we can sort the substring of the second string starting from the $ 2 $ -nd character and ending with the $ 4 $ -th character);
- $ f(\text{a}, \text{b}) = 1337 $ .

You are given $ n $ strings $ s_1, s_2, \dots, s_k $ having equal length. Calculate $ \sum \limits_{i = 1}^{n} \sum\limits_{j = i + 1}^{n} f(s_i, s_j) $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of strings.

Then $ n $ lines follow, each line contains one of the strings $ s_i $ , consisting of lowercase Latin letters. $ |s_1| = |s_2| = \ldots = |s_n| $ , and $ n \cdot |s_1| \le 2 \cdot 10^5 $ . All these strings are pairwise distinct.

## 输出格式

Print one integer: $ \sum \limits_{i = 1}^{n} \sum\limits_{j = i + 1}^{n} f(s_i, s_j) $ .

## 样例 #1

### 输入

```
4
zzz
bac
abc
acb
```

### 输出

```
4015
```

## 样例 #2

### 输入

```
2
a
b
```

### 输出

```
1337
```

