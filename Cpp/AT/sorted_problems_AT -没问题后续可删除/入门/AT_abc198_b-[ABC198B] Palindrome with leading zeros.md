---
title: "[ABC198B] Palindrome with leading zeros"
layout: "post"
diff: 入门
pid: AT_abc198_b
tag: []
---

# [ABC198B] Palindrome with leading zeros

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc198/tasks/abc198_b

整数 $ N $ が与えられます。

$ N $ を十進法で表した文字列の先頭に $ 0 $ 個以上の `0` をつけることで、回文にすることはできますか？

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $

## 输出格式

回文にできるなら `Yes`、できないなら `No` を出力せよ。

## 说明/提示

### 制約

- $ 0\ \leq\ N\ \leq\ 10^9 $

### Sample Explanation 1

`1210` の先頭に $ 1 $ 個の `0` をつけると `01210` となり回文になります。

### Sample Explanation 2

`777` はもともと回文です。

## 样例 #1

### 输入

```
1210
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
777
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
123456789
```

### 输出

```
No
```

