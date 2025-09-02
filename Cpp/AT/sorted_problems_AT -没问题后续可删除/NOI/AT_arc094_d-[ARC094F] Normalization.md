---
title: "[ARC094F] Normalization"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_arc094_d
tag: []
---

# [ARC094F] Normalization

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc094/tasks/arc094_d

`a`,`b`,`c` からなる文字列 $ S $ が与えられます。次の操作を $ 0 $ 回以上繰り返して作ることのできる文字列としてありうるものの個数を $ 998244353 $ で割ったあまりを求めてください。

- $ 1\leq\ i\leq\ |S|-1 $ かつ $ S $ の $ i $ 文字目と $ i+1 $ 文字目が異なるような整数 $ i $ を選ぶ。$ S $ の $ i $ 文字目と $ i+1 $ 文字目を両方、(`a`,`b`,`c` のうち)そのどちらとも異なる文字で置き換える。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

操作を繰り返して作ることのできる文字列としてありうるものの個数を $ 998244353 $ で割ったあまりを出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ |S|\ \leq\ 2\ ×\ 10^5 $
- $ S $ は `a`,`b`,`c` からなる

### Sample Explanation 1

`abc`,`aaa`,`ccc` を作ることができます。

## 样例 #1

### 输入

```
abc
```

### 输出

```
3
```

## 样例 #2

### 输入

```
abbac
```

### 输出

```
65
```

## 样例 #3

### 输入

```
babacabac
```

### 输出

```
6310
```

## 样例 #4

### 输入

```
ababacbcacbacacbcbbcbbacbaccacbacbacba
```

### 输出

```
148010497
```

