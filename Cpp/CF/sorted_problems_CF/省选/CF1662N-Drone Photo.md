---
title: "Drone Photo"
layout: "post"
diff: 省选/NOI-
pid: CF1662N
tag: []
---

# Drone Photo

## 题目描述

Today, like every year at SWERC, the $ n^2 $ contestants have gathered outside the venue to take a drone photo. Jennifer, the social media manager for the event, has arranged them into an $ n\times n $ square. Being very good at her job, she knows that the contestant standing on the intersection of the $ i $ -th row with the $ j $ -th column is $ a_{i,j} $ years old. Coincidentally, she notices that no two contestants have the same age, and that everyone is between $ 1 $ and $ n^2 $ years old.

Jennifer is planning to have some contestants hold a banner with the ICPC logo parallel to the ground, so that it is clearly visible in the aerial picture. Here are the steps that she is going to follow in order to take the perfect SWERC drone photo.

- First of all, Jennifer is going to select four contestants standing on the vertices of an axis-aligned rectangle.
- Then, she will have the two younger contestants hold one of the poles, while the two older contestants will hold the other pole.
- Finally, she will unfold the banner, using the poles to support its two ends. Obviously, this can only be done if the two poles are parallel and do not cross, as shown in the pictures below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/0c66204e6b46ec54ef4970646675d11080bec4fc.png)Being very indecisive, Jennifer would like to try out all possible arrangements for the banner, but she is worried that this may cause the contestants to be late for the competition. How many different ways are there to choose the four contestants holding the poles in order to take a perfect photo? Two choices are considered different if at least one contestant is included in one but not the other.

## 输入格式

The first line contains a single integer $ n $ ( $ 2\le n \le 1500 $ ).

The next $ n $ lines describe the ages of the contestants. Specifically, the $ i $ -th line contains the integers $ a_{i,1},a_{i,2},\ldots,a_{i,n} $ ( $ 1\le a_{i,j}\le n^2 $ ).

It is guaranteed that $ a_{i,j}\neq a_{k,l} $ if $ i\neq k $ or $ j\neq l $ .

## 输出格式

Print the number of ways for Jennifer to choose the four contestants holding the poles.

## 说明/提示

In the first sample, there are $ 4 $ contestants, arranged as follows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/e7e2a81b002e3a2bac197b62545c6ad11a69f7a8.png)There is only one way to choose four contestants, with one pole held by contestants aged $ 1 $ and $ 2 $ and the other one by contestants aged $ 3 $ and $ 4 $ . But then, as we can see in the picture, the poles cross.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/626f6c3701e63bf775605758d69491672a9a7858.png)Since there is no valid way to choose four contestants, the answer is $ 0 $ .

In the second sample, the $ 4 $ contestants are arranged as follows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/52911f8374a060499e28117449cb8c5d56740ef4.png)Once again, there is only one way to choose four contestants, but this time the poles don't cross.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/3dbefc9c39c8ce185cc2f953aaf6d4a443ef99d4.png)Therefore, the answer is $ 1 $ .

In the third sample, the $ 9 $ contestants are arranged as follows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/0b2bd9d2be4297c7b6df8f81316d0db59aa26e9e.png)There are $ 6 $ ways of choosing four contestants so that the poles don't cross, as shown in the following pictures.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/72f4724e30f1d908a8873c65b21364979d578b9b.png)

## 样例 #1

### 输入

```
2
1 3
4 2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2
3 2
4 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
9 2 4
1 5 3
7 8 6
```

### 输出

```
6
```

