---
title: "Short Code"
layout: "post"
diff: 省选/NOI-
pid: CF965E
tag: ['字符串', '贪心', '递归']
---

# Short Code

## 题目描述

Arkady's code contains $ n $ variables. Each variable has a unique name consisting of lowercase English letters only. One day Arkady decided to shorten his code.

He wants to replace each variable name with its non-empty prefix so that these new names are still unique (however, a new name of some variable can coincide with some old name of another or same variable). Among such possibilities he wants to find the way with the smallest possible total length of the new names.

A string $ a $ is a prefix of a string $ b $ if you can delete some (possibly none) characters from the end of $ b $ and obtain $ a $ .

Please find this minimum possible total length of new names.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of variables.

The next $ n $ lines contain variable names, one per line. Each name is non-empty and contains only lowercase English letters. The total length of these strings is not greater than $ 10^5 $ . The variable names are distinct.

## 输出格式

Print a single integer — the minimum possible total length of new variable names.

## 说明/提示

In the first example one of the best options is to shorten the names in the given order as "cod", "co", "c".

In the second example we can shorten the last name to "aac" and the first name to "a" without changing the other names.

## 样例 #1

### 输入

```
3
codeforces
codehorses
code

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5
abba
abb
ab
aa
aacada

```

### 输出

```
11

```

## 样例 #3

### 输入

```
3
telegram
digital
resistance

```

### 输出

```
3

```

