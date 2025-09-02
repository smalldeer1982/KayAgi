---
title: "Iqea"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF936E
tag: []
---

# Iqea

## 题目描述

Gridland is placed on infinite grid and has a shape of figure consisting of cells. Every cell of Gridland is a city. Two cities that are placed in adjacent cells are connected by the road of length $ 1 $ . It's possible to get from any city to any other city using roads. The distance between two cities is the minimum total road length on path from one city to another. It's possible to get from any cell that doesn't belong to Gridland to any other cell that doesn't belong to Gridland by using only cells which don't belong to Gridland. In other words, Gridland is connected and complement of Gridland is also connected.

At the moment no city in Gridland has Iqea famous shop. But Iqea has great plans for building shops in Gridland. For customers' convenience Iqea decided to develop an application. Using this application everyone can learn the distance to the nearest Iqea. You are to develop this application.

You are asked to process two types of queries:

- new Iqea shop has been opened in the city with coordinates $ (x,y) $ ;
- customer wants to know the distance to the nearest already opened Iqea shop from his city located in a cell with coordinates $ (x,y) $ .

Pay attention that customer can move only by roads and can never leave Gridland on his way to the shop.

## 输入格式

The first line contains one integer $ n $ — number of cities in Gridland ( $ 1<=n<=300000 $ ). The following $ n $ lines contain two integers $ x_{i} $ and $ y_{i} $ — coordinates of cell that contains $ i $ -th city ( $ 1<=x_{i},y_{i}<=300000 $ ). No two cells coincide. Cells form connected area, complement of this area is also connected.

The following line contains single integer $ q $ — number of queries ( $ 0<=q<=300000 $ ). Following $ q $ lines contain queries, $ i $ -th line consists of three integers $ t_{i} $ , $ x_{i} $ and $ y_{i} $ ( $ t_{i}∈{1,2} $ , $ 1<=x_{i},y_{i}<=300000 $ ). If $ t_{i}=1 $ , new Iqea shop has been opened in the city with coordinates $ (x_{i},y_{i}) $ . It's guaranteed that there was no Iqea shop in this city before. If $ t_{i}=2 $ , you are to find the distance to the nearest already opened Iqea shop from the city with coordinates $ (x_{i},y_{i}) $ . It's guaranteed that in queries of both types cell $ (x_{i},y_{i}) $ belongs to Gridland.

## 输出格式

For every query of second type output single integer — minimum distance to the nearest Iqea shop. If no Iqea shop has been already opened, output $ -1 $ .

## 样例 #1

### 输入

```
7
1 2
1 3
2 3
3 1
3 2
3 3
4 2
5
2 3 2
1 4 2
2 1 2
1 3 3
2 2 3

```

### 输出

```
-1
5
1

```

## 样例 #2

### 输入

```
6
1 1
1 2
1 3
2 1
2 2
3 1
4
1 3 1
2 1 2
1 2 2
2 1 3

```

### 输出

```
3
2

```

