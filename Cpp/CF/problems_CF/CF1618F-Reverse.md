---
title: "Reverse"
layout: "post"
diff: 普及+/提高
pid: CF1618F
tag: []
---

# Reverse

## 题目描述

You are given two positive integers $ x $ and $ y $ . You can perform the following operation with $ x $ : write it in its binary form without leading zeros, add $ 0 $ or $ 1 $ to the right of it, reverse the binary form and turn it into a decimal number which is assigned as the new value of $ x $ .

For example:

- $ 34 $ can be turned into $ 81 $ via one operation: the binary form of $ 34 $ is $ 100010 $ , if you add $ 1 $ , reverse it and remove leading zeros, you will get $ 1010001 $ , which is the binary form of $ 81 $ .
- $ 34 $ can be turned into $ 17 $ via one operation: the binary form of $ 34 $ is $ 100010 $ , if you add $ 0 $ , reverse it and remove leading zeros, you will get $ 10001 $ , which is the binary form of $ 17 $ .
- $ 81 $ can be turned into $ 69 $ via one operation: the binary form of $ 81 $ is $ 1010001 $ , if you add $ 0 $ , reverse it and remove leading zeros, you will get $ 1000101 $ , which is the binary form of $ 69 $ .
- $ 34 $ can be turned into $ 69 $ via two operations: first you turn $ 34 $ into $ 81 $ and then $ 81 $ into $ 69 $ .

Your task is to find out whether $ x $ can be turned into $ y $ after a certain number of operations (possibly zero).

## 输入格式

The only line of the input contains two integers $ x $ and $ y $ ( $ 1 \le x, y \le 10^{18} $ ).

## 输出格式

Print YES if you can make $ x $ equal to $ y $ and NO if you can't.

## 说明/提示

In the first example, you don't even need to do anything.

The fourth example is described in the statement.

## 样例 #1

### 输入

```
3 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
7 4
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
2 8
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
34 69
```

### 输出

```
YES
```

## 样例 #5

### 输入

```
8935891487501725 71487131900013807
```

### 输出

```
YES
```

