---
title: "[ABC146B] ROT N"
layout: "post"
diff: 入门
pid: AT_abc146_b
tag: []
---

# [ABC146B] ROT N

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc146/tasks/abc146_b

英大文字のみからなる文字列 $ S $ があります。また、整数 $ N $ が与えられます。

$ S $ の各文字を、アルファベット順で $ N $ 個後の文字に置き換えた文字列を出力してください。

ただしアルファベット順で `Z` の $ 1 $ 個後の文字は `A` とみなします。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S $

## 输出格式

$ S $ の各文字を、アルファベット順で $ N $ 個後の文字に置き換えた文字列を出力せよ。

## 说明/提示

### 制約

- $ 0\ \leq\ N\ \leq\ 26 $
- $ 1\ \leq\ |S|\ \leq\ 10^4 $
- $ S $ は英大文字のみからなる

### Sample Explanation 1

アルファベット順で `Z` の $ 1 $ 個後の文字は `A` であることに注意してください。

## 样例 #1

### 输入

```
2
ABCXYZ
```

### 输出

```
CDEZAB
```

## 样例 #2

### 输入

```
0
ABCXYZ
```

### 输出

```
ABCXYZ
```

## 样例 #3

### 输入

```
13
ABCDEFGHIJKLMNOPQRSTUVWXYZ
```

### 输出

```
NOPQRSTUVWXYZABCDEFGHIJKLM
```

