---
title: "Amr and The Large Array"
layout: "post"
diff: 普及/提高-
pid: CF558B
tag: []
---

# Amr and The Large Array

## 题目描述

Amr has got a large array of size $ n $ . Amr doesn't like large arrays so he intends to make it smaller.

Amr doesn't care about anything in the array except the beauty of it. The beauty of the array is defined to be the maximum number of times that some number occurs in this array. He wants to choose the smallest subsegment of this array such that the beauty of it will be the same as the original array.

Help Amr by choosing the smallest subsegment possible.

## 输入格式

The first line contains one number $ n $ ( $ 1<=n<=10^{5} $ ), the size of the array.

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=10^{6} $ ), representing elements of the array.

## 输出格式

Output two integers $ l,r $ ( $ 1<=l<=r<=n $ ), the beginning and the end of the subsegment chosen respectively.

If there are several possible answers you may output any of them.

## 说明/提示

A subsegment $ B $ of an array $ A $ from $ l $ to $ r $ is an array of size $ r-l+1 $ where $ B_{i}=A_{l+i-1} $ for all $ 1<=i<=r-l+1 $

## 样例 #1

### 输入

```
5
1 1 2 2 1

```

### 输出

```
1 5
```

## 样例 #2

### 输入

```
5
1 2 2 3 1

```

### 输出

```
2 3
```

## 样例 #3

### 输入

```
6
1 2 2 1 1 2

```

### 输出

```
1 5
```

