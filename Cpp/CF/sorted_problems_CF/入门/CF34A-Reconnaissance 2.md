---
title: "Reconnaissance 2"
layout: "post"
diff: 入门
pid: CF34A
tag: []
---

# Reconnaissance 2

## 题目描述

 $ n $ soldiers stand in a circle. For each soldier his height $ a_{i} $ is known. A reconnaissance unit can be made of such two neighbouring soldiers, whose heights difference is minimal, i.e. $ |a_{i}-a_{j}| $ is minimal. So each of them will be less noticeable with the other. Output any pair of soldiers that can form a reconnaissance unit.

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=100 $ ) — amount of soldiers. Then follow the heights of the soldiers in their order in the circle — $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=1000 $ ). The soldier heights are given in clockwise or counterclockwise direction.

## 输出格式

Output two integers — indexes of neighbouring soldiers, who should form a reconnaissance unit. If there are many optimum solutions, output any of them. Remember, that the soldiers stand in a circle.

## 说明/提示

#### 题目描述：
操场上有 $n$ 个士兵站成了一个环，每名士兵有一个身高 $h_i$，试求两相邻士兵 $x,y$，使得士兵 $x$ 和士兵 $y$ 身高差最小。

#### 输入：
第一行 $n$，之后 $n$ 个整数 $h_i$。

#### 输出：
题目描述中的 $x,y$，若有多解任意输出一组即可。
#### 数据范围：
$2\leq n\leq100,1\leq h_i\leq1000$

Translated by @[稀神探女](/user/85216)，Reformed by @[chenyilai](/user/249879)。

## 样例 #1

### 输入

```
5
10 12 13 15 10

```

### 输出

```
5 1

```

## 样例 #2

### 输入

```
4
10 20 30 40

```

### 输出

```
1 2

```

