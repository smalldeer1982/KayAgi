---
title: "[ABC256G] Black and White Stones"
layout: "post"
diff: 提高+/省选-
pid: AT_abc256_g
tag: []
---

# [ABC256G] Black and White Stones

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc256/tasks/abc256_g

一辺の長さが整数 $ D $ の正 $ N $ 角形があります。

頂点から始めて、周上に距離 $ 1 $ ごとに黒い石か白い石を置きます。これにより、$ N $ 角形の各辺上に $ D+1 $ 個、全体で $ ND $ 個の石が置かれます。

石の置き方のうち、各辺上にある白い石の個数が等しくなるようなものは何通りありますか？ $ 998244353 $ で割った余りを求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ D $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 10^{12} $
- $ 1\ \leq\ D\ \leq\ 10^4 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

下図の $ 10 $ 通りがあります。 !\[図\](https://img.atcoder.jp/abc256/ba2bebe9d374f281e2b44e36231abae2.png)

### Sample Explanation 2

$ 998244353 $ で割った余りを求めてください。

## 样例 #1

### 输入

```
3 2
```

### 输出

```
10
```

## 样例 #2

### 输入

```
299792458 3141
```

### 输出

```
138897974
```

