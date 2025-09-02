---
title: "Modular Exponentiation"
layout: "post"
diff: 入门
pid: CF913A
tag: ['模拟']
---

# Modular Exponentiation

## 题目描述

The following problem is well-known: given integers $ n $ and $ m $ , calculate

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913A/73fb55a49ff8c4211b34696969c8aef5090c1d6d.png), where $ 2^{n}=2·2·...·2 $ ( $ n $ factors), and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913A/b0d2851c9c5ab36f8f15a3eac416cac07be09dd3.png) denotes the remainder of division of $ x $ by $ y $ .

You are asked to solve the "reverse" problem. Given integers $ n $ and $ m $ , calculate

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913A/d4dceae314a5c8428af0d75bf92415449f36c7d5.png).

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=10^{8} $ ).

The second line contains a single integer $ m $ ( $ 1<=m<=10^{8} $ ).

## 输出格式

Output a single integer — the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913A/d4dceae314a5c8428af0d75bf92415449f36c7d5.png).

## 说明/提示

In the first example, the remainder of division of 42 by $ 2^{4}=16 $ is equal to 10.

In the second example, 58 is divisible by $ 2^{1}=2 $ without remainder, and the answer is 0.

## 样例 #1

### 输入

```
4
42

```

### 输出

```
10

```

## 样例 #2

### 输入

```
1
58

```

### 输出

```
0

```

## 样例 #3

### 输入

```
98765432
23456789

```

### 输出

```
23456789

```

