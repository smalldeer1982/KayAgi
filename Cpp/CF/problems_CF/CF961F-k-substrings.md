---
title: "k-substrings"
layout: "post"
diff: 省选/NOI-
pid: CF961F
tag: []
---

# k-substrings

## 题目描述

给定一个长度为 $n$ 的字符串 $T$ 。

定义 $k$ 子串表示 $S_k , S_{k+1} ~ \cdots S_{n - k +1}$ 。显然的， $1$子串= $T$，并且有  $\lceil \frac n 2 \rceil$ 个 $k$ 子串。

对于每一个 $k$ 子串  $k=1,2,3...\lceil \frac n 2 \rceil$ ，试找出最大长度的字符串 $t$，使得 $t$ 是 $T$ 的前缀和后缀且 $t$ 的 长度为奇数。

## 输入格式

输入的第一行是一个整数 $n$，表示字符串的长度。

输入的第二行是一个长度为 $n$ 的字符串。

## 输出格式

输出 $\lceil \frac n 2 \rceil$ 个数，其中第 $i$ 个数为 满足 $t$ 是 $i$ 子串的前缀和后缀的字符串  $t$ 的最大长度。

翻译贡献者：@[misinclair](https://www.luogu.com.cn/user/46749)

## 样例 #1

### 输入

```
15
bcabcabcabcabca

```

### 输出

```
9 7 5 3 1 -1 -1 -1

```

## 样例 #2

### 输入

```
24
abaaabaaaabaaabaaaabaaab

```

### 输出

```
15 13 11 9 7 5 3 1 1 -1 -1 1

```

## 样例 #3

### 输入

```
19
cabcabbcabcabbcabca

```

### 输出

```
5 3 1 -1 -1 1 1 -1 -1 -1

```

