---
title: "最頻値 (Mode)"
layout: "post"
diff: 难度0
pid: AT_joi2020_yo1b_c
tag: []
---

# 最頻値 (Mode)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2020yo1b/tasks/joi2020_yo1b_c

長さ $ N $ の数列 $ A_1,\ A_2,\ \ldots,\ A_N $ が与えられる． この数列の各項は $ 1 $ 以上 $ M $ 以下の整数である．

長さ $ M $ の新たな数列 $ B_1,\ B_2,\ \ldots,\ B_M $ を以下のように定義する．

- 各 $ j $ ($ 1\ \leqq\ j\ \leqq\ M $) に対して，$ B_j $ の値は $ A_i\ =\ j $ を満たす整数 $ i $ ($ 1\ \leqq\ i\ \leqq\ N $) の個数に等しい．

$ B_1,\ B_2,\ \ldots,\ B_M $ の最大値を求めよ．

## 输入格式

入力は以下の形式で標準入力から与えられる．

> $ N $ $ M $ $ A_1 $ $ A_2 $ $ \cdots $ $ A_N $

## 输出格式

$ B_1,\ B_2,\ \ldots,\ B_M $ の最大値を $ 1 $ 行で出力せよ．

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ \leqq\ 100 $．
- $ 1\ \leqq\ M\ \leqq\ 100 $．
- $ 1\ \leqq\ A_i\ \leqq\ M $ ($ 1\ \leqq\ i\ \leqq\ N $)．

### Sample Explanation 1

数列 $ B_1,\ B_2,\ B_3 $ は $ 2,\ 1,\ 1 $ となり，これらの最大値は $ 2 $ である．

## 样例 #1

### 输入

```
4 3
1 1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6 5
3 3 2 1 2 3
```

### 输出

```
3
```

