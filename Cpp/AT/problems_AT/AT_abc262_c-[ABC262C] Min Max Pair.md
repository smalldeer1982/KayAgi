---
title: "[ABC262C] Min Max Pair"
layout: "post"
diff: 普及-
pid: AT_abc262_c
tag: []
---

# [ABC262C] Min Max Pair

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc262/tasks/abc262_c

$ 1 $ 以上 $ N $ 以下の整数からなる長さ $ N $ の数列 $ a\ =\ (a_1,\ \dots,\ a_N) $ が与えられます。

以下の条件を全て満たす整数 $ i,\ j $ の組の総数を求めてください。

- $ 1\ \leq\ i\ \lt\ j\ \leq\ N $
- $ \min(a_i,\ a_j)\ =\ i $
- $ \max(a_i,\ a_j)\ =\ j $

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ a_1 $ $ \ldots $ $ a_N $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ 1\ \leq\ a_i\ \leq\ N\ \,\ (1\ \leq\ i\ \leq\ N) $
- 入力は全て整数

### Sample Explanation 1

$ (i,\ j)\ =\ (1,\ 4),\ (2,\ 3) $ が条件を満たします。

## 样例 #1

### 输入

```
4
1 3 2 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10
5 8 2 2 1 6 7 2 9 10
```

### 输出

```
8
```

