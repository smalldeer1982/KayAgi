---
title: "PERIOD2 - Periodic function, trip 2"
layout: "post"
diff: 难度0
pid: SP22270
tag: []
---

# PERIOD2 - Periodic function, trip 2

## 题目描述

米兰科维奇周期理论展示了多个周期函数的累积效应。通过轨道强迫，我们可以研究地球过去的气候变化模式。

![米兰科维奇循环 - 图片](../../content/francky:Milankovitch "http://en.wikipedia.org/wiki/Milankovitch_cycles")

## 输入格式

第一行输入一个整数 $T$，表示测试用例的数量。接下来的 $T$ 行中，每行包括两个整数 $N$ 和 $M$。对于每个用例，考虑所有周期为 $n$ 的函数，其周期 $n$ 在 $[1, N]$ 范围内。这些函数的和具有一个共同的最小周期。

## 输出格式

对于每组输入，输出这些函数族的最小公共周期。因为结果可能非常大，请输出它除以 $M$ 后的余数。

## 说明/提示

- $1 \le T \le 10^5$
- $1 \le N, M \le 10^9$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
2 10
3 100
4 7
```

### 输出

```
2
6
5
```

