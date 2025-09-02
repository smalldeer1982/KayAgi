---
title: "Row GCD"
layout: "post"
diff: 普及+/提高
pid: CF1458A
tag: []
---

# Row GCD

## 题目描述

You are given two positive integer sequences $ a_1, \ldots, a_n $ and $ b_1, \ldots, b_m $ . For each $ j = 1, \ldots, m $ find the greatest common divisor of $ a_1 + b_j, \ldots, a_n + b_j $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^{18}) $ .

The third line contains $ m $ integers $ b_1, \ldots, b_m $ ( $ 1 \leq b_j \leq 10^{18}) $ .

## 输出格式

Print $ m $ integers. The $ j $ -th of them should be equal to GCD $ (a_1 + b_j, \ldots, a_n + b_j) $ .

## 样例 #1

### 输入

```
4 4
1 25 121 169
1 2 7 23
```

### 输出

```
2 3 8 24
```

