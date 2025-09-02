---
title: "Infinity Gauntlet"
layout: "post"
diff: 入门
pid: CF987A
tag: ['字符串', '概率论']
---

# Infinity Gauntlet

## 题目描述

# 题目大意
你偷看了Thanos的无尽手套，手套上有6颗无限宝石：
- the **Power** Gem of **purple** color, 紫色的力量宝石
- the **Time** Gem of **green** color, 绿色的时间宝石
- the **Space** Gem of **blue** color, 蓝色的空间宝石
- the **Soul** Gem of **orange** color, 橙色的灵魂宝石
- the **Reality** Gem of **red** color, 红色的现实宝石
- the **Mind** Gem of **yellow** color. 黄色的心灵宝石

现在给出你偷看到的宝石的**颜色**，请你确定缺少了哪些宝石（**名称**）

## 输入格式

第一行一个整数 $n(0≤n≤6)$ ,表示你看到的宝石数量

下面 $n$ 行，每行一个字符串，表示你看到宝石的颜色，所有字符串都是小写的。

## 输出格式

第一行一个整数 $m(0≤m≤6)$ ，表示缺少的宝石的个数

下面 $m$ 行，每行一个宝石的**名字**，顺序随意，**名字首字母要记得大写，其他小写**。

感谢@二元长天笑 提供的翻译

## 样例 #1

### 输入

```
4
red
purple
yellow
orange

```

### 输出

```
2
Space
Time

```

## 样例 #2

### 输入

```
0

```

### 输出

```
6
Time
Space
Power
Reality
Mind
Soul

```

