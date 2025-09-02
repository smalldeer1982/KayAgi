---
title: "Inna and Binary Logic"
layout: "post"
diff: 提高+/省选-
pid: CF400E
tag: []
---

# Inna and Binary Logic

## 题目描述

Inna is fed up with jokes about female logic. So she started using binary logic instead.

Inna has an array of $ n $ elements $ a_{1}[1],a_{1}[2],...,a_{1}[n] $ . Girl likes to train in her binary logic, so she does an exercise consisting of $ n $ stages: on the first stage Inna writes out all numbers from array $ a_{1} $ , on the $ i $ -th $ (i>=2) $ stage girl writes all elements of array $ a_{i} $ , which consists of $ n-i+1 $ integers; the $ k $ -th integer of array $ a_{i} $ is defined as follows: $ a_{i}[k]=a_{i-1}[k] AND a_{i-1}[k+1] $ . Here AND is bit-wise binary logical operation.

Dima decided to check Inna's skill. He asks Inna to change array, perform the exercise and say the sum of all ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF400E/150441d31156a32e0b2da63844d600138a543898.png) elements she wrote out during the current exercise.

Help Inna to answer the questions!

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n,m<=10^{5}) $ — size of array $ a_{1} $ and number of Dima's questions. Next line contains $ n $ integers $ a_{1}[1],a_{1}[2],...,a_{1}[n] $ $ (0<=a_{i}<=10^{5}) $ — initial array elements.

Each of next $ m $ lines contains two integers — Dima's question description. Each question consists of two integers $ p_{i},v_{i} $ $ (1<=p_{i}<=n; 0<=v_{i}<=10^{5}) $ . For this question Inna should make $ a_{1}[p_{i}] $ equals $ v_{i} $ , and then perform the exercise. Please, note that changes are saved from question to question.

## 输出格式

For each question print Inna's answer on a single line.

## 样例 #1

### 输入

```
3 4
1 1 1
1 1
2 2
3 2
1 2

```

### 输出

```
6
4
7
12

```

