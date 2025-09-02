---
title: "GCDEX - GCD Extreme"
layout: "post"
diff: 提高+/省选-
pid: SP3871
tag: ['数学', '素数判断,质数,筛法', '最大公约数 gcd']
---

# GCDEX - GCD Extreme

## 题目描述

得定 $n$ ，求
$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中 $\gcd(i,j)$ 指的是 $i$ 和 $j$ 的最大公约数。

## 输入格式

**本题有多组数据。**

对于每组数据，输出一个整数 $n$ ，如果 $n=0$ 就终止程序。

## 输出格式

对于每组数据，输出计算结果。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 10^6$，不超过 $20000$ 组数据。

## 样例 #1

### 输入

```
10
100
200000
0
```

### 输出

```
67
13015
143295493160

Time limit has been changed. Some AC solutions get TLE
```

