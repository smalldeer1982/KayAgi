---
title: "Diverse Substrings"
layout: "post"
diff: 普及+/提高
pid: CF386C
tag: ['枚举', '双指针 two-pointer']
---

# Diverse Substrings

## 题目描述

给定一个字符串 $s$，定义 $d(x)$ 为字符串 $x$ 内不同的字符个数。

求有多少个 $s$ 的子串 $s1$，使得 $d(s1)$ 为给定的 $t_{i}$。

## 输入格式

第一行包含一个字符串 $s$。

## 输出格式

第一行输出 $d(s)$。

然后输出 $t_1,t_2,\cdots,t_{d(s)}$ 对应的子串数量。

$1 \le |s| \le 3 \times 10^5$。

## 样例 #1

### 输入

```
abca

```

### 输出

```
3
4
3
3

```

## 样例 #2

### 输入

```
aabacaabbad

```

### 输出

```
4
14
19
28
5

```

