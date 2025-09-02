---
title: "Product transformation"
layout: "post"
diff: 提高+/省选-
pid: CF852F
tag: []
---

# Product transformation

## 题目描述

Consider an array $ A $ with $ N $ elements, all being the same integer $ a $ .

Define the product transformation as a simultaneous update $ A_{i}=A_{i}·A_{i+1} $ , that is multiplying each element to the element right to it for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852F/6fc715796ff6b053c1fbfce2cbd3ef15490be11e.png), with the last number $ A_{N} $ remaining the same. For example, if we start with an array $ A $ with $ a=2 $ and $ N=4 $ , then after one product transformation $ A=[4,\ 4,\ 4,\ 2] $ , and after two product transformations $ A=[16,\ 16,\ 8,\ 2] $ .

Your simple task is to calculate the array $ A $ after $ M $ product transformations. Since the numbers can get quite big you should output them modulo $ Q $ .

## 输入格式

The first and only line of input contains four integers $ N $ , $ M $ , $ a $ , $ Q $ ( $ 7<=Q<=10^{9}+123 $ , $ 2<=a<=10^{6}+123 $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852F/7bf3dc8dfd4f63cf153f6d6469587d6914d2f757.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852F/f742a70333572ee21e11b5a43ec5f0a2a3c5a39d.png) is prime), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852F/f742a70333572ee21e11b5a43ec5f0a2a3c5a39d.png) is the multiplicative order of the integer $ a $ modulo $ Q $ , see notes for definition.

## 输出格式

You should output the array $ A $ from left to right.

## 说明/提示

The multiplicative order of a number $ a $ modulo $ Q $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852F/f742a70333572ee21e11b5a43ec5f0a2a3c5a39d.png), is the smallest natural number $ x $ such that $ a^{x}\ mod\ Q=1 $ . For example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852F/0356983d0321626e54baaf7ca150cf5fcbe1dd67.png).

## 样例 #1

### 输入

```
2 2 2 7

```

### 输出

```
1 2 
```

