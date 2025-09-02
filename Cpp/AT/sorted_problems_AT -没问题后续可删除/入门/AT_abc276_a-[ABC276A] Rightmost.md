---
title: "[ABC276A] Rightmost"
layout: "post"
diff: 入门
pid: AT_abc276_a
tag: []
---

# [ABC276A] Rightmost

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc276/tasks/abc276_a

英小文字からなる文字列 $ S $ が与えられます。  
 $ S $ に `a` が現れるならば最後に現れるのが何文字目かを出力し、現れないならば $ -1 $ を出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ S $ は英小文字からなる長さ $ 1 $ 以上 $ 100 $ 以下の文字列

### Sample Explanation 1

$ S $ に `a` は $ 3 $ 回現れますが、最後に現れるのは $ 7 $ 文字目なので、$ 7 $ を出力します。

### Sample Explanation 2

$ S $ に `a` は現れないので、$ -1 $ を出力します。

## 样例 #1

### 输入

```
abcdaxayz
```

### 输出

```
7
```

## 样例 #2

### 输入

```
bcbbbz
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
aaaaa
```

### 输出

```
5
```

