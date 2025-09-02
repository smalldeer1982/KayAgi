---
title: "[ABC300G] P-smooth number"
layout: "post"
diff: 提高+/省选-
pid: AT_abc300_g
tag: []
---

# [ABC300G] P-smooth number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc300/tasks/abc300_g

$ k $ 以下の素数のみを素因数に持つ正整数を $ k $-smooth number と呼びます。  
 整数 $ N $ および $ 100 $ 以下の素数 $ P $ が与えられるので、 $ N $ 以下の $ P $-smooth number の個数を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ P $

## 输出格式

答えを整数として出力せよ。

## 说明/提示

### 制約

- $ N $ は $ 1\ \le\ N\ \le\ 10^{16} $ を満たす整数
- $ P $ は $ 2\ \le\ P\ \le\ 100 $ を満たす素数
 
### Sample Explanation 1

$ 36 $ 以下の $ 3 $-smooth number は $ 1,2,3,4,6,8,9,12,16,18,24,27,32,36 $ の $ 14 $ 個です。 $ 1 $ は任意の素数 $ k $ に対して $ k $-smooth number であることに注意してください。

## 样例 #1

### 输入

```
36 3
```

### 输出

```
14
```

## 样例 #2

### 输入

```
10000000000000000 97
```

### 输出

```
2345134674
```

