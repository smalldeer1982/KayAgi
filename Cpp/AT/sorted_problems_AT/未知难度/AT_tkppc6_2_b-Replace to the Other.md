---
title: "Replace to the Other"
layout: "post"
diff: 难度0
pid: AT_tkppc6_2_b
tag: []
---

# Replace to the Other

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tkppc6-2/tasks/tkppc6_2_b

`A`, `B` のみからなる長さ $ N $ の文字列 $ S $, $ T $ が与えられます。以下の操作を $ 0 $ 回以上繰り返すことで $ S $ を $ T $ に一致させられるかを判定し、可能なら必要な操作回数の最小値を求めてください。

- $ S_i=S_{i+1} $ であるような整数 $ i\ (1\ \leq\ i\ \lt\ N) $ を選び、$ S_i $ と $ S_{i+1} $ を `A`, `B` のうち現在とは異なる文字にそれぞれ置き換える。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S $ $ T $

## 输出格式

問題文中の操作によって $ S $ を $ T $ に一致させられるなら必要な操作回数の最小値を、一致させられないなら `-1` を出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ S $, $ T $ は `A`, `B` のみからなる長さ $ N $ の文字列

### Sample Explanation 1

例えば以下のような手順で操作を行うのが最善です。 - $ i=1 $ として操作を行う。$ S $ は `BBB` となる。 - $ i=2 $ として操作を行う。$ S $ は `BAA` となり、これは $ T $ に一致する。

### Sample Explanation 2

そもそも操作を一回も行うことができず、$ S $ を $ T $ に一致させることはできないため、`-1` を出力します。

### Sample Explanation 3

$ S $ と $ T $ が既に一致しているため、一度も操作を行う必要がありません。 原案: \[NatsubiSogan\](https://atcoder.jp/users/NatsubiSogan)

## 样例 #1

### 输入

```
3
AAB
BAA
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
ABA
AAA
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4
ABAB
ABAB
```

### 输出

```
0
```

