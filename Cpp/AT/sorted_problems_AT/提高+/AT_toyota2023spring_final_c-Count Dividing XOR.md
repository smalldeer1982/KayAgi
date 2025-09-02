---
title: "Count Dividing XOR"
layout: "post"
diff: 提高+/省选-
pid: AT_toyota2023spring_final_c
tag: []
---

# Count Dividing XOR

## 题目描述

[problemUrl]: https://atcoder.jp/contests/toyota2023spring-final/tasks/toyota2023spring_final_c

整数 $ L,R $ が与えられます． 以下の条件を満たす整数の組 $ (A,B) $ の個数を数えてください．

- $ L\ \leq\ A\ <\ B\ \leq\ R $
- $ A $ は $ A\ \oplus\ B $ で割り切れる．
- $ B $ は $ A\ \oplus\ B $ で割り切れる．

ただしここで $ \oplus $ はビット単位 $ \mathrm{XOR} $ 演算を表します．

  ビット単位 $ \mathrm{XOR} $ 演算とは  非負整数 $ A,\ B $ のビット単位 $ \mathrm{XOR} $ 、$ A\ \oplus\ B $ は、以下のように定義されます。

- $ A\ \oplus\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \oplus\ 101\ =\ 110 $)。  
 一般に $ k $ 個の非負整数 $ p_1,\ p_2,\ p_3,\ \dots,\ p_k $ のビット単位 $ \mathrm{XOR} $ は $ (\dots\ ((p_1\ \oplus\ p_2)\ \oplus\ p_3)\ \oplus\ \dots\ \oplus\ p_k) $ と定義され、これは $ p_1,\ p_2,\ p_3,\ \dots,\ p_k $ の順番によらないことが証明できます。

## 输入格式

入力は以下の形式で標準入力から与えられる．

> $ L $ $ R $

## 输出格式

答えを出力せよ．

## 说明/提示

### 制約

- $ 1\ \leq\ L\ <\ R\ \leq\ 10^{18} $
- $ R-L\ \leq\ 10^6 $
- 入力される値はすべて整数である

### Sample Explanation 1

$ (A,B)=(4,5) $ と $ (A,B)=(4,6) $ が条件を満たします．

## 样例 #1

### 输入

```
3 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 100
```

### 输出

```
124
```

## 样例 #3

### 输入

```
999000000 1000000000
```

### 输出

```
1726239
```

