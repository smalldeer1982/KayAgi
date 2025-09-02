---
title: "Iterated Linear Function"
layout: "post"
diff: 提高+/省选-
pid: CF678D
tag: []
---

# Iterated Linear Function

## 题目描述

Consider a linear function $ f(x)=Ax+B $ . Let's define $ g^{(0)}(x)=x $ and $ g^{(n)}(x)=f(g^{(n-1)}(x)) $ for $ n&gt;0 $ . For the given integer values $ A $ , $ B $ , $ n $ and $ x $ find the value of $ g^{(n)}(x) $ modulo $ 10^{9}+7 $ .

## 输入格式

The only line contains four integers $ A $ , $ B $ , $ n $ and $ x $ ( $ 1<=A,B,x<=10^{9},1<=n<=10^{18} $ ) — the parameters from the problem statement.

Note that the given value $ n $ can be too large, so you should use $ 64 $ -bit integer type to store it. In C++ you can use the long long integer type and in Java you can use long integer type.

## 输出格式

Print the only integer $ s $ — the value $ g^{(n)}(x) $ modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
3 4 1 1

```

### 输出

```
7

```

## 样例 #2

### 输入

```
3 4 2 1

```

### 输出

```
25

```

## 样例 #3

### 输入

```
3 4 3 1

```

### 输出

```
79

```

