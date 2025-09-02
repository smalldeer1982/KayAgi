---
title: "Bubble Cup hypothesis"
layout: "post"
diff: 省选/NOI-
pid: CF1423J
tag: []
---

# Bubble Cup hypothesis

## 题目描述

The Bubble Cup hypothesis stood unsolved for $ 130 $ years. Who ever proves the hypothesis will be regarded as one of the greatest mathematicians of our time! A famous mathematician Jerry Mao managed to reduce the hypothesis to this problem:

Given a number $ m $ , how many polynomials $ P $ with coefficients in set $ {\{0,1,2,3,4,5,6,7\}} $ have: $ P(2)=m $ ?

Help Jerry Mao solve the long standing problem!

## 输入格式

The first line contains a single integer $ t $ $ (1 \leq t \leq 5\cdot 10^5) $ - number of test cases.

On next line there are $ t $ numbers, $ m_i $ $ (1 \leq m_i \leq 10^{18}) $ - meaning that in case $ i $ you should solve for number $ m_i $ .

## 输出格式

For each test case $ i $ , print the answer on separate lines: number of polynomials $ P $ as described in statement such that $ P(2)=m_i $ , modulo $ 10^9 + 7 $ .

## 说明/提示

In first case, for $ m=2 $ , polynomials that satisfy the constraint are $ x $ and $ 2 $ .

In second case, for $ m=4 $ , polynomials that satisfy the constraint are $ x^2 $ , $ x + 2 $ , $ 2x $ and $ 4 $ .

## 样例 #1

### 输入

```
2
2 4
```

### 输出

```
2
4
```

