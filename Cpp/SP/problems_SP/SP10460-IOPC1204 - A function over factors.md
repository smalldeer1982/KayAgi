---
title: "IOPC1204 - A function over factors"
layout: "post"
diff: 省选/NOI-
pid: SP10460
tag: []
---

# IOPC1204 - A function over factors

## 题目描述

### $\mu (n)$ 为：
- 如果存在一个质数 $p$ 使得 $p^2$ 是 $n$ 的因子，则 $\mu (n)=0$。否则
- 如果 $n$ 有奇数个质因子，$\mu (n)=-1$。
- 否则，$\mu (n)=1$。

### $\displaystyle f(n)=\sum_{d \mid n} d μ(d)$，其中 $d$ 是 $n$ 的因数。

### 现在给出 $X$，求一个最小的 $n$，使得 $|f(n)|>X$。

## 输入格式

第一行，一个整数 $T$，表示有 $T$ 组数据。

接下来 $T$ 行，每行一个 $X$，意义如题所述。

## 输出格式

共 $T$ 行，每行对应一个 $X$。

## 样例 #1

### 输入

```
2
1
2
```

### 输出

```
3
5
```

