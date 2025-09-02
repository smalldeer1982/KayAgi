---
title: "[ABC287A] Majority"
layout: "post"
diff: 入门
pid: AT_abc287_a
tag: []
---

# [ABC287A] Majority

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc287/tasks/abc287_a

ある提案に対し、$ N $ 人の人が賛成か反対かを表明しています。なお、$ N $ は奇数です。

$ i\ \,\ (i\ =\ 1,\ 2,\ \dots,\ N) $ 番目の人の意見は文字列 $ S_i $ で表され、$ S_i\ = $ `For` のとき賛成しており、$ S_i\ = $ `Against` のとき反対しています。

過半数の人がこの提案に賛成しているかどうかを判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S_1 $ $ S_2 $ $ \vdots $ $ S_N $

## 输出格式

$ N $ 人のうち過半数が提案に賛成しているならば `Yes`、そうでなければ `No` と出力せよ。

## 说明/提示

### 制約

- $ N $ は $ 1 $ 以上 $ 99 $ 以下の**奇数**
- 全ての $ i\ =\ 1,\ 2,\ \dots,\ N $ に対し、$ S_i\ = $ `For` または $ S_i\ = $ `Against`
 
### Sample Explanation 1

提案に賛成している人数は $ 2 $ 人であり、これは半数を超えているので `Yes` と出力します。

### Sample Explanation 2

提案に賛成している人数は $ 2 $ 人であり、これは半数以下なので `No` と出力します。

## 样例 #1

### 输入

```
3
For
Against
For
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5
Against
Against
For
Against
For
```

### 输出

```
No
```

## 样例 #3

### 输入

```
1
For
```

### 输出

```
Yes
```

