---
title: "Reverse and Concatenate"
layout: "post"
diff: 入门
pid: CF1634A
tag: ['字符串']
---

# Reverse and Concatenate

## 题目描述

Real stupidity beats artificial intelligence every time.

— Terry Pratchett, Hogfather, Discworld



You are given a string $ s $ of length $ n $ and a number $ k $ . Let's denote by $ rev(s) $ the reversed string $ s $ (i.e. $ rev(s) = s_n s_{n-1} ... s_1 $ ). You can apply one of the two kinds of operations to the string:

- replace the string $ s $ with $ s + rev(s) $
- replace the string $ s $ with $ rev(s) + s $

How many different strings can you get as a result of performing exactly $ k $ operations (possibly of different kinds) on the original string $ s $ ?

In this statement we denoted the concatenation of strings $ s $ and $ t $ as $ s + t $ . In other words, $ s + t = s_1 s_2 ... s_n t_1 t_2 ... t_m $ , where $ n $ and $ m $ are the lengths of strings $ s $ and $ t $ respectively.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 100 $ ) — number of test cases. Next $ 2 \cdot t $ lines contain $ t $ test cases:

The first line of a test case contains two integers $ n $ and $ k $ ( $ 1 \le n \le 100 $ , $ 0 \le k \le 1000 $ ) — the length of the string and the number of operations respectively.

The second string of a test case contains one string $ s $ of length $ n $ consisting of lowercase Latin letters.

## 输出格式

For each test case, print the answer (that is, the number of different strings that you can get after exactly $ k $ operations) on a separate line.

It can be shown that the answer does not exceed $ 10^9 $ under the given constraints.

## 说明/提示

In the first test case of the example:

After the first operation the string $ s $ can become either aabbaa or baaaab. After the second operation there are 2 possibilities for $ s $ : aabbaaaabbaa and baaaabbaaaab.

## 样例 #1

### 输入

```
4
3 2
aab
3 3
aab
7 1
abacaba
2 0
ab
```

### 输出

```
2
2
1
1
```

