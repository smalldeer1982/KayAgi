---
title: "[ABC312A] Chord"
layout: "post"
diff: 入门
pid: AT_abc312_a
tag: ['模拟']
---

# [ABC312A] Chord

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc312/tasks/abc312_a

英大文字からなる長さ $ 3 $ の文字列 $ S $ が与えられます。$ S $ が `ACE`、`BDF`、`CEG`、`DFA`、`EGB`、`FAC`、`GBD` のいずれかと等しいとき `Yes` を、そうでないとき `No` を出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

$ S $ が `ACE`、`BDF`、`CEG`、`DFA`、`EGB`、`FAC`、`GBD` のいずれかと等しいとき `Yes` を、そうでないとき `No` を出力せよ。

## 说明/提示

### 制約

- $ S $ は英大文字からなる長さ $ 3 $ の文字列
 
### Sample Explanation 1

$ S\ = $ `ABC` のとき、$ S $ は `ACE`、`BDF`、`CEG`、`DFA`、`EGB`、`FAC`、`GBD` のいずれとも等しくないので `No` を出力します。

## 样例 #1

### 输入

```
ABC
```

### 输出

```
No
```

## 样例 #2

### 输入

```
FAC
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
XYX
```

### 输出

```
No
```

