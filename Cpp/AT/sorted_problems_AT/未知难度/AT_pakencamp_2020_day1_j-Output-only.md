---
title: "Output-only"
layout: "post"
diff: 难度0
pid: AT_pakencamp_2020_day1_j
tag: []
---

# Output-only

## 题目描述

请生成 $10^5$ 个直角三角形。

具体地，设第 $i$ 个直角三角形的两直角边长分别为 $a_i,b_i$，斜边长为 $c_i$，则 $\forall\ i\in [1,10^5]\bigcap \N*$：

> - $a_i,b_i,c_i\in \N*$；
>
> - $1\le a_i\le b_i\le c_i\le 10^{18}$;
>
> - $a^2+b^2=c^2$；
>
> - $\gcd(a_i,b_i,c_i)=1$；
> 
> - $\forall\ j\in [1,10^5]\bigcap \N*$，若 $i\neq j$，则 $(a_i,b_i,c_i)\neq (a_j,b_j,c_j)$。

你需要输出 $10^5$ 个三元组，第 $i$ 个三元组即为你生成的第 $i$ 个直角三角形的三边长 $(a_i,b_i,c_i)$，满足题目条件。

## 输入格式

本题无输入。

## 输出格式

输出 $10^5$ 行，第 $i$ 行输出的三个整数 $a_i,b_i,c_i$ 表示你生成的第 $i$ 个直角三角形的三边长。你需要保证任意两个你输出的三角形都不相似。

## 样例 #1

### 输入

```
None
```

### 输出

```
3 4 5
5 12 13
8 15 17
```

