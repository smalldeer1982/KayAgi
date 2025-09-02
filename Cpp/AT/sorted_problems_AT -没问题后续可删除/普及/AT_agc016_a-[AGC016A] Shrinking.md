---
title: "[AGC016A] Shrinking"
layout: "post"
diff: 普及/提高-
pid: AT_agc016_a
tag: []
---

# [AGC016A] Shrinking

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc016/tasks/agc016_a

すぬけ君は、次のルールに従い、長さ $ N $ の文字列 $ t $ を長さ $ N\ -\ 1 $ の文字列 $ t' $ へ変えることができます。

- 各 $ i $ ($ 1\ <\ =\ i\ <\ =\ N\ -\ 1 $) について、$ t' $ の $ i $ 文字目は $ t $ の $ i $, $ i\ +\ 1 $ 文字目のどちらかである。

英小文字のみからなる文字列 $ s $ があります。 すぬけ君の目標は、$ s $ に上記の操作を繰り返し行い、$ s $ が単一の文字のみからなるようにすることです。 目標を達成するために必要な操作回数の最小値を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ s $

## 输出格式

目標を達成するために必要な操作回数の最小値を出力せよ。

## 说明/提示

### 制約

- $ 1\ <\ =\ |s|\ <\ =\ 100 $
- $ s $ は英小文字のみからなる。

### Sample Explanation 1

例えば、`serval` → `srvvl` → `svvv` → `vvv` と変えればよいです。

### Sample Explanation 2

例えば、`jackal` → `aacaa` → `aaaa` と変えればよいです。

### Sample Explanation 3

最初から $ s $ が単一の文字のみからなっています。

### Sample Explanation 4

$ 8 $ 回の操作によって、$ s $ を `rrrrrrrrrrrrrrrrrr` へ変えることができます。

## 样例 #1

### 输入

```
serval
```

### 输出

```
3
```

## 样例 #2

### 输入

```
jackal
```

### 输出

```
2
```

## 样例 #3

### 输入

```
zzz
```

### 输出

```
0
```

## 样例 #4

### 输入

```
whbrjpjyhsrywlqjxdbrbaomnw
```

### 输出

```
8
```

