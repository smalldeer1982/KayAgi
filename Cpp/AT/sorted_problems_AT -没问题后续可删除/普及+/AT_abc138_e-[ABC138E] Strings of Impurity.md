---
title: "[ABC138E] Strings of Impurity"
layout: "post"
diff: 普及+/提高
pid: AT_abc138_e
tag: []
---

# [ABC138E] Strings of Impurity

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc138/tasks/abc138_e

英小文字からなる二つの文字列 $ s,\ t $ が与えられます。次の条件を満たす整数 $ i $ $ (1\ \leq\ i\ \leq\ 10^{100}\ \times\ |s|) $ が存在するか判定し、存在する場合はそのような $ i $ の最小値を求めてください。

- $ s $ を $ 10^{100} $ 個連結して得られる文字列を $ s' $ とする。$ t $ は、文字列 $ {s'}_1{s'}_2\ldots{s'}_i $ ($ s' $ の先頭 $ i $ 文字) の部分列である。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ s $ $ t $

## 输出格式

条件を満たす整数 $ i $ が存在する場合はそのような $ i $ の最小値を、存在しない場合は `-1` を出力せよ。

## 说明/提示

### 注記

- 文字列 $ a $ の部分列とは、$ a $ から $ 0 $ 文字以上を削除して残った文字を相対的な順序を保ったまま連結して得られる文字列です。例えば、`contest` の部分列には `net`, `c`, `contest` などがあります。

### 制約

- $ 1\ \leq\ |s|\ \leq\ 10^5 $
- $ 1\ \leq\ |t|\ \leq\ 10^5 $
- $ s,\ t $ は英小文字からなる。

### Sample Explanation 1

$ t\ = $ `son` は文字列 `contestcon` ($ s'\ = $ `contestcontestcontest...` の先頭 $ 10 $ 文字) の部分列であるため、$ i\ =\ 10 $ は条件を満たします。 一方で、$ t $ は文字列 `contestco` ($ s' $ の先頭 $ 9 $ 文字) の部分列ではないため、$ i\ =\ 9 $ は条件を満たしません。 同様に、$ 8 $ 以下の任意の整数も条件を満たしません。よって、条件を満たす整数 $ i $ の最小値は $ 10 $ です。

### Sample Explanation 2

$ t\ = $ `programming` は $ s'\ = $ `contestcontestcontest...` の部分列ではありません。よって、条件を満たす整数 $ i $ は存在しません。

### Sample Explanation 3

ここにそのようなケースを置くことはできませんが、答えは $ 32 $ bit 整数に収まらない可能性があるのでご注意ください。

## 样例 #1

### 输入

```
contest
son
```

### 输出

```
10
```

## 样例 #2

### 输入

```
contest
programming
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
contest
sentence
```

### 输出

```
33
```

