---
title: "Alyona and a Narrow Fridge"
layout: "post"
diff: 普及/提高-
pid: CF1119B
tag: []
---

# Alyona and a Narrow Fridge

## 题目描述

一个大小是 $2\times h$ 的冰箱（就是 $2$ 列 $h$ 行），有 $n$ 个瓶子，高度分别是 $a_1,a_2,\cdots,a_n$，要求把最多瓶子放进冰箱（要求按顺序）。

瓶子只能放在架子上。可以有任意多个架子。架子不能把瓶子砍成两瓣。

## 输入格式

第一行：$n(1\leq n\leq 10^3)$，$h(1\leq h\leq 10^9)$。

第二行：$a_1,a_2,\cdots,a_n(1\leq a_i\leq h)$。

## 输出格式

一行，一个数 $k$，表示能把 $a_1,a_2,\cdots,a_k$ 放进冰箱。

### 样例解释

样例 1：![1.png](https://i.loli.net/2019/04/09/5cac975d6b989.png)  
样例 2：![2.png](https://i.loli.net/2019/04/09/5cac975d4dd86.png)  
样例 3：![3.png](https://i.loli.net/2019/04/09/5cac975d4b839.png)

## 样例 #1

### 输入

```
5 7
2 3 5 4 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
10 10
9 1 1 1 1 1 1 1 1 1

```

### 输出

```
4

```

## 样例 #3

### 输入

```
5 10
3 1 4 2 4

```

### 输出

```
5

```

