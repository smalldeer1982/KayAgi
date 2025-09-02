---
title: "文字列の反転 (Inversion of a String)"
layout: "post"
diff: 难度0
pid: AT_joi2020_yo1b_b
tag: []
---

# 文字列の反転 (Inversion of a String)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2020yo1b/tasks/joi2020_yo1b_b

長さ $ N $ の文字列 $ S $ が与えられる．

$ S $ の $ A $ 文字目から $ B $ 文字目までの文字の並びを逆にし，それ以外の文字はそのままにしたとき，どのような文字列ができるだろうか．ただし，$ S $ の先頭の文字が $ 1 $ 文字目，末尾の文字が $ N $ 文字目である．

文字列 $ S $ と，$ 2 $ つの整数 $ A,\ B $ が与えられたとき，$ S $ のうち $ A $ 文字目から $ B $ 文字目までの文字の並びを逆にしてできる文字列を出力するプログラムを作成せよ．

## 输入格式

入力は以下の形式で標準入力から与えられる．

> $ N $ $ A $ $ B $ $ S $

## 输出格式

$ S $ のうち $ A $ 文字目から $ B $ 文字目までの文字の並びを逆にしてできる文字列を $ 1 $ 行で出力せよ．

## 说明/提示

### 制約

- $ 1\ \leqq\ A\ \leqq\ B\ \leqq\ N\ \leqq\ 200 $．
- $ S $ は長さ $ N $ の文字列である．
- $ S $ の各文字は英大文字または英小文字である．

### Sample Explanation 2

$ A\ =\ B $ かもしれない．

## 样例 #1

### 输入

```
10 3 7
JOIjoiJoIj
```

### 输出

```
JOJiojIoIj
```

## 样例 #2

### 输入

```
9 6 6
abcdefghi
```

### 输出

```
abcdefghi
```

