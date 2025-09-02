---
title: "Hardwood Species"
layout: "post"
diff: 难度0
pid: UVA10226
tag: []
---

# Hardwood Species

## 题目描述

给定若干字符串，请求出每个字符串在全部字符串中的百分比。

## 输入格式

第一行一个整数 $t$，代表数据组数。

在 $t$ 组数据中，每一组有若干行，每行一个字符串，可能有空格，代表输入进来的字符串。

每一组数据之间用一个空行隔开。

## 输出格式

对于每一组数据，输出若干行，按字符串的字典序输出每一个字符串和它在全部单词中的百分比（保留 $4$ 位小数）。

每一组数据的输出之间用一个空行隔开。

## 说明/提示

对于 $100\%$ 的数据，字符串种数不超过 $10^4$，字符串总数不超过 $10^6$，字符串长度不超过 $30$。

## 样例 #1

### 输入

```
1

Red Alder
Ash
Aspen
Basswood
Ash
Beech
Yellow Birch
Ash
Cherry
Cottonwood
Ash
Cypress
Red Elm
Gum
Hackberry
White Oak
Hickory
Pecan
Hard Maple
White Oak
Soft Maple
Red Oak
Red Oak
White Oak
Poplan
Sassafras
Sycamore
Black Walnut
Willow

```

### 输出

```
Ash 13.7931
Aspen 3.4483
Basswood 3.4483
Beech 3.4483
Black Walnut 3.4483
Cherry 3.4483
Cottonwood 3.4483
Cypress 3.4483
Gum 3.4483
Hackberry 3.4483
Hard Maple 3.4483
Hickory 3.4483
Pecan 3.4483
Poplan 3.4483
Red Alder 3.4483
Red Elm 3.4483
Red Oak 6.8966
Sassafras 3.4483
Soft Maple 3.4483
Sycamore 3.4483
White Oak 10.3448
Willow 3.4483
Yellow Birch 3.4483
```

