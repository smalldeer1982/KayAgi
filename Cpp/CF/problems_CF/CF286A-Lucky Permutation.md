---
title: "Lucky Permutation"
layout: "post"
diff: 普及/提高-
pid: CF286A
tag: []
---

# Lucky Permutation

## 题目描述

A permutation $ p $ of size $ n $ is the sequence $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct integers, each of them is from $ 1 $ to $ n $ $ (1<=p_{i}<=n) $ .

A lucky permutation is such permutation $ p $ , that any integer $ i $ $ (1<=i<=n) $ meets this condition $ p_{pi}=n-i+1 $ .

You have integer $ n $ . Find some lucky permutation $ p $ of size $ n $ .

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the required permutation size.

## 输出格式

Print "-1" (without the quotes) if the lucky permutation $ p $ of size $ n $ doesn't exist.

Otherwise, print $ n $ distinct integers $ p_{1},p_{2},...,p_{n} $ $ (1<=p_{i}<=n) $ after a space — the required permutation.

If there are multiple answers, you can print any of them.

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
-1

```

## 样例 #3

### 输入

```
4

```

### 输出

```
2 4 1 3 

```

## 样例 #4

### 输入

```
5

```

### 输出

```
2 5 3 1 4 

```

