---
title: "[ARC162F] Montage"
layout: "post"
diff: 省选/NOI-
pid: AT_arc162_f
tag: ['动态规划 DP', '动态规划优化', '前缀和']
---

# [ARC162F] Montage

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc162/tasks/arc162_f

正整数 $ N,\ M $ が与えられます。各要素が $ 0 $ または $ 1 $ である $ N $ 行 $ M $ 列の行列 $ A $ は全部で $ 2^{NM} $ 個存在しますが、そのうち以下の条件を満たすものの個数を $ 998244353 $ で割ったあまりを求めてください。

- $ 1\ \leq\ a\ <\ c\ \leq\ N $ かつ $ 1\ \leq\ b\ <\ d\ \leq\ M $ を満たす全ての整数の組 $ (a,\ b,\ c,\ d) $ について、$ A_{a,\ b}\ \times\ A_{c,\ d}\ \leq\ A_{a,\ d}\ \times\ A_{c,\ b} $ が成り立つ。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $

## 输出格式

答えを $ 1 $ 行に出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ M\ \leq\ 400 $
- 入力される数値は全て整数
 
### Sample Explanation 1

条件は $ A_{1,1}\ \times\ A_{2,2}\ \leq\ A_{1,2}\ \times\ A_{2,1} $ です。$ \begin{pmatrix}\ 1\ &amp;\ 0\ \\ 0\ &amp;\ 1\ \end{pmatrix},\ \begin{pmatrix}\ 1\ &amp;\ 1\ \\ 0\ &amp;\ 1\ \end{pmatrix},\ \begin{pmatrix}\ 1\ &amp;\ 0\ \\ 1\ &amp;\ 1\ \end{pmatrix} $ 以外の $ 13 $ 個が条件を満たします。

### Sample Explanation 2

$ 2^{NM} $ 個すべての行列が条件を満たすので、$ 2^{30} $ を $ 998244353 $ で割ったあまりである $ 75497471 $ を出力します。

## 样例 #1

### 输入

```
2 2
```

### 输出

```
13
```

## 样例 #2

### 输入

```
1 30
```

### 输出

```
75497471
```

## 样例 #3

### 输入

```
400 400
```

### 输出

```
412670892
```

