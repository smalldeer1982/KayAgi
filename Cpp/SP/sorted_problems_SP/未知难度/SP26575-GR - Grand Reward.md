---
title: "GR - Grand Reward"
layout: "post"
diff: 难度0
pid: SP26575
tag: []
---

# GR - Grand Reward

## 题目描述

Grand 公司每个月都会评选出最佳员工并给予奖励。本月有四位员工：Sameh、Ameen、Shafeek 和 Atef，他们都表现优异，但经理只能选择一位来奖励。他想出了一个有趣的方法。

这四位员工分别站在一个 $N \times N$ 的方阵四个方向：分别是东边的 Sameh、北边的 Ameen、西边的 Shafeek 和南边的 Atef。矩阵的元素从 1 开始以递增的方式排列，从左到右、从上到下，直到填满整个矩阵。例如：

```
 Ameen
 1 2 3
Sameh 4 5 6 Shafeek
 7 8 9
 Atef
```

然后，我们将这个矩阵顺时针旋转 $T$ 次，每次旋转 90 度。最终获得奖金的员工，是他所在边的元素之和最大的那位。

例如，当 $T=4$ 且 $N=3$ 时，

![des](http://s21.postimg.org/ep24j1yhj/image.jpg)

获胜者是 Atef，因为他所在的边上元素之和为 $7+8+9=24$，最大。

你的任务是编写一个程序来实现这一过程。

## 输入格式

输入包含两个整数 $N$ 和 $T$，分别代表矩阵的大小和旋转的次数。这里 $3 \leq N \leq 100$，$0 \leq T \leq 100$。

## 输出格式

输出旋转后的矩阵，以及获得奖励的员工姓名（Sameh、Ameen、Shafeek 或 Atef）。

### 示例

```
输入：
3 4

输出：
7 4 1
8 5 2
9 6 3
Atef
```

 **本翻译由 AI 自动生成**

