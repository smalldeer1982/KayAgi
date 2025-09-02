---
title: "[ARC141D] Non-divisible Set"
layout: "post"
diff: 省选/NOI-
pid: AT_arc141_d
tag: []
---

# [ARC141D] Non-divisible Set

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc141/tasks/arc141_d

正整数からなる集合 $ S $ について、任意の $ a,\ b\ \in\ S\ (a\neq\ b) $ について $ b $ が $ a $ の倍数でないとき、 $ S $ を「良い集合」と呼びます。

$ N $ 個の $ 1 $ 以上 $ 2M $ 以下の整数からなる集合 $ S=\lbrace\ A_1,\ A_2,\ \dots,\ A_N\rbrace $ が与えられます。

各 $ i=1,\ 2,\ \dots,\ N $ に対し、$ A_i $ を含む $ S $ の部分集合であって、要素数が $ M $ である「良い集合」が存在するか判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられます。

> $ N $ $ M $ $ A_1 $ $ A_2 $ $ \dots $ $ A_{N} $

## 输出格式

$ N $ 行出力してください。 $ i $ 行目には $ A_i $ を含む $ S $ の部分集合であって、要素数が $ M $ である「良い集合」が存在する場合 `Yes` を、存在しない場合 `No` を出力してください。

## 说明/提示

### 制約

- $ M\ \leq\ N\ \leq\ 2M $
- $ 1\ \leq\ M\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ A_1\ <\ A_2\ <\ \dots\ <\ A_N\ \leq\ 2M $
- 入力される値はすべて整数

### Sample Explanation 1

$ A_1=1 $ を含む「良い集合」は明らかに $ \lbrace\ 1\rbrace $ しか存在せず、要素数は $ 1 $ しかないため、$ i=1 $ に対する答えは `No` です。 $ A_2=2 $ を含む「良い集合」としては例えば $ \lbrace\ 2,\ 3,\ 5\rbrace $ が考えられます。このことから $ i=2 $ に対する答えは `Yes` です。

## 样例 #1

### 输入

```
5 3
1 2 3 4 5
```

### 输出

```
No
Yes
Yes
Yes
Yes
```

## 样例 #2

### 输入

```
4 4
2 4 6 8
```

### 输出

```
No
No
No
No
```

## 样例 #3

### 输入

```
13 10
2 3 4 6 7 9 10 11 13 15 17 19 20
```

### 输出

```
No
No
Yes
Yes
Yes
Yes
Yes
Yes
Yes
Yes
Yes
Yes
No
```

