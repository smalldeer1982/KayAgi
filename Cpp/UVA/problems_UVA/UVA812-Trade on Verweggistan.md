---
title: "Trade on Verweggistan"
layout: "post"
diff: 难度0
pid: UVA812
tag: []
---

# Trade on Verweggistan

## 题目描述

## 题意翻译
有$w$个工作堆，每一堆有$b_i$个物品，购买每一物品所需花的价值为$prul_{i,j}$

每购买一个物品可以得到$10$的利润，每次购买物品$prul_{i,j}$之前必须先购买$prul_{i,1},···prul_{i,j-1}$

求所能够获得的最大利润，以及获得这些利润需要购买物品的个数。输出所有可以获得最小利润的方案，如果有超过十种方案可以取得最小的利润，输出购买个数最少的十个

## 输入格式

多组数据。

第一行一个整数$w$，后面$w$行，每行第一个整数$b_i$，后面$b_i$个整数，表示$prul_{i,1},···prul_{i,b_i}$

读入到$w=0$时停止

## 输出格式

具体细节见样例

对于每组数据，输出三行。

第一行为测试点的编号（从1开始），第二行为最大可以获得的利润，第三行为可能的方案，从小到大输出十个

## 样例 #1

### 输入

```
1
6 12 3 10 7 16 5
2
5 7 3 11 9 10
9 1 2 3 4 10 16 10 4 16
0
```

### 输出

```
Workyards 1
Maximum profit is 8.
Number of pruls to buy: 4
Workyards 2
Maximum profit is 40.
Number of pruls to buy: 6 7 8 9 10 12 13
```

