---
title: "Unsolvable"
layout: "post"
diff: 提高+/省选-
pid: CF225E
tag: []
---

# Unsolvable

## 题目描述

Consider the following equation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF225E/546df2c440088cc1d07628a3b2e6a0b61a00f3dc.png) where sign $ [a] $ represents the integer part of number $ a $ .Let's find all integer $ z $ $ (z&gt;0) $ , for which this equation is unsolvable in positive integers. The phrase "unsolvable in positive integers" means that there are no such positive integers $ x $ and $ y $ $ (x,y&gt;0) $ , for which the given above equation holds.

Let's write out all such $ z $ in the increasing order: $ z_{1},z_{2},z_{3} $ , and so on $ (z_{i}&lt;z_{i+1}) $ . Your task is: given the number $ n $ , find the number $ z_{n} $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=40 $ ).

## 输出格式

Print a single integer — the number $ z_{n} $ modulo $ 1000000007 $ $ (10^{9}+7) $ . It is guaranteed that the answer exists.

## 样例 #1

### 输入

```
1

```

### 输出

```
1
```

## 样例 #2

### 输入

```
2

```

### 输出

```
3
```

## 样例 #3

### 输入

```
3

```

### 输出

```
15
```

