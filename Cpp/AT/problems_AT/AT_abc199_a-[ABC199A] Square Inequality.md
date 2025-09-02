---
title: "[ABC199A] Square Inequality"
layout: "post"
diff: 入门
pid: AT_abc199_a
tag: []
---

# [ABC199A] Square Inequality

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc199/tasks/abc199_a

整数 $ A,\ B,\ C $ が与えられます。  
 $ A^2\ +\ B^2\ <\ C^2 $ かを判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A $ $ B $ $ C $

## 输出格式

$ A^2\ +\ B^2\ <\ C^2 $ なら `Yes` を、そうでないなら `No` を出力せよ。

## 说明/提示

### 制約

- $ 0\ \le\ A\ \le\ 1000 $
- $ 0\ \le\ B\ \le\ 1000 $
- $ 0\ \le\ C\ \le\ 1000 $
- $ A,\ B,\ C $ は整数である

### Sample Explanation 1

$ A^2\ +\ B^2\ =\ 2^2\ +\ 2^2\ =\ 8 $ 、$ C^2\ =\ 4^2\ =\ 16 $ より $ A^2\ +\ B^2\ <\ C^2 $ なので `Yes` を出力します。

### Sample Explanation 2

$ A^2\ +\ B^2\ =\ 200 $ 、$ C^2\ =\ 100 $ なので $ A^2\ +\ B^2\ <\ C^2 $ ではありません。

## 样例 #1

### 输入

```
2 2 4
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
10 10 10
```

### 输出

```
No
```

## 样例 #3

### 输入

```
3 4 5
```

### 输出

```
No
```

