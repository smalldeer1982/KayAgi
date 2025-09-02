---
title: "[ABC148B] Strings with the Same Length"
layout: "post"
diff: 入门
pid: AT_abc148_b
tag: []
---

# [ABC148B] Strings with the Same Length

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc148/tasks/abc148_b

英小文字のみからなる長さ $ N $ の文字列 $ S $, $ T $ が与えられます。

$ S $ の $ 1 $ 文字目、$ T $ の $ 1 $ 文字目、$ S $ の $ 2 $ 文字目、$ T $ の$ 2 $ 文字目、$ S $ の $ 3 $ 文字目、...、$ S $ の$ N $ 文字目、$ T $ の$ N $ 文字目というように、 $ S $ の各文字と $ T $ の各文字を先頭から順に交互に文字を並べ、新しい文字列を作ります。この新しくできた文字列を出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S $ $ T $

## 输出格式

新しくできた文字列を出力せよ。

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 100 $
- $ |S|\ =\ |T|\ =\ N $
- $ S $, $ T $ は英小文字のみからなる文字列

## 样例 #1

### 输入

```
2
ip cc
```

### 输出

```
icpc
```

## 样例 #2

### 输入

```
8
hmhmnknk uuuuuuuu
```

### 输出

```
humuhumunukunuku
```

## 样例 #3

### 输入

```
5
aaaaa aaaaa
```

### 输出

```
aaaaaaaaaa
```

