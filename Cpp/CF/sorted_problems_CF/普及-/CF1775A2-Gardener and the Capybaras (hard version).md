---
title: "Gardener and the Capybaras (hard version)"
layout: "post"
diff: 普及-
pid: CF1775A2
tag: []
---

# Gardener and the Capybaras (hard version)

## 题目描述

有三个只由字符 `a,b` 构成的字符串 $a,b,c$ ，且 $a\le b,c\le b$ 或 $a\ge b,c\ge b$。 将它们拼在一起构成了一个新字符串 $s$。


现在给你 $s$，($3\le |s|\le 2\cdot 10^5$)，你要复原这三个字符串。

一共有 $T(T\le 10^4)$ 组测试数据，所有数据中字符串的总长不会超过 $4\cdot 10^5$。

## 输入格式

第一行，一个数 $T$。  
接下来的 $T$ 行，每行一个字符串，表示字符串 $s$。

## 输出格式

对于每组测试数据，输出一行三个字符串，用空格隔开，表示拆出的三个字符串。

如果有多种拆分方式，输出任意一种。

如果无法拆分，则输出 `:(`。

## 说明/提示

定义字符串 $x$ 小于 $y$ ，当且仅当：

$x$ 是 $y$ 的前缀，且 $x \not =y$ 。

或

在 $x$ 与 $y$ 的第一个不同的位置，$x$ 的这一位字符是 `a`，$y$ 的这一位字符是 `b`。

## 样例 #1

### 输入

```
5
bbba
aba
aaa
abba
abbb
```

### 输出

```
b bb a
a b a
a a a
ab b a
a bb b
```

