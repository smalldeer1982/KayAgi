---
title: "Simple Skewness"
layout: "post"
diff: 提高+/省选-
pid: CF626E
tag: []
---

# Simple Skewness

## 题目描述

Define the simple skewness of a collection of numbers to be the collection's mean minus its median. You are given a list of $ n $ (not necessarily distinct) integers. Find the non-empty subset (with repetition) with the maximum simple skewness.

The mean of a collection is the average of its elements. The median of a collection is its middle element when all of its elements are sorted, or the average of its two middle elements if it has even size.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=200\ 000 $ ) — the number of elements in the list.

The second line contains $ n $ integers $ x_{i} $ ( $ 0<=x_{i}<=1000000 $ ) — the $ i $ th element of the list.

## 输出格式

In the first line, print a single integer $ k $ — the size of the subset.

In the second line, print $ k $ integers — the elements of the subset in any order.

If there are multiple optimal subsets, print any.

## 说明/提示

In the first case, the optimal subset is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF626E/0b9550a7a9f20f7b56fdc9073fe6e2b4a2093ee5.png), which has mean $ 5 $ , median $ 2 $ , and simple skewness of $ 5-2=3 $ .

In the second case, the optimal subset is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF626E/d0a3a979416d48c43b3c8a042caaf404373f99fe.png). Note that repetition is allowed.

In the last case, any subset has the same median and mean, so all have simple skewness of $ 0 $ .

## 样例 #1

### 输入

```
4
1 2 3 12

```

### 输出

```
3
1 2 12 

```

## 样例 #2

### 输入

```
4
1 1 2 2

```

### 输出

```
3
1 1 2 

```

## 样例 #3

### 输入

```
2
1 2

```

### 输出

```
2
1 2

```

