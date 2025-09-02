---
title: "[ABC147A] Blackjack"
layout: "post"
diff: 入门
pid: AT_abc147_a
tag: []
---

# [ABC147A] Blackjack

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc147/tasks/abc147_a

$ 3 $ 個の整数 $ A_1 $, $ A_2 $, $ A_3 $ が与えられます。

$ A_1+A_2+A_3 $ が $ 22 $ 以上なら `bust`、$ 21 $ 以下なら `win` を出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A_1 $ $ A_2 $ $ A_3 $

## 输出格式

$ A_1+A_2+A_3 $ が $ 22 $ 以上なら `bust`、$ 21 $ 以下なら `win` を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ A_i\ \leq\ 13\ (i=1,2,3) $
- 入力中のすべての値は整数である。

### Sample Explanation 1

$ 5+7+9=21 $ なので `win` を出力します。

### Sample Explanation 2

$ 13+7+2=22 $ なので `bust` を出力します。

## 样例 #1

### 输入

```
5 7 9
```

### 输出

```
win
```

## 样例 #2

### 输入

```
13 7 2
```

### 输出

```
bust
```

