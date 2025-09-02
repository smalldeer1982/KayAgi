---
title: "Parallelepiped walk"
layout: "post"
diff: 难度0
pid: UVA503
tag: []
---

# Parallelepiped walk

## 题目描述

问题描述：
 
给出平行六面体表面的两个点A和B。请你计算从点A到达点B的最短路径长度平方。 
长方体外形尺寸 $l,w,h$ 和点的坐标都是整数。

## 输入格式

输入有多行，每行输入 $l,w,h(1 \le l,w,h \le 1000)$ 和 $x_a,y_a,z_a,x_b,y_b,z_b(0 \le x_a,x_b \le l, 0 \le y_a,y_b \le w, 0 \le z_a,z_b \le h)$ 。 $x_a,y_a,z_a$ 表示点A的位置， $x_b,y_b,z_b$ 表示点B的位置。

## 输出格式

一行一个整数，表示平面上从点A到达点B的最短路径长度平方。

## 样例 #1

### 输入

```
5 5 2 3 1 2 3 5 0
300 600 900 300 550 0 0 550 900
```

### 输出

```
36
970000
```

