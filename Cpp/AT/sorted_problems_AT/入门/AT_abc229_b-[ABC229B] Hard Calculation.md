---
title: "[ABC229B] Hard Calculation"
layout: "post"
diff: 入门
pid: AT_abc229_b
tag: []
---

# [ABC229B] Hard Calculation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc229/tasks/abc229_b

正整数 $ A,B $ が与えられます。  
 $ A+B $ を(十進法で)計算する時、繰り上がりが生じないなら `Easy` 、生じるなら `Hard` と出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A $ $ B $

## 输出格式

繰り上がりが生じないなら `Easy` 、生じるなら `Hard` と出力せよ。

## 说明/提示

### 制約

- $ A,B $ は整数
- $ 1\ \le\ A,B\ \le\ 10^{18} $

### Sample Explanation 1

$ 229+390 $ を計算する際、十の位から百の位へと繰り上がりが発生します。よって、答えは `Hard` です。

### Sample Explanation 2

繰り上がりは発生しません。答えは `Easy` です。 また、入力が $ 32 $bit 整数に収まらないこともあります。

## 样例 #1

### 输入

```
229 390
```

### 输出

```
Hard
```

## 样例 #2

### 输入

```
123456789 9876543210
```

### 输出

```
Easy
```

