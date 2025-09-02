---
title: "Display Size"
layout: "post"
diff: 入门
pid: CF747A
tag: ['数学', '枚举']
---

# Display Size

## 题目描述

A big company decided to launch a new series of rectangular displays, and decided that the display must have exactly $ n $ pixels.

Your task is to determine the size of the rectangular display — the number of lines (rows) of pixels $ a $ and the number of columns of pixels $ b $ , so that:

- there are exactly $ n $ pixels on the display;
- the number of rows does not exceed the number of columns, it means $ a<=b $ ;
- the difference $ b-a $ is as small as possible.

## 输入格式

The first line contains the positive integer $ n $ ( $ 1<=n<=10^{6} $ ) — the number of pixels display should have.

## 输出格式

Print two integers — the number of rows and columns on the display.

## 说明/提示

In the first example the minimum possible difference equals 2, so on the display should be 2 rows of 4 pixels.

In the second example the minimum possible difference equals 0, so on the display should be 8 rows of 8 pixels.

In the third example the minimum possible difference equals 4, so on the display should be 1 row of 5 pixels.

## 样例 #1

### 输入

```
8

```

### 输出

```
2 4

```

## 样例 #2

### 输入

```
64

```

### 输出

```
8 8

```

## 样例 #3

### 输入

```
5

```

### 输出

```
1 5

```

## 样例 #4

### 输入

```
999999

```

### 输出

```
999 1001

```

