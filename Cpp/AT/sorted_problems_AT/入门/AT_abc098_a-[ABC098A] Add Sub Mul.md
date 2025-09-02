---
title: "[ABC098A] Add Sub Mul"
layout: "post"
diff: 入门
pid: AT_abc098_a
tag: []
---

# [ABC098A] Add Sub Mul

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc098/tasks/abc098_a

$ 2 $ つの整数 $ A $, $ B $ が与えられます。 $ A+B $, $ A-B $, $ A\ \times\ B $ の中で最大の値を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A $ $ B $

## 输出格式

$ A+B $, $ A-B $, $ A\ \times\ B $ の中で最大の値を出力せよ。

## 说明/提示

### 制約

- $ -1000\ \leq\ A,B\ \leq\ 1000 $
- 入力はすべて整数である

### Sample Explanation 1

$ 3+1=4 $, $ 3-1=2 $, $ 3\ \times\ 1=3 $ なので、この中で最大の値である $ 4 $ が答えになります。

### Sample Explanation 2

$ 4\ -\ (-2)\ =\ 6 $ が最大の値になります。

## 样例 #1

### 输入

```
3 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 -2
```

### 输出

```
6
```

## 样例 #3

### 输入

```
0 0
```

### 输出

```
0
```

