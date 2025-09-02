---
title: "[AGC069E] Pair of Sequences"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_agc069_e
tag: ['多项式']
---

# [AGC069E] Pair of Sequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc069/tasks/agc069_e

整数 $ N,M,X,Y $ が与えられます。

数列 $ A=(a_1,\ldots,a_N),\ B=(b_1,\ldots,b_N) $ の組 $ (A,B) $ であって以下の条件すべてを満たすものの個数を $ 998244353 $ で割った余りを求めてください。

- $ A $ は非負整数列
- $ B $ は $ (0,1,\ldots,M-1) $ の部分列
- $ \sum\limits_{i=1}^{N}\ a_i\ =\ X $
- $ \sum\limits_{i=1}^{N}\ a_i\ b_i\ =\ Y $

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $ $ X $ $ Y $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ X\ ,\ Y\ \leq\ 2\ \times\ 10^5 $
- 入力はすべて整数
 
### Sample Explanation 1

条件を満たす $ (A,B) $ の組は以下の $ 5 $ 個です。 - $ A=(0,2,1),\ B=(0,1,2) $ - $ A=(1,0,2),\ B=(0,1,2) $ - $ A=(1,1,1),\ B=(0,1,3) $ - $ A=(1,2,0),\ B=(0,2,3) $ - $ A=(2,1,0),\ B=(1,2,3) $

### Sample Explanation 2

条件を満たす $ (A,B) $ の組が存在しません。

### Sample Explanation 3

$ 998244353 $ で割った余りを求めてください。

## 样例 #1

### 输入

```
3 4 3 4
```

### 输出

```
5
```

## 样例 #2

### 输入

```
1 1 1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
12345 67890 9876 54321
```

### 输出

```
150392014
```

