---
title: "[AHC039A] Purse Seine Fishing"
layout: "post"
diff: 难度0
pid: AT_ahc039_a
tag: []
---

# [AHC039A] Purse Seine Fishing

## 题目描述

在一个二维平面上，给定 $N$ 条鲭鱼和 $N$ 条鯵鱼。你的任务是设计一个多边形，使得其内部包含的鲭鱼数量减去鯵鱼数量的差值最大。此外，位于多边形边界上的点也被视为在多边形内部。

## 输入格式

输入通过标准输入提供，格式如下：

> $ N $ $ x_0 $ $ y_0 $ $ \cdots $ $ x_{2N-1} $ $ y_{2N-1} $

- 所有测试用例均固定鲭鱼和鯵鱼的数量 $N$ 为 5000。
- 对于每个 $i=0,1,\cdots,N-1$，$(x_i,y_i)$ 为第 $i$ 条鲭鱼的坐标。
- 对于每个 $i=0,1,\cdots,N-1$，$(x_{N+i},y_{N+i})$ 为第 $i$ 条鯵鱼的坐标。
- 每个坐标 $(x_i,y_i)$ 满足 $0 \leq x_i, y_i \leq 10^5$，且所有坐标互不相同。

## 输出格式

输出一个多边形，它的顶点数为 $m$（$4 \leq m \leq 1000$）。设第 $i$ 个顶点的坐标为 $(a_i,b_i)$，请按以下格式打印到标准输出：

> $ m $ $ a_0 $ $ b_0 $ $ \cdots $ $ a_{m-1} $ $ b_{m-1} $

输出的顶点不必严格组成多边形的角度，即允许连续的三个顶点共线。但所有顶点坐标必须互不相同，顺序可以是顺时针或逆时针。

[查看示例](https://img.atcoder.jp/ahc039/KNtTkgAy.html?lang=ja&seed=0&output=sample)

可以多次输出解决方案，只有最后一次输出会被用于评分。利用 Web 版可视化工具可以对多个解进行比较。

## 说明/提示

### 条件

1. 多边形的顶点数不超过 1000，且边长的总和不超过 $4 \times 10^5$。
2. 每个顶点的坐标为整数并满足 $0 \leq x, y \leq 10^5$。
3. 每条边必须平行于 $x$ 轴或 $y$ 轴。
4. 多边形不能自交：非相邻边之间没有交点，相邻边之间只有一个公共顶点。

### 得分计算

假设输出的多边形内部包含的鲭鱼总数为 $a$，鯵鱼总数为 $b$，得分为 $\max(0, a-b+1)$。

### 输入数据生成方法

- $\mathrm{rand}(L,U)$：在 $L$ 到 $U$ 范围内生成一个整数。
- $\mathrm{rand\_double}(L,U)$：在 $L$ 到 $U$ 范围内生成一个实数。
- $\mathrm{normal}(\mu,\sigma)$：根据平均值 $\mu$ 和标准差 $\sigma$ 的正态分布生成一个随机实数。

首先生成鲭鱼的坐标。随机选择一个集群数量 $n = \mathrm{rand}(10, 25)$。对于每个集群 $i$，随机生成权重 $w_i = \mathrm{rand\_double}(0, 1)$，中心点 $(cx_i, cy_i) = (\mathrm{rand}(20000, 80000), \mathrm{rand}(20000, 80000))$ 和标准差 $\sigma_i = \mathrm{rand}(1000, 5000)$。重复生成 $N$ 条鲭鱼，每次根据权重随机选择一个集群，然后生成 $x = \mathrm{round}(\mathrm{normal}(cx_i, \sigma_i))$ 和 $y = \mathrm{round}(\mathrm{normal}(cy_i, \sigma_i))$。如果生成坐标满足条件且互不相同，则接��该坐标；否则重试。

鲭鱼生成完毕后，以同样的方法生成鯵鱼的坐标。

### 工具（输入生成器和可视化工具）

- [Web 版](https://img.atcoder.jp/ahc039/KNtTkgAy.html?lang=ja): 更高性能并支持动画显示。
- [本地版](https://img.atcoder.jp/ahc039/KNtTkgAy.zip): 需要 Rust 语言编译环境。
  - [Windows 版编译好的程序](https://img.atcoder.jp/ahc039/KNtTkgAy_windows.zip): 如果不想设置 Rust 环境，可以使用此版本。

比赛期间请勿分享可视化结果或讨论解法。

 **本翻译由 AI 自动生成**

