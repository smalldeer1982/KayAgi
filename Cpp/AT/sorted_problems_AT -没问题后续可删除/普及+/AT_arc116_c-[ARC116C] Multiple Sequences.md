---
title: "[ARC116C] Multiple Sequences"
layout: "post"
diff: 普及+/提高
pid: AT_arc116_c
tag: []
---

# [ARC116C] Multiple Sequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc116/tasks/arc116_c

整数 $ N $ , $ M $ が与えられます。 長さ $ N $ の整数列 $ A $ であって、以下の条件を満たすものの数を答えてください。

- $ 1\ \leq\ A_i\ \leq\ M\ \left(i\ =\ 1,\ 2,\ \ldots,\ N\right) $
- $ A_{i+1} $ は $ A_i $ の倍数 $ \left(i\ =\ 1,\ 2,\ \ldots,\ N\ -\ 1\right) $

ただし、答えは非常に大きくなる場合があるので、 $ 998244353 $ で割った余りを答えてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $

### Sample Explanation 1

条件を満たす数列 $ A $ として、例えば以下のようなものが考えられます。 - $ A\ =\ \left(1,\ 1,\ 4\right) $ - $ A\ =\ \left(3,\ 3,\ 3\right) $ - $ A\ =\ \left(1,\ 2,\ 4\right) $

## 样例 #1

### 输入

```
3 4
```

### 输出

```
13
```

## 样例 #2

### 输入

```
20 30
```

### 输出

```
71166
```

## 样例 #3

### 输入

```
200000 200000
```

### 输出

```
835917264
```

