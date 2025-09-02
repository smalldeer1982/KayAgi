---
title: "[ABC279B] LOOKUP"
layout: "post"
diff: 入门
pid: AT_abc279_b
tag: []
---

# [ABC279B] LOOKUP

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc279/tasks/abc279_b

英小文字からなる文字列 $ S,T $ が与えられるので、 $ T $ が $ S $ の(連続する)部分文字列かどうか判定してください。

なお、文字列 $ X $ に以下の操作を $ 0 $ 回以上施して文字列 $ Y $ が得られる時、またその時に限り $ Y $ は $ X $ の(連続する)部分文字列であると言います。

- 以下の $ 2 $ つの操作から $ 1 $ つを選択して、その操作を行う。
  - $ X $ の先頭の $ 1 $ 文字を削除する。
  - $ X $ の末尾の $ 1 $ 文字を削除する。

例えば `tag` は `voltage` の(連続する)部分文字列ですが、 `ace` は `atcoder` の(連続する)部分文字列ではありません。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $ $ T $

## 输出格式

$ T $ が $ S $ の(連続する)部分文字列なら `Yes` 、そうでないなら `No` と出力せよ。

## 说明/提示

### 制約

- $ S,T $ は英小文字からなる
- $ 1\ \le\ |S|,|T|\ \le\ 100 $ ( $ |X| $ は文字列 $ X $ の長さ )

### Sample Explanation 1

`tag` は `voltage` の(連続する)部分文字列です。

### Sample Explanation 2

`ace` は `atcoder` の(連続する)部分文字列ではありません。

### Sample Explanation 4

$ S=T $ である場合もあります。

## 样例 #1

### 输入

```
voltage
tag
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
atcoder
ace
```

### 输出

```
No
```

## 样例 #3

### 输入

```
gorilla
gorillagorillagorilla
```

### 输出

```
No
```

## 样例 #4

### 输入

```
toyotasystems
toyotasystems
```

### 输出

```
Yes
```

