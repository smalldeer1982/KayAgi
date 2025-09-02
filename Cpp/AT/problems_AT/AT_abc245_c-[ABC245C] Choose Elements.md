---
title: "[ABC245C] Choose Elements"
layout: "post"
diff: 普及-
pid: AT_abc245_c
tag: []
---

# [ABC245C] Choose Elements

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc245/tasks/abc245_c

長さ $ N $ の整数からなる数列 $ A=(A_1,\ldots,A_N),B=(B_1,\ldots,B_N) $ が与えられます。

以下の条件を全て満たす長さ $ N $ の数列 $ X=(X_1,\ldots,X_N) $ が存在するかを判定してください。

- すべての $ i(1\leq\ i\leq\ N) $ について、$ X_i\ =\ A_i $ または $ X_i\ =\ B_i $
- すべての $ i(1\leq\ i\leq\ N-1) $ について、$ |X_i\ -\ X_{i+1}|\ \leq\ K $

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ K $ $ A_1 $ $ \ldots $ $ A_N $ $ B_1 $ $ \ldots $ $ B_N $

## 输出格式

条件を全て満たす $ X $ が存在するならば `Yes` と、存在しないならば `No` と出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0 \leq\ K\ \leq\ 10^9 $
- $ 1\ \leq\ A_i,B_i\ \leq\ 10^9 $
- 入力は全て整数である

### Sample Explanation 1

$ X=(9,6,3,7,5) $ が全ての条件を満たします。

### Sample Explanation 2

条件を満たす $ X $ は存在しません。

## 样例 #1

### 输入

```
5 4
9 8 3 7 2
1 6 2 9 5
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
4 90
1 1 1 100
1 2 3 100
```

### 输出

```
No
```

## 样例 #3

### 输入

```
4 1000000000
1 1 1000000000 1000000000
1 1000000000 1 1000000000
```

### 输出

```
Yes
```

