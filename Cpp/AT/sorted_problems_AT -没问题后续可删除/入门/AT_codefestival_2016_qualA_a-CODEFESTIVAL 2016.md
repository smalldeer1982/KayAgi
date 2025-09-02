---
title: "CODEFESTIVAL 2016"
layout: "post"
diff: 入门
pid: AT_codefestival_2016_qualA_a
tag: []
---

# CODEFESTIVAL 2016

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2016-quala/tasks/codefestival_2016_qualA_a

このコンテストの名前は `CODE FESTIVAL` です。 しかし、高橋君はいつも `CODEFESTIVAL` と書き間違えてしまいます。 つまり、`CODE` と `FESTIVAL` の間の半角スペースを省いてしまいます。

そこで高橋君は、省いてしまった半角スペースを復元するプログラムを作ることにしました。

長さ $ 12 $ の文字列 $ s $ が与えられます。 $ s $ の前半 $ 4 $ 文字と後半 $ 8 $ 文字の間に半角スペースを $ 1 $ つ挿入し、出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ s $

## 输出格式

$ s $ の前半 $ 4 $ 文字と後半 $ 8 $ 文字の間に半角スペースを $ 1 $ つ挿入し、出力せよ。 出力の末尾には改行を入れること。

## 说明/提示

### 制約

- $ s $ は長さ $ 12 $ である。
- $ s $ は英大文字のみからなる。

### Sample Explanation 1

`CODEFESTIVAL` の前半 $ 4 $ 文字と後半 $ 8 $ 文字の間に半角スペースを $ 1 $ つ挿入すると、`CODE FESTIVAL` となります。

## 样例 #1

### 输入

```
CODEFESTIVAL
```

### 输出

```
CODE FESTIVAL
```

## 样例 #2

### 输入

```
POSTGRADUATE
```

### 输出

```
POST GRADUATE
```

## 样例 #3

### 输入

```
ABCDEFGHIJKL
```

### 输出

```
ABCD EFGHIJKL
```

