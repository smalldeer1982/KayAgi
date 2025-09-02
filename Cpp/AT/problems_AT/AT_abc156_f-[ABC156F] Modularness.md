---
title: "[ABC156F] Modularness"
layout: "post"
diff: 提高+/省选-
pid: AT_abc156_f
tag: []
---

# [ABC156F] Modularness

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc156/tasks/abc156_f

長さ $ k $ の数列 $ d_0,d_1,...,d_{k\ -\ 1} $ があります。

以下のクエリ $ q $ 個を順に処理してください。

- $ i $ 番目のクエリは $ 3 $ つの整数 $ n_i,x_i,m_i $ からなる。 長さ $ n_i $ の数列 $ a_0,a_1,...,a_{n_i\ -\ 1} $ を、 \\\[ \\begin{aligned} a\_j = \\begin{cases} x\_i &amp; ( j = 0 ) \\\\ a\_{j - 1} + d\_{(j - 1)~\\textrm{mod}~k} &amp; ( 0 &lt; j \\leq n\_i - 1 ) \\end{cases}\\end{aligned} \\\] と定める。 $ (a_j~\textrm{mod}~m_i)\ <\ (a_{j\ +\ 1}~\textrm{mod}~m_i) $ であるような、$ j~(0\ \leq\ j\ <\ n_i\ -\ 1) $ の個数を出力する。

ここで $ 2 $ つの整数 $ y,\ z~(z\ >\ 0) $ について、$ (y~\textrm{mod}~z) $ は $ y $ を $ z $ で割った余りを表します。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ k $ $ q $ $ d_0 $ $ d_1 $ $ ... $ $ d_{k\ -\ 1} $ $ n_1 $ $ x_1 $ $ m_1 $ $ n_2 $ $ x_2 $ $ m_2 $ $ : $ $ n_q $ $ x_q $ $ m_q $

## 输出格式

$ q $ 行出力せよ。

$ i $ 行目には、$ i $ 番目のクエリに対する答えを出力せよ。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ k,\ q\ \leq\ 5000 $
- $ 0\ \leq\ d_i\ \leq\ 10^9 $
- $ 2\ \leq\ n_i\ \leq\ 10^9 $
- $ 0\ \leq\ x_i\ \leq\ 10^9 $
- $ 2\ \leq\ m_i\ \leq\ 10^9 $

### Sample Explanation 1

$ 1 $ つ目のクエリについて、問題文で示した数列 {$ a_j $} は $ 3,6,7,11,14 $ になります。 - $ (a_0~\textrm{mod}~2)\ >\ (a_1~\textrm{mod}~2) $ - $ (a_1~\textrm{mod}~2)\ <\ (a_2~\textrm{mod}~2) $ - $ (a_2~\textrm{mod}~2)\ =\ (a_3~\textrm{mod}~2) $ - $ (a_3~\textrm{mod}~2)\ >\ (a_4~\textrm{mod}~2) $ であるため、このクエリに対する答えは $ 1 $ です。

## 样例 #1

### 输入

```
3 1
3 1 4
5 3 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7 3
27 18 28 18 28 46 1000000000
1000000000 1 7
1000000000 2 10
1000000000 3 12
```

### 输出

```
224489796
214285714
559523809
```

