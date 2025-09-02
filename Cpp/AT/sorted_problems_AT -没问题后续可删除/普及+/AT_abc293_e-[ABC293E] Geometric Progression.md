---
title: "[ABC293E] Geometric Progression"
layout: "post"
diff: 普及+/提高
pid: AT_abc293_e
tag: []
---

# [ABC293E] Geometric Progression

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc293/tasks/abc293_e

整数 $ A,\ X,\ M $ が与えられます。$ \displaystyle\ \sum_{i\ =\ 0}^{X-1}\ A^i $ を $ M $ で割った余りを求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A $ $ X $ $ M $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ A,\ M\ \leq\ 10^9 $
- $ 1\ \leq\ X\ \leq\ 10^{12} $
- 入力はすべて整数

### Sample Explanation 1

$ 3^0\ +\ 3^1\ +\ 3^2\ +\ 3^3\ =\ 40 $ です。$ 40 $ を $ 7 $ で割った余りは $ 5 $ であるため、$ 5 $ を出力します。

## 样例 #1

### 输入

```
3 4 7
```

### 输出

```
5
```

## 样例 #2

### 输入

```
8 10 9
```

### 输出

```
0
```

## 样例 #3

### 输入

```
1000000000 1000000000000 998244353
```

### 输出

```
919667211
```

