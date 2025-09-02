---
title: "[ABC164A] Sheep and Wolves"
layout: "post"
diff: 入门
pid: AT_abc164_a
tag: []
---

# [ABC164A] Sheep and Wolves

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc164/tasks/abc164_a

羊が $ S $ 匹、狼が $ W $ 匹います。

狼の数が羊の数以上のとき、羊は狼に襲われてしまいます。

羊が狼に襲われるなら `unsafe`、襲われないなら `safe` を出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $ $ W $

## 输出格式

羊が狼に襲われるなら `unsafe`、襲われないなら `safe` を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ S\ \leq\ 100 $
- $ 1\ \leq\ W\ \leq\ 100 $

### Sample Explanation 1

羊が $ 4 $ 匹、狼が $ 5 $ 匹います。狼の数が羊の数以上なので、羊は狼に襲われてしまいます。

### Sample Explanation 2

多勢に無勢です。

## 样例 #1

### 输入

```
4 5
```

### 输出

```
unsafe
```

## 样例 #2

### 输入

```
100 2
```

### 输出

```
safe
```

## 样例 #3

### 输入

```
10 10
```

### 输出

```
unsafe
```

