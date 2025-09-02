---
title: "[ABC315A] tcdr"
layout: "post"
diff: 入门
pid: AT_abc315_a
tag: ['模拟']
---

# [ABC315A] tcdr

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc315/tasks/abc315_a

英小文字からなる文字列 $ S $ が与えられます。  
 $ S $ から `a`, `e`, `i`, `o`, `u` をすべて取り除いて得られる文字列を出力してください。  
 なお、$ S $ は `a`, `e`, `i`, `o`, `u` 以外の文字を一つ以上含みます。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ S $ は英小文字からなる長さ $ 1 $ 以上 $ 100 $ 以下の文字列
- $ S $ は `a`, `e`, `i`, `o`, `u` 以外の文字を一つ以上含む
 
### Sample Explanation 1

$ S\ = $ `atcoder` のとき、$ 1,\ 4,\ 6 $ 文字目を取り除いて `tcdr` を得ます。

## 样例 #1

### 输入

```
atcoder
```

### 输出

```
tcdr
```

## 样例 #2

### 输入

```
xyz
```

### 输出

```
xyz
```

## 样例 #3

### 输入

```
aaaabbbbcccc
```

### 输出

```
bbbbcccc
```

