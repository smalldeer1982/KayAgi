---
title: "The Last Hole!"
layout: "post"
diff: 省选/NOI-
pid: CF274C
tag: []
---

# The Last Hole!

## 题目描述

Luyi has $ n $ circles on the plane. The $ i $ -th circle is centered at $ (x_{i},y_{i}) $ . At the time zero circles start to grow simultaneously. In other words, the radius of each circle at time $ t\ (t&gt;0) $ is equal to $ t $ . The circles are drawn as black discs on an infinite white plane. So at each moment the plane consists of several black and white regions. Note that the circles may overlap while growing.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF274C/9b4e1ebb881bb05cb98067ff4ad19ee2f6db6140.png)We define a hole as a closed, connected white region. For instance, the figure contains two holes shown by red border. During growing some holes may be created and it is easy to see that each created hole will disappear eventually. Luyi asks you to find moment of time such that the last hole disappears. In other words, you should find the first moment such that no hole can be seen after that.

## 输入格式

The first line of the input contains integer $ n $ ( $ 1<=n<=100 $ ). Each of the next $ n $ lines contains two integers $ x_{i} $ and $ y_{i} $ ( $ -10^{4}<=x_{i},y_{i}<=10^{4} $ ), indicating the location of $ i $ -th circle.

It's guaranteed that no two circles are centered at the same point.

## 输出格式

Print the moment where the last hole disappears. If there exists no moment in which we can find holes print -1.

The answer will be considered correct if the absolute or relative error does not exceed $ 10^{-4} $ .

## 样例 #1

### 输入

```
3
0 0
1 1
2 2

```

### 输出

```
-1

```

## 样例 #2

### 输入

```
4
0 0
0 2
2 2
2 0

```

### 输出

```
1.414214

```

## 样例 #3

### 输入

```
4
0 1
0 -1
-2 0
4 0

```

### 输出

```
2.125000

```

