---
title: "Chopping Carrots (Easy Version)"
layout: "post"
diff: 普及/提高-
pid: CF1706D1
tag: ['数学']
---

# Chopping Carrots (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本间的区别仅为 $n$、$k$、$a_i$ 和 $\sum n$ 的上界。

注意不正常的空间限制。

给出长度为 $n$ 的整数数组 $ a_1, a_2, \ldots, a_n $，以及一个整数 $k$。

一个长度为 $n$ 的整数数组 $ p_1, p_2, \ldots, p_n $ 的花费为 $\max\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right) - \min\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right)$。
此处，$ \lfloor \frac{x}{y} \rfloor $ 表示 $x$ 除以 $y$ 的整数部分。
请找到花费最小的数组 $p$，且满足对任意 $ 1 \le i \le n$ 都有 $ 1 \le p_i \le k $。

## 输入格式

第一行包括一个整数 $t$（$ 1 \le t \le 100 $），表示接下来测试组的数量。

对于每一个测试组，第一行包括两个整数 $n$ 和 $k$（$ 1 \le n, k \le 3000 $）。

对于每一个测试组，第二行包括 $n$ 个整数 $ a_1, a_2, \ldots, a_n $（$ 1 \le a_1 \le a_2 \le \ldots \le a_n \le 3000 $）。

保证 $\sum n \le 3000$。

## 输出格式

对于每一个测试组，输出一个整数，表示满足上述条件的数组 $p$ 的花费的最小值。

## 样例 #1

### 样例输入 #1

```
7
5 2
4 5 6 8 11
5 12
4 5 6 8 11
3 1
2 9 15
7 3
2 3 5 5 6 9 10
6 56
54 286 527 1436 2450 2681
3 95
16 340 2241
2 2
1 3
```

### 样例输出 #1

```
2
0
13
1
4
7
0
```

## 说明/提示

在第一个测试组中，最优的数组是 $ p = [1, 1, 1, 2, 2] $。
$ \lfloor \frac{a_i}{p_i} \rfloor $ 得到的结果数组为 $ [4, 5, 6, 4, 5] $。
数组 $p$ 的花费为 $ \max\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) - \min\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) = 6 - 4 = 2 $。
可以证明，没有（满足题目条件的）数组的花费更小。

在第二个测试组中，最优的数组之一为 $ p = [12, 12, 12, 12, 12] $，它使得所有的 $ \lfloor \frac{a_i}{p_i} \rfloor $ 的值都为 $0$。

在第三个测试组中，唯一可能的数组为 $ p = [1, 1, 1] $。

## 样例 #1

### 输入

```
7
5 2
4 5 6 8 11
5 12
4 5 6 8 11
3 1
2 9 15
7 3
2 3 5 5 6 9 10
6 56
54 286 527 1436 2450 2681
3 95
16 340 2241
2 2
1 3
```

### 输出

```
2
0
13
1
4
7
0
```

