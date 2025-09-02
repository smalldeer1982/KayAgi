---
title: "Watering Flowers"
layout: "post"
diff: 普及/提高-
pid: CF617C
tag: []
---

# Watering Flowers

## 题目描述

A flowerbed has many flowers and two fountains.

You can adjust the water pressure and set any values $ r_{1}(r_{1}>=0) $ and $ r_{2}(r_{2}>=0) $ , giving the distances at which the water is spread from the first and second fountain respectively. You have to set such $ r_{1} $ and $ r_{2} $ that all the flowers are watered, that is, for each flower, the distance between the flower and the first fountain doesn't exceed $ r_{1} $ , or the distance to the second fountain doesn't exceed $ r_{2} $ . It's OK if some flowers are watered by both fountains.

You need to decrease the amount of water you need, that is set such $ r_{1} $ and $ r_{2} $ that all the flowers are watered and the $ r_{1}^{2}+r_{2}^{2} $ is minimum possible. Find this minimum value.

## 输入格式

The first line of the input contains integers $ n $ , $ x_{1} $ , $ y_{1} $ , $ x_{2} $ , $ y_{2} $ ( $ 1<=n<=2000 $ , $ -10^{7}<=x_{1},y_{1},x_{2},y_{2}<=10^{7} $ ) — the number of flowers, the coordinates of the first and the second fountain.

Next follow $ n $ lines. The $ i $ -th of these lines contains integers $ x_{i} $ and $ y_{i} $ ( $ -10^{7}<=x_{i},y_{i}<=10^{7} $ ) — the coordinates of the $ i $ -th flower.

It is guaranteed that all $ n+2 $ points in the input are distinct.

## 输出格式

Print the minimum possible value $ r_{1}^{2}+r_{2}^{2} $ . Note, that in this problem optimal answer is always integer.

## 说明/提示

The first sample is ( $ r_{1}^{2}=5 $ , $ r_{2}^{2}=1 $ ): ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF617C/2d8d9a04106e184829b587a5ec1ff5859c519f17.png) The second sample is ( $ r_{1}^{2}=1 $ , $ r_{2}^{2}=32 $ ): ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF617C/3a67f8e9001d1413dc94db849ab2167229f3fb78.png)

## 样例 #1

### 输入

```
2 -1 0 5 3
0 2
5 2

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4 0 0 5 0
9 4
8 3
-1 0
1 4

```

### 输出

```
33

```

