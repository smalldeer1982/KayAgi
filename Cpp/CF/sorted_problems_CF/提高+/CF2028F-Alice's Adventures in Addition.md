---
title: "Alice's Adventures in Addition"
layout: "post"
diff: 提高+/省选-
pid: CF2028F
tag: ['动态规划 DP', '标签465']
---

# Alice's Adventures in Addition

## 题目描述

**注意不寻常的空间限制。**

柴郡猫给爱丽丝出了一个题：给定 $n$ 个整数 $a_1,a_2,\dots,a_n$ 和一个整数 $m$，能否在以下等式的 $\circ $ 中放入 $+$ 和 $\times$ 使得等式成立：

$$
a_1 \circ a_2 \circ \cdots \circ a_n = m
$$

我们遵循通常的运算顺序：$\times$ 在 $+$ 之前进行。

虽然爱丽丝的象棋下得很好，但她的数学却不好。请帮帮她，让她找到离开仙境的方法！

## 输入格式

每个测试点内有多组数据，第一行一个整数 $t$，表示数据组数。

接下来 $t$ 组数据，对于每组数据：

## 输出格式

对于每组数据，输出一行一个 `YES` 或 `NO` 表示答案，大小写均可。

## 说明/提示

$1\le t\le 10^4$，$1\le n\le \sum n\le 2\times 10^5$，$1\le m\le 10^4$，$0\le a_i\le 10^4$。

## 样例 #1

### 输入

```
6
5 4
2 1 1 1 2
5 5
2 1 1 1 2
5 6
2 1 1 1 2
5 7
2 1 1 1 2
5 8
2 1 1 1 2
5 6
2 0 2 2 3
```

### 输出

```
YES
YES
YES
YES
NO
YES
```

