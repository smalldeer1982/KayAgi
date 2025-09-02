---
title: "Shifting"
layout: "post"
diff: 提高+/省选-
pid: CF286B
tag: []
---

# Shifting

## 题目描述

John Doe has found the beautiful permutation formula.

Let's take permutation $ p=p_{1},p_{2},...,p_{n} $ . Let's define transformation $ f $ of this permutation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF286B/25e74201607d55d0e22ffd7930ca53b5830fbc7a.png)where $ k $ $ (k&gt;1) $ is an integer, the transformation parameter, $ r $ is such maximum integer that $ rk<=n $ . If $ rk=n $ , then elements $ p_{rk+1},p_{rk+2} $ and so on are omitted. In other words, the described transformation of permutation $ p $ cyclically shifts to the left each consecutive block of length $ k $ and the last block with the length equal to the remainder after dividing $ n $ by $ k $ .

John Doe thinks that permutation $ f(f( ... f(p=[1,2,...,n],2) ... ,n-1),n) $ is beautiful. Unfortunately, he cannot quickly find the beautiful permutation he's interested in. That's why he asked you to help him.

Your task is to find a beautiful permutation for the given $ n $ . For clarifications, see the notes to the third sample.

## 输入格式

A single line contains integer $ n $ ( $ 2<=n<=10^{6} $ ).

## 输出格式

Print $ n $ distinct space-separated integers from $ 1 $ to $ n $ — a beautiful permutation of size $ n $ .

## 说明/提示

A note to the third test sample:

- $ f([1,2,3,4],2)=[2,1,4,3] $
- $ f([2,1,4,3],3)=[1,4,2,3] $
- $ f([1,4,2,3],4)=[4,2,3,1] $

## 样例 #1

### 输入

```
2

```

### 输出

```
2 1 

```

## 样例 #2

### 输入

```
3

```

### 输出

```
1 3 2 

```

## 样例 #3

### 输入

```
4

```

### 输出

```
4 2 3 1 

```

