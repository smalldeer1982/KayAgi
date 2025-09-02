---
title: "[ABC285A] Edge Checker 2"
layout: "post"
diff: 入门
pid: AT_abc285_a
tag: ['模拟']
---

# [ABC285A] Edge Checker 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc285/tasks/abc285_a

下の画像で示す図において、$ a $ 番の点と $ b $ 番の点が線で直接結ばれているかを答えてください。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc285_a/b232f1e7ed679c7b9c924ada22c954d50903b73f.png)

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ a $ $ b $

## 输出格式

$ a $ 番の点と $ b $ 番の点が線で直接結ばれているなら `Yes`、結ばれていないなら `No` を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ a\ \lt\ b\ \leq\ 15 $
- $ a,b $ は整数

### Sample Explanation 1

問題文で示した図において、$ 1 $ 番の点と $ 2 $ 番の点は線で直接結ばれています。 よって、`Yes` を出力します。

### Sample Explanation 2

問題文で示した図において、$ 2 $ 番の点と $ 8 $ 番の点は線で直接結ばれていません。 よって、`No` を出力します。

## 样例 #1

### 输入

```
1 2
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2 8
```

### 输出

```
No
```

## 样例 #3

### 输入

```
14 15
```

### 输出

```
No
```

