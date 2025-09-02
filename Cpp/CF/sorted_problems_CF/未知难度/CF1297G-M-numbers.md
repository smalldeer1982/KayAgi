---
title: "M-numbers"
layout: "post"
diff: 难度0
pid: CF1297G
tag: []
---

# M-numbers

## 题目描述

For a given positive integer $ m $ , a positive number is called a $ m $ -number if the product of its digits is $ m $ . For example, the beginning of a series of $ 24 $ -numbers are as follows: $ 38 $ , $ 46 $ , $ 64 $ , $ 83 $ , $ 138 $ , $ 146 $ , $ 164 $ , $ 183 $ , $ 226 $ ...

You are given a positive integer $ m $ and $ k $ . Print $ k $ -th among $ m $ -numbers if all $ m $ -numbers are sorted in ascending order.

## 输入格式

A single line of input contains two integers $ m $ and $ k $ ( $ 2 \le m \le 10^9 $ , $ 1 \le k \le 10^9 $ ).

## 输出格式

Print the desired number — $ k $ -th among all $ m $ -numbers if $ m $ -numbers are sorted in ascending order. If the answer does not exist, print -1.

## 样例 #1

### 输入

```
24 9
```

### 输出

```
226
```

## 样例 #2

### 输入

```
24 1
```

### 输出

```
38
```

## 样例 #3

### 输入

```
5040 1000000000
```

### 输出

```
111121111315213227111
```

## 样例 #4

### 输入

```
2020 2020
```

### 输出

```
-1
```

