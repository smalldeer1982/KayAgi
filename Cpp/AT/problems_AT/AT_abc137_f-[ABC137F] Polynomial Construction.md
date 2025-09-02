---
title: "[ABC137F] Polynomial Construction"
layout: "post"
diff: 省选/NOI-
pid: AT_abc137_f
tag: []
---

# [ABC137F] Polynomial Construction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc137/tasks/abc137_f

素数 $ p $ と、長さ $ p $ の $ 0 $ と $ 1 $ からなる整数列 $ a_0,\ \ldots,\ a_{p-1} $ が与えられます。

以下の条件を満たす $ p-1 $ 次以下の多項式 $ f(x)\ =\ b_{p-1}\ x^{p-1}\ +\ b_{p-2}\ x^{p-2}\ +\ \ldots\ +\ b_0 $ を一つ求めてください。

- 各 $ i $ $ (0\ \leq\ i\ \leq\ p-1) $ に対し、$ b_i $ は $ 0\ \leq\ b_i\ \leq\ p-1 $ なる整数
- 各 $ i $ $ (0\ \leq\ i\ \leq\ p-1) $ に対し、$ f(i)\ \equiv\ a_i\ \pmod\ p $

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ p $ $ a_0 $ $ a_1 $ $ \ldots $ $ a_{p-1} $

## 输出格式

条件を満たす多項式 $ f(x) $ の一つにおける $ b_0,\ b_1,\ \ldots,\ b_{p-1} $ の値をこの順に空白区切りで出力せよ。

なお、解は必ず存在することが示せる。複数の解が存在する場合は、そのうちのどれを出力してもよい。

## 说明/提示

### 制約

- $ 2\ \leq\ p\ \leq\ 2999 $
- $ p $ は素数である。
- $ 0\ \leq\ a_i\ \leq\ 1 $

### Sample Explanation 1

$ f(x)\ =\ x\ +\ 1 $ は以下のように条件を満たします。 - $ f(0)\ =\ 0\ +\ 1\ =\ 1\ \equiv\ 1\ \pmod\ 2 $ - $ f(1)\ =\ 1\ +\ 1\ =\ 2\ \equiv\ 0\ \pmod\ 2 $

### Sample Explanation 2

$ f(x)\ =\ 0 $ も有効な出力です。

## 样例 #1

### 输入

```
2
1 0
```

### 输出

```
1 1
```

## 样例 #2

### 输入

```
3
0 0 0
```

### 输出

```
0 0 0
```

## 样例 #3

### 输入

```
5
0 1 0 1 0
```

### 输出

```
0 2 0 1 3
```

