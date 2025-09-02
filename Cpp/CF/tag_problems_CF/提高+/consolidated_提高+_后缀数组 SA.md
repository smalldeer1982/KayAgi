---
title: "Division + LCP (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF1968G2
tag: ['后缀数组 SA']
---

# Division + LCP (hard version)

## 题目描述

This is the hard version of the problem. In this version $ l\le r $ .

You are given a string $ s $ . For a fixed $ k $ , consider a division of $ s $ into exactly $ k $ continuous substrings $ w_1,\dots,w_k $ . Let $ f_k $ be the maximal possible $ LCP(w_1,\dots,w_k) $ among all divisions.

 $ LCP(w_1,\dots,w_m) $ is the length of the Longest Common Prefix of the strings $ w_1,\dots,w_m $ .

For example, if $ s=abababcab $ and $ k=4 $ , a possible division is $ \color{red}{ab}\color{blue}{ab}\color{orange}{abc}\color{green}{ab} $ . The $ LCP(\color{red}{ab},\color{blue}{ab},\color{orange}{abc},\color{green}{ab}) $ is $ 2 $ , since $ ab $ is the Longest Common Prefix of those four strings. Note that each substring consists of a continuous segment of characters and each character belongs to exactly one substring.

Your task is to find $ f_l,f_{l+1},\dots,f_r $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ , $ l $ , $ r $ ( $ 1 \le l \le r \le n \le 2 \cdot 10^5 $ ) — the length of the string and the given range.

The second line of each test case contains string $ s $ of length $ n $ , all characters are lowercase English letters.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output $ r-l+1 $ values: $ f_l,\dots,f_r $ .

## 样例 #1

### 输入

```
7
3 1 3
aba
3 2 3
aaa
7 1 5
abacaba
9 1 6
abababcab
10 1 10
aaaaaaawac
9 1 9
abafababa
7 2 7
vvzvvvv
```

### 输出

```
3 1 0 
1 1 
7 3 1 1 0 
9 2 2 2 0 0 
10 3 2 1 1 1 1 1 0 0 
9 3 2 1 1 0 0 0 0 
2 2 1 1 1 0
```



---

