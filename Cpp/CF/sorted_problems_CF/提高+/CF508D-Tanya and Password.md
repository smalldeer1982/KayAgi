---
title: "Tanya and Password"
layout: "post"
diff: 提高+/省选-
pid: CF508D
tag: []
---

# Tanya and Password

## 题目描述

While dad was at work, a little girl Tanya decided to play with dad's password to his secret database. Dad's password is a string consisting of $ n+2 $ characters. She has written all the possible $ n $ three-letter continuous substrings of the password on pieces of paper, one for each piece of paper, and threw the password out. Each three-letter substring was written the number of times it occurred in the password. Thus, Tanya ended up with $ n $ pieces of paper.

Then Tanya realized that dad will be upset to learn about her game and decided to restore the password or at least any string corresponding to the final set of three-letter strings. You have to help her in this difficult task. We know that dad's password consisted of lowercase and uppercase letters of the Latin alphabet and digits. Uppercase and lowercase letters of the Latin alphabet are considered distinct.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=2·10^{5} $ ), the number of three-letter substrings Tanya got.

Next $ n $ lines contain three letters each, forming the substring of dad's password. Each character in the input is a lowercase or uppercase Latin letter or a digit.

## 输出格式

If Tanya made a mistake somewhere during the game and the strings that correspond to the given set of substrings don't exist, print "NO".

If it is possible to restore the string that corresponds to given set of substrings, print "YES", and then print any suitable password option.

## 样例 #1

### 输入

```
5
aca
aba
aba
cab
bac

```

### 输出

```
YES
abacaba

```

## 样例 #2

### 输入

```
4
abc
bCb
cb1
b13

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
7
aaa
aaa
aaa
aaa
aaa
aaa
aaa

```

### 输出

```
YES
aaaaaaaaa

```

