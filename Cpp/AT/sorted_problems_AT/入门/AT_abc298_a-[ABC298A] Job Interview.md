---
title: "[ABC298A] Job Interview"
layout: "post"
diff: 入门
pid: AT_abc298_a
tag: []
---

# [ABC298A] Job Interview

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc298/tasks/abc298_a

高橋君はある会社の採用面接を受けました。

面接官の人数 $ N $ と、各面接官の高橋君への評価を表す長さ $ N $ の文字列 $ S $ が与えられます。  
 $ i=1,2,\ldots,N $ に対し $ S $ の $ i $ 文字目が $ i $ 番目の面接官の評価に対応し、`o` は「良」、`-` は「可」、`x` は 「不可」を表します。

高橋君は以下の $ 2 $ つの条件を両方満たすならば合格、そうでなければ不合格です。

- 「良」と評価した面接官が少なくとも $ 1 $ 人いる
- 「不可」と評価した面接官がいない
 
高橋君が合格かどうかを判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S $

## 输出格式

高橋君が合格ならば `Yes` と、そうでなければ `No` と出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ S $ は `o`, `-`, `x` のみからなる長さが $ N $ の文字列
 
### Sample Explanation 1

$ 1,\ 2 $ 番目の面接官が「良」と評価していて、さらに「不可」と評価した面接官がいないため合格です。

### Sample Explanation 2

「良」と評価した面接官が $ 1 $ 人もいないため不合格です。

### Sample Explanation 4

$ 100 $ 番目の面接官が「不可」と評価しているため不合格です。

## 样例 #1

### 输入

```
4
oo--
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3
---
```

### 输出

```
No
```

## 样例 #3

### 输入

```
1
o
```

### 输出

```
Yes
```

## 样例 #4

### 输入

```
100
ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooox
```

### 输出

```
No
```

