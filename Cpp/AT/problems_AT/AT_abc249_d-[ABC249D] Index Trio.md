---
title: "[ABC249D] Index Trio"
layout: "post"
diff: 普及/提高-
pid: AT_abc249_d
tag: []
---

# [ABC249D] Index Trio

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc249/tasks/abc249_d

長さ $ N $ の整数列 $ A\ =\ (A_1,\ \dots,\ A_N) $ が与えられます。

以下の条件を全て満たす整数の組 $ (i,\ j,\ k) $ の総数を求めてください。

- $ 1\ \leq\ i,\ j,\ k\ \leq\ N $
- $ \frac{A_i}{A_j}\ =\ A_k $

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ \ldots $ $ A_N $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 2\ \times\ 10^5\ \,\ (1\ \leq\ i\ \leq\ N) $
- 入力は全て整数

### Sample Explanation 1

$ (i,\ j,\ k)\ =\ (1,\ 2,\ 3),\ (1,\ 3,\ 2) $ が条件を満たします。

## 样例 #1

### 输入

```
3
6 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1
2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
10
1 3 2 4 6 8 2 2 3 7
```

### 输出

```
62
```

