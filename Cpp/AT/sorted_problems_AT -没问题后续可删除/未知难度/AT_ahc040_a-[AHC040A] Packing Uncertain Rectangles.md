---
title: "[AHC040A] Packing Uncertain Rectangles"
layout: "post"
diff: 难度0
pid: AT_ahc040_a
tag: []
---

# [AHC040A] Packing Uncertain Rectangles

## 题目描述

给定 $N$ 个长方形，每个长方形的实际宽度为 $w_i$，高度为 $h_i$。由于观测误差，输入中提供的是 $w'_i = \mathrm{normal}(w_i, \sigma)$ 和 $h'_i = \mathrm{normal}(h_i, \sigma)$ 的值。这些值的生成方式如下：

1. 从均值为 $\mu$，标准差为 $\sigma$ 的正态分布中随机生成一个值。
2. 将该值四舍五入成整数。
3. 如果小于 1 则置为 1，大于 $10^9$ 则置为 $10^9$。

要求将这些长方形按照编号顺序放置于平面上，且不能重叠。长方形可以按需旋转 $90^\circ$，从而交换长宽。

问题的坐标系定义为：向右为 $x$ 轴正方向，向下为 $y$ 轴正方向。长方形需放置于 $x \geq 0$ 且 $y \geq 0$ 的区域，具体摆放方法用序列 $(p_0, r_0, d_0, b_0), (p_1, r_1, d_1, b_1), \dots$ 表示，其中：

- $p_i$ 表示第 $i$ 个放置的长方形编号（$0 \leq p_i \leq N-1$）。可以放置部分长方形，但编号必须递增，即 $i < j$ 必须满足 $p_i < p_j$。
- $r_i$ 表示是否旋转 $90^\circ$。$r_i = 0$ 表示不旋转，$r_i = 1$ 表示旋转。
- $d_i$ 指摆放方向：如果 $d_i$ 为 `U`，则自下而上移动，直至与其他长方形底边或 $y = 0$ 相接；若为 `L`，则自右向左移动，直至与其他长方形右边或 $x = 0$ 相接。
- $b_i$ 是长方形放置时的参考基准，需为 $-1$ 或已放置长方形的编号。
  - `U` 时，$b_i = -1$ 表示左边对齐 $x = 0$；其他值表示左边对齐指定长方形的右边。
  - `L` 时，$b_i = -1$ 表示上边对齐 $y = 0$；其他值表示上边对齐指定长方形的底边。

#### 操作示例

以下是将第3个长方形不旋转下的示例，分别展示在不同方向和基准条件下的放置结果（图片链接略）。

这些操作要重复 $T$ 次：

1. 每次开始时从空白状态重新指定放置方案。
2. 根据指定方案，计算所有长方形的最大宽度 $W$ 和最大高度 $H$。接着，给出测量结果 $W' = \mathrm{normal}(W, \sigma)$ 和 $H' = \mathrm{normal}(H, \sigma)$。

## 输入格式

首先输入长方形的数量 $N$、操作次数 $T$、测量误差标准差 $\sigma$ 及每个长方形的观测值 $w'_i, h'_i$，格式如下：

> $N$ $T$ $\sigma$ $w'_0$ $h'_0$ $\ldots$ $w'_{N-1}$ $h'_{N-1}$

其中：

- $30 \leq N \leq 100$
- $N/2 \leq T \leq 4N$
- $1000 \leq \sigma \leq 10000$

接下来，你要进行 $T$ 次操作。对于每次操作，输出长方形的放置方式 $(p_0, r_0, d_0, b_0), \ldots, (p_{n-1}, r_{n-1}, d_{n-1}, b_{n-1})$，输出格式为：

> $n$ $p_0$ $r_0$ $d_0$ $b_0$ $\ldots$ $p_{n-1}$ $r_{n-1}$ $d_{n-1}$ $b_{n-1}$

在每次输出放置信息后，从标准输入读取横宽和纵长的测量结果 $W'$ 和 $H'$：

> $W'$ $H'$

**输出后必须换行并刷新标准输出，否则可能导致TLE。**

## 说明/提示

在第 $t$ 次摆放中，定义横宽为 $W_t$，纵长为 $H_t$，未使用的长方形集合为 $U_t$。第 $t$ 次得分 $s_t$ 定义为：

\[ s_t = W_t + H_t + \sum_{i \in U_t} (w_i + h_i) \]

目标是最小化所有 $s_t$ 中的最小值。得出绝对分数后，根据公式计算相对分数，该分数用于评分。

请注意，系统测试仅对最后一次提交进行，因此请确保最终提交正确无误。

### 示例程序

以下是 Python 示例程序，该程序随机选取每个长方形的旋转、位置试图找到最优解：

```python
import random

def query(prdb):
    print(len(prdb))
    for p, r, d, b in prdb:
        print(p, r, d, b)
    W, H = map(int, input().split())
    return W, H

N, T, sigma = map(int, input().split())
wh = [tuple(map(int, input().split())) for _ in range(N)]

rng = random.Random(1234)

for _ in range(T):
    prdb = []
    for i in range(N):
        prdb.append((
            i,
            rng.randint(0, 1),
            ['U', 'L'][rng.randint(0, 1)],
            rng.randint(-1, i - 1),
        ))
    query(prdb)
```

 **本翻译由 AI 自动生成**

