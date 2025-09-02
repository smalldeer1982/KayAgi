---
title: "A Change in Thermal Unit"
layout: "post"
diff: 入门
pid: UVA11984
tag: []
---

# A Change in Thermal Unit

## 题目描述

摄氏温标（$\degree\!\mathrm{C}$）与华氏温标（$\degree\!\mathrm{F}$）是两大国际主流的计量温度的标准。其换算公式如下：

$$F=\frac{9}{5}C+32$$

在本问题中，你将得到 $2$ 个整数 $C, d$，表示初始温度为 $C \,\degree\!\mathrm{C}$，温度增长了 $d \,\degree\!\mathrm{F}$。求温度增长后的温度为多少摄氏度。结果保留两位小数。

**存在多组数据。**

## 输入格式

第一行一个整数 $T$，表示数据的组数。

接下来 $T$ 行，每行两个整数 $C,d$。

## 输出格式

对于每组数据，输出温度增长后的温度（摄氏度）。

**【数据规模与约定】**

对于所有数据，$T\leq 100$，$0\leq C,d\leq 100$。

## 样例 #1

### 输入

```
2
100 0
0 100
```

### 输出

```
Case 1: 100.00
Case 2: 55.56
```

