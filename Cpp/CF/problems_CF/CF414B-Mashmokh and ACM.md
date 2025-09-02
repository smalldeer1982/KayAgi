---
title: "Mashmokh and ACM"
layout: "post"
diff: 普及/提高-
pid: CF414B
tag: []
---

# Mashmokh and ACM

## 题目描述

Mashmokh's boss, Bimokh, didn't like Mashmokh. So he fired him. Mashmokh decided to go to university and participate in ACM instead of finding a new job. He wants to become a member of Bamokh's team. In order to join he was given some programming tasks and one week to solve them. Mashmokh is not a very experienced programmer. Actually he is not a programmer at all. So he wasn't able to solve them. That's why he asked you to help him with these tasks. One of these tasks is the following.

A sequence of $ l $ integers $ b_{1},b_{2},...,b_{l} $ $ (1<=b_{1}<=b_{2}<=...<=b_{l}<=n) $ is called good if each number divides (without a remainder) by the next number in the sequence. More formally ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF414B/c97c90bdd5f34b7b09ca5088db0c88621395bd9c.png) for all $ i $ $ (1<=i<=l-1) $ .

Given $ n $ and $ k $ find the number of good sequences of length $ k $ . As the answer can be rather large print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line of input contains two space-separated integers $ n,k (1<=n,k<=2000) $ .

## 输出格式

Output a single integer — the number of good sequences of length $ k $ modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample the good sequences are: $ [1,1],[2,2],[3,3],[1,2],[1,3] $ .

## 样例 #1

### 输入

```
3 2

```

### 输出

```
5

```

## 样例 #2

### 输入

```
6 4

```

### 输出

```
39

```

## 样例 #3

### 输入

```
2 1

```

### 输出

```
2

```

