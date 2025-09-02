---
title: "Three Strings"
layout: "post"
diff: 普及/提高-
pid: CF2050E
tag: ['动态规划 DP']
---

# Three Strings

## 题目描述

You are given three strings: $ a $ , $ b $ , and $ c $ , consisting of lowercase Latin letters. The string $ c $ was obtained in the following way:

1. At each step, either string $ a $ or string $ b $ was randomly chosen, and the first character of the chosen string was removed from it and appended to the end of string $ c $ , until one of the strings ran out. After that, the remaining characters of the non-empty string were added to the end of $ c $ .
2. Then, a certain number of characters in string $ c $ were randomly changed.

For example, from the strings $ a=\color{red}{\text{abra}} $ and $ b=\color{blue}{\text{cada}} $ , without character replacements, the strings $ \color{blue}{\text{ca}}\color{red}{\text{ab}}\color{blue}{\text{d}}\color{red}{\text{ra}}\color{blue}{\text{a}} $ , $ \color{red}{\text{abra}}\color{blue}{\text{cada}} $ , $ \color{red}{\text{a}}\color{blue}{\text{cada}}\color{red}{\text{bra}} $ could be obtained.

Find the minimum number of characters that could have been changed in string $ c $ .

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^3 $ ) — the number of test cases.

The first line of each test case contains one string of lowercase Latin letters $ a $ ( $ 1 \leq |a| \leq 10^3 $ ) — the first string, where $ |a| $ denotes the length of string $ a $ .

The second line of each test case contains one string of lowercase Latin letters $ b $ ( $ 1 \leq |b| \leq 10^3 $ ) — the second string, where $ |b| $ denotes the length of string $ b $ .

The third line of each test case contains one string of lowercase Latin letters $ c $ ( $ |c| = |a| + |b| $ ) — the third string.

It is guaranteed that the sum of $ |a| $ across all test cases does not exceed $ 2 \cdot 10^3 $ . Also, the sum of $ |b| $ across all test cases does not exceed $ 2 \cdot 10^3 $ .

## 输出格式

For each test case, output a single integer — the minimum number of characters that could have been changed in string $ c $ .

## 样例 #1

### 输入

```
7
a
b
cb
ab
cd
acbd
ab
ba
aabb
xxx
yyy
xyxyxy
a
bcd
decf
codes
horse
codeforces
egg
annie
egaegaeg
```

### 输出

```
1
0
2
0
3
2
3
```

