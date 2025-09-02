---
title: "Ehab the Xorcist"
layout: "post"
diff: 普及+/提高
pid: CF1325D
tag: []
---

# Ehab the Xorcist

## 题目描述

Given 2 integers $ u $ and $ v $ , find the shortest array such that [bitwise-xor](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of its elements is $ u $ , and the sum of its elements is $ v $ .

## 输入格式

The only line contains 2 integers $ u $ and $ v $ $ (0 \le u,v \le 10^{18}) $ .

## 输出格式

If there's no array that satisfies the condition, print "-1". Otherwise:

The first line should contain one integer, $ n $ , representing the length of the desired array. The next line should contain $ n $ positive integers, the array itself. If there are multiple possible answers, print any.

## 说明/提示

In the first sample, $ 3\oplus 1 = 2 $ and $ 3 + 1 = 4 $ . There is no valid array of smaller length.

Notice that in the fourth sample the array is empty.

## 样例 #1

### 输入

```
2 4
```

### 输出

```
2
3 1
```

## 样例 #2

### 输入

```
1 3
```

### 输出

```
3
1 1 1
```

## 样例 #3

### 输入

```
8 5
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
0 0
```

### 输出

```
0
```

