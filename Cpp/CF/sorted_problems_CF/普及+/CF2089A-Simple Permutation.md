---
title: "Simple Permutation"
layout: "post"
diff: 普及+/提高
pid: CF2089A
tag: ['数学', '构造']
---

# Simple Permutation

## 题目描述

给定一个整数 $n$。构造一个长度为 $n$ 的排列 $p_1, p_2, \ldots, p_n$，使其满足以下性质：

对于 $1 \le i \le n$，定义 $c_i = \lceil \frac{p_1 + p_2 + \ldots + p_i}{i} \rceil$，那么在 $c_1, c_2, \ldots, c_n$ 中必须至少有 $\lfloor \frac{n}{3} \rfloor - 1$ 个素数。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10$）——测试用例的数量。接下来描述每个测试用例。

每个测试用例的一行中包含一个整数 $n$（$2 \le n \le 10^5$）——排列的大小。

## 输出格式

对于每个测试用例，输出满足条件的排列 $p_1, p_2, \ldots, p_n$。题目保证这样的排列总是存在。

## 说明/提示

第一个测试案例中，$c_1 = \lceil \frac{2}{1} \rceil = 2$，$c_2 = \lceil \frac{2+1}{2} \rceil = 2$。这两个数都是素数。

第三个测试案例中，$c_1 = \lceil \frac{2}{1} \rceil = 2$，$c_2 = \lceil \frac{3}{2} \rceil = 2$，$c_3 = \lceil \frac{6}{3} \rceil = 2$，$c_4 = \lceil \frac{10}{4} \rceil = 3$，$c_5 = \lceil \frac{15}{5} \rceil = 3$。所有这些数都是素数。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
2
3
5
```

### 输出

```
2 1
2 1 3
2 1 3 4 5
```

