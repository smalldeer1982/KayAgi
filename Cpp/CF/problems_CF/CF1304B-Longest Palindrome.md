---
title: "Longest Palindrome"
layout: "post"
diff: 普及/提高-
pid: CF1304B
tag: []
---

# Longest Palindrome

## 题目描述

Returning back to problem solving, Gildong is now studying about palindromes. He learned that a palindrome is a string that is the same as its reverse. For example, strings "pop", "noon", "x", and "kkkkkk" are palindromes, while strings "moon", "tv", and "abab" are not. An empty string is also a palindrome.

Gildong loves this concept so much, so he wants to play with it. He has $ n $ distinct strings of equal length $ m $ . He wants to discard some of the strings (possibly none or all) and reorder the remaining strings so that the concatenation becomes a palindrome. He also wants the palindrome to be as long as possible. Please help him find one.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 100 $ , $ 1 \le m \le 50 $ ) — the number of strings and the length of each string.

Next $ n $ lines contain a string of length $ m $ each, consisting of lowercase Latin letters only. All strings are distinct.

## 输出格式

In the first line, print the length of the longest palindrome string you made.

In the second line, print that palindrome. If there are multiple answers, print any one of them. If the palindrome is empty, print an empty line or don't print this line at all.

## 说明/提示

In the first example, "battab" is also a valid answer.

In the second example, there can be 4 different valid answers including the sample output. We are not going to provide any hints for what the others are.

In the third example, the empty string is the only valid palindrome string.

## 样例 #1

### 输入

```
3 3
tab
one
bat
```

### 输出

```
6
tabbat
```

## 样例 #2

### 输入

```
4 2
oo
ox
xo
xx
```

### 输出

```
6
oxxxxo
```

## 样例 #3

### 输入

```
3 5
hello
codef
orces
```

### 输出

```
0
```

## 样例 #4

### 输入

```
9 4
abab
baba
abcd
bcde
cdef
defg
wxyz
zyxw
ijji
```

### 输出

```
20
ababwxyzijjizyxwbaba
```

