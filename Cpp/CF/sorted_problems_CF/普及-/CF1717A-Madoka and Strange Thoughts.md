---
title: "Madoka and Strange Thoughts"
layout: "post"
diff: 普及-
pid: CF1717A
tag: ['数论']
---

# Madoka and Strange Thoughts

## 题目描述

给定一个整数 $n$，求出有多少组满足条件的 $\left ( a, b\right) (1 \le a, b \le n)$，使得 $\frac{\operatorname{lcm}(a, b) }{\gcd(a, b) } \le 3$。

在该题目中，$\gcd(a, b)$ 指的是 $a$ 和 $b$ 的最大公约数，而 $lcm(a, b)$ 指的是 $a$ 和 $b$ 的最小公倍数。

## 输入格式

第一行输入一个整数 $t(1 \le t \le 10^4)$，代表测试数据的组数。

接下来 $t$ 行，每行一个整数 $n(1 \le n \le 10^8)$，代表题目中的整数 $n$。

## 输出格式

对于每个测试数据，输出一个整数，代表满足条件的 $(a, b)$ 的数量。

## 样例 #1

### 输入

```
6
1
2
3
4
5
100000000
```

### 输出

```
1
4
7
10
11
266666666
```

