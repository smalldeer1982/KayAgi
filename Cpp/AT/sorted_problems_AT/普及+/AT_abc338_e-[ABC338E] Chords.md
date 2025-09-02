---
title: "[ABC338E] Chords"
layout: "post"
diff: 普及+/提高
pid: AT_abc338_e
tag: ['栈', 'ST 表']
---

# [ABC338E] Chords

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc338/tasks/abc338_e

円周上に $ 2N $ 個の点が等間隔に並んでおり、ある点から始めて時計回りに $ 1 $ から $ 2N $ までの番号が付けられています。

円周上にはさらに $ N $ 個の弦があり、$ i $ 個目の弦は点 $ A_i $ と点 $ B_i $ を結んでいます。 ここで、$ A_1,\dots,A_N,B_1,\dots,B_N $ は全て相異なることが保証されます。

弦どうしの交点が存在するかどうか判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ B_1 $ $ A_2 $ $ B_2 $ $ \vdots $ $ A_N $ $ B_N $

## 输出格式

弦どうしの交点が存在するならば `Yes` を、存在しないならば `No` を出力せよ。

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i,B_i\ \leq\ 2N $
- $ A_1,\dots,A_N,B_1,\dots,B_N $ は全て相異なる
- 入力は全て整数

### Sample Explanation 1

!\[\](https://img.atcoder.jp/abc338/de1d9dd6cf38caec1c69fe035bdba545.png) 図のように、弦 $ 1 $（点 $ 1 $ と点 $ 3 $ を結ぶ線分）と弦 $ 2 $（点 $ 4 $ と点 $ 2 $ を結ぶ線分）が交点を持つので、`Yes` を出力します。

### Sample Explanation 2

!\[\](https://img.atcoder.jp/abc338/1b3b982c8d6ca59f00ca0edd218fb9c4.png) 図のように、弦どうしの交点は存在しないので、`No` を出力します。

## 样例 #1

### 输入

```
3
1 3
4 2
5 6
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3
6 1
4 3
2 5
```

### 输出

```
No
```

## 样例 #3

### 输入

```
4
2 4
3 7
8 6
5 1
```

### 输出

```
Yes
```

