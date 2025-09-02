---
title: "[ABC346A] Adjacent Product"
layout: "post"
diff: 入门
pid: AT_abc346_a
tag: []
---

# [ABC346A] Adjacent Product

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc346/tasks/abc346_a

$ N $ 個の整数 $ A_1,A_2,\dots,A_N $ が与えられます。 また、$ B_i=A_i\times\ A_{i+1}\ (1\leq\ i\leq\ N-1) $ と定めます。

$ B_1,B_2,\dots,B_{N-1} $ をこの順に空白区切りで出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ \dots $ $ A_N $

## 输出格式

$ B_1,B_2,\dots,B_{N-1} $ をこの順に空白区切りで出力せよ。

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 100 $
- $ 1\leq\ A_i\ \leq\ 100 $
- 入力は全て整数
 
### Sample Explanation 1

$ B_1=A_1\times\ A_2\ =\ 12,\ B_2=A_2\times\ A_3\ =\ 24 $ です。

## 样例 #1

### 输入

```
3
3 4 6
```

### 输出

```
12 24
```

## 样例 #2

### 输入

```
5
22 75 26 45 72
```

### 输出

```
1650 1950 1170 3240
```

