---
title: "Fifa and Fafa"
layout: "post"
diff: 普及+/提高
pid: CF935C
tag: []
---

# Fifa and Fafa

## 题目描述

Fifa and Fafa are sharing a flat. Fifa loves video games and wants to download a new soccer game. Unfortunately, Fafa heavily uses the internet which consumes the quota. Fifa can access the internet through his Wi-Fi access point. This access point can be accessed within a range of $ r $ meters (this range can be chosen by Fifa) from its position. Fifa must put the access point inside the flat which has a circular shape of radius $ R $ . Fifa wants to minimize the area that is not covered by the access point inside the flat without letting Fafa or anyone outside the flat to get access to the internet.

The world is represented as an infinite 2D plane. The flat is centered at $ (x_{1},y_{1}) $ and has radius $ R $ and Fafa's laptop is located at $ (x_{2},y_{2}) $ , not necessarily inside the flat. Find the position and the radius chosen by Fifa for his access point which minimizes the uncovered area.

## 输入格式

The single line of the input contains 5 space-separated integers $ R,x_{1},y_{1},x_{2},y_{2} $ ( $ 1<=R<=10^{5} $ , $ |x_{1}|,|y_{1}|,|x_{2}|,|y_{2}|<=10^{5} $ ).

## 输出格式

Print three space-separated numbers $ x_{ap},y_{ap},r $ where $ (x_{ap},y_{ap}) $ is the position which Fifa chose for the access point and $ r $ is the radius of its range.

Your answer will be considered correct if the radius does not differ from optimal more than $ 10^{-6} $ absolutely or relatively, and also the radius you printed can be changed by no more than $ 10^{-6} $ (absolutely or relatively) in such a way that all points outside the flat and Fafa's laptop position are outside circle of the access point range.

## 样例 #1

### 输入

```
5 3 3 1 1

```

### 输出

```
3.7677669529663684 3.7677669529663684 3.914213562373095

```

## 样例 #2

### 输入

```
10 5 5 5 15

```

### 输出

```
5.0 5.0 10.0

```

