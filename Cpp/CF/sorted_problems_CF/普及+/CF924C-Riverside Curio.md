---
title: "Riverside Curio"
layout: "post"
diff: 普及+/提高
pid: CF924C
tag: []
---

# Riverside Curio

## 题目描述

Arkady decides to observe a river for $ n $ consecutive days. The river's water level on each day is equal to some real value.

Arkady goes to the riverside each day and makes a mark on the side of the channel at the height of the water level, but if it coincides with a mark made before, no new mark is created. The water does not wash the marks away. Arkady writes down the number of marks strictly above the water level each day, on the $ i $ -th day this value is equal to $ m_{i} $ .

Define $ d_{i} $ as the number of marks strictly under the water level on the $ i $ -th day. You are to find out the minimum possible sum of $ d_{i} $ over all days. There are no marks on the channel before the first day.

## 输入格式

The first line contains a single positive integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of days.

The second line contains $ n $ space-separated integers $ m_{1},m_{2},...,m_{n} $ ( $ 0<=m_{i}<i $ ) — the number of marks strictly above the water on each day.

## 输出格式

Output one single integer — the minimum possible sum of the number of marks strictly below the water level among all days.

## 说明/提示

In the first example, the following figure shows an optimal case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924C/ad72072688b34b2729139a36473993902a371313.png)Note that on day $ 3 $ , a new mark should be created because if not, there cannot be $ 3 $ marks above water on day $ 4 $ . The total number of marks underwater is $ 0+0+2+0+3+1=6 $ .

In the second example, the following figure shows an optimal case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924C/193fbf53ff0eac39a568b94979481249f6765c97.png)

## 样例 #1

### 输入

```
6
0 1 0 3 0 2

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5
0 1 2 1 2

```

### 输出

```
1

```

## 样例 #3

### 输入

```
5
0 1 1 2 2

```

### 输出

```
0

```

