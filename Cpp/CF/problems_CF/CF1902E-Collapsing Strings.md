---
title: "Collapsing Strings"
layout: "post"
diff: 普及+/提高
pid: CF1902E
tag: []
---

# Collapsing Strings

## 题目描述

You are given $ n $ strings $ s_1, s_2, \dots, s_n $ , consisting of lowercase Latin letters. Let $ |x| $ be the length of string $ x $ .

Let a collapse $ C(a, b) $ of two strings $ a $ and $ b $ be the following operation:

- if $ a $ is empty, $ C(a, b) = b $ ;
- if $ b $ is empty, $ C(a, b) = a $ ;
- if the last letter of $ a $ is equal to the first letter of $ b $ , then $ C(a, b) = C(a_{1,|a|-1}, b_{2,|b|}) $ , where $ s_{l,r} $ is the substring of $ s $ from the $ l $ -th letter to the $ r $ -th one;
- otherwise, $ C(a, b) = a + b $ , i. e. the concatenation of two strings.

Calculate $ \sum\limits_{i=1}^n \sum\limits_{j=1}^n |C(s_i, s_j)| $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ).

Each of the next $ n $ lines contains a string $ s_i $ ( $ 1 \le |s_i| \le 10^6 $ ), consisting of lowercase Latin letters.

The total length of the strings doesn't exceed $ 10^6 $ .

## 输出格式

Print a single integer — $ \sum\limits_{i=1}^n \sum\limits_{j=1}^n |C(s_i, s_j)| $ .

## 样例 #1

### 输入

```
3
aba
ab
ba
```

### 输出

```
20
```

## 样例 #2

### 输入

```
5
abab
babx
xab
xba
bab
```

### 输出

```
126
```

