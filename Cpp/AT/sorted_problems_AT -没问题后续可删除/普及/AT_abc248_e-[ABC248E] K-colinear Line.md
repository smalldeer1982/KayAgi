---
title: "[ABC248E] K-colinear Line"
layout: "post"
diff: 普及/提高-
pid: AT_abc248_e
tag: []
---

# [ABC248E] K-colinear Line

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc248/tasks/abc248_e

座標平面上の $ N $ 個の点が与えられます。 $ 1\leq\ i\leq\ N $ について、$ i $ 番目の点の座標は $ (X_i,\ Y_i) $ です。

座標平面上の直線であって、$ N $ 個の点のうち $ K $ 個以上の点を通るものの個数を求めてください。  
ただし、そのようなものが無数に存在する場合は `Infinity` を出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ K $ $ X_1 $ $ Y_1 $ $ X_2 $ $ Y_2 $ $ \vdots $ $ X_N $ $ Y_N $

## 输出格式

与えられた $ N $ 個の点のうち $ K $ 個以上の点を通る直線の数を出力せよ。ただし、そのようなものが無数に存在する場合は `Infinity` を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 300 $
- $ \lvert\ X_i\ \rvert,\ \lvert\ Y_i\ \rvert\ \leq\ 10^9 $
- $ i\neq\ j $ ならば $ X_i\neq\ X_j $ または $ Y_i\neq\ Y_j $
- 入力はすべて整数

### Sample Explanation 1

$ x=0 $, $ y=0 $, $ y=x\pm\ 1 $, $ y=-x\pm\ 1 $ の $ 6 $ 本の直線が条件をみたします。 例えば、$ x=0 $ は、$ 1 $, $ 3 $, $ 5 $ 番目の $ 3 $ 個の点を通ります。 よって、$ 6 $ を出力します。

### Sample Explanation 2

原点を通る直線は無数に存在します。 よって、`Infinity` を出力します。

## 样例 #1

### 输入

```
5 2
0 0
1 0
0 1
-1 0
0 -1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
1 1
0 0
```

### 输出

```
Infinity
```

