---
title: "[ABC225A] Distinct Strings"
layout: "post"
diff: 入门
pid: AT_abc225_a
tag: []
---

# [ABC225A] Distinct Strings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc225/tasks/abc225_a

英小文字のみからなる長さ $ 3 $ の文字列 $ S $ が与えられます。

$ S $ の各文字を並び替えて得られる文字列は、何種類ありますか？

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

$ S $ の各文字を並び替えて得られる文字列の種類数を出力せよ。

## 说明/提示

### 制約

- $ S $ は英小文字のみからなる長さ $ 3 $ の文字列

### Sample Explanation 1

$ S= $ `aba` の各文字を並び替えて得られる文字列は、`aab`, `aba`, `baa` の $ 3 $ 通りです。

### Sample Explanation 2

$ S= $ `ccc` の各文字を並び替えて得られる文字列は、`ccc` の $ 1 $ 通りのみです。

### Sample Explanation 3

$ S= $ `xyz` の各文字を並び替えて得られる文字列は、`xyz`, `xzy`, `yxz`, `yzx`, `zxy`, `zyx` の $ 6 $ 通りです。

## 样例 #1

### 输入

```
aba
```

### 输出

```
3
```

## 样例 #2

### 输入

```
ccc
```

### 输出

```
1
```

## 样例 #3

### 输入

```
xyz
```

### 输出

```
6
```

