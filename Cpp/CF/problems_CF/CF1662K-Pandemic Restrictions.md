---
title: "Pandemic Restrictions"
layout: "post"
diff: 难度0
pid: CF1662K
tag: []
---

# Pandemic Restrictions

## 题目描述

After a long time living abroad, you have decided to move back to Italy and have to find a place to live, but things are not so easy due to the ongoing global pandemic.

Your three friends Fabio, Flavio and Francesco live at the points with coordinates $ (x_1, y_1), (x_2, y_2) $ and $ (x_3, y_3) $ , respectively. Due to the mobility restrictions in response to the pandemic, meetings are limited to $ 3 $ persons, so you will only be able to meet $ 2 $ of your friends at a time. Moreover, in order to contain the spread of the infection, the authorities have imposed the following additional measure: for each meeting, the sum of the lengths travelled by each of the attendees from their residence place to the place of the meeting must not exceed $ r $ .

What is the minimum value of $ r $ (which can be any nonnegative real number) for which there exists a place of residence that allows you to hold the three possible meetings involving you and two of your friends? Note that the chosen place of residence need not have integer coordinates.

## 输入格式

The first line contains the two integers $ x_1, y_1 $ ( $ -10^4 \le x_1, y_1 \le 10^4 $ ) — the coordinates of the house of your friend Fabio.

The second line contains the two integers $ x_2, y_2 $ ( $ -10^4 \le x_2, y_2 \le 10^4 $ ) — the coordinates of the house of your friend Flavio.

The third line contains the two integers $ x_3, y_3 $ ( $ -10^4 \le x_3, y_3 \le 10^4 $ ) — the coordinates of the house of your friend Francesco.

It is guaranteed that your three friends live in different places (i.e., the three points $ (x_1, y_1) $ , $ (x_2, y_2) $ , $ (x_3, y_3) $ are guaranteed to be distinct).

## 输出格式

Print the minimum value of $ r $ which allows you to find a residence place satisfying the above conditions. Your answer is considered correct if its absolute or relative error does not exceed $ 10^{-4} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer is accepted if and only if $ \frac{|a - b|}{\max{(1, |b|)}} \le 10^{-4} $ .

## 说明/提示

In the first sample, Fabio, Flavio and Francesco live at the points with coordinates $ (0,0) $ , $ (5,0) $ and $ (3,3) $ respectively. The optimal place of residence, represented by a green house in the picture below, is at the point with coordinates $ (2.3842..., 0.4151...) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662K/6176cb025ba764f3a2bdc46444ffdcc96a60555a.png) For instance, it is possible for you to meet Flavio and Francesco at the point depicted below, so that the sum of the lengths travelled by the three attendees is at most (and in fact equal to) $ r=5.0686... $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662K/b1add33fb4a361b53c9130c6e51e6f022ff88899.png)In the second sample, any point on the segment $ \{(x,0):\ -1 \leq x \leq 1 \} $ is an optimal place of residence.

## 样例 #1

### 输入

```
0 0
5 0
3 3
```

### 输出

```
5.0686143166
```

## 样例 #2

### 输入

```
-1 0
0 0
1 0
```

### 输出

```
2.0000000000
```

