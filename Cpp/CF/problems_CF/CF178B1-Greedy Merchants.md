---
title: "Greedy Merchants"
layout: "post"
diff: 普及+/提高
pid: CF178B1
tag: []
---

# Greedy Merchants

## 题目描述

In ABBYY a wonderful Smart Beaver lives. This time, he began to study history. When he read about the Roman Empire, he became interested in the life of merchants.

The Roman Empire consisted of $ n $ cities numbered from $ 1 $ to $ n $ . It also had $ m $ bidirectional roads numbered from $ 1 $ to $ m $ . Each road connected two different cities. Any two cities were connected by no more than one road.

We say that there is a path between cities $ c_{1} $ and $ c_{2} $ if there exists a finite sequence of cities $ t_{1},t_{2},...,t_{p} $ $ (p>=1) $ such that:

- $ t_{1}=c_{1} $
- $ t_{p}=c_{2} $
- for any $ i $ $ (1<=i<p) $ , cities $ t_{i} $ and $ t_{i+1} $ are connected by a road

We know that there existed a path between any two cities in the Roman Empire.

In the Empire $ k $ merchants lived numbered from $ 1 $ to $ k $ . For each merchant we know a pair of numbers $ s_{i} $ and $ l_{i} $ , where $ s_{i} $ is the number of the city where this merchant's warehouse is, and $ l_{i} $ is the number of the city where his shop is. The shop and the warehouse could be located in different cities, so the merchants had to deliver goods from the warehouse to the shop.

Let's call a road important for the merchant if its destruction threatens to ruin the merchant, that is, without this road there is no path from the merchant's warehouse to his shop. Merchants in the Roman Empire are very greedy, so each merchant pays a tax (1 dinar) only for those roads which are important for him. In other words, each merchant pays $ d_{i} $ dinars of tax, where $ d_{i} $ ( $ d_{i}>=0 $ ) is the number of roads important for the $ i $ -th merchant.

The tax collection day came in the Empire. The Smart Beaver from ABBYY is very curious by nature, so he decided to count how many dinars each merchant had paid that day. And now he needs your help.

## 输入格式

The first input line contains two integers $ n $ and $ m $ , separated by a space, $ n $ is the number of cities, and $ m $ is the number of roads in the empire.

The following $ m $ lines contain pairs of integers $ a_{i} $ , $ b_{i} $ $ (1<=a_{i},b_{i}<=n,a_{i}≠b_{i}) $ , separated by a space — the numbers of cities connected by the $ i $ -th road. It is guaranteed that any two cities are connected by no more than one road and that there exists a path between any two cities in the Roman Empire.

The next line contains a single integer $ k $ — the number of merchants in the empire.

The following $ k $ lines contain pairs of integers $ s_{i} $ , $ l_{i} $ $ (1<=s_{i},l_{i}<=n) $ , separated by a space, — $ s_{i} $ is the number of the city in which the warehouse of the $ i $ -th merchant is located, and $ l_{i} $ is the number of the city in which the shop of the $ i $ -th merchant is located.

The input limitations for getting 20 points are:

- $ 1<=n<=200 $
- $ 1<=m<=200 $
- $ 1<=k<=200 $

The input limitations for getting 50 points are:

- $ 1<=n<=2000 $
- $ 1<=m<=2000 $
- $ 1<=k<=2000 $

The input limitations for getting 100 points are:

- $ 1<=n<=10^{5} $
- $ 1<=m<=10^{5} $
- $ 1<=k<=10^{5} $

## 输出格式

Print exactly $ k $ lines, the $ i $ -th line should contain a single integer $ d_{i} $ — the number of dinars that the $ i $ -th merchant paid.

## 说明/提示

The given sample is illustrated in the figure below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178B1/4913bb025cb3137535b72c7a1543583701455251.png)Let's describe the result for the first merchant. The merchant's warehouse is located in city $ 1 $ and his shop is in city $ 5 $ . Let us note that if either road, $ (1,2) $ or $ (2,3) $ is destroyed, there won't be any path between cities $ 1 $ and $ 5 $ anymore. If any other road is destroyed, the path will be preserved. That's why for the given merchant the answer is $ 2 $ .

## 样例 #1

### 输入

```
7 8
1 2
2 3
3 4
4 5
5 6
5 7
3 5
4 7
4
1 5
2 4
2 6
4 7

```

### 输出

```
2
1
2
0

```

