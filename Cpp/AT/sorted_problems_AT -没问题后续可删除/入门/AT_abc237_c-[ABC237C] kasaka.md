---
title: "[ABC237C] kasaka"
layout: "post"
diff: 入门
pid: AT_abc237_c
tag: []
---

# [ABC237C] kasaka

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc237/tasks/abc237_c

英小文字からなる文字列 $ S $ が与えられます。 $ S $ の先頭に `a` をいくつか（ $ 0 $ 個でも良い）つけ加えて回文にすることができるか判定してください。

ただし、長さ $ N $ の文字列 $ A=A_1A_2\ldots\ A_N $ が回文であるとは、すべての $ 1\leq\ i\leq\ N $ について $ A_i=A_{N+1-i} $ が成り立っていることをいいます。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

$ S $ の先頭に `a` をいくつかつけ加えて回文にすることができるならば `Yes` を、そうでないならば `No` を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ \lvert\ S\ \rvert\ \leq\ 10^6 $
- $ S $ は英小文字のみからなる。

### Sample Explanation 1

`kasaka` の先頭に `a` を $ 1 $ つ付け加えることによって、`akasaka` となり回文となるため `Yes` を出力します。

### Sample Explanation 2

`atcoder` の先頭に `a` をいくつ付け加えても回文となる事はありません。

### Sample Explanation 3

`php` はそれ自体回文です。$ S $ の先頭に付け加える `a` は $ 0 $ 個でも許されるため、`Yes` を出力します。

## 样例 #1

### 输入

```
kasaka
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
atcoder
```

### 输出

```
No
```

## 样例 #3

### 输入

```
php
```

### 输出

```
Yes
```

