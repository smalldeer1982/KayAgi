---
title: "[ABC227E] Swap"
layout: "post"
diff: 提高+/省选-
pid: AT_abc227_e
tag: []
---

# [ABC227E] Swap

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc227/tasks/abc227_e

`K`, `E`, `Y` のみからなる文字列 $ S $ が与えられます。

$ S $ の隣接する $ 2 $ 文字を入れ替える操作を $ K $ 回まで行えるとき、作ることができる文字列は何種類ありますか？

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $ $ K $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ |S|\ \leq\ 30 $
- $ 0\ \leq\ K\ \leq\ 10^9 $
- $ S $ は `K`, `E`, `Y` のみからなる

### Sample Explanation 1

`KEY` に対して $ 1 $ 回以下の操作を行うことで得られる文字列は `KEY`, `EKY`, `KYE` の $ 3 $ 種類です。

### Sample Explanation 2

`KKEE` に対して $ 2 $ 回以下の操作を行うことで得られる文字列は `KKEE`, `KEKE`, `EKKE`, `KEEK` の $ 4 $ 種類です。

## 样例 #1

### 输入

```
KEY
1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
KKEE
2
```

### 输出

```
4
```

## 样例 #3

### 输入

```
KKEEYY
1000000000
```

### 输出

```
90
```

