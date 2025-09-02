---
title: "PRETILE - Prefix Tiling"
layout: "post"
diff: 难度0
pid: SP2743
tag: []
---

# PRETILE - Prefix Tiling

## 题目描述

给定一个字符串 $S$，其长度为 $N$，由字母 'A' 到 'Z' 组成（$1 \le N \le 100,000$）。对于任意的整数 $L$（$1 \le L \le N$），定义 $match(L)$ 为：把 $S$ 的前缀长度为 $L$ 的部分重复拼接，看它能与整个字符串 $S$ 的最长前缀有多长。也就是说，$match(L)$ 是最小的非负整数 $k$，使得 $S[k] \neq S[k \mod L]$，如果这样的 $k$ 不存在，则 $match(L) = N$。例如，当 $S = \text{``ABCAB''}$ 时，有 $match(1) = 1$（第一个字符就不同），$match(3) = 5$（整个字符串都被匹配），以及 $match(4) = 4$（在第四个字符不匹配）。计算并输出 $match(1) + match(2) + \ldots + match(N)$ 的总和。

## 输入格式

第一行输入一个整数 $T$ （$1 \le T \le 10$），表示测试用例的数量。接下来的每一行包含一个字符串 $S$，代表一个测试用例。

## 输出格式

对于每个测试用例，输出一个整数，即 $match(1) + match(2) + \ldots + match(N)$ 的值。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
ABCAB
ZZZZZZ
```

### 输出

```
17
36
```

