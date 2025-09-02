---
title: "Polynomial Divisors"
layout: "post"
diff: 省选/NOI-
pid: AT_tenka1_2019_e
tag: []
---

# Polynomial Divisors

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2019/tasks/tenka1_2019_e

$ N $ 次の整数係数多項式 $ f(x)=a_Nx^N+a_{N-1}x^{N-1}+...+a_0 $ が与えられます。任意の整数 $ x $ に対して $ p $ が $ f(x) $ を割り切るような素数 $ p $ をすべて求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ a_N $ $ : $ $ a_0 $

## 输出格式

任意の整数 $ x $ に対して $ p $ が $ f(x) $ を割り切るような素数 $ p $ を小さい順にすべて出力せよ。

## 说明/提示

### 制約

- $ 0\ \leq\ N\ \leq\ 10^4 $
- $ |a_i|\ \leq\ 10^9(0\leq\ i\leq\ N) $
- $ a_N\ \neq\ 0 $
- 入力はすべて整数である

### Sample Explanation 1

$ 2,7 $ は例えば、$ f(1)=14 $ や $ f(2)=28 $ を割り切ります。

### Sample Explanation 2

条件を満たす素数がない場合もあります。

## 样例 #1

### 输入

```
2
7
-7
14
```

### 输出

```
2
7
```

## 样例 #2

### 输入

```
3
1
4
1
5
```

### 输出

```

```

## 样例 #3

### 输入

```
0
998244353
```

### 输出

```
998244353
```

