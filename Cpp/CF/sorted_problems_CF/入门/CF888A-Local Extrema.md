---
title: "Local Extrema"
layout: "post"
diff: 入门
pid: CF888A
tag: ['模拟']
---

# Local Extrema

## 题目描述

You are given an array $ a $ . Some element of this array $ a_{i} $ is a local minimum iff it is strictly less than both of its neighbours (that is, $ a_{i}<a_{i-1} $ and $ a_{i}<a_{i+1} $ ). Also the element can be called local maximum iff it is strictly greater than its neighbours (that is, $ a_{i}>a_{i-1} $ and $ a_{i}>a_{i+1} $ ). Since $ a_{1} $ and $ a_{n} $ have only one neighbour each, they are neither local minima nor local maxima.

An element is called a local extremum iff it is either local maximum or local minimum. Your task is to calculate the number of local extrema in the given array.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=1000 $ ) — the number of elements in array $ a $ .

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=1000 $ ) — the elements of array $ a $ .

## 输出格式

Print the number of local extrema in the given array.

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
4
1 5 2 5

```

### 输出

```
2

```

