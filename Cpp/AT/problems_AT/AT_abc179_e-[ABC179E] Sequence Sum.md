---
title: "[ABC179E] Sequence Sum"
layout: "post"
diff: 普及/提高-
pid: AT_abc179_e
tag: []
---

# [ABC179E] Sequence Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc179/tasks/abc179_e

$ x $ を $ m $ で割った余りを $ f(x,m) $ と表します。

初期値 $ A_1=X $ および漸化式 $ A_{n+1}=\ f(A_n^2,\ M) $ で定まる数列を $ A $ とします。$ \displaystyle{\sum_{i=1}^N\ A_i} $ を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ X $ $ M $

## 输出格式

$ \displaystyle{\sum_{i=1}^N\ A_i} $ を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{10} $
- $ 0\ \leq\ X\ <\ M\ \leq\ 10^5 $
- 入力は全て整数

### Sample Explanation 1

数列 $ A $ は $ 2,4,16,256,471,620,\ldots $ となるので、答えは $ 2+4+16+256+471+620=1369 $ となります。

### Sample Explanation 2

数列 $ A $ は $ 2,4,0,0,\ldots $ となるので、答えは $ 6 $ となります。

## 样例 #1

### 输入

```
6 2 1001
```

### 输出

```
1369
```

## 样例 #2

### 输入

```
1000 2 16
```

### 输出

```
6
```

## 样例 #3

### 输入

```
10000000000 10 99959
```

### 输出

```
492443256176507
```

