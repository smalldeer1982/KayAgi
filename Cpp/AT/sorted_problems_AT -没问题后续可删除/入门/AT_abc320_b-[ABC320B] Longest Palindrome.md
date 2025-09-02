---
title: "[ABC320B] Longest Palindrome"
layout: "post"
diff: 入门
pid: AT_abc320_b
tag: ['字符串']
---

# [ABC320B] Longest Palindrome

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc320/tasks/abc320_b

文字列 $ S $ が与えられます。 $ S $ の連続する部分文字列のうち、回文であるものの長さの最大値を求めてください。  
 ただし、$ S $ の連続する部分文字列であって回文であるものは常に存在します。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ S $ は長さ $ 2 $ 以上 $ 100 $ 以下の英大文字からなる文字列
 
### Sample Explanation 1

`TOYOTA` の連続する部分文字列 `TOYOT` は長さ $ 5 $ の回文です。 `TOYOTA` の唯一の長さ $ 6 $ の連続する部分文字列 `TOYOTA` は回文でないので、$ 5 $ を出力します。

### Sample Explanation 2

すべての長さ $ 1 $ の連続する部分文字列は回文です。

## 样例 #1

### 输入

```
TOYOTA
```

### 输出

```
5
```

## 样例 #2

### 输入

```
ABCDEFG
```

### 输出

```
1
```

## 样例 #3

### 输入

```
AAAAAAAAAA
```

### 输出

```
10
```

