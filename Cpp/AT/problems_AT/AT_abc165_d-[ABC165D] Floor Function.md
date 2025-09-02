---
title: "[ABC165D] Floor Function"
layout: "post"
diff: 普及-
pid: AT_abc165_d
tag: []
---

# [ABC165D] Floor Function

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc165/tasks/abc165_d

整数 $ A $, $ B $, $ N $ が与えられます。

$ N $ 以下の非負整数 $ x $ に対する $ floor(Ax/B)\ -\ A\ ×\ floor(x/B) $ の最大値を求めてください。

ただし、$ floor(t) $ とは、実数 $ t $ 以下の最大の整数のことを表します。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A $ $ B $ $ N $

## 输出格式

$ N $ 以下の非負整数 $ x $ に対する $ floor(Ax/B)\ -\ A\ ×\ floor(x/B) $ の最大値を整数として出力せよ。

## 说明/提示

### 制約

- $ 1\ <\ =\ A\ <\ =\ 10^{6} $
- $ 1\ <\ =\ B\ <\ =\ 10^{12} $
- $ 1\ <\ =\ N\ <\ =\ 10^{12} $
- 入力は全て整数

### Sample Explanation 1

$ x=3 $ のとき、$ floor(Ax/B)-A×floor(x/B)\ =\ floor(15/7)\ -\ 5×floor(3/7)\ =\ 2 $ となり、これが最大です。

## 样例 #1

### 输入

```
5 7 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
11 10 9
```

### 输出

```
9
```

