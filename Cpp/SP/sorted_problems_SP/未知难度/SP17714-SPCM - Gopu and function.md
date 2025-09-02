---
title: "SPCM - Gopu and function"
layout: "post"
diff: 难度0
pid: SP17714
tag: []
---

# SPCM - Gopu and function

## 题目描述

有一天，Gopu 在阅读一道数学题，这道题中的函数 $f$ 看起来很奇怪，定义如下：

$$
f(n) = 
\begin{cases} 
1, & \text{如果 } n \text{ 是质数} \\
f(\text{质因数的总和}) + \text{不同质因数的个数}, & \text{否则}
\end{cases}
$$

给定一个整数 $n$，请你计算 $f(n)$ 的值。

## 输入格式

第一行是一个整数 $T$，表示测试用例的数量。（$1 \le T \le 20$）

接下来的每个测试用例包含一个整数 $n$。（$2 \le n \le 10^{12}$）

## 输出格式

对于每个测试用例，输出 $f(n)$ 的值，每个结果占一行。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6\n2\n3\n4\n5\n20\n123456&nbsp;
```

### 输出

```
\n1\n1\n2\n1\n3\n6
```

