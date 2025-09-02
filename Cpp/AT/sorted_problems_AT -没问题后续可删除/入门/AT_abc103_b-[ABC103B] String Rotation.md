---
title: "[ABC103B] String Rotation"
layout: "post"
diff: 入门
pid: AT_abc103_b
tag: []
---

# [ABC103B] String Rotation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc103/tasks/abc103_b

英小文字からなる文字列 $ S $, $ T $ が与えられます。

$ S $ を回転させて $ T $ に一致させられるか判定してください。

すなわち、以下の操作を任意の回数繰り返して $ S $ を $ T $ に一致させられるか判定してください。

操作: $ S\ =\ S_1\ S_2\ ...\ S_{|S|} $ のとき、$ S $ を $ S_{|S|}\ S_1\ S_2\ ...\ S_{|S|-1} $ に変更する

ここで、$ |X| $ は文字列 $ X $ の長さを表します。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $ $ T $

## 输出格式

$ S $ を回転させて $ T $ に一致させられる場合は `Yes`、一致させられない場合は `No` を出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ |S|\ \leq\ 100 $
- $ |S|\ =\ |T| $
- $ S $, $ T $ は英小文字からなる

### Sample Explanation 1

\- $ 1 $ 回目の操作で `kyoto` が `okyot` になります - $ 2 $ 回目の操作で `okyot` が `tokyo` になります

### Sample Explanation 2

何度操作を行っても `abc` と `arc` を一致させられません。

## 样例 #1

### 输入

```
kyoto
tokyo
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
abc
arc
```

### 输出

```
No
```

## 样例 #3

### 输入

```
aaaaaaaaaaaaaaab
aaaaaaaaaaaaaaab
```

### 输出

```
Yes
```

