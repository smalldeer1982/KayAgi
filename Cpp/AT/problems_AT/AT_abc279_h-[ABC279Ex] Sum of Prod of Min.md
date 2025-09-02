---
title: "[ABC279Ex] Sum of Prod of Min"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_abc279_h
tag: []
---

# [ABC279Ex] Sum of Prod of Min

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc279/tasks/abc279_h

正整数 $ N,M $ が与えられます。ただし、$ N\leq\ M\ \leq\ 2N $ が保証されます。

$ \displaystyle\ \sum_{i=1}^{N}\ S_i\ =\ M $ を満たす全ての正整数列 $ S=(S_1,S_2,\dots,S_N) $ について以下の値を求め、 その総和を素数 $ 200\ 003 $ で割った余りを出力してください (通常とは異なる $ \bmod $ の値に注意してください)。

- $ \displaystyle\ \prod_{k=1}^{N}\ \min(k,S_k) $

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $

## 输出格式

答えを整数として出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{12} $
- $ N\ \leq\ M\ \leq\ 2N $
- 入力は全て整数

### Sample Explanation 1

条件を満たす $ S $ は、 $ S=(1,1,3),\ S=(1,2,2),\ S=(1,3,1),\ S=(2,1,2),\ S=(2,2,1),\ S=(3,1,1) $ の $ 6 $ つです。 それぞれの $ S $ について $ \displaystyle\ \prod_{k=1}^{N}\ \min(k,S_k) $ の値を求めると、 - $ S=(1,1,3) $ : $ 1\times\ 1\ \times\ 3\ =\ 3 $ - $ S=(1,2,2) $ : $ 1\times\ 2\ \times\ 2\ =\ 4 $ - $ S=(1,3,1) $ : $ 1\times\ 2\ \times\ 1\ =\ 2 $ - $ S=(2,1,2) $ : $ 1\times\ 1\ \times\ 2\ =\ 2 $ - $ S=(2,2,1) $ : $ 1\times\ 2\ \times\ 1\ =\ 2 $ - $ S=(3,1,1) $ : $ 1\times\ 1\ \times\ 1\ =\ 1 $ となるため、その総和である $ 14 $ を出力します。

### Sample Explanation 2

総和を $ 200\ 003 $ で割った余りを出力してください。

## 样例 #1

### 输入

```
3 5
```

### 输出

```
14
```

## 样例 #2

### 输入

```
1126 2022
```

### 输出

```
40166
```

## 样例 #3

### 输入

```
1000000000000 1500000000000
```

### 输出

```
180030
```

