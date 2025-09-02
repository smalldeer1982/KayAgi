---
title: "Count Triplets"
layout: "post"
diff: 难度0
pid: AT_nikkei2019_2_final_a
tag: []
---

# Count Triplets

## 题目描述

[problemUrl]: https://atcoder.jp/contests/nikkei2019-2-final/tasks/nikkei2019_2_final_a

高橋君は $ A_1,\ A_2,\ \cdots,\ A_N $ の $ N $ 要素からなる整数列 $ A $ を持っています。

$ A_i\ <\ A_j\ >\ A_k $ を満たす $ (i,\ j,\ k)\ (1\ \leq\ i\ <\ j\ <\ k\ \leq\ N) $ の組の個数を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ \cdots $ $ A_N $

## 输出格式

$ A_i\ <\ A_j\ >\ A_k $ を満たす $ (i,\ j,\ k)\ (1\ \leq\ i\ <\ j\ <\ k\ \leq\ N) $ の組の個数を出力せよ。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 5000 $
- $ 0\ \leq\ A_i\ \leq\ 10^9 $
- 入力は全て整数である

### Sample Explanation 1

条件を満たす組は $ (i,\ j,\ k)\ =\ (1,\ 3,\ 4),\ (2,\ 3,\ 4) $ の $ 2 $ つがあります。

### Sample Explanation 2

$ A_i\ <\ A_j\ >\ A_k $ を満たす $ (i,\ j,\ k) $ の組はありません。

## 样例 #1

### 输入

```
4
1 2 3 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
2 2 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
10
0 7 7 6 9 8 1 3 2 0
```

### 输出

```
57
```

