---
title: "[ABC394B] cat"
layout: "post"
diff: 难度0
pid: AT_abc394_b
tag: []
---

# [ABC394B] cat

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc394/tasks/abc394_b

英小文字からなる $ N $ 個の文字列 $ S_1,\ S_2,\ \ldots,\ S_N $ が与えられます。ここで、文字列の長さはそれぞれ相異なります。

これらの文字列を長さの昇順に並べ替え、この順に結合して得られる文字列を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S_1 $ $ S_2 $ $ \vdots $ $ S_N $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 50 $
- $ N $ は整数
- $ S_i $ は長さ $ 1 $ 以上 $ 50 $ 以下の英小文字からなる文字列
- $ i\ \neq\ j $ のとき $ S_i $ と $ S_j $ の長さは異なる
 
### Sample Explanation 1

$ ( $ `tc`$ , $ `oder`$ , $ `a` $ ) $ を文字列の長さの昇順に並べ替えると $ ( $ `a`$ , $ `tc`$ , $ `oder` $ ) $ となります。これらの文字列を順に結合すると文字列 `atcoder` が得られます。

## 样例 #1

### 输入

```
3
tc
oder
a
```

### 输出

```
atcoder
```

## 样例 #2

### 输入

```
4
cat
enate
on
c
```

### 输出

```
concatenate
```

