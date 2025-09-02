---
title: "[ABC338A] Capitalized?"
layout: "post"
diff: 入门
pid: AT_abc338_a
tag: []
---

# [ABC338A] Capitalized?

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc338/tasks/abc338_a

英大文字・英小文字からなる空でない文字列 $ S $ が与えられます。以下の条件が満たされているか判定してください。

- $ S $ の先頭の文字は大文字であり、それ以外の文字はすべて小文字である。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

条件が満たされていれば `Yes`、そうでなければ `No` を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 100 $（$ |S| $ は文字列 $ S $ の長さ）
- $ S $ の各文字は英大文字または英小文字である。
 
### Sample Explanation 1

`Capitalized` の先頭の文字 `C` は大文字であり、それ以外の文字 `apitalized` はすべて小文字であるため、`Yes` を出力します。

### Sample Explanation 2

`AtCoder` は先頭以外にも大文字 `C` を含むため、`No` を出力します。

### Sample Explanation 3

`yes` の先頭の文字 `y` は大文字でないため、`No` を出力します。

## 样例 #1

### 输入

```
Capitalized
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
AtCoder
```

### 输出

```
No
```

## 样例 #3

### 输入

```
yes
```

### 输出

```
No
```

## 样例 #4

### 输入

```
A
```

### 输出

```
Yes
```

