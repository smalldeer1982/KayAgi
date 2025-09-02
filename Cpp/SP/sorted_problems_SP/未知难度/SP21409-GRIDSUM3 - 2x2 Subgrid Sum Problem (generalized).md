---
title: "GRIDSUM3 - 2x2 Subgrid Sum Problem (generalized)"
layout: "post"
diff: 难度0
pid: SP21409
tag: []
---

# GRIDSUM3 - 2x2 Subgrid Sum Problem (generalized)

## 题目描述

本题是 [KWACIK](http://pl.spoj.com/problems/KWACIK/)（波兰语）和 [GRIDSUM2](../GRIDSUM2/) 问题的广义高约束版本。

![示例：k=5, a=1, b=3, n=8 的情况。](../../../content/min_25:grid_5x5.png "示例：k=5, a=1, b=3, n=8 的情况。")

给定一个 $k \times k$ 的网格。在每个网格单元中，你可以放置一个整数 $m$，并且 $a \le m \le b$。

现在的问题是，要求出将整数放置在网格中的所有可能方法，使得每个 $2 \times 2$ 的子网格中的整数和为 $n$。

由于结果可能非常大，请输出方法数对 $479001600$ （即等于 $12!$）取模的值。

## 输入格式

第一行输入一个整数 $T$，表示测试用例的数量（$1 \le T \le 10^5$）。

接下来的 $T$ 行中，每行包含四个整数 $k$、$a$、$b$ 和 $n$。

其中，$2 \le k \le 1000$，$1 \le a \le b \le 10^9$，$1 \le n \le 10^9$。

## 输出格式

对于每个测试用例，输出一个整数，即满足条件的方法数对 $479001600$ 取模后的结果。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
2 1 2 4
3 1 2 5
4 1 3 6
5 1 3 8
```

### 输出

```
1
8
74
1383
```

