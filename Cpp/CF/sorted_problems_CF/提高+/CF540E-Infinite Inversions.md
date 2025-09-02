---
title: "Infinite Inversions"
layout: "post"
diff: 提高+/省选-
pid: CF540E
tag: []
---

# Infinite Inversions

## 题目描述

There is an infinite sequence consisting of all positive integers in the increasing order: $ p={1,2,3,...} $ . We performed $ n $ swap operations with this sequence. A $ swap(a,b) $ is an operation of swapping the elements of the sequence on positions $ a $ and $ b $ . Your task is to find the number of inversions in the resulting sequence, i.e. the number of such index pairs $ (i,j) $ , that $ i&lt;j $ and $ p_{i}&gt;p_{j} $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of swap operations applied to the sequence.

Each of the next $ n $ lines contains two integers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=10^{9} $ , $ a_{i}≠b_{i} $ ) — the arguments of the swap operation.

## 输出格式

Print a single integer — the number of inversions in the resulting sequence.

## 说明/提示

In the first sample the sequence is being modified as follows: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF540E/c911e52ddf33371777464860f326e25b9c055886.png). It has 4 inversions formed by index pairs $ (1,4) $ , $ (2,3) $ , $ (2,4) $ and $ (3,4) $ .

## 样例 #1

### 输入

```
2
4 2
1 4

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3
1 6
3 4
2 5

```

### 输出

```
15

```

