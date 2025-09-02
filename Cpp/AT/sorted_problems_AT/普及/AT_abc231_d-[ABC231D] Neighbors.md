---
title: "[ABC231D] Neighbors"
layout: "post"
diff: 普及/提高-
pid: AT_abc231_d
tag: []
---

# [ABC231D] Neighbors

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc231/tasks/abc231_d

$ 1 $ から $ N $ の番号がついた $ N $ 人を横一列に並べる方法のうち、以下の形式の $ M $ 個の条件全てを満たすものが存在するか判定してください。

- 条件：人 $ A_i $ と人 $ B_i $ は隣り合っている

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $ $ A_1 $ $ B_1 $ $ \vdots $ $ A_M $ $ B_M $

## 输出格式

条件を満たす並べ方が存在するなら `Yes`、存在しないなら `No` と出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 10^5 $
- $ 1\leq\ A_i\ <\ B_i\ \leq\ N $
- $ (A_i,B_i) $ は相異なる

### Sample Explanation 1

例えば $ 4,1,3,2 $ の順に並べることで全ての条件を満たすことができます。

### Sample Explanation 2

どのように並べても全ての条件を満たすことはできません。

## 样例 #1

### 输入

```
4 2
1 3
2 3
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
4 3
1 4
2 4
3 4
```

### 输出

```
No
```

