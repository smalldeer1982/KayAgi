---
title: "[ABC240A] Edge Checker"
layout: "post"
diff: 入门
pid: AT_abc240_a
tag: []
---

# [ABC240A] Edge Checker

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc240/tasks/abc240_a

下の画像で示す図において、$ a $ 番の点と $ b $ 番の点が線で直接結ばれているかを答えてください。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc240_a/f5adeb25247ba30397bc0cea3bcc56cd667df4d2.png)

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ a $ $ b $

## 输出格式

$ a $ 番の点と $ b $ 番の点が線で直接結ばれている場合は `Yes` を出力し、結ばれていない場合は `No` を出力せよ。  
 ジャッジは英大文字と英小文字を厳密に区別することに注意せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ a\ \lt\ b\ \leq\ 10 $
- $ a,\ b $ は整数

### Sample Explanation 1

問題文で示した図において、$ 4 $ 番の点と $ 5 $ 番の点は線で直接結ばれています。 よって、`Yes` を出力します。

### Sample Explanation 2

問題文で示した図において、$ 3 $ 番の点と $ 5 $ 番の点は線で直接結ばれていません。 よって、`No` を出力します。

## 样例 #1

### 输入

```
4 5
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3 5
```

### 输出

```
No
```

## 样例 #3

### 输入

```
1 10
```

### 输出

```
Yes
```

