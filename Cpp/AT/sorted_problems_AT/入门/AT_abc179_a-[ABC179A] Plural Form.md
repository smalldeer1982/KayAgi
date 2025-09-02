---
title: "[ABC179A] Plural Form"
layout: "post"
diff: 入门
pid: AT_abc179_a
tag: []
---

# [ABC179A] Plural Form

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc179/tasks/abc179_a

AtCoder 王国では、英小文字を用いる高橋語という言語が使われています。

高橋語では、名詞の複数形は次のルールで綴られます。

- 単数形の末尾が `s` 以外なら、単数形の末尾に `s` をつける
- 単数形の末尾が `s` なら、単数形の末尾に `es` をつける

高橋語の名詞の単数形 $ S $ が与えられるので、複数形を出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

与えられた高橋語の複数形を出力せよ。

## 说明/提示

### 制約

- $ S $ は長さ $ 1 $ 以上 $ 1000 $ 以下の文字列
- $ S $ は英小文字のみを含む

### Sample Explanation 1

`apple` の末尾は `e` なので、複数形は `apples` になります。

### Sample Explanation 2

`bus` の末尾は `s` なので、複数形は `buses` になります。

## 样例 #1

### 输入

```
apple
```

### 输出

```
apples
```

## 样例 #2

### 输入

```
bus
```

### 输出

```
buses
```

## 样例 #3

### 输入

```
box
```

### 输出

```
boxs
```

