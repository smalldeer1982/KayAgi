---
title: "Colored Balls"
layout: "post"
diff: 普及+/提高
pid: CF1954D
tag: ['动态规划 DP']
---

# Colored Balls

## 题目描述

There are balls of $ n $ different colors; the number of balls of the $ i $ -th color is $ a_i $ .

The balls can be combined into groups. Each group should contain at most $ 2 $ balls, and no more than $ 1 $ ball of each color.

Consider all $ 2^n $ sets of colors. For a set of colors, let's denote its value as the minimum number of groups the balls of those colors can be distributed into. For example, if there are three colors with $ 3 $ , $ 1 $ and $ 7 $ balls respectively, they can be combined into $ 7 $ groups (and not less than $ 7 $ ), so the value of that set of colors is $ 7 $ .

Your task is to calculate the sum of values over all $ 2^n $ possible sets of colors. Since the answer may be too large, print it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the number of colors.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 5000 $ ) — the number of balls of the $ i $ -th color.

Additional constraint on input: the total number of balls doesn't exceed $ 5000 $ .

## 输出格式

Print a single integer — the sum of values of all $ 2^n $ sets of colors, taken modulo $ 998\,244\,353 $ .

## 说明/提示

Consider the first example. There are $ 8 $ sets of colors:

- for the empty set, its value is $ 0 $ ;
- for the set $ \{1\} $ , its value is $ 1 $ ;
- for the set $ \{2\} $ , its value is $ 1 $ ;
- for the set $ \{3\} $ , its value is $ 2 $ ;
- for the set $ \{1,2\} $ , its value is $ 1 $ ;
- for the set $ \{1,3\} $ , its value is $ 2 $ ;
- for the set $ \{2,3\} $ , its value is $ 2 $ ;
- for the set $ \{1,2,3\} $ , its value is $ 2 $ .

So, the sum of values over all $ 2^n $ sets of colors is $ 11 $ .

## 样例 #1

### 输入

```
3
1 1 2
```

### 输出

```
11
```

## 样例 #2

### 输入

```
1
5
```

### 输出

```
5
```

## 样例 #3

### 输入

```
4
1 3 3 7
```

### 输出

```
76
```

