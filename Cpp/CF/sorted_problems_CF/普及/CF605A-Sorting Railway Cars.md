---
title: "Sorting Railway Cars"
layout: "post"
diff: 普及/提高-
pid: CF605A
tag: ['排序']
---

# Sorting Railway Cars

## 题目描述

An infinitely long railway has a train consisting of $ n $ cars, numbered from $ 1 $ to $ n $ (the numbers of all the cars are distinct) and positioned in arbitrary order. David Blaine wants to sort the railway cars in the order of increasing numbers. In one move he can make one of the cars disappear from its place and teleport it either to the beginning of the train, or to the end of the train, at his desire. What is the minimum number of actions David Blaine needs to perform in order to sort the train?

## 输入格式

The first line of the input contains integer $ n $ ( $ 1<=n<=100000 $ ) — the number of cars in the train.

The second line contains $ n $ integers $ p_{i} $ ( $ 1<=p_{i}<=n $ , $ p_{i}≠p_{j} $ if $ i≠j $ ) — the sequence of the numbers of the cars in the train.

## 输出格式

Print a single integer — the minimum number of actions needed to sort the railway cars.

## 说明/提示

In the first sample you need first to teleport the $ 4 $ -th car, and then the $ 5 $ -th car to the end of the train.

## 样例 #1

### 输入

```
5
4 1 2 5 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4
4 1 3 2

```

### 输出

```
2

```

