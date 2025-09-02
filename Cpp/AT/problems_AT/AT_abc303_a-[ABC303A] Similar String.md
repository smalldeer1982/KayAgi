---
title: "[ABC303A] Similar String"
layout: "post"
diff: 入门
pid: AT_abc303_a
tag: []
---

# [ABC303A] Similar String

## 题目描述

定义字符 $x$ 和 $y$ 相似，当且仅当 $x$ 和 $y$ 满足以下三个条件之一：
- $x$ 和 $y$ 是相同的字符。
- $x$ 和 $y$ 中一个是 `1`，一个是 `l`。
- $x$ 和 $y$ 中一个是 `0`，一个是 `o`。

定义长度为 $n$ 的字符串 $s$ 和 $t$ 相似，当且仅当 $s$ 和 $t$ 满足以下条件：
- 对于所有 $1\le i\le n$，都满足 $s_i$ 和 $t_i$ 相似。

## 输入格式

第一行输入一个整数 $n~(1\le n\le 100)$，代表字符串长度。

第二行和第三行输入两个长度为 $n$ 的两个字符串 $s$ 和 $t$，且仅由小写字母和数字组成。

## 输出格式

若字符串 $s$ 和 $t$ 相似，输出 `Yes`，否则输出 `No`。

Translated by [Special_Tony](https://www.luogu.com.cn/user/571147) .

## 样例 #1

### 输入

```
3
l0w
1ow
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3
abc
arc
```

### 输出

```
No
```

## 样例 #3

### 输入

```
4
nok0
n0ko
```

### 输出

```
Yes
```

