---
title: "Math Division"
layout: "post"
diff: 普及+/提高
pid: CF2081A
tag: ['动态规划 DP', '概率论']
---

# Math Division

## 题目描述

Ecrade 有一个整数 $x$。他将以长度为 $n$ 的二进制数的形式向你展示这个数。

存在两种操作：
1. 将 $x$ 替换为 $\left\lfloor \frac{x}{2}\right\rfloor$，其中 $\left\lfloor \frac{x}{2}\right\rfloor$ 是小于等于 $\frac{x}{2}$ 的最大整数。
2. 将 $x$ 替换为 $\left\lceil \frac{x}{2}\right\rceil$，其中 $\left\lceil \frac{x}{2}\right\rceil$ 是大于等于 $\frac{x}{2}$ 的最小整数。

Ecrade 将执行若干次操作直到 $x$ 变为 $1$。每次操作时，他会独立地以 $\frac{1}{2}$ 的概率选择执行第一种操作或第二种操作。

Ecrade 想知道他将执行的操作次数的期望值（模 $10^9 + 7$）。由于问题有一定难度，请你帮助他！

## 输入格式

第一行输入一个整数 $t$（$1 \le t \le 10^5$）——测试用例数量。接下来描述每个测试用例。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 10^5$）——$x$ 的二进制表示长度。

每个测试用例的第二行包含一个长度为 $n$ 的二进制字符串：表示 $x$ 的二进制形式，从最高有效位到最低有效位给出。保证 $x$ 的最高有效位为 $1$。

保证所有测试用例的 $n$ 总和不超过 $10^5$。

## 输出格式

对于每个测试用例，输出一个整数表示 Ecrade 将执行的操作次数的期望值（模 $10^9 + 7$）。

形式化地，令 $M = 10^9 + 7$。可以证明精确答案可以表示为不可约分数 $\dfrac{p}{q}$，其中 $p$ 和 $q$ 为整数且 $q \not \equiv 0 \pmod{M}$。请输出 $p \cdot q^{-1} \bmod M$。换句话说，输出满足 $0 \le x < M$ 且 $x \cdot q \equiv p \pmod{M}$ 的整数 $x$。

## 说明/提示

为简化描述，我们将第一种操作称为 $\text{OPER 1}$，第二种操作称为 $\text{OPER 2}$。

第一个测试用例中，$x=6$，存在六种可能的操作序列：
- $6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{4}$。
- $6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{8}$。
- $6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 2}} 1$，概率为 $\dfrac{1}{8}$。
- $6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{4}$。
- $6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{8}$。
- $6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 2}} 1$，概率为 $\dfrac{1}{8}$。

因此，操作次数的期望为 $2 \cdot \dfrac{1}{4} + 3 \cdot \dfrac{1}{8} + 3 \cdot \dfrac{1}{8} + 2 \cdot \dfrac{1}{4} + 3 \cdot \dfrac{1}{8} + 3 \cdot \dfrac{1}{8} = \dfrac{5}{2} \equiv 500\,000\,006 \pmod{10^9 + 7}$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
3
110
3
100
10
1101001011
```

### 输出

```
500000006
2
193359386
```

