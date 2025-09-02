---
title: "Area of a Star"
layout: "post"
diff: 提高+/省选-
pid: CF630P
tag: ['数学']
---

# Area of a Star

## 题目描述

It was decided in IT City to distinguish successes of local IT companies by awards in the form of stars covered with gold from one side. To order the stars it is necessary to estimate order cost that depends on the area of gold-plating. Write a program that can calculate the area of a star.

A "star" figure having $ n>=5 $ corners where $ n $ is a prime number is constructed the following way. On the circle of radius $ r $ $ n $ points are selected so that the distances between the adjacent ones are equal. Then every point is connected by a segment with two maximally distant points. All areas bounded by the segments parts are the figure parts.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630P/39542693730deb3e42477c452be9d403bea1f94e.png)

## 输入格式

The only line of the input contains two integers $ n $ ( $ 5<=n&lt;10^{9} $ , $ n $ is prime) and $ r $ ( $ 1<=r<=10^{9} $ ) — the number of the star corners and the radius of the circumcircle correspondingly.

## 输出格式

Output one number — the star area. The relative error of your answer should not be greater than $ 10^{-7} $ .

## 样例 #1

### 输入

```
7 10

```

### 输出

```
108.395919545675
```

