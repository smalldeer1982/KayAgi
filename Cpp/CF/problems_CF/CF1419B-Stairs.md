---
title: "Stairs"
layout: "post"
diff: 普及-
pid: CF1419B
tag: []
---

# Stairs

## 题目描述

Jett is tired after destroying the town and she wants to have a rest. She likes high places, that's why for having a rest she wants to get high and she decided to craft staircases.

Staircase is a squared figure that consists of square cells. Each staircase consists of an arbitrary number of stairs. If a staircase has $ n $ stairs, then it is made of $ n $ columns, the first column is $ 1 $ cell high, the second column is $ 2 $ cells high, $ \ldots $ , the $ n $ -th column if $ n $ cells high. The lowest cells of all stairs must be in the same row.

A staircase with $ n $ stairs is called nice, if it may be covered by $ n $ disjoint squares made of cells. All squares should fully consist of cells of a staircase.

 This is how a nice covered staircase with $ 7 $ stairs looks like: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1419B/20e8f39717a3a82bb8f73bd6c4f499217c03a037.png)Find out the maximal number of different nice staircases, that can be built, using no more than $ x $ cells, in total. No cell can be used more than once.

## 输入格式

The first line contains a single integer $ t $ $ (1 \le t \le 1000) $ — the number of test cases.

The description of each test case contains a single integer $ x $ $ (1 \le x \le 10^{18}) $ — the number of cells for building staircases.

## 输出格式

For each test case output a single integer — the number of different nice staircases, that can be built, using not more than $ x $ cells, in total.

## 说明/提示

In the first test case, it is possible to build only one staircase, that consists of $ 1 $ stair. It's nice. That's why the answer is $ 1 $ .

In the second test case, it is possible to build two different nice staircases: one consists of $ 1 $ stair, and another consists of $ 3 $ stairs. This will cost $ 7 $ cells. In this case, there is one cell left, but it is not possible to use it for building any nice staircases, that have not been built yet. That's why the answer is $ 2 $ .

In the third test case, it is possible to build only one of two nice staircases: with $ 1 $ stair or with $ 3 $ stairs. In the first case, there will be $ 5 $ cells left, that may be used only to build a staircase with $ 2 $ stairs. This staircase is not nice, and Jett only builds nice staircases. That's why in this case the answer is $ 1 $ . If Jett builds a staircase with $ 3 $ stairs, then there are no more cells left, so the answer is $ 1 $ again.

## 样例 #1

### 输入

```
4
1
8
6
1000000000000000000
```

### 输出

```
1
2
1
30
```

