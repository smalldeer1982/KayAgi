---
title: "Shohag Loves Strings"
layout: "post"
diff: 普及-
pid: CF2039B
tag: ['字符串', '贪心']
---

# Shohag Loves Strings

## 题目描述

# Shohag Loves Strings

## 问题描述

给定一个字符串 $s$，定义 $f(p)$ 为字符串 $p$ 的所有不同的非空子字符串的数量。从字符串 $s$ 中找到一个非空子字符串 $p$，使得 $f(p)$ 为偶数。如果找不到这样的子字符串，则输出 $-1$。

## 输入格式

- 第一行包含一个整数 $t$，表示测试数量 $(1 \le t \le 10^4)$。
- 接下来 $t$ 行，每行一个字符串 $s$，表示每次测试中的字符串 $s$。$(1 \le |s| \le 10^5)$，且所有字符串的总长度不超过 $3 \times 10^5$。

## 输出格式

- 对于每次测试，输出一个非空子字符串 $p$，使得 $f(p)$ 为偶数，如果不存在这样的子字符串，则输出 $-1$ 。若存在多个解，输出任意一个即可。

## 样例 #1

### 输入

```
5
dcabaac
a
youknowwho
codeforces
bangladesh
```

### 输出

```
abaa
-1
youknowwho
eforce
bang
```

