---
title: "Sereja and Dividing"
layout: "post"
diff: 省选/NOI-
pid: CF380E
tag: []
---

# Sereja and Dividing

## 题目描述

Let's assume that we have a sequence of doubles $ a_{1},a_{2},...,a_{|a|} $ and a double variable $ x $ . You are allowed to perform the following two-staged operation:

1. choose an index of the sequence element $ i $ $ (1<=i<=|a|) $ ;
2. consecutively perform assignments: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF380E/baffd80c48ee79165f910c02d82d94b1e032eff1.png).

Let's use function $ g(a,x) $ to represent the largest value that can be obtained from variable $ x $ , using the described operation any number of times and sequence $ a $ .

Sereja has sequence $ b_{1},b_{2},...,b_{|b|} $ . Help Sereja calculate sum: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF380E/61f426b3571521d30a29374c6c07cc3eb3b48dc9.png). Record $ [b_{i},b_{i+1},...,b_{j}] $ represents a sequence containing the elements in brackets in the given order. To avoid problems with precision, please, print the required sum divided by $ |b|^{2} $ .

## 输入格式

The first line contains integer $ |b| $ $ (1<=|b|<=3·10^{5}) $ — the length of sequence $ b $ . The second line contains $ |b| $ integers $ b_{1} $ , $ b_{2} $ , $ ... $ , $ b_{|b|} $ $ (1<=b_{i}<=10^{5}) $ .

## 输出格式

In a single line print a real number — the required sum divided by $ |b|^{2} $ . Your answer will be considered correct if its absolute or relative error won't exceed $ 10^{-6} $ .

## 样例 #1

### 输入

```
5
1 2 3 4 1

```

### 输出

```
1.238750000000000

```

