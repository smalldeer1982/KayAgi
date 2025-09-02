---
title: "Kyoya and Colored Balls"
layout: "post"
diff: 普及/提高-
pid: CF553A
tag: ['排列组合']
---

# Kyoya and Colored Balls

## 题目描述

Kyoya Ootori has a bag with $ n $ colored balls that are colored with $ k $ different colors. The colors are labeled from $ 1 $ to $ k $ . Balls of the same color are indistinguishable. He draws balls from the bag one by one until the bag is empty. He noticed that he drew the last ball of color $ i $ before drawing the last ball of color $ i+1 $ for all $ i $ from $ 1 $ to $ k-1 $ . Now he wonders how many different ways this can happen.

## 输入格式

The first line of input will have one integer $ k $ ( $ 1<=k<=1000 $ ) the number of colors.

Then, $ k $ lines will follow. The $ i $ -th line will contain $ c_{i} $ , the number of balls of the $ i $ -th color ( $ 1<=c_{i}<=1000 $ ).

The total number of balls doesn't exceed 1000.

## 输出格式

A single integer, the number of ways that Kyoya can draw the balls from the bag as described in the statement, modulo $ 1000000007 $ .

## 说明/提示

In the first sample, we have 2 balls of color 1, 2 balls of color 2, and 1 ball of color 3. The three ways for Kyoya are:

`<br></br>1 2 1 2 3<br></br>1 1 2 2 3<br></br>2 1 1 2 3<br></br>`

## 样例 #1

### 输入

```
3
2
2
1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
1
2
3
4

```

### 输出

```
1680

```



---

