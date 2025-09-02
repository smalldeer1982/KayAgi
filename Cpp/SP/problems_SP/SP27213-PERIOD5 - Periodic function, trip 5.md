---
title: "PERIOD5 - Periodic function, trip 5"
layout: "post"
diff: 难度0
pid: SP27213
tag: []
---

# PERIOD5 - Periodic function, trip 5

## 题目描述

太阳活动周期的预测对多个机构和行业团体非常重要，因为它能直接影响低地球轨道卫星的寿命。这是由于卫星受到的空气阻力与太阳活动周期密切相关 \[...\]。[(NOAA)](http://www.swpc.noaa.gov/products/solar-cycle-progression)

![400年太阳黑子观测历史](../../content/francky:Sun400 "400年太阳黑子观测历史")[(太阳活动周期)](http://en.wikipedia.org/wiki/Solar_cycle)

## 输入格式

第一行输入一个整数 $N$。第二行输入 $N \times N$ 个整数 $y$，这些是某个周期函数 $f$ 的前 $N \times N$ 个值，由多个周期函数相加得到的函数，且这些函数的最大周期都不超过 $N$。第三行输入 $N \times N$ 个整数 $x$。

## 输出格式

输出每一个给定 $x$ 对应的 $f(x)$ 值，具体参见范例。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
15 3 17 2 16 4 15 3 17
10 100 1000 10000 100000 1000000 10000000 100000000 1000000000
```

### 输出

```
16 16 16 16 16 16 16 16 16
```

