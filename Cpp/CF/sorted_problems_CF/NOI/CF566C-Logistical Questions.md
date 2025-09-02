---
title: "Logistical Questions"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF566C
tag: []
---

# Logistical Questions

## 题目描述

Some country consists of $ n $ cities, connected by a railroad network. The transport communication of the country is so advanced that the network consists of a minimum required number of $ (n-1) $ bidirectional roads (in the other words, the graph of roads is a tree). The $ i $ -th road that directly connects cities $ a_{i} $ and $ b_{i} $ , has the length of $ l_{i} $ kilometers.

The transport network is served by a state transporting company FRR (Fabulous Rail Roads). In order to simplify the price policy, it offers a single ride fare on the train. In order to follow the route of length $ t $ kilometers, you need to pay ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF566C/4783342c233dee54d6aad50e90f122716039e425.png) burles. Note that it is forbidden to split a long route into short segments and pay them separately (a special railroad police, or RRP, controls that the law doesn't get violated).

A Large Software Company decided to organize a programming tournament. Having conducted several online rounds, the company employees determined a list of finalists and sent it to the logistical department to find a place where to conduct finals. The Large Software Company can easily organize the tournament finals in any of the $ n $ cities of the country, so the the main factor in choosing the city for the last stage of the tournament is the total cost of buying tickets for all the finalists. We know that the $ i $ -th city of the country has $ w_{i} $ cup finalists living there.

Help the company employees find the city such that the total cost of travel of all the participants to it is minimum.

## 输入格式

The first line of the input contains number $ n $ ( $ 1<=n<=200000 $ ) — the number of cities in the country.

The next line contains $ n $ integers $ w_{1},w_{2},...,w_{n} $ ( $ 0<=w_{i}<=10^{8} $ ) — the number of finalists living in each city of the country.

Next $ (n-1) $ lines contain the descriptions of the railroad, the $ i $ -th line contains three integers, $ a_{i} $ , $ b_{i} $ , $ l_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ , $ 1<=l_{i}<=1000 $ ).

## 输出格式

Print two numbers — an integer $ f $ that is the number of the optimal city to conduct the competition, and the real number $ c $ , equal to the minimum total cost of transporting all the finalists to the competition. Your answer will be considered correct if two conditions are fulfilled at the same time:

1. The absolute or relative error of the printed number $ c $ in comparison with the cost of setting up a final in city $ f $ doesn't exceed $ 10^{-6} $ ;
2. Absolute or relative error of the printed number $ c $ in comparison to the answer of the jury doesn't exceed $ 10^{-6} $ .

If there are multiple answers, you are allowed to print any of them.

## 说明/提示

In the sample test an optimal variant of choosing a city to conduct the finals of the competition is $ 3 $ . At such choice the cost of conducting is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF566C/d27433edacc370f4d98644d4c1867b0e65f8d3a2.png) burles.

In the second sample test, whatever city you would choose, you will need to pay for the transport for five participants, so you will need to pay ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF566C/2742addad9ff0521989570c4ca211f5401fbe3a4.png) burles for each one of them.

## 样例 #1

### 输入

```
5
3 1 2 6 5
1 2 3
2 3 1
4 3 9
5 3 1

```

### 输出

```
3 192.0
```

## 样例 #2

### 输入

```
2
5 5
1 2 2

```

### 输出

```
1 14.142135623730951000

```

