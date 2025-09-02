---
title: "[ARC113C] String Invasion"
layout: "post"
diff: 普及/提高-
pid: AT_arc113_c
tag: []
---

# [ARC113C] String Invasion

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc113/tasks/arc113_c

長さ $ N $ の文字列 $ S $ が与えられます。$ S $ の $ i $ 文字目を $ s_i $ で表します。以下の操作を繰り返せる回数の最大値を求めてください。

- 連続する $ 3 $ 文字 $ s_i,s_{i+1},s_{i+2}\quad\ (1\leq\ i\leq\ |S|-2) $ であって、$ s_i=s_{i+1}\neq\ s_{i+2} $ であるものを選ぶ。$ s_{i+2} $ を $ s_i $ で置き換える。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

操作を繰り返せる回数の最大値を出力せよ。

## 说明/提示

### 制約

- $ 3\ \leq\ |S|\ \leq\ 2\times\ 10^5 $
- $ S $ は英小文字からなる

### Sample Explanation 1

以下のように $ 3 $ 回の操作を行うことができます。 - $ i=2 $ に対して操作を行う。操作後の文字列は `acccpt` になる。 - $ i=3 $ に対して操作を行う。操作後の文字列は `acccct` になる。 - $ i=4 $ に対して操作を行う。操作後の文字列は `accccc` になる。

## 样例 #1

### 输入

```
accept
```

### 输出

```
3
```

## 样例 #2

### 输入

```
atcoder
```

### 输出

```
0
```

## 样例 #3

### 输入

```
anerroroccurred
```

### 输出

```
16
```

