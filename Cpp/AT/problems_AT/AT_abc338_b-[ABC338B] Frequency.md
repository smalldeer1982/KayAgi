---
title: "[ABC338B] Frequency"
layout: "post"
diff: 入门
pid: AT_abc338_b
tag: []
---

# [ABC338B] Frequency

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc338/tasks/abc338_b

英小文字からなる文字列 $ S $ が与えられます。$ S $ に最も多く出現する文字を求めてください。そのような文字が複数ある場合は、そのうちアルファベット順で最も早いものを答えてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

$ S $ に最も多く出現する文字のうちアルファベット順で最も早いものを出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 1000 $（$ |S| $ は文字列 $ S $ の長さ）
- $ S $ の各文字は英小文字である。
 
### Sample Explanation 1

`frequency` には `e` が $ 2 $ 回出現し、これは他のどの文字よりも多いため `e` を出力します。

### Sample Explanation 2

`atcoder` には `a`, `t`, `c`, `o`, `d`, `e`, `r` が $ 1 $ 回ずつ出現するため、このうちアルファベット順で最も早い `a` を出力します。

## 样例 #1

### 输入

```
frequency
```

### 输出

```
e
```

## 样例 #2

### 输入

```
atcoder
```

### 输出

```
a
```

## 样例 #3

### 输入

```
pseudopseudohypoparathyroidism
```

### 输出

```
o
```

