---
title: "[ABC330B] Minimize Abs 1"
layout: "post"
diff: 入门
pid: AT_abc330_b
tag: []
---

# [ABC330B] Minimize Abs 1

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc330/tasks/abc330_b

長さ $ N $ の整数列 $ A=(A_1,A_2,\ldots,A_N) $ 及び整数 $ L,R $ が与えられます。ここで $ L,R $ は $ L\leq\ R $ を満たします。

$ i=1,2,\ldots,N $ について以下の $ 2 $ つの条件を共に満たす整数 $ X_i $ を求めてください。なお、求める整数は常に一意に定まります。

- $ L\leq\ X_i\ \leq\ R $
- $ L $ 以上 $ R $ 以下であるようなどの整数 $ Y $ についても $ |X_i\ -\ A_i|\ \leq\ |Y-A_i| $ を満たす

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ L $ $ R $ $ A_1 $ $ \ldots $ $ A_N $

## 输出格式

$ i=1,2,\ldots,N $ について $ X_i $ を空白区切りで出力せよ。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ L\leq\ R\ \leq\ 10^9 $
- $ 1\leq\ A_i\leq\ 10^9 $
- 入力は全て整数
 
### Sample Explanation 1

$ i=1 $ では、 - $ |4-3|=1 $ - $ |5-3|=2 $ - $ |6-3|=3 $ - $ |7-3|=4 $ より $ X_i\ =\ 4 $ です。

## 样例 #1

### 输入

```
5 4 7
3 1 4 9 7
```

### 输出

```
4 4 4 7 7
```

## 样例 #2

### 输入

```
3 10 10
11 10 9
```

### 输出

```
10 10 10
```

