---
title: "String Problem"
layout: "post"
diff: 普及/提高-
pid: AT_xmascon17_e
tag: []
---

# String Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/xmascon17/tasks/xmascon17_e

$ 2 $ つの文字列 $ S,\ T $ が与えられます。 以下のような操作を好きな順番で好きなだけ行うことで $ S $ を $ T $ にできるかどうかを判定してください。

- 操作 $ A $：$ S $ に含まれる文字 `A` を $ 1 $ つ削除する。
- 操作 $ B $：$ S $ の好きな位置に文字 `B` を $ 1 $ つ挿入する。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $ $ T $

## 输出格式

可能な場合は `YES` を、不可能な場合は `NO` を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|,\ |T|\ \leq\ 1000 $
- $ S,\ T $ は大文字アルファベットのみからなる

### 部分点

- $ |S|\ \leq\ 10 $ を満たすデータセットに正解した場合は、$ 50 $ 点が与えられる。
- 追加制約のないデータセットに正解した場合は、上記とは別に $ 50 $ 点が与えられる。

### Sample Explanation 1

例えば `XMAS` → `XBMAS` → `XBMS` のように操作すれば良いです。

### Sample Explanation 2

例えば `AABABA` → `ABABA` → `BABABA` → `BABABAB` → `BABBABAB` のように操作すれば良いです。

## 样例 #1

### 输入

```
XMAS
XBMS
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
AABABA
BABBABAB
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
AB
AA
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
ATCODER
CONTEST
```

### 输出

```
NO
```

