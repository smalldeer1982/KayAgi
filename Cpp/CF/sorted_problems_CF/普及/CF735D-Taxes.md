---
title: "Taxes"
layout: "post"
diff: 普及/提高-
pid: CF735D
tag: ['数学', '素数判断,质数,筛法']
---

# Taxes

## 题目描述

Mr. Funt now lives in a country with a very specific tax laws. The total income of mr. Funt during this year is equal to $ n $ ( $ n>=2 $ ) burles and the amount of tax he has to pay is calculated as the maximum divisor of $ n $ (not equal to $ n $ , of course). For example, if $ n=6 $ then Funt has to pay $ 3 $ burles, while for $ n=25 $ he needs to pay $ 5 $ and if $ n=2 $ he pays only $ 1 $ burle.

As mr. Funt is a very opportunistic person he wants to cheat a bit. In particular, he wants to split the initial $ n $ in several parts $ n_{1}+n_{2}+...+n_{k}=n $ (here $ k $ is arbitrary, even $ k=1 $ is allowed) and pay the taxes for each part separately. He can't make some part equal to $ 1 $ because it will reveal him. So, the condition $ n_{i}>=2 $ should hold for all $ i $ from $ 1 $ to $ k $ .

Ostap Bender wonders, how many money Funt has to pay (i.e. minimal) if he chooses and optimal way to split $ n $ in parts.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=2·10^{9} $ ) — the total year income of mr. Funt.

## 输出格式

Print one integer — minimum possible number of burles that mr. Funt has to pay as a tax.

## 样例 #1

### 输入

```
4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
27

```

### 输出

```
3

```

