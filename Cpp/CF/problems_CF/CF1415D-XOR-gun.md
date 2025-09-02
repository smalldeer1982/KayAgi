---
title: "XOR-gun"
layout: "post"
diff: 普及+/提高
pid: CF1415D
tag: []
---

# XOR-gun

## 题目描述

Arkady owns a non-decreasing array $ a_1, a_2, \ldots, a_n $ . You are jealous of its beauty and want to destroy this property. You have a so-called XOR-gun that you can use one or more times.

In one step you can select two consecutive elements of the array, let's say $ x $ and $ y $ , remove them from the array and insert the integer $ x \oplus y $ on their place, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). Note that the length of the array decreases by one after the operation. You can't perform this operation when the length of the array reaches one.

For example, if the array is $ [2, 5, 6, 8] $ , you can select $ 5 $ and $ 6 $ and replace them with $ 5 \oplus 6 = 3 $ . The array becomes $ [2, 3, 8] $ .

You want the array no longer be non-decreasing. What is the minimum number of steps needed? If the array stays non-decreasing no matter what you do, print $ -1 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 10^5 $ ) — the initial length of the array.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the array. It is guaranteed that $ a_i \le a_{i + 1} $ for all $ 1 \le i < n $ .

## 输出格式

Print a single integer — the minimum number of steps needed. If there is no solution, print $ -1 $ .

## 说明/提示

In the first example you can select $ 2 $ and $ 5 $ and the array becomes $ [7, 6, 8] $ .

In the second example you can only obtain arrays $ [1, 1] $ , $ [3, 3] $ and $ [0] $ which are all non-decreasing.

In the third example you can select $ 1 $ and $ 2 $ and the array becomes $ [3, 4, 6, 20] $ . Then you can, for example, select $ 3 $ and $ 4 $ and the array becomes $ [7, 6, 20] $ , which is no longer non-decreasing.

## 样例 #1

### 输入

```
4
2 5 6 8
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
1 2 4 6 20
```

### 输出

```
2
```

