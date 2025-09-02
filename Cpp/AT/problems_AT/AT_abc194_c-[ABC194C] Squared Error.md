---
title: "[ABC194C] Squared Error"
layout: "post"
diff: 普及-
pid: AT_abc194_c
tag: []
---

# [ABC194C] Squared Error

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc194/tasks/abc194_c

長さ $ N $ の数列 $ A $ が与えられます。  
 各要素同士の差の $ 2 $ 乗の和、すなわち $ \displaystyle\ \sum_{i\ =\ 2}^{N}\ \sum_{j\ =\ 1}^{i\ -\ 1}\ (A_i\ -\ A_j)^2 $ を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ A_3 $ $ \cdots $ $ A_N $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 3\ \times\ 10^5 $
- $ |A_i|\ \le\ 200 $
- 入力に含まれる値は全て整数

### Sample Explanation 1

$ \sum_{i\ =\ 2}^{N}\ \sum_{j\ =\ 1}^{i\ -\ 1}\ (A_i\ -\ A_j)^2\ =\ (8\ -\ 2)^2\ +\ (4\ -\ 2)^2\ +\ (4\ -\ 8)^2\ =\ 56 $ です。

## 样例 #1

### 输入

```
3
2 8 4
```

### 输出

```
56
```

## 样例 #2

### 输入

```
5
-5 8 9 -4 -3
```

### 输出

```
950
```

