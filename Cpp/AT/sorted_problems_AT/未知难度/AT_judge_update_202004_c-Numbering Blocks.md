---
title: "Numbering Blocks"
layout: "post"
diff: 难度0
pid: AT_judge_update_202004_c
tag: []
---

# Numbering Blocks

## 题目描述

[problemUrl]: https://atcoder.jp/contests/judge-update-202004/tasks/judge_update_202004_c

積み木の山が $ 3 $ つ並んでおり、それぞれの山には $ a_1\ \geq\ a_2\ \geq\ a_3 $ 個の積み木が積まれています。

全部で $ N\ =\ a_1\ +\ a_2\ +\ a_3 $ 個の積み木がありますが、これらに $ 1 $ から $ N $ までの整数をちょうど $ 1 $ つずつ書き込みます。

ただし、次の条件を全て満たす必要があります。

- 左から $ i $ 個目の山の下から $ j $ 個目の積み木に書かれた整数を $ X_{i,\ j} $ で表す $ (1\ \leq\ i\ \leq\ 3,\ 1\ \leq\ j\ \leq\ a_i) $ とき、
  - $ X_{i,\ j}\ >\ X_{i,\ j-1}\ (1\ \leq\ i\ \leq\ 3,\ 1\ <\ j\ \leq\ a_i) $
  - $ X_{i,\ j}\ >\ X_{i-1,\ j}\ (1\ <\ i\ \leq\ 3,\ 1\ \leq\ j\ \leq\ a_i) $

この条件を満たす整数の書き込み方の個数を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ a_1 $ $ a_2 $ $ a_3 $

## 输出格式

条件を満たす整数の書き込み方の個数を出力せよ。

## 说明/提示

### 制約

- $ 3\ \geq\ a_1\ \geq\ a_2\ \geq\ a_3\ \geq\ 1 $
- 入力は全て整数である

### Sample Explanation 1

左から $ 1,\ 2,\ 3 $ と書き込むしかありません。

### Sample Explanation 2

以下の $ 3 $ 通りの書き込み方が存在します。 !\[Blocks\](https://img.atcoder.jp/judge-update-202004/efca39d8f5e89676e3cc3819597b4ee5.png "書き込み方")

## 样例 #1

### 输入

```
1 1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 1 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2 2 1
```

### 输出

```
5
```

