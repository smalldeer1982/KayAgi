---
title: "Scaygerboss"
layout: "post"
diff: 省选/NOI-
pid: CF513F1
tag: []
---

# Scaygerboss

## 题目描述

Cthulhu 决定抓住 Scaygerboss。Scaygerboss 发现了这一点，并试图躲藏在一群他的 scaygers 中。除 Scaygerboss 之外，每个 scayger 都是雄性或雌性。Scaygerboss 的性别是“其他”。

Scaygers 在一个被分割成单元格的二维地图上分散着。如果一个 Scayger 与一个与其性别不同的 Scayger 正好停留在同一个单元格中，那么它看起来既呆萌又可爱。如果地图上所有的 Scayger 看起来都是呆萌又可爱的，Cthulhu 将无法抓住 Scaygerboss。

Scaygers 可以以不同的速度移动。对于每个 Scayger，我们给出了它从一个单元移动到相邻单元所需的时间。如果两个单元共享一个边，则它们是相邻的。在任何时刻，不包含障碍物的每个单元都可以被任意数量的 Scaygers 占据。Scaygers 不能移动到有障碍物的单元。

计算出如果 Scaygers 朝着这个目标做出最优的移动，所有的scaygers看起来既呆萌又可爱所需的最短时间。

### **简明题意**

给出 Scaygers 在网格图上的初始分布以及每个 Scayger 的速度，求使每个 Scayger 至少与一个异性 Scayger 在同一格的最短时间。

## 输入格式

第一行包含 $4$ 个整数：$n$，$m$，$males$，$females$ $(0\le males,females\le n\cdot m)$。$n$ 和 $m$ 是地图的尺寸；$males$ 和 $females$ 是雄性 scaygers 和雌性 scaygers 的数量。

接下来的 $n$ 行描述了地图。每一行都包含了 $m$ 个字符。字符 `.` 表示一个空闲的单元格；字符 `#` 表示一个有障碍物的单元格。

下一行包含 $3$ 个整数 $r$，$c$ 和 $t$ $（1 \le r \le n，1 \le c \le m,1 \le t \le 10^9）$，分别表示 Scaygerboss 的当前坐标和 Scaygerboss 移动到相邻单元格所需的时间。接下来的 males 行包含具有与 Scaygerboss 相同格式的坐标和时间的 male scaygers 的坐标和时间。接下来的 females 行包含具有与 Scaygerboss 相同格式的坐标和时间的 female scaygers 的坐标和时间。（坐标和时间的限制与 Scaygerboss 相同。）所有的 scaygers 都居住在没有障碍物的单元格中。

该问题由两个子问题组成。这两个子问题在输入方面有不同的约束条件。对于正确提交子问题，你将获得部分得分。下面是子问题的描述。

- 在子问题 $F1$ （$14$ 分）中，数据范围是 $1\le n,m\le 11$。
- 在子问题 $F2$ （$6$ 分）中，数据范围是 $1\le n, m\le 22$。

## 输出格式

输出使所有 scaygers 看起来呆萌又可爱所需的最少时间，如果不可能则输出 $-1$。

### **说明/提示**

考虑样例一。Scaygers 隐藏在一个 $4\times 4$ 的地图上。Scaygerboss 隐藏于单元格 $(2,1)$ 并可以在 $1$ 个单位时间内在单元格之间移动。地图上还有 $2$ 个雄性和 $3$ 个雌性 Scaygers。其中一个雌性最初位于单元格 $(1,1)$，而其他所有 Scaygers 都在单元格 $(2,1)$。所有 Scaygers 在 $2$ 个单位的时间内在单元格之间移动。如果 Scaygerboss 和来自单元格 $(1,1)$ 的雌性 Scayger 移动到单元格 $(1,2)$，并且来自位于单元格 $(2,1)$ 中的一个雄性和一个雌性 Scayger 移动到单元格 $(1,1)$，那么所有 Scaygers 将在 $2$ 个单位时间内看起来呆萌又可爱。

## 样例 #1

### 输入

```
4 4 2 3
....
.###
####
####
2 1 1
2 1 2
2 1 2
2 1 2
2 1 2
1 1 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 4 2 2
....
.###
2 1 1
2 1 2
2 1 2
2 1 2
2 1 2

```

### 输出

```
-1

```

