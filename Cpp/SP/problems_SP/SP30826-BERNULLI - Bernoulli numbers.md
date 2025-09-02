---
title: "BERNULLI - Bernoulli numbers"
layout: "post"
diff: 难度0
pid: SP30826
tag: []
---

# BERNULLI - Bernoulli numbers

## 题目描述

$\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 是数学天才。

有一天，她想到这样一个题：求 $\ln |B_n|$，其中 $B_n$ 为 Bernoulli 数。

她觉得这个题太简单，就交给你来造数据了。

## 输入格式

输入若干行，每行一个正整数 $n$。

## 输出格式

对于每组数据，输出一个实数表示 $\ln |B_n|$。  
如果你的输出与答案的相对或绝对误差不超过 $10^{-15}$，则被视为正确。

## 说明/提示

对于 $100\%$ 的数据，$2 \le n < 2^{32}$，$n$ 为偶数，输入不超过 $1250000$ 个数。

【tips】  
Bernoulli 数的指数型生成函数为 
$$B(x)=\frac{x}{\text e^x-1}$$

## 样例 #1

### 输入

```
4
10
50
```

### 输出

```
-3,4011973816621553754132366916069
-2,580216829592325170273661603119
57,277060811865704087099873424857
Sample input and output are readable for your convenience!!! 
TL = 5 * My time
```

