---
title: "Remove the Bracket"
layout: "post"
diff: 普及+/提高
pid: CF1787C
tag: []
---

# Remove the Bracket

## 题目描述

RSJ 得到了一个长为 $n$ 的序列 $a_1,a_2, \ldots, a_n$ 和一个正整数 $s$，他想要计算 $\prod\limits_{i=1}^n a_i$。对于 $a_2,a_3, \ldots, a_{n-1}$ 中的每一个，他都选取了一对**非负整数** $x_i,y_i$ 使得 $x_i + y_i = a_i$ 且 $(x_i-s) \cdot (y_i-s) \geq 0$。他使用如下的方法计算：

$$
\begin{aligned}
\text{Product} &= a_1 \cdot a_2 \cdot a_3 \cdot \ldots \cdot a_n \\
&= a_1 \cdot (x_2+y_2) \cdot (x_3+y_3) \cdot (x_4 + y_4) \cdot \ldots \cdot (x_{n-1}+y_{n-1}) \cdot a_n \\
&\overset{\text{?}}{=} a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + y_4 \cdot \ldots \cdot x_{n-1}+y_{n-1} \cdot a_n
\end{aligned}
$$

但是他在计算时出现了错误，不小心把括号弄丢了（式子第 $3$ 行）。于是，他想要知道写错了的式子（$F = a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + y_4 \cdot \ldots \cdot x_{n-1}+y_{n-1} \cdot a_n$）的最小值是多少。

~~这是原本的题面，审核改成了现在的样子（真就 remove the bracket 了，导致赛时式子有歧义，在此向大家道歉~~


第二行 $n$ 个正整数 $a_1,a_2,\ldots,a_n$（$0 \le a_i \le 2 \cdot 10^5$）表示序列 $a$。

保证所有测试数据的 $n$ 之和不超过 $2\cdot 10^5$。

## 输入格式

输入第一行一个正整数 $t$（$1\le t\le 10^4$）表示数据组数。

## 输出格式

每组测试数据输出一行一个正整数表示 $F$ 的最小值。

### 样例解释

第一组测试数据中，$2\cdot 0+0\cdot 1+0\cdot 3+0\cdot 4 = 0$。

第二组测试数据中，$5\cdot 1+2\cdot 2+2\cdot 2+1\cdot 5 = 18$。

## 样例 #1

### 输入

```
10
5 0
2 0 1 3 4
5 1
5 3 4 3 5
7 2
7 6 5 4 3 2 1
5 1
1 2 3 4 5
5 2
1 2 3 4 5
4 0
0 1 1 1
5 5
4 3 5 6 4
4 1
0 2 1 0
3 99999
200000 200000 200000
6 8139
7976 129785 12984 78561 173685 15480
```

### 输出

```
0
18
32
11
14
0
16
0
40000000000
2700826806
```

