---
title: "GREAT_E - The Great Escape"
layout: "post"
diff: 难度0
pid: SP11157
tag: []
---

# GREAT_E - The Great Escape

## 题目描述

Primo 是加拉加斯市著名的吉他手，热爱生活的他到附近的食品店买了一个南美洲非常有名的小吃——arepa。

正在享用 arepa 时，他的朋友 Maxx 打来电话。Maxx 正驾驶着直升机，发现许多粉丝在街上寻找 Primo。

Primo 开始觉得有些疯狂，他想尽可能多地吃 arepa，尽量拖延被粉丝找到的时间。他对这些粉丝可不感兴趣，因为他早有女朋友了。

你的任务是帮助 Primo。那么，Maxx 会在直升机上告诉你各条街道的连接情况、通行时间，还会告知每条街道在被粉丝堵住前剩余的时间。

如果粉丝堵住了一条街，这条街就不再考虑，Primo 绝不会走这条街道！

Primo 对 arepa 十分喜爱，请帮他在粉丝找到他之前尽情享用这段时间。

### 输入格式：

首先输入一个整数 $T$，表示测试用例的数量。接下来的 $T$ 个部分描述每个测试用例：

每个测试用例的第一行有三个整数 $N, R, M$，分别代表交叉路口的数量、街道的数量，以及 Primo 最大可以吃 arepa 的时间。

接下来 $R$ 行，每行包含三个整数和一个字符串 $R_i, R_j, W_{ij}, T_{ij}$，表示交叉路口 $i$ 和 $j$ 之间的连接，过街时间为 $W_{ij}$ 分钟，粉丝将在 $T_{ij}$ 分钟后堵住这条街。如果粉丝不会出现，那么 $T_{ij}$ 为 INF。

每个测试用例的最后一行有两个整数 $S, E$，分别表示 Primo 所在的起点（食品店）和他的家（终点）。

注意：如果粉丝不会堵住某条街，那么 $T_{ij}$ 为 INF。

此外：你可以在任一交叉路口之间双向通行。

### 输出格式：

输出应以 “Case #i: ” 字符串开头，其中 $i$ 是测试用例的编号。

如果 Primo 能顺利逃脱，则输出 “Primo can escape in T minute(s)” 其中 $T$ 是他可以吃 arepa 的最长时间；如果无法逃脱，则输出 “Primo can't escape”。

### 数据范围与提示：

- $1 \leq N \leq 100,000$
- $1 \leq R \leq 100,000$
- $1 \leq M \leq 100,000$
- $1 \leq R_1, R_2 < N$
- $1 \leq T_{ij}, W_{ij} \leq 500$

说明：每个交叉路口至少连接至另一个交叉路口，输入中不会有相同的连接关系，并且 Primo 总能达到他的家。

### 样例输入：

```
4

3 2 100

0 1 30 40

1 2 10 40

0 2

3 2 100

0 1 30 INF

1 2 10 INF

0 2

4 3 100

0 1 20 INF

1 2 40 INF

2 3 50 120

0 3

2 1 100

0 1 1 2

0 1
```

### 样例输出：

```
Case #1: Primo can't escape

Case #2: Primo can escape in 100 minute(s)

Case #3: Primo can escape in 9 minute(s)

Case #4: Primo can't escape
```

 **本翻译由 AI 自动生成**

