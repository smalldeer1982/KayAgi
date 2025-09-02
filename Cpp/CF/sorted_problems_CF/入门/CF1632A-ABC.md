---
title: "ABC"
layout: "post"
diff: 入门
pid: CF1632A
tag: []
---

# ABC

## 题目描述

Recently, the students of School 179 have developed a unique algorithm, which takes in a binary string $ s $ as input. However, they soon found out that if some substring $ t $ of $ s $ is a palindrome of length greater than 1, the algorithm will work incorrectly. Can the students somehow reorder the characters of $ s $ so that the algorithm will work correctly on the string?

A binary string is a string where each character is either 0 or 1.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

A palindrome is a string that reads the same backwards as forwards.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 100 $ ). Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100 $ ) — the length of the string $ s $ .

The second line of each test case contains the string $ s $ of length $ n $ consisting only of the characters 0 and 1.

## 输出格式

For each test case, print YES (case-insensitive) if it is possible to reorder the characters of $ s $ so that there are no substrings that are a palindrome of length greater than 1, or NO (case-insensitive) otherwise.

## 说明/提示

In the first three test cases, the given strings do not contain palindromes of length greater than 1, so the answers are YES.

In the last test case, it is impossible to reorder the characters so that the string does not contain palindromes of length greater than 1, so the answer is NO.

## 样例 #1

### 输入

```
4
1
1
2
10
2
01
4
1010
```

### 输出

```
YES
YES
YES
NO
```

