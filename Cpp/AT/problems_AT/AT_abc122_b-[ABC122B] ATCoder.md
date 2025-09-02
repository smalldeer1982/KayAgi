---
title: "[ABC122B] ATCoder"
layout: "post"
diff: 入门
pid: AT_abc122_b
tag: []
---

# [ABC122B] ATCoder

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc122/tasks/abc122_b

英大文字からなる文字列 $ S $ が与えられます。$ S $ の部分文字列 (注記を参照) であるような最も長い *ACGT 文字列* の長さを求めてください。

ここで、ACGT 文字列とは `A`, `C`, `G`, `T` 以外の文字を含まない文字列です。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

$ S $ の部分文字列であるような最も長い ACGT 文字列の長さを出力せよ。

## 说明/提示

### 注記

文字列 $ T $ の部分文字列とは、$ T $ の先頭と末尾から $ 0 $ 文字以上を取り去って得られる文字列です。

例えば、`ATCODER` の部分文字列には `TCO`, `AT`, `CODER`, `ATCODER`, `` (空文字列) が含まれ、`AC` は含まれません。

### 制約

- $ S $ は長さ $ 1 $ 以上 $ 10 $ 以下の文字列である。
- $ S $ の各文字は英大文字である。

### Sample Explanation 1

`ATCODER` の部分文字列であるような ACGT 文字列のうち、最も長いものは `ATC` です。

### Sample Explanation 2

`HATAGAYA` の部分文字列であるような ACGT 文字列のうち、最も長いものは `ATAGA` です。

### Sample Explanation 3

`SHINJUKU` の部分文字列であるような ACGT 文字列のうち、最も長いものは `` (空文字列) です。

## 样例 #1

### 输入

```
ATCODER
```

### 输出

```
3
```

## 样例 #2

### 输入

```
HATAGAYA
```

### 输出

```
5
```

## 样例 #3

### 输入

```
SHINJUKU
```

### 输出

```
0
```

