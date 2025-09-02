---
title: "[ABC260A] A Unique Letter"
layout: "post"
diff: 入门
pid: AT_abc260_a
tag: []
---

# [ABC260A] A Unique Letter

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc260/tasks/abc260_a

長さ $ 3 $ の文字列 $ S $ が与えられます。  
$ S $ に $ 1 $ 度だけ含まれる文字を $ 1 $ つ出力してください。  
但し、そのような文字が存在しない場合は代わりに `-1` と出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

答えを出力せよ。正解が複数ある場合、どれを出力してもよい。

## 说明/提示

### 制約

- $ S $ は英小文字のみからなる $ 3 $ 文字の文字列

### Sample Explanation 1

`pop` に `o` は $ 1 $ 度だけ含まれます。

### Sample Explanation 2

`abc` に `a`, `b`, `c` はどれも $ 1 $ 度だけ含まれるので、どれを出力しても構いません。

### Sample Explanation 3

`xxx` に $ 1 $ 度だけ含まれる文字はありません。

## 样例 #1

### 输入

```
pop
```

### 输出

```
o
```

## 样例 #2

### 输入

```
abc
```

### 输出

```
a
```

## 样例 #3

### 输入

```
xxx
```

### 输出

```
-1
```

