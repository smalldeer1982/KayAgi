---
title: "[ABC266G] Yet Another RGB Sequence"
layout: "post"
diff: 提高+/省选-
pid: AT_abc266_g
tag: ['组合数学', '容斥原理']
---

# [ABC266G] Yet Another RGB Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc266/tasks/abc266_g

整数 $ R,G,B,K $ が与えられます。`R`, `G`, `B` からなる文字列 $ S $ であって、以下の条件をすべて満たすものの個数を $ 998244353 $ で割った余りを求めてください。

- $ S $ に含まれる `R`, `G`, `B` の個数はそれぞれ $ R,G,B $ 個である。
- $ S $ に（連続する）部分文字列として含まれる `RG` の個数は $ K $ 個である。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ R $ $ G $ $ B $ $ K $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ R,G,B\leq\ 10^6 $
- $ 0\ \leq\ K\ \leq\ \mathrm{min}(R,G) $
- 入力は全て整数

### Sample Explanation 1

条件を満たす文字列は以下の $ 6 $ 個です。 - `RRGB` - `RGRB` - `RGBR` - `RBRG` - `BRRG` - `BRGR`

### Sample Explanation 2

個数を $ 998244353 $ で割った余りを求めてください。

## 样例 #1

### 输入

```
2 1 1 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
1000000 1000000 1000000 1000000
```

### 输出

```
80957240
```

