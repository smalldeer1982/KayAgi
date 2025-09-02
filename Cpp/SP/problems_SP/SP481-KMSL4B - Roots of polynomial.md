---
title: "KMSL4B - Roots of polynomial"
layout: "post"
diff: 难度0
pid: SP481
tag: []
---

# KMSL4B - Roots of polynomial

## 题目描述

$p(x)=p_k\times x^k + \dots + p_0 \times x^0$ 是一次数最高为 $20$ 的多项式。检查 $p()$ 的所有根在复平面中是否属于单位圆 $|z| <1$ 。

## 输入格式

第一行为测试数据组数。

接下来的各组数据，先给出次数 $k$ ，再在下一行给出系数 $p_0,p_1,\dots$  。

## 输出格式

对于每一个多项式，如果其所有根都在单位圆内，输出`1`，否则输出`0`。

## 样例 #1

### 输入

```
2
2
1 2 1
2
0.5 1 1
```

### 输出

```
0
1
```

