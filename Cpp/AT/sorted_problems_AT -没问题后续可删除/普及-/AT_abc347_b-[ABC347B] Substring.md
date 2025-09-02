---
title: "[ABC347B] Substring"
layout: "post"
diff: 普及-
pid: AT_abc347_b
tag: []
---

# [ABC347B] Substring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc347/tasks/abc347_b

英小文字からなる文字列 $ S $ が与えられます。$ S $ の空でない部分文字列は何種類ありますか？

ただし、部分文字列とは連続する部分列のことを指します。例えば、`xxx` は `yxxxy` の部分文字列ですが、`xxyxx` の部分文字列ではありません。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ S $ は英小文字からなる長さ $ 1 $ 以上 $ 100 $ 以下の文字列
 
### Sample Explanation 1

$ S $ の空でない部分文字列は以下の $ 5 $ 種類です。 - `a` - `y` - `ay` - `ya` - `yay`

## 样例 #1

### 输入

```
yay
```

### 输出

```
5
```

## 样例 #2

### 输入

```
aababc
```

### 输出

```
17
```

## 样例 #3

### 输入

```
abracadabra
```

### 输出

```
54
```

