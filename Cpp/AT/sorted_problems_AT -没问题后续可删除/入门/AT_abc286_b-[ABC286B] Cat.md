---
title: "[ABC286B] Cat"
layout: "post"
diff: 入门
pid: AT_abc286_b
tag: ['模拟']
---

# [ABC286B] Cat

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc286/tasks/abc286_b

長さ $ N $ の文字列 $ S $ が与えられます。

$ S $ に連続して含まれる `na` を全て `nya` に置き換えて得られる文字列を答えてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ N $ は $ 1 $ 以上 $ 1000 $ 以下の整数
- $ S $ は英小文字からなる長さ $ N $ の文字列
 
### Sample Explanation 1

`naan` に連続して含まれる `na` を全て `nya` に置き換えて得られる文字列は `nyaan` です。

### Sample Explanation 2

$ S $ に `na` が連続して含まれないこともあります。

## 样例 #1

### 输入

```
4
naan
```

### 输出

```
nyaan
```

## 样例 #2

### 输入

```
4
near
```

### 输出

```
near
```

## 样例 #3

### 输入

```
8
national
```

### 输出

```
nyationyal
```

