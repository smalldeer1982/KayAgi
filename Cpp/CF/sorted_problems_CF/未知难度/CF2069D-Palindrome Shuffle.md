---
title: "Palindrome Shuffle"
layout: "post"
diff: 难度0
pid: CF2069D
tag: []
---

# Palindrome Shuffle

## 题目描述

You are given a string $ s $ consisting of lowercase Latin letters.

You can perform the following operation with the string $ s $ : choose a contiguous substring (possibly empty) of $ s $ and shuffle it (reorder the characters in the substring as you wish).

Recall that a palindrome is a string that reads the same way from the first character to the last and from the last character to the first. For example, the strings a, bab, acca, bcabcbacb are palindromes, but the strings ab, abbbaa, cccb are not.

Your task is to determine the minimum possible length of the substring on which the aforementioned operation must be performed in order to convert the given string $ s $ into a palindrome.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The only line of each test case contains a string $ s $ ( $ 2 \le |s| \le 2 \cdot 10^5 $ ), consisting of lowercase Latin letters.

Additional constraints on the input:

- the string $ s $ has an even length;
- the string $ s $ can always be converted to a palindrome;
- the sum of lengths of $ s $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the minimum possible length of the substring on which the aforementioned operation must be performed in order to convert the given string $ s $ into a palindrome.

## 说明/提示

In the first example, you can perform the operation as follows: baba $ \rightarrow $ baab.

In the second example, the string is already a palindrome, so we can shuffle an empty substring.

In the third example, you can perform the operation as follows: ddaa $ \rightarrow $ adda.

In the fourth example, you can perform the operation as follows: acbacddacbca $ \rightarrow $ acbcaddacbca.

## 样例 #1

### 输入

```
4
baba
cc
ddaa
acbacddacbca
```

### 输出

```
2
0
3
2
```

