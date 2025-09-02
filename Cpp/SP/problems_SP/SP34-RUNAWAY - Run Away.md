---
title: "RUNAWAY - Run Away"
layout: "post"
diff: 提高+/省选-
pid: SP34
tag: []
---

# RUNAWAY - Run Away

## 题目描述

在给定范围内找一个点，使得距离所有点的最小值最大。

## 输入格式

第一行，输入一个数 $T$，表示共有 $T$ 组数据。
 
对于每组数据，以用空格分开的三个数 $X,Y,M$ 开始，满足 $1\le X,Y \le 10000,1 \le M \le 1000$，其中 $X,Y$ 是给定的范围，$M$ 是点的数量。

其下 $M$ 行，每行输入两个数 $U_i,V_i$，保证 $0\le U_i \le X,0\le V_i\le Y$ 表示第 $i$ 个点在 $(U_i,V_i)$ 。
**同一位置可能有多个点**

## 输出格式

对于每一组数据，输出一行 `The safest point is (P, Q).` 其中 $P,Q$ 是所求得的点的坐标，两坐标精确至小数点后一位。

Translated by @我是lyy @Error_502

## 样例 #1

### 输入

```
3
1000 50 1
10 10
100 100 4
10 10
10 90
90 10
90 90
3000 3000 4
1200 85
63 2500
2700 2650 
2990 100
```

### 输出

```
The safest point is (1000.0, 50.0).
The safest point is (50.0, 50.0).
The safest point is (1433.0, 1669.8).
```

