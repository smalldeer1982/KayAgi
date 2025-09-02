---
title: "[ABC071B] Not Found"
layout: "post"
diff: 入门
pid: AT_abc071_b
tag: ['字符串']
---

# [ABC071B] Not Found

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc071/tasks/abc071_b

英小文字からなる文字列 $ S $ が与えられます． $ S $ に現れない英小文字であって，最も辞書順（アルファベット順）で小さいものを求めてください． ただし，$ S $ にすべての英小文字が現れる場合は，代わりに `None` を出力してください．

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

$ S $ に現れない英小文字であって，最も辞書順で小さいものを出力せよ． ただし，$ S $ にすべての英小文字が現れる場合は，代わりに `None` を出力せよ．

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 10^5 $ ($ |S| $ は文字列 $ S $ の長さ)
- $ S $ は英小文字のみからなる．

### Sample Explanation 1

`atcoderregularcontest` という文字列には `a` は現れますが `b` は現れません．

### Sample Explanation 2

この文字列には，すべての英小文字が現れます．

## 样例 #1

### 输入

```
atcoderregularcontest
```

### 输出

```
b
```

## 样例 #2

### 输入

```
abcdefghijklmnopqrstuvwxyz
```

### 输出

```
None
```

## 样例 #3

### 输入

```
fajsonlslfepbjtsaayxbymeskptcumtwrmkkinjxnnucagfrg
```

### 输出

```
d
```

