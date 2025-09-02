---
title: "[AGC006A] Prefix and Suffix"
layout: "post"
diff: 普及-
pid: AT_agc006_a
tag: []
---

# [AGC006A] Prefix and Suffix

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc006/tasks/agc006_a

すぬけ君は次の条件を満たす文字列に興味があります。

- 長さ $ N $ 以上である。
- 先頭 $ N $ 文字が文字列 $ s $ に一致する。
- 末尾 $ N $ 文字が文字列 $ t $ に一致する。

条件を満たす文字列のうち、最も短いものの長さを求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ s $ $ t $

## 输出格式

条件を満たす文字列のうち、最も短いものの長さを出力せよ。

## 说明/提示

### 制約

- $ 1\ <\ =N\ <\ =100 $
- $ s $, $ t $ は長さ $ N $ である。
- $ s $, $ t $ は英小文字のみからなる。

### Sample Explanation 1

最も短い文字列は `abcde` です。

### Sample Explanation 2

最も短い文字列は `az` です。

### Sample Explanation 3

最も短い文字列は `expr` です。

## 样例 #1

### 输入

```
3
abc
cde
```

### 输出

```
5
```

## 样例 #2

### 输入

```
1
a
z
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
expr
expr
```

### 输出

```
4
```

