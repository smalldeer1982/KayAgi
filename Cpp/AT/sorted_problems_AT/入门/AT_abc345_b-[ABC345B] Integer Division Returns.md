---
title: "[ABC345B] Integer Division Returns"
layout: "post"
diff: 入门
pid: AT_abc345_b
tag: []
---

# [ABC345B] Integer Division Returns

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc345/tasks/abc345_b

$ -10^{18} $ 以上 $ 10^{18} $ 以下の整数 $ X $ が与えられるので、$ \left\lceil\ \dfrac{X}{10}\ \right\rceil $ を出力してください。  
 ここで、$ \left\lceil\ a\ \right\rceil $ は $ a $ 以上の整数のうち最小のものを意味します。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ X $

## 输出格式

$ \left\lceil\ \dfrac{X}{10}\ \right\rceil $ を整数として出力せよ。

## 说明/提示

### 制約

- $ -10^{18}\ \leq\ X\ \leq\ 10^{18} $
- $ X $ は整数
 
### Sample Explanation 1

$ \frac{27}{10}\ =\ 2.7 $ 以上の整数は $ 3,\ 4,\ 5,\ \dots $ です。この中で一番小さい整数は $ 3 $ なので、$ \left\ \lceil\ \frac{27}{10}\ \right\ \rceil\ =\ 3 $ となります。

### Sample Explanation 2

$ \frac{-13}{10}\ =\ -1.3 $ 以上の整数は、全ての正整数および $ 0,\ -1 $ です。この中で一番小さい整数は $ -1 $ なので、$ \left\ \lceil\ \frac{-13}{10}\ \right\ \rceil\ =\ -1 $ となります。

### Sample Explanation 3

$ \frac{40}{10}\ =\ 4 $ 以上の整数で一番小さい整数は $ 4 $ 自身です。

## 样例 #1

### 输入

```
27
```

### 输出

```
3
```

## 样例 #2

### 输入

```
-13
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
40
```

### 输出

```
4
```

## 样例 #4

### 输入

```
-20
```

### 输出

```
-2
```

## 样例 #5

### 输入

```
123456789123456789
```

### 输出

```
12345678912345679
```

