---
title: "Cases"
layout: "post"
diff: 提高+/省选-
pid: CF1995D
tag: ['状态合并']
---

# Cases

## 题目描述

You're a linguist studying a mysterious ancient language. You know that

1. Its words consist only of the first $ c $ letters of the Latin alphabet.
2. Each word has a case which can be unambiguously determined by its last letter (different letters correspond to different cases). For example, words "ABACABA" and "ABA" (if they exist) have the same case in this language because they both have the same ending 'A', whereas "ALICE" and "BOB" have different cases. If the language does not have a case corresponding to some letter, it means that the word cannot end with this letter.
3. The length of each word is $ k $ or less.

You have a single text written in this language. Unfortunately, as the language is really ancient, spaces between words are missing and all letters are uppercase. You wonder what is the minimum number of cases the language can have. Can you find this out?

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10\,000 $ ) — the number of test cases. It is followed by descriptions of the test cases.

The first line of each test case contains three integers $ n $ , $ c $ , $ k $ ( $ 1 \le k \le n \le 2^{18} $ , $ 1 \le c \le 18 $ ) — the length of the text, the number of letters in the language, and the maximum length of the word.

The second line contains a string of $ n $ characters — the text itself. Each character is one of the first $ c $ uppercase letters of the Latin alphabet.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2^{18} $ and the sum of $ 2^c $ over all test cases does not exceed $ 2^{18} $ .

## 输出格式

For each test case, output a single line consisting of a single integer — the minimum number of cases in the language.

## 说明/提示

In the first test case, there must be five cases in the language (for each of the letters 'A', 'B', 'C', 'D', and 'E' there must be a case that has a corresponding ending).

In the fourth test case, one case with ending 'B' is sufficient.

## 样例 #1

### 输入

```
7
5 5 1
ABCDE
3 1 2
AAA
3 2 2
AAB
10 2 2
ABABABABAB
4 4 4
DCBA
1 17 1
Q
9 3 2
ABCABCABC
```

### 输出

```
5
1
2
1
1
1
2
```

