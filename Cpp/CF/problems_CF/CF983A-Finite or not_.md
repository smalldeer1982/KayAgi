---
title: "Finite or not?"
layout: "post"
diff: 普及/提高-
pid: CF983A
tag: ['数学', '最大公约数 gcd', '进制']
---

# Finite or not?

## 题目描述

有 $n$ 组数据，每一组数据读入一个分数的分子 $p$、分母 $q$ 和进制 $b$（分子、分母均以十进制读入）求在 $b$ 进制下 $\frac{p}{q}$ 是否为有限小数。如果是，输出 `Finite`，否则输出 `Infinite`

## 输入格式

第一行输入 $n$

接下来 $n$ 行输入 $p$, $q$ 和 $b$。

## 输出格式

对于每一组数据，输出 `Finite` 或 `Infinite`

1 <= n <= 10^5, 1 <= b, p, q <= 10^18

由 @Medoric 提供翻译

## 样例 #1

### 输入

```
2
6 12 10
4 3 10

```

### 输出

```
Finite
Infinite

```

## 样例 #2

### 输入

```
4
1 1 2
9 36 2
4 12 3
3 5 4

```

### 输出

```
Finite
Finite
Finite
Infinite

```

