---
title: "[ARC107A] Simple Math"
layout: "post"
diff: 入门
pid: AT_arc107_a
tag: []
---

# [ARC107A] Simple Math

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc107/tasks/arc107_a

$ 3 $ つの正整数 $ A,\ B,\ C $ が与えられます。

$ \sum_{a=1}^{A}\ \sum_{b=1}^{B}\ \sum_{c=1}^{C}\ abc $

を $ 998244353 $ で割った余りを求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A $ $ B $ $ C $

## 输出格式

求めた値を $ 998244353 $ で割った余りを出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ A,\ B,\ C\ \leq\ 10^9 $

### Sample Explanation 1

$ (1\ \times\ 1\ \times\ 1)\ +\ (1\ \times\ 1\ \times\ 2)\ +\ (1\ \times\ 1\ \times\ 3)\ +\ (1\ \times\ 2\ \times\ 1)\ +\ (1\ \times\ 2\ \times\ 2)\ +\ (1\ \times\ 2\ \times\ 3)\ =\ 1\ +\ 2\ +\ 3\ +\ 2\ +\ 4\ +\ 6\ =\ 18 $ となります。

### Sample Explanation 2

$ 998244353 $ で割った余りを求めることに注意してください。

## 样例 #1

### 输入

```
1 2 3
```

### 输出

```
18
```

## 样例 #2

### 输入

```
1000000000 987654321 123456789
```

### 输出

```
951633476
```

