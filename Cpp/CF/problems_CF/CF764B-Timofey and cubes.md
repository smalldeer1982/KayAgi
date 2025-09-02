---
title: "Timofey and cubes"
layout: "post"
diff: 普及-
pid: CF764B
tag: []
---

# Timofey and cubes

## 题目描述

Young Timofey has a birthday today! He got kit of $ n $ cubes as a birthday present from his parents. Every cube has a number $ a_{i} $ , which is written on it. Timofey put all the cubes in a row and went to unpack other presents.

In this time, Timofey's elder brother, Dima reordered the cubes using the following rule. Suppose the cubes are numbered from $ 1 $ to $ n $ in their order. Dima performs several steps, on step $ i $ he reverses the segment of cubes from $ i $ -th to $ (n-i+1) $ -th. He does this while $ i<=n-i+1 $ .

After performing the operations Dima went away, being very proud of himself. When Timofey returned to his cubes, he understood that their order was changed. Help Timofey as fast as you can and save the holiday — restore the initial order of the cubes using information of their current location.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=2·10^{5} $ ) — the number of cubes.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ -10^{9}<=a_{i}<=10^{9} $ ), where $ a_{i} $ is the number written on the $ i $ -th cube after Dima has changed their order.

## 输出格式

Print $ n $ integers, separated by spaces — the numbers written on the cubes in their initial order.

It can be shown that the answer is unique.

## 说明/提示

Consider the first sample.

1. At the begining row was \[ $ 2 $ , $ 3 $ , $ 9 $ , $ 6 $ , $ 7 $ , $ 1 $ , $ 4 $ \].
2. After first operation row was \[ $ 4 $ , $ 1 $ , $ 7 $ , $ 6 $ , $ 9 $ , $ 3 $ , $ 2 $ \].
3. After second operation row was \[ $ 4 $ , $ 3 $ , $ 9 $ , $ 6 $ , $ 7 $ , $ 1 $ , $ 2 $ \].
4. After third operation row was \[ $ 4 $ , $ 3 $ , $ 7 $ , $ 6 $ , $ 9 $ , $ 1 $ , $ 2 $ \].
5. At fourth operation we reverse just middle element, so nothing has changed. The final row is \[ $ 4 $ , $ 3 $ , $ 7 $ , $ 6 $ , $ 9 $ , $ 1 $ , $ 2 $ \]. So the answer for this case is row \[ $ 2 $ , $ 3 $ , $ 9 $ , $ 6 $ , $ 7 $ , $ 1 $ , $ 4 $ \].

## 样例 #1

### 输入

```
7
4 3 7 6 9 1 2

```

### 输出

```
2 3 9 6 7 1 4
```

## 样例 #2

### 输入

```
8
6 1 4 2 5 6 9 2

```

### 输出

```
2 1 6 2 5 4 9 6
```

