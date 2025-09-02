---
title: "Cipher Shifer"
layout: "post"
diff: 入门
pid: CF1840A
tag: []
---

# Cipher Shifer

## 题目描述

There is a string $ a $ (unknown to you), consisting of lowercase Latin letters, encrypted according to the following rule into string $ s $ :

- after each character of string $ a $ , an arbitrary (possibly zero) number of any lowercase Latin letters, different from the character itself, is added;
- after each such addition, the character that we supplemented is added.

You are given string $ s $ , and you need to output the initial string $ a $ . In other words, you need to decrypt string $ s $ .

Note that each string encrypted in this way is decrypted uniquely.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The descriptions of the test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 100 $ ) — the length of the encrypted message.

The second line of each test case contains a string $ s $ of length $ n $ — the encrypted message obtained from some string $ a $ .

## 输出格式

For each test case, output the decrypted message $ a $ on a separate line.

## 说明/提示

In the first encrypted message, the letter $ a $ is encrypted as $ aba $ , and the letter $ c $ is encrypted as $ cabac $ .

In the second encrypted message, only one letter $ q $ is encrypted as $ qzxcq $ .

In the third encrypted message, zero characters are added to each letter.

## 样例 #1

### 输入

```
3
8
abacabac
5
qzxcq
20
ccooddeeffoorrcceess
```

### 输出

```
ac
q
codeforces
```

