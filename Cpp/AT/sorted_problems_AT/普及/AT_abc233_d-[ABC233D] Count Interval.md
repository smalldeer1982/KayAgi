---
title: "[ABC233D] Count Interval"
layout: "post"
diff: 普及/提高-
pid: AT_abc233_d
tag: []
---

# [ABC233D] Count Interval

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc233/tasks/abc233_d

長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $ と、整数 $ K $ が与えられます。

$ A $ の連続部分列のうち、要素の和が $ K $ になるものはいくつありますか？  
 すなわち、以下の条件を全て満たす整数の組 $ (l,r) $ はいくつありますか？

- $ 1\leq\ l\leq\ r\leq\ N $
- $ \displaystyle\sum_{i=l}^{r}A_i\ =\ K $

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ K $ $ A_1 $ $ A_2 $ $ \ldots $ $ A_N $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ |A_i|\ \leq\ 10^9 $
- $ |K|\ \leq\ 10^{15} $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ (l,r)=(1,2),(3,3),(2,6) $ の $ 3 $ 組が条件を満たします。

### Sample Explanation 2

条件を満たす $ (l,r) $ の組が $ 1 $ つも存在しないこともあります。

## 样例 #1

### 输入

```
6 5
8 -3 5 7 0 -4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 -1000000000000000
1000000000 -1000000000
```

### 输出

```
0
```

