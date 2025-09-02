---
title: "Powers of Two"
layout: "post"
diff: 普及/提高-
pid: CF702B
tag: []
---

# Powers of Two

## 题目描述

You are given $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Find the number of pairs of indexes $ i,j $ ( $ i&lt;j $ ) that $ a_{i}+a_{j} $ is a power of $ 2 $ (i. e. some integer $ x $ exists so that $ a_{i}+a_{j}=2^{x} $ ).

## 输入格式

The first line contains the single positive integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of integers.

The second line contains $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print the number of pairs of indexes $ i,j $ ( $ i&lt;j $ ) that $ a_{i}+a_{j} $ is a power of $ 2 $ .

## 说明/提示

In the first example the following pairs of indexes include in answer: $ (1,4) $ and $ (2,4) $ .

In the second example all pairs of indexes $ (i,j) $ (where $ i&lt;j $ ) include in answer.

## 样例 #1

### 输入

```
4
7 3 2 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
1 1 1

```

### 输出

```
3

```

