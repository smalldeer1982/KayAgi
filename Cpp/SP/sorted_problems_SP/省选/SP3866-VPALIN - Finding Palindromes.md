---
title: "VPALIN - Finding Palindromes"
layout: "post"
diff: 省选/NOI-
pid: SP3866
tag: []
---

# VPALIN - Finding Palindromes

## 题目描述

给出$n$个字符串，将$n$个字符串两两首尾相连，可以得到$n*n$个新的字符串。

求在这$n*n$个字符串中，有多少个是回文的。

## 输入格式

第一行一个整数$n$，表示字符串的个数。

接下来$n$行描述每个字符串：

第$i+1$包括第$i$个字符串的长度$li$，然后是一个空格和一个字符串（只包括英文小写字母）。

所有字符串总长度不超过$2e6$，不同行的两个字符串可能相同。

## 输出格式

输出一个整数，为回文串的数量。

## 样例 #1

### 输入

```
3
1 a
2 bb
2 aa
```

### 输出

```
5
The 5 palindromes are:
aa aaa aaa bbb aaaa
```

