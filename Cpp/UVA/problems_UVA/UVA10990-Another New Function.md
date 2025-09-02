---
title: "Another New Function"
layout: "post"
diff: 难度0
pid: UVA10990
tag: []
---

# Another New Function

## 题目描述

函数 $\varphi(x)$ 是人所共知的一种函数，因此这里不作论述。

并且，对于任意整数 $n$，不断地取它的 $\varphi$ 值并赋值之，可以得到 $1$，这个取 $\varphi$ 的次数我们记作 $\phi(n)$。

而后，我们定义一个函数（这里 $m\le n$）

$$\psi(m,n)=\sum_{k=m}^n\phi(k)$$

你的任务是求 $\psi(m,n)$ 的值。

## 输入格式

$T(1\le T\le2000)$ 组数据，每组数据两个整数 $m,n(2\le m\le n\le 2\times10^6)$。

## 输出格式

对于每组数据，输出 $\psi(m,n)$。

## 样例 #1

### 输入

```
2
2 10
100000 200000
```

### 输出

```
22
1495105
```

