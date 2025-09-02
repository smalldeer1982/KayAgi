---
title: "[ABC201A] Tiny Arithmetic Sequence"
layout: "post"
diff: 入门
pid: AT_abc201_a
tag: []
---

# [ABC201A] Tiny Arithmetic Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc201/tasks/abc201_a

長さ $ 3 $ の数列 $ A=(A_1,A_2,A_3) $ が与えられます。

$ A $ を適切に並び替えて等差数列にすることはできますか？

即ち、$ A_3-A_2=A_2-A_1 $ を満たすように $ A $ を並び替えることはできますか？

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A_1 $ $ A_2 $ $ A_3 $

## 输出格式

$ A $ を並び替えて等差数列にできるなら `Yes`、できないなら `No` と出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ A_i\ \leq\ 100 $
- 入力は全て整数

### Sample Explanation 1

例えば $ (1,3,5) $ と並び替えることで等差数列になります。

### Sample Explanation 2

どのように並び替えても $ A $ は等差数列になりません。

### Sample Explanation 3

$ A $ の要素が全て等しい場合や、$ A $ が元から等差数列になっている場合もあります。

## 样例 #1

### 输入

```
5 1 3
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
1 4 3
```

### 输出

```
No
```

## 样例 #3

### 输入

```
5 5 5
```

### 输出

```
Yes
```

