---
title: "Nezzar and Nice Beatmap"
layout: "post"
diff: 提高+/省选-
pid: CF1477C
tag: []
---

# Nezzar and Nice Beatmap

## 题目描述

Nezzar loves the game osu!.

osu! is played on beatmaps, which can be seen as an array consisting of distinct points on a plane. A beatmap is called nice if for any three consecutive points $ A,B,C $ listed in order, the angle between these three points, centered at $ B $ , is strictly less than $ 90 $ degrees.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1477C/e3be07fe7f328d9736ba1797d6c378eea9a0cf27.png)Points $ A,B,C $ on the left have angle less than $ 90 $ degrees, so they can be three consecutive points of a nice beatmap; Points $ A',B',C' $ on the right have angle greater or equal to $ 90 $ degrees, so they cannot be three consecutive points of a nice beatmap.Now Nezzar has a beatmap of $ n $ distinct points $ A_1,A_2,\ldots,A_n $ . Nezzar would like to reorder these $ n $ points so that the resulting beatmap is nice.

Formally, you are required to find a permutation $ p_1,p_2,\ldots,p_n $ of integers from $ 1 $ to $ n $ , such that beatmap $ A_{p_1},A_{p_2},\ldots,A_{p_n} $ is nice. If it is impossible, you should determine it.

## 输入格式

The first line contains a single integer $ n $ ( $ 3 \le n \le 5000 $ ).

Then $ n $ lines follow, $ i $ -th of them contains two integers $ x_i $ , $ y_i $ ( $ -10^9 \le x_i, y_i \le 10^9 $ ) — coordinates of point $ A_i $ .

It is guaranteed that all points are distinct.

## 输出格式

If there is no solution, print $ -1 $ .

Otherwise, print $ n $ integers, representing a valid permutation $ p $ .

If there are multiple possible answers, you can print any.

## 说明/提示

Here is the illustration for the first test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1477C/c3fc0fe3cc31d46f5db97d11a3cc278faa7f4e6f.png)Please note that the angle between $ A_1 $ , $ A_2 $ and $ A_5 $ , centered at $ A_2 $ , is treated as $ 0 $ degrees. However, angle between $ A_1 $ , $ A_5 $ and $ A_2 $ , centered at $ A_5 $ , is treated as $ 180 $ degrees.

## 样例 #1

### 输入

```
5
0 0
5 0
4 2
2 1
3 0
```

### 输出

```
1 2 5 3 4
```

