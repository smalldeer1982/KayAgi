---
title: "[ABC061A] Between Two Integers"
layout: "post"
diff: 入门
pid: AT_abc061_a
tag: []
---

# [ABC061A] Between Two Integers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc061/tasks/abc061_a

$ 3 $ つの整数 $ A,B,C $ が与えられます。  
 整数 $ C $ が $ A $ 以上 かつ $ B $ 以下であるかを判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A $ $ B $ $ C $

## 输出格式

条件を満たす場合は`Yes`、そうでない場合は`No`を出力せよ。

## 说明/提示

### 制約

- $ -100≦A,B,C≦100 $
- $ A,B,C $ は全て整数

### Sample Explanation 1

整数 $ C=2 $ は $ A=1 $ 以上 かつ、$ B=3 $ 以下 であるため`Yes`と出力します。

### Sample Explanation 2

整数 $ C=4 $ は $ A=6 $ 以上ではないため`No`と出力します。

## 样例 #1

### 输入

```
1 3 2
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
6 5 4
```

### 输出

```
No
```

## 样例 #3

### 输入

```
2 2 2
```

### 输出

```
Yes
```

