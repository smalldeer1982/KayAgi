---
title: "[ABC380D] Strange Mirroring"
layout: "post"
diff: 普及/提高-
pid: AT_abc380_d
tag: ['数学']
---

# [ABC380D] Strange Mirroring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc380/tasks/abc380_d

英大小文字からなる文字列 $ S $ が与えられます。

$ S $ に以下の操作を $ 10^{100} $ 回繰り返します。

- まず、 $ S $ の大文字を小文字に、小文字を大文字に書き換えた文字列を $ T $ とする。
- その後、 $ S $ と $ T $ とをこの順に連結した文字列を新たな $ S $ とする。
 
$ Q $ 個の質問に答えて下さい。 そのうち $ i $ 個目は次の通りです。

- 全ての操作を終えた後の $ S $ の先頭から $ K_i $ 文字目を求めよ。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $ $ Q $ $ K_1 $ $ K_2 $ $ \dots $ $ K_Q $

## 输出格式

$ i $ 個目の質問の答えを $ C_i $ とする時、以下の形式で $ 1 $ 行に空白区切りで出力せよ。

> $ C_1 $ $ C_2 $ $ \dots $ $ C_Q $

## 说明/提示

### 制約

- $ S $ は英大小文字からなる長さ $ 1 $ 以上 $ 2\ \times\ 10^5 $ 以下の文字列
- $ Q,K_i $ は整数
- $ 1\ \le\ Q\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ K_i\ \le\ 10^{18} $
 
### Sample Explanation 1

操作前の $ S\ = $ `aB` です。 - `aB` に $ 1 $ 回操作を行うと `aBAb` となります。 - `aB` に $ 2 $ 回操作を行うと `aBAbAbaB` となります。 - $ \dots $ $ 10^{100} $ 回の操作を終えた後の $ S\ = $ `aBAbAbaBAbaBaBAb`... です。

## 样例 #1

### 输入

```
aB
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
```

### 输出

```
a B A b A b a B A b a B a B A b
```

## 样例 #2

### 输入

```
qWeRtYuIoP
8
1 1 2 3 5 8 13 21
```

### 输出

```
q q W e t I E Q
```

## 样例 #3

### 输入

```
AnUoHrjhgfLMcDIpzxXmEWPwBZvbKqQuiJTtFSlkNGVReOYCdsay
5
1000000000000000000 123456789 1 987654321 999999999999999999
```

### 输出

```
K a A Z L
```

