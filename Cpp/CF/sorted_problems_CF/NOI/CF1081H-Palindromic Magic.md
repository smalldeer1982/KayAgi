---
title: "Palindromic Magic"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1081H
tag: []
---

# Palindromic Magic

## 题目描述

After learning some fancy algorithms about palindromes, Chouti found palindromes very interesting, so he wants to challenge you with this problem.

Chouti has got two strings $ A $ and $ B $ . Since he likes [palindromes](https://en.wikipedia.org/wiki/Palindrome), he would like to pick $ a $ as some non-empty palindromic substring of $ A $ and $ b $ as some non-empty palindromic substring of $ B $ . Concatenating them, he will get string $ ab $ .

Chouti thinks strings he could get this way are interesting, so he wants to know how many different strings he can get.

## 输入格式

The first line contains a single string $ A $ ( $ 1 \le |A| \le 2 \cdot 10^5 $ ).

The second line contains a single string $ B $ ( $ 1 \le |B| \le 2 \cdot 10^5 $ ).

Strings $ A $ and $ B $ contain only lowercase English letters.

## 输出格式

The first and only line should contain a single integer — the number of possible strings.

## 说明/提示

In the first example, attainable strings are

- "a" + "a" = "aa",
- "aa" + "a" = "aaa",
- "aa" + "aba" = "aaaba",
- "aa" + "b" = "aab",
- "a" + "aba" = "aaba",
- "a" + "b" = "ab".

In the second example, attainable strings are "aa", "aaa", "aaaa", "aaaba", "aab", "aaba", "ab", "abaa", "abaaa", "abaaba", "abab", "ba", "baa", "baba", "bb".

Notice that though "a"+"aa"="aa"+"a"="aaa", "aaa" will only be counted once.

## 样例 #1

### 输入

```
aa
aba

```

### 输出

```
6

```

## 样例 #2

### 输入

```
aaba
abaa

```

### 输出

```
15

```

