---
title: "CLOPPAIR - Closest Point Pair"
layout: "post"
diff: 提高+/省选-
pid: SP8725
tag: []
---

# CLOPPAIR - Closest Point Pair

## 题目描述

给你$n$个点，找出一对它们之间欧式距离最短的点对（即求最近点对）

保证所有点都是唯一的，且只有一对距离最短
***

## 输入格式

第一行为整数$n(2\leq n\leq 5\cdot10^4)$;

然后每行两个数$x,y$，表示这个点的$x$坐标和$y$坐标，$|x-y|\leq10^6$。
***

## 输出格式

输出三个数$a,b,c$，其中$a,b$表示最近的点对，$c$表示这两点之间的距离（即输出最近点对及其距离）。$c$保留$6$位小数。

