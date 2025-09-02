---
title: "[ABC162D] RGB Triplets"
layout: "post"
diff: 普及/提高-
pid: AT_abc162_d
tag: []
---

# [ABC162D] RGB Triplets

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc162/tasks/abc162_d

`R`, `G`, `B` のみからなる、長さ $ N $ の文字列 $ S $ があります。

以下の $ 2 $ つの条件をともに満たす組 $ (i,~j,~k)~(1\ \leq\ i\ <\ j\ <\ k\ \leq\ N) $ の数を求めてください。

- $ S_i\ \neq\ S_j $ かつ $ S_i\ \neq\ S_k $ かつ $ S_j\ \neq\ S_k $ である
- $ j\ -\ i\ \neq\ k\ -\ j $ である

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S $

## 输出格式

題意を満たす組の数を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 4000 $
- $ S $ は `R`, `G`, `B` のみからなる、長さ $ N $ の文字列である

### Sample Explanation 1

組 $ (1,~3,~4) $ だけが $ 2 $ つの条件をともに満たします。組 $ (2,~3,~4) $ は、$ 1 $ つ目の条件は満たしますが $ 2 $ つ目の条件を満たさないので不適です。

## 样例 #1

### 输入

```
4
RRGB
```

### 输出

```
1
```

## 样例 #2

### 输入

```
39
RBRBGRBGGBBRRGBBRRRBGGBRBGBRBGBRBBBGBBB
```

### 输出

```
1800
```

