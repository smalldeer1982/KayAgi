---
title: "Circles of Waiting"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF963E
tag: []
---

# Circles of Waiting

## 题目描述

A chip was placed on a field with coordinate system onto point $ (0,0) $ .

Every second the chip moves randomly. If the chip is currently at a point $ (x,y) $ , after a second it moves to the point $ (x-1,y) $ with probability $ p_{1} $ , to the point $ (x,y-1) $ with probability $ p_{2} $ , to the point $ (x+1,y) $ with probability $ p_{3} $ and to the point $ (x,y+1) $ with probability $ p_{4} $ . It's guaranteed that $ p_{1}+p_{2}+p_{3}+p_{4}=1 $ . The moves are independent.

Find out the expected time after which chip will move away from origin at a distance greater than $ R $ (i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF963E/246aa7b086b7ae016d999e705d5862993be04853.png) will be satisfied).

## 输入格式

First line contains five integers $ R,a_{1},a_{2},a_{3} $ and $ a_{4} $ ( $ 0<=R<=50,1<=a_{1},a_{2},a_{3},a_{4}<=1000 $ ).

Probabilities $ p_{i} $ can be calculated using formula ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF963E/f4c10e1f02852c4316fc9bec25d03186d7840bcb.png).

## 输出格式

It can be shown that answer for this problem is always a rational number of form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF963E/ed2c29110477df816fcacba17d99273426c4dd91.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF963E/2a1de71f5127e0ac869e59f9af51dec4e82446fc.png).

Print $ P·Q^{-1} $ modulo $ 10^{9}+7 $ .

## 说明/提示

In the first example initially the chip is located at a distance $ 0 $ from origin. In one second chip will move to distance $ 1 $ is some direction, so distance to origin will become $ 1 $ .

Answers to the second and the third tests: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF963E/1afdb873d5404107498744fbaddde38ee83fd279.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF963E/4c1b0d15ba2866c8474bd814731c993c182c0d7d.png).

## 样例 #1

### 输入

```
0 1 1 1 1

```

### 输出

```
1
```

## 样例 #2

### 输入

```
1 1 1 1 1

```

### 输出

```
666666674
```

## 样例 #3

### 输入

```
1 1 2 1 2

```

### 输出

```
538461545
```

