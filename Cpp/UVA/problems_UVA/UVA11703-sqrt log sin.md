---
title: "sqrt log sin"
layout: "post"
diff: 入门
pid: UVA11703
tag: []
---

# sqrt log sin

## 题目描述

## 题目背景

![](https://cdn.luogu.org/upload/pic/49652.png)

一个珂怕的教授让你做这道题：

$$x_0 = 1$$
$$x_i = x_{\left\lfloor i - \sqrt x \right\rfloor} + x_{\left\lfloor\ln(i)\right\rfloor} + x_{\left\lfloor i\sin^2 (i) \right\rfloor}$$

求$x_i \bmod 10^6$的值。

## 输入格式

输入包含很多个在$[0,10^6]$之间整数，每行一个整数。用$-1$表示输入结束。

## 输出格式

对于每个输入$i$，你应该输出单独的一行，表示$x_i \bmod 10^6$的值。

## 样例 #1

### 输入

```
0
-1
```

### 输出

```
1
```

