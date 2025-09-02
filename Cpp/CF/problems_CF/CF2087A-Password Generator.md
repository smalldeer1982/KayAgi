---
title: "Password Generator"
layout: "post"
diff: 难度0
pid: CF2087A
tag: []
---

# Password Generator

## 题目描述

Monocarp is going to register on the Codeforces website, but he can't come up with a sufficiently secure password. The requirements that his password must meet are as follows:

- the password must consist of digits, as well as uppercase and lowercase letters of the Latin alphabet;
- there must be exactly $ a $ digits, exactly $ b $ uppercase letters, and exactly $ c $ lowercase letters;
- for security, no two adjacent characters in the password should be the same. The lowercase and uppercase versions of the same letter are considered different characters.

Write a program that generates a password that meets all the requirements.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case consists of one line containing three integers $ a $ , $ b $ , and $ c $ ( $ 1 \le a, b, c \le 10 $ ).

## 输出格式

For each test case, output one line containing any suitable password. It can be shown that there is always at least one password that meets the requirements.

## 样例 #1

### 输入

```
2
2 1 6
3 3 6
```

### 输出

```
abaCaba42
b3sTpAs5w0rD
```

