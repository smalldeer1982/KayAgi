---
title: "Meals on Wheels Routing System"
layout: "post"
diff: 难度0
pid: UVA206
tag: []
---

# Meals on Wheels Routing System

## 题目描述

"Meals on Wheels"机构决定为本市市民送外卖。

为了节省时间，让饭菜始终是热的，此机构设计了一种算法来为顾客的地址排序，再把订单分配给外卖小哥。

把整个城市看做一个平面直角坐标系，机构总部在原点(0,0)，每个顾客的地址用(x,y)表示，x轴正半轴为东，负半轴为西，y轴正半轴为北，负半轴为南。

你现在需要编写一个程序，输入每天的司机数量（其实就是路线数）和每个顾客的情况（名字与坐标），然后以以下规则安排路线：

1.计算出每个顾客的极坐标，其中正东方向为0∘，正北方向为90∘.

2.按照角度排递增序，然后尽可能平均地分配路线。

3.角度高的路线数不应该比角度低的路线数多。（其实就是路线数也要从小往大递增）

4.如果两个顾客极坐标的角度相同，那么按照距离排序。

5.任一两条路线的顾客差不得超过1。

你的程序不仅要确定路线的安排方案，还要计算出每条路线的长度。这里的长度包括机构总部到顾客家的距离，后续顾客家之间的距离，和最后返回总部的距离。
距离都以曼哈顿距离计算。

## 输入格式

本题多测。

第一行是一个字符串，代表数据的ID（其实没啥用）。

第二行是两个数n,m，代表路径数与顾客数。

接下来2m行是顾客信息，分别是一个长度为sss的字符串（名字）和坐标(x,y)。

输入文件以EOF结束，保证合法。

## 输出格式

输出数据包含数据ID，顾客数量和路线数量，路线ID，分别送到的顾客姓名，路线长度和路线总长度。

（其实看样例更好理解）

## 说明/提示

1≤ID.length≤50

1≤s≤25

/什么？n和m？抱歉，翻译者也没找到。（逃

Translater:@Luisvacson

## 样例 #1

### 输入

```
Sample Route List 1
4 10
able
1 2
baker
-3 6
charlie
-4 -5
donald
4 -7
eloise
3 4
frank
2 2
gertrude
5 9
horace
-2 -5
inez
5 -3
james
0 1
Sample Route List 2
1 1
charlie
1 1
```

### 输出

```
Sample Route List 1
Number of Customers: 10
Number of Routes: 4
Route ==&gt; 1
Customer: frank
Customer: eloise
Customer: gertrude
Route Length ==&gt; 28
Route ==&gt; 2
Customer: able
Customer: james
Customer: baker
Route Length ==&gt; 22
Route ==&gt; 3
Customer: charlie
Customer: horace
Route Length ==&gt; 18
Route ==&gt; 4
Customer: donald
Customer: inez
Route Length ==&gt; 24
Total Route Length ==&gt; 92
***********************************
Sample Route List 2
Number of Customers: 1
Number of Routes: 1
Route ==&gt; 1
Customer: charlie
Route Length ==&gt; 4
Total Route Length ==&gt; 4
```

