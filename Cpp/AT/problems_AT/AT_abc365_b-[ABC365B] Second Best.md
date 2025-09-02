---
title: "[ABC365B] Second Best"
layout: "post"
diff: 入门
pid: AT_abc365_b
tag: ['排序']
---

# [ABC365B] Second Best

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc365/tasks/abc365_b

長さ $ N $ の整数列 $ A=(A_1,\ldots,A_N) $ が与えられます。ここで $ A_1,A_2,\ldots,A_N $ は相異なります。

$ A $ の中で二番目に大きい要素は $ A $ の何番目の要素でしょうか。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ \ldots $ $ A_{N} $

## 输出格式

$ A $ の中で二番目に大きい要素が $ A $ の $ X $ 番目であるとき、$ X $ を整数として出力せよ。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 100 $
- $ 1\leq\ A_i\ \leq\ 10^9 $
- $ A_1,A_2,\ldots,A_N $ は相異なる
- 入力される数値は全て整数
 
### Sample Explanation 1

$ A $ の中で二番目に大きい要素は $ A_3 $ なので $ 3 $ を出力してください。

## 样例 #1

### 输入

```
4
8 2 5 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
8
1 2 3 4 5 10 9 11
```

### 输出

```
6
```

