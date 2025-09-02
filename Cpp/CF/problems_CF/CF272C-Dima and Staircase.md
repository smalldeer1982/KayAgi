---
title: "Dima and Staircase"
layout: "post"
diff: 普及/提高-
pid: CF272C
tag: []
---

# Dima and Staircase

## 题目描述

Dima's got a staircase that consists of $ n $ stairs. The first stair is at height $ a_{1} $ , the second one is at $ a_{2} $ , the last one is at $ a_{n} $ ( $ 1<=a_{1}<=a_{2}<=...<=a_{n} $ ).

Dima decided to play with the staircase, so he is throwing rectangular boxes at the staircase from above. The $ i $ -th box has width $ w_{i} $ and height $ h_{i} $ . Dima throws each box vertically down on the first $ w_{i} $ stairs of the staircase, that is, the box covers stairs with numbers $ 1,2,...,w_{i} $ . Each thrown box flies vertically down until at least one of the two following events happen:

- the bottom of the box touches the top of a stair;
- the bottom of the box touches the top of a box, thrown earlier.

We only consider touching of the horizontal sides of stairs and boxes, at that touching with the corners isn't taken into consideration. Specifically, that implies that a box with width $ w_{i} $ cannot touch the stair number $ w_{i}+1 $ .

You are given the description of the staircase and the sequence in which Dima threw the boxes at it. For each box, determine how high the bottom of the box after landing will be. Consider a box to fall after the previous one lands.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{5}) $ — the number of stairs in the staircase. The second line contains a non-decreasing sequence, consisting of $ n $ integers, $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}; a_{i}<=a_{i+1}) $ .

The next line contains integer $ m $ $ (1<=m<=10^{5}) $ — the number of boxes. Each of the following $ m $ lines contains a pair of integers $ w_{i},h_{i} $ $ (1<=w_{i}<=n; 1<=h_{i}<=10^{9}) $ — the size of the $ i $ -th thrown box.

The numbers in the lines are separated by spaces.

## 输出格式

Print $ m $ integers — for each box the height, where the bottom of the box will be after landing. Print the answers for the boxes in the order, in which the boxes are given in the input.

Please, do not use the %lld specifier to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

The first sample are shown on the picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF272C/141a6409b5823a4a8bdecfcecc6a55967701b504.png)

## 样例 #1

### 输入

```
5
1 2 3 6 6
4
1 1
3 1
1 1
4 3

```

### 输出

```
1
3
4
6

```

## 样例 #2

### 输入

```
3
1 2 3
2
1 1
3 1

```

### 输出

```
1
3

```

## 样例 #3

### 输入

```
1
1
5
1 2
1 10
1 10
1 10
1 10

```

### 输出

```
1
3
13
23
33

```

