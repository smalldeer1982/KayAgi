---
title: "[ABC371E] I Hate Sigma Problems"
layout: "post"
diff: 普及+/提高
pid: AT_abc371_e
tag: ['排列组合']
---

# [ABC371E] I Hate Sigma Problems

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc371/tasks/abc371_e

長さ $ N $ の整数列 $ A=(A_1,A_2,\ldots,A_N) $ が与えられます。また、$ f(l,r) $ を以下で定義します。

- $ (A_l,A_{l+1},\ldots,A_{r-1},A_{r}) $ に含まれる値の種類数
 
次の式の値を求めてください。

 $ \displaystyle\ \sum_{i=1}^{N}\sum_{j=i}^N\ f(i,j) $

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ \ldots $ $ A_N $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\leq\ N $
- 入力される数値は全て整数
 
### Sample Explanation 1

$ f(1,2) $ について考えます。$ (A_1,A_2)=(1,2) $ に含まれる値の種類数は $ 2 $ なので $ f(1,2)=2 $ です。 $ f(2,3) $ について考えます。$ (A_2,A_3)=(2,2) $ に含まれる値の種類数は $ 1 $ なので $ f(2,3)=1 $ です。 $ f $ の総和は $ 8 $ となります。

## 样例 #1

### 输入

```
3
1 2 2
```

### 输出

```
8
```

## 样例 #2

### 输入

```
9
5 4 2 2 3 2 4 4 1
```

### 输出

```
111
```

