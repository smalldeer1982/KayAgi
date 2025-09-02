---
title: "[AGC037A] Dividing a String"
layout: "post"
diff: 普及-
pid: AT_agc037_a
tag: ['贪心']
---

# [AGC037A] Dividing a String

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc037/tasks/agc037_a

英小文字からなる文字列 $ S $ が与えられます。以下の条件をみたす最大の正整数 $ K $ を求めてください。

- $ S $ の空でない $ K $ 個の文字列への分割 $ S=S_1S_2...S_K $ であって $ S_i\ \neq\ S_{i+1} $ ($ 1\ ≦\ i\ ≦\ K-1 $) を満たすものが存在する。

ただし、$ S_1,S_2,...,S_K $ をこの順に連結して得られる文字列のことを $ S_1S_2...S_K $ によって表しています。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

条件をみたす最大の正整数 $ K $ を出力せよ。

## 说明/提示

### 制約

- $ 1\ ≦\ |S|\ ≦\ 2\ \times\ 10^5 $
- $ S $ は英小文字からなる

### Sample Explanation 1

例えば `aa`,`b`,`ba`,`a` と $ S $ を $ 4 $ つの文字列に分割することができます。

## 样例 #1

### 输入

```
aabbaa
```

### 输出

```
4
```

## 样例 #2

### 输入

```
aaaccacabaababc
```

### 输出

```
12
```

