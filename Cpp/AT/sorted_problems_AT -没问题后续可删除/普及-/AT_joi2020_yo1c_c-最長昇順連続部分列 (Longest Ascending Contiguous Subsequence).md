---
title: "最長昇順連続部分列 (Longest Ascending Contiguous Subsequence)"
layout: "post"
diff: 普及-
pid: AT_joi2020_yo1c_c
tag: []
---

# 最長昇順連続部分列 (Longest Ascending Contiguous Subsequence)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2020yo1c/tasks/joi2020_yo1c_c

長さ $ N $ の正整数列 $ A=(A_1,\ A_2,\ \ldots,\ A_N) $ が与えられる．正整数列 $ A $ の連続部分列の中で昇順に並んでいるもののうち，最長のものの長さを求めよ．

すなわち，$ A_l\ \leqq\ A_{l+1}\ \leqq\ \cdots\ \leqq\ A_r $ を満たすような $ 2 $ つの整数 $ l,\ r $ ( $ 1\ \leqq\ l\ \leqq\ r\ \leqq\ N $ ) について，$ r-l+1 $ の最大値を求めよ．

## 输入格式

入力は以下の形式で標準入力から与えられる．

> $ N $ $ A_1 $ $ A_2 $ $ \cdots $ $ A_N $

## 输出格式

正整数列 $ A $ の連続部分列の中で昇順に並んでいるもののうち，最長のものの長さを $ 1 $ 行で出力せよ．

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ \leqq\ 100 $．
- $ 1\ \leqq\ A_i\ \leqq\ 2020 $ ($ 1\ \leqq\ i\ \leqq\ N $)．

### Sample Explanation 1

正整数列 $ A $ の $ 4 $ 項目から $ 6 $ 項目までに対応する連続部分列は $ 1,\ 5,\ 9 $ であり，これは昇順である．これより長い昇順な連続部分列は存在しない．

### Sample Explanation 2

正整数列 $ A $ の $ 5 $ 項目から $ 6 $ 項目までに対応する連続部分列は $ 5,\ 5 $ であり，これは昇順である．これより長い昇順な連続部分列は存在しない．

## 样例 #1

### 输入

```
10
3 1 4 1 5 9 2 6 5 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10
9 8 7 6 5 5 4 3 2 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
9
1 2 2 12 120 210 202 1010 2020
```

### 输出

```
6
```

