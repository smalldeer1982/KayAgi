---
title: "Banned Palindromes"
layout: "post"
diff: 难度0
pid: AT_pakencamp_2021_day2_e
tag: []
---

# Banned Palindromes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/pakencamp-2021-day2/tasks/pakencamp_2021_day2_e

正整数 $ N,M $ が与えられます。すべての要素が $ 1 $ 以上 $ M $ 以下である長さ $ N $ の正整数列 $ a $ であって、以下の条件を満たすものの個数を $ 998244353 $ で割った余りを求めてください。

- $ a $ の長さ $ 2 $ 以上の連続部分列であって、回文であるようなものが存在しない。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 10^{12} $
- $ 1\ \le\ M\ \le\ 10^{12} $
- 入力は全て整数

### Sample Explanation 1

$ a=(1,2),(2,1) $ の時条件を満たします。

### Sample Explanation 3

$ 998244353 $ で割った余りを求めることをお忘れなく。 原案: \[turtle0123\\\_\\\_\](https://atcoder.jp/users/turtle0123\_\_)

## 样例 #1

### 输入

```
2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 3
```

### 输出

```
6
```

## 样例 #3

### 输入

```
314 159
```

### 输出

```
809839613
```

