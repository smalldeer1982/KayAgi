---
title: "Hitachi String"
layout: "post"
diff: 入门
pid: AT_hitachi2020_a
tag: []
---

# Hitachi String

## 题目描述

[problemUrl]: https://atcoder.jp/contests/hitachi2020/tasks/hitachi2020_a

文字列 `hi` が $ 1 $ 個以上繋がってできる文字列を、 hitachi文字列 と定義します。

例えば、 `hi` や `hihi` などは hitachi文字列 であり、 `ha` や `hii` は hitachi文字列 ではありません。

文字列 $ S $ が与えられるので、 $ S $ が hitachi文字列 かどうかを判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

$ S $ が hitachi文字列 であれば `Yes` を、そうでなければ `No` を出力せよ。

## 说明/提示

### 制約

- $ S $ の長さは $ 1 $ 以上 $ 10 $ 以下
- $ S $ は英小文字列

### Sample Explanation 1

`hihi` は `hi` を $ 2 $ 個繋げてできる文字列なので、 hitachi文字列です。

## 样例 #1

### 输入

```
hihi
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
hi
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
ha
```

### 输出

```
No
```

