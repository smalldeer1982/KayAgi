---
title: "Interesting Ratio"
layout: "post"
diff: 普及/提高-
pid: CF2091E
tag: ['数论', '素数判断,质数,筛法']
---

# Interesting Ratio

## 题目描述

最近，Misha 在 IT Campus "NEIMARK" 的夏令营中学习了新课题 —— 欧几里得算法。

当发现 $a \cdot b = \text{lcm}(a, b) \cdot \text{gcd}(a, b)$ 时，他有些惊讶。其中 $\text{gcd}(a, b)$ 是 $a$ 和 $b$ 的[最大公约数 (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor)，而 $\text{lcm}(a, b)$ 是[最小公倍数 (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple)。Misha 想到既然 LCM 和 GCD 的乘积存在，或许它们的商也值得研究：$F(a, b) = \frac{\text{lcm}(a, b)}{\text{gcd}(a, b)}$。

例如，他取 $a = 2$ 和 $b = 4$，计算得到 $F(2, 4) = \frac{4}{2} = 2$，结果是一个质数（一个数如果恰好有两个因数则为质数）！现在他认为当 $a < b$ 且 $F(a, b)$ 是质数时，这个比值 $F(a, b)$ 是"有趣的比值"。

由于 Misha 刚接触数论，他需要你帮忙计算 —— 满足 $F(a, b)$ 是"有趣的比值"且 $1 \leq a < b \leq n$ 的不同数对 $(a, b)$ 有多少个？

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ($1 \leq t \leq 10^3$)。接下来是每个测试用例的描述。

每个测试用例单独一行，包含一个整数 $n$ ($2 \leq n \leq 10^7$)。

保证所有测试用例的 $n$ 之和不超过 $10^7$。


## 输出格式

对于每个测试用例，输出满足条件 $1 \leq a < b \leq n$ 的"有趣比值" $F(a, b)$ 的数量。


## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
5
10
34
10007
```

### 输出

```
4
11
49
24317
```

