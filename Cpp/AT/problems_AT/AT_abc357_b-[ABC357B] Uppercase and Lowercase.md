---
title: "[ABC357B] Uppercase and Lowercase"
layout: "post"
diff: 入门
pid: AT_abc357_b
tag: ['模拟']
---

# [ABC357B] Uppercase and Lowercase

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc357/tasks/abc357_b

英小文字と英大文字からなる文字列 $ S $ が与えられます。$ S $ の長さは奇数です。  
 $ S $ に含まれる大文字の個数が小文字の個数よりも多ければ、$ S $ に含まれる全ての小文字を大文字に変換してください。  
 そうでない場合は、$ S $ に含まれる全ての大文字を小文字に変換してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

問題文の指示に従って文字を変換した後の $ S $ を出力せよ。

## 说明/提示

### 制約

- $ S $ は英小文字および英大文字からなる文字列
- $ S $ の長さは $ 1 $ 以上 $ 99 $ 以下の奇数
 
### Sample Explanation 1

`AtCoder` に含まれる小文字の個数は $ 5 $ 個、大文字の個数は $ 2 $ 個です。よって `AtCoder` に含まれる全ての大文字を小文字に変換した `atcoder` が答えとなります。

### Sample Explanation 2

`SunTORY` に含まれる小文字の個数は $ 2 $ 個、大文字の個数は $ 5 $ 個です。よって `SunTORY` に含まれる全ての小文字を大文字に変換した `SUNTORY` が答えとなります。

## 样例 #1

### 输入

```
AtCoder
```

### 输出

```
atcoder
```

## 样例 #2

### 输入

```
SunTORY
```

### 输出

```
SUNTORY
```

## 样例 #3

### 输入

```
a
```

### 输出

```
a
```

