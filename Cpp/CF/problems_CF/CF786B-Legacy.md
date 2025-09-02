---
title: "Legacy"
layout: "post"
diff: 省选/NOI-
pid: CF786B
tag: ['线段树', '图论建模', '最短路']
---

# Legacy

## 题目描述

Rick and his co-workers have made a new radioactive formula and a lot of bad guys are after them. So Rick wants to give his legacy to Morty before bad guys catch them.

There are $ n $ planets in their universe numbered from $ 1 $ to $ n $ . Rick is in planet number $ s $ (the earth) and he doesn't know where Morty is. As we all know, Rick owns a portal gun. With this gun he can open one-way portal from a planet he is in to any other planet (including that planet). But there are limits on this gun because he's still using its free trial.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786B/9ce8ffb5132d0e638eaee42e56a9bbc8517d720d.png)By default he can not open any portal by this gun. There are $ q $ plans in the website that sells these guns. Every time you purchase a plan you can only use it once but you can purchase it again if you want to use it more.

Plans on the website have three types:

1. With a plan of this type you can open a portal from planet $ v $ to planet $ u $ .
2. With a plan of this type you can open a portal from planet $ v $ to any planet with index in range $ [l,r] $ .
3. With a plan of this type you can open a portal from any planet with index in range $ [l,r] $ to planet $ v $ .

Rick doesn't known where Morty is, but Unity is going to inform him and he wants to be prepared for when he finds and start his journey immediately. So for each planet (including earth itself) he wants to know the minimum amount of money he needs to get from earth to that planet.

## 输入格式

The first line of input contains three integers $ n $ , $ q $ and $ s $ ( $ 1<=n,q<=10^{5} $ , $ 1<=s<=n $ ) — number of planets, number of plans and index of earth respectively.

The next $ q $ lines contain the plans. Each line starts with a number $ t $ , type of that plan ( $ 1<=t<=3 $ ). If $ t=1 $ then it is followed by three integers $ v $ , $ u $ and $ w $ where $ w $ is the cost of that plan ( $ 1<=v,u<=n $ , $ 1<=w<=10^{9} $ ). Otherwise it is followed by four integers $ v $ , $ l $ , $ r $ and $ w $ where $ w $ is the cost of that plan ( $ 1<=v<=n $ , $ 1<=l<=r<=n $ , $ 1<=w<=10^{9} $ ).

## 输出格式

In the first and only line of output print $ n $ integers separated by spaces. $ i $ -th of them should be minimum money to get from earth to $ i $ -th planet, or $ -1 $ if it's impossible to get to that planet.

## 说明/提示

In the first sample testcase, Rick can purchase $ 4 $ th plan once and then $ 2 $ nd plan in order to get to get to planet number $ 2 $ .

## 样例 #1

### 输入

```
3 5 1
2 3 2 3 17
2 3 2 2 16
2 2 2 3 3
3 3 1 1 12
1 3 3 17

```

### 输出

```
0 28 12 

```

## 样例 #2

### 输入

```
4 3 1
3 4 1 3 12
2 2 3 4 10
1 2 4 16

```

### 输出

```
0 -1 -1 12 

```

