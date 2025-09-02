---
title: "[AGC026E] Synchronized Subsequence"
layout: "post"
diff: 省选/NOI-
pid: AT_agc026_e
tag: []
---

# [AGC026E] Synchronized Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc026/tasks/agc026_e

$ N $ 個の `a` と $ N $ 個の `b` からなる，長さ $ 2N $ の文字列 $ S $ が与えられます。

あなたは $ S $ からいくつかの文字を選びます。ただし各 $ i\ =\ 1,2,...,N $ について，$ S $ で $ i $ 番目に出現する `a` と $ i $ 番目に出現する `b` から片方だけ選ぶことは出来ません。 そして選んだ文字たちを( $ S $ での順番通りに)結合します。

こうして得られる文字列のうち，辞書順で最大のものを求めて下さい。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S $

## 输出格式

条件を満たす $ T $ のうち，辞書順で最大のものを出力して下さい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3000 $
- $ S $ は $ N $ 個の `a` と `b` からなる，長さ $ 2N $ の文字列である。

### Sample Explanation 1

$ S $ の $ 1,\ 3,\ 4,\ 6 $ 番目の文字からなる部分列 $ T $ は，条件を満たします。

### Sample Explanation 2

全ての文字を選ぶことも可能です。

## 样例 #1

### 输入

```
3
aababb
```

### 输出

```
abab
```

## 样例 #2

### 输入

```
3
bbabaa
```

### 输出

```
bbabaa
```

## 样例 #3

### 输入

```
6
bbbaabbabaaa
```

### 输出

```
bbbabaaa
```

## 样例 #4

### 输入

```
9
abbbaababaababbaba
```

### 输出

```
bbaababababa
```

