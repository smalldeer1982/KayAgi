---
title: "Distance Pairs"
layout: "post"
diff: 难度0
pid: AT_codefestival_2016_ex_a
tag: []
---

# Distance Pairs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/cf16-exhibition/tasks/codefestival_2016_ex_a

$ N $ 頂点の連結な無向グラフがあり、頂点には $ 1～N $ の番号が付いています。 辺の長さはすべて $ 1 $ です。 各 $ i\ (1≦i≦N) $ について、頂点 $ 1 $ と頂点 $ i $ の距離が $ A_i $、頂点 $ 2 $ と頂点 $ i $ の距離が $ B_i $ であることが分かっています。 このようなグラフが存在するかを判定してください。また、存在する場合は、辺の本数として考えられる最小値を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ B_1 $ $ A_2 $ $ B_2 $ : $ A_N $ $ B_N $

## 输出格式

条件を満たすグラフが存在する場合は辺の本数の最小値を、存在しない場合は `-1` を出力せよ。

## 说明/提示

### 制約

- $ 2≦N≦10^5 $
- $ 0≦A_i,B_i≦N-1 $

### Sample Explanation 1

下図のような $ 2 $ 種類のグラフが考えられますが、右のグラフの方が辺の本数が少ないです。 !\[\](https://atcoder.jp/img/code-festival-2016-final/dd1e04d837fd7fc1be56b231cd8c2a17.png)

### Sample Explanation 2

このようなグラフは存在しません。

## 样例 #1

### 输入

```
4
0 1
1 0
1 1
2 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
0 1
1 0
2 2
```

### 输出

```
-1
```

