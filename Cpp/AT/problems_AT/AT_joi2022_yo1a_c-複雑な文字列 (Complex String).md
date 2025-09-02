---
title: "複雑な文字列 (Complex String)"
layout: "post"
diff: 入门
pid: AT_joi2022_yo1a_c
tag: []
---

# 複雑な文字列 (Complex String)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2022yo1a/tasks/joi2022_yo1a_c

長さ $ N $ の文字列 $ S $ が与えられる．$ S $ の各文字は `A`，`B`，`C`，`D`，`E` のいずれかである．

$ S $ に $ 3 $ 種類以上の文字が出現する場合は `Yes` を，そうでない場合は `No` を出力せよ．

## 输入格式

入力は以下の形式で標準入力から与えられる．

> $ N $ $ S $

## 输出格式

$ S $ に $ 3 $ 種類以上の文字が出現する場合は `Yes` を，そうでない場合は `No` を出力せよ．

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ \leqq\ 100 $．
- $ S $ は長さ $ N $ の文字列である．
- $ S $ の各文字は `A`，`B`，`C`，`D`，`E` のいずれかである．
- $ N $ は整数である．

### Sample Explanation 1

出現する文字は `A`，`B`，`E` の $ 3 $ 種類である．$ 3 $ 種類以上の文字が出現するため，`Yes` を出力する．

### Sample Explanation 2

出現する文字は `A`，`D` の $ 2 $ 種類である．$ 3 $ 種類以上の文字が出現しないため，`No` を出力する．

## 样例 #1

### 输入

```
4
BABE
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3
DAD
```

### 输出

```
No
```

## 样例 #3

### 输入

```
5
BACED
```

### 输出

```
Yes
```

## 样例 #4

### 输入

```
28
EEEEEEEEEEEEEEEEEEEEEEEEEEEE
```

### 输出

```
No
```

