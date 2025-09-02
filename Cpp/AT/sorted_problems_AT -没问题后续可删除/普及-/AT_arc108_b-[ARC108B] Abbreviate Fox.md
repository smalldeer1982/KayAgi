---
title: "[ARC108B] Abbreviate Fox"
layout: "post"
diff: 普及-
pid: AT_arc108_b
tag: []
---

# [ARC108B] Abbreviate Fox

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc108/tasks/arc108_b

長さ $ N $ の英小文字のみからなる文字列 $ s $ が与えられます。 すぬけ君は $ s $ から `fox` という部分文字列を $ 1 $ つ選んで取り除き、その前後の部分を連結する、という操作を何度でも行うことができます。

すぬけ君が操作を何度か行ったあと、$ s $ の長さは最小でいくつになりえますか？

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ s $

## 输出格式

すぬけ君が操作を何度か行ったあとの $ s $ の長さとしてありうる値の最小値を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ s $ は英小文字のみからなる長さ $ N $ の文字列

### Sample Explanation 1

\- `icefox` の末尾 `fox` を取り除くことで $ s $ を `ice` にすることができます。

### Sample Explanation 2

\- `fox` という部分文字列が存在しません。

## 样例 #1

### 输入

```
6
icefox
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
firebox
```

### 输出

```
7
```

## 样例 #3

### 输入

```
48
ffoxoxuvgjyzmehmopfohrupffoxoxfofofoxffoxoxejffo
```

### 输出

```
27
```

