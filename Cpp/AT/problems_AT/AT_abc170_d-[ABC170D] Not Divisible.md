---
title: "[ABC170D] Not Divisible"
layout: "post"
diff: 普及/提高-
pid: AT_abc170_d
tag: []
---

# [ABC170D] Not Divisible

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc170/tasks/abc170_d

長さ $ N $ の数列 $ A $ が与えられます。

次の性質を満たす整数 $ i $ $ \left(1\ \leq\ i\ \leq\ N\ \right) $ の数を答えてください。

- $ i\ \neq\ j $ である任意の整数 $ j $ $ \left(1\ \leq\ j\ \leq\ N\right) $ について $ A_i $ は $ A_j $ で割り切れない

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ \cdots $ $ A_N $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^6 $

### Sample Explanation 1

問の性質を満たすのは $ 2 $ , $ 3 $ , $ 4 $ です。

### Sample Explanation 2

同じ数が存在する場合に注意してください。

## 样例 #1

### 输入

```
5
24 11 8 3 16
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
5 5 5 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
10
33 18 45 28 8 19 89 86 2 4
```

### 输出

```
5
```

