---
title: "Maximum Waterfall"
layout: "post"
diff: 省选/NOI-
pid: CF269D
tag: []
---

# Maximum Waterfall

## 题目描述

Emuskald was hired to design an artificial waterfall according to the latest trends in landscape architecture. A modern artificial waterfall consists of multiple horizontal panels affixed to a wide flat wall. The water flows down the top of the wall from panel to panel until it reaches the bottom of the wall.

The wall has height $ t $ and has $ n $ panels on the wall. Each panel is a horizontal segment at height $ h_{i} $ which begins at $ l_{i} $ and ends at $ r_{i} $ . The $ i $ -th panel connects the points $ (l_{i},h_{i}) $ and $ (r_{i},h_{i}) $ of the plane. The top of the wall can be considered a panel connecting the points $ (-10^{9},t) $ and $ (10^{9},t) $ . Similarly, the bottom of the wall can be considered a panel connecting the points $ (-10^{9},0) $ and $ (10^{9},0) $ . No two panels share a common point.

Emuskald knows that for the waterfall to be aesthetically pleasing, it can flow from panel $ i $ to panel $ j $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269D/5a41f87b0168f94e6178285e1ee91e69b10580d9.png)) only if the following conditions hold:

1. $ max(l_{i},l_{j})&lt;min(r_{i},r_{j}) $ (horizontal projections of the panels overlap);
2. $ h_{j}&lt;h_{i} $ (panel $ j $ is below panel $ i $ );
3. there is no such panel $ k $ $ (h_{j}&lt;h_{k}&lt;h_{i}) $ that the first two conditions hold for the pairs $ (i,k) $ and $ (k,j) $ .

Then the flow for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269D/5a41f87b0168f94e6178285e1ee91e69b10580d9.png) is equal to $ min(r_{i},r_{j})-max(l_{i},l_{j}) $ , the length of their horizontal projection overlap.

Emuskald has decided that in his waterfall the water will flow in a single path from top to bottom. If water flows to a panel (except the bottom of the wall), the water will fall further to exactly one lower panel. The total amount of water flow in the waterfall is then defined as the minimum horizontal projection overlap between two consecutive panels in the path of the waterfall. Formally:

1. the waterfall consists of a single path of panels ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269D/94bd9e9fe8db4cd80fd47cf8dd35094a595a876f.png);
2. the flow of the waterfall is the minimum flow in the path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269D/94bd9e9fe8db4cd80fd47cf8dd35094a595a876f.png).

 To make a truly great waterfall Emuskald must maximize this water flow, but there are too many panels and he is having a hard time planning his creation. Below is an example of a waterfall Emuskald wants:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269D/772bd38da020894115b05646ae3719e2b6fc3c60.png)Help Emuskald maintain his reputation and find the value of the maximum possible water flow.

## 输入格式

The first line of input contains two space-separated integers $ n $ and $ t $ ( $ 1<=n<=10^{5} $ , $ 2<=t<=10^{9} $ ), the number of the panels excluding the top and the bottom panels, and the height of the wall. Each of the $ n $ following lines contain three space-separated integers $ h_{i} $ , $ l_{i} $ and $ r_{i} $ ( $ 0&lt;h_{i}&lt;t $ , $ -10^{9}<=l_{i}&lt;r_{i}<=10^{9} $ ), the height, left and right ends of the $ i $ -th panel segment.

It is guaranteed that no two segments share a common point.

## 输出格式

Output a single integer — the maximum possible amount of water flow in the desired waterfall.

## 说明/提示

The first test case corresponds to the picture.

## 样例 #1

### 输入

```
5 6
4 1 6
3 2 7
5 9 11
3 10 15
1 13 16

```

### 输出

```
4

```

## 样例 #2

### 输入

```
6 5
4 2 8
3 1 2
2 2 3
2 6 12
1 0 7
1 8 11

```

### 输出

```
2

```

