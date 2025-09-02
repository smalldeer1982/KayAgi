---
title: "Cave Painting"
layout: "post"
diff: 普及/提高-
pid: CF922C
tag: []
---

# Cave Painting

## 题目描述

Imp is watching a documentary about cave painting.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922C/492e738c81624c946c2f042260b850d1eaf30603.png)Some numbers, carved in chaotic order, immediately attracted his attention. Imp rapidly proposed a guess that they are the remainders of division of a number $ n $ by all integers $ i $ from $ 1 $ to $ k $ . Unfortunately, there are too many integers to analyze for Imp.

Imp wants you to check whether all these remainders are distinct. Formally, he wants to check, if all ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922C/39f2e5c509199205284370aee9d1f8146afae4b5.png), $ 1<=i<=k $ , are distinct, i. e. there is no such pair $ (i,j) $ that:

- $ 1 \leq i < j \leq k $ ,
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922C/ac7c31555d5d75a7ddeca570475f6120983c1d66.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922C/a2ab7eb81b242742b5775a80b9ed4a6c9876ed81.png) is the remainder of division $ x $ by $ y $ .

## 输入格式

The only line contains two integers $ n $ , $ k $ $ (1<=n,k<=10^{18}) $ .

## 输出格式

Print "Yes", if all the remainders are distinct, and "No" otherwise.

You can print each letter in arbitrary case (lower or upper).

## 说明/提示

In the first sample remainders modulo $ 1 $ and $ 4 $ coincide.

## 样例 #1

### 输入

```
4 4

```

### 输出

```
No

```

## 样例 #2

### 输入

```
5 3

```

### 输出

```
Yes

```

