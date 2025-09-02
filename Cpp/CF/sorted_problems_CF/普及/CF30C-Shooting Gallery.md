---
title: "Shooting Gallery"
layout: "post"
diff: 普及/提高-
pid: CF30C
tag: []
---

# Shooting Gallery

## 题目描述

One warm and sunny day king Copa decided to visit the shooting gallery, located at the Central Park, and try to win the main prize — big pink plush panda. The king is not good at shooting, so he invited you to help him.

The shooting gallery is an infinite vertical plane with Cartesian coordinate system on it. The targets are points on this plane. Each target is described by it's coordinates $ x_{i} $ , and $ y_{i} $ , by the time of it's appearance $ t_{i} $ and by the number $ p_{i} $ , which gives the probability that Copa hits this target if he aims at it.

A target appears and disappears instantly, so Copa can hit the target only if at the moment $ t_{i} $ his gun sight aimed at $ (x_{i},y_{i}) $ . Speed of movement of the gun sight on the plane is equal to 1. Copa knows all the information about the targets beforehand (remember, he is a king!). He wants to play in the optimal way, which maximizes the expected value of the amount of hit targets. He can aim at any target at the moment 0.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=1000 $ ) — amount of targets in the shooting gallery. Then $ n $ lines follow, each describing one target. Each description consists of four numbers $ x_{i} $ , $ y_{i} $ , $ t_{i} $ , $ p_{i} $ (where $ x_{i} $ , $ y_{i} $ , $ t_{i} $ — integers, $ -1000<=x_{i},y_{i}<=1000,0<=t_{i}<=10^{9} $ , real number $ p_{i} $ is given with no more than 6 digits after the decimal point, $ 0<=p_{i}<=1 $ ). No two targets may be at the same point.

## 输出格式

Output the maximum expected value of the amount of targets that was shot by the king. Your answer will be accepted if it differs from the correct answer by not more than $ 10^{-6} $ .

## 样例 #1

### 输入

```
1
0 0 0 0.5

```

### 输出

```
0.5000000000

```

## 样例 #2

### 输入

```
2
0 0 0 0.6
5 0 5 0.7

```

### 输出

```
1.3000000000

```

