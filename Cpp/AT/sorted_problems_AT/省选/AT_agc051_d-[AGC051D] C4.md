---
title: "[AGC051D] C4"
layout: "post"
diff: 省选/NOI-
pid: AT_agc051_d
tag: ['矩阵树定理', '欧拉回路']
---

# [AGC051D] C4

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc051/tasks/agc051_d

以下の無向グラフにおいて、$ S $ から $ S $ へのウォークであって辺 $ ST $, $ TU $, $ UV $, $ VS $ をそれぞれ $ a $, $ b $, $ c $, $ d $ 回通るもの (向きは不問) の数を $ 998,244,353 $ で割った余りを求めてください。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc051_d/648da6e8de7f6ac243febb92657c094616c7b1d5.png)

## 输入格式

入力は標準入力から以下の形式で与えられる。

> $ a $ $ b $ $ c $ $ d $

## 输出格式

答えを出力せよ。

## 说明/提示

### 注記

$ S $ から $ S $ へのウォークとは、頂点の列 $ v_0\ =\ S,\ v_1,\ \ldots,\ v_k\ =\ S $ であって、各 $ i\ (0\ \leq\ i\ <\ k) $ について $ v_i $ と $ v_{i+1} $ を結ぶ辺があるものをいいます。 $ 2 $ つのウォークは、列として異なるときに異なるとみなされます。

### 制約

- $ 1\ \leq\ a,\ b,\ c,\ d\ \leq\ 500,000 $
- 入力中の全ての値は整数である。

### Sample Explanation 1

条件を満たすウォークは $ 10 $ 個あり、その一例は $ S $ $ \rightarrow $ $ T $ $ \rightarrow $ $ U $ $ \rightarrow $ $ V $ $ \rightarrow $ $ U $ $ \rightarrow $ $ T $ $ \rightarrow $ $ S $ $ \rightarrow $ $ V $ $ \rightarrow $ $ S $ です。

## 样例 #1

### 输入

```
2 2 2 2
```

### 输出

```
10
```

## 样例 #2

### 输入

```
1 2 3 4
```

### 输出

```
0
```

## 样例 #3

### 输入

```
470000 480000 490000 500000
```

### 输出

```
712808431
```

