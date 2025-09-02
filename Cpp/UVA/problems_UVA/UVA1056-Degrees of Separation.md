---
title: "Degrees of Separation"
layout: "post"
diff: 难度0
pid: UVA1056
tag: []
---

# Degrees of Separation

## 题目描述

### 题目背景

在这个相互联系日渐紧密的世界中，据推测，地球上的每个人都与其他人的最大分离度不超过6。 在这个问题中，你需要实现一个程序来求得人际网络的最大分离度。


一个人际关系网络由许多人与关系组成，每个关系连接两个人。

对于任意两个人，他们的分离度是指联系二人所需的**最小**的关系数。

对于一个人际关系网络而言，最大分离度是指这个网络中任意两人分离度的最大值。

对于一个人际关系网络，如果存在两个人不能通过一系列人际关系相连，那么这个人际关系网络是**不连通的**。

如下图，人际关系网络$\mathrm{A}$是联通的，最大分离度为$2$ ，人际关系网络$\mathrm{B}$是不连通的。

![Network](https://cdn.luogu.com.cn/upload/image_hosting/l5snl03i.png)

你需要对于一个给定的人际关系网络，判断它是否连通，以及求出最大分离度。

## 输入格式

输入有多组数据。

每组数据的第一行为$2$个整数$P$,$R$,为人际关系网络中的人数与关系数。

接下来一行是$R$个关系，每个关系包含两个人名，代表这两个人之间有联系。保证$P$个人人名各不相同且名字中不含空格。

因为一个人可能有多个关系，所以同一个人名在一组数据可能出现不止一次。

输入以最后一行两个$0$结束。

## 输出格式

对于每组数据输出一行，为最大分离度，如果不连通，那么输出
`` DISCONNECTED``，每两组数据输出之间空一行。

### 输入输出样例

**输入 #1**
```
4 4
Ashok Kiyoshi Ursala Chun Ursala Kiyoshi Kiyoshi Chun
4 2
Ashok Chun Ursala Kiyoshi
6 5
Bubba Cooter Ashok Kiyoshi Ursala Chun Ursala Kiyoshi Kiyoshi Chun
0 0
```

**输出 #1**

```
Network 1: 2

Network 2: DISCONNECTED

Network 3: DISCONNECTED
```

## 说明/提示

$2 \le P \le 50$

$R \ge 1$

