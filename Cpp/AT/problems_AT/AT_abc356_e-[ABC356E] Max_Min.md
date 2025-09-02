---
title: "[ABC356E] Max/Min"
layout: "post"
diff: 普及/提高-
pid: AT_abc356_e
tag: ['数学', '枚举']
---

# [ABC356E] Max/Min

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc356/tasks/abc356_e

長さ $ N $ の数列 $ A=(A_1,\ldots,A_N) $ が与えられます。

$ \displaystyle\ \sum_{i=1}^{N-1}\sum_{j=i+1}^{N}\left\lfloor\frac{\max(A_i,A_j)}{\min(A_i,A_j)}\right\rfloor $ を求めてください。

ただし、$ \lfloor\ x\ \rfloor $ は $ x $ 以下の最大の整数を表します。例えば、$ \lfloor\ 3.14\ \rfloor=3 $、$ \lfloor\ 2\ \rfloor=2 $ です。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ \ldots $ $ A_N $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^6 $
- 入力は全て整数である
 
### Sample Explanation 1

求める値は $ \left\lfloor\frac{\max(3,1)}{\min(3,1)}\right\rfloor\ +\ \left\lfloor\frac{\max(3,4)}{\min(3,4)}\right\rfloor\ +\ \left\lfloor\frac{\max(1,4)}{\min(1,4)}\right\rfloor\\ =\left\lfloor\frac{3}{1}\right\rfloor\ +\ \left\lfloor\frac{4}{3}\right\rfloor\ +\ \left\lfloor\frac{4}{1}\right\rfloor\\ =3+1+4\\ =8 $ となります。

## 样例 #1

### 输入

```
3
3 1 4
```

### 输出

```
8
```

## 样例 #2

### 输入

```
6
2 7 1 8 2 8
```

### 输出

```
53
```

## 样例 #3

### 输入

```
12
3 31 314 3141 31415 314159 2 27 271 2718 27182 271828
```

### 输出

```
592622
```

