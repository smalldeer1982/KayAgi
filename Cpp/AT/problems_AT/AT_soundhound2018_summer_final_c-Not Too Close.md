---
title: "Not Too Close"
layout: "post"
diff: 提高+/省选-
pid: AT_soundhound2018_summer_final_c
tag: ['动态规划 DP', '组合数学']
---

# Not Too Close

## 题目描述

[problemUrl]: https://atcoder.jp/contests/soundhound2018-summer-final/tasks/soundhound2018_summer_final_c

$ N $ 頂点の無向グラフであって、以下の条件をすべて満たすものの個数を $ 10^9\ +\ 7 $ で割った余りを求めてください。

- $ N $ 個の頂点には $ 1 $ から $ N $ までの番号が振られている。
- グラフは自己辺や多重辺を持たない（連結である必要はない）。
- すべての辺の長さを $ 1 $ とすると、頂点 $ 1,\ 2 $ 間の最短距離は $ D $ である。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ D $

## 输出格式

条件をすべて満たすグラフの個数を $ 10^9\ +\ 7 $ で割った余りを出力せよ。

## 说明/提示

### 注記

二つのグラフ $ G_1,\ G_2 $ は、以下が満たされる場合に異なるとみなされ、満たされない場合に同一とみなされます。

- ある整数の組 $ (i,\ j) $ $ (1\ <\ =\ i\ <\ j\ <\ =\ N) $ が存在し、頂点 $ i,\ j $ を直接結ぶ辺が $ G_1,\ G_2 $ のうち一方のみに存在する。

### 制約

- $ 1\ <\ =\ D\ <\ N\ <\ =\ 30 $
- $ N,\ D $ は整数である。

### Sample Explanation 1

条件を満たすグラフは下図の $ 2 $ 通りです。 !\[\](https://img.atcoder.jp/soundhound2018-summer-final/4b0c83895d12c1a9c90cb3e8060db969.png)

### Sample Explanation 2

条件を満たすグラフは下図の $ 14 $ 通りです。 !\[\](https://img.atcoder.jp/soundhound2018-summer-final/df4dffb7f2140b22a6c7ccc86f6c9cf9.png)

### Sample Explanation 3

mod $ (10^9\ +\ 7) $ にご注意ください。

## 样例 #1

### 输入

```
4 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
14
```

## 样例 #3

### 输入

```
30 15
```

### 输出

```
313862829
```

