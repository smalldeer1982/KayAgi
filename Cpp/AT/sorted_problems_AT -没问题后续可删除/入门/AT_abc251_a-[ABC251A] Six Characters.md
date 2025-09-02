---
title: "[ABC251A] Six Characters"
layout: "post"
diff: 入门
pid: AT_abc251_a
tag: []
---

# [ABC251A] Six Characters

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc251/tasks/abc251_a

英小文字からなる文字列 $ S $ が与えられます。 $ S $ の長さは $ 1 $ 以上かつ $ 3 $ 以下です。

$ S $ を繰り返して得られる文字列であって、長さが $ 6 $ のものを出力してください。

本問題の制約下で、そのような文字列はただ一つ存在することが示せます。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

答えとなる長さ $ 6 $ の文字列を出力せよ。

## 说明/提示

### 制約

- $ S $ は英小文字からなる長さ $ 1 $ 以上 $ 3 $ 以下の文字列

### Sample Explanation 1

$ S\ = $ `abc` を繰り返してできる文字列として、`abc` 、`abcabc` 、`abcabcabc` 、`abcabcabcabc` などがあります。 そのうち、長さが $ 6 $ のものは `abcabc` です。よって、`abcabc` と出力します。

## 样例 #1

### 输入

```
abc
```

### 输出

```
abcabc
```

## 样例 #2

### 输入

```
zz
```

### 输出

```
zzzzzz
```

