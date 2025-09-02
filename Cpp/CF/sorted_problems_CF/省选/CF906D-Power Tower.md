---
title: "Power Tower"
layout: "post"
diff: 省选/NOI-
pid: CF906D
tag: ['递归', '标签462']
---

# Power Tower

## 题目描述

Priests of the Quetzalcoatl cult want to build a tower to represent a power of their god. Tower is usually made of power-charged rocks. It is built with the help of rare magic by levitating the current top of tower and adding rocks at its bottom. If top, which is built from $ k-1 $ rocks, possesses power $ p $ and we want to add the rock charged with power $ w_{k} $ then value of power of a new tower will be $ {w_{k}}^{p} $ .

Rocks are added from the last to the first. That is for sequence $ w_{1},...,w_{m} $ value of power will be

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF906D/a7b9adfbee151f2e3ef09f9dbad2cf6b657882ca.png)After tower is built, its power may be extremely large. But still priests want to get some information about it, namely they want to know a number called cumulative power which is the true value of power taken modulo $ m $ . Priests have $ n $ rocks numbered from $ 1 $ to $ n $ . They ask you to calculate which value of cumulative power will the tower possess if they will build it from rocks numbered $ l,l+1,...,r $ .

## 输入格式

First line of input contains two integers $ n $ ( $ 1<=n<=10^{5} $ ) and $ m $ ( $ 1<=m<=10^{9} $ ).

Second line of input contains $ n $ integers $ w_{k} $ ( $ 1<=w_{k}<=10^{9} $ ) which is the power of rocks that priests have.

Third line of input contains single integer $ q $ ( $ 1<=q<=10^{5} $ ) which is amount of queries from priests to you.

 $ k^{th} $ of next $ q $ lines contains two integers $ l_{k} $ and $ r_{k} $ ( $ 1<=l_{k}<=r_{k}<=n $ ).

## 输出格式

Output $ q $ integers. $ k $ -th of them must be the amount of cumulative power the tower will have if is built from rocks $ l_{k},l_{k}+1,...,r_{k} $ .

## 说明/提示

 $ 3^{27}=7625597484987 $

## 样例 #1

### 输入

```
6 1000000000
1 2 2 3 3 3
8
1 1
1 6
2 2
2 3
2 4
4 4
4 5
4 6

```

### 输出

```
1
1
2
4
256
3
27
597484987

```

