---
title: "HLPRSRCH - Help a researcher"
layout: "post"
diff: 难度0
pid: SP7772
tag: []
---

# HLPRSRCH - Help a researcher

## 题目描述

一位科学家正在研究某种细菌。他发现这些细菌需要经过 **T** 单位时间才能够成熟并开始繁殖。此外，这些细菌每隔 **T** 个单位时间会以恒定的速率产生 **N** 个新细菌。

### 任务

请编写一个程序，输入以下数据：
- **L**：实验开始时的细菌总数
- **M**：其中已经成熟的细菌数量
- **T**：细菌成熟所需的时间，同时也是繁殖 **N** 个新细菌所需的时间
- **N**：每 **T** 单位时间所繁殖的新细菌数量
- **Z**：实验经过的总时间

要求计算在 **Z** 单位时间后细菌的总数，忽略细菌寿命因素。

## 输入格式

- **L**（实验初始时的细菌总数）
- **M**（初始时成熟的细菌数量）
- **T**（细菌成熟及每次繁殖所需的单位时间）
- **N**（每 **T** 单位时间的繁殖数量）
- **Z**（实验持续的总时间）

## 输出格式

- 经过 **Z** 单位时间后的细菌总数。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n3\n2\n3\n1\n3\n\n
```

### 输出

```
\n5\n\nThe experiment begins with 2 mature bacteria and one unmature bacterium.\nFor, each of the mature bacteria reproduces after 3 units of time.\nThen th total becomes 4 -as each one got a new one (2*2)-.\nBut, for the unmature bacterium after 3 units of time, it only become mature.\nAfter all of that the experiment finishes with 5 bacteria.\n\n\nInput\n2\n0\n1\n1\n100\n\nOutput:\n1146295688027634168202\n\n
```

