---
title: "Sex Assignments And Breeding Experiments"
layout: "post"
diff: 难度0
pid: UVA359
tag: []
---

# Sex Assignments And Breeding Experiments

## 题目描述

给你一个有向图，每一个点要么入度为 $ 2 $ ，要么入度为 $ 0 $ 。

如果图中的每一个点都满足上述要求，则输出

```cpp
Graph number i is sexy
```
反之，输出

```cpp
Graph number i is not sexy
```
其中， $ i $ 代表第几组数据。

## 输入格式

有多组数据，每组数据第一行为 $ n $ 和 $ m $ ，代表图的点数和边数。

第 $ 2 $ 行至第 $ 2 + m - 1 $ 行，每行两个数 $ u $ ， $ v $ ，表示有一条连接 $ u $ 和 $ v $ 的有向边。

