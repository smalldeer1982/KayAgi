---
title: "Beautiful Harmony"
layout: "post"
diff: 入门
pid: AT_cpsco2019_s1_b
tag: []
---

# Beautiful Harmony

## 题目描述

[problemUrl]: https://atcoder.jp/contests/cpsco2019-s1/tasks/cpsco2019_s1_b

英小文字からなる文字列 $ S $ が「美しい」とは、 $ S $ に $ 1 $ つ以上含まれるアルファベットについて、その出現回数がすべて等しいことを言います。例えば、`abba` や `ddddd`，`xyz` は美しいですが、`aab` や `xyxyxyz` は美しくありません。

文字列 $ S $ が与えられるので、$ S $ が美しいかどうかを判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられます。

> $ S $

## 输出格式

 $ S $ が美しいなら`Yes` 、美しくないなら`No` と $ 1 $ 行に出力してください。

## 说明/提示

### 制約

- $ S $ の長さは $ 1 $ 以上 $ 10^5 $ 以下
- $ S $ は英小文字のみからなる

### Sample Explanation 1

`a`，`b`，`c` が $ 2 $ 回ずつですべて出現回数が等しいので美しいです。

## 样例 #1

### 输入

```
ababcc
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
reiwa
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
cpsco
```

### 输出

```
No
```

