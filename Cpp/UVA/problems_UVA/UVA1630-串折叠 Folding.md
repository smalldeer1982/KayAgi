---
title: "串折叠 Folding"
layout: "post"
diff: 省选/NOI-
pid: UVA1630
tag: ['字符串', '动态规划 DP']
---

# 串折叠 Folding

## 题目描述

折叠由大写字母组成的长度为 $n$（$1\leqslant n\leqslant100$）的一个字符串，使得其成为一个尽量短的字符串，例如 `AAAAAA` 变成 `6(A)`。

这个折叠是可以嵌套的，例如 `NEEEEERYESYESYESNEEEEERYESYESYES` 会变成 `2(N5(E)R3(YES))`。

多解时可以输出任意解。

Translated by @_UKE自动机_

## 输入格式

**输入有多组数据**。

输入若干行，第 $i$ 行有一个仅由大写字母组成的，长度小于等于 $100$ 的字符串。

## 输出格式

对于每组输入，输出折叠后的字符串。

多解时可以输出任意解。

## 样例 #1

### 输入

```
AAAAAAAAAABABABCCD
NEERCYESYESYESNEERCYESYESYES
```

### 输出

```
9(A)3(AB)CCD
2(NEERC3(YES))
```

