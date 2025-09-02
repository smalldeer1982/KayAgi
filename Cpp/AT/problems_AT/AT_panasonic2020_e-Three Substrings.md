---
title: "Three Substrings"
layout: "post"
diff: 提高+/省选-
pid: AT_panasonic2020_e
tag: []
---

# Three Substrings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/panasonic2020/tasks/panasonic2020_e

すぬけ君は、文字列 $ s $ を持っています。 あぬけ君、ぶぬけ君、くぬけ君は次のような方法でそれぞれ文字列 $ a,\ b,\ c $ を得ました。

- $ s $ の空でない ($ s $ 全体であってもよい) 連続な部分文字列を一つ選ぶ。その部分文字列のうちいくつかの文字 ($ 0 $ 個や全部であってもよい) を `?` で置き換える。

たとえば、$ s $ が `mississippi` であるとき、部分文字列として `ssissip` を選び、その $ 1,\ 3 $ 文字目を `?` で置き換えることで `?s?ssip` を得ることができます。

文字列 $ a,\ b,\ c $ が与えられます。 $ s $ の長さとして考えられる最小値を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ a $ $ b $ $ c $

## 输出格式

$ s $ の長さとして考えられる最小値を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ |a|,\ |b|,\ |c|\ \leq\ 2000 $
- $ a,\ b,\ c $ は英小文字と `?` からなる。

### Sample Explanation 1

たとえば、$ s $ が `atcoder` のとき条件を満たします。

### Sample Explanation 2

$ a,\ b,\ c $ は相異なるとは限りません。

## 样例 #1

### 输入

```
a?c
der
cod
```

### 输出

```
7
```

## 样例 #2

### 输入

```
atcoder
atcoder
???????
```

### 输出

```
7
```

