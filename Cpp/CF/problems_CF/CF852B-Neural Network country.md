---
title: "Neural Network country"
layout: "post"
diff: 普及+/提高
pid: CF852B
tag: []
---

# Neural Network country

## 题目描述

Due to the recent popularity of the Deep learning new countries are starting to look like Neural Networks. That is, the countries are being built deep with many layers, each layer possibly having many cities. They also have one entry, and one exit point.

There are exactly $ L $ layers, each having $ N $ cities. Let us look at the two adjacent layers $ L_{1} $ and $ L_{2} $ . Each city from the layer $ L_{1} $ is connected to each city from the layer $ L_{2} $ with the traveling cost $ c_{ij} $ for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/945db37d32744d415049d069cc0844aba4f66789.png), and each pair of adjacent layers has the same cost in between their cities as any other pair (they just stacked the same layers, as usual). Also, the traveling costs to each city from the layer $ L_{2} $ are same for all cities in the $ L_{1} $ , that is $ c_{ij} $ is the same for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/c68efb3baed3cf7572378486b7c111ddb2e0536c.png), and fixed $ j $ .

Doctor G. needs to speed up his computations for this country so he asks you to find the number of paths he can take from entry to exit point such that his traveling cost is divisible by given number $ M $ .

## 输入格式

The first line of input contains $ N\ (1<=N<=10^{6}) $ , $ L\ (2<=L<=10^{5}) $ and $ M\ (2<=M<=100) $ , the number of cities in each layer, the number of layers and the number that travelling cost should be divisible by, respectively.

Second, third and fourth line contain $ N $ integers each denoting costs $ 0<=cost<=M $ from entry point to the first layer, costs between adjacent layers as described above, and costs from the last layer to the exit point.

## 输出格式

Output a single integer, the number of paths Doctor G. can take which have total cost divisible by $ M $ , modulo $ 10^{9}+7 $ .

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/a69d8a08d51c12997ef7e1fffeead190caef4b9f.png)

This is a country with $ 3 $ layers, each layer having $ 2 $ cities. Paths ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/ec8d7c564cdb67dc57f9922091a73334d330a237.png), and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/4299965c61d16bcfc0b10fce7b833b4b1e5fc7b5.png) are the only paths having total cost divisible by $ 13 $ . Notice that input edges for layer cities have the same cost, and that they are same for all layers.

## 样例 #1

### 输入

```
2 3 13
4 6
2 1
3 4

```

### 输出

```
2
```

