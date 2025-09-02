---
title: "PISANO - Modular Fibonacci Period"
layout: "post"
diff: 省选/NOI-
pid: SP13419
tag: []
---

# PISANO - Modular Fibonacci Period

## 题目描述

定义斐波那契数列：

- $F_0 = 0 , F_1 = 1$；
- $\forall i \geq 2 , F_i = F_{i-1} + F_{i-2}$。

给出 $T$ 组询问，每组询问给出正整数 $P$，试求出斐波那契数列在 $\bmod\ P$ 意义下的最小循环节，即找到最小的正整数 $m$ 满足 $F_m \equiv 0 (\bmod\ P) , F_{m+1} \equiv 1(\bmod\ P)$。

## 输入格式

第一行一个整数 $T$ 表示数据组数，接下来 $T$ 行每行一个整数 $P$。

## 输出格式

对于每组询问输出一行表示对应询问的最小循环节，如果不存在循环节则输出 `Not periodic.`。

## 说明/提示

$1 \leq T \leq 10^4$，$1 \leq P \leq 10^{12}$

## 样例 #1

### 输入

```
3
4
5
6
```

### 输出

```
6
20
24
```

