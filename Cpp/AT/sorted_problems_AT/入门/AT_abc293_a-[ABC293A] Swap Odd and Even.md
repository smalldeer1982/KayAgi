---
title: "[ABC293A] Swap Odd and Even"
layout: "post"
diff: 入门
pid: AT_abc293_a
tag: []
---

# [ABC293A] Swap Odd and Even

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc293/tasks/abc293_a

英小文字からなる長さが偶数の文字列 $ S $ が与えられます。$ S $ の長さを $ |S| $、$ S $ の $ i $ 文字目を $ S_i $ で表します。

$ i\ =\ 1,\ 2,\ \ldots,\ \frac{|S|}{2} $ の順に以下の操作を行い、すべての操作を終えた後の $ S $ を出力してください。

- $ S_{2i-1} $ と $ S_{2i} $ を入れ替える

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ S $ は英小文字からなる長さが偶数の文字列
- $ S $ の長さは $ 100 $ 以下

### Sample Explanation 1

操作を行う前は $ S\ = $ `abcdef` です。 $ i\ =\ 1 $ について操作を行うと、$ S_1 $ と $ S_2 $ が入れ替わるので $ S\ = $ `bacdef` になります。 $ i\ =\ 2 $ について操作を行うと、$ S_3 $ と $ S_4 $ が入れ替わるので $ S\ = $ `badcef` になります。 $ i\ =\ 3 $ について操作を行うと、$ S_5 $ と $ S_6 $ が入れ替わるので $ S\ = $ `badcfe` になります。 したがって、`badcfe` を出力します。

## 样例 #1

### 输入

```
abcdef
```

### 输出

```
badcfe
```

## 样例 #2

### 输入

```
aaaa
```

### 输出

```
aaaa
```

## 样例 #3

### 输入

```
atcoderbeginnercontest
```

### 输出

```
taocedbrgeniencrnoetts
```

