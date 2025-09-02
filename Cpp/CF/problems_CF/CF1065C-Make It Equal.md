---
title: "Make It Equal"
layout: "post"
diff: 普及+/提高
pid: CF1065C
tag: ['模拟', '贪心', '树状数组']
---

# Make It Equal

## 题目描述

There is a toy building consisting of $ n $ towers. Each tower consists of several cubes standing on each other. The $ i $ -th tower consists of $ h_i $ cubes, so it has height $ h_i $ .

Let's define operation slice on some height $ H $ as following: for each tower $ i $ , if its height is greater than $ H $ , then remove some top cubes to make tower's height equal to $ H $ . Cost of one "slice" equals to the total number of removed cubes from all towers.

Let's name slice as good one if its cost is lower or equal to $ k $ ( $ k \ge n $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1065C/658a593f32bf5073d4f1a1a7bd7987feaeb4f838.png)Calculate the minimum number of good slices you have to do to make all towers have the same height. Of course, it is always possible to make it so.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ n \le k \le 10^9 $ ) — the number of towers and the restriction on slices, respectively.

The second line contains $ n $ space separated integers $ h_1, h_2, \dots, h_n $ ( $ 1 \le h_i \le 2 \cdot 10^5 $ ) — the initial heights of towers.

## 输出格式

Print one integer — the minimum number of good slices you have to do to make all towers have the same heigth.

## 说明/提示

In the first example it's optimal to make $ 2 $ slices. The first slice is on height $ 2 $ (its cost is $ 3 $ ), and the second one is on height $ 1 $ (its cost is $ 4 $ ).

## 样例 #1

### 输入

```
5 5
3 1 2 2 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 5
2 3 4 5

```

### 输出

```
2

```

