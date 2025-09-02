---
title: "[ABC245Ex] Product Modulo 2"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_abc245_h
tag: []
---

# [ABC245Ex] Product Modulo 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc245/tasks/abc245_h

長さ $ K $ の整数からなる数列 $ A=(A_1,\ldots,A_K) $ のうち、以下の条件を全て満たすものは何通りありますか？  
 $ 998244353 $ で割った余りを求めてください。

- すべての $ i(1\leq\ i\leq\ K) $ について、$ 0\leq\ A_i\ \leq\ M-1 $
- $ \displaystyle\prod_{i=1}^{K}\ A_i\ \equiv\ N\ \pmod\ M $

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ K $ $ N $ $ M $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ 10^9 $
- $ 0\ \leq\ N\ \lt\ M\ \leq\ 10^{12} $
- 入力は全て整数である

### Sample Explanation 1

条件を満たす $ A $ は、$ (1,3),(3,1),(3,3),(3,5),(5,3) $ の $ 5 $ つです。

### Sample Explanation 3

$ 998244353 $ で割った余りを求めてください。

## 样例 #1

### 输入

```
2 3 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
10 0 2
```

### 输出

```
1023
```

## 样例 #3

### 输入

```
1000000000 20220326 1000000000000
```

### 输出

```
561382653
```

