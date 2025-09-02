---
title: "[ABC407A] Approximation"
layout: "post"
diff: 入门
pid: AT_abc407_a
tag: ['数学', '枚举']
---

# [ABC407A] Approximation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc407/tasks/abc407_a

正整数 $ A $ と正の奇数 $ B $ が与えられます。

実数 $ \dfrac\ AB $ との差が最小となる整数を出力してください。

ただし、制約のもとでそのような整数がただ一つ存在することが証明できます。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A $ $ B $

## 输出格式

$ \dfrac\ AB $ との差が最小となる整数を出力せよ。

## 说明/提示

### 制約

- $ 1\leq\ A\leq407 $
- $ 1\leq\ B\leq407 $
- $ B $ は奇数
- 入力はすべて整数
 
### Sample Explanation 1

$ \dfrac\ AB=\dfrac47=0.5714\ldots $ です。 $ \dfrac\ AB $ と $ 1 $ との差は $ \dfrac37=0.4285\ldots $ で、これより差が小さい整数はありません。 よって、`1` を出力してください。

### Sample Explanation 2

$ \dfrac\ AB=\dfrac{407}{29}=14.0344\ldots $ です。 $ \dfrac\ AB $ と $ 14 $ との差は $ \dfrac1{29}=0.0344\ldots $ で、これより差が小さい整数はありません。 よって、`14` を出力してください。

### Sample Explanation 3

$ \dfrac\ AB $ が整数である場合もあります。

## 样例 #1

### 输入

```
4 7
```

### 输出

```
1
```

## 样例 #2

### 输入

```
407 29
```

### 输出

```
14
```

## 样例 #3

### 输入

```
22 11
```

### 输出

```
2
```

