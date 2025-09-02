---
title: "KRECT - Counting K-Rectangle"
layout: "post"
diff: 难度0
pid: SP4329
tag: []
---

# KRECT - Counting K-Rectangle

## 题目描述

给定一个m*n平方板。每个方块都包含一个英文字母（'A'…'Z'）。

板的k矩形是一个边与板的边平行的矩形，并且包含k种不同类型的字母。

例如，这个4*3板：

```
CED
CEB
CBC
DDA
```

矩形[（1,1）,（2,2）]是板的2个矩形，因为它包含两个不同的字母：C和E。

给出m，n，k和一个m*n的板。确定板中有多少K矩形。

## 输入格式

第一行包含3个整数m、n和k。（1≤m，n≤100   1≤k≤26）

下面的m行，每行n个字母（'A'…'Z'）

## 输出格式

板中K矩形的数目。

## 样例 #1

### 输入

```
4 3 3
CED
CEB
CBC
DDA
```

### 输出

```
12
```

