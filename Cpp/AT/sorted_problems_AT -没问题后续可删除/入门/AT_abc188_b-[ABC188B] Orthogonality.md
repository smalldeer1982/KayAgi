---
title: "[ABC188B] Orthogonality"
layout: "post"
diff: 入门
pid: AT_abc188_b
tag: []
---

# [ABC188B] Orthogonality

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc188/tasks/abc188_b

$ 2 $ つの $ N $ 次元ベクトル $ A\ =\ (A_1,\ A_2,\ A_3,\ \dots,\ A_N),\ B\ =\ (B_1,\ B_2,\ B_3,\ \dots,\ B_N) $ が与えられます。  
 $ A $ と $ B $ の内積が $ 0 $ かどうかを判定してください。  
 すなわち、$ A_1B_1\ +\ A_2B_2\ +\ A_3B_3\ +\ \dots\ +\ A_NB_N\ =\ 0 $ かどうかを判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ A_3 $ $ \dots $ $ A_N $ $ B_1 $ $ B_2 $ $ B_3 $ $ \dots $ $ B_N $

## 输出格式

$ A $ と $ B $ の内積が $ 0 $ ならば `Yes` を、$ 0 $ でないならば `No` を出力せよ。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 100000 $
- $ -100\ \le\ A_i\ \le\ 100 $
- $ -100\ \le\ B_i\ \le\ 100 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ A $ と $ B $ の内積は $ (-3)\ \times\ 4\ +\ 6\ \times\ 2\ =\ 0 $ です。

### Sample Explanation 2

$ A $ と $ B $ の内積は $ 4\ \times\ (-1)\ +\ 5\ \times\ (-3)\ =\ -19 $ です。

### Sample Explanation 3

$ A $ と $ B $ の内積は $ 1\ \times\ 3\ +\ 3\ \times\ (-6)\ +\ 5\ \times\ 3\ =\ 0 $ です。

## 样例 #1

### 输入

```
2
-3 6
4 2
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2
4 5
-1 -3
```

### 输出

```
No
```

## 样例 #3

### 输入

```
3
1 3 5
3 -6 3
```

### 输出

```
Yes
```

