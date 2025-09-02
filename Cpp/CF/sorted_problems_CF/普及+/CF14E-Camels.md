---
title: "Camels"
layout: "post"
diff: 普及+/提高
pid: CF14E
tag: []
---

# Camels

## 题目描述

Bob likes to draw camels: with a single hump, two humps, three humps, etc. He draws a camel by connecting points on a coordinate plane. Now he's drawing camels with $ t $ humps, representing them as polylines in the plane. Each polyline consists of $ n $ vertices with coordinates $ (x_{1},y_{1}) $ , $ (x_{2},y_{2}) $ , ..., $ (x_{n},y_{n}) $ . The first vertex has a coordinate $ x_{1}=1 $ , the second — $ x_{2}=2 $ , etc. Coordinates $ y_{i} $ might be any, but should satisfy the following conditions:

- there should be $ t $ humps precisely, i.e. such indexes $ j $ ( $ 2<=j<=n-1 $ ), so that $ y_{j-1}&lt;y_{j}&gt;y_{j+1} $ ,
- there should be precisely $ t-1 $ such indexes $ j $ ( $ 2<=j<=n-1 $ ), so that $ y_{j-1}&gt;y_{j}&lt;y_{j+1} $ ,
- no segment of a polyline should be parallel to the $ Ox $ -axis,
- all $ y_{i} $ are integers between 1 and 4.

For a series of his drawings of camels with $ t $ humps Bob wants to buy a notebook, but he doesn't know how many pages he will need. Output the amount of different polylines that can be drawn to represent camels with $ t $ humps for a given number $ n $ .

## 输入格式

The first line contains a pair of integers $ n $ and $ t $ ( $ 3<=n<=20 $ , $ 1<=t<=10 $ ).

## 输出格式

Output the required amount of camels with $ t $ humps.

## 说明/提示

In the first sample test sequences of $ y $ -coordinates for six camels are: 123421, 123431, 123432, 124321, 134321 и 234321 (each digit corresponds to one value of $ y_{i} $ ).

## 样例 #1

### 输入

```
6 1

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4 2

```

### 输出

```
0

```

