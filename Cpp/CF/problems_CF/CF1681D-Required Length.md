---
title: "Required Length"
layout: "post"
diff: 普及/提高-
pid: CF1681D
tag: ['动态规划 DP', '枚举', '广度优先搜索 BFS']
---

# Required Length

## 题目描述

You are given two integer numbers, $ n $ and $ x $ . You may perform several operations with the integer $ x $ .

Each operation you perform is the following one: choose any digit $ y $ that occurs in the decimal representation of $ x $ at least once, and replace $ x $ by $ x \cdot y $ .

You want to make the length of decimal representation of $ x $ (without leading zeroes) equal to $ n $ . What is the minimum number of operations required to do that?

## 输入格式

The only line of the input contains two integers $ n $ and $ x $ ( $ 2 \le n \le 19 $ ; $ 1 \le x < 10^{n-1} $ ).

## 输出格式

Print one integer — the minimum number of operations required to make the length of decimal representation of $ x $ (without leading zeroes) equal to $ n $ , or $ -1 $ if it is impossible.

## 说明/提示

In the second example, the following sequence of operations achieves the goal:

1. multiply $ x $ by $ 2 $ , so $ x = 2 \cdot 2 = 4 $ ;
2. multiply $ x $ by $ 4 $ , so $ x = 4 \cdot 4 = 16 $ ;
3. multiply $ x $ by $ 6 $ , so $ x = 16 \cdot 6 = 96 $ ;
4. multiply $ x $ by $ 9 $ , so $ x = 96 \cdot 9 = 864 $ .

## 样例 #1

### 输入

```
2 1
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
4
```

## 样例 #3

### 输入

```
13 42
```

### 输出

```
12
```

