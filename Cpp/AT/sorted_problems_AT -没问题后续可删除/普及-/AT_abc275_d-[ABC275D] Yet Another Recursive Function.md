---
title: "[ABC275D] Yet Another Recursive Function"
layout: "post"
diff: 普及-
pid: AT_abc275_d
tag: []
---

# [ABC275D] Yet Another Recursive Function

## 题目描述

定义函数 $f(x)$ 有如下定义

- $ f(0)\ =\ 1 $
- 对于任意正整数 $k$ 有 $f(k)\ = f(\lfloor\frac{k}{2}\rfloor)\ +\ f(\lfloor\frac{k}{3}\rfloor) $

$ \lfloor A\rfloor $ 代表小于等于 $A$ 的最大整数。

求 $f(x)$。

## 输入格式

一个整数。

> $ N $

## 输出格式

一行，一个整数，代表 $f(N)$ 的值。

## 样例 #1

### 样例输入 #1

```
2
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
0
```

### 样例输出 #2

```
1
```

## 样例 #3

### 样例输入 #3

```
100
```

### 样例输出 #3

```
55
```

## 说明/提示

- $ 0\ \le\ N\ \le\ 10^{18} $

### 样例一解释

$ f(2)\ =\ f(\lfloor\frac{2}{2}\rfloor)\ +\ f(\lfloor\frac{2}{3}\rfloor)\ =\ f(1)\ +\ f(0)\ =(f(\lfloor\frac{1}{2}\rfloor)\ +\ f(\lfloor\frac{1}{3}\rfloor))\ +\ f(0)\ =(f(0)+f(0))\ +\ f(0)=\ 3 $。

## 样例 #1

### 输入

```
2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
100
```

### 输出

```
55
```

