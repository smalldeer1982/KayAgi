---
title: "[ABC326B] 326-like Numbers"
layout: "post"
diff: 入门
pid: AT_abc326_b
tag: []
---

# [ABC326B] 326-like Numbers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc326/tasks/abc326_b

$ 3 $ 桁の正整数であって、百の位の数と十の位の数の積が一の位の数と等しいものを **326-like number** と呼びます。

例えば $ 326,400,144 $ は 326-like number であり、$ 623,777,429 $ は 326-like number ではありません。

整数 $ N $ が与えられるので、$ N $ 以上の最小の 326-like number を求めてください。なお、制約の条件下で答えは必ず存在します。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 100\ \leq\ N\ \leq\ 919 $
- $ N $ は整数である
 
### Sample Explanation 1

$ 320,321,322,323,324,325 $ は 326-like number ではなく、$ 326 $ は 326-like number です。

### Sample Explanation 2

$ 144 $ は 326-like number です。

## 样例 #1

### 输入

```
320
```

### 输出

```
326
```

## 样例 #2

### 输入

```
144
```

### 输出

```
144
```

## 样例 #3

### 输入

```
516
```

### 输出

```
600
```

